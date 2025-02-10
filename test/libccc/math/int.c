
#include <math.h>

#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



// Disable certain GCC warnings temporarily
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
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



#define SUBVAL	(__typeof__(x))(((__typeof__(x))1 << (sizeof(x)*8 - 1)) - 1)
#define MIDVAL	(__typeof__(x))( (__typeof__(x))1 << (sizeof(x)*8 - 1))
#define ENDVAL	(__typeof__(x))(~(__typeof__(x))0)
#define ABS(X)	(__typeof__(X))((X) < 0 ? -(X) : +(X))
#define SGN(X)	(__typeof__(X))((X) < 0 ? -1 : +1)



#if LIBCONFIG_USE_INT128

	#define DEFINEFUNC_UINT_CHECK(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##u8	(t_u8    x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u16	(t_u16   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u32	(t_u32   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u64	(t_u64   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u128	(t_u128  x)	{ FUNCBODY } \
	t_bool	FUNCNAME##uint	(t_uint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_RELATION(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##u8	(t_u8    x, t_u8    y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u16	(t_u16   x, t_u16   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u32	(t_u32   x, t_u32   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u64	(t_u64   x, t_u64   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u128	(t_u128  x, t_u128  y)	{ FUNCBODY } \
	t_bool	FUNCNAME##uint	(t_uint  x, t_uint  y)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_FUNCTION(FUNCNAME, FUNCBODY) \
	t_u8	FUNCNAME##u8	(t_u8    x)	{ FUNCBODY } \
	t_u16	FUNCNAME##u16	(t_u16   x)	{ FUNCBODY } \
	t_u32	FUNCNAME##u32	(t_u32   x)	{ FUNCBODY } \
	t_u64	FUNCNAME##u64	(t_u64   x)	{ FUNCBODY } \
	t_u128	FUNCNAME##u128	(t_u128  x)	{ FUNCBODY } \
	t_uint	FUNCNAME##uint	(t_uint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_OPERATOR(FUNCNAME, FUNCBODY) \
	t_u8	FUNCNAME##u8	(t_u8    x, t_u8    y)	{ FUNCBODY } \
	t_u16	FUNCNAME##u16	(t_u16   x, t_u16   y)	{ FUNCBODY } \
	t_u32	FUNCNAME##u32	(t_u32   x, t_u32   y)	{ FUNCBODY } \
	t_u64	FUNCNAME##u64	(t_u64   x, t_u64   y)	{ FUNCBODY } \
	t_u128	FUNCNAME##u128	(t_u128  x, t_u128  y)	{ FUNCBODY } \
	t_uint	FUNCNAME##uint	(t_uint  x, t_uint  y)	{ FUNCBODY } \

#else

	#define DEFINEFUNC_UINT_CHECK(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##u8	(t_u8    x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u16	(t_u16   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u32	(t_u32   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##u64	(t_u64   x)	{ FUNCBODY } \
	t_bool	FUNCNAME##uint	(t_uint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_RELATION(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##u8	(t_u8    x, t_u8    y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u16	(t_u16   x, t_u16   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u32	(t_u32   x, t_u32   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##u64	(t_u64   x, t_u64   y)	{ FUNCBODY } \
	t_bool	FUNCNAME##uint	(t_uint  x, t_uint  y)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_FUNCTION(FUNCNAME, FUNCBODY) \
	t_u8	FUNCNAME##u8	(t_u8    x)	{ FUNCBODY } \
	t_u16	FUNCNAME##u16	(t_u16   x)	{ FUNCBODY } \
	t_u32	FUNCNAME##u32	(t_u32   x)	{ FUNCBODY } \
	t_u64	FUNCNAME##u64	(t_u64   x)	{ FUNCBODY } \
	t_uint	FUNCNAME##uint	(t_uint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_UINT_OPERATOR(FUNCNAME, FUNCBODY) \
	t_u8	FUNCNAME##u8	(t_u8    x, t_u8    y)	{ FUNCBODY } \
	t_u16	FUNCNAME##u16	(t_u16   x, t_u16   y)	{ FUNCBODY } \
	t_u32	FUNCNAME##u32	(t_u32   x, t_u32   y)	{ FUNCBODY } \
	t_u64	FUNCNAME##u64	(t_u64   x, t_u64   y)	{ FUNCBODY } \
	t_uint	FUNCNAME##uint	(t_uint  x, t_uint  y)	{ FUNCBODY } \

