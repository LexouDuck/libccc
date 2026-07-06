#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/lzss.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0xC0FFEE42;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_LZSS].totals.tests += 1; \
		if (!(_CONDITION_)) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_LZSS].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = LZSS_Compress(&comp_size, data, size);
	CHECK(comp != NULL, "compress returned NULL (size=%zu)", (size_t)size);
	if (!comp) return;
	CHECK(comp_size <= (t_size)LZSS_COMPRESS_MAXSIZE(size),
		"compressed size %zu exceeds bound %zu (input %zu)",
		(size_t)comp_size, (size_t)LZSS_COMPRESS_MAXSIZE(size), (size_t)size);
	t_size gds = LZSS_GetDecompressedSize(comp, comp_size);
	CHECK(gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
	t_u8* decomp = LZSS_Decompress(&decomp_size, comp, comp_size);
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

int		testsuite_compress_lzss(void)
{
	print_suite_title("libccc/compress/lzss");

	print_nonstd();

	if (g_test.config.verbose)
		printf("=== testing LZSS (fill byte 0x%02X) ===\n", LIBCONFIG_COMPRESS_LZSS_FILLBYTE);
	// 1) edge cases
	t_u8 one = 0x42;
	roundtrip(&one, 0);
	roundtrip(&one, 1);
	{	// empty input must compress to an empty stream
		t_size cs;
		t_u8* c = LZSS_Compress(&cs, &one, 0);
		CHECK(c != NULL && cs == 0, "compress(empty) is not an empty stream");
		free(c);
	}
	// 2) repeated runs (overlapping matches), various lengths incl. window-scale
	{
		static t_u8 buf[70000];
		memset(buf, 0x5A, sizeof(buf));
		t_size sizes[] = {2,3,4,17,18,19,255,4095,4096,4097,65536,70000};
		for (unsigned i = 0; i < sizeof(sizes)/sizeof(*sizes); i++)
		roundtrip(buf, sizes[i]);
	}
	// 3) leading spaces (interacts with the space-filled window on the Okumura side)
	{
		static t_u8 buf[10000];
		memset(buf, ' ', sizeof(buf));
		roundtrip(buf, sizeof(buf));
		for (t_size i = 5000; i < sizeof(buf); i++)
			buf[i] = (t_u8)rnd();
		roundtrip(buf, sizeof(buf));
	}
	// 4) periodic patterns straddling the window/distance boundary
	{
		static t_u8 buf[60000];
		t_size periods[] = {1,2,3,17,18,19,4077,4078,4079,4095,4096,4097};
		for (unsigned p = 0; p < sizeof(periods)/sizeof(*periods); p++)
		{
			for (t_size i = 0; i < sizeof(buf); i++)
				buf[i] = (t_u8)((i / 3) % periods[p]);
		  	roundtrip(buf, sizeof(buf));
		}
	}
	// 5) incompressible data (worst-case bound check)
	{
		static t_u8 buf[300000];
		for (t_size i = 0; i < sizeof(buf); i++)
			buf[i] = (t_u8)rnd();
		for (t_size n = 1; n <= 80; n++)
			roundtrip(buf, n);
		roundtrip(buf, sizeof(buf));
		t_size cs;
		t_u8* c = LZSS_Compress(&cs, buf, sizeof(buf));
		if (g_test.config.verbose)
			printf("incompressible: %zu -> %zu bytes (bound %zu)\n",
		(size_t)sizeof(buf), (size_t)cs, (size_t)LZSS_COMPRESS_MAXSIZE(sizeof(buf)));
		free(c);
	}
	// 6) text-like data (ratio sanity)
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
		t_u8* c = LZSS_Compress(&cs, buf, n);
		if (g_test.config.verbose)
			printf("ratio check: %zu bytes of text -> %zu bytes\n", (size_t)n, (size_t)cs);
		CHECK(cs < n / 2, "expected <50%% size on repetitive text");
		free(c);
	}
	// 7) random fuzz roundtrips with varied structure
	for (int iter = 0; iter < 400; iter++)
	{
		static t_u8 buf[40000];
		t_size n = rnd() % 40000;
		for (t_size i = 0; i < n; i++)
		{
			unsigned r = rnd() % 100;
			if (i > 0 && r < 45)
			{
				t_size src = rnd() % i;
				t_size ln = 1 + rnd() % 64;
				for (t_size k = 0; k < ln && i < n; k++, i++)
					buf[i] = buf[src + (k % (i - src ? i - src : 1))];
				if (i) i--;
			}
			else buf[i] = (t_u8)(rnd() % (1 + rnd() % 255));
		}
		roundtrip(buf, n);
	}
	// 8) hand-built decode vectors
	{
		t_size ds;
		CHECK(LZSS_Decompress(&ds, NULL, 5) == NULL, "NULL data accepted");
		t_u8 lit[] = {0x01, 0x41}; // flag: 1 literal, 'A'
		t_u8* d = LZSS_Decompress(&ds, lit, 2);
		CHECK(d && ds == 1 && d[0] == 'A', "single literal vector failed");
		free(d);
		t_u8 fill[] = {0x00, 0x00, 0x0F}; // pair: ring position 0, length 18 -> pristine window
		d = LZSS_Decompress(&ds, fill, 3);
		CHECK(d && ds == 18, "fill-byte vector: wrong size");
		if (d) for (int k = 0; k < 18; k++)
			CHECK(d[k] == LIBCONFIG_COMPRESS_LZSS_FILLBYTE, "fill-byte vector: byte %d is 0x%02X", k, d[k]);
		free(d);
		t_u8 lone = 0xFF; // flag byte, then end of input: valid, produces nothing
		d = LZSS_Decompress(&ds, &lone, 1);
		CHECK(d != NULL && ds == 0, "lone flag byte rejected");
		free(d);
		t_u8 trunc[] = {0x00, 0x12}; // pair item, but only 1 byte follows
		CHECK(LZSS_Decompress(&ds, trunc, 2) == NULL, "truncated match item accepted");
		d = LZSS_Decompress(&ds, trunc, 0); // empty stream: valid, empty output
		CHECK(d != NULL && ds == 0, "empty stream rejected");
		free(d);
	}
	// 9) decompressing garbage must never crash
	for (int iter = 0; iter < 5000; iter++)
	{
		t_u8 buf[600];
		t_size n = rnd() % 600;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)rnd();
		t_size ds;
			t_u8* d = LZSS_Decompress(&ds, buf, n);
		if (d) free(d);
	}
	// 9b) bit-flip/truncation mutation fuzz on valid streams
	for (int iter = 0; iter < 3000; iter++)
	{
		t_u8 buf[800];
		t_size n = 1 + rnd() % 800;
		for (t_size i = 0; i < n; i++)
			buf[i] = (t_u8)(rnd() % (1 + rnd() % 40));
		t_size cs;
		t_u8* c = LZSS_Compress(&cs, buf, n);
		if (!c || !cs)
		{
			free(c);
			continue;
		}
		c[rnd() % cs] ^= (t_u8)(1 << (rnd() % 8));
		t_size ds;
		t_u8* d = LZSS_Decompress(&ds, c, rnd() % (cs + 1));
		if (d) free(d);
		free(c);
	}
	return (OK);
}
