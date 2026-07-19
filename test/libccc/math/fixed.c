
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
DEFINEFUNC_FIXED_OPERATOR(hypot, if (isnan(x_f) || isnan(y_f)) result = NAN;	else result = hypot(x_f, y_f);)
DEFINEFUNC_FIXED_OPERATOR(logn,  result = (log2(x_f) / log2(y_f));)
DEFINEFUNC_FIXED_OPERATOR(atan2, result = atan2(x_f, y_f);)
DEFINEFUNC_FIXED_FUNCTION(exp,   result = exp(x_f);)
DEFINEFUNC_FIXED_FUNCTION(exp2,  result = exp2(x_f);)
DEFINEFUNC_FIXED_FUNCTION(exp10, result = pow(10., x_f);)
DEFINEFUNC_FIXED_FUNCTION(ln,    result = log(x_f);)
DEFINEFUNC_FIXED_FUNCTION(log2,  result = log2(x_f);)
DEFINEFUNC_FIXED_FUNCTION(log10, result = log10(x_f);)
DEFINEFUNC_FIXED_FUNCTION(sin,   result = sin(x_f);)
DEFINEFUNC_FIXED_FUNCTION(cos,   result = cos(x_f);)
DEFINEFUNC_FIXED_FUNCTION(tan,   result = tan(x_f);)
DEFINEFUNC_FIXED_FUNCTION(asin,  result = asin(x_f);)
DEFINEFUNC_FIXED_FUNCTION(acos,  result = acos(x_f);)
DEFINEFUNC_FIXED_FUNCTION(atan,  result = atan(x_f);)
DEFINEFUNC_FIXED_FUNCTION(sinh,  result = sinh(x_f);)
DEFINEFUNC_FIXED_FUNCTION(cosh,  result = cosh(x_f);)
DEFINEFUNC_FIXED_FUNCTION(tanh,  result = tanh(x_f);)
DEFINEFUNC_FIXED_FUNCTION(asinh, result = asinh(x_f);)
DEFINEFUNC_FIXED_FUNCTION(acosh, result = acosh(x_f);)
DEFINEFUNC_FIXED_FUNCTION(atanh, result = atanh(x_f);)

#if LIBCONFIG_USE_INT128
#define DEFINEFUNC_FIXED_ROOTN_REF_128	DEFINEFUNC_FIXED_ROOTN_REF(128)
#define DEFINEFUNC_FIXED_ISPRIME_REF_128	DEFINEFUNC_FIXED_ISPRIME_REF(128)
#else
#define DEFINEFUNC_FIXED_ROOTN_REF_128
#define DEFINEFUNC_FIXED_ISPRIME_REF_128
#endif

// custom reference for `rootn`, since its second argument is a `t_u8`
#define DEFINEFUNC_FIXED_ROOTN_REF(BITS) \
t_q##BITS	rootnq##BITS(t_q##BITS x, t_u8 n) \
{ \
	t_f64	x_f = Float_FromQ##BITS(x); \
	t_f64	result = NAN; \
	if (n == 0)							result = NAN; \
	else if (x_f < 0 && (n % 2) == 1)	result = -pow(-x_f, 1. / (t_f64)n); \
	else if (x_f < 0)					result = NAN; \
	else								result = pow(x_f, 1. / (t_f64)n); \
	return (Q##BITS##_FromF64(result)); \
} \

DEFINEFUNC_FIXED_ROOTN_REF(8)
DEFINEFUNC_FIXED_ROOTN_REF(16)
DEFINEFUNC_FIXED_ROOTN_REF(32)
DEFINEFUNC_FIXED_ROOTN_REF(64)
DEFINEFUNC_FIXED_ROOTN_REF_128

// custom reference for `isprime`, since it returns a `t_bool`
#define DEFINEFUNC_FIXED_ISPRIME_REF(BITS) \
t_bool	isprimeq##BITS(t_q##BITS x) \
{ \
	t_f64	x_f = Float_FromQ##BITS(x); \
	if (isnan(x_f) || isinf(x_f) || x_f <= 1 || x_f != floor(x_f)) \
		return (FALSE); \
	t_u64	value = (t_u64)x_f; \
	for (t_u64 i = 2; i * i <= value; ++i) \
	{ \
		if (value % i == 0) \
			return (FALSE); \
	} \
	return (TRUE); \
} \

DEFINEFUNC_FIXED_ISPRIME_REF(8)
DEFINEFUNC_FIXED_ISPRIME_REF(16)
DEFINEFUNC_FIXED_ISPRIME_REF(32)
DEFINEFUNC_FIXED_ISPRIME_REF(64)
DEFINEFUNC_FIXED_ISPRIME_REF_128



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
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){+3}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){-3}) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM / 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)-(Q##BITS##_DENOM / 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)-(Q##BITS##_DENOM) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM * 3 / 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM * 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)-(Q##BITS##_DENOM * 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM * 5 / 2) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM * 3) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)-(Q##BITS##_DENOM * 3) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)(Q##BITS##_DENOM * 4) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, (t_q##BITS){ (t_s##BITS)-(Q##BITS##_DENOM * 4) }) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_MIN) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_MAX) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE, TEST(BITS, FUNCNAME, Q##BITS##_ERROR) ); \
}