#endif

// DEFINEFUNC_UINT_CHECK(isnan, return (!LIBCONFIG_UINT_NAN ? 0 : (x == ENDVAL));)
// DEFINEFUNC_UINT_CHECK(isinf, return (!LIBCONFIG_UINT_INF ? 0 : (LIBCONFIG_UINT_NAN ? (x == ENDVAL - 1) : (x == ENDVAL)));)
DEFINEFUNC_UINT_FUNCTION(abs,   return (x);)
DEFINEFUNC_UINT_FUNCTION(sgn,   return (x == 0 ? 0 : +1);)
DEFINEFUNC_UINT_OPERATOR(min,   return (x < y ? x : y);)
DEFINEFUNC_UINT_OPERATOR(max,   return (x > y ? x : y);)
DEFINEFUNC_UINT_OPERATOR(add,   return (x + y);)
DEFINEFUNC_UINT_OPERATOR(sub,   return (x - y);)
DEFINEFUNC_UINT_OPERATOR(mul,   return (x * y);)
DEFINEFUNC_UINT_OPERATOR(div,   if (y == 0)	return (LIBCONFIG_UINT_INF ? ENDVAL : (LIBCONFIG_UINT_NAN ? ENDVAL : 0));	return (x / y);)
DEFINEFUNC_UINT_OPERATOR(mod,   if (y == 0)	return (LIBCONFIG_UINT_INF ? +x     : (LIBCONFIG_UINT_NAN ? ENDVAL : 0));	return (x % y);)
DEFINEFUNC_UINT_OPERATOR(rem,   if (y == 0)	return (LIBCONFIG_UINT_INF ? +x     : (LIBCONFIG_UINT_NAN ? ENDVAL : 0));	return (x % y);)
DEFINEFUNC_UINT_OPERATOR(pow,   __typeof__(x) result = 1;	while (TRUE)	{	if (y & 1)	result *= x;	y >>= 1;	if (y == 0)	break;	x *= x;	}	return result;)	// t_float result = pow((t_float)x, y);	return isnan(result) ? 0 : result;)
DEFINEFUNC_UINT_FUNCTION(root2, t_float result = sqrt((t_float)x);	return isnan(result) ? 0 : result;)
DEFINEFUNC_UINT_FUNCTION(root3, t_float result = cbrt((t_float)x);	return isnan(result) ? 0 : result;)
DEFINEFUNC_UINT_OPERATOR(rootn, t_float result = pow((t_float)x, 1/y);	return isnan(result) ? 0 : result;)
DEFINEFUNC_UINT_OPERATOR(gcd,   if (x && y)	while ((x %= y) && (y %= x));	return (x | y);)
DEFINEFUNC_UINT_OPERATOR(lcm,   if (x && y)	while ((x %= y) && (y %= x));	return (x / ((x | y) == 0 ? 1 : (x | y)) * y);)



//


/*
DEFINETEST_UINT_FUNCTION(8, isnan)
DEFINETEST_UINT_FUNCTION(8, isinf)

DEFINETEST_UINT_FUNCTION(16, isnan)
DEFINETEST_UINT_FUNCTION(16, isinf)

DEFINETEST_UINT_FUNCTION(32, isnan)
DEFINETEST_UINT_FUNCTION(32, isinf)

DEFINETEST_UINT_FUNCTION(64, isnan)
DEFINETEST_UINT_FUNCTION(64, isinf)

#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_FUNCTION(128, isnan)
DEFINETEST_UINT_FUNCTION(128, isinf)
#endif
*/



#undef  TEST
#define TEST(BITS, FUNCTION, ARG) \
	FUNCTION##u##BITS((ARG)), (ARG)

