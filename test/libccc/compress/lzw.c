#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libccc/compress/lzw.h"

#include "test.h"
#include "test_utils.h"



static unsigned rng_state = 0xC0FFEE42;
static unsigned rnd(void) { rng_state = rng_state * 1664525 + 1013904223; return rng_state >> 8; }

#define CHECK(_CONDITION_, _MESSAGE_, ...) \
	do { \
		g_test.suites[TESTSUITE_COMPRESS_LZW].totals.tests += 1; \
		if (!(_CONDITION_)) \
		{ \
			g_test.suites[TESTSUITE_COMPRESS_LZW].totals.failed += 1; \
			printf(ANSI_COLOR_FG_RED "TEST FAILED: "_MESSAGE_"\n"ANSI_RESET, ##__VA_ARGS__); \
		} \
	} while (0) \

static void roundtrip(t_u8 const* data, t_size size)
{
	t_size comp_size = 42, decomp_size = 42;
	t_u8* comp = LZW_Compress(&comp_size, data, size);
	CHECK(comp != NULL, "compress returned NULL (size=%zu)", (size_t)size);
	if (!comp) return;
	CHECK(comp_size <= (t_size)LZW_COMPRESS_MAXSIZE(size),
		"compressed size %zu exceeds bound %zu (input %zu)",
		(size_t)comp_size, (size_t)LZW_COMPRESS_MAXSIZE(size), (size_t)size);
#if (LZW_HEADER_SIZE > 0)
	CHECK(comp[0] == LZW_HEADER_MAGIC_0 && comp[1] == LZW_HEADER_MAGIC_1, "bad magic bytes");
	CHECK((comp[2] & 0x1F) == LZW_MAXBITS && (comp[2] & 0x80), "bad header flags byte 0x%02X", comp[2]);
#endif
	t_size gds = LZW_GetDecompressedSize(comp, comp_size);
	CHECK(gds == size, "GetDecompressedSize %zu != %zu", (size_t)gds, (size_t)size);
	t_u8* decomp = LZW_Decompress(&decomp_size, comp, comp_size);
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

int		testsuite_compress_lzw(void)
{
	print_suite_title("libccc/compress/lzw");

	print_nonstd();

	if (g_test.config.verbose)
		printf("=== testing LZW format %d, maxbits %d ===\n", LIBCONFIG_COMPRESS_LZW_FORMAT, LZW_MAXBITS);
	// 1) edge cases
	t_u8 one = 0x42;
	roundtrip(&one, 0);
	roundtrip(&one, 1);
	t_u8 tiny[] = {1,2,2,1,2,2,1,2,2};
	for (t_size n = 1; n <= 9; n++) roundtrip(tiny, n);
	// 2) all-identical buffers (exercises the KwKwK case intensely)
	{
		static t_u8 buf[70000]; memset(buf, 0x5A, sizeof(buf));
		t_size sizes[] = {2,3,4,5,255,256,257,511,512,513,4095,4096,4097,65535,65536,70000};
		for (unsigned i = 0; i < sizeof(sizes)/sizeof(*sizes); i++) roundtrip(buf, sizes[i]);
	}
	// 3) incompressible data (worst-case bound + dictionary-full clears + all width transitions)
	{
		static t_u8 buf[300000]; for (t_size i = 0; i < sizeof(buf); i++) buf[i] = (t_u8)rnd();
		for (t_size n = 1; n <= 80; n++) roundtrip(buf, n);
		roundtrip(buf, 1000);
		roundtrip(buf, 65536);
		roundtrip(buf, sizeof(buf));
	}
	// 4) text-like repetitive data (ratio sanity)
	{
		static t_u8 buf[65536]; const char* words[] = {"hello ","world ","foo ","hello world "};
		t_size n = 0; while (n < 60000)
		{
			const char* w = words[rnd()%4];
			memcpy(buf+n, w, strlen(w));
			n += strlen(w);
		}
		roundtrip(buf, n);
		t_size cs; t_u8* c = LZW_Compress(&cs, buf, n);
		if (g_test.config.verbose)
			printf("ratio check: %zu bytes of repetitive text -> %zu bytes\n", (size_t)n, (size_t)cs);
		CHECK(cs < n / 2, "expected at least 2x compression on repetitive text");
		free(c);
	}
	// 5) alternating patterns of varying periods (stress dictionary paths near width changes)
	{
		static t_u8 buf[20000];
		for (unsigned period = 1; period <= 40; period++)
		{
			for (t_size i = 0; i < sizeof(buf); i++) buf[i] = (t_u8)(i % period);
		  roundtrip(buf, 500 + period * 400);
		}
	}
	// 6) random fuzz with varied structures
	for (int iter = 0; iter < 400; iter++)
	{
		static t_u8 buf[30000]; t_size n = rnd() % 30000; t_size i = 0;
		while (i < n)
		{
			if (rnd() % 3 == 0 && i > 4)
			{
				t_size src = rnd() % i; t_size len = 1 + rnd() % 800;
				while (len-- && i < n)
				{
					buf[i] = buf[src++]; i++;
				}
			}
			else {
				t_size len = 1 + rnd() % 20; t_u8 b = (t_u8)rnd();
				while (len-- && i < n) buf[i++] = (rnd()%2) ? b : (t_u8)rnd();
			}
		}
		roundtrip(buf, n);
	}
	// 7) decompressing garbage must never crash, and must fail cleanly or produce something valid
	for (int iter = 0; iter < 3000; iter++)
	{
		t_u8 buf[400]; t_size n = rnd() % 400;
		for (t_size i = 0; i < n; i++) buf[i] = (t_u8)rnd();
		t_size ds; t_u8* d = LZW_Decompress(&ds, buf, n);
		if (d) free(d);
	}
	// 7b) bit-flip/truncation mutation fuzz on valid streams (must never crash)
	for (int iter = 0; iter < 2000; iter++)
	{
		t_u8 buf[600]; t_size n = 1 + rnd() % 600;
		for (t_size i = 0; i < n; i++) buf[i] = (t_u8)(rnd() % 5);
		t_size cs; t_u8* c = LZW_Compress(&cs, buf, n);
		if (!c) continue;
		c[rnd() % cs] ^= (t_u8)(1 << (rnd() % 8));
		t_size ds; t_u8* d = LZW_Decompress(&ds, c, rnd() % (cs + 1));
		if (d) free(d);
		free(c);
	}
	// 8) malformed inputs must be rejected (return NULL)
	{
		t_size ds;
		CHECK(LZW_Decompress(&ds, NULL, 5) == NULL, "NULL data accepted");
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
		t_u8 badmagic[] = {0x1F, 0x9E, 0x90, 0x41};
		CHECK(LZW_Decompress(&ds, badmagic, sizeof(badmagic)) == NULL, "bad magic accepted");
		t_u8 shorthdr[] = {0x1F, 0x9D};
		CHECK(LZW_Decompress(&ds, shorthdr, sizeof(shorthdr)) == NULL, "truncated header accepted");
		t_u8 badbits[] = {0x1F, 0x9D, (t_u8)(0x80 | 31), 0x41}; // maxbits 31 > compiled max
		CHECK(LZW_Decompress(&ds, badbits, sizeof(badbits)) == NULL, "out-of-range maxbits accepted");
		// empty stream (header only) is VALID and decompresses to 0 bytes:
		t_u8 empty[] = {0x1F, 0x9D, (t_u8)(0x80 | LZW_MAXBITS)};
		t_u8* d = LZW_Decompress(&ds, empty, sizeof(empty));
		CHECK(d != NULL && ds == 0, "header-only stream rejected");
		free(d);
#endif
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_RAW && LZW_MAXBITS == 12)
		// hand-built vectors (9-bit codes, LSB-first packing):
		t_u8 empty_stream[] = {0x00, 0x03, 0x02}; // CLEAR(256), END(257)
		t_u8* d = LZW_Decompress(&ds, empty_stream, sizeof(empty_stream));
		CHECK(d != NULL && ds == 0, "hand-built empty stream rejected");
		free(d);
		t_size cs; t_u8* c = LZW_Compress(&cs, (t_u8 const*)"", 0);
		CHECK(c && cs == 3 && memcmp(c, empty_stream, 3) == 0, "compress(empty) != hand-built vector");
		free(c);
		t_u8 badcode[] = {0x00, 0x21, 0x03}; // CLEAR(256), then code 400 (not in dictionary)
		CHECK(LZW_Decompress(&ds, badcode, sizeof(badcode)) == NULL, "out-of-dictionary code accepted");
		t_u8 badfirst[] = {0x00, 0x05, 0x02}; // CLEAR(256), then code 258 (non-literal first code)
		CHECK(LZW_Decompress(&ds, badfirst, sizeof(badfirst)) == NULL, "non-literal first code accepted");
		t_u8 noend[] = {0x00, 0x83, 0x00}; // CLEAR(256), literal 'A'(65), no END code
		CHECK(LZW_Decompress(&ds, noend, sizeof(noend)) == NULL, "stream with missing END code accepted");
#endif
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_TIFF)
		// hand-built vectors (9-bit codes, MSB-first packing):
		t_u8 empty_stream[] = {0x80, 0x40, 0x40}; // CLEAR(256), END(257)
		t_u8* d = LZW_Decompress(&ds, empty_stream, sizeof(empty_stream));
		CHECK(d != NULL && ds == 0, "hand-built empty stream rejected");
		free(d);
		t_size cs; t_u8* c = LZW_Compress(&cs, (t_u8 const*)"", 0);
		CHECK(c && cs == 3 && memcmp(c, empty_stream, 3) == 0, "compress(empty) != hand-built vector");
		free(c);
#endif
	}
	return (OK);
}
