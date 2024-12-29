
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcTan, atan)
#elif LIBCONFIG_USE_CCC_MATH
// very fast sigmoid approximation
// score: 0.77	for [-5,+5]-> 200 tests
#define DEFINEFUNC_FLOAT_ARCTAN(BITS) \
t_f##BITS	F##BITS##_ArcTan(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	t_f##BITS n = 1.54 - abs_x / (0.9 + abs_x); \
	if (n < 0.65) \
		n = 0.65; \
	return ((PI_HALF * x) / (n + abs_x)); \
} \

// 3 different curves, some discontinuity
// score: 38.20	for [-5,+5]-> 200 tests
#if 0
	static const t_f##BITS result_1_0 = 0x1.921fb54442d18p-1;
	static const t_f##BITS result_2_5 = 0x1.30b6d796a4da7p0;
	t_f##BITS abs_x;
	t_f##BITS add = 0;

	abs_x = F##BITS##_Abs(x);
	if (abs_x == 1.0)	return (result_1_0);
	if (abs_x == 2.5)	return (result_2_5);
	else if (abs_x > 2.5)
		x *= 1.3;
	else if (abs_x > 1.0)
	{
		x *= 0.9;
		add = (0.05 * x);
	}
	else
	{
		x *= 0.57;
		add = (0.22 * x);
	}
	return ((PI_HALF * x) / (1. + abs_x) + add);
#endif

// crazy simple exp() approximation
// score: 60.59	for [-5, 5]-> 200 tests
#if 0
	return (3. / (1 + Float_Exp(-1.1 * x)) - 1.5);
#endif

DEFINEFUNC_FLOAT_ARCTAN(32)
DEFINEFUNC_FLOAT_ARCTAN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCTAN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCTAN(128)
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

/*! atan(x)
** Method
**   1. Reduce x to positive by atan(x) = -atan(-x).
**   2. According to the integer k=4t+0.25 chopped, t=x, the argument
**      is further reduced to one of the following intervals and the
**      arctangent of t is evaluated by the corresponding formula:
**
**      [0,7/16]      atan(x) = t-t^3*(a1+t^2*(a2+...(a10+t^2*a11)...)
**      [7/16,11/16]  atan(x) = atan(1/2) + atan( (t-0.5)/(1+t/2) )
**      [11/16.19/16] atan(x) = atan( 1 ) + atan( (t-1)/(1+t) )
**      [19/16,39/16] atan(x) = atan(3/2) + atan( (t-1.5)/(1+1.5t) )
**      [39/16,INF]   atan(x) = atan(INF) + atan( -1/t )
**
** Constants:
** The hexadecimal values are the intended ones for the following
** constants. The decimal values may be used, provided that the
** compiler will convert from decimal to binary accurately enough
** to produce the hexadecimal values shown.
*/

