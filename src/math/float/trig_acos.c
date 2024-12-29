
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcCos, acos)
#elif LIBCONFIG_USE_CCC_MATH
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#define DEFINEFUNC_FLOAT_ARCCOS(BITS) \
t_f##BITS	F##BITS##_ArcCos(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((F##BITS##_Abs(x) > 1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if (F##BITS##_Abs(x) == 1.) \
		return (INFINITY * SGN(x)); \
	t_f##BITS result = PI_HALF; \
	t_f##BITS power = x; \
	result += power * -1.;			power *= (x * x); \
	result += power * -0.0584;		power *= (x * x); \
	result += power * -0.6852;		power *= (x * x); \
	result += power * +1.16616;		power *= (x * x); \
	result += power * -0.9933563268; \
	return (result); \
} \

// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((-0.8047926 * x * x - 0.766) * x + PI_HALF); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCCOS(32)
DEFINEFUNC_FLOAT_ARCCOS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCCOS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCCOS(128)
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

/*! acos(x)
** Method :
**      acos(x)  = pi/2 - asin(x)
**      acos(-x) = pi/2 + asin(x)
** For |x|<=0.5
**      acos(x) = pi/2 - (x + x*x^2*R(x^2))     (see asin.c)
** For x>0.5
**      acos(x) = pi/2 - (pi/2 - 2asin(sqrt((1-x)/2)))
**              = 2asin(sqrt((1-x)/2))
**              = 2s + 2s*z*R(z)        ...z=(1-x)/2, s=sqrt(z)
**              = 2f + (2c + 2s*z*R(z))
**     where f=hi part of s, and c = (z-f*f)/(s+f) is the correction term
**     for f so that f+c ~ sqrt(z).
** For x<-0.5
**      acos(x) = pi - 2asin(sqrt((1-|x|)/2))
**              = pi - 0.5*(s+s*z*R(z)), where z=(1-|x|)/2,s=sqrt(z)
**
** Special cases:
**      if x is NaN, return x itself;
**      if |x|>1, return NaN with invalid signal.
**
** Function needed: sqrt
*/

t_f32	F32_ArcCos(t_f32 x)
{
	static const t_f32 pio2_hi = 1.5707962513e+00; /* 0x3fc90fda */
	static const t_f32 pio2_lo = 7.5497894159e-08; /* 0x33a22168 */
	t_f32 z,w,s,c,df;
	t_u32 hx,ix;

	GET_FLOAT_WORD(hx, x);
	ix = hx & 0x7fffffff;
	/* |x| >= 1 or nan */
	if (ix >= 0x3f800000)
	{
		if (ix == 0x3f800000)
		{
			if (hx >> 31)
				return 2*pio2_hi + 0x1p-120f;
			return 0;
		}
		return 0/(x-x);
	}
	/* |x| < 0.5 */
	if (ix < 0x3f000000)
	{
		if (ix <= 0x32800000) /* |x| < 2**-26 */
			return pio2_hi + 0x1p-120f;
		return pio2_hi - (x - (pio2_lo-x*__invtrig_polynomial_f32(x*x)));
	}
	/* x < -0.5 */
	if (hx >> 31)
	{
		z = (1+x)*0.5f;
		s = F32_Root2(z);
		w = __invtrig_polynomial_f32(z)*s-pio2_lo;
		return 2*(pio2_hi - (s+w));
	}
	/* x > 0.5 */
	z = (1-x)*0.5f;
	s = F32_Root2(z);
	GET_FLOAT_WORD(hx,s);
	SET_FLOAT_WORD(df,hx&0xfffff000);
	c = (z-df*df)/(s+df);
	w = __invtrig_polynomial_f32(z)*s+c;
	return 2*(df+w);
}

