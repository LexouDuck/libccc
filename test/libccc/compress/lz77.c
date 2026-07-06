#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/lz77.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0xDEADBEEF;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_LZ77].totals.tests += 1; \
		if (!(_CONDITION_)) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_LZ77].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = LZ77_Compress(&comp_size, data, size);
	CHECK(comp != NULL, "compress returned NULL (size=%zu)", (size_t)size);
	if (!comp) return;
	CHECK(comp_size <= (t_size)LZ77_COMPRESS_MAXSIZE(size) + (size ? 0 : 1),
		"compressed size %zu exceeds bound %zu (input %zu)",
		(size_t)comp_size, (size_t)LZ77_COMPRESS_MAXSIZE(size), (size_t)size);
#if (LZ77_HEADER_SIZE > 0)
	CHECK(comp_size % 4 == 0, "compressed size %zu not padded to 4", (size_t)comp_size);
	CHECK(comp[0] == LZ77_HEADER_MAGIC, "bad magic byte 0x%02X", comp[0]);
	CHECK((t_size)(comp[1] | (comp[2] << 8) | ((t_size)comp[3] << 16)) == size, "header size mismatch");
#endif
	t_size gds = LZ77_GetDecompressedSize(comp, comp_size);
	CHECK(size == 0 || gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
	t_u8* decomp = LZ77_Decompress(&decomp_size, comp, comp_size);
	CHECK(decomp != NULL, "decompress returned NULL");
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

int		testsuite_compress_lz77(void)
{
	print_suite_title("libccc/compress/lz77");

	print_nonstd();

	if (g_test.config.verbose)
		printf("=== testing LZ77 format %d ===\n", LIBCONFIG_COMPRESS_LZ77_FORMAT);
	// 1) edge cases
	t_u8 one = 0x42;
	roundtrip(&one, 0);
	roundtrip(&one, 1);
	t_u8 tiny[] = {1,2,2,1,2,2,1,2,2};
	for (t_size n = 1; n <= 9; n++) roundtrip(tiny, n);
	// 2) all-identical buffers (exercises overlapping copies, dist == 1 unless MINDISTANCE > 1)
	{
		static t_u8 buf[70000];
		memset(buf, 0x5A, sizeof(buf));
		t_size sizes[] = {2,3,4,17,18,19,16,272,273,65807,65808,65809,70000};
		for (unsigned i = 0; i < sizeof(sizes)/sizeof(*sizes); i++)
			roundtrip(buf, sizes[i]);
	}
	// 3) incompressible data (worst-case bound), incl. flag-group boundaries
	{
		static t_u8 buf[4099];
		for (int i = 0; i < 4099; i++)
			buf[i] = (t_u8)rnd();
		for (t_size n = 1; n <= 130; n++)
			roundtrip(buf, n);
		roundtrip(buf, 4099);
	}
	// 4) text-like repetitive data
	{
		static t_u8 buf[8192];
		const char* words[] = {"hello ","world ","foo ","hello world "};
		t_size n = 0;
		while (n < 8000)
		{
			const char* w = words[rnd()%4];
			memcpy(buf+n, w, strlen(w));
			n += strlen(w);
		}
		roundtrip(buf, n);
		t_size cs;
		t_u8* c = LZ77_Compress(&cs, buf, n);
		if (g_test.config.verbose)
			printf("ratio check: %zu bytes of repetitive text -> %zu bytes\n", (size_t)n, (size_t)cs);
		CHECK(cs < n / 2, "expected at least 2x compression on repetitive text");
		free(c);
	}
	// 5) window-boundary: repetition exactly 4096/4097 bytes apart
	{
		static t_u8 buf[10000];
		for (int i = 0; i < 5000; i++)
			buf[i] = (t_u8)rnd();
		memcpy(buf + 4096 + 100, buf + 100, 200); // distance exactly 4096 from some positions
		roundtrip(buf, 8192);
	}
	// 6) random fuzz with varied run structures
	for (int iter = 0; iter < 500; iter++)
	{
		static t_u8 buf[8192];
		t_size n = rnd() % 8192;
		t_size i = 0;
		while (i < n)
		{
			if (rnd() % 3 == 0 && i > 4) // copy an earlier chunk (creates matches)
			{
				t_size src = rnd() % i;
				t_size len = 1 + rnd() % 600;
				while (len-- && i < n)
				{
					buf[i] = buf[src++];
					i++;
				}
			}
			else
			{
				t_size len = 1 + rnd() % 20;
				t_u8 b = (t_u8)rnd();
				while (len-- && i < n) buf[i++] = (rnd()%2) ? b : (t_u8)rnd();
			}
		}
		roundtrip(buf, n);
	}
	// 7) decompressing garbage must never crash, and must fail cleanly or roundtrip
	for (int iter = 0; iter < 3000; iter++)
	{
		t_u8 buf[300];
		t_size n = rnd() % 300;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)rnd();
		t_size ds;
		t_u8* d = LZ77_Decompress(&ds, buf, n);
		if (d) free(d);
	}
	// 8) malformed inputs must be rejected (return NULL)
	{
		t_size ds;
#if (LZ77_HEADER_SIZE > 0)
		t_u8 badmagic[] = {0xFF, 4, 0, 0,  0x00, 'a','b','c','d'};
		CHECK(LZ77_Decompress(&ds, badmagic, sizeof(badmagic)) == NULL, "bad magic accepted");
		t_u8 shorthdr[] = {LZ77_HEADER_MAGIC, 1, 0};
		CHECK(LZ77_Decompress(&ds, shorthdr, sizeof(shorthdr)) == NULL, "truncated header accepted");
		t_u8 sizemismatch[] = {LZ77_HEADER_MAGIC, 10, 0, 0,  0x00, 'a','b','c','d','e','f','g'};
		CHECK(LZ77_Decompress(&ds, sizemismatch, sizeof(sizemismatch)) == NULL, "truncated stream accepted");
		t_u8 baddist[] = {LZ77_HEADER_MAGIC, 5, 0, 0,  0x80, 0x00, 0x00, 0x00}; // 1st token = back-ref with produced == 0
		CHECK(LZ77_Decompress(&ds, baddist, sizeof(baddist)) == NULL, "invalid distance accepted");
		t_u8 badtoken[] = {LZ77_HEADER_MAGIC, 5, 0, 0,  0x40, 'a', 0x00}; // 2nd token = back-ref, truncated
		CHECK(LZ77_Decompress(&ds, badtoken, sizeof(badtoken)) == NULL, "truncated token accepted");
#else
		t_u8 baddist[] = {0x80, 0x00, 0x00}; // 1st token = back-ref with produced == 0
		CHECK(LZ77_Decompress(&ds, baddist, sizeof(baddist)) == NULL, "invalid distance accepted");
		t_u8 badtoken[] = {0x40, 'a', 0x00}; // 2nd token = back-ref, truncated
		CHECK(LZ77_Decompress(&ds, badtoken, sizeof(badtoken)) == NULL, "truncated token accepted");
#endif
		CHECK(LZ77_Decompress(&ds, NULL, 5) == NULL, "NULL data accepted");
	}
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_GBA)
	// 9) GBA interop: exact known-good compressed stream (hand-verified against GBATEK spec)
	{
		// 12 x 'A': literal 'A', then back-ref (len 11, dist 1) -> flags 0x40, token 0x80 0x00
		t_u8 data[12];
		memset(data, 'A', 12);
		t_u8 expected[] = {0x10, 12, 0, 0,  0x40, 'A', 0x80, 0x00};
		t_size cs;
		t_u8* c = LZ77_Compress(&cs, data, 12);
	#if (LIBCONFIG_COMPRESS_LZ77_MINDISTANCE == 1)
		CHECK(c && cs == 8 && memcmp(c, expected, 8) == 0, "GBA interop: compress vector mismatch");
	#endif
		free(c);
		// decode-only vector: "abc" + back-ref (len 7, dist 3) = "abcabcabca"
		t_u8 stream[] = {0x10, 10, 0, 0,  0x10, 'a','b','c', 0x40, 0x02,  0x00, 0x00};
		t_size ds;
		t_u8* d = LZ77_Decompress(&ds, stream, sizeof(stream));
		CHECK(d && ds == 10 && memcmp(d, "abcabcabca", 10) == 0, "GBA interop: decompress vector mismatch");
		free(d);
	}