t_f32	F32_ArcTan(t_f32 x)
{
	static const t_f32 atanhi[] =
	{
		+4.6364760399e-01, /* atan(0.5)hi 0x3eed6338 */
		+7.8539812565e-01, /* atan(1.0)hi 0x3f490fda */
		+9.8279368877e-01, /* atan(1.5)hi 0x3f7b985e */
		+1.5707962513e+00, /* atan(inf)hi 0x3fc90fda */
	};
	static const t_f32 atanlo[] =
	{
		+5.0121582440e-09, /* atan(0.5)lo 0x31ac3769 */
		+3.7748947079e-08, /* atan(1.0)lo 0x33222168 */
		+3.4473217170e-08, /* atan(1.5)lo 0x33140fb4 */
		+7.5497894159e-08, /* atan(inf)lo 0x33a22168 */
	};
	static const t_f32 aT[] =
	{
		+3.3333328366e-01,
		-1.9999158382e-01,
		+1.4253635705e-01,
		-1.0648017377e-01,
		+6.1687607318e-02,
	};
	t_f32 w,s1,s2,z;
	t_u32 ix,sign;
	int id;

	GET_FLOAT_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix >= 0x4c800000)
	{	/* if |x| >= 2**26 */
		if (IS_NAN(x))
			return x;
		z = atanhi[3] + 0x1p-120f;
		return sign ? -z : z;
	}
	if (ix < 0x3ee00000)
	{	/* |x| < 0.4375 */
		if (ix < 0x39800000)
		{	/* |x| < 2**-12 */
			if (ix < 0x00800000)
				/* raise underflow for subnormal x */
				{}/*FORCE_EVAL(x*x);*/
			return x;
		}
		id = -1;
	}
	else
	{
		x = F32_Abs(x);
		if (ix < 0x3f980000)
		{	/* |x| < 1.1875 */
			if (ix < 0x3f300000)
			{	/*  7/16 <= |x| < 11/16 */
				id = 0;
				x = (2.0f*x - 1.0f)/(2.0f + x);
			}
			else
			{	/* 11/16 <= |x| < 19/16 */
				id = 1;
				x = (x - 1.0f)/(x + 1.0f);
			}
		}
		else
		{
			if (ix < 0x401c0000)
			{	/* |x| < 2.4375 */
				id = 2;
				x = (x - 1.5f)/(1.0f + 1.5f*x);
			}
			else
			{	/* 2.4375 <= |x| < 2**26 */
				id = 3;
				x = -1.0f/x;
			}
		}
	}
	/* end of argument reduction */
	z = x*x;
	w = z*z;
	/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
	s1 = z*(aT[0]+w*(aT[2]+w*aT[4]));
	s2 = w*(aT[1]+w*aT[3]);
	if (id < 0)
		return x - x*(s1+s2);
	z = atanhi[id] - ((x*(s1+s2) - atanlo[id]) - x);
	return sign ? -z : z;
}



t_f64	F64_ArcTan(t_f64 x)
{
	static const t_f64 atanhi[] =
	{
		+4.63647609000806093515e-01, /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
		+7.85398163397448278999e-01, /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
		+9.82793723247329054082e-01, /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
		+1.57079632679489655800e+00, /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
	};
	static const t_f64 atanlo[] =
	{
		+2.26987774529616870924e-17, /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
		+3.06161699786838301793e-17, /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
		+1.39033110312309984516e-17, /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
		+6.12323399573676603587e-17, /* atan(inf)lo 0x3C91A626, 0x33145C07 */
	};
	static const t_f64 aT[] =
	{
		+3.33333333333329318027e-01, /* 0x3FD55555, 0x5555550D */
		-1.99999999998764832476e-01, /* 0xBFC99999, 0x9998EBC4 */
		+1.42857142725034663711e-01, /* 0x3FC24924, 0x920083FF */
		-1.11111104054623557880e-01, /* 0xBFBC71C6, 0xFE231671 */
		+9.09088713343650656196e-02, /* 0x3FB745CD, 0xC54C206E */
		-7.69187620504482999495e-02, /* 0xBFB3B0F2, 0xAF749A6D */
		+6.66107313738753120669e-02, /* 0x3FB10D66, 0xA0D03D51 */
		-5.83357013379057348645e-02, /* 0xBFADDE2D, 0x52DEFD9A */
		+4.97687799461593236017e-02, /* 0x3FA97B4B, 0x24760DEB */
		-3.65315727442169155270e-02, /* 0xBFA2B444, 0x2C6A6C2F */
		+1.62858201153657823623e-02, /* 0x3F90AD3A, 0xE322DA11 */
	};
	t_f64 w,s1,s2,z;
	t_u32 ix,sign;
	int id;

	GET_HIGH_WORD(ix, x);
	sign = ix >> 31;
	ix &= 0x7fffffff;
	if (ix >= 0x44100000)
	{	/* if |x| >= 2^66 */
		if (IS_NAN(x))
			return x;
		z = atanhi[3] + 0x1p-120f;
		return sign ? -z : z;
	}
	if (ix < 0x3fdc0000)
	{	/* |x| < 0.4375 */
		if (ix < 0x3e400000)
		{	/* |x| < 2^-27 */
			if (ix < 0x00100000)
				/* raise underflow for subnormal x */
				{}/*FORCE_EVAL((t_f32)x);*/
			return x;
		}
		id = -1;
	}
	else
	{
		x = F64_Abs(x);
		if (ix < 0x3ff30000)
		{	/* |x| < 1.1875 */
			if (ix < 0x3fe60000)
			{	/*  7/16 <= |x| < 11/16 */
				id = 0;
				x = (2.0*x-1.0)/(2.0+x);
			}
			else
			{	/* 11/16 <= |x| < 19/16 */
				id = 1;
				x = (x-1.0)/(x+1.0);
			}
		}
		else
		{
			if (ix < 0x40038000)
			{	/* |x| < 2.4375 */
				id = 2;
				x = (x-1.5)/(1.0+1.5*x);
			}
			else
			{	/* 2.4375 <= |x| < 2^66 */
				id = 3;
				x = -1.0/x;
			}
		}
	}
	/* end of argument reduction */
	z = x*x;
	w = z*z;
	/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
	s1 = z*(aT[0]+w*(aT[2]+w*(aT[4]+w*(aT[6]+w*(aT[8]+w*aT[10])))));
	s2 = w*(aT[1]+w*(aT[3]+w*(aT[5]+w*(aT[7]+w*aT[9]))));
	if (id < 0)
		return x - x*(s1+s2);
	z = atanhi[id] - (x*(s1+s2) - atanlo[id] - x);
	return sign ? -z : z;
}

