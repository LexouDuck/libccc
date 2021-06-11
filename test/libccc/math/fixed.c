
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include "test.h"



#define DEFINETEST_FIXED_(BITS) \
void	print_test_q##BITS##(char const* test_name, int can_segfault,		\
		t_q##BITS	a,														\
		t_q##BITS	b)														\
{																			\
	TEST_INIT(q##BITS)														\
	TEST_PERFORM_LIBC(	q##BITS##, a, b)									\
	TEST_PRINT(q##BITS,	q##BITS##, "a="SF_Q##BITS", b="SF_Q##BITS, a, b)	\
}																			\
void	test_q##BITS##(void)												\
{																			\
/*	| TEST FUNCTION        | TEST NAME        |CAN SEGV| EXPECTING           | TEST ARGS */	\
	print_test_q##BITS##("q"#BITS"     ",	FALSE,               (0 + 0), 0, 0      );	\
}

#ifndef c_q16
void test_q16(void)	{}
#else
DEFINETEST_FIXED_(16)
#endif

#ifndef c_q32
void test_q32(void)	{}
#else
DEFINETEST_FIXED_(32)
#endif

#ifndef c_q64
void test_q64(void)	{}
#else
DEFINETEST_FIXED_(64)
#endif

#ifdef __int128
#ifndef c_q128
void test_q128(void)	{}
#else
DEFINETEST_FIXED_(128)
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

	// TODO

	return (OK);
}