DEFINETEST_FIXED_FUNCTION(8, abs)
DEFINETEST_FIXED_FUNCTION(8, sgn)
DEFINETEST_FIXED_FUNCTION(8, root2)
DEFINETEST_FIXED_FUNCTION(8, root3)
DEFINETEST_FIXED_FUNCTION(8, exp)
DEFINETEST_FIXED_FUNCTION(8, exp2)
DEFINETEST_FIXED_FUNCTION(8, exp10)
DEFINETEST_FIXED_FUNCTION(8, ln)
DEFINETEST_FIXED_FUNCTION(8, log2)
DEFINETEST_FIXED_FUNCTION(8, log10)
DEFINETEST_FIXED_FUNCTION(8, sin)
DEFINETEST_FIXED_FUNCTION(8, cos)
DEFINETEST_FIXED_FUNCTION(8, tan)
DEFINETEST_FIXED_FUNCTION(8, asin)
DEFINETEST_FIXED_FUNCTION(8, acos)
DEFINETEST_FIXED_FUNCTION(8, atan)
DEFINETEST_FIXED_FUNCTION(8, sinh)
DEFINETEST_FIXED_FUNCTION(8, cosh)
DEFINETEST_FIXED_FUNCTION(8, tanh)
DEFINETEST_FIXED_FUNCTION(8, asinh)
DEFINETEST_FIXED_FUNCTION(8, acosh)
DEFINETEST_FIXED_FUNCTION(8, atanh)

DEFINETEST_FIXED_FUNCTION(16, abs)
DEFINETEST_FIXED_FUNCTION(16, sgn)
DEFINETEST_FIXED_FUNCTION(16, root2)
DEFINETEST_FIXED_FUNCTION(16, root3)
DEFINETEST_FIXED_FUNCTION(16, exp)
DEFINETEST_FIXED_FUNCTION(16, exp2)
DEFINETEST_FIXED_FUNCTION(16, exp10)
DEFINETEST_FIXED_FUNCTION(16, ln)
DEFINETEST_FIXED_FUNCTION(16, log2)
DEFINETEST_FIXED_FUNCTION(16, log10)
DEFINETEST_FIXED_FUNCTION(16, sin)
DEFINETEST_FIXED_FUNCTION(16, cos)
DEFINETEST_FIXED_FUNCTION(16, tan)
DEFINETEST_FIXED_FUNCTION(16, asin)
DEFINETEST_FIXED_FUNCTION(16, acos)
DEFINETEST_FIXED_FUNCTION(16, atan)
DEFINETEST_FIXED_FUNCTION(16, sinh)
DEFINETEST_FIXED_FUNCTION(16, cosh)
DEFINETEST_FIXED_FUNCTION(16, tanh)
DEFINETEST_FIXED_FUNCTION(16, asinh)
DEFINETEST_FIXED_FUNCTION(16, acosh)
DEFINETEST_FIXED_FUNCTION(16, atanh)

