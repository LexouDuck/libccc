
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



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



/*
** ************************************************************************** *|
**                       Convert Fixed-point to Strings                       *|
** ************************************************************************** *|
*/

#ifndef c_fixed_
void test_fixed_(void)	{}
#else
void	print_test_fixed_(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_fixed_(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	// TODO
}
#endif



#define DEFINETEST_FIXED_TO_STR(TYPE, NEW) \
void	print_test_##TYPE##tostr(char const* test_name, int can_segfault,		\
		char const* expecting,													\
		t_##TYPE number)														\
{																				\
	char* q = String_Format(FORMAT_S64".("FORMAT_U64"/"FORMAT_U64")",			\
		(t_s64)(number >> FIXED_BITS_FRACTIONPART),								\
		(t_u64)(number & (FIXED_MASK_FRACTIONPART)),							\
		(t_u64)1 << FIXED_BITS_FRACTIONPART);									\
	TEST_INIT(str)																\
	TEST_PERFORM(	TYPE##tostr, number)										\
	TEST_PRINT(str, TYPE##tostr, "number=%s", q)								\
	TEST_FREE()																	\
	free(q);																	\
}																				\
void	test_##TYPE##tostr(void)																											\
{																																			\
/*	| TEST FUNCTION         | TEST NAME                  |CAN SEGV| EXPECTING                       | TEST ARGS							*/	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "1.(0/256)", NEW(+1,                       0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "-1.(0/256)", NEW(-1,                       0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "10.(0/256)", NEW(+10,                      0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "-10.(0/256)", NEW(-10,                      0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                      "0.(0/256)", NEW( 0,                       0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                     "42.(0/256)", NEW(+42,                      0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "111.(0/256)", NEW(+111,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                   "-111.(0/256)", NEW(-111,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 8 min)     ",	FALSE,                   "-128.(0/256)", NEW(-128,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 8 max)     ",	FALSE,                    "127.(0/256)", NEW(+127,                     0, 1));	\
	if (g_test.flags.test_overflow) {																										\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 8 min)     ",	FALSE,                   "-129.(0/256)", NEW(-129,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 8 max)     ",	FALSE,                    "128.(0/256)", NEW(+128,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 8 maxdigit)",	FALSE,                 "-99999.(0/256)", NEW(-99999,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 8 maxdigit)",	FALSE,                  "99999.(0/256)", NEW(+99999,                   0, 1));	\
	}																																		\
	if (sizeof(t_##TYPE) * 8 >= 16)																											\
	{																																		\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                    "777.(0/256)", NEW(+777,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                   "-666.(0/256)", NEW(-666,                     0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                 "-10000.(0/256)", NEW(-10000,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,                  "10000.(0/256)", NEW(+10000,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 16min)     ",	FALSE,                 "-32768.(0/256)", NEW(-32768,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 16max)     ",	FALSE,                  "32767.(0/256)", NEW(+32767,                   0, 1));	\
	if (g_test.flags.test_overflow) {																										\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 16min)     ",	FALSE,                 "-32769.(0/256)", NEW(-32769,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 16max)     ",	FALSE,                  "32768.(0/256)", NEW(+32768,                   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 16maxdigit)",	FALSE,               "-9999999.(0/256)", NEW(-9999999,                 0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 16maxdigit)",	FALSE,                "9999999.(0/256)", NEW(+9999999,                 0, 1));	\
	}																																		\
	if (sizeof(t_##TYPE) * 8 >= 32)																											\
	{																																		\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "-123456789.(0/256)", NEW(-123456789,               0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,              "123456789.(0/256)", NEW(+123456789,               0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "-987654321.(0/256)", NEW(-987654321,               0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,              "987654321.(0/256)", NEW(+987654321,               0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 32min)     ",	FALSE,            "-2147483648.(0/256)", NEW(-2147483648,              0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 32max)     ",	FALSE,             "2147483647.(0/256)", NEW(+2147483647,              0, 1));	\
	if (g_test.flags.test_overflow) {																										\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 32min)     ",	FALSE,            "-2147483649.(0/256)", NEW(-2147483649,              0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 32max)     ",	FALSE,             "2147483648.(0/256)", NEW(+2147483648,              0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 32maxdigit)",	FALSE,          "-999999999999.(0/256)", NEW(-999999999999,            0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 32maxdigit)",	FALSE,           "999999999999.(0/256)", NEW(+999999999999,            0, 1));	\
	}																																		\
	if (sizeof(t_##TYPE) * 8 >= 64)																											\
	{																																		\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,            "-2147483649.(0/256)", NEW(-2147483649,              0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,             "2147483648.(0/256)", NEW(+2147483648,              0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,          "-999999999999.(0/256)", NEW(-999999999999,            0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr                 ",	FALSE,           "999999999999.(0/256)", NEW(+999999999999,            0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64min)     ",	FALSE,   "-9223372036854775808.(0/256)", NEW(-9223372036854775808ll,   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64max)     ",	FALSE,    "9223372036854775807.(0/256)", NEW(+9223372036854775807ll,   0, 1));	\
	if (g_test.flags.test_overflow) {																										\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 64min)     ",	FALSE,   "-9223372036854775809.(0/256)", NEW(-9223372036854775809ll,   0, 1));	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 64max)     ",	FALSE,    "9223372036854775808.(0/256)", NEW(+9223372036854775808ll,   0, 1));	\
/*	print_test_##TYPE##tostr(#TYPE"tostr (n < 64maxdigit)",	FALSE, "-999999999999999999999.(0/256)", NEW(-999999999999999999999ll, 0, 1));*/\
/*	print_test_##TYPE##tostr(#TYPE"tostr (n > 64maxdigit)",	FALSE,  "999999999999999999999.(0/256)", NEW(+999999999999999999999ll, 0, 1));*/\
	}																																		\
	}}}																																		\
}

#ifndef c_q16tostr
void test_q16tostr(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q16, Q16)
#endif

#ifndef c_q32tostr
void test_q32tostr(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q32, Q32)
#endif

#ifndef c_q64tostr
void test_q64tostr(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q64, Q64)
#endif

#if !defined(c_q128tostr) || !defined(__int128)
void test_q128tostr(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q128, Q128)
#endif

#ifndef c_fixedtostr
void test_fixedtostr(void)	{}
#else
DEFINETEST_FIXED_TO_STR(fixed, Fixed)
#endif



/*
** ************************************************************************** *|
**                       Convert Fixed-point to Strings                       *|
** ************************************************************************** *|
*/

// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

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

	test_q16tostr();
	test_q32tostr();
	test_q64tostr();
	test_q128tostr();
	test_fixedtostr();

	// TODO

	return (OK);
}
