
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcSin, asin)
#elif LIBCONFIG_USE_CCC_MATH
// mixed approach: polynomial approximation + stepwise linear approx
#define DEFINEFUNC_FLOAT_ARCSIN(BITS) \
t_f##BITS	F##BITS##_ArcSin(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((x < -1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if CCCERROR((x > +1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	if (abs_x == 1.) \
		return (PI_HALF * SGN(x)); \
	t_f##BITS const correction = -0.0005; \
	t_f##BITS result = 0; \
	if (abs_x < 0.651609764) \
	{ \
		t_f##BITS power = x; \
		result += power * -1.0000000000;	power *= (x * x); \
		result += power * -0.0584000000;	power *= (x * x); \
		result += power * -0.6852000000;	power *= (x * x); \
		result += power * +1.1661600000;	power *= (x * x); \
		result += power * -0.9933563268; \
		return (-result); \
	} \
	if (abs_x < 0.92) \
	{ \
		t_f##BITS const term = abs_x - 0.85; \
		t_f##BITS power = term; \
		result = 1.0168; \
		result += power * 1.9164;	power *= term; \
		result += power * 2.7894;	power *= term; \
		result += power * 4.5131; \
	} \
	else if (abs_x < 0.9323076923076923)	result = (02.6537466126925790 * abs_x + -01.27336639846293750 + correction); \
	else if (abs_x < 0.9435897435897436)	result = (02.8866517417672997 * abs_x + -01.49050564187721560 + correction); \
	else if (abs_x < 0.9538461538461539)	result = (03.1672223729550377 * abs_x + -01.75524921181846600 + correction); \
	else if (abs_x < 0.9630769230769230)	result = (03.5114088569871450 * abs_x + -02.08355016581832200 + correction); \
	else if (abs_x < 0.9712820512820513)	result = (03.9432048093094780 * abs_x + -02.49940288297798400 + correction); \
	else if (abs_x < 0.9784615384615385)	result = (04.5004611357475275 * abs_x + -03.04065595081063300 + correction); \
	else if (abs_x < 0.9846153846153847)	result = (05.2466177344165230 * abs_x + -03.77074148427752660 + correction); \
	else if (abs_x < 0.9897435897435898)	result = (06.2968623133130330 * abs_x + -04.80482845426793800 + correction); \
	else if (abs_x < 0.9973333333333333)	result = (09.2624681237850730 * abs_x + -07.74001779488898100 + correction); \
	else if (abs_x < 0.9993333333333333)	result = (18.2645234110693050 * abs_x + -16.71806760140712500 + correction); \
	else if (abs_x < 0.9997777777777778)	result = (34.7279053082986500 * abs_x + -33.17047391070498000 + correction); \
	else if (abs_x < 1.0000000000000000)	result = (94.8700867138177800 * abs_x + -93.29929038702288000 + correction); \
	return (x < 0 ? -result : +result); \
} \

// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#if 0
	t_f##BITS result = 0;
	t_f##BITS power = x;
	result += power * -1.0000000000;	power *= (x * x);
	result += power * -0.0584000000;	power *= (x * x);
	result += power * -0.6852000000;	power *= (x * x);
	result += power * +1.1661600000;	power *= (x * x);
	result += power * -0.9933563268;
	return (-result);
#endif

// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((0.8047926 * x * x + 0.766) * x); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCSIN(32)
DEFINEFUNC_FLOAT_ARCSIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCSIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCSIN(128)
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
** Converted to t_f80 by David Schultz <das@FreeBSD.ORG>.
*/

/*! asin(x)
** Method :
**      Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
**      we approximate asin(x) on [0,0.5] by
**              asin(x) = x + x*x^2*R(x^2)
**      where
**              R(x^2) is a rational approximation of (asin(x)-x)/x^3
**      and its remez error is bounded by
**              |(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
**
**      For x in [0.5,1]
**              asin(x) = pi/2-2*asin(sqrt((1-x)/2))
**      Let y = (1-x), z = y/2, s := sqrt(z), and pio2_hi+pio2_lo=pi/2;
**      then for x>0.98
**              asin(x) = pi/2 - 2*(s+s*z*R(z))
**                      = pio2_hi - (2*(s+s*z*R(z)) - pio2_lo)
**      For x<=0.98, let pio4_hi = pio2_hi/2, then
**              f = hi part of s;
**              c = sqrt(z) - f = (z-f*f)/(s+f)         ...f+c=sqrt(z)
**      and
**              asin(x) = pi/2 - 2*(s+s*z*R(z))
**                      = pio4_hi+(pio4-2s)-(2s*z*R(z)-pio2_lo)
**                      = pio4_hi+(pio4-2f)-(2s*z*R(z)-(pio2_lo+2c))
**
** Special cases:
**      if x is NaN, return x itself;
**      if |x|>1, return NaN with invalid signal.
*/

