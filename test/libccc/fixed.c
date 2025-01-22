
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/math.h"

#include "test.h"
#include "test_utils.h"



// Disable certain GCC warnings temporarily
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-overflow"
// Disable certain clang warnings temporarily
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicitly-unsigned-literal"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconstant-conversion"



/*============================================================================*\
||                       Convert Fixed-point to Strings                       ||
\*============================================================================*/

#define DEFINETEST_FIXED_TO_STR(TYPE, NAME) \
void	print_test_##TYPE##tostr(char const* test_name, t_testflags flags, \
		char const* expecting, \
		t_##TYPE number) \
{ \
	char* q = String_Format(SF_S64 ".(" SF_S64 "/" SF_S64 ")", \
		(t_s64)(number._ / FIXED_DENOMINATOR), \
		(t_s64)(number._ % FIXED_DENOMINATOR), \
		(t_s64)(FIXED_DENOMINATOR)); \
	TEST_INIT(str) \
	TEST_PERFORM(	TYPE##tostr, number) \
	TEST_PRINT(str, TYPE##tostr, "number=%s", q) \
	TEST_FREE() \
	free(q); \
} \
void	test_##TYPE##tostr(void) \
{ \
/*	| TEST FUNCTION         | TEST NAME                  |TESTFLAG| EXPECTING                       | TEST ARGS								*/ \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "0.(0/256)", NAME##_From( 0,                       1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "1.(0/256)", NAME##_From(+1,                       1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "-1.(0/256)", NAME##_From(-1,                       1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "10.(0/256)", NAME##_From(+10,                      1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "-10.(0/256)", NAME##_From(-10,                      1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "42.(0/256)", NAME##_From(+42,                      1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "0.(0/256)", NAME##_From( 0,                       2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "0.(128/256)", NAME##_From(+1,                       2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                   "0.(-128/256)", NAME##_From(-1,                       2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "5.(0/256)", NAME##_From(+10,                      2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "-5.(0/256)", NAME##_From(-10,                      2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "21.(0/256)", NAME##_From(+42,                      2)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "0.(0/256)", NAME##_From( 0,                     128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "0.(2/256)", NAME##_From(+1,                     128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "0.(-2/256)", NAME##_From(-1,                     128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "0.(20/256)", NAME##_From(+10,                    128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "0.(-20/256)", NAME##_From(-10,                    128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "0.(84/256)", NAME##_From(+42,                    128)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "111.(0/256)", NAME##_From(+111,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                   "-111.(0/256)", NAME##_From(-111,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 8 min)     ",	FALSE,                   "-128.(0/256)", NAME##_From(-128,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 8 max)     ",	FALSE,                    "127.(0/256)", NAME##_From(+127,                     1)); \
	if (g_test.config.test_overflow) { \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 8 min)     ",	FALSE,                   "-129.(0/256)", NAME##_From(-129,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 8 max)     ",	FALSE,                    "128.(0/256)", NAME##_From(+128,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 8 maxdigit)",	FALSE,                 "-99999.(0/256)", NAME##_From(-99999,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 8 maxdigit)",	FALSE,                  "99999.(0/256)", NAME##_From(+99999,                   1)); \
	} \
	if (sizeof(t_##TYPE) * 8 >= 16) \
	{ \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "777.(0/256)", NAME##_From(+777,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                   "-666.(0/256)", NAME##_From(-666,                     1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                 "-10000.(0/256)", NAME##_From(-10000,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                  "10000.(0/256)", NAME##_From(+10000,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 16min)     ",	FALSE,                 "-32768.(0/256)", NAME##_From(-32768,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 16max)     ",	FALSE,                  "32767.(0/256)", NAME##_From(+32767,                   1)); \
	if (g_test.config.test_overflow) { \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 16min)     ",	FALSE,                 "-32769.(0/256)", NAME##_From(-32769,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 16max)     ",	FALSE,                  "32768.(0/256)", NAME##_From(+32768,                   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 16maxdigit)",	FALSE,               "-9999999.(0/256)", NAME##_From(-9999999,                 1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 16maxdigit)",	FALSE,                "9999999.(0/256)", NAME##_From(+9999999,                 1)); \
	} \
	if (sizeof(t_##TYPE) * 8 >= 32) \
	{ \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "-123456789.(0/256)", NAME##_From(-123456789,               1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,              "123456789.(0/256)", NAME##_From(+123456789,               1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "-987654321.(0/256)", NAME##_From(-987654321,               1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,              "987654321.(0/256)", NAME##_From(+987654321,               1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 32min)     ",	FALSE,            "-2147483648.(0/256)", NAME##_From(-2147483648,              1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 32max)     ",	FALSE,             "2147483647.(0/256)", NAME##_From(+2147483647,              1)); \
	if (g_test.config.test_overflow) { \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 32min)     ",	FALSE,            "-2147483649.(0/256)", NAME##_From(-2147483649,              1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 32max)     ",	FALSE,             "2147483648.(0/256)", NAME##_From(+2147483648,              1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 32maxdigit)",	FALSE,          "-999999999999.(0/256)", NAME##_From(-999999999999,            1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 32maxdigit)",	FALSE,           "999999999999.(0/256)", NAME##_From(+999999999999,            1)); \
	} \
	if (sizeof(t_##TYPE) * 8 >= 64) \
	{ \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,            "-2147483649.(0/256)", NAME##_From(-2147483649,              1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "2147483648.(0/256)", NAME##_From(+2147483648,              1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,          "-999999999999.(0/256)", NAME##_From(-999999999999,            1)); \
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,           "999999999999.(0/256)", NAME##_From(+999999999999,            1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64min)     ",	FALSE,   "-9223372036854775808.(0/256)", NAME##_From(-9223372036854775808ll,   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64max)     ",	FALSE,    "9223372036854775807.(0/256)", NAME##_From(+9223372036854775807ll,   1)); \
	if (g_test.config.test_overflow) { \
	print_test_##TYPE##tostr(#TYPE"tostr (n < 64min)     ",	FALSE,   "-9223372036854775809.(0/256)", NAME##_From(-9223372036854775809ll,   1)); \
	print_test_##TYPE##tostr(#TYPE"tostr (n > 64max)     ",	FALSE,    "9223372036854775808.(0/256)", NAME##_From(+9223372036854775808ll,   1)); \
/*	print_test_##TYPE##tostr(#TYPE"tostr (n < 64maxdigit)",	FALSE, "-999999999999999999999.(0/256)", NAME##_From(-999999999999999999999ll, 1));*/\
/*	print_test_##TYPE##tostr(#TYPE"tostr (n > 64maxdigit)",	FALSE,  "999999999999999999999.(0/256)", NAME##_From(+999999999999999999999ll, 1));*/\
	} \
	}}} \
}

#ifndef c_q16tostr
void test_q16tostr(void)	{}
#warning "q16tostr() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_TO_STR(q16, Q16)
#endif

#ifndef c_q32tostr
void test_q32tostr(void)	{}
#warning "q32tostr() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_TO_STR(q32, Q32)
#endif

#ifndef c_q64tostr
void test_q64tostr(void)	{}
#warning "q64tostr() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_TO_STR(q64, Q64)
#endif

#if !defined(c_q128tostr) || !defined(__int128)
void test_q128tostr(void)	{}
#warning "q128tostr() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_TO_STR(q128, Q128)
#endif



/*============================================================================*\
||                       Convert Fixed-point to Strings                       ||
\*============================================================================*/

// TODO



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
// Resets the clang warning settings back to normal
#pragma clang diagnostic pop
#pragma clang diagnostic pop



int		testsuite_fixed(void)
{
	print_suite_title("libccc/fixed");

	print_nonstd();

//	test_qtostr();
//	test_q16tostr();
//	test_q32tostr();
//	test_q64tostr();
//	test_q128tostr();

	// TODO

	return (OK);
}
