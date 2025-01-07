
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(ArcTan2, atan2)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_ARCTAN2(BITS) \
t_f##BITS	F##BITS##_ArcTan2(t_f##BITS y, t_f##BITS x) \
{ \
	if CCCERROR((IS_NAN(x) || IS_NAN(y)), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	static const t_f##BITS pi_lo = 1.2246467991473531772E-16; \
	if (y == 0.0) \
		return ((x < 0 ? PI : 0) * SGN(x)); \
	if (x == 0.0) \
		return (PI_HALF * SGN(y)); \
	if (IS_INFINITY(x)) \
	{ \
		if (IS_INFINITY(y)) \
			return ((x < 0 ? 3 * PI_QUARTER : PI_QUARTER) * SGN(y)); \
		else \
			return ((x < 0 ? PI : 0) * SGN(y)); \
	} \
	if (IS_INFINITY(y)) \
		return (PI_HALF * SGN(y)); \
	if (x == 1.0) \
		return (F##BITS##_ArcTan(y)); \
	t_s32 exp_x = F##BITS##_GetExp2(x); \
	t_s32 exp_y = F##BITS##_GetExp2(y); \
	t_f##BITS result = F##BITS##_Abs(y / x); \
	if ((exp_y - exp_x) > 60)		/* |y / x| > +2^60 */ \
		result = PI_HALF + 0.5 * pi_lo; \
	else if ((exp_y - exp_x) < -60)	/* |y| / x < -2^60 */ \
		result = 0.0; \
	else \
		result = F##BITS##_ArcTan(result); \
	if (x < 0) \
		return ((PI - (result - pi_lo)) * SGN(y)); \
	else \
		return (y < 0 ? -result : result); \
} \

DEFINEFUNC_FLOAT_ARCTAN2(32)
DEFINEFUNC_FLOAT_ARCTAN2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCTAN2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCTAN2(128)
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

/*! atan2(y,x)
** Method :
**      1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
**      2. Reduce x to positive by (if x and y are unexceptional):
**              ARG (x+iy) = arctan(y/x)           ... if x > 0,
**              ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
**
** Special cases:
**
**      ATAN2((anything), NaN ) is NaN;
**      ATAN2(NAN , (anything) ) is NaN;
**      ATAN2(+-0, +(anything but NaN)) is +-0  ;
**      ATAN2(+-0, -(anything but NaN)) is +-pi ;
**      ATAN2(+-(anything but 0 and NaN), 0) is +-pi/2;
**      ATAN2(+-(anything but INF and NaN), +INF) is +-0 ;
**      ATAN2(+-(anything but INF and NaN), -INF) is +-pi;
**      ATAN2(+-INF,+INF ) is +-pi/4 ;
**      ATAN2(+-INF,-INF ) is +-3pi/4;
**      ATAN2(+-INF, (anything but,0,NaN, and INF)) is +-pi/2;
**
** Constants:
** The hexadecimal values are the intended ones for the following
** constants. The decimal values may be used, provided that the
** compiler will convert from decimal to binary accurately enough
** to produce the hexadecimal values shown.
*/



t_f32	F32_ArcTan2(t_f32 y, t_f32 x)
{
	static const t_f32
	pi     = +3.1415927410e+00, /* 0x40490fdb */
	pi_lo  = -8.7422776573e-08; /* 0xb3bbbd2e */
	t_f32 z;
	t_u32 m,ix,iy;

	if (IS_NAN(x) || IS_NAN(y))
		return x+y;
	GET_F32_WORD(ix, x);
	GET_F32_WORD(iy, y);
	if (ix == 0x3f800000)  /* x=1.0 */
		return F32_ArcTan(y);
	m = ((iy>>31)&1) | ((ix>>30)&2);  /* 2*sign(x)+sign(y) */
	ix &= 0x7fffffff;
	iy &= 0x7fffffff;

	/* when y = 0 */
	if (iy == 0)
	{
		switch (m)
		{
			case 0:
			case 1: return y;   /* atan(+-0,+anything)=+-0 */
			case 2: return  pi; /* atan(+0,-anything) = pi */
			case 3: return -pi; /* atan(-0,-anything) =-pi */
		}
	}
	/* when x = 0 */
	if (ix == 0)
		return m&1 ? -pi/2 : pi/2;
	/* when x is INF */
	if (ix == 0x7f800000)
	{
		if (iy == 0x7f800000)
		{
			switch (m)
			{
				case 0: return  pi/4; /* atan(+INF,+INF) */
				case 1: return -pi/4; /* atan(-INF,+INF) */
				case 2: return 3*pi/4;  /*atan(+INF,-INF)*/
				case 3: return -3*pi/4; /*atan(-INF,-INF)*/
			}
		}
		else
		{
			switch (m)
			{
				case 0: return  0.0f;    /* atan(+...,+INF) */
				case 1: return -0.0f;    /* atan(-...,+INF) */
				case 2: return  pi; /* atan(+...,-INF) */
				case 3: return -pi; /* atan(-...,-INF) */
			}
		}
	}
	/* |y/x| > 0x1p26 */
	if (ix+(26<<23) < iy || iy == 0x7f800000)
		return m&1 ? -pi/2 : pi/2;

	/* z = atan(|y/x|) with correct underflow */
	if ((m&2) && iy+(26<<23) < ix)  /*|y/x| < 0x1p-26, x < 0 */
		z = 0.0;
	else
		z = F32_ArcTan(F32_Abs(y/x));
	switch (m)
	{
		case 0: return z;              /* atan(+,+) */
		case 1: return -z;             /* atan(-,+) */
		case 2: return pi - (z-pi_lo); /* atan(+,-) */
		case 3: return (z-pi_lo) - pi; /* atan(-,-) */
		default:
			return NAN;
	}
}

t_f64	F64_ArcTan2(t_f64 y, t_f64 x)
{
	static const t_f64
	pi     = 3.1415926535897931160E+00, /* 0x400921FB, 0x54442D18 */
	pi_lo  = 1.2246467991473531772E-16; /* 0x3CA1A626, 0x33145C07 */
	t_f64 z;
	t_u32 m,lx,ly,ix,iy;

	if (IS_NAN(x) || IS_NAN(y))
		return x+y;
	GET_F64_WORDS(ix, lx, x);
	GET_F64_WORDS(iy, ly, y);
	if (((ix - 0x3ff00000) | lx) == 0)  /* x = 1.0 */
		return F64_ArcTan(y);
	m = ((iy>>31)&1) | ((ix>>30)&2);  /* 2*sign(x)+sign(y) */
	ix = ix & 0x7fffffff;
	iy = iy & 0x7fffffff;

	/* when y = 0 */
	if ((iy|ly) == 0)
	{
		switch(m)
		{
			case 0:
			case 1: return y;   /* atan(+-0,+anything)=+-0 */
			case 2: return  pi; /* atan(+0,-anything) = pi */
			case 3: return -pi; /* atan(-0,-anything) =-pi */
		}
	}
	/* when x = 0 */
	if ((ix|lx) == 0)
		return m&1 ? -pi/2 : pi/2;
	/* when x is INF */
	if (ix == 0x7ff00000)
	{
		if (iy == 0x7ff00000)
		{
			switch(m)
			{
				case 0: return  pi/4;   /* atan(+INF,+INF) */
				case 1: return -pi/4;   /* atan(-INF,+INF) */
				case 2: return  3*pi/4; /* atan(+INF,-INF) */
				case 3: return -3*pi/4; /* atan(-INF,-INF) */
			}
		}
		else
		{
			switch(m)
			{
				case 0: return  0.0; /* atan(+...,+INF) */
				case 1: return -0.0; /* atan(-...,+INF) */
				case 2: return  pi;  /* atan(+...,-INF) */
				case 3: return -pi;  /* atan(-...,-INF) */
			}
		}
	}
	/* |y/x| > 0x1p64 */
	if (ix+(64<<20) < iy || iy == 0x7ff00000)
		return m&1 ? -pi/2 : pi/2;

	/* z = atan(|y/x|) without spurious underflow */
	if ((m&2) && iy+(64<<20) < ix)  /* |y/x| < 0x1p-64, x<0 */
		z = 0;
	else
		z = F64_ArcTan(F64_Abs(y/x));
	switch (m)
	{
		case 0: return z;              /* atan(+,+) */
		case 1: return -z;             /* atan(-,+) */
		case 2: return pi - (z-pi_lo); /* atan(+,-) */
		case 3: return (z-pi_lo) - pi; /* atan(-,-) */
		default:
			return NAN;
	}
}

#define DEFINEFUNC_FLOAT_ARCTAN2(BITS) \
t_f##BITS	F##BITS##_ArcTan2(t_f##BITS y, t_f##BITS x) \
{ \
	union ldshape ux, uy; \
	t_f##BITS z; \
	int m, ex, ey; \
 \
	if (IS_NAN(x) || IS_NAN(y)) \
		return x+y; \
	if (x == 1) \
		return F##BITS##_ArcTan(y); \
	ux.f = x; \
	uy.f = y; \
	ex = ux.i.se & 0x7fff; \
	ey = uy.i.se & 0x7fff; \
	m = 2*(ux.i.se>>15) | uy.i.se>>15; \
	if (y == 0) \
	{ \
		switch(m) \
		{ \
			case 0: \
			case 1: return y;           /* atan(+-0,+anything)=+-0 */ \
			case 2: return  2*pio2_hi;  /* atan(+0,-anything) = pi */ \
			case 3: return -2*pio2_hi;  /* atan(-0,-anything) =-pi */ \
		} \
	} \
	if (x == 0) \
		return m&1 ? -pio2_hi : pio2_hi; \
	if (ex == 0x7fff) \
	{ \
		if (ey == 0x7fff) \
		{ \
			switch(m) \
			{ \
				case 0: return  pio2_hi/2;   /* atan(+INF,+INF) */ \
				case 1: return -pio2_hi/2;   /* atan(-INF,+INF) */ \
				case 2: return  1.5*pio2_hi; /* atan(+INF,-INF) */ \
				case 3: return -1.5*pio2_hi; /* atan(-INF,-INF) */ \
			} \
		} \
		else \
		{ \
			switch(m) \
			{ \
				case 0: return  0.0;        /* atan(+...,+INF) */ \
				case 1: return -0.0;        /* atan(-...,+INF) */ \
				case 2: return  2*pio2_hi;  /* atan(+...,-INF) */ \
				case 3: return -2*pio2_hi;  /* atan(-...,-INF) */ \
			} \
		} \
	} \
	if (ex+120 < ey || ey == 0x7fff) \
		return m&1 ? -pio2_hi : pio2_hi; \
	/* z = atan(|y/x|) without spurious underflow */ \
	if ((m&2) && ey+120 < ex)  /* |y/x| < 0x1p-120, x<0 */ \
		z = 0.0; \
	else \
		z = F##BITS##_ArcTan(F##BITS##_Abs(y/x)); \
	switch (m) \
	{ \
		case 0: return z;               /* atan(+,+) */ \
		case 1: return -z;              /* atan(-,+) */ \
		case 2: return 2*pio2_hi-(z-2*pio2_lo); /* atan(+,-) */ \
		case 3: return (z-2*pio2_lo)-2*pio2_hi; /* atan(-,-) */ \
		default: \
			return NAN; \
	} \
} \

#if LIBCONFIG_USE_FLOAT80
static const t_f80 pio2_hi = +1.57079632679489661926L;
static const t_f80 pio2_lo = -2.50827880633416601173e-20L;
DEFINEFUNC_FLOAT_ARCCOS(80)
#endif

#if LIBCONFIG_USE_FLOAT128
static const t_f128 pio2_hi = +1.57079632679489661923132169163975140L;
static const t_f128 pio2_lo = +4.33590506506189051239852201302167613e-35L;
DEFINEFUNC_FLOAT_ARCCOS(128)
#endif



#endif
