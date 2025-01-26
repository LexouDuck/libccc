
#include "libccc/text/format.h"
#include "libccc/int.h"
#include "libccc/math/int.h"

#include "test.h"
#include "test_utils.h"



// Disable certain GCC warnings temporarily
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
// Disable certain clang warnings temporarily
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverflow"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdivision-by-zero"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconstant-conversion"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winteger-overflow"



#if 0 // test template

#define DEFINETEST_UINT_(BITS) \
void	print_test_u##BITS##(char const* test_name, t_testflags flags, \
		t_u##BITS	x, \
		t_u##BITS	y) \
{ \
	TEST_INIT(u##BITS) \
	TEST_PERFORM_LIBC(	u##BITS##, x, y) \
	TEST_PRINT(u##BITS,	u##BITS##, "x=" SF_U##BITS ", y=" SF_U##BITS, x, y) \
} \
void	test_u##BITS##(void) \
{ \
/*	| TEST FUNCTION        | TEST NAME        |TESTFLAG| EXPECTING           | TEST ARGS */ \
/*	print_test_u##BITS##("u"#BITS"     ",	FALSE,               (0 + 0), 0, 0      );	*/ \
}

#ifndef c_u8
void test_u8(void)	{}
#warning "u8() test suite function defined, but the function isn't defined."
#else
DEFINETEST_UINT_(8)
#endif

#ifndef c_u16
void test_u16(void)	{}
#warning "u16() test suite function defined, but the function isn't defined."
#else
DEFINETEST_UINT_(16)
#endif

#ifndef c_u32
void test_u32(void)	{}
#warning "u32() test suite function defined, but the function isn't defined."
#else
DEFINETEST_UINT_(32)
#endif

#ifndef c_u64
void test_u64(void)	{}
#warning "u64() test suite function defined, but the function isn't defined."
#else
DEFINETEST_UINT_(64)
#endif

#ifndef c_u128
void test_u128(void)	{}
#warning "u128() test suite function defined, but the function isn't defined."
#else
DEFINETEST_UINT_(128)
#endif

#endif



#undef  TEST
#define TEST(BITS, LHS, OPERATOR, RHS) \
	EXCEPTION(BITS, LHS, OPERATOR, RHS) ((LHS) OPERATOR (RHS)), (LHS), (RHS)

#undef  EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	



#define DEFINETEST_UINT_OPERATOR(OP, FUNCNAME, BITS) \
void	print_test_u##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_u##BITS	expecting, \
		t_u##BITS	x, \
		t_u##BITS	y) \
{ \
	TEST_INIT(u##BITS) \
	TEST_PERFORM(		u##BITS##FUNCNAME, x, y) \
	TEST_PRINT(u##BITS,	u##BITS##FUNCNAME, "x=" SF_U##BITS ", y=" SF_U##BITS, x, y)\
} \
void	test_u##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME                      |TESTFLAG| TEST */ \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP, 0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,+1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,+2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP, 0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,+1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,+2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP, 0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,+1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,+2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,+1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,+2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=max;y=0)  ",	FALSE, TEST(BITS, U##BITS##_MAX, OP,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=max;y=1)  ",	FALSE, TEST(BITS, U##BITS##_MAX, OP, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=max;y=2)  ",	FALSE, TEST(BITS, U##BITS##_MAX, OP, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=0;y=max)  ",	FALSE, TEST(BITS,  0, OP, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=1;y=max)  ",	FALSE, TEST(BITS, +1, OP, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=2;y=max)  ",	FALSE, TEST(BITS, +2, OP, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" (x=max;y=max)",	FALSE, TEST(BITS, U##BITS##_MAX, OP, U##BITS##_MAX) ); \
}

DEFINETEST_UINT_OPERATOR(+, add, 8)
DEFINETEST_UINT_OPERATOR(+, add, 16)
DEFINETEST_UINT_OPERATOR(+, add, 32)
DEFINETEST_UINT_OPERATOR(+, add, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(+, add, 128)
#endif

DEFINETEST_UINT_OPERATOR(-, sub, 8)
DEFINETEST_UINT_OPERATOR(-, sub, 16)
DEFINETEST_UINT_OPERATOR(-, sub, 32)
DEFINETEST_UINT_OPERATOR(-, sub, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(-, sub, 128)
#endif

DEFINETEST_UINT_OPERATOR(*, mul, 8)
DEFINETEST_UINT_OPERATOR(*, mul, 16)
DEFINETEST_UINT_OPERATOR(*, mul, 32)
DEFINETEST_UINT_OPERATOR(*, mul, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(*, mul, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0) ? (LIBCONFIG_UINT_INF ? U##BITS##_MAX : U##BITS##_ERROR) :
DEFINETEST_UINT_OPERATOR(/, div, 8)
DEFINETEST_UINT_OPERATOR(/, div, 16)
DEFINETEST_UINT_OPERATOR(/, div, 32)
DEFINETEST_UINT_OPERATOR(/, div, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(/, div, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0) ? (LIBCONFIG_UINT_INF ? U##BITS##_MAX : U##BITS##_ERROR) :
DEFINETEST_UINT_OPERATOR(%, mod, 8)
DEFINETEST_UINT_OPERATOR(%, mod, 16)
DEFINETEST_UINT_OPERATOR(%, mod, 32)
DEFINETEST_UINT_OPERATOR(%, mod, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(%, mod, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0) ? (LIBCONFIG_UINT_INF ? U##BITS##_MAX : U##BITS##_ERROR) :
DEFINETEST_UINT_OPERATOR(%, rem, 8)
DEFINETEST_UINT_OPERATOR(%, rem, 16)
DEFINETEST_UINT_OPERATOR(%, rem, 32)
DEFINETEST_UINT_OPERATOR(%, rem, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(%, rem, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	



#undef  TEST
#define TEST(BITS, LHS, OPERATOR, RHS) \
	EXCEPTION(BITS, LHS, OPERATOR, RHS) ((LHS) OPERATOR (RHS)), (LHS), (RHS)

#undef  EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	



#define DEFINETEST_SINT_OPERATOR(OP, FUNCNAME, BITS) \
void	print_test_s##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_s##BITS	expecting, \
		t_s##BITS	x, \
		t_s##BITS	y) \
{ \
	TEST_INIT(s##BITS) \
	TEST_PERFORM(		s##BITS##FUNCNAME, x, y) \
	TEST_PRINT(s##BITS,	s##BITS##FUNCNAME, "x=" SF_S##BITS ", y=" SF_S##BITS, x, y)\
} \
void	test_s##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME                      |TESTFLAG| TEST */ \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP, 0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP, 0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1,OP,10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP, 0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2,OP,10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP, 0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1,OP,10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP, 0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2,OP,10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,+2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,-2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10,OP,10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=min;y= 0) ",	FALSE, TEST(BITS, S##BITS##_MIN, OP,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=min;y=-1) ",	FALSE, TEST(BITS, S##BITS##_MIN, OP, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=min;y=-2) ",	FALSE, TEST(BITS, S##BITS##_MIN, OP, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=max;y= 0) ",	FALSE, TEST(BITS, S##BITS##_MAX, OP,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=max;y=+1) ",	FALSE, TEST(BITS, S##BITS##_MAX, OP, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=max;y=+2) ",	FALSE, TEST(BITS, S##BITS##_MAX, OP, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x= 0;y=min) ",	FALSE, TEST(BITS,  0, OP, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=-1;y=min) ",	FALSE, TEST(BITS, -1, OP, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=-2;y=min) ",	FALSE, TEST(BITS, -2, OP, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x= 0;y=max) ",	FALSE, TEST(BITS,  0, OP, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=+1;y=max) ",	FALSE, TEST(BITS, +1, OP, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=+2;y=max) ",	FALSE, TEST(BITS, +2, OP, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=min;y=min)",	FALSE, TEST(BITS, S##BITS##_MIN, OP, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=min;y=max)",	FALSE, TEST(BITS, S##BITS##_MIN, OP, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" (x=max;y=max)",	FALSE, TEST(BITS, S##BITS##_MAX, OP, S##BITS##_MAX) ); \
}

DEFINETEST_SINT_OPERATOR(+, add, 8)
DEFINETEST_SINT_OPERATOR(+, add, 16)
DEFINETEST_SINT_OPERATOR(+, add, 32)
DEFINETEST_SINT_OPERATOR(+, add, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(+, add, 128)
#endif

DEFINETEST_SINT_OPERATOR(-, sub, 8)
DEFINETEST_SINT_OPERATOR(-, sub, 16)
DEFINETEST_SINT_OPERATOR(-, sub, 32)
DEFINETEST_SINT_OPERATOR(-, sub, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(-, sub, 128)
#endif

DEFINETEST_SINT_OPERATOR(*, mul, 8)
DEFINETEST_SINT_OPERATOR(*, mul, 16)
DEFINETEST_SINT_OPERATOR(*, mul, 32)
DEFINETEST_SINT_OPERATOR(*, mul, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(*, mul, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0) ? (LIBCONFIG_SINT_INF ? S##BITS##_MAX : S##BITS##_ERROR) :
DEFINETEST_SINT_OPERATOR(/, div, 8)
DEFINETEST_SINT_OPERATOR(/, div, 16)
DEFINETEST_SINT_OPERATOR(/, div, 32)
DEFINETEST_SINT_OPERATOR(/, div, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(/, div, 128)
#endif

DEFINETEST_SINT_OPERATOR(%, mod, 8)
DEFINETEST_SINT_OPERATOR(%, mod, 16)
DEFINETEST_SINT_OPERATOR(%, mod, 32)
DEFINETEST_SINT_OPERATOR(%, mod, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(%, mod, 128)
#endif

DEFINETEST_SINT_OPERATOR(%, rem, 8)
DEFINETEST_SINT_OPERATOR(%, rem, 16)
DEFINETEST_SINT_OPERATOR(%, rem, 32)
DEFINETEST_SINT_OPERATOR(%, rem, 64)
#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(%, rem, 128)
#endif



// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
// Resets the clang warning settings back to normal
#pragma clang diagnostic pop
#pragma clang diagnostic pop
#pragma clang diagnostic pop
#pragma clang diagnostic pop



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_int(void)
{
	print_suite_title("libccc/math/int");

	print_nonstd();

#if LIBCONFIG_USE_INT128
	#define RUNTESTSUITE(FUNCNAME) \
		test_u8##FUNCNAME(); \
		test_u16##FUNCNAME(); \
		test_u32##FUNCNAME(); \
		test_u64##FUNCNAME(); \
		test_u128##FUNCNAME(); \
		test_s8##FUNCNAME(); \
		test_s16##FUNCNAME(); \
		test_s32##FUNCNAME(); \
		test_s64##FUNCNAME(); \
		test_s128##FUNCNAME(); \

#else
		test_u8##FUNCNAME(); \
		test_u16##FUNCNAME(); \
		test_u32##FUNCNAME(); \
		test_u64##FUNCNAME(); \
		test_s8##FUNCNAME(); \
		test_s16##FUNCNAME(); \
		test_s32##FUNCNAME(); \
		test_s64##FUNCNAME(); \

#endif

//	RUNTESTSUITE(isnan)
//	RUNTESTSUITE(isinf)
//	RUNTESTSUITE(abs)
//	RUNTESTSUITE(sgn)
//	RUNTESTSUITE(min)
//	RUNTESTSUITE(max)
	RUNTESTSUITE(add)
	RUNTESTSUITE(sub)
	RUNTESTSUITE(mul)
	RUNTESTSUITE(div)
	RUNTESTSUITE(mod)
//	RUNTESTSUITE(rem)
//	RUNTESTSUITE(pow)
//	RUNTESTSUITE(root2)
//	RUNTESTSUITE(root3)
//	RUNTESTSUITE(rootn)
//	RUNTESTSUITE(lcm)
//	RUNTESTSUITE(gcd)

	return (OK);
}
