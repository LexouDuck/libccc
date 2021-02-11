
#include "libccc/fixed.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Woverflow"
// "-Wimplicitly-unsigned-literal"
// "-Wconstant-conversion"



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



#define DEFINETEST_FIXED_TO_STR(TYPE) \
void	print_test_##TYPE##_to_str(char const* test_name, int can_segfault,			\
		char const* expecting,														\
		t_##TYPE number)															\
{																					\
	char* tmp = String_Format("%+li.(%lu/%lu)",										\
		(t_s64)Fixed_IntegerPart(number),											\
		(t_u64)Fixed_FractionPart(number),											\
		(t_u64)1 << LIBCONFIG_BITS_FIXED_FRACTIONPART);								\
	TEST_PERFORM_RESULT(TYPE##_to_str, number)										\
	print_test_str(test_name, "_"#TYPE"_to_str", result_libccc, tmp, can_segfault);	\
	print_timer_result(&t, FALSE);													\
	TEST_PRINT_ARGS(tmp)															\
	String_Delete(&tmp);															\
}																					\
void	test_##TYPE##_to_str(void)																										\
{																																		\
/*	| TEST FUNCTION      | TEST NAME                         |CAN SEGV| EXPECTING              | TEST ARGS							*/	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "+1", Fixed(+1,                       0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "-1", Fixed(-1,                       0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "+10", Fixed(+10,                      0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "-10", Fixed(-10,                      0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "0", Fixed( 0,                       0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "+42", Fixed(+42,                      0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "+111", Fixed(+111,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-111", Fixed(-111,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8 min)     ",	FALSE,                   "-128", Fixed(-128,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8 max)     ",	FALSE,                   "+127", Fixed(+127,                     0));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8 min)     ",	FALSE,                   "-129", Fixed(-129,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8 max)     ",	FALSE,                   "+128", Fixed(+128,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8 maxdigit)",	FALSE,                 "-99999", Fixed(-99999,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8 maxdigit)",	FALSE,                 "+99999", Fixed(+99999,                   0));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 16)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "+777", Fixed(+777,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-666", Fixed(-666,                     0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                 "-10000", Fixed(-10000,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                 "+10000", Fixed(+10000,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16min)     ",	FALSE,                 "-32768", Fixed(-32768,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16max)     ",	FALSE,                 "+32767", Fixed(+32767,                   0));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16min)     ",	FALSE,                 "-32769", Fixed(-32769,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16max)     ",	FALSE,                 "+32768", Fixed(+32768,                   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16maxdigit)",	FALSE,               "-9999999", Fixed(-9999999,                 0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16maxdigit)",	FALSE,               "+9999999", Fixed(+9999999,                 0));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 32)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-123456789", Fixed(-123456789,               0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "+123456789", Fixed(+123456789,               0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-987654321", Fixed(-987654321,               0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "+987654321", Fixed(+987654321,               0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32min)     ",	FALSE,            "-2147483648", Fixed(-2147483648,              0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32max)     ",	FALSE,            "+2147483647", Fixed(+2147483647,              0));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32min)     ",	FALSE,            "-2147483649", Fixed(-2147483649,              0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32max)     ",	FALSE,            "+2147483648", Fixed(+2147483648,              0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32maxdigit)",	FALSE,          "-999999999999", Fixed(-999999999999,            0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32maxdigit)",	FALSE,          "+999999999999", Fixed(+999999999999,            0));	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 64)																										\
	{																																	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,            "-2147483649", Fixed(-2147483649,              0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,            "+2147483648", Fixed(+2147483648,              0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,          "-999999999999", Fixed(-999999999999,            0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,          "+999999999999", Fixed(+999999999999,            0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64min)     ",	FALSE,   "-9223372036854775808", Fixed(-9223372036854775808LL,   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64max)     ",	FALSE,   "+9223372036854775807", Fixed(+9223372036854775807LL,   0));	\
	if (g_test.flags.test_overflow) {																									\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64min)     ",	FALSE,   "-9223372036854775809", Fixed(-9223372036854775809LL,   0));	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64max)     ",	FALSE,   "+9223372036854775808", Fixed(+9223372036854775808LL,   0));	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64maxdigit)",	FALSE, "-999999999999999999999", Fixed(-999999999999999999999LL, 0));*/	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64maxdigit)",	FALSE, "+999999999999999999999", Fixed(+999999999999999999999LL, 0));*/	\
	}																																	\
	}}}																																	\
}

#ifndef c_q16_to_str
void test_q16_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q16)
#endif

#ifndef c_q32_to_str
void test_q32_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q32)
#endif

#ifndef c_q64_to_str
void test_q64_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q64)
#endif

#if !defined(c_q128_to_str) || !defined(__int128)
void test_q128_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(q128)
#endif

#ifndef c_fixed_to_str
void test_fixed_to_str(void)	{}
#else
DEFINETEST_FIXED_TO_STR(fixed)
#endif



/*
** ************************************************************************** *|
**                       Convert Fixed-point to Strings                       *|
** ************************************************************************** *|
*/

// TODO



#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_fixed(void)
{
	print_suite_title("fixed");

	print_nonstd();

	test_q16_to_str();
	test_q32_to_str();
	test_q64_to_str();
	test_q128_to_str();
	test_fixed_to_str();

	// TODO

	return (OK);
}