t_f32	F32_ArcSin(t_f32 x)
{
	static const t_f64 pio2 = 1.570796326794896558e+00;
	t_f64 s;
	t_f32 z;
	t_u32 hx,ix;

	GET_FLOAT_WORD(hx, x);
	ix = hx & 0x7fffffff;
	if (ix >= 0x3f800000)
	{  /* |x| >= 1 */
		if (ix == 0x3f800000)  /* |x| == 1 */
			return x*pio2 + 0x1p-120f;  /* asin(+-1) = +-pi/2 with inexact */
		return 0/(x-x);  /* asin(|x|>1) is NaN */
	}
	if (ix < 0x3f000000)
	{  /* |x| < 0.5 */
		/* if 0x1p-126 <= |x| < 0x1p-12, avoid raising underflow */
		if (ix < 0x39800000 && ix >= 0x00800000)
			return x;
		return x + x*__invtrig_polynomial_f32(x*x);
	}
	/* 1 > |x| >= 0.5 */
	z = (1 - F32_Abs(x))*0.5f;
	s = F64_Root2(z);
	x = pio2 - 2*(s+s*__invtrig_polynomial_f32(z));
	if (hx >> 31)
		return -x;
	return x;
}

t_f64	F64_ArcSin(t_f64 x)
{
	static const t_f64 pio2_hi = 1.57079632679489655800e+00; /* 0x3FF921FB, 0x54442D18 */
	static const t_f64 pio2_lo = 6.12323399573676603587e-17; /* 0x3C91A626, 0x33145C07 */
	t_f64 z,r,s;
	t_u32 hx,ix;

	GET_HIGH_WORD(hx, x);
	ix = hx & 0x7fffffff;
	/* |x| >= 1 or nan */
	if (ix >= 0x3ff00000)
	{
		t_u32 lx;
		GET_LOW_WORD(lx, x);
		if (((ix - 0x3ff00000) | lx) == 0)
			/* asin(1) = +-pi/2 with inexact */
			return x*pio2_hi + 0x1p-120f;
		return 0/(x-x);
	}
	/* |x| < 0.5 */
	if (ix < 0x3fe00000)
	{
		/* if 0x1p-1022 <= |x| < 0x1p-26, avoid raising underflow */
		if (ix < 0x3e500000 && ix >= 0x00100000)
			return x;
		return x + x*__invtrig_polynomial_f64(x*x);
	}
	/* 1 > |x| >= 0.5 */
	z = (1 - F64_Abs(x))*0.5;
	s = F64_Root2(z);
	r = __invtrig_polynomial_f64(z);
	if (ix >= 0x3fef3333)
	{  /* if |x| > 0.975 */
		x = pio2_hi-(2*(s+s*r)-pio2_lo);
	}
	else
	{
		t_f64 f,c;
		/* f+c = sqrt(z) */
		f = s;
		SET_LOW_WORD(f,0);
		c = (z-f*f)/(s+f);
		x = 0.5*pio2_hi - (2*s*r - (pio2_lo-2*c) - (0.5*pio2_hi-2*f));
	}
	if (hx >> 31)
		return -x;
	return x;
}

#define DEFINEFUNC_FLOAT_ARCSIN(BITS) \
t_f##BITS	F##BITS##_ArcSin(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	t_f##BITS z, r, s; \
	t_u16 e = u.i.se & 0x7fff; \
	int sign = u.i.se >> 15; \
 \
	if (e >= 0x3fff) \
	{   /* |x| >= 1 or nan */ \
		/* asin(+-1)=+-pi/2 with inexact */ \
		if (x == 1 || x == -1) \
			return x*pio2_hi + 0x1p-120f; \
		return 0/(x-x); \
	} \
	if (e < 0x3fff - 1) \
	{  /* |x| < 0.5 */ \
		if (e < 0x3fff - (LDBL_MANT_DIG+1)/2) \
		{ \
			/* return x with inexact if x!=0 */ \
			FORCE_EVAL(x + 0x1p120f); \
			return x; \
		} \
		return x + x*__invtrig_polynomial_f##BITS(x*x); \
	} \
	/* 1 > |x| >= 0.5 */ \
	z = (1.0 - F##BITS##_Abs(x))*0.5; \
	s = F##BITS##_Root2(z); \
	r = __invtrig_polynomial_f##BITS(z); \
	if (CLOSETO1(u)) \
	{ \
		x = pio2_hi - (2*(s+s*r)-pio2_lo); \
	} \
	else \
	{ \
		t_f##BITS f, c; \
		u.f = s; \
		CLEARBOTTOM(u); \
		f = u.f; \
		c = (z - f*f)/(s + f); \
		x = 0.5*pio2_hi-(2*s*r - (pio2_lo-2*c) - (0.5*pio2_hi-2*f)); \
	} \
	return sign ? -x : x; \
} \

#if LIBCONFIG_USE_FLOAT8
#define CLOSETO1(u)	(u.i.m>>56 >= 0xf7)
#define CLEARBOTTOM(u)	(u.i.m &= -1ULL << 32)
static const t_f80 pio2_hi = +1.57079632679489661926L;
static const t_f80 pio2_lo = -2.50827880633416601173e-20L;
DEFINEFUNC_FLOAT_ARCSIN(80)
#endif

#if LIBCONFIG_USE_FLOAT128
#define CLOSETO1(u)	(u.i.top >= 0xee00)
#define CLEARBOTTOM(u)	(u.i.lo = 0)
static const t_f128 pio2_hi = +1.57079632679489661923132169163975140L;
static const t_f128 pio2_lo = +4.33590506506189051239852201302167613e-35L;
DEFINEFUNC_FLOAT_ARCSIN(128)
#endif



#endif