DEFINETEST_FIXED_FUNCTION(32, abs)
DEFINETEST_FIXED_FUNCTION(32, sgn)
DEFINETEST_FIXED_FUNCTION(32, root2)
DEFINETEST_FIXED_FUNCTION(32, root3)
DEFINETEST_FIXED_FUNCTION(32, exp)
DEFINETEST_FIXED_FUNCTION(32, exp2)
DEFINETEST_FIXED_FUNCTION(32, exp10)
DEFINETEST_FIXED_FUNCTION(32, ln)
DEFINETEST_FIXED_FUNCTION(32, log2)
DEFINETEST_FIXED_FUNCTION(32, log10)
DEFINETEST_FIXED_FUNCTION(32, sin)
DEFINETEST_FIXED_FUNCTION(32, cos)
DEFINETEST_FIXED_FUNCTION(32, tan)
DEFINETEST_FIXED_FUNCTION(32, asin)
DEFINETEST_FIXED_FUNCTION(32, acos)
DEFINETEST_FIXED_FUNCTION(32, atan)
DEFINETEST_FIXED_FUNCTION(32, sinh)
DEFINETEST_FIXED_FUNCTION(32, cosh)
DEFINETEST_FIXED_FUNCTION(32, tanh)
DEFINETEST_FIXED_FUNCTION(32, asinh)
DEFINETEST_FIXED_FUNCTION(32, acosh)
DEFINETEST_FIXED_FUNCTION(32, atanh)

DEFINETEST_FIXED_FUNCTION(64, abs)
DEFINETEST_FIXED_FUNCTION(64, sgn)
DEFINETEST_FIXED_FUNCTION(64, root2)
DEFINETEST_FIXED_FUNCTION(64, root3)
DEFINETEST_FIXED_FUNCTION(64, exp)
DEFINETEST_FIXED_FUNCTION(64, exp2)
DEFINETEST_FIXED_FUNCTION(64, exp10)
DEFINETEST_FIXED_FUNCTION(64, ln)
DEFINETEST_FIXED_FUNCTION(64, log2)
DEFINETEST_FIXED_FUNCTION(64, log10)
DEFINETEST_FIXED_FUNCTION(64, sin)
DEFINETEST_FIXED_FUNCTION(64, cos)
DEFINETEST_FIXED_FUNCTION(64, tan)
DEFINETEST_FIXED_FUNCTION(64, asin)
DEFINETEST_FIXED_FUNCTION(64, acos)
DEFINETEST_FIXED_FUNCTION(64, atan)
DEFINETEST_FIXED_FUNCTION(64, sinh)
DEFINETEST_FIXED_FUNCTION(64, cosh)
DEFINETEST_FIXED_FUNCTION(64, tanh)
DEFINETEST_FIXED_FUNCTION(64, asinh)
DEFINETEST_FIXED_FUNCTION(64, acosh)
DEFINETEST_FIXED_FUNCTION(64, atanh)

#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_FUNCTION(128, abs)
DEFINETEST_FIXED_FUNCTION(128, sgn)
DEFINETEST_FIXED_FUNCTION(128, root2)
DEFINETEST_FIXED_FUNCTION(128, root3)
DEFINETEST_FIXED_FUNCTION(128, exp)
DEFINETEST_FIXED_FUNCTION(128, exp2)
DEFINETEST_FIXED_FUNCTION(128, exp10)
DEFINETEST_FIXED_FUNCTION(128, ln)
DEFINETEST_FIXED_FUNCTION(128, log2)
DEFINETEST_FIXED_FUNCTION(128, log10)
DEFINETEST_FIXED_FUNCTION(128, sin)
DEFINETEST_FIXED_FUNCTION(128, cos)
DEFINETEST_FIXED_FUNCTION(128, tan)
DEFINETEST_FIXED_FUNCTION(128, asin)
DEFINETEST_FIXED_FUNCTION(128, acos)
DEFINETEST_FIXED_FUNCTION(128, atan)
DEFINETEST_FIXED_FUNCTION(128, sinh)
DEFINETEST_FIXED_FUNCTION(128, cosh)
DEFINETEST_FIXED_FUNCTION(128, tanh)
DEFINETEST_FIXED_FUNCTION(128, asinh)
DEFINETEST_FIXED_FUNCTION(128, acosh)
DEFINETEST_FIXED_FUNCTION(128, atanh)
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

