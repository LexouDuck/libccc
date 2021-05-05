
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
void	print_test_##TYPE##_to_str(char const* test_name, int can_segfault,			\
		char const* expecting,														\
		t_##TYPE number)															\
{																					\
	char* tmp = String_Format(FORMAT_S64".("FORMAT_U64"/"FORMAT_U64")",				\
		(t_s64)(number >> FIXED_BITS_FRACTIONPART),									\
		(t_u64)(number & (FIXED_MASK_FRACTIONPART)),								\
		(t_u64)1 << FIXED_BITS_FRACTIONPART);										\
	TEST_PERFORM(char*, TYPE##_to_str, number)										\
	print_test_str(test_name, "_"#TYPE"_to_str", result_libccc, tmp, can_segfault);	\
	print_timer_result(&t, FALSE);													\
	TEST_PRINT_ARGS("%s", tmp)														\
	free(tmp);																		\
}																					\
void	test_##TYPE##_to_str(void)																										\
{																																		\
/*	| TEST FUNCTION      | TEST NAME                         |CAN SEGV| EXPECTING              | TEST ARGS							*/	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "+1",  NEW(+1,                       0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "-1",  NEW(-1,                       0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "+10",  NEW(+10,                      0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "-10",  NEW(-10,                      0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "0",  NEW( 0,                       0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "+42",  NEW(+42,                      0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "+111",  NEW(+111,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-111",  NEW(-111,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8 min)     ",	FALSE,                   "-128",  NEW(-128,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8 max)     ",	FALSE,                   "+127",  NEW(+127,                     0, 1));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8 min)     ",	FALSE,                   "-129",  NEW(-129,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8 max)     ",	FALSE,                   "+128",  NEW(+128,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8 maxdigit)",	FALSE,                 "-99999",  NEW(-99999,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8 maxdigit)",	FALSE,                 "+99999",  NEW(+99999,                   0, 1));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 16)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "+777",  NEW(+777,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-666",  NEW(-666,                     0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                 "-10000",  NEW(-10000,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                 "+10000",  NEW(+10000,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16min)     ",	FALSE,                 "-32768",  NEW(-32768,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16max)     ",	FALSE,                 "+32767",  NEW(+32767,                   0, 1));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16min)     ",	FALSE,                 "-32769",  NEW(-32769,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16max)     ",	FALSE,                 "+32768",  NEW(+32768,                   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16maxdigit)",	FALSE,               "-9999999",  NEW(-9999999,                 0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16maxdigit)",	FALSE,               "+9999999",  NEW(+9999999,                 0, 1));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 32)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-123456789",  NEW(-123456789,               0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "+123456789",  NEW(+123456789,               0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-987654321",  NEW(-987654321,               0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "+987654321",  NEW(+987654321,               0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32min)     ",	FALSE,            "-2147483648",  NEW(-2147483648,              0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32max)     ",	FALSE,            "+2147483647",  NEW(+2147483647,              0, 1));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32min)     ",	FALSE,            "-2147483649",  NEW(-2147483649,              0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32max)     ",	FALSE,            "+2147483648",  NEW(+2147483648,              0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32maxdigit)",	FALSE,          "-999999999999",  NEW(-999999999999,            0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32maxdigit)",	FALSE,          "+999999999999",  NEW(+999999999999,            0, 1));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 64)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,            "-2147483649",  NEW(-2147483649,              0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,            "+2147483648",  NEW(+2147483648,              0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,          "-999999999999",  NEW(-999999999999,            0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,          "+999999999999",  NEW(+999999999999,            0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64min)     ",	FALSE,   "-9223372036854775808",  NEW(-9223372036854775808LL,   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64max)     ",	FALSE,   "+9223372036854775807",  NEW(+9223372036854775807LL,   0, 1));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64min)     ",	FALSE,   "-9223372036854775809",  NEW(-9223372036854775809LL,   0, 1));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64max)     ",	FALSE,   "+9223372036854775808",  NEW(+9223372036854775808LL,   0, 1));	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64maxdigit)",	FALSE, "-999999999999999999999",  NEW(-999999999999999999999LL, 0, 1));*/	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64maxdigit)",	FALSE, "+999999999999999999999",  NEW(+999999999999999999999LL, 0, 1));*/	\
	}																																	\
	}}}																																	\
}

#ifndef c_q16_to_str
void test_q16_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q16, Q16)
#endif

#ifndef c_q32_to_str
void test_q32_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q32, Q32)
#endif

#ifndef c_q64_to_str
void test_q64_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q64, Q64)
#endif

#if !defined(c_q128_to_str) || !defined(__int128)
void test_q128_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q128, Q128)
#endif

#ifndef c_fixed_to_str
void test_fixed_to_str(void)	{}
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

	test_q16_to_str();
	test_q32_to_str();
	test_q64_to_str();
	test_q128_to_str();
	test_fixed_to_str();

	// TODO

	return (OK);
}
