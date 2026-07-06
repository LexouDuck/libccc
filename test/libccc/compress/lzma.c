#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/lzma.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0xBADC0DE5;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_LZMA].totals.tests += 1; \
		if (!(_CONDITION_)) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_LZMA].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = LZMA_Compress(&comp_size, data, size);
	CHECK(comp != NULL, "compress returned NULL (size=%zu)", (size_t)size);
	if (!comp) return;
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_ALONE)
	CHECK(comp[0] == LZMA_PROPSBYTE, "bad properties byte 0x%02X", comp[0]);
	t_u64 hdr_size = 0;
	for (int i = 0; i < 8; i++) hdr_size |= ((t_u64)comp[5 + i] << (i * 8));
	CHECK(hdr_size == size, "header size mismatch");
	t_size gds = LZMA_GetDecompressedSize(comp, comp_size);
	CHECK(gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
#else
	t_size gds = LZMA_GetDecompressedSize(comp, comp_size); // full decode for RAW
	CHECK(gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
#endif
	t_u8* decomp = LZMA_Decompress(&decomp_size, comp, comp_size);
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

int		testsuite_compress_lzma(void)
{
	print_suite_title("libccc/compress/lzma");

	print_nonstd();

	if (g_test.config.verbose)
		printf("=== testing LZMA format %d (lc=%d lp=%d pb=%d) ===\n",
			LIBCONFIG_COMPRESS_LZMA_FORMAT,
			LIBCONFIG_COMPRESS_LZMA_LC,
			LIBCONFIG_COMPRESS_LZMA_LP,
			LIBCONFIG_COMPRESS_LZMA_PB);
	// 1) edge cases
	t_u8 one = 0x42;
	roundtrip(&one, 0);
	roundtrip(&one, 1);
	t_u8 tiny[] = {1,2,2,1,2,2,1,2,2};
	for (t_size n = 1; n <= 9; n++) roundtrip(tiny, n);
	// 2) all-identical buffers (short reps + rep matches + matched literals)
	{
		static t_u8 buf[70000];
		memset(buf, 0x5A, sizeof(buf));
		t_size sizes[] = {2,3,4,5,273,274,300,4096,70000};
		for (unsigned i = 0; i < sizeof(sizes)/sizeof(*sizes); i++)
			roundtrip(buf, sizes[i]);
	}
	// 3) incompressible data (worst case for the adaptive model; encoder growth path)
	{
		static t_u8 buf[200000];
		for (t_size i = 0; i < sizeof(buf); i++)
			buf[i] = (t_u8)rnd();
		for (t_size n = 1; n <= 40; n++)
			roundtrip(buf, n);
		roundtrip(buf, 5000);
		roundtrip(buf, sizeof(buf));
	}
	// 4) repetitive text (rep-distance heavy)
	{
		static t_u8 buf[65536];
		const char* words[] = {"hello ","world ","foo ","hello world "};
		t_size n = 0;
		while (n < 60000)
		{
			const char* w = words[rnd()%4];
			memcpy(buf+n, w, strlen(w));
			n += strlen(w);
		}
		roundtrip(buf, n);
		t_size cs; t_u8* c = LZMA_Compress(&cs, buf, n);
		if (g_test.config.verbose)
			printf("ratio check: %zu bytes of repetitive text -> %zu bytes\n", (size_t)n, (size_t)cs);
		CHECK(cs < n / 4, "expected at least 4x compression on repetitive text");
		free(c);
	}
	// 5) structured data with periodic patterns (exercises pb/lp contexts and dist_align)
	{
		static t_u8 buf[50000];
		for (unsigned period = 1; period <= 24; period++)
		{
			for (t_size i = 0; i < sizeof(buf); i++)
				buf[i] = (t_u8)((i % period) * 7 + (i / 512));
			roundtrip(buf, 2000 + period * 1500);
		}
	}
	// 6) random fuzz with varied structures (rep/match/literal mixing, large distances)
	for (int iter = 0; iter < 150; iter++)
	{
		static t_u8 buf[60000];
		t_size n = rnd() % 60000;
		t_size i = 0;
		while (i < n)
		{
			if (rnd() % 3 == 0 && i > 4)
			{
				t_size src = rnd() % i;
				t_size len = 1 + rnd() % 1000;
				while (len-- && i < n)
				{
					buf[i] = buf[src++];
					i++;
				}
			}
			else {
				t_size len = 1 + rnd() % 20;
				t_u8 b = (t_u8)rnd();
				while (len-- && i < n) buf[i++] = (rnd()%2) ? b : (t_u8)rnd();
			}
		}
		roundtrip(buf, n);
	}
	// 7) decompressing garbage must never crash, and must fail cleanly or produce something
	for (int iter = 0; iter < 2000; iter++)
	{
		t_u8 buf[300];
		t_size n = rnd() % 300;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)rnd();
		if (n > 13 && rnd() % 2)
		{
			buf[0] = (t_u8)(rnd() % 225);
			buf[13] = 0;
		} // semi-plausible headers
		t_size ds;
		t_u8* d = LZMA_Decompress(&ds, buf, n);
		if (d) free(d);
	}
	// 7b) bit-flip/truncation mutation fuzz on valid streams (must never crash)
	for (int iter = 0; iter < 1000; iter++)
	{
		t_u8 buf[500];
		t_size n = 1 + rnd() % 500;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)(rnd() % 7);
		t_size cs;
		t_u8* c = LZMA_Compress(&cs, buf, n);
		if (!c) continue;
		c[rnd() % cs] ^= (t_u8)(1 << (rnd() % 8));
		t_size ds;
		t_u8* d = LZMA_Decompress(&ds, c, rnd() % (cs + 1));
		if (d) free(d);
		free(c);
	}
	// 8) malformed inputs must be rejected (return NULL)
	{
		t_size ds;
		CHECK(LZMA_Decompress(&ds, NULL, 20) == NULL, "NULL data accepted");
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_ALONE)
		t_u8 shorthdr[] = {0x5D, 0, 0, 0x10};
		CHECK(LZMA_Decompress(&ds, shorthdr, sizeof(shorthdr)) == NULL, "truncated header accepted");
		t_u8 badprops[19] = {0};
		badprops[0] = 225;
		CHECK(LZMA_Decompress(&ds, badprops, sizeof(badprops)) == NULL, "invalid props byte accepted");
		t_u8 nonzero[19] = {0};
		nonzero[0] = 0x5D;
		nonzero[13] = 1; // first range-coder byte must be 0
		CHECK(LZMA_Decompress(&ds, nonzero, sizeof(nonzero)) == NULL, "nonzero first stream byte accepted");
		// truncated valid stream: cut a real compressed buffer in half
		static t_u8 buf[3000];
		for (t_size i = 0; i < sizeof(buf); i++)
			buf[i] = (t_u8)rnd();
		t_size cs;
		t_u8* c = LZMA_Compress(&cs, buf, sizeof(buf));
		CHECK(LZMA_Decompress(&ds, c, cs / 2) == NULL, "truncated stream accepted");
		free(c);
#endif
	}
	return (OK);
}
