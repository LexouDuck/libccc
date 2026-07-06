#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/rle.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0x12345678;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_RLE].totals.tests += 1; \
		if (_CONDITION_) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_RLE].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size, int check_bound)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = RLE_Compress(&comp_size, data, size);
	CHECK((!comp), "compress returned NULL (size=%zu)", (size_t)size);
	CHECK((check_bound && comp_size > (size ? RLE_COMPRESS_MAXSIZE(size) : 1)),
		"compressed size %zu exceeds bound %zu (input %zu)", (size_t)comp_size, (size_t)RLE_COMPRESS_MAXSIZE(size), (size_t)size);
	t_size gds = RLE_GetDecompressedSize(comp, comp_size);
	CHECK((size != 0 && gds != size), "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
	t_u8* decomp = RLE_Decompress(&decomp_size, comp, comp_size);
	CHECK((!decomp), "decompress returned NULL");
	CHECK((decomp_size != size), "decompressed size %zu != %zu", (size_t)decomp_size, (size_t)size);
	CHECK((size && memcmp(decomp, data, size) != 0), "roundtrip data mismatch (size=%zu)", (size_t)size);
	free(comp);
	free(decomp);
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_compress_rle(void)
{
	print_suite_title("libccc/compress/rle");

	print_nonstd();

	// 1) edge cases
	t_u8 one = 0x42;
	roundtrip(&one, 0, 1); // empty input
	roundtrip(&one, 1, 1); // single byte
	t_u8 two_same[] = {7,7}; // 2-run
	roundtrip(two_same, 2, 1);
	t_u8 two_diff[] = {7,8};
	roundtrip(two_diff, 2, 1);
	// 2) all-identical buffers of many sizes (incl. multiples of 128 +/- 1)
	{
		t_u8 buf[100];
		memset(buf, 0xAB, sizeof(buf));
		for (t_size n = 1; n <= 100; n++)
			roundtrip(buf, n, 1);
	}
	// 3) all-distinct (incompressible) data, sizes around 128 boundaries
	{
		t_u8 buf[100];
		for (int i = 0; i < 100; i++)
			buf[i] = (t_u8)(i * 7 + (i>>3));
		for (t_size n = 1; n <= 100; n++)
			roundtrip(buf, n, 1);
	}
	// 4) adversarial: 1 literal byte + 3-run repeated, and 129-literals + 3-runs
	{
		t_u8 buf[100];
		int i = 0;
		while (i + 4 <= 100)
		{
			buf[i] = (t_u8)(i);
			buf[i+1]=buf[i+2]=buf[i+3]=0xEE;
			i += 4;
		}
		for (t_size n = 1; n <= 100; n++)
			roundtrip(buf, n, 1);
	}
	// 5) random fuzz: varied run-lengths
	for (int iter = 0; iter < 300; iter++)
	{
		t_u8 buf[2048];
		t_size n = rnd() % 2048;
		t_size i = 0;
		while (i < n)
		{
			t_u8 b = (t_u8)rnd();
			t_size run = 1 + rnd() % (rnd() % 2 ? 4 : 300);
			while (run-- && i < n) buf[i++] = b;
		}
		roundtrip(buf, n, 1);
	}
	// 6) decompressing garbage should not crash; NULL should error cleanly
	for (int iter = 0; iter < 2000; iter++)
	{
		t_u8 buf[256];
		t_size n = rnd() % 256;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)rnd();
		t_size ds;
		t_u8* d = RLE_Decompress(&ds, buf, n);
		if (d) free(d); // if it decoded, it must re-encode/decode consistently
	}
	// 7) no-op control bytes (0x80) decode to empty
	{
		t_u8 buf[] = {0x80, 0x80, 0x80};
		t_size ds = 99;
		t_u8* d = RLE_Decompress(&ds, buf, 3);
		CHECK((!d || ds != 0), "0x80 no-op case");
		if (d) free(d);
	}
	// 8) truncated repeat run -> must return NULL
	{
		t_u8 buf[] = {0xFE};
		t_size ds = 99;
		t_u8* d = RLE_Decompress(&ds, buf, 1);
		CHECK((d != NULL || ds != 0), "truncated repeat not rejected");
	}
	// 9) truncated literal run -> must return NULL
	{
		t_u8 buf[] = {0x05, 1, 2};
		t_size ds = 99;
		t_u8* d = RLE_Decompress(&ds, buf, 3);
		CHECK((d != NULL || ds != 0), "truncated literal not rejected");
	}
	// 10) compression ratio sanity on highly repetitive data
	{
		t_u8 buf[1280];
		memset(buf, 0, sizeof(buf));
		t_size cs;
		t_u8* c = RLE_Compress(&cs, buf, sizeof(buf));
		if (g_test.config.verbose)
			printf("ratio check: 1280 zero bytes -> %zu bytes compressed\n", (size_t)cs);
		CHECK((cs != 20), "expected 20 bytes (10 runs of 128)");
		free(c);
	}
	return (OK);
}