t_f64	F64_ArcCos(t_f64 x)
{
	static const t_f64 pio2_hi = 1.57079632679489655800e+00; /* 0x3FF921FB, 0x54442D18 */
	static const t_f64 pio2_lo = 6.12323399573676603587e-17; /* 0x3C91A626, 0x33145C07 */
	t_f64 z,w,s,c,df;
	t_u32 hx,ix;

	GET_HIGH_WORD(hx, x);
	ix = hx & 0x7fffffff;
	/* |x| >= 1 or nan */
	if (ix >= 0x3ff00000)
	{
		t_u32 lx;

		GET_LOW_WORD(lx,x);
		if (((ix - 0x3ff00000) | lx) == 0)
		{
			/* acos(1)=0, acos(-1)=pi */
			if (hx >> 31)
				return 2*pio2_hi + 0x1p-120f;
			return 0;
		}
		return 0/(x-x);
	}
	/* |x| < 0.5 */
	if (ix < 0x3fe00000)
	{
		if (ix <= 0x3c600000)  /* |x| < 2**-57 */
			return pio2_hi + 0x1p-120f;
		return pio2_hi - (x - (pio2_lo-x*__invtrig_polynomial_f64(x*x)));
	}
	/* x < -0.5 */
	if (hx >> 31)
	{
		z = (1.0+x)*0.5;
		s = F64_Root2(z);
		w = __invtrig_polynomial_f64(z)*s-pio2_lo;
		return 2*(pio2_hi - (s+w));
	}
	/* x > 0.5 */
	z = (1.0-x)*0.5;
	s = F64_Root2(z);
	df = s;
	SET_LOW_WORD(df,0);
	c = (z-df*df)/(s+df);
	w = __invtrig_polynomial_f64(z)*s+c;
	return 2*(df+w);
}

#define DEFINEFUNC_FLOAT_ARCCOS(BITS) \
t_f##BITS	F##BITS##_ArcCos(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	t_f##BITS z, s, c, f; \
	t_u16 e = u.i.se & 0x7fff; \
 \
	/* |x| >= 1 or nan */ \
	if (e >= 0x3fff) \
	{ \
		if (x == 1) \
			return 0; \
		if (x == -1) \
			return 2*pio2_hi + 0x1p-120f; \
		return 0/(x-x); \
	} \
	/* |x| < 0.5 */ \
	if (e < 0x3fff - 1) \
	{ \
		if (e < 0x3fff - LDBL_MANT_DIG - 1) \
			return pio2_hi + 0x1p-120f; \
		return pio2_hi - (__invtrig_polynomial_f##BITS(x*x)*x - pio2_lo + x); \
	} \
	/* x < -0.5 */ \
	if (u.i.se >> 15) \
	{ \
		z = (1 + x)*0.5; \
		s = F##BITS_Root2(z); \
		return 2*(pio2_hi - (__invtrig_polynomial_f##BITS(z)*s - pio2_lo + s)); \
	} \
	/* x > 0.5 */ \
	z = (1 - x)*0.5; \
	s = F##BITS_Root2(z); \
	u.f = s; \
	CLEARBOTTOM(u); \
	f = u.f; \
	c = (z - f*f)/(s + f); \
	return 2*(__invtrig_polynomial_f##BITS(z)*s + c + f); \
} \

#if LIBCONFIG_USE_FLOAT80
#define CLEARBOTTOM(u)	(u.i.m &= -1ULL << 32)
static const t_f80 pio2_hi = +1.57079632679489661926L;
static const t_f80 pio2_lo = -2.50827880633416601173e-20L;
DEFINEFUNC_FLOAT_ARCCOS(80)
#endif

#if LIBCONFIG_USE_FLOAT128
#define CLEARBOTTOM(u)	(u.i.lo = 0)
static const t_f128 pio2_hi = +1.57079632679489661923132169163975140L;
static const t_f128 pio2_lo = +4.33590506506189051239852201302167613e-35L;
DEFINEFUNC_FLOAT_ARCCOS(128)
#endif



#endif