//! Same as DEFINETEST_FIXED_OPERATOR, but with additional fractional/integer-valued test cases
#define QV(BITS, EXPR)	((t_q##BITS){ (t_s##BITS)(EXPR) })
#define DEFINETEST_FIXED_OPERATOR_EXT(BITS, FUNCNAME, MAYFPE) \
void	test_q##BITS##FUNCNAME##_ext(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME         |TESTFLAG| TEST */ \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 1)), QV(BITS,  (Q##BITS##_DENOM * 1))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 2)), QV(BITS,  (Q##BITS##_DENOM * 1))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 2)), QV(BITS,  (Q##BITS##_DENOM * 2))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 3)), QV(BITS,  (Q##BITS##_DENOM * 2))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM / 2)), QV(BITS,  (Q##BITS##_DENOM * 2))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 2)), QV(BITS, -(Q##BITS##_DENOM * 1))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS, -(Q##BITS##_DENOM * 3)), QV(BITS,  (Q##BITS##_DENOM * 2))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 4)), QV(BITS,  (Q##BITS##_DENOM * 4))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 4)), QV(BITS, -(Q##BITS##_DENOM * 4))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM*5/2)), QV(BITS,  (Q##BITS##_DENOM * 3))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM * 3)), QV(BITS,  (Q##BITS##_DENOM / 2))) ); \
	print_test_q##BITS##FUNCNAME("q"#BITS#FUNCNAME" ",	FALSE,  TEST(BITS, FUNCNAME, QV(BITS,  (Q##BITS##_DENOM*5/2)), QV(BITS,  (Q##BITS##_DENOM / 2))) ); \
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
DEFINETEST_FIXED_OPERATOR(8, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR(8, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(8, atan2, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(8, mul, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(8, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(8, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(8, pow, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(8, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(8, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(8, atan2, FALSE)

DEFINETEST_FIXED_OPERATOR(16, min, FALSE)
DEFINETEST_FIXED_OPERATOR(16, max, FALSE)
DEFINETEST_FIXED_OPERATOR(16, add, FALSE)
DEFINETEST_FIXED_OPERATOR(16, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(16, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(16, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, pow, FALSE)
DEFINETEST_FIXED_OPERATOR(16, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR(16, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(16, atan2, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(16, mul, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(16, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(16, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(16, pow, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(16, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(16, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(16, atan2, FALSE)

DEFINETEST_FIXED_OPERATOR(32, min, FALSE)
DEFINETEST_FIXED_OPERATOR(32, max, FALSE)
DEFINETEST_FIXED_OPERATOR(32, add, FALSE)
DEFINETEST_FIXED_OPERATOR(32, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(32, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(32, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, pow, FALSE)
DEFINETEST_FIXED_OPERATOR(32, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR(32, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(32, atan2, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(32, mul, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(32, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(32, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(32, pow, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(32, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(32, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(32, atan2, FALSE)

DEFINETEST_FIXED_OPERATOR(64, min, FALSE)
DEFINETEST_FIXED_OPERATOR(64, max, FALSE)
DEFINETEST_FIXED_OPERATOR(64, add, FALSE)
DEFINETEST_FIXED_OPERATOR(64, sub, FALSE)
DEFINETEST_FIXED_OPERATOR(64, mul, FALSE)
DEFINETEST_FIXED_OPERATOR(64, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, rem, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, pow, FALSE)
DEFINETEST_FIXED_OPERATOR(64, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR(64, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(64, atan2, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(64, mul, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(64, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(64, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(64, pow, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(64, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(64, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(64, atan2, FALSE)

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
DEFINETEST_FIXED_OPERATOR(128, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR(128, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR(128, atan2, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(128, mul, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(128, div, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(128, mod, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(128, pow, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(128, hypot, FALSE)
DEFINETEST_FIXED_OPERATOR_EXT(128, logn, ALLOW_SIGFPE)
DEFINETEST_FIXED_OPERATOR_EXT(128, atan2, FALSE)
#endif



/*============================================================================*\\
||                     Special cases: `rootn`, `isprime`                      ||
\\*============================================================================*/

// custom test for `rootn`, since its second argument is a `t_u8`
#define DEFINETEST_FIXED_ROOTN(BITS) \
void	print_test_q##BITS##rootn(char const* test_name, t_testflags flags, t_q##BITS expecting, t_q##BITS x, t_u8 n) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(q##BITS##rootn, x, n) \
	TEST_PRINT(q##BITS,	q##BITS##rootn, "x=" SF_Q##BITS ", n=%u", x, n) \
} \
void	test_q##BITS##rootn(void) \
{ \
	t_q##BITS const	values[] = { \
		(t_q##BITS){ 0 }, \
		(t_q##BITS){ +1 }, \
		(t_q##BITS){ +2 }, \
		(t_q##BITS){ -1 }, \
		(t_q##BITS){ -2 }, \
		(t_q##BITS){ 10 }, \
		QV(BITS, Q##BITS##_DENOM), \
		QV(BITS, Q##BITS##_DENOM * 2), \
		QV(BITS, Q##BITS##_DENOM * 5 / 2), \
		QV(BITS, -(Q##BITS##_DENOM * 2)), \
		QV(BITS, Q##BITS##_DENOM * 4), \
		Q##BITS##_MIN, \
		Q##BITS##_MAX, \
		Q##BITS##_ERROR, \
	}; \
	for (t_uint i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) \
	for (t_u8 n = 0; n <= 5; ++n) \
	{ \
		print_test_q##BITS##rootn("q"#BITS"rootn ",	FALSE, rootnq##BITS(values[i], n), values[i], n); \
	} \
} \

DEFINETEST_FIXED_ROOTN(8)
DEFINETEST_FIXED_ROOTN(16)
DEFINETEST_FIXED_ROOTN(32)
DEFINETEST_FIXED_ROOTN(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_ROOTN(128)
#endif

// custom test for `isprime`, since it returns a `t_bool`
#define DEFINETEST_FIXED_ISPRIME(BITS) \
void	print_test_q##BITS##isprime(char const* test_name, t_testflags flags, t_bool expecting, t_q##BITS x) \
{ \
	TEST_INIT(bool) \
	TEST_PERFORM(q##BITS##isprime, x) \
	TEST_PRINT(bool,	q##BITS##isprime, "x=" SF_Q##BITS, x) \
} \
void	test_q##BITS##isprime(void) \
{ \
	t_q##BITS const	values[] = { \
		(t_q##BITS){ 0 }, \
		(t_q##BITS){ +1 }, \
		(t_q##BITS){ +2 }, \
		(t_q##BITS){ -1 }, \
		(t_q##BITS){ 10 }, \
		QV(BITS, Q##BITS##_DENOM / 2), \
		QV(BITS, Q##BITS##_DENOM), \
		QV(BITS, Q##BITS##_DENOM * 2), \
		QV(BITS, Q##BITS##_DENOM * 3), \
		QV(BITS, -(Q##BITS##_DENOM * 3)), \
		QV(BITS, Q##BITS##_DENOM * 4), \
		QV(BITS, Q##BITS##_DENOM * 5), \
		QV(BITS, Q##BITS##_DENOM * 6), \
		QV(BITS, Q##BITS##_DENOM * 7), \
		Q##BITS##_MIN, \
		Q##BITS##_MAX, \
		Q##BITS##_ERROR, \
	}; \
	for (t_uint i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) \
	{ \
		print_test_q##BITS##isprime("q"#BITS"isprime ",	FALSE, isprimeq##BITS(values[i]), values[i]); \
	} \
} \

DEFINETEST_FIXED_ISPRIME(8)
DEFINETEST_FIXED_ISPRIME(16)
DEFINETEST_FIXED_ISPRIME(32)
DEFINETEST_FIXED_ISPRIME(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_ISPRIME(128)
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
	RUNTESTSUITE(rootn)
	RUNTESTSUITE(hypot)
	RUNTESTSUITE(exp)
	RUNTESTSUITE(exp2)
	RUNTESTSUITE(exp10)
	RUNTESTSUITE(ln)
	RUNTESTSUITE(log2)
	RUNTESTSUITE(log10)
	RUNTESTSUITE(logn)
	RUNTESTSUITE(sin)
	RUNTESTSUITE(cos)
	RUNTESTSUITE(tan)
	RUNTESTSUITE(asin)
	RUNTESTSUITE(acos)
	RUNTESTSUITE(atan)
	RUNTESTSUITE(atan2)
	RUNTESTSUITE(sinh)
	RUNTESTSUITE(cosh)
	RUNTESTSUITE(tanh)
	RUNTESTSUITE(asinh)
	RUNTESTSUITE(acosh)
	RUNTESTSUITE(atanh)
	RUNTESTSUITE(isprime)
	RUNTESTSUITE(mul_ext)
	RUNTESTSUITE(div_ext)
	RUNTESTSUITE(mod_ext)
	RUNTESTSUITE(pow_ext)
	RUNTESTSUITE(hypot_ext)
	RUNTESTSUITE(logn_ext)
	RUNTESTSUITE(atan2_ext)

	return (OK);
}
