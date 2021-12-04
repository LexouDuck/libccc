
#include "libccc/format.h"
#include "libccc/float.h"
#include "libccc/math/float.h"

#include "test.h"



#define DEFINETEST_FLOAT_(BITS) \
void	print_test_f##BITS##(char const* test_name, int can_segfault,		\
		t_f##BITS	expecting,												\
		t_f##BITS	a,														\
		t_f##BITS	b)														\
{																			\
	TEST_INIT(f##BITS)														\
	TEST_PERFORM_LIBC(	f##BITS##, a, b)									\
	TEST_PRINT(f##BITS,	f##BITS##, "a="SF_F##BITS", b="SF_F##BITS, a, b)	\
}																			\
void	test_f##BITS##(void)												\
{																			\
//	| TEST FUNCTION        | TEST NAME        |CAN SEGV| EXPECTING           | TEST ARGS //	\
	print_test_f##BITS##("u"#BITS"     ",	FALSE,               (0 + 0), 0, 0      );	\
}

#ifndef c_f32
void test_f32(void)	{}
#else
DEFINETEST_FLOAT_(32)
#endif

#ifndef c_f64
void test_f64(void)	{}
#else
DEFINETEST_FLOAT_(64)
#endif

#ifndef c_f80
void test_f80(void)	{}
#else
DEFINETEST_FLOAT_(80)
#endif

#if LIBCONFIG_USE_INT128
#ifndef c_f128
void test_f128(void)	{}
#else
DEFINETEST_FLOAT_(128)
#endif
#endif



// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_float(void)
{
	print_suite_title("libccc/math/float");

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
