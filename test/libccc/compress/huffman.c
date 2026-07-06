#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/huffman.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0xFEEDBEEF;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_HUFFMAN].totals.tests += 1; \
		if (!(_CONDITION_)) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_HUFFMAN].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = HUFFMAN_Compress(&comp_size, data, size);
	CHECK(comp != NULL, "compress returned NULL (size=%zu)", (size_t)size);
	if (!comp) return;
	CHECK(comp_size <= (t_size)HUFFMAN_COMPRESS_MAXSIZE(size),
		"compressed size %zu exceeds bound %zu (input %zu)",
		(size_t)comp_size, (size_t)HUFFMAN_COMPRESS_MAXSIZE(size), (size_t)size);
	t_size gds = HUFFMAN_GetDecompressedSize(comp, comp_size);
	CHECK(gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
	t_u8* decomp = HUFFMAN_Decompress(&decomp_size, comp, comp_size);
	CHECK(decomp != NULL, "decompress returned NULL (size=%zu)", (size_t)size);
	if (decomp)
	{
		CHECK(decomp_size == size, "decompressed size %zu != %zu", (size_t)decomp_size, (size_t)size);
		CHECK(size == 0 || memcmp(decomp, data, size) == 0, "roundtrip data mismatch (size=%zu)", (size_t)size);
		free(decomp);
	}
	free(comp);
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_compress_huffman(void)
{
	print_suite_title("libccc/compress/huffman");

	print_nonstd();

	if (g_test.config.verbose)
		printf("=== testing HUFFMAN format %d ===\n", LIBCONFIG_COMPRESS_HUFFMAN_FORMAT);
	// 1) edge cases: empty, single byte, single repeated byte (degenerate trees)
	t_u8 one = 0x42;
	roundtrip(&one, 0);
	roundtrip(&one, 1);
	{
		static t_u8 buf[70000];
		memset(buf, 0x5A, sizeof(buf));
		t_size sizes[] = {2,3,255,256,4096,65536,70000};
		for (unsigned i = 0; i < sizeof(sizes)/sizeof(*sizes); i++)
			roundtrip(buf, sizes[i]);
	}
	// 2) two/few distinct symbols, extreme skew
	{
		static t_u8 buf[100000];
		for (t_size i = 0; i < sizeof(buf); i++)
			buf[i] = (rnd() % 1000 == 0) ? 0xFF : 0x00;
		roundtrip(buf, sizeof(buf));
	}
	// 3) Fibonacci frequencies: forces a Huffman tree deeper than 15 levels, exercising the length-limiting path
	{
		static t_u8 buf[130000]; t_size n = 0;
		unsigned fa = 1, fb = 1;
		for (unsigned sym = 0; sym < 24; sym++)
		{
			for (unsigned k = 0; k < fa && n < sizeof(buf); k++)
				buf[n++] = (t_u8)sym;
			unsigned t = fa + fb;
			fa = fb;
			fb = t;
		}
		if (g_test.config.verbose)
			printf("fibonacci input: %zu bytes, 24 distinct symbols\n", (size_t)n);
		roundtrip(buf, n);
		// also shuffled (same frequencies, interleaved)
		for (t_size i = n; i-- > 1;)
		{
			t_size j = rnd() % (i + 1);
			t_u8 t = buf[i];
			buf[i] = buf[j];
			buf[j] = t;
		}
		roundtrip(buf, n);
	}
	// 4) uniform random (incompressible; all 256 symbols, ~8bit entropy)
	{
		static t_u8 buf[300000];
		for (t_size i = 0; i < sizeof(buf); i++)
			buf[i] = (t_u8)rnd();
		for (t_size n = 1; n <= 80; n++)
			roundtrip(buf, n);
		roundtrip(buf, sizeof(buf));
		t_size cs; t_u8* c = HUFFMAN_Compress(&cs, buf, sizeof(buf));
		if (g_test.config.verbose)
			printf("incompressible: %zu -> %zu bytes (%.3f bits/byte)\n", (size_t)sizeof(buf), (size_t)cs, cs * 8.0 / sizeof(buf));
		CHECK(cs < sizeof(buf) + sizeof(buf) / 16 + 200, "incompressible overhead too large");
		free(c);
	}
	// 5) text-like data (skewed distribution; ratio sanity)
	{
		static t_u8 buf[65536];
		const char* words[] = {"hello ","world ","foo ","the quick brown fox "};
		t_size n = 0;
		while (n < 60000)
		{
			const char* w = words[rnd()%4];
			memcpy(buf+n, w, strlen(w));
			n += strlen(w);
		}
		roundtrip(buf, n);
		t_size cs;
		t_u8* c = HUFFMAN_Compress(&cs, buf, n);
		if (g_test.config.verbose)
			printf("ratio check: %zu bytes of text -> %zu bytes\n", (size_t)n, (size_t)cs);
		CHECK(cs < n * 7 / 10, "expected <70%% size on text");
		free(c);
	}
	// 6) random fuzz with varied alphabet sizes and skews
	for (int iter = 0; iter < 500; iter++)
	{
		static t_u8 buf[30000];
		t_size n = rnd() % 30000;
		unsigned alphabet = 1 + rnd() % 256;
		unsigned skew = 1 + rnd() % 8;
		for (t_size i = 0; i < n; i++)
		{
			unsigned v = rnd() % alphabet;
			for (unsigned s = 1; s < skew; s++)
				v = (v * (rnd() % alphabet)) / alphabet;
			buf[i] = (t_u8)v;
		}
		roundtrip(buf, n);
	}
	// 7) decompressing garbage must never crash
	for (int iter = 0; iter < 3000; iter++)
	{
		t_u8 buf[500];
		t_size n = rnd() % 500;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)rnd();
		t_size ds;
		t_u8* d = HUFFMAN_Decompress(&ds, buf, n);
		if (d) free(d);
	}
	// 7b) bit-flip/truncation mutation fuzz on valid streams
	for (int iter = 0; iter < 2000; iter++)
	{
		t_u8 buf[600];
		t_size n = 1 + rnd() % 600;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)(rnd() % (1 + rnd() % 40));
		t_size cs;
		t_u8* c = HUFFMAN_Compress(&cs, buf, n);
		if (!c) continue;
		c[rnd() % cs] ^= (t_u8)(1 << (rnd() % 8));
		t_size ds;
		t_u8* d = HUFFMAN_Decompress(&ds, c, rnd() % (cs + 1));
		if (d) free(d);
		free(c);
	}
	// 8) malformed inputs must be rejected
	{
		t_size ds;
		CHECK(HUFFMAN_Decompress(&ds, NULL, 5) == NULL, "NULL data accepted");
#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT == HUFFMAN_FORMAT_RAW)
		t_u8 tbl[200] = {0};
		CHECK(HUFFMAN_Decompress(&ds, tbl, 100) == NULL, "truncated table accepted");
		// valid degenerate table: only END, length 1; stream = one '0' bit
		memset(tbl, 0, sizeof(tbl));
		tbl[128] = 0x01;
		tbl[129] = 0x00;
		t_u8* d = HUFFMAN_Decompress(&ds, tbl, 130);
		CHECK(d != NULL && ds == 0, "valid degenerate stream rejected");
		free(d);
		t_size cs;
		t_u8* c = HUFFMAN_Compress(&cs, (t_u8 const*)"", 0);
		CHECK(c && cs == 130 && memcmp(c, tbl, 130) == 0, "compress(empty) != hand-built vector");
		free(c);
		memset(tbl, 0, sizeof(tbl)); tbl[128] = 0x02;
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "degenerate 2-bit code accepted");
		memset(tbl, 0, sizeof(tbl)); tbl[0] = 0x11; tbl[128] = 0x01; // three 1-bit codes: oversubscribed
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "oversubscribed table accepted");
		memset(tbl, 0, sizeof(tbl)); tbl[0] = 0x02; tbl[128] = 0x02; // two 2-bit codes: incomplete
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "incomplete table accepted");
		memset(tbl, 0, sizeof(tbl)); tbl[0] = 0x11; // syms 0,1 but no END code
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "table without END code accepted");
		memset(tbl, 0, sizeof(tbl)); tbl[128] = 0x11; // nonzero padding nibble
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "nonzero table padding accepted");
		memset(tbl, 0, sizeof(tbl)); tbl[0] = 0x01; tbl[128] = 0x01; tbl[129] = 0x00; // '0' = sym 0, then EOF
		CHECK(HUFFMAN_Decompress(&ds, tbl, 130) == NULL, "stream missing END code accepted");