#define DEFINETEST_UINT_FUNCTION(BITS, FUNCNAME) \
void	print_test_u##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_u##BITS	expecting, \
		t_u##BITS	x) \
{ \
	TEST_INIT(u##BITS) \
	TEST_PERFORM(		u##BITS##FUNCNAME, x) \
	TEST_PRINT(u##BITS,	u##BITS##FUNCNAME, "x=" SF_U##BITS, x)\
} \
void	test_u##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +3) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +5) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, U##BITS##_MAX - 1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, U##BITS##_ERROR) ); \
}

DEFINETEST_UINT_FUNCTION(8, abs)
DEFINETEST_UINT_FUNCTION(8, sgn)
DEFINETEST_UINT_FUNCTION(8, root2)
DEFINETEST_UINT_FUNCTION(8, root3)

DEFINETEST_UINT_FUNCTION(16, abs)
DEFINETEST_UINT_FUNCTION(16, sgn)
DEFINETEST_UINT_FUNCTION(16, root2)
DEFINETEST_UINT_FUNCTION(16, root3)

DEFINETEST_UINT_FUNCTION(32, abs)
DEFINETEST_UINT_FUNCTION(32, sgn)
DEFINETEST_UINT_FUNCTION(32, root2)
DEFINETEST_UINT_FUNCTION(32, root3)

DEFINETEST_UINT_FUNCTION(64, abs)
DEFINETEST_UINT_FUNCTION(64, sgn)
DEFINETEST_UINT_FUNCTION(64, root2)
DEFINETEST_UINT_FUNCTION(64, root3)

#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_FUNCTION(128, abs)
DEFINETEST_UINT_FUNCTION(128, sgn)
DEFINETEST_UINT_FUNCTION(128, root2)
DEFINETEST_UINT_FUNCTION(128, root3)
#endif



#undef  TEST
#define TEST(BITS, OPERATOR, LHS, RHS) \
	OPERATOR##u##BITS((LHS),(RHS)), (LHS), (RHS)

#define DEFINETEST_UINT_OPERATOR(BITS, FUNCNAME, MAYFPE) \
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
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME,  0,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME,  0, U##BITS##_ERROR) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +1,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +1, U##BITS##_ERROR) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +2,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +2, U##BITS##_ERROR) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, 10,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, 10, U##BITS##_ERROR) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, U##BITS##_MAX,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_MAX, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_MAX, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_MAX, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_MAX, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, U##BITS##_MAX, U##BITS##_ERROR) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, U##BITS##_ERROR,  0) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_ERROR, +1) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_ERROR, +2) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_ERROR, 10) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, U##BITS##_ERROR, U##BITS##_MAX) ); \
	print_test_u##BITS##FUNCNAME("u"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, U##BITS##_ERROR, U##BITS##_ERROR) ); \
}

DEFINETEST_UINT_OPERATOR(8, min, FALSE)
DEFINETEST_UINT_OPERATOR(8, max, FALSE)
DEFINETEST_UINT_OPERATOR(8, add, FALSE)
DEFINETEST_UINT_OPERATOR(8, sub, FALSE)
DEFINETEST_UINT_OPERATOR(8, mul, FALSE)
DEFINETEST_UINT_OPERATOR(8, div, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(8, mod, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(8, rem, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(8, pow, FALSE)
DEFINETEST_UINT_OPERATOR(8, rootn, FALSE)
DEFINETEST_UINT_OPERATOR(8, lcm, FALSE)
DEFINETEST_UINT_OPERATOR(8, gcd, FALSE)

DEFINETEST_UINT_OPERATOR(16, min, FALSE)
DEFINETEST_UINT_OPERATOR(16, max, FALSE)
DEFINETEST_UINT_OPERATOR(16, add, FALSE)
DEFINETEST_UINT_OPERATOR(16, sub, FALSE)
DEFINETEST_UINT_OPERATOR(16, mul, FALSE)
DEFINETEST_UINT_OPERATOR(16, div, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(16, mod, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(16, rem, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(16, pow, FALSE)
DEFINETEST_UINT_OPERATOR(16, rootn, FALSE)
DEFINETEST_UINT_OPERATOR(16, lcm, FALSE)
DEFINETEST_UINT_OPERATOR(16, gcd, FALSE)

DEFINETEST_UINT_OPERATOR(32, min, FALSE)
DEFINETEST_UINT_OPERATOR(32, max, FALSE)
DEFINETEST_UINT_OPERATOR(32, add, FALSE)
DEFINETEST_UINT_OPERATOR(32, sub, FALSE)
DEFINETEST_UINT_OPERATOR(32, mul, FALSE)
DEFINETEST_UINT_OPERATOR(32, div, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(32, mod, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(32, rem, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(32, pow, FALSE)
DEFINETEST_UINT_OPERATOR(32, rootn, FALSE)
DEFINETEST_UINT_OPERATOR(32, lcm, FALSE)
DEFINETEST_UINT_OPERATOR(32, gcd, FALSE)

DEFINETEST_UINT_OPERATOR(64, min, FALSE)
DEFINETEST_UINT_OPERATOR(64, max, FALSE)
DEFINETEST_UINT_OPERATOR(64, add, FALSE)
DEFINETEST_UINT_OPERATOR(64, sub, FALSE)
DEFINETEST_UINT_OPERATOR(64, mul, FALSE)
DEFINETEST_UINT_OPERATOR(64, div, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(64, mod, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(64, rem, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(64, pow, FALSE)
DEFINETEST_UINT_OPERATOR(64, rootn, FALSE)
DEFINETEST_UINT_OPERATOR(64, lcm, FALSE)
DEFINETEST_UINT_OPERATOR(64, gcd, FALSE)

#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_OPERATOR(128, min, FALSE)
DEFINETEST_UINT_OPERATOR(128, max, FALSE)
DEFINETEST_UINT_OPERATOR(128, add, FALSE)
DEFINETEST_UINT_OPERATOR(128, sub, FALSE)
DEFINETEST_UINT_OPERATOR(128, mul, FALSE)
DEFINETEST_UINT_OPERATOR(128, div, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(128, mod, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(128, rem, ALLOW_SIGFPE)
DEFINETEST_UINT_OPERATOR(128, pow, FALSE)
DEFINETEST_UINT_OPERATOR(128, rootn, FALSE)
DEFINETEST_UINT_OPERATOR(128, lcm, FALSE)
DEFINETEST_UINT_OPERATOR(128, gcd, FALSE)
#endif



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#if LIBCONFIG_USE_INT128

	#define DEFINEFUNC_SINT_FUNCTION(FUNCNAME, FUNCBODY) \
	t_s8	FUNCNAME##s8	(t_s8    x)	{ FUNCBODY } \
	t_s16	FUNCNAME##s16	(t_s16   x)	{ FUNCBODY } \
	t_s32	FUNCNAME##s32	(t_s32   x)	{ FUNCBODY } \
	t_s64	FUNCNAME##s64	(t_s64   x)	{ FUNCBODY } \
	t_s128	FUNCNAME##s128	(t_s128  x)	{ FUNCBODY } \
	t_sint	FUNCNAME##sint	(t_sint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_SINT_OPERATOR(FUNCNAME, FUNCBODY) \
	t_s8	FUNCNAME##s8	(t_s8    x, t_s8    y)	{ FUNCBODY } \
	t_s16	FUNCNAME##s16	(t_s16   x, t_s16   y)	{ FUNCBODY } \
	t_s32	FUNCNAME##s32	(t_s32   x, t_s32   y)	{ FUNCBODY } \
	t_s64	FUNCNAME##s64	(t_s64   x, t_s64   y)	{ FUNCBODY } \
	t_s128	FUNCNAME##s128	(t_s128  x, t_s128  y)	{ FUNCBODY } \
	t_sint	FUNCNAME##sint	(t_sint  x, t_sint  y)	{ FUNCBODY } \

#else

	#define DEFINEFUNC_SINT_FUNCTION(FUNCNAME, FUNCBODY) \
	t_s8	FUNCNAME##s8	(t_s8    x)	{ FUNCBODY } \
	t_s16	FUNCNAME##s16	(t_s16   x)	{ FUNCBODY } \
	t_s32	FUNCNAME##s32	(t_s32   x)	{ FUNCBODY } \
	t_s64	FUNCNAME##s64	(t_s64   x)	{ FUNCBODY } \
	t_sint	FUNCNAME##sint	(t_sint  x)	{ FUNCBODY } \

	#define DEFINEFUNC_SINT_OPERATOR(FUNCNAME, FUNCBODY) \
	t_s8	FUNCNAME##s8	(t_s8    x, t_s8    y)	{ FUNCBODY } \
	t_s16	FUNCNAME##s16	(t_s16   x, t_s16   y)	{ FUNCBODY } \
	t_s32	FUNCNAME##s32	(t_s32   x, t_s32   y)	{ FUNCBODY } \
	t_s64	FUNCNAME##s64	(t_s64   x, t_s64   y)	{ FUNCBODY } \
	t_sint	FUNCNAME##sint	(t_sint  x, t_sint  y)	{ FUNCBODY } \

#endif

// DEFINEFUNC_SINT_CHECK(isnan, return (!LIBCONFIG_SINT_NAN ? 0 : (x == MIDVAL));)
// DEFINEFUNC_SINT_CHECK(isinf, return (!LIBCONFIG_SINT_INF ? 0 : (LIBCONFIG_SINT_NAN ? (x == (__typeof__(x))(MIDVAL - 1) || x == (__typeof__(x))(MIDVAL + 1)) : (x == MIDVAL)));)
DEFINEFUNC_SINT_FUNCTION(abs,   return (x < 0 ? -x : +x);)
DEFINEFUNC_SINT_FUNCTION(sgn,   return (x == 0 ? 0 : (x < 0 ? -1 : +1));)
DEFINEFUNC_SINT_OPERATOR(min,   return (x < y ? x : y);)
DEFINEFUNC_SINT_OPERATOR(max,   return (x > y ? x : y);)
DEFINEFUNC_SINT_OPERATOR(add,   return (x + y);)
DEFINEFUNC_SINT_OPERATOR(sub,   return (x - y);)
DEFINEFUNC_SINT_OPERATOR(mul,   return (x * y);)
DEFINEFUNC_SINT_OPERATOR(div,   if (y == 0)	return (LIBCONFIG_SINT_INF ? (MIDVAL - SGN(x)) : (LIBCONFIG_SINT_NAN ? MIDVAL : 0));	if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && x == MIDVAL && y == -1)	return (MIDVAL);	return (x / y);)
DEFINEFUNC_SINT_OPERATOR(mod,   if (y == 0)	return (LIBCONFIG_SINT_INF ? (MIDVAL - SGN(x)) : (LIBCONFIG_SINT_NAN ? MIDVAL : 0));	if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && x == MIDVAL && y == -1)	return (0);	return (x % y);)
DEFINEFUNC_SINT_OPERATOR(rem,   if (y == 0)	return (LIBCONFIG_SINT_INF ? (MIDVAL - SGN(x)) : (LIBCONFIG_SINT_NAN ? MIDVAL : 0));	if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && x == MIDVAL && y == -1)	return (0);	if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && (x == MIDVAL) && (y == SUBVAL))	return (SUBVAL - 1);	return ((x < 0 ? -x : +x) % (y < 0 ? -y : +y) * (x < 0 ? -1 : 1));)
DEFINEFUNC_SINT_OPERATOR(pow,   __typeof__(x) result = 1;	if (y < 0)	return (x == 0 ? 0 : (1 / x));	while (TRUE)	{	if (y & 1)	result *= x;	y >>= 1;	if (y == 0)	break;	x *= x;	}	return result;)	// t_float result = pow((t_float)x, y);	return isnan(result) ? 0 : result;)
DEFINEFUNC_SINT_FUNCTION(root2, t_float result = sqrt((t_float)x);	return isnan(result) ? 0 : result;)
DEFINEFUNC_SINT_FUNCTION(root3, t_float result = cbrt((t_float)x);	return isnan(result) ? 0 : result;)
DEFINEFUNC_SINT_OPERATOR(rootn, t_float result = pow((t_float)x, 1/y);	return isnan(result) ? 0 : result;)
DEFINEFUNC_SINT_OPERATOR(gcd,   if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && ((x == MIDVAL && y == -1) || (x == -1 && y == MIDVAL)))	return (1);	if (x && y)	while ((x %= y) && (y %= x));	return (x | y);)
DEFINEFUNC_SINT_OPERATOR(lcm,   if (!LIBCONFIG_SINT_INF && !LIBCONFIG_SINT_NAN && ((x == MIDVAL && y == -1) || (x == -1 && y == MIDVAL)))	return (1);	if (x && y)	while ((x %= y) && (y %= x));	return (x / (((x | y) == 0) ? 1 : (x | y)) * y);)



#undef  TEST
#define TEST(BITS, FUNCTION, ARG) \
	FUNCTION##s##BITS((ARG)), (ARG)

#define DEFINETEST_SINT_FUNCTION(BITS, FUNCNAME) \
void	print_test_s##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_s##BITS	expecting, \
		t_s##BITS	x) \
{ \
	TEST_INIT(s##BITS) \
	TEST_PERFORM(		s##BITS##FUNCNAME, x) \
	TEST_PRINT(s##BITS,	s##BITS##FUNCNAME, "x=" SF_S##BITS, x)\
} \
void	test_s##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +3) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, +5) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME,+10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, -3) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, -5) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME,-10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, S##BITS##_MIN+1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, S##BITS##_MAX-1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, S##BITS##_MIN  ) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, S##BITS##_MAX  ) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, S##BITS##_ERROR) ); \
}

DEFINETEST_SINT_FUNCTION(8, abs)
DEFINETEST_SINT_FUNCTION(8, sgn)
DEFINETEST_SINT_FUNCTION(8, root2)
DEFINETEST_SINT_FUNCTION(8, root3)

DEFINETEST_SINT_FUNCTION(16, abs)
DEFINETEST_SINT_FUNCTION(16, sgn)
DEFINETEST_SINT_FUNCTION(16, root2)
DEFINETEST_SINT_FUNCTION(16, root3)

DEFINETEST_SINT_FUNCTION(32, abs)
DEFINETEST_SINT_FUNCTION(32, sgn)
DEFINETEST_SINT_FUNCTION(32, root2)
DEFINETEST_SINT_FUNCTION(32, root3)

DEFINETEST_SINT_FUNCTION(64, abs)
DEFINETEST_SINT_FUNCTION(64, sgn)
DEFINETEST_SINT_FUNCTION(64, root2)
DEFINETEST_SINT_FUNCTION(64, root3)

#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_FUNCTION(128, abs)
DEFINETEST_SINT_FUNCTION(128, sgn)
DEFINETEST_SINT_FUNCTION(128, root2)
DEFINETEST_SINT_FUNCTION(128, root3)
#endif



//


/*
DEFINETEST_SINT_FUNCTION(8, isnan)
DEFINETEST_SINT_FUNCTION(8, isinf)

DEFINETEST_SINT_FUNCTION(16, isnan)
DEFINETEST_SINT_FUNCTION(16, isinf)

DEFINETEST_SINT_FUNCTION(32, isnan)
DEFINETEST_SINT_FUNCTION(32, isinf)

DEFINETEST_SINT_FUNCTION(64, isnan)
DEFINETEST_SINT_FUNCTION(64, isinf)

#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_FUNCTION(128, isnan)
DEFINETEST_SINT_FUNCTION(128, isinf)
#endif
*/



#undef  TEST
#define TEST(BITS, OPERATOR, LHS, RHS) \
	OPERATOR##s##BITS((LHS),(RHS)), (LHS), (RHS)

#define DEFINETEST_SINT_OPERATOR(BITS, FUNCNAME, MAYFPE) \
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
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME,  0,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME,  0, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME,  0, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +1,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, 10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +1, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +1, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +2,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, 10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, +2, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, +2, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, -1,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, 10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -1, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, -1, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, -2,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, 10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, -2, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, -2, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, 10,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, 10) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, 10, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, 10, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_MAX,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MAX, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_MAX, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_MIN,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MIN, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MIN, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_MIN, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MIN, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MIN, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_MIN, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_MIN, S##BITS##_ERROR) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_ERROR,  0) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, +1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, +2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, -1) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, -2) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, S##BITS##_MAX) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, S##BITS##_ERROR, S##BITS##_MIN) ); \
	print_test_s##BITS##FUNCNAME("s"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, S##BITS##_ERROR, S##BITS##_ERROR) ); \
}

DEFINETEST_SINT_OPERATOR(8, min, FALSE)
DEFINETEST_SINT_OPERATOR(8, max, FALSE)
DEFINETEST_SINT_OPERATOR(8, add, FALSE)
DEFINETEST_SINT_OPERATOR(8, sub, FALSE)
DEFINETEST_SINT_OPERATOR(8, mul, FALSE)
DEFINETEST_SINT_OPERATOR(8, div, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(8, mod, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(8, rem, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(8, pow, FALSE)
//DEFINETEST_SINT_OPERATOR(8, rootn, FALSE)
DEFINETEST_SINT_OPERATOR(8, lcm, FALSE)
DEFINETEST_SINT_OPERATOR(8, gcd, FALSE)

DEFINETEST_SINT_OPERATOR(16, min, FALSE)
DEFINETEST_SINT_OPERATOR(16, max, FALSE)
DEFINETEST_SINT_OPERATOR(16, add, FALSE)
DEFINETEST_SINT_OPERATOR(16, sub, FALSE)
DEFINETEST_SINT_OPERATOR(16, mul, FALSE)
DEFINETEST_SINT_OPERATOR(16, div, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(16, mod, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(16, rem, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(16, pow, FALSE)
//DEFINETEST_SINT_OPERATOR(16, rootn, FALSE)
DEFINETEST_SINT_OPERATOR(16, lcm, FALSE)
DEFINETEST_SINT_OPERATOR(16, gcd, FALSE)

DEFINETEST_SINT_OPERATOR(32, min, FALSE)
DEFINETEST_SINT_OPERATOR(32, max, FALSE)
DEFINETEST_SINT_OPERATOR(32, add, FALSE)
DEFINETEST_SINT_OPERATOR(32, sub, FALSE)
DEFINETEST_SINT_OPERATOR(32, mul, FALSE)
DEFINETEST_SINT_OPERATOR(32, div, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(32, mod, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(32, rem, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(32, pow, FALSE)
//DEFINETEST_SINT_OPERATOR(32, rootn, FALSE)
DEFINETEST_SINT_OPERATOR(32, lcm, FALSE)
DEFINETEST_SINT_OPERATOR(32, gcd, FALSE)

DEFINETEST_SINT_OPERATOR(64, min, FALSE)
DEFINETEST_SINT_OPERATOR(64, max, FALSE)
DEFINETEST_SINT_OPERATOR(64, add, FALSE)
DEFINETEST_SINT_OPERATOR(64, sub, FALSE)
DEFINETEST_SINT_OPERATOR(64, mul, FALSE)
DEFINETEST_SINT_OPERATOR(64, div, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(64, mod, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(64, rem, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(64, pow, FALSE)
//DEFINETEST_SINT_OPERATOR(64, rootn, FALSE)
DEFINETEST_SINT_OPERATOR(64, lcm, FALSE)
DEFINETEST_SINT_OPERATOR(64, gcd, FALSE)

#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_OPERATOR(128, min, FALSE)
DEFINETEST_SINT_OPERATOR(128, max, FALSE)
DEFINETEST_SINT_OPERATOR(128, add, FALSE)
DEFINETEST_SINT_OPERATOR(128, sub, FALSE)
DEFINETEST_SINT_OPERATOR(128, mul, FALSE)
DEFINETEST_SINT_OPERATOR(128, div, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(128, mod, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(128, rem, ALLOW_SIGFPE)
DEFINETEST_SINT_OPERATOR(128, pow, FALSE)
//DEFINETEST_SINT_OPERATOR(128, rootn, FALSE)
DEFINETEST_SINT_OPERATOR(128, lcm, FALSE)
DEFINETEST_SINT_OPERATOR(128, gcd, FALSE)
#endif



// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
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
	#define RUNTESTSUITE(FUNCNAME) \
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
	RUNTESTSUITE(abs)
	RUNTESTSUITE(sgn)
	RUNTESTSUITE(min)
	RUNTESTSUITE(max)
	RUNTESTSUITE(add)
	RUNTESTSUITE(sub)
	RUNTESTSUITE(mul)
	RUNTESTSUITE(div)
	RUNTESTSUITE(mod)
	RUNTESTSUITE(rem)
	RUNTESTSUITE(pow)
//	RUNTESTSUITE(root2)
//	RUNTESTSUITE(root3)
//	RUNTESTSUITE(rootn)
//	RUNTESTSUITE(lcm)
//	RUNTESTSUITE(gcd)

	return (OK);
}
