
#include <math.h>

#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
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



#define MIDVAL	(__typeof__(x._))((__typeof__(x._))1 << (sizeof(x._)*8 - 1))
#define ENDVAL	(__typeof__(x._))(~(__typeof__(x._))0)
#define ABS(X)	(__typeof__(X))((X) < 0 ? -(X) : +(X))
#define SGN(X)	(__typeof__(X))((X) < 0 ? -1 : +1)



#if LIBCONFIG_USE_INT128

	#define DEFINEFUNC_FIXED_CHECK(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##q8	(t_q8    x)	{ t_f64   x_f = Float_FromQ8	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q16	(t_q16   x)	{ t_f64   x_f = Float_FromQ16	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q32	(t_q32   x)	{ t_f64   x_f = Float_FromQ32	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q64	(t_q64   x)	{ t_f64   x_f = Float_FromQ64	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q128	(t_q128  x)	{ t_f64   x_f = Float_FromQ128	(x);	FUNCBODY	} \

	#define DEFINEFUNC_FIXED_RELATION(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##q8	(t_q8    x, t_q8    y)	{ t_f64   x_f = Float_FromQ8	(x);  t_f64   y_f = Float_FromQ8	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q16	(t_q16   x, t_q16   y)	{ t_f64   x_f = Float_FromQ16	(x);  t_f64   y_f = Float_FromQ16	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q32	(t_q32   x, t_q32   y)	{ t_f64   x_f = Float_FromQ32	(x);  t_f64   y_f = Float_FromQ32	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q64	(t_q64   x, t_q64   y)	{ t_f64   x_f = Float_FromQ64	(x);  t_f64   y_f = Float_FromQ64	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q128	(t_q128  x, t_q128  y)	{ t_f64   x_f = Float_FromQ128	(x);  t_f64   y_f = Float_FromQ128	(y);	FUNCBODY	} \

	#define DEFINEFUNC_FIXED_FUNCTION(FUNCNAME, FUNCBODY) \
	t_q8	FUNCNAME##q8	(t_q8    x)	{ t_f64   x_f = Float_FromQ8	(x);	t_f64   result = NAN;	FUNCBODY	return Q8_FromF64	(result);	} \
	t_q16	FUNCNAME##q16	(t_q16   x)	{ t_f64   x_f = Float_FromQ16	(x);	t_f64   result = NAN;	FUNCBODY	return Q16_FromF64	(result);	} \
	t_q32	FUNCNAME##q32	(t_q32   x)	{ t_f64   x_f = Float_FromQ32	(x);	t_f64   result = NAN;	FUNCBODY	return Q32_FromF64	(result);	} \
	t_q64	FUNCNAME##q64	(t_q64   x)	{ t_f64   x_f = Float_FromQ64	(x);	t_f64   result = NAN;	FUNCBODY	return Q64_FromF64	(result);	} \
	t_q128	FUNCNAME##q128	(t_q128  x)	{ t_f64   x_f = Float_FromQ128	(x);	t_f64   result = NAN;	FUNCBODY	return Q128_FromF64	(result);	} \

	#define DEFINEFUNC_FIXED_OPERATOR(FUNCNAME, FUNCBODY) \
	t_q8	FUNCNAME##q8	(t_q8    x, t_q8    y)	{ t_f64   x_f = Float_FromQ8	(x);  t_f64   y_f = Float_FromQ8	(y);	t_f64   result = NAN;	FUNCBODY	return Q8_FromF64	(result);	} \
	t_q16	FUNCNAME##q16	(t_q16   x, t_q16   y)	{ t_f64   x_f = Float_FromQ16	(x);  t_f64   y_f = Float_FromQ16	(y);	t_f64   result = NAN;	FUNCBODY	return Q16_FromF64	(result);	} \
	t_q32	FUNCNAME##q32	(t_q32   x, t_q32   y)	{ t_f64   x_f = Float_FromQ32	(x);  t_f64   y_f = Float_FromQ32	(y);	t_f64   result = NAN;	FUNCBODY	return Q32_FromF64	(result);	} \
	t_q64	FUNCNAME##q64	(t_q64   x, t_q64   y)	{ t_f64   x_f = Float_FromQ64	(x);  t_f64   y_f = Float_FromQ64	(y);	t_f64   result = NAN;	FUNCBODY	return Q64_FromF64	(result);	} \
	t_q128	FUNCNAME##q128	(t_q128  x, t_q128  y)	{ t_f64   x_f = Float_FromQ128	(x);  t_f64   y_f = Float_FromQ128	(y);	t_f64   result = NAN;	FUNCBODY	return Q128_FromF64	(result);	} \