#define DEFINEFUNC_FLOAT_ARCTAN(BITS) \
t_f##BITS	F##BITS##_ArcTan(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	t_f##BITS w, s1, s2, z; \
	int id; \
	unsigned e = u.i.se & 0x7fff; \
	unsigned sign = u.i.se >> 15; \
	unsigned expman; \
 \
	if (e >= 0x3fff + LDBL_MANT_DIG + 1) \
	{	/* if |x| is large, atan(x)~=pi/2 */ \
		if (IS_NAN(x)) \
			return x; \
		return sign ? -atanhi[3] : atanhi[3]; \
	} \
	/* Extract the exponent and the first few bits of the mantissa. */ \
	expman = EXPMAN(u); \
	if (expman < ((0x3fff - 2) << 8) + 0xc0) \
	{	/* |x| < 0.4375 */ \
		if (e < 0x3fff - (LDBL_MANT_DIG+1)/2) \
		{	/* if |x| is small, atanl(x)~=x */ \
			/* raise underflow if subnormal */ \
			if (e == 0) \
				{}/*FORCE_EVAL((t_f32)x);*/ \
			return x; \
		} \
		id = -1; \
	} \
	else \
	{ \
		x = F##BITS##_Abs(x); \
		if (expman < (0x3fff << 8) + 0x30) \
		{	/* |x| < 1.1875 */ \
			if (expman < ((0x3fff - 1) << 8) + 0x60) \
			{	/*  7/16 <= |x| < 11/16 */ \
				id = 0; \
				x = (2.0*x-1.0)/(2.0+x); \
			} \
			else \
			{	/* 11/16 <= |x| < 19/16 */ \
				id = 1; \
				x = (x-1.0)/(x+1.0); \
			} \
		} \
		else \
		{ \
			if (expman < ((0x3fff + 1) << 8) + 0x38) \
			{	/* |x| < 2.4375 */ \
				id = 2; \
				x = (x-1.5)/(1.0+1.5*x); \
			} \
			else \
			{	/* 2.4375 <= |x| */ \
				id = 3; \
				x = -1.0/x; \
			} \
		} \
	} \
	/* end of argument reduction */ \
	z = x*x; \
	w = z*z; \
	/* break sum aT[i]z**(i+1) into odd and even poly */ \
	s1 = z*T_even(w); \
	s2 = w*T_odd(w); \
	if (id < 0) \
		return x - x*(s1+s2); \
	z = atanhi[id] - ((x*(s1+s2) - atanlo[id]) - x); \
	return sign ? -z : z; \
} \

