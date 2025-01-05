
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Tan, tan)
#elif LIBCONFIG_USE_CCC_MATH

// trigonometric formula method
#define DEFINEFUNC_FLOAT_TAN(BITS) \
t_f##BITS	F##BITS##_Tan(t_f##BITS x) \
{ \
	t_f##BITS	cosine; \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	cosine = F##BITS##_Cos(x); \
	if CCCERROR((cosine == 0.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	return (F##BITS##_Sin(x) / cosine); \
} \

// fast polynomial approximation for [-1,+1] and 1/x approximation for the rest
// score: 0.23	for [-40,+40]=> 200 tests
#if 0
	t_f##BITS	a;
	t_s64		floor_a;

	if (x < -PI_HALF)
	{
		x = -x + PI_HALF;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x = PI - x;
		x -= PI_HALF;
	}
	else if (x > PI_HALF)
	{
		x += PI_HALF;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x -= PI_HALF;
	}
	if (x < -0.997592567)
		return (-1 / (x + PI_HALF) + 0.343 * x + 0.538);
	if (x > 0.997592567)
		return (-(1 / (x - PI_HALF) - 0.343 * x + 0.538));

	t_f##BITS result = x;
	t_f##BITS power = x * x * x;

	result += power * 0.33333333333;	power *= (x * x);
	result += power * 0.13333333333;	power *= (x * x);
	result += power * 0.09;
	return (result);
#endif

DEFINEFUNC_FLOAT_TAN(32)
DEFINEFUNC_FLOAT_TAN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TAN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TAN(128)
#endif



#else

/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
** Conversion to t_f32 by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
** Optimized by Bruce D. Evans.
*/

/*! tan(x)
** Return tangent function of x.
**
** kernel function:
**      __tan           ... tangent function on [-pi/4,pi/4]
**      __rem_pi2_f64   ... argument reduction routine
**
** Method.
**      Let S,C and T denote the sin, cos and tan respectively on
**      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
**      in [-pi/4 , +pi/4], and let n = k mod 4.
**      We have
**
**          n        sin(x)      cos(x)        tan(x)
**     ----------------------------------------------------------
**          0          S           C             T
**          1          C          -S            -1/T
**          2         -S          -C             T
**          3         -C           S            -1/T
**     ----------------------------------------------------------
**
** Special cases:
**      Let trig be any of sin, cos, or tan.
**      trig(+-INF)  is NaN, with signals;
**      trig(NaN)    is that NaN;
**
** Accuracy:
**      TRIG(x) returns trig(x) nearly rounded
*/

t_f32	F32_Tan(t_f32 x)
{
	/* Small multiples of pi/2 rounded to t_f64 precision. */
	static const t_f64 t1pio2 = 1*PI_HALF; /* 0x3FF921FB, 0x54442D18 */
	static const t_f64 t2pio2 = 2*PI_HALF; /* 0x400921FB, 0x54442D18 */
	static const t_f64 t3pio2 = 3*PI_HALF; /* 0x4012D97C, 0x7F3321D2 */
	static const t_f64 t4pio2 = 4*PI_HALF; /* 0x401921FB, 0x54442D18 */
	t_f64 y;
	t_u32 ix;
	unsigned n, sign;

	GET_FLOAT_WORD(ix, x);
	sign = ix >> 31;
	ix &= 0x7fffffff;

	if (ix <= 0x3f490fda)
	{  /* |x| ~<= pi/4 */
		if (ix < 0x39800000)
		{  /* |x| < 2**-12 */
			/* raise inexact if x!=0 and underflow if subnormal */
			/*FORCE_EVAL(ix < 0x00800000 ? x/0x1p120f : x+0x1p120f);*/
			return x;
		}
		return __tan_f32(x, 0);
	}
	if (ix <= 0x407b53d1)
	{  /* |x| ~<= 5*pi/4 */
		if (ix <= 0x4016cbe3)  /* |x| ~<= 3pi/4 */
			return __tan_f32((sign ? x+t1pio2 : x-t1pio2), 1);
		else
			return __tan_f32((sign ? x+t2pio2 : x-t2pio2), 0);
	}
	if (ix <= 0x40e231d5)
	{  /* |x| ~<= 9*pi/4 */
		if (ix <= 0x40afeddf)  /* |x| ~<= 7*pi/4 */
			return __tan_f32((sign ? x+t3pio2 : x-t3pio2), 1);
		else
			return __tan_f32((sign ? x+t4pio2 : x-t4pio2), 0);
	}

	/* tan(Inf or NaN) is NaN */
	if (ix >= 0x7f800000)
		return x - x;

	/* argument reduction */
	n = __rem_pi2_f32(x, &y);
	return __tan_f32(y, n&1);
}

t_f64	F64_Tan(t_f64 x)
{
	t_f64 y[2];
	t_u32 ix;
	unsigned n;

	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	/* |x| ~< pi/4 */
	if (ix <= 0x3fe921fb)
	{
		if (ix < 0x3e400000) /* |x| < 2**-27 */
		{
			/* raise inexact if x!=0 and underflow if subnormal */
			/*FORCE_EVAL(ix < 0x00100000 ? x/0x1p120f : x+0x1p120f);*/
			return x;
		}
		return __tan_f64(x, 0.0, 0);
	}

	/* tan(Inf or NaN) is NaN */
	if (ix >= 0x7ff00000)
		return x - x;

	/* argument reduction */
	n = __rem_pi2_f64(x, y);
	return __tan_f64(y[0], y[1], n&1);
}

#define DEFINEFUNC_FLOAT_TAN(BITS) \
t_f##BITS	F##BITS##_Tan(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	t_f##BITS y[2]; \
	unsigned n; \
 \
	u.i.se &= 0x7fff; \
	if (u.i.se == 0x7fff) \
		return x - x; \
	if (u.f < M_PI_4) \
	{ \
		if (u.i.se < 0x3fff - LDBL_MANT_DIG/2) \
		{ \
			/* raise inexact if x!=0 and underflow if subnormal */ \
			/*FORCE_EVAL(u.i.se == 0 ? x*0x1p-120f : x+0x1p120f);*/ \
			return x; \
		} \
		return __tan_f##BITS(x, 0, 0); \
	} \
	n = __rem_pi2_f##BITS(x, y); \
	return __tan_f##BITS(y[0], y[1], n&1); \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TAN(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TAN(128)
#endif

#endif
