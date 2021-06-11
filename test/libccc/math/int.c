
_#include "libccc/int.h"
#include "libccc/math/int.h"

#include "test.h"



#define DEFINETEST_UINT_(BITS) \
void	print_test_u##BITS##(char const* test_name, int can_segfault,		\
		t_u##BITS	a,														\
		t_u##BITS	b)														\
{																			\
	TEST_INIT(u##BITS)														\
	TEST_PERFORM_LIBC(	u##BITS##, a, b)									\
	TEST_PRINT(u##BITS,	u##BITS##, "a="SF_U##BITS", b="SF_U##BITS, a, b)	\
}																			\
void	test_u##BITS##(void)												\
{																			\
//	| TEST FUNCTION        | TEST NAME        |CAN SEGV| EXPECTING           | TEST ARGS //	\
	print_test_u##BITS##("u"#BITS"     ",	FALSE,               (0 + 0), 0, 0      );	\
}

#ifndef c_u8
void test_u8(void)	{}
#else
DEFINETEST_UINT_(8)
#endif

#ifndef c_u16
void test_u16(void)	{}
#else
DEFINETEST_UINT_(16)
#endif

#ifndef c_u32
void test_u32(void)	{}
#else
DEFINETEST_UINT_(32)
#endif

#ifndef c_u64
void test_u64(void)	{}
#else
DEFINETEST_UINT_(64)
#endif

#ifdef __int128
#ifndef c_u128
void test_u128(void)	{}
#else
DEFINETEST_UINT_(128)
#endif
#endif




#define DEFINETEST_UINT_ADD(BITS) \
void	print_test_u##BITS##add(char const* test_name, int can_segfault,	\
		t_u##BITS	a,														\
		t_u##BITS	b)														\
{																			\
	TEST_INIT(u##BITS)														\
	TEST_PERFORM_LIBC(	u##BITS##, a, b)									\
	TEST_PRINT(u##BITS,	u##BITS##, "a="SF_U##BITS", b="SF_U##BITS, a, b)	\
}																			\
void	test_u##BITS##add(void)												\
{																			\
/*	| TEST FUNCTION        | TEST NAME        |CAN SEGV| EXPECTING           | TEST ARGS */	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (0 + 0), 0, 0      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (1 + 0), 1, 0      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (0 + 1), 0, 1      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (1 + 1), 1, 1      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (1 + 1), 1, 1      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (2 + 1), 2, 1      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (1 + 2), 1, 2      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (2 + 2), 2, 2      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (3 + 5), 3, 5      );	\
	print_test_u##BITS##add("u"#BITS"add     ",	FALSE,               (3 + 5), 3, 5      );	\
}

#ifndef c_u8
void test_u8(void)	{}
#else
DEFINETEST_UINT_ADD(8)
#endif

#ifndef c_u16
void test_u16(void)	{}
#else
DEFINETEST_UINT_ADD(16)
#endif

#ifndef c_u32
void test_u32(void)	{}
#else
DEFINETEST_UINT_ADD(32)
#endif

#ifndef c_u64
void test_u64(void)	{}
#else
DEFINETEST_UINT_ADD(64)
#endif

#ifdef __int128
#ifndef c_u128
void test_u128(void)	{}
#else
DEFINETEST_UINT_ADD(128)
#endif
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_int(void)
{
	print_suite_title("libccc/math/int");

	print_nonstd();

	// TODO

	return (OK);
}
