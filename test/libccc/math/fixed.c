
#include "libccc/text/format.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include "test.h"

#if 0 // test template

#define DEFINETEST_FIXED_(BITS) \
void	print_test_q##BITS##(char const* test_name, t_testflags flags, \
		t_q##BITS	expecting, \
		t_q##BITS	a, \
		t_q##BITS	b) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM_LIBC(	q##BITS##, a, b) \
	TEST_PRINT(q##BITS,	q##BITS##, "a="SF_Q##BITS", b="SF_Q##BITS, a, b) \
} \
void	test_q##BITS##(void) \
{ \
/*	| TEST FUNCTION        | TEST NAME        |TESTFLAG| EXPECTING           | TEST ARGS */ \
	print_test_q##BITS##("q"#BITS"     ",	FALSE,               (0 + 0), 0, 0      ); \
}

#ifndef c_q16
void test_q16(void)	{}
#warning "q16() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_(16)
#endif

#ifndef c_q32
void test_q32(void)	{}
#warning "q32() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_(32)
#endif

#ifndef c_q64
void test_q64(void)	{}
#warning "q64() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_(64)
#endif

#if LIBCONFIG_USE_INT128
#ifndef c_q128
void test_q128(void)	{}
#warning "q128() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FIXED_(128)
#endif
#endif

#endif

// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_fixed(void)
{
	print_suite_title("libccc/math/fixed");

	print_nonstd();

//	test_add();
//	test_sub();
//	test_mul();
//	test_div();
//	test_mod();
//	test_pow();
//	test_sqrt();
//	test_abs();

	return (OK);
}