#else

	#define DEFINEFUNC_FIXED_CHECK(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##q8	(t_q8    x)	{ t_f64   x_f = Float_FromQ8	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q16	(t_q16   x)	{ t_f64   x_f = Float_FromQ16	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q32	(t_q32   x)	{ t_f64   x_f = Float_FromQ32	(x);	FUNCBODY	} \
	t_bool	FUNCNAME##q64	(t_q64   x)	{ t_f64   x_f = Float_FromQ64	(x);	FUNCBODY	} \

	#define DEFINEFUNC_FIXED_RELATION(FUNCNAME, FUNCBODY) \
	t_bool	FUNCNAME##q8	(t_q8    x, t_q8    y)	{ t_f64   x_f = Float_FromQ8	(x);  t_f64   y_f = Float_FromQ8	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q16	(t_q16   x, t_q16   y)	{ t_f64   x_f = Float_FromQ16	(x);  t_f64   y_f = Float_FromQ16	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q32	(t_q32   x, t_q32   y)	{ t_f64   x_f = Float_FromQ32	(x);  t_f64   y_f = Float_FromQ32	(y);	FUNCBODY	} \
	t_bool	FUNCNAME##q64	(t_q64   x, t_q64   y)	{ t_f64   x_f = Float_FromQ64	(x);  t_f64   y_f = Float_FromQ64	(y);	FUNCBODY	} \

	#define DEFINEFUNC_FIXED_FUNCTION(FUNCNAME, FUNCBODY) \
	t_q8	FUNCNAME##q8	(t_q8    x)	{ t_f64   x_f = Float_FromQ8	(x);	t_f64   result = NAN;	FUNCBODY	return Q8_FromF64	(result);	} \
	t_q16	FUNCNAME##q16	(t_q16   x)	{ t_f64   x_f = Float_FromQ16	(x);	t_f64   result = NAN;	FUNCBODY	return Q16_FromF64	(result);	} \
	t_q32	FUNCNAME##q32	(t_q32   x)	{ t_f64   x_f = Float_FromQ32	(x);	t_f64   result = NAN;	FUNCBODY	return Q32_FromF64	(result);	} \
	t_q64	FUNCNAME##q64	(t_q64   x)	{ t_f64   x_f = Float_FromQ64	(x);	t_f64   result = NAN;	FUNCBODY	return Q64_FromF64	(result);	} \

	#define DEFINEFUNC_FIXED_OPERATOR(FUNCNAME, FUNCBODY) \
	t_q8	FUNCNAME##q8	(t_q8    x, t_q8    y)	{ t_f64   x_f = Float_FromQ8	(x);  t_f64   y_f = Float_FromQ8	(y);	t_f64   result = NAN;	FUNCBODY	return Q8_FromF64	(result);	} \
	t_q16	FUNCNAME##q16	(t_q16   x, t_q16   y)	{ t_f64   x_f = Float_FromQ16	(x);  t_f64   y_f = Float_FromQ16	(y);	t_f64   result = NAN;	FUNCBODY	return Q16_FromF64	(result);	} \
	t_q32	FUNCNAME##q32	(t_q32   x, t_q32   y)	{ t_f64   x_f = Float_FromQ32	(x);  t_f64   y_f = Float_FromQ32	(y);	t_f64   result = NAN;	FUNCBODY	return Q32_FromF64	(result);	} \
	t_q64	FUNCNAME##q64	(t_q64   x, t_q64   y)	{ t_f64   x_f = Float_FromQ64	(x);  t_f64   y_f = Float_FromQ64	(y);	t_f64   result = NAN;	FUNCBODY	return Q64_FromF64	(result);	} \

#endif