#else
		t_u8 hdr[16] = {0x1F, 0x1E, 0,0,0,0, 1, 0, 0x41};
		t_u8 bad[16];
		memcpy(bad, hdr, sizeof(hdr)); bad[1] = 0x9D;
		CHECK(HUFFMAN_Decompress(&ds, bad, 9) == NULL, "bad magic accepted");
		memcpy(bad, hdr, sizeof(hdr)); bad[6] = 0;
		CHECK(HUFFMAN_Decompress(&ds, bad, 9) == NULL, "tree depth 0 accepted");
		memcpy(bad, hdr, sizeof(hdr)); bad[6] = 25;
		CHECK(HUFFMAN_Decompress(&ds, bad, 9) == NULL, "tree depth 25 accepted");
		CHECK(HUFFMAN_Decompress(&ds, hdr, 5) == NULL, "truncated header accepted");
		CHECK(HUFFMAN_Decompress(&ds, hdr, 8) == NULL, "truncated symbol table accepted");
		// size-field surgery on a valid stream: mismatches must be rejected
		t_u8 sample[] = "ABAB";
		t_size cs;
		t_u8* c = HUFFMAN_Compress(&cs, sample, 4);
		c[5] += 1; // header says 5 bytes, coded data has 4
		CHECK(HUFFMAN_Decompress(&ds, c, cs) == NULL, "premature end-of-block accepted");
		c[5] -= 2; // header says 3 bytes, coded data has 4
		CHECK(HUFFMAN_Decompress(&ds, c, cs) == NULL, "oversized coded data accepted");
		c[5] += 1;
		t_u8* d = HUFFMAN_Decompress(&ds, c, cs); // restored: must be valid again
		CHECK(d != NULL && ds == 4 && memcmp(d, sample, 4) == 0, "restored stream rejected");
		free(d);
		free(c);
		// duplicate symbol in the symbol table
		t_u8 dup[] = {0x1F, 0x1E, 0,0,0,2, 2, 1, 0, 0x41, 0x41, 0x00};
		CHECK(HUFFMAN_Decompress(&ds, dup, sizeof(dup)) == NULL, "duplicate symbol accepted");
#endif
	}
	return (OK);
}