#if LIBCONFIG_USE_FLOAT80
static const t_f80 atanhi[] =
{
	+4.63647609000806116202e-01L,
	+7.85398163397448309628e-01L,
	+9.82793723247329067960e-01L,
	+1.57079632679489661926e+00L,
};
static const t_f80 atanlo[] =
{
	+1.18469937025062860669e-20L,
	-1.25413940316708300586e-20L,
	+2.55232234165405176172e-20L,
	-2.50827880633416601173e-20L,
};
static const t_f80 aT[] =
{
	+3.33333333333333333017e-01L,
	-1.99999999999999632011e-01L,
	+1.42857142857046531280e-01L,
	-1.11111111100562372733e-01L,
	+9.09090902935647302252e-02L,
	-7.69230552476207730353e-02L,
	+6.66661718042406260546e-02L,
	-5.88158892835030888692e-02L,
	+5.25499891539726639379e-02L,
	-4.70119845393155721494e-02L,
	+4.03539201366454414072e-02L,
	-2.91303858419364158725e-02L,
	+1.24822046299269234080e-02L,
};
#define EXPMAN(u) ((u.i.se & 0x7fff)<<8 | (u.i.m>>55 & 0xff))

static
t_f80	T_even(t_f80 x)
{
	return aT[0] + x * (aT[2] + x * (aT[4] + x * (aT[6] + x * (aT[8] + x * (aT[10] + x * aT[12])))));
}
static
t_f80	T_odd(t_f80 x)
{
	return aT[1] + x * (aT[3] + x * (aT[5] + x * (aT[7] + x * (aT[9] + x * aT[11]))));
}
#endif

#if LIBCONFIG_USE_FLOAT128
static const t_f128 atanhi[] =
{
	+4.63647609000806116214256231461214397e-01L,
	+7.85398163397448309615660845819875699e-01L,
	+9.82793723247329067985710611014666038e-01L,
	+1.57079632679489661923132169163975140e+00L,
};
static const t_f128 atanlo[] =
{
	+4.89509642257333492668618435220297706e-36L,
	+2.16795253253094525619926100651083806e-35L,
	-2.31288434538183565909319952098066272e-35L,
	+4.33590506506189051239852201302167613e-35L,
};
static const t_f128 aT[] =
{
	+3.33333333333333333333333333333333125e-01L,
	-1.99999999999999999999999999999180430e-01L,
	+1.42857142857142857142857142125269827e-01L,
	-1.11111111111111111111110834490810169e-01L,
	+9.09090909090909090908522355708623681e-02L,
	-7.69230769230769230696553844935357021e-02L,
	+6.66666666666666660390096773046256096e-02L,
	-5.88235294117646671706582985209643694e-02L,
	+5.26315789473666478515847092020327506e-02L,
	-4.76190476189855517021024424991436144e-02L,
	+4.34782608678695085948531993458097026e-02L,
	-3.99999999632663469330634215991142368e-02L,
	+3.70370363987423702891250829918659723e-02L,
	-3.44827496515048090726669907612335954e-02L,
	+3.22579620681420149871973710852268528e-02L,
	-3.03020767654269261041647570626778067e-02L,
	+2.85641979882534783223403715930946138e-02L,
	-2.69824879726738568189929461383741323e-02L,
	+2.54194698498808542954187110873675769e-02L,
	-2.35083879708189059926183138130183215e-02L,
	+2.04832358998165364349957325067131428e-02L,
	-1.54489555488544397858507248612362957e-02L,
	+8.64492360989278761493037861575248038e-03L,
	-2.58521121597609872727919154569765469e-03L,
};
#define EXPMAN(u) ((u.i.se & 0x7fff)<<8 | u.i.top>>8)

static
t_f128 T_even(t_f128 x)
{
	return (aT[0] +
		x * (aT[2]  + x * (aT[4]  + x * (aT[6]  + x * (aT[8] +
		x * (aT[10] + x * (aT[12] + x * (aT[14] + x * (aT[16] +
		x * (aT[18] + x * (aT[20] + x * aT[22])))))))))));
}
static
t_f128 T_odd(t_f128 x)
{
	return (aT[1] +
		x * (aT[3]  + x * (aT[5]  + x * (aT[7]  + x * (aT[9] +
		x * (aT[11] + x * (aT[13] + x * (aT[15] + x * (aT[17] +
		x * (aT[19] + x * (aT[21] + x * aT[23])))))))))));
}
#endif



#endif