// DEFINEFUNC_FIXED_CHECK(isnan, return (!LIBCONFIG_FIXED_NAN ? 0 : (x_f == MIDVAL));)
// DEFINEFUNC_FIXED_CHECK(isinf, return (!LIBCONFIG_FIXED_INF ? 0 : (LIBCONFIG_FIXED_NAN ? (x_f == (__typeof__(x_f))(MIDVAL - 1) || x_f == (__typeof__(x_f))(MIDVAL + 1)) : (x_f == MIDVAL)));)
DEFINEFUNC_FIXED_FUNCTION(abs,   result = fabs(x_f);)
DEFINEFUNC_FIXED_FUNCTION(sgn,   result = isnan(x_f) ? 0 : (x_f == 0 ? 0 : (x_f < 0 ? -1 : +1));)
DEFINEFUNC_FIXED_OPERATOR(min,   if (isnan(x_f) && isnan(y_f)) result = NAN;	else if (isnan(x_f)) result = y_f;	else if (isnan(y_f)) result = x_f;	else result = (x_f < y_f ? x_f : y_f);)
DEFINEFUNC_FIXED_OPERATOR(max,   if (isnan(x_f) && isnan(y_f)) result = NAN;	else if (isnan(x_f)) result = y_f;	else if (isnan(y_f)) result = x_f;	else result = (x_f > y_f ? x_f : y_f);)
DEFINEFUNC_FIXED_OPERATOR(add,   result = (x_f + y_f);)
DEFINEFUNC_FIXED_OPERATOR(sub,   result = (x_f - y_f);)
DEFINEFUNC_FIXED_OPERATOR(mul,   result = (x_f * y_f);)
DEFINEFUNC_FIXED_OPERATOR(div,   result = (x_f / y_f);)
DEFINEFUNC_FIXED_OPERATOR(mod,   result = fmod(x_f, y_f);)
DEFINEFUNC_FIXED_OPERATOR(rem,   int tmp;	result = remquo(x_f, y_f, &tmp);)
DEFINEFUNC_FIXED_OPERATOR(pow,   result = pow(x_f, y_f);)
DEFINEFUNC_FIXED_FUNCTION(root2, result = sqrt(x_f);)
DEFINEFUNC_FIXED_FUNCTION(root3, result = cbrt(x_f);)
DEFINEFUNC_FIXED_OPERATOR(rootn, result = pow(x_f, 1. / y_f);)



//


/*
DEFINETEST_FIXED_FUNCTION(8, isnan)
DEFINETEST_FIXED_FUNCTION(8, isinf)

DEFINETEST_FIXED_FUNCTION(16, isnan)
DEFINETEST_FIXED_FUNCTION(16, isinf)

DEFINETEST_FIXED_FUNCTION(32, isnan)
DEFINETEST_FIXED_FUNCTION(32, isinf)

DEFINETEST_FIXED_FUNCTION(64, isnan)
DEFINETEST_FIXED_FUNCTION(64, isinf)

#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_FUNCTION(128, isnan)
DEFINETEST_FIXED_FUNCTION(128, isinf)
#endif
*/



#undef  TEST
#define TEST(BITS, FUNCTION, ARG) \
	FUNCTION##q##BITS((ARG)), (ARG)

#define DEFINETEST_FIXED_FUNCTION(BITS, FUNCNAME) \
void	print_test_q##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_q##BITS	expecting, \
		t_q##BITS	x) \
{ \
	char*	str_x = q##BITS##tostr(x); \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		q##BITS##FUNCNAME, x) \
	TEST_PRINT(q##BITS,	q##BITS##FUNCNAME, "x=%s", str_x)\
	free(str_x); \
} \
void	test_q##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){+10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){-10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_ERROR) ); \
}

DEFINETEST_FIXED_FUNCTION(8, abs)
DEFINETEST_FIXED_FUNCTION(8, sgn)
DEFINETEST_FIXED_FUNCTION(8, root2)
DEFINETEST_FIXED_FUNCTION(8, root3)

DEFINETEST_FIXED_FUNCTION(16, abs)
DEFINETEST_FIXED_FUNCTION(16, sgn)
DEFINETEST_FIXED_FUNCTION(16, root2)
DEFINETEST_FIXED_FUNCTION(16, root3)

DEFINETEST_FIXED_FUNCTION(32, abs)
DEFINETEST_FIXED_FUNCTION(32, sgn)
DEFINETEST_FIXED_FUNCTION(32, root2)
DEFINETEST_FIXED_FUNCTION(32, root3)

DEFINETEST_FIXED_FUNCTION(64, abs)
DEFINETEST_FIXED_FUNCTION(64, sgn)
DEFINETEST_FIXED_FUNCTION(64, root2)
DEFINETEST_FIXED_FUNCTION(64, root3)

#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_FUNCTION(128, abs)
DEFINETEST_FIXED_FUNCTION(128, sgn)
DEFINETEST_FIXED_FUNCTION(128, root2)
DEFINETEST_FIXED_FUNCTION(128, root3)
#endif



#undef  TEST
#define TEST(BITS, OPERATOR, LHS, RHS) \
	OPERATOR##q##BITS((LHS),(RHS)), (LHS), (RHS)