#endif
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_NDS)
	// 9) NDS interop: decode-only vectors for the 3 token sizes (hand-built from the LZ11 spec)
	{
		// 'x' + 2-byte token (len 4, dist 1): b0 = ((4-1)<<4)|0 = 0x30, b1 = 0x00 -> "xxxxx"
		t_u8 s2[] = {0x11, 5, 0, 0,  0x40, 'x', 0x30, 0x00};
		t_size ds;
		t_u8* d = LZ77_Decompress(&ds, s2, sizeof(s2));
		CHECK(d && ds == 5 && memcmp(d, "xxxxx", 5) == 0, "NDS interop: 2-byte token vector mismatch");
		free(d);
		// 'y' + 3-byte token (len 17, dist 1): len-0x11 = 0 -> b0 = 0x00, b1 = 0x00, b2 = 0x00 -> 18 x 'y'
		t_u8 s3[] = {0x11, 18, 0, 0,  0x40, 'y', 0x00, 0x00, 0x00};
		d = LZ77_Decompress(&ds, s3, sizeof(s3));
		t_u8 exp3[18];
		memset(exp3, 'y', 18);
		CHECK(d && ds == 18 && memcmp(d, exp3, 18) == 0, "NDS interop: 3-byte token vector mismatch");
		free(d);
		// 'z' + 4-byte token (len 273, dist 1): len-0x111 = 0 -> b0 = 0x10, b1 = 0x00, b2 = 0x00, b3 = 0x00 -> 274 x 'z'
		t_u8 s4[] = {0x11, 0x12, 0x01, 0,  0x40, 'z', 0x10, 0x00, 0x00, 0x00};
		d = LZ77_Decompress(&ds, s4, sizeof(s4));
		CHECK(d && ds == 274, "NDS interop: 4-byte token vector mismatch (size)");
		if (d)
		{
			for (int i = 0; i < 274; i++) if (d[i] != 'z')
			{
				CHECK(0, "NDS interop: 4-byte token data mismatch");
				break;
			}
		}
		free(d);
	}
#endif
#if (LIBCONFIG_COMPRESS_LZ77_MINDISTANCE > 1)
	// 10) verify the compressor never emits a distance below the configured minimum
	{
		static t_u8 buf[5000];
		memset(buf, 0xEE, sizeof(buf));
		t_size cs;
		t_u8* c = LZ77_Compress(&cs, buf, sizeof(buf));
		t_size i = LZ77_HEADER_SIZE, produced = 0;
		while (produced < sizeof(buf) && i < cs)
		{
			t_u8 flags = c[i++];
			for (int b = 0; b < 8 && produced < sizeof(buf); b++)
			{
				if (flags & (0x80 >> b))
				{	// (this scan assumes the 2-byte RAW/GBA token format)
					t_size dist = (((t_size)(c[i] & 0xF) << 8) | c[i+1]) + 1;
					CHECK(dist >= LIBCONFIG_COMPRESS_LZ77_MINDISTANCE, "distance %zu below minimum", (size_t)dist);
					produced += (c[i] >> 4) + 3;
					i += 2;
				}
				else
				{
					produced += 1;
					i += 1;
				}
			}
		}
		roundtrip(buf, sizeof(buf));
		free(c);
	}
#endif
	return (OK);
}