#define DEFINETEST_FIXED_OPERATOR(BITS, FUNCNAME, MAYFPE) \
void	print_test_q##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_q##BITS	expecting, \
		t_q##BITS	x, \
		t_q##BITS	y) \
{ \
	char*	str_x = q##BITS##tostr(x); \
	char*	str_y = q##BITS##tostr(y); \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		q##BITS##FUNCNAME, x, y) \
	TEST_PRINT(q##BITS,	q##BITS##FUNCNAME, "x=%s, y=%s", str_x, str_y)\
	free(str_x); \
	free(str_y); \
} \
void	test_q##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){ 0}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, (t_q##BITS){10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+1}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){+1}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, (t_q##BITS){10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){+2}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){+2}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, (t_q##BITS){10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-1}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){-1}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, (t_q##BITS){10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){-2}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){-2}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, (t_q##BITS){10}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, (t_q##BITS){10}, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, (t_q##BITS){10}, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_MAX, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MAX, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_MAX, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_MIN, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MIN, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MIN, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_MIN, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MIN, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MIN, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_MIN, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_MIN, Q##BITS##_ERROR) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_ERROR, (t_q##BITS){ 0}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, (t_q##BITS){+1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, (t_q##BITS){+2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, (t_q##BITS){-1}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, (t_q##BITS){-2}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, Q##BITS##_ERROR, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	MAYFPE, TEST(BITS, FUNCNAME, Q##BITS##_ERROR, Q##BITS##_ERROR) ); \
}

DEFINETEST_FIXED_OPERATOR(8, min, FALSE)
DEFINETEST_FIXED_OPERATOR(8, max, FALSE)
DEFINETEST_FIXED_OPERATOR(8, add, FALSE)
DEFINETEST_FIXED_OPERATOR(8, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(8, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(8, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(8, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(8, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(8, pow, FALSE)
//DEFINETEST_FIXED_OPERATOR(8, rootn, FALSE)

DEFINETEST_FIXED_OPERATOR(16, min, FALSE)
DEFINETEST_FIXED_OPERATOR(16, max, FALSE)
DEFINETEST_FIXED_OPERATOR(16, add, FALSE)
DEFINETEST_FIXED_OPERATOR(16, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(16, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(16, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, pow, FALSE)
//DEFINETEST_FIXED_OPERATOR(16, rootn, FALSE)

DEFINETEST_FIXED_OPERATOR(32, min, FALSE)
DEFINETEST_FIXED_OPERATOR(32, max, FALSE)
DEFINETEST_FIXED_OPERATOR(32, add, FALSE)
DEFINETEST_FIXED_OPERATOR(32, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(32, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(32, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, pow, FALSE)
//DEFINETEST_FIXED_OPERATOR(32, rootn, FALSE)

DEFINETEST_FIXED_OPERATOR(64, min, FALSE)
DEFINETEST_FIXED_OPERATOR(64, max, FALSE)
DEFINETEST_FIXED_OPERATOR(64, add, FALSE)
DEFINETEST_FIXED_OPERATOR(64, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(64, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(64, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, pow, FALSE)
//DEFINETEST_FIXED_OPERATOR(64, rootn, FALSE)

#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_OPERATOR(128, min, FALSE)
DEFINETEST_FIXED_OPERATOR(128, max, FALSE)
DEFINETEST_FIXED_OPERATOR(128, add, FALSE)
DEFINETEST_FIXED_OPERATOR(128, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(128, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(128, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(128, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(128, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(128, pow, FALSE)
//DEFINETEST_FIXED_OPERATOR(128, rootn, FALSE)
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

int		testsuite_math_fixed(void)
{
	print_suite_title("libccc/math/fixed");

	print_nonstd();

#if LIBCONFIG_USE_INT128
	#define RUNTESTSUITE(FUNCNAME) \
		test_q8##FUNCNAME(); \
		test_q16##FUNCNAME(); \
		test_q32##FUNCNAME(); \
		test_q64##FUNCNAME(); \
		test_q128##FUNCNAME(); \

#else
	#define RUNTESTSUITE(FUNCNAME) \
		test_q8##FUNCNAME(); \
		test_q16##FUNCNAME(); \
		test_q32##FUNCNAME(); \
		test_q64##FUNCNAME(); \

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
	RUNTESTSUITE(root2)
	RUNTESTSUITE(root3)
//	RUNTESTSUITE(rootn)

	return (OK);
}
