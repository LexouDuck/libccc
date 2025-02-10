
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH

#elif LIBCONFIG_USE_CCC_MATH

t_float	__inv_factorial(t_uint n)
{
	static const t_float	result[16] =
	{
		1.,
		1.,
		1. / 2,
		1. / 6,
		1. / 24,
		1. / 120,
		1. / 720,
		1. / 5040,
		1. / 40320,
		1. / 362880,
		1. / 3628800,
		1. / 39916800,
		1. / 479001600,
		1. / 6227020800,
		1. / 87178291200,
		1. / 1307674368000,
	};
	return (result[n]); //static so it shouldn't be called with any weird values
//	return (n >= 16) ? 0. : result[n];
}

#else

/*
** ============================================================================
** Copyright (c) 1993 by Sun Microsystems, Inc. All rights reserved.
** Copyright (c) 2008 Steven G. Kargl, David Schultz, Bruce D. Evans.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this software
** is freely granted, provided that this notice is preserved.
** ============================================================================
*/



/*! __sin( x, y, iy)
**	kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
**	Input x is assumed to be bounded by ~pi/4 in magnitude.
**	Input y is the tail of x.
**	Input iy indicates whether y is 0. (if iy=0, y assume to be 0).
**
**	Algorithm
**		1. Since sin(-x) = -sin(x), we need only to consider positive x.
**		2. Callers must return sin(-0) = -0 without calling here since our
**			odd polynomial is not evaluated in a way that preserves -0.
**			Callers may do the optimization sin(x) ~ x for tiny x.
**		3. sin(x) is approximated by a polynomial of degree 13 on [0,pi/4]
**			sin(x) ~ x + S1*x^3 + ... + S6*x^13
**			where
**
**		|sin(x)         2     4     6     8     10     12  |     -58
**		|----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
**		|  x                                               |
**
**		4. sin(x+y) = sin(x) + sin'(x')*y
**					~ sin(x) + (1-x*x/2)*y
**			For better accuracy, let
**				polynomial = x^3*(S2+x^2*(S3+x^2*(S4+x^2*(S5+x^2*S6))))
**			then
**				sin(x) = x + (S1*x^3+ (x^2*(polynomial-y/2)+y))
*/

/* |sin(x)/x - s(x)| < 2**-37.5 (~[-4.89e-12, 4.824e-12]). */

#if LIBCONFIG_USE_FLOAT16
t_f16	__sin_f16(t_f64 x)
{
	return (t_f16)__sin_f32(x);
}
#endif

t_f32	__sin_f32(t_f64 x)
{
	static const t_f64 S1 = -0x15555554CBAC77.0p-55; /* -0.166666666416265235595 */
	static const t_f64 S2 = +0x111110896EFBB2.0p-59; /* +0.0083333293858894631756 */
	static const t_f64 S3 = -0x1A00F9E2CAE774.0p-65; /* -0.000198393348360966317347 */
	static const t_f64 S4 = +0x16CD878C3B46A7.0p-71; /* +0.0000027183114939898219064 */
	t_f64 x2 = x * x;
	t_f64 x4 = x2 * x2;
	t_f64 polynomial = S3 + x2*S4;
	t_f64 x3 = x2 * x;
	return ((x + x3*(S1 + x2*S2)) + x3*x4*polynomial);
}

t_f64	__sin_f64(t_f64 x, t_f64 y, int iy)
{
	static const t_f64 S1 = -1.66666666666666324348e-01; /* 0xBFC55555, 0x55555549 */
	static const t_f64 S2 = +8.33333333332248946124e-03; /* 0x3F811111, 0x1110F8A6 */
	static const t_f64 S3 = -1.98412698298579493134e-04; /* 0xBF2A01A0, 0x19C161D5 */
	static const t_f64 S4 = +2.75573137070700676789e-06; /* 0x3EC71DE3, 0x57B1FE7D */
	static const t_f64 S5 = -2.50507602534068634195e-08; /* 0xBE5AE5E6, 0x8A2B9CEB */
	static const t_f64 S6 = +1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */
	t_f64 x2 = x * x;
	t_f64 x4 = x2 * x2;
	t_f64 polynomial = S2 + x2*(S3 + x2*S4) + x2*x4*(S5 + x2*S6);
	t_f64 x3 = x2 * x;
	if (iy == 0)
		return (x + x3*(S1 + x2*polynomial));
	return (x - ((x2*(0.5*y - x3*polynomial) - y) - x3*S1));
}

#if LIBCONFIG_USE_FLOAT80
/*! ld80 version of __sin.c.  See __sin.c for most comments. */
/*
** Domain [-0.7854, 0.7854], range ~[-1.89e-22, 1.915e-22]
** |sin(x)/x - s(x)| < 2**-72.1
**
** See __cosl.c for more details about the polynomial.
*/
t_f80	__sin_f80(t_f80 x, t_f80 y, int iy)
{
	static const t_f80 S1 = -0.166666666666666666671L;  /* -0xaaaaaaaaaaaaaaab.0p-66 */
	static const t_f64 S2 = +0.83333333333333332e-2; /*  0x11111111111111.0p-59 */
	static const t_f64 S3 = -0.19841269841269427e-3; /* -0x1a01a01a019f81.0p-65 */
	static const t_f64 S4 = +0.27557319223597490e-5; /*  0x171de3a55560f7.0p-71 */
	static const t_f64 S5 = -0.25052108218074604e-7; /* -0x1ae64564f16cad.0p-78 */
	static const t_f64 S6 = +1.6059006598854211e-10; /*  0x161242b90243b5.0p-85 */
	static const t_f64 S7 = -7.6429779983024564e-13; /* -0x1ae42ebd1b2e00.0p-93 */
	static const t_f64 S8 = +2.6174587166648325e-15; /*  0x179372ea0b3f64.0p-101 */
	t_f80 x2 = x * x;
	t_f80 x3 = x2 * x;
	t_f80 polynomial = (S2+x2*(S3+x2*(S4+x2*(S5+x2*(S6+x2*(S7+x2*S8))))));
	if (iy == 0)
		return (x+x3*(S1+x2*polynomial));
	return (x - ((x2*(0.5*y-x3*polynomial)-y)-x3*S1));
}
#endif

#if LIBCONFIG_USE_FLOAT128
/*! ld128 version of __sin.c.  See __sin.c for most comments. */
/*
** Domain [-0.7854, 0.7854], range ~[-1.53e-37, 1.659e-37]
** |sin(x)/x - s(x)| < 2**-122.1
**
** See __cosl.c for more details about the polynomial.
*/
t_f128	__sin_f128(t_f128 x, t_f128 y, int iy)
{
	static const t_f128 S1  = -0.16666666666666666666666666666666666606732416116558e0L;
	static const t_f128 S2  = +0.83333333333333333333333333333331135404851288270047e-02L;
	static const t_f128 S3  = -0.19841269841269841269841269839935785325638310428717e-03L;
	static const t_f128 S4  = +0.27557319223985890652557316053039946268333231205686e-05L;
	static const t_f128 S5  = -0.25052108385441718775048214826384312253862930064745e-07L;
	static const t_f128 S6  = +0.16059043836821614596571832194524392581082444805729e-09L;
	static const t_f128 S7  = -0.76471637318198151807063387954939213287488216303768e-12L;
	static const t_f128 S8  = +0.28114572543451292625024967174638477283187397621303e-14L;
	static const t_f64  S9  = -0.82206352458348947812512122163446202498005154296863e-17;
	static const t_f64  S10 = +0.19572940011906109418080609928334380560135358385256e-19;
	static const t_f64  S11 = -0.38680813379701966970673724299207480965452616911420e-22;
	static const t_f64  S12 = +0.64038150078671872796678569586315881020659912139412e-25;
	t_f128 x2 = x * x;
	t_f128 x3 = x2 * x;
	t_f128 polynomial = (S2+x2*(S3+x2*(S4+x2*(S5+x2*(S6+x2*(S7+x2*(S8+x2*(S9+x2*(S10+x2*(S11+x2*S12))))))))));
	if (iy == 0)
		return (x+x3*(S1+x2*polynomial));
	return x-((x2*(0.5*y-x3*polynomial)-y)-x3*S1);
}
#endif

/*! __cos(x, y)
**	kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
**	Input x is assumed to be bounded by ~pi/4 in magnitude.
**	Input y is the tail of x.
**
**	Algorithm
**		1. Since cos(-x) = cos(x), we need only to consider positive x.
**		2. if x < 2^-27 (hx<0x3E400000 0), return 1 with inexact if x!=0.
**		3. cos(x) is approximated by a polynomial of degree 14 on [0,pi/4]
**			cos(x) ~ 1 - x*x/2 + C1*x^4+ ... + C6*x^14
**			where the remez error is
**			cos(x)-(1-.5*x^2+C1*x^4+C2*x^6+C3*x^8+C4*x^10+C5*x^12+C6*x^14)| <= 2
**
**		4. let r = C1*x^4+C2*x^6+C3*x^8+C4*x^10+C5*x^12+C6*x^14, then
**				cos(x) ~ 1 - x*x/2 + r
**			since
**				cos(x+y) ≈ cos(x) - sin(x)*y ≈ cos(x) - x*y,
**			a correction term is necessary in cos(x) and hence
**				cos(x+y) = 1 - (x*x/2 - (r - x*y))
**			For better accuracy, rearrange to
**				cos(x+y) ~ w + (tmp + (r-x*y))
**			where w = 1 - x*x/2 and tmp is a tiny correction term
**			(1 - x*x/2 == w + tmp exactly in infinite precision).
**			The exactness of w + tmp in infinite precision depends on w
**			and tmp having the same precision as x.  If they have extra
**			precision due to compiler bugs, then the extra precision is
**			only good provided it is retained in all terms of the final
**			expression for cos().  Retention happens in all cases tested
**			under FreeBSD, so don't pessimize things by forcibly clipping
**			any extra precision in w.
*/

/* |cos(x) - c(x)| < 2**-34.1 (~[-5.37e-11, 5.295e-11]). */

#if LIBCONFIG_USE_FLOAT16
t_f16	__cos_f16(t_f64 x)
{
	return (t_f16)__cos_f32(x);
}
#endif

t_f32	__cos_f32(t_f64 x)
{
	static const t_f64 C1 = -0x1FFFFFFD0C5E81.0p-54; /* -0.499999997251031003120 */
	static const t_f64 C2 = +0x155553E1053A42.0p-57; /* +0.0416666233237390631894 */
	static const t_f64 C3 = -0x16C087E80F1E27.0p-62; /* -0.00138867637746099294692 */
	static const t_f64 C4 = +0x199342E0EE5069.0p-68; /* +0.0000243904487962774090654 */
	t_f64 x2 = x * x;
	t_f64 x4 = x2 * x2;
	t_f64 polynomial = C3 + x2 * C4;
	return (((1. + x2 * C1) + x4 * C2) + (x4 * x2) * polynomial);
}

t_f64	__cos_f64(t_f64 x, t_f64 y)
{
	static const t_f64 C1 = +4.16666666666666019037e-02; /* 0x3FA55555, 0x5555554C */
	static const t_f64 C2 = -1.38888888888741095749e-03; /* 0xBF56C16C, 0x16C15177 */
	static const t_f64 C3 = +2.48015872894767294178e-05; /* 0x3EFA01A0, 0x19CB1590 */
	static const t_f64 C4 = -2.75573143513906633035e-07; /* 0xBE927E4F, 0x809C52AD */
	static const t_f64 C5 = +2.08757232129817482790e-09; /* 0x3E21EE9E, 0xBDB4B1C4 */
	static const t_f64 C6 = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */
	t_f64 x2 = x * x;
	t_f64 polynomial = (x2*(C1+x2*(C2+x2*(C3+x2*(C4+x2*(C5+x2*C6))))));
	t_f64 hx2 = 0.5 * x2;
	t_f64 mhx2 = 1. - hx2;
	return (mhx2 + (((1. - mhx2) - hx2) + (x2 * polynomial - x * y)));
}

#if LIBCONFIG_USE_FLOAT80
/*! ld80 version of __cos.c.  See __cos.c for most comments. */
/*
**	Domain [-0.7854, 0.7854]
**	range ~[-2.43e-23, 2.425e-23]:
**		|cos(x) - c(x)| < 2**-75.1
**
**		The coefficients of c(x) were generated by a pari-gp script using
**		a Remez algorithm that searches for the best higher coefficients
**		after rounding leading coefficients to a specified precision.
**
**		Simpler methods like Chebyshev or basic Remez barely suffice for
**		cos() in 64-bit precision, because we want the coefficient of x^2
**		to be precisely -0.5 so that multiplying by it is exact, and plain
**		rounding of the coefficients of a good polynomial approximation only
**		gives this up to about 64-bit precision.  Plain rounding also gives
**		a mediocre approximation for the coefficient of x^4, but a rounding
**		error of 0.5 ulps for this coefficient would only contribute ~0.01
**		ulps to the final error, so this is unimportant.
**		Rounding errors in higher coefficients are even less important.
**
**		In fact, coefficients above the x^4 one only need to have 53-bit
**		precision, and this is more efficient.  We get this optimization
**		almost for free from the complications needed to search for the best
**		higher coefficients.
*/
t_f80	__cos_f80(t_f80 x, t_f80 y)
{
	static const t_f80 C1 = +0.416666666666666666136e-1L; /* +0xAAAAAAAAAAAAAA9B.0p-68 */
	static const t_f64 C2 = -0.13888888888888874e-2; /* -0x16C16C16C16C10.0p-62 */
	static const t_f64 C3 = +0.24801587301571716e-4; /* +0x1A01A01A018E22.0p-68 */
	static const t_f64 C4 = -0.27557319215507120e-6; /* -0x127E4FB7602F22.0p-74 */
	static const t_f64 C5 = +0.20876754400407278e-8; /* +0x11EED8CAAECCF1.0p-81 */
	static const t_f64 C6 = -1.1470297442401303e-11; /* -0x19393412BD1529.0p-89 */
	static const t_f64 C7 = +4.7383039476436467e-14; /* +0x1AAC9D9AF5C43E.0p-97 */
	t_f80 x2 = x * x;
	t_f80 polynomial = (x2*(C1+x2*(C2+x2*(C3+x2*(C4+x2*(C5+x2*(C6+x2*C7)))))));
	t_f80 hx2 = 0.5 * x2;
	t_f80 mhx2 = 1. - hx2;
	return mhx2 + (((1. - mhx2) - hx2) + (x2 * polynomial - x * y));
}
#endif

#if LIBCONFIG_USE_FLOAT128
/*! ld128 version of __cos.c.  See __cos.c for most comments. */
/*
**	Domain [-0.7854, 0.7854]
**	range ~[-1.80e-37, 1.79e-37]:
**		|cos(x) - c(x))| < 2**-122.0
**
**		113-bit precision requires more care than 64-bit precision, since
**		simple methods give a minimax polynomial with coefficient for x^2
**		that is 1 ulp below 0.5, but we want it to be precisely 0.5.
**		See above for more details.
*/
t_f128	__cos_f128(t_f128 x, t_f128 y)
{
	static const t_f128 C1  = +0.4166666666666666666666666666666658424671e-01L;
	static const t_f128 C2  = -0.1388888888888888888888888888863490893732e-02L;
	static const t_f128 C3  = +0.2480158730158730158730158600795304914210e-04L;
	static const t_f128 C4  = -0.2755731922398589065255474947078934284324e-06L;
	static const t_f128 C5  = +0.2087675698786809897659225313136400793948e-08L;
	static const t_f128 C6  = -0.1147074559772972315817149986812031204775e-10L;
	static const t_f128 C7  = +0.4779477332386808976875457937252120293400e-13L;
	static const t_f64  C8  = -0.1561920696721507929516718307820958119868e-15;
	static const t_f64  C9  = +0.4110317413744594971475941557607804508039e-18;
	static const t_f64  C10 = -0.8896592467191938803288521958313920156409e-21;
	static const t_f64  C11 = +0.1601061435794535138244346256065192782581e-23;
	t_f128 x2 = x * x;
	t_f128 polynomial = (x2*(C1+x2*(C2+x2*(C3+x2*(C4+x2*(C5+x2*(C6+x2*(C7+x2*(C8+x2*(C9+x2*(C10+x2*C11)))))))))));
	t_f128 hx2 = 0.5 * x2;
	t_f128 mhx2 = 1. - hx2;
	return mhx2 + (((1. - mhx2) - hx2) + (x2 * polynomial - x * y));
}
#endif



/*
** ====================================================
** Copyright 2004 Sun Microsystems, Inc.  All Rights Reserved.
** Copyright (c) 2008 Steven G. Kargl, David Schultz, Bruce D. Evans.
**
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/

/*! __tan( x, y, k )
** kernel tan function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
** Input x is assumed to be bounded by ~pi/4 in magnitude.
** Input y is the tail of x.
** Input odd indicates whether tan (if odd = 0) or -1/tan (if odd = 1) is returned.
**
** Algorithm
**      1. Since tan(-x) = -tan(x), we need only to consider positive x.
**      2. Callers must return tan(-0) = -0 without calling here since our
**         odd polynomial is not evaluated in a way that preserves -0.
**         Callers may do the optimization tan(x) ~ x for tiny x.
**      3. tan(x) is approximated by a odd polynomial of degree 27 on
**         [0,0.67434]
**                               3             27
**              tan(x) ~ x + T1*x + ... + T13*x
**         where
**
**              |tan(x)         2     4            26   |     -59.2
**              |----- - (1+T1*x +T2*x +.... +T13*x    )| <= 2
**              |  x                                    |
**
**         Note: tan(x+y) = tan(x) + tan'(x)*y
**                        ~ tan(x) + (1+x*x)*y
**         Therefore, for better accuracy in computing tan(x+y), let
**                   3      2      2       2       2
**              r = x *(T2+x *(T3+x *(...+x *(T12+x *T13))))
**         then
**                                  3    2
**              tan(x+y) = x + (T1*x + (x *(r+y)+y))
**
**      4. For x in [0.67434,pi/4],  let y = pi/4 - x, then
**              tan(x) = tan(pi/4-y) = (1-tan(y))/(1+tan(y))
**                     = 1 - 2*(tan(y) - (tan(y)^2)/(1+tan(y)))
*/

#if LIBCONFIG_USE_FLOAT16
t_f16	__tan_f16(t_f64 x)
{
	return (t_f16)__tan_f32(x);
}
#endif

t_f32	__tan_f32(t_f64 x, t_bool odd)
{
	/* |tan(x)/x - t(x)| < 2**-25.5 (~[-2e-08, 2e-08]). */
	static const t_f64 polynomial[] =
	{
		+0x15554D3418C99F.0p-54, /* 0.333331395030791399758 */
		+0x1112FD38999F72.0p-55, /* 0.133392002712976742718 */
		+0x1B54C91D865AFE.0p-57, /* 0.0533812378445670393523 */
		+0x191DF3908C33CE.0p-58, /* 0.0245283181166547278873 */
		+0x185DADFCECF44E.0p-61, /* 0.00297435743359967304927 */
		+0x1362B9BF971BCD.0p-59, /* 0.00946564784943673166728 */
	};
	t_f64 z,r,w,s,t,u;
	/*
	Split up the polynomial into small independent terms to give opportunities for parallel evaluation.
	The chosen splitting is micro-optimized for Athlons (XP, X64).
	It costs 2 multiplications relative to Horner's method on sequential machines.
	
	We add the small terms from lowest degree up for efficiency on non-sequential machines
	(the lowest degree terms tend to be ready earlier).
	Apart from this, we don't care about order of operations,
	and don't need to to care since we have precision to spare.
	However, the chosen splitting is good for accuracy too,
	and would give results as accurate as Horner's method if
	the small terms were added from highest degree down.
	*/
	z = x*x;
	r = polynomial[4] + z*polynomial[5];
	t = polynomial[2] + z*polynomial[3];
	w = z*z;
	s = z*x;
	u = polynomial[0] + z*polynomial[1];
	r = (x + s*u) + (s*w)*(t + w*r);
	return odd ? -1.0/r : r;
}

t_f64	__tan_f64(t_f64 x, t_f64 y, t_bool odd)
{
	static const t_f64 pio4 = 7.85398163397448278999e-01; /* 3FE921FB, 54442D18 */
	static const t_f64 pio4lo = 3.06161699786838301793e-17; /* 3C81A626, 33145C07 */
	static const t_f64 polynomial[] =
	{
		+3.33333333333334091986e-01, /* 3FD55555, 55555563 */
		+1.33333333333201242699e-01, /* 3FC11111, 1110FE7A */
		+5.39682539762260521377e-02, /* 3FABA1BA, 1BB341FE */
		+2.18694882948595424599e-02, /* 3F9664F4, 8406D637 */
		+8.86323982359930005737e-03, /* 3F8226E3, E96E8493 */
		+3.59207910759131235356e-03, /* 3F6D6D22, C9560328 */
		+1.45620945432529025516e-03, /* 3F57DBC8, FEE08315 */
		+5.88041240820264096874e-04, /* 3F4344D8, F2F26501 */
		+2.46463134818469906812e-04, /* 3F3026F7, 1A8D1068 */
		+7.81794442939557092300e-05, /* 3F147E88, A03792A6 */
		+7.14072491382608190305e-05, /* 3F12B80F, 32F0A7E9 */
		-1.85586374855275456654e-05, /* BEF375CB, DB605373 */
		+2.59073051863633712884e-05, /* 3EFB2A70, 74BF7AD4 */
	};
	t_f64 z, r, v, w, s, a;
	t_f64 w0, a0;
	t_u32 hx;
	int big, sign;

	GET_F64_WORD_HI(hx,x);
	big = (hx&0x7fffffff) >= 0x3FE59428; /* |x| >= 0.6744 */
	if (big) {
		sign = hx>>31;
		if (sign) {
			x = -x;
			y = -y;
		}
		x = (pio4 - x) + (pio4lo - y);
		y = 0.0;
	}
	z = x * x;
	w = z * z;
	/*
	 * Break x^5*(polynomial[1]+x^2*polynomial[2]+...) into
	 * x^5(polynomial[1]+x^4*polynomial[3]+...+x^20*polynomial[11]) +
	 * x^5(x^2*(polynomial[2]+x^4*polynomial[4]+...+x^22*[T12]))
	*/
	r = polynomial[1] + w*(polynomial[3] + w*(polynomial[5] + w*(polynomial[7] + w*(polynomial[9] + w*polynomial[11]))));
	v = z*(polynomial[2] + w*(polynomial[4] + w*(polynomial[6] + w*(polynomial[8] + w*(polynomial[10] + w*polynomial[12])))));
	s = z * x;
	r = y + z*(s*(r + v) + y) + s*polynomial[0];
	w = x + r;
	if (big) {
		s = 1 - 2*odd;
		v = s - 2.0 * (x + (r - w*w/(w + s)));
		return sign ? -v : v;
	}
	if (!odd)
		return w;
	/* -1.0/(x+r) has up to 2ulp error, so compute it accurately */
	w0 = w;
	SET_F64_WORD_LO(w0, 0);
	v = r - (w0 - x);      /* w0+v = r+x */
	a0 = a = -1. / w;
	SET_F64_WORD_LO(a0, 0);
	return a0 + a*(1. + a0*w0 + a0*v);
}

#define DEFINEFUNC_FLOAT_TAN(BITS) \
t_f##BITS	__tan_f##BITS(t_f##BITS x, t_f##BITS y, t_bool odd) \
{ \
	t_f##BITS z, r, v, w, s, a, t; \
	int big, sign; \
 \
	big = F##BITS##_Abs(x) >= 0.67434; \
	if (big) { \
		sign = 0; \
		if (x < 0) { \
			sign = 1; \
			x = -x; \
			y = -y; \
		} \
		x = (pio4 - x) + (pio4lo - y); \
		y = 0.0; \
	} \
	z = x * x; \
	w = z * z; \
	r = RPOLY(w); \
	v = z * VPOLY(w); \
	s = z * x; \
	r = y + z * (s * (r + v) + y) + T3 * s; \
	w = x + r; \
	if (big) { \
		s = 1 - 2*odd; \
		v = s - 2.0 * (x + (r - w * w / (w + s))); \
		return sign ? -v : v; \
	} \
	if (!odd) \
		return w; \
	/* \
	 * if allow error up to 2 ulp, simply return \
	 * -1. / (x+r) here \
	 */ \
	/* compute -1. / (x+r) accurately */ \
	z = w; \
	z = z + 0x1p32 - 0x1p32; \
	v = r - (z - x);       /* z+v = r+x */ \
	t = a = -1. / w;      /* a = -1.0/w */ \
	t = t + 0x1p32 - 0x1p32; \
	s = 1. + t * z; \
	return t + a * (s + t * v); \
} \

#if LIBCONFIG_USE_FLOAT80
/*
 * Domain [-0.67434, 0.67434], range ~[-2.25e-22, 1.921e-22]
 * |tan(x)/x - t(x)| < 2**-71.9
 *
 * See __cosl.c for more details about the polynomial.
 */
static const long double
pio4   =  0.785398163397448309628L,    /*  0xc90fdaa22168c235.0p-64 */
pio4lo = -1.25413940316708300586e-20L; /* -0xece675d1fc8f8cbb.0p-130 */
T3  =  0.333333333333333333180L,       /*  0xaaaaaaaaaaaaaaa5.0p-65 */
T5  =  0.133333333333333372290L,       /*  0x88888888888893c3.0p-66 */
T7  =  0.0539682539682504975744L,      /*  0xdd0dd0dd0dc13ba2.0p-68 */
static const double
T9  =  0.021869488536312216,           /*  0x1664f4882cc1c2.0p-58 */
T11 =  0.0088632355256619590,          /*  0x1226e355c17612.0p-59 */
T13 =  0.0035921281113786528,          /*  0x1d6d3d185d7ff8.0p-61 */
T15 =  0.0014558334756312418,          /*  0x17da354aa3f96b.0p-62 */
T17 =  0.00059003538700862256,         /*  0x13559358685b83.0p-63 */
T19 =  0.00023907843576635544,         /*  0x1f56242026b5be.0p-65 */
T21 =  0.000097154625656538905,        /*  0x1977efc26806f4.0p-66 */
T23 =  0.000038440165747303162,        /*  0x14275a09b3ceac.0p-67 */
T25 =  0.000018082171885432524,        /*  0x12f5e563e5487e.0p-68 */
T27 =  0.0000024196006108814377,       /*  0x144c0d80cc6896.0p-71 */
T29 =  0.0000078293456938132840,       /*  0x106b59141a6cb3.0p-69 */
T31 = -0.0000032609076735050182,       /* -0x1b5abef3ba4b59.0p-71 */
T33 =  0.0000023261313142559411;       /*  0x13835436c0c87f.0p-71 */
#define RPOLY(w) (T5 + w * (T9 + w * (T13 + w * (T17 + w * (T21 + w * (T25 + w * (T29 + w * T33)))))))
#define VPOLY(w) (T7 + w * (T11 + w * (T15 + w * (T19 + w * (T23 + w * (T27 + w * T31))))))

DEFINEFUNC_FLOAT_TAN(80)
#endif

#if LIBCONFIG_USE_FLOAT128
/*
 * Domain [-0.67434, 0.67434], range ~[-3.37e-36, 1.982e-37]
 * |tan(x)/x - t(x)| < 2**-117.8 (XXX should be ~1e-37)
 *
 * See __cosl.c for more details about the polynomial.
 */
static const long double
pio4 = 0x1.921fb54442d18469898cc51701b8p-1L,
pio4lo = 0x1.cd129024e088a67cc74020bbea60p-116L;
T3  = 0x1.5555555555555555555555555553p-02L,
T5  = 0x1.1111111111111111111111111eb5p-03L,
T7  = 0x1.ba1ba1ba1ba1ba1ba1ba1b694cd6p-05L,
T9  = 0x1.664f4882c10f9f32d6bbe09d8bcdp-06L,
T11 = 0x1.226e355e6c23c8f5b4f5762322eep-07L,
T13 = 0x1.d6d3d0e157ddfb5fed8e84e27b37p-09L,
T15 = 0x1.7da36452b75e2b5fce9ee7c2c92ep-10L,
T17 = 0x1.355824803674477dfcf726649efep-11L,
T19 = 0x1.f57d7734d1656e0aceb716f614c2p-13L,
T21 = 0x1.967e18afcb180ed942dfdc518d6cp-14L,
T23 = 0x1.497d8eea21e95bc7e2aa79b9f2cdp-15L,
T25 = 0x1.0b132d39f055c81be49eff7afd50p-16L,
T27 = 0x1.b0f72d33eff7bfa2fbc1059d90b6p-18L,
T29 = 0x1.5ef2daf21d1113df38d0fbc00267p-19L,
T31 = 0x1.1c77d6eac0234988cdaa04c96626p-20L,
T33 = 0x1.cd2a5a292b180e0bdd701057dfe3p-22L,
T35 = 0x1.75c7357d0298c01a31d0a6f7d518p-23L,
T37 = 0x1.2f3190f4718a9a520f98f50081fcp-24L,
static const double
T39 =  0.000000028443389121318352,	/*  0x1e8a7592977938.0p-78 */
T41 =  0.000000011981013102001973,	/*  0x19baa1b1223219.0p-79 */
T43 =  0.0000000038303578044958070,	/*  0x107385dfb24529.0p-80 */
T45 =  0.0000000034664378216909893,	/*  0x1dc6c702a05262.0p-81 */
T47 = -0.0000000015090641701997785,	/* -0x19ecef3569ebb6.0p-82 */
T49 =  0.0000000029449552300483952,	/*  0x194c0668da786a.0p-81 */
T51 = -0.0000000022006995706097711,	/* -0x12e763b8845268.0p-81 */
T53 =  0.0000000015468200913196612,	/*  0x1a92fc98c29554.0p-82 */
T55 = -0.00000000061311613386849674,	/* -0x151106cbc779a9.0p-83 */
T57 =  1.4912469681508012e-10;		/*  0x147edbdba6f43a.0p-85 */
#define RPOLY(w) (T5 + w * (T9 + w * (T13 + w * (T17 + w * (T21 + w * (T25 + w * (T29 + w * (T33 + w * (T37 + w * (T41 + w * (T45 + w * (T49 + w * (T53 + w * T57)))))))))))))
#define VPOLY(w) (T7 + w * (T11 + w * (T15 + w * (T19 + w * (T23 + w * (T27 + w * (T31 + w * (T35 + w * (T39 + w * (T43 + w * (T47 + w * (T51 + w * T55))))))))))))

DEFINEFUNC_FLOAT_TAN(128)
#endif



/* origin: FreeBSD /usr/src/lib/msun/src/e_rem_pio2f.c */
/*
** Conversion to t_f32 by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
** Debugged and optimized by Bruce D. Evans.
*/
/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/
/*! __rem_pi2_f32(x,y)
**
** return the remainder of x rem pi/2 in *y
** use t_f64 precision for everything except passing x
** use __rem_pi2_large() for large x
*/

#if LIBCONFIG_USE_FLOAT16
t_sint	__rem_pi2_f16(t_f16 x, t_f64 *y)
{
	return __rem_pi2_f32(x, y);
}
#endif

#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif

t_sint __rem_pi2_f32(t_f32 x, t_f64 *y)
{
	static const t_f64	toint   = 1.5 / F64_EPSILON;
	static const t_f64	pio4    = 0x1.921fb6p-1;
	static const t_f64	invpio2 = 6.36619772367581382433e-01; /* 0x3FE45F30, 0x6DC9C883 */	/* 53 bits of 2/pi */
	static const t_f64	pio2_1  = 1.57079631090164184570e+00; /* 0x3FF921FB, 0x50000000 */	/* first 25 bits of pi/2 */
	static const t_f64	pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */	/* pi/2 - pio2_1 */
	u_cast_f32 u = {x};
	t_f64	tx[1],ty[1];
	t_f64	fn;
	t_u32	ix;
	t_sint	n;
	t_sint	e0;
	t_bool	sign;

	ix = u.as_u & 0x7FFFFFFF;
	/* 25+53 bit pi is good enough for medium size */
	if (ix < 0x4DC90FDB) /* |x| ~< 2^28*(pi/2), medium size */
	{
		/* Use a specialized rint() to get fn. */
		fn = (t_f64)x*invpio2 + toint - toint;
		n  = (t_s32)fn;
		*y = x - fn*pio2_1 - fn*pio2_1t;
		/* Matters with directed rounding. */
		if (predict_false(*y < -pio4))
		{
			n--;
			fn--;
			*y = x - fn*pio2_1 - fn*pio2_1t;
		}
		else if (predict_false(*y > pio4))
		{
			n++;
			fn++;
			*y = x - fn*pio2_1 - fn*pio2_1t;
		}
		return n;
	}
	if (ix>=0x7f800000) /* x is inf or NaN */
	{
		*y = x-x;
		return 0;
	}
	/* scale x into [2^23, 2^24-1] */
	sign = u.as_u>>31;
	e0 = (ix >> F32_MANTISSA_BITS) - (0x7F + F32_MANTISSA_BITS); /* e0 = ilogb(|x|)-23, positive */
	u.as_u = ix - (e0 << F32_MANTISSA_BITS);
	tx[0] = u.as_f;
	n  =  __rem_pi2_large(tx,ty,e0,1,0);
	if (sign)
	{
		*y = -ty[0];
		return -n;
	}
	*y = ty[0];
	return n;
}
/* origin: FreeBSD /usr/src/lib/msun/src/e_rem_pio2.c */
/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunSoft, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
**
** Optimized by Bruce D. Evans.
*/
/* __rem_pi2_f64(x,y)
**
** return the remainder of x rem pi/2 in y[0]+y[1]
** use __rem_pi2_large() for large x
*/


#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif

/* caller must handle the case when reduction is not needed: |x| ~<= pi/4 */
t_sint __rem_pi2_f64(t_f64 x, t_f64 *y)
{
	static const t_f64
	toint   = 1.5 / F64_EPSILON,
	pio4    = 0x1.921fb54442d18p-1,
	invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */	/* 53 bits of 2/pi */
	pio2_1  = 1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */	/* first  33 bit of pi/2 */
	pio2_1t = 6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */	/* pi/2 - pio2_1 */
	pio2_2  = 6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */	/* second 33 bit of pi/2 */
	pio2_2t = 2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */	/* pi/2 - (pio2_1+pio2_2) */
	pio2_3  = 2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */	/* third  33 bit of pi/2 */
	pio2_3t = 8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */	/* pi/2 - (pio2_1+pio2_2+pio2_3) */

	u_cast_f64 u = {x};
	t_f64 z,w,t,r,fn;
	t_f64 tx[3],ty[2];
	t_u32 ix;
	int sign, n, ex, ey, i;

	sign = u.as_u>>63;
	ix = u.as_u>>32 & 0x7fffffff;
	if (ix <= 0x400f6a7a)
	{ /* |x| ~<= 5pi/4 */
		if ((ix & 0xfffff) == 0x921fb) /* |x| ~= pi/2 or 2pi/2 */
			goto medium; /* cancellation -- use medium case */
		if (ix <= 0x4002d97c)
		{ /* |x| ~<= 3pi/4 */
			if (!sign)
			{
				z = x - pio2_1; /* one round good to 85 bits */
				y[0] = z - pio2_1t;
				y[1] = (z-y[0]) - pio2_1t;
				return 1;
			}
			else
			{
				z = x + pio2_1;
				y[0] = z + pio2_1t;
				y[1] = (z-y[0]) + pio2_1t;
				return -1;
			}
		}
		else
		{
			if (!sign)
			{
				z = x - 2*pio2_1;
				y[0] = z - 2*pio2_1t;
				y[1] = (z-y[0]) - 2*pio2_1t;
				return 2;
			}
			else
			{
				z = x + 2*pio2_1;
				y[0] = z + 2*pio2_1t;
				y[1] = (z-y[0]) + 2*pio2_1t;
				return -2;
			}
		}
	}
	if (ix <= 0x401c463b)
	{ /* |x| ~<= 9pi/4 */
		if (ix <= 0x4015fdbc)
		{ /* |x| ~<= 7pi/4 */
			if (ix == 0x4012d97c) /* |x| ~= 3pi/2 */
				goto medium;
			if (!sign)
			{
				z = x - 3*pio2_1;
				y[0] = z - 3*pio2_1t;
				y[1] = (z-y[0]) - 3*pio2_1t;
				return 3;
			}
			else
			{
				z = x + 3*pio2_1;
				y[0] = z + 3*pio2_1t;
				y[1] = (z-y[0]) + 3*pio2_1t;
				return -3;
			}
		}
		else
		{
			if (ix == 0x401921fb) /* |x| ~= 4pi/2 */
				goto medium;
			if (!sign)
			{
				z = x - 4*pio2_1;
				y[0] = z - 4*pio2_1t;
				y[1] = (z-y[0]) - 4*pio2_1t;
				return 4;
			}
			else
			{
				z = x + 4*pio2_1;
				y[0] = z + 4*pio2_1t;
				y[1] = (z-y[0]) + 4*pio2_1t;
				return -4;
			}
		}
	}
	if (ix < 0x413921fb)
	{ /* |x| ~< 2^20*(pi/2), medium size */
medium:
		/* rint(x/(pi/2)) */
		fn = (t_f64)x*invpio2 + toint - toint;
		n = (t_s32)fn;
		r = x - fn*pio2_1;
		w = fn*pio2_1t; /* 1st round, good to 85 bits */
		/* Matters with directed rounding. */
		if (predict_false(r - w < -pio4))
		{
			n--;
			fn--;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		else if (predict_false(r - w > pio4))
		{
			n++;
			fn++;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		y[0] = r - w;
		u.as_f = y[0];
		ey = u.as_u>>52 & 0x7ff;
		ex = ix>>20;
		if (ex - ey > 16)
		{	/* 2nd round, good to 118 bits */
			t = r;
			w = fn*pio2_2;
			r = t - w;
			w = fn*pio2_2t - ((t-r)-w);
			y[0] = r - w;
			u.as_f = y[0];
			ey = u.as_u>>52 & 0x7ff;
			if (ex - ey > 49)
			{	/* 3rd round, good to 151 bits, covers all cases */
				t = r;
				w = fn*pio2_3;
				r = t - w;
				w = fn*pio2_3t - ((t-r)-w);
				y[0] = r - w;
			}
		}
		y[1] = (r - y[0]) - w;
		return n;
	}
	/*
	**	all other (large) arguments
	*/
	if (ix >= 0x7ff00000)
	{ /* x is inf or NaN */
		y[0] = y[1] = x - x;
		return 0;
	}
	/* set z = scalbn(|x|,-ilogb(x)+23) */
	u.as_f = x;
	u.as_u &= (t_u64)-1>>12;
	u.as_u |= (t_u64)(0x3ff + 23)<<52;
	z = u.as_f;
	for (i=0; i < 2; i++)
	{
		tx[i] = (t_f64)(t_s32)z;
		z     = (z-tx[i])*0x1p24;
	}
	tx[i] = z;
	/* skip zero terms, first term is non-zero */
	while (tx[i] == 0.0)
		i--;
	n = __rem_pi2_large(tx,ty,(int)(ix>>20)-(0x3ff+23),i+1,1);
	if (sign)
	{
		y[0] = -ty[0];
		y[1] = -ty[1];
		return -n;
	}
	y[0] = ty[0];
	y[1] = ty[1];
	return n;
}

/* origin: FreeBSD /usr/src/lib/msun/ld80/e_rem_pio2.c */
/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
** Copyright (c) 2008 Steven G. Kargl, David Schultz, Bruce D. Evans.
**
** Developed at SunSoft, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
**
** Optimized by Bruce D. Evans.
*/
/* ld80 and ld128 version of __rem_pi2_f64(x,y)
**
** return the remainder of x rem pi/2 in y[0]+y[1]
** use __rem_pi2_large() for large x
*/


#if LIBCONFIG_USE_FLOAT80

/* u ~< 0x1p25*pi/2 */
#define SMALL(u) (((u.i.se & 0x7fffU)<<16 | u.i.m>>48) < ((0x3fff + 25)<<16 | 0x921f>>1 | 0x8000))
#define QUOBITS(x) ((t_u32)(t_s32)x & 0x7fffffff)
#define ROUND1 22
#define ROUND2 61
#define NX 3
#define NY 2

int __rem_pi2_f80(t_f80 x, t_f80 *y)
{
	static const t_f80 toint = 1.5 / F80_EPSILON;
	static const t_f64
	pio2_1 =  1.57079632679597125389e+00, /* 0x3FF921FB, 0x54444000   */	/* first  39 bits of pi/2 */
	pio2_2 = -1.07463465549783099519e-12, /* -0x12e7b967674000.0p-092 */	/* second 39 bits of pi/2 */
	pio2_3 =  6.36831716351370313614e-25; /* +0x18a2e037074000.0p-133 */	/* third  39 bits of pi/2 */
	static const t_f80
	pio4    =  0x1.921fb54442d1846ap-1L,
	invpio2 =  6.36619772367581343076e-01L, /*  0xa2f9836e4e44152a.0p-064 */	/* 64 bits of 2/pi */
	pio2_1t = -1.07463465549719416346e-12L, /* -0x973dcb3b399d747f.0p-103 */	/* pi/2 - pio2_1 */
	pio2_2t =  6.36831716351095013979e-25L, /*  0xc51701b839a25205.0p-144 */	/* pi/2 - (pio2_1+pio2_2) */
	pio2_3t = -2.75299651904407171810e-37L; /* -0xbb5bf6c7ddd660ce.0p-185 */	/* pi/2 - (pio2_1+pio2_2+pio2_3) */

	union ldshape u,uz;
	t_f80 z,w,t,r,fn;
	t_f64 tx[NX],ty[NY];
	int ex,ey,n,i;

	u.f = x;
	ex = u.i.se & 0x7fff;
	if (SMALL(u))
	{
		/* rint(x/(pi/2)) */
		fn = x*invpio2 + toint - toint;
		n = QUOBITS(fn);
		r = x-fn*pio2_1;
		w = fn*pio2_1t; /* 1st round good to 102/180 bits (ld80/ld128) */
		/* Matters with directed rounding. */
		if (predict_false(r - w < -pio4))
		{
			n--;
			fn--;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		else if (predict_false(r - w > pio4))
		{
			n++;
			fn++;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		y[0] = r-w;
		u.f = y[0];
		ey = u.i.se & 0x7fff;
		if (ex - ey > ROUND1)
		{ /* 2nd iteration needed, good to 141/248 (ld80/ld128) */
			t = r;
			w = fn*pio2_2;
			r = t-w;
			w = fn*pio2_2t-((t-r)-w);
			y[0] = r-w;
			u.f = y[0];
			ey = u.i.se & 0x7fff;
			if (ex - ey > ROUND2)
			{ /* 3rd iteration, good to 180/316 bits */
				t = r; /* will cover all possible cases (not verified for ld128) */
				w = fn*pio2_3;
				r = t-w;
				w = fn*pio2_3t-((t-r)-w);
				y[0] = r-w;
			}
		}
		y[1] = (r - y[0]) - w;
		return n;
	}
	/*
	**	all other (large) arguments
	*/
	if (ex == 0x7fff)
	{               /* x is inf or NaN */
		y[0] = y[1] = x - x;
		return 0;
	}
	/* set z = scalbn(|x|,-ilogb(x)+23) */
	uz.f = x;
	uz.i.se = 0x3fff + 23;
	z = uz.f;
	for (i=0; i < NX - 1; i++)
	{
		tx[i] = (t_f64)(t_s32)z;
		z     = (z-tx[i])*0x1p24;
	}
	tx[i] = z;
	while (tx[i] == 0)
		i--;
	n = __rem_pi2_large(tx, ty, ex-0x3fff-23, i+1, NY);
	w = ty[1];
	if (NY == 3)
		w += ty[2];
	r = ty[0] + w;
	/* TODO: for ld128 this does not follow the recommendation of the
	comments of __rem_pi2_large which seem wrong if |ty[0]| > |ty[1]+ty[2]| */
	w -= r - ty[0];
	if (u.i.se >> 15)
	{
		y[0] = -r;
		y[1] = -w;
		return -n;
	}
	y[0] = r;
	y[1] = w;
	return n;
}
#endif

#if LIBCONFIG_USE_FLOAT128
/* u ~< 0x1p45*pi/2 */
#define SMALL(u) (((u.i.se & 0x7fffU)<<16 | u.i.top) < ((0x3fff + 45)<<16 | 0x921f))
#define QUOBITS(x) ((t_u32)(t_s64)x & 0x7fffffff)
#define ROUND1 51
#define ROUND2 119
#define NX 5
#define NY 3

int __rem_pi2_f128(t_f80 x, t_f80 *y)
{
	static const t_f80 toint = 1.5 / F128_EPSILON;
	static const t_f80
	pio4    =  0x1.921fb54442d18469898cc51701b8p-1L,
	invpio2 =  6.3661977236758134307553505349005747e-01L,	/*  0x145f306dc9c882a53f84eafa3ea6a.0p-113 */
	pio2_1  =  1.5707963267948966192292994253909555e+00L,	/*  0x1921fb54442d18469800000000000.0p-112 */
	pio2_1t =  2.0222662487959507323996846200947577e-21L,	/*  0x13198a2e03707344a4093822299f3.0p-181 */
	pio2_2  =  2.0222662487959507323994779168837751e-21L,	/*  0x13198a2e03707344a400000000000.0p-181 */
	pio2_2t =  2.0670321098263988236496903051604844e-43L,	/*  0x127044533e63a0105df531d89cd91.0p-254 */
	pio2_3  =  2.0670321098263988236499468110329591e-43L,	/*  0x127044533e63a0105e00000000000.0p-254 */
	pio2_3t = -2.5650587247459238361625433492959285e-65L;	/* -0x159c4ec64ddaeb5f78671cbfb2210.0p-327 */

	union ldshape u,uz;
	t_f80 z,w,t,r,fn;
	t_f64 tx[NX],ty[NY];
	int ex,ey,n,i;

	u.f = x;
	ex = u.i.se & 0x7fff;
	if (SMALL(u))
	{
		/* rint(x/(pi/2)) */
		fn = x*invpio2 + toint - toint;
		n = QUOBITS(fn);
		r = x-fn*pio2_1;
		w = fn*pio2_1t; /* 1st round good to 102/180 bits (ld80/ld128) */
		/* Matters with directed rounding. */
		if (predict_false(r - w < -pio4))
		{
			n--;
			fn--;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		else if (predict_false(r - w > pio4))
		{
			n++;
			fn++;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		y[0] = r-w;
		u.f = y[0];
		ey = u.i.se & 0x7fff;
		if (ex - ey > ROUND1)
		{ /* 2nd iteration needed, good to 141/248 (ld80/ld128) */
			t = r;
			w = fn*pio2_2;
			r = t-w;
			w = fn*pio2_2t-((t-r)-w);
			y[0] = r-w;
			u.f = y[0];
			ey = u.i.se & 0x7fff;
			if (ex - ey > ROUND2)
			{ /* 3rd iteration, good to 180/316 bits */
				t = r; /* will cover all possible cases (not verified for ld128) */
				w = fn*pio2_3;
				r = t-w;
				w = fn*pio2_3t-((t-r)-w);
				y[0] = r-w;
			}
		}
		y[1] = (r - y[0]) - w;
		return n;
	}
	/*
	**	all other (large) arguments
	*/
	if (ex == 0x7fff)
	{               /* x is inf or NaN */
		y[0] = y[1] = x - x;
		return 0;
	}
	/* set z = scalbn(|x|,-ilogb(x)+23) */
	uz.f = x;
	uz.i.se = 0x3fff + 23;
	z = uz.f;
	for (i=0; i < NX - 1; i++)
	{
		tx[i] = (t_f64)(t_s32)z;
		z     = (z-tx[i])*0x1p24;
	}
	tx[i] = z;
	while (tx[i] == 0)
		i--;
	n = __rem_pi2_large(tx, ty, ex-0x3fff-23, i+1, NY);
	w = ty[1];
	if (NY == 3)
		w += ty[2];
	r = ty[0] + w;
	/* TODO: for ld128 this does not follow the recommendation of the
	comments of __rem_pi2_large which seem wrong if |ty[0]| > |ty[1]+ty[2]| */
	w -= r - ty[0];
	if (u.i.se >> 15)
	{
		y[0] = -r;
		y[1] = -w;
		return -n;
	}
	y[0] = r;
	y[1] = w;
	return n;
}
#endif

/* origin: FreeBSD /usr/src/lib/msun/src/k_rem_pio2.c */
/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunSoft, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/
/*! __rem_pi2_large(x,y,e0,nx,prec)
** t_f64 x[],y[]; int e0,nx,prec;
**
** __rem_pi2_large return the last three digits of N with
**              y = x - N*pi/2
** so that |y| < pi/2.
**
** The method is to compute the integer (mod 8) and fraction parts of
** (2/pi)*x without doing the full multiplication. In general we
** skip the part of the product that are known to be a huge integer (
** more accurately, = 0 mod 8 ). Thus the number of operations are
** independent of the exponent of the input.
**
** (2/pi) is represented by an array of 24-bit integers in ipio2[].
**
** Input parameters:
**      x[]     The input value (must be positive) is broken into nx
**              pieces of 24-bit integers in t_f64 precision format.
**              x[i] will be the i-th 24 bit of x. The scaled exponent
**              of x[0] is given in input parameter e0 (i.e., x[0]*2^e0
**              match x's up to 24 bits.
**
**              Example of breaking a t_f64 positive z into x[0]+x[1]+x[2]:
**                      e0 = ilogb(z)-23
**                      z  = scalbn(z,-e0)
**              for i = 0,1,2
**                      x[i] = floor(z)
**                      z    = (z-x[i])*2**24
**
**
**      y[]     ouput result in an array of t_f64 precision numbers.
**              The dimension of y[] is:
**                      24-bit  precision       1
**                      53-bit  precision       2
**                      64-bit  precision       2
**                      113-bit precision       3
**              The actual value is the sum of them. Thus for 113-bit
**              precison, one may have to do something like:
**
**              t_f80 t,w,r_head, r_tail;
**              t = (t_f80)y[2] + (t_f80)y[1];
**              w = (t_f80)y[0];
**              r_head = t+w;
**              r_tail = w - (r_head - t);
**
**      e0      The exponent of x[0]. Must be <= 16360 or you need to
**              expand the ipio2 table.
**
**      nx      dimension of x[]
**
**      prec    an integer indicating the precision:
**                      0       24  bits (single)
**                      1       53  bits (t_f64)
**                      2       64  bits (extended)
**                      3       113 bits (quad)
**
** External function:
**      t_f64 scalbn(), floor();
**
**
** Here is the description of some local variables:
**
**      jk      jk+1 is the initial number of terms of ipio2[] needed
**              in the computation. The minimum and recommended value
**              for jk is 3,4,4,6 for single, t_f64, extended, and quad.
**              jk+1 must be 2 larger than you might expect so that our
**              recomputation test works. (Up to 24 bits in the integer
**              part (the 24 bits of it that we compute) and 23 bits in
**              the fraction part may be lost to cancelation before we
**              recompute.)
**
**      jz      local integer variable indicating the number of
**              terms of ipio2[] used.
**
**      jx      nx - 1
**
**      jv      index for pointing to the suitable ipio2[] for the
**              computation. In general, we want
**                      ( 2^e0*x[0] * ipio2[jv-1]*2^(-24jv) )/8
**              is an integer. Thus
**                      e0-3-24*jv >= 0 or (e0-3)/24 >= jv
**              Hence jv = max(0,(e0-3)/24).
**
**      jp      jp+1 is the number of terms in PIo2[] needed, jp = jk.
**
**      q[]     t_f64 array with integral value, representing the
**              24-bits chunk of the product of x and 2/pi.
**
**      q0      the corresponding exponent of q[0]. Note that the
**              exponent for q[i] would be q0-24*i.
**
**      PIo2[]  t_f64 precision array, obtained by cutting pi/2
**              into 24 bits chunks.
**
**      f[]     ipio2[] in floating point
**
**      iq[]    integer array by breaking up q[] in 24-bits chunk.
**
**      fq[]    final product of x*(2/pi) in fq[0],..,fq[jk]
**
**      ih      integer. If >0 it indicates q[] is >= 0.5, hence
**              it also indicates the *sign* of the result.
**
*/
/*
** Constants:
** The hexadecimal values are the intended ones for the following
** constants. The decimal values may be used, provided that the
** compiler will convert from decimal to binary accurately enough
** to produce the hexadecimal values shown.
*/


static const int init_jk[] = {3,4,4,6}; /* initial value for jk */

/*
** Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi
**
**              integer array, contains the (24*i)-th to (24*i+23)-th
**              bit of 2/pi after binary point. The corresponding
**              floating value is
**
**                      ipio2[i] * 2^(-24(i+1)).
**
** NB: This table must have at least (e0-3)/24 + jk terms.
**     For quad precision (e0 <= 16360, jk = 6), this is 686.
*/
static const t_s32 ipio2[] =
{
0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,

#if LDBL_MAX_EXP > 1024
0x47C419, 0xC367CD, 0xDCE809, 0x2A8359, 0xC4768B, 0x961CA6,
0xDDAF44, 0xD15719, 0x053EA5, 0xFF0705, 0x3F7E33, 0xE832C2,
0xDE4F98, 0x327DBB, 0xC33D26, 0xEF6B1E, 0x5EF89F, 0x3A1F35,
0xCAF27F, 0x1D87F1, 0x21907C, 0x7C246A, 0xFA6ED5, 0x772D30,
0x433B15, 0xC614B5, 0x9D19C3, 0xC2C4AD, 0x414D2C, 0x5D000C,
0x467D86, 0x2D71E3, 0x9AC69B, 0x006233, 0x7CD2B4, 0x97A7B4,
0xD55537, 0xF63ED7, 0x1810A3, 0xFC764D, 0x2A9D64, 0xABD770,
0xF87C63, 0x57B07A, 0xE71517, 0x5649C0, 0xD9D63B, 0x3884A7,
0xCB2324, 0x778AD6, 0x23545A, 0xB91F00, 0x1B0AF1, 0xDFCE19,
0xFF319F, 0x6A1E66, 0x615799, 0x47FBAC, 0xD87F7E, 0xB76522,
0x89E832, 0x60BFE6, 0xCDC4EF, 0x09366C, 0xD43F5D, 0xD7DE16,
0xDE3B58, 0x929BDE, 0x2822D2, 0xE88628, 0x4D58E2, 0x32CAC6,
0x16E308, 0xCB7DE0, 0x50C017, 0xA71DF3, 0x5BE018, 0x34132E,
0x621283, 0x014883, 0x5B8EF5, 0x7FB0AD, 0xF2E91E, 0x434A48,
0xD36710, 0xD8DDAA, 0x425FAE, 0xCE616A, 0xA4280A, 0xB499D3,
0xF2A606, 0x7F775C, 0x83C2A3, 0x883C61, 0x78738A, 0x5A8CAF,
0xBDD76F, 0x63A62D, 0xCBBFF4, 0xEF818D, 0x67C126, 0x45CA55,
0x36D9CA, 0xD2A828, 0x8D61C2, 0x77C912, 0x142604, 0x9B4612,
0xC459C4, 0x44C5C8, 0x91B24D, 0xF31700, 0xAD43D4, 0xE54929,
0x10D5FD, 0xFCBE00, 0xCC941E, 0xEECE70, 0xF53E13, 0x80F1EC,
0xC3E7B3, 0x28F8C7, 0x940593, 0x3E71C1, 0xB3092E, 0xF3450B,
0x9C1288, 0x7B20AB, 0x9FB52E, 0xC29247, 0x2F327B, 0x6D550C,
0x90A772, 0x1FE76B, 0x96CB31, 0x4A1679, 0xE27941, 0x89DFF4,
0x9794E8, 0x84E6E2, 0x973199, 0x6BED88, 0x365F5F, 0x0EFDBB,
0xB49A48, 0x6CA467, 0x427271, 0x325D8D, 0xB8159F, 0x09E5BC,
0x25318D, 0x3974F7, 0x1C0530, 0x010C0D, 0x68084B, 0x58EE2C,
0x90AA47, 0x02E774, 0x24D6BD, 0xA67DF7, 0x72486E, 0xEF169F,
0xA6948E, 0xF691B4, 0x5153D1, 0xF20ACF, 0x339820, 0x7E4BF5,
0x6863B2, 0x5F3EDD, 0x035D40, 0x7F8985, 0x295255, 0xC06437,
0x10D86D, 0x324832, 0x754C5B, 0xD4714E, 0x6E5445, 0xC1090B,
0x69F52A, 0xD56614, 0x9D0727, 0x50045D, 0xDB3BB4, 0xC576EA,
0x17F987, 0x7D6B49, 0xBA271D, 0x296996, 0xACCCC6, 0x5414AD,
0x6AE290, 0x89D988, 0x50722C, 0xBEA404, 0x940777, 0x7030F3,
0x27FC00, 0xA871EA, 0x49C266, 0x3DE064, 0x83DD97, 0x973FA3,
0xFD9443, 0x8C860D, 0xDE4131, 0x9D3992, 0x8C70DD, 0xE7B717,
0x3BDF08, 0x2B3715, 0xA0805C, 0x93805A, 0x921110, 0xD8E80F,
0xAF806C, 0x4BFFDB, 0x0F9038, 0x761859, 0x15A562, 0xBBCB61,
0xB989C7, 0xBD4010, 0x04F2D2, 0x277549, 0xF6B6EB, 0xBB22DB,
0xAA140A, 0x2F2689, 0x768364, 0x333B09, 0x1A940E, 0xAA3A51,
0xC2A31D, 0xAEEDAF, 0x12265C, 0x4DC26D, 0x9C7A2D, 0x9756C0,
0x833F03, 0xF6F009, 0x8C402B, 0x99316D, 0x07B439, 0x15200C,
0x5BC3D8, 0xC492F5, 0x4BADC6, 0xA5CA4E, 0xCD37A7, 0x36A9E6,
0x9492AB, 0x6842DD, 0xDE6319, 0xEF8C76, 0x528B68, 0x37DBFC,
0xABA1AE, 0x3115DF, 0xA1AE00, 0xDAFB0C, 0x664D64, 0xB705ED,
0x306529, 0xBF5657, 0x3AFF47, 0xB9F96A, 0xF3BE75, 0xDF9328,
0x3080AB, 0xF68C66, 0x15CB04, 0x0622FA, 0x1DE4D9, 0xA4B33D,
0x8F1B57, 0x09CD36, 0xE9424E, 0xA4BE13, 0xB52333, 0x1AAAF0,
0xA8654F, 0xA5C1D2, 0x0F3F0B, 0xCD785B, 0x76F923, 0x048B7B,
0x721789, 0x53A6C6, 0xE26E6F, 0x00EBEF, 0x584A9B, 0xB7DAC4,
0xBA66AA, 0xCFCF76, 0x1D02D1, 0x2DF1B1, 0xC1998C, 0x77ADC3,
0xDA4886, 0xA05DF7, 0xF480C6, 0x2FF0AC, 0x9AECDD, 0xBC5C3F,
0x6DDED0, 0x1FC790, 0xB6DB2A, 0x3A25A3, 0x9AAF00, 0x9353AD,
0x0457B6, 0xB42D29, 0x7E804B, 0xA707DA, 0x0EAA76, 0xA1597B,
0x2A1216, 0x2DB7DC, 0xFDE5FA, 0xFEDB89, 0xFDBE89, 0x6C76E4,
0xFCA906, 0x70803E, 0x156E85, 0xFF87FD, 0x073E28, 0x336761,
0x86182A, 0xEABD4D, 0xAFE7B3, 0x6E6D8F, 0x396795, 0x5BBF31,
0x48D784, 0x16DF30, 0x432DC7, 0x356125, 0xCE70C9, 0xB8CB30,
0xFD6CBF, 0xA200A4, 0xE46C05, 0xA0DD5A, 0x476F21, 0xD21262,
0x845CB9, 0x496170, 0xE0566B, 0x015299, 0x375550, 0xB7D51E,
0xC4F133, 0x5F6E13, 0xE4305D, 0xA92E85, 0xC3B21D, 0x3632A1,
0xA4B708, 0xD4B1EA, 0x21F716, 0xE4698F, 0x77FF27, 0x80030C,
0x2D408D, 0xA0CD4F, 0x99A520, 0xD3A2B3, 0x0A5D2F, 0x42F9B4,
0xCBDA11, 0xD0BE7D, 0xC1DB9B, 0xBD17AB, 0x81A2CA, 0x5C6A08,
0x17552E, 0x550027, 0xF0147F, 0x8607E1, 0x640B14, 0x8D4196,
0xDEBE87, 0x2AFDDA, 0xB6256B, 0x34897B, 0xFEF305, 0x9EBFB9,
0x4F6A68, 0xA82A4A, 0x5AC44F, 0xBCF82D, 0x985AD7, 0x95C7F4,
0x8D4D0D, 0xA63A20, 0x5F57A4, 0xB13F14, 0x953880, 0x0120CC,
0x86DD71, 0xB6DEC9, 0xF560BF, 0x11654D, 0x6B0701, 0xACB08C,
0xD0C0B2, 0x485551, 0x0EFB1E, 0xC37295, 0x3B06A3, 0x3540C0,
0x7BDC06, 0xCC45E0, 0xFA294E, 0xC8CAD6, 0x41F3E8, 0xDE647C,
0xD8649B, 0x31BED9, 0xC397A4, 0xD45877, 0xC5E369, 0x13DAF0,
0x3C3ABA, 0x461846, 0x5F7555, 0xF5BDD2, 0xC6926E, 0x5D2EAC,
0xED440E, 0x423E1C, 0x87C461, 0xE9FD29, 0xF3D6E7, 0xCA7C22,
0x35916F, 0xC5E008, 0x8DD7FF, 0xE26A6E, 0xC6FDB0, 0xC10893,
0x745D7C, 0xB2AD6B, 0x9D6ECD, 0x7B723E, 0x6A11C6, 0xA9CFF7,
0xDF7329, 0xBAC9B5, 0x5100B7, 0x0DB2E2, 0x24BA74, 0x607DE5,
0x8AD874, 0x2C150D, 0x0C1881, 0x94667E, 0x162901, 0x767A9F,
0xBEFDFD, 0xEF4556, 0x367ED9, 0x13D9EC, 0xB9BA8B, 0xFC97C4,
0x27A831, 0xC36EF1, 0x36C594, 0x56A8D8, 0xB5A8B4, 0x0ECCCF,
0x2D8912, 0x34576F, 0x89562C, 0xE3CE99, 0xB920D6, 0xAA5E6B,
0x9C2A3E, 0xCC5F11, 0x4A0BFD, 0xFBF4E1, 0x6D3B8E, 0x2C86E2,
0x84D4E9, 0xA9B4FC, 0xD1EEEF, 0xC9352E, 0x61392F, 0x442138,
0xC8D91B, 0x0AFC81, 0x6A4AFB, 0xD81C2F, 0x84B453, 0x8C994E,
0xCC2254, 0xDC552A, 0xD6C6C0, 0x96190B, 0xB8701A, 0x649569,
0x605A26, 0xEE523F, 0x0F117F, 0x11B5F4, 0xF5CBFC, 0x2DBC34,
0xEEBC34, 0xCC5DE8, 0x605EDD, 0x9B8E67, 0xEF3392, 0xB817C9,
0x9B5861, 0xBC57E1, 0xC68351, 0x103ED8, 0x4871DD, 0xDD1C2D,
0xA118AF, 0x462C21, 0xD7F359, 0x987AD9, 0xC0549E, 0xFA864F,
0xFC0656, 0xAE79E5, 0x362289, 0x22AD38, 0xDC9367, 0xAAE855,
0x382682, 0x9BE7CA, 0xA40D51, 0xB13399, 0x0ED7A9, 0x480569,
0xF0B265, 0xA7887F, 0x974C88, 0x36D1F9, 0xB39221, 0x4A827B,
0x21CF98, 0xDC9F40, 0x5547DC, 0x3A74E1, 0x42EB67, 0xDF9DFE,
0x5FD45E, 0xA4677B, 0x7AACBA, 0xA2F655, 0x23882B, 0x55BA41,
0x086E59, 0x862A21, 0x834739, 0xE6E389, 0xD49EE5, 0x40FB49,
0xE956FF, 0xCA0F1C, 0x8A59C5, 0x2BFA94, 0xC5C1D3, 0xCFC50F,
0xAE5ADB, 0x86C547, 0x624385, 0x3B8621, 0x94792C, 0x876110,
0x7B4C2A, 0x1A2C80, 0x12BF43, 0x902688, 0x893C78, 0xE4C4A8,
0x7BDBE5, 0xC23AC4, 0xEAF426, 0x8A67F7, 0xBF920D, 0x2BA365,
0xB1933D, 0x0B7CBD, 0xDC51A4, 0x63DD27, 0xDDE169, 0x19949A,
0x9529A8, 0x28CE68, 0xB4ED09, 0x209F44, 0xCA984E, 0x638270,
0x237C7E, 0x32B90F, 0x8EF5A7, 0xE75614, 0x08F121, 0x2A9DB5,
0x4D7E6F, 0x5119A5, 0xABF9B5, 0xD6DF82, 0x61DD96, 0x023616,
0x9F3AC4, 0xA1A283, 0x6DED72, 0x7A8D39, 0xA9B882, 0x5C326B,
0x5B2746, 0xED3400, 0x7700D2, 0x55F4FC, 0x4D5901, 0x8071E0,
#endif
};

static const t_f64 PIo2[] =
{
  1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
  7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
  5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
  3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
  1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
  1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
  2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
  2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
};

t_sint __rem_pi2_large(t_f64 *x, t_f64 *y, t_sint e0, t_sint nx, t_sint prec)
{
	t_s32 jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
	t_f64 z,fw,f[20],fq[20],q[20];

	/* initialize jk*/
	jk = init_jk[prec];
	jp = jk;

	/* determine jx,jv,q0, note that 3>q0 */
	jx = nx-1;
	jv = (e0-3)/24;  if (jv<0) jv=0;
	q0 = e0-24*(jv+1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
	j = jv-jx; m = jx+jk;
	for (i=0; i<=m; i++,j++)
		f[i] = j<0 ? 0.0 : (t_f64)ipio2[j];

	/* compute q[0],q[1],...q[jk] */
	for (i=0; i<=jk; i++)
	{
		for (j=0,fw=0.0; j<=jx; j++)
			fw += x[j]*f[jx+i-j];
		q[i] = fw;
	}

	jz = jk;
recompute:
	/* distill q[] into iq[] reversingly */
	for (i=0,j=jz,z=q[jz]; j>0; i++,j--)
	{
		fw    = (t_f64)(t_s32)(0x1p-24*z);
		iq[i] = (t_s32)(z - 0x1p24*fw);
		z     = q[j-1]+fw;
	}

	/* compute n */
	z  = F64_From(z,q0);      /* actual value of z */
	z -= 8.0 * F64_Floor(z*0.125); /* trim off integer >= 8 */
	n  = (t_s32)z;
	z -= (t_f64)n;
	ih = 0;
	if (q0 > 0)
	{ /* need iq[jz-1] to determine n */
		i  = iq[jz-1]>>(24-q0); n += i;
		iq[jz-1] -= i<<(24-q0);
		ih = iq[jz-1]>>(23-q0);
	}
	else if (q0 == 0) ih = iq[jz-1]>>23;
	else if (z >= 0.5) ih = 2;

	if (ih > 0)
	{ /* q > 0.5 */
		n += 1; carry = 0;
		for (i=0; i<jz; i++)
		{ /* compute 1-q */
			j = iq[i];
			if (carry == 0)
			{
				if (j != 0)
				{
					carry = 1;
					iq[i] = 0x1000000 - j;
				}
			}
			else
				iq[i] = 0xffffff - j;
		}
		if (q0 > 0)
		{ /* rare case: chance is 1 in 12 */
			switch(q0)
			{
			case 1:
				iq[jz-1] &= 0x7fffff; break;
			case 2:
				iq[jz-1] &= 0x3fffff; break;
			}
		}
		if (ih == 2)
		{
			z = 1. - z;
			if (carry != 0)
				z -= F64_From(1.0,q0);
		}
	}

	/* check if recomputation is needed */
	if (z == 0.0)
	{
		j = 0;
		for (i=jz-1; i>=jk; i--) j |= iq[i];
		if (j == 0)
		{ /* need recomputation */
			for (k=1; iq[jk-k]==0; k++); /* k = no. of terms needed */

			for (i=jz+1; i<=jz+k; i++)
			{ /* add q[jz+1] to q[jz+k] */
				f[jx+i] = (t_f64)ipio2[jv+i];
				for (j=0,fw=0.0; j<=jx; j++)
					fw += x[j]*f[jx+i-j];
				q[i] = fw;
			}
			jz += k;
			goto recompute;
		}
	}

	/* chop off zero terms */
	if (z == 0.0)
	{
		jz -= 1;
		q0 -= 24;
		while (iq[jz] == 0)
		{
			jz--;
			q0 -= 24;
		}
	}
	else /* break z into 24-bit if necessary */
	{
		z = F64_From(z,-q0);
		if (z >= 0x1p24)
		{
			fw = (t_f64)(t_s32)(0x1p-24*z);
			iq[jz] = (t_s32)(z - 0x1p24*fw);
			jz += 1;
			q0 += 24;
			iq[jz] = (t_s32)fw;
		}
		else
			iq[jz] = (t_s32)z;
	}

	/* convert integer "bit" chunk to floating-point value */
	fw = F64_From(1.0,q0);
	for (i=jz; i>=0; i--)
	{
		q[i] = fw*(t_f64)iq[i];
		fw *= 0x1p-24;
	}
	/* compute PIo2[0,...,jp]*q[jz,...,0] */
	for(i=jz; i>=0; i--)
	{
		for (fw=0.0,k=0; k<=jp && k<=jz-i; k++)
			fw += PIo2[k]*q[i+k];
		fq[jz-i] = fw;
	}
	/* compress fq[] into y[] */
	switch(prec)
	{
	case 0:
		fw = 0.0;
		for (i=jz; i>=0; i--)
			fw += fq[i];
		y[0] = ih==0 ? fw : -fw;
		break;
	case 1:
	case 2:
		fw = 0.0;
		for (i=jz; i>=0; i--)
			fw += fq[i];
		// TODO: drop excess precision here once t_f64 is used
		fw = (t_f64)fw;
		y[0] = ih==0 ? fw : -fw;
		fw = fq[0]-fw;
		for (i=1; i<=jz; i++)
			fw += fq[i];
		y[1] = ih==0 ? fw : -fw;
		break;
	case 3: /* painful */
		for (i=jz; i>0; i--)
		{
			fw      = fq[i-1]+fq[i];
			fq[i]  += fq[i-1]-fw;
			fq[i-1] = fw;
		}
		for (i=jz; i>1; i--)
		{
			fw      = fq[i-1]+fq[i];
			fq[i]  += fq[i-1]-fw;
			fq[i-1] = fw;
		}
		for (fw=0.0,i=jz; i>=2; i--)
			fw += fq[i];
		if (ih==0)
		{
			y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
		}
		else
		{
			y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
		}
	}
	return n&7;
}



/* used in asinl() and acosl() */
/* R(x^2) is a rational approximation of (asin(x)-x)/x^3 with Remez algorithm */

#if LIBCONFIG_USE_FLOAT16
t_f16	__invtrig_polynomial_f16(t_f16 z)
{
	return (t_f16)__invtrig_polynomial_f32(z);
}
#endif

t_f32 __invtrig_polynomial_f32(t_f32 z)
{
	/* coefficients for polynomial_f32(x^2) */
	static const t_f32 pS0 = +1.6666586697e-01;
	static const t_f32 pS1 = -4.2743422091e-02;
	static const t_f32 pS2 = -8.6563630030e-03;
	static const t_f32 qS1 = -7.0662963390e-01;
	t_f32 p, q;
	p = z*(pS0+z*(pS1+z*pS2));
	q = 1.0f+z*qS1;
	return p/q;
}

t_f64 __invtrig_polynomial_f64(t_f64 z)
{
	/* coefficients for polynomial_f32(x^2) */
	static const t_f64 pS0 = +1.66666666666666657415e-01; /* 0x3FC55555, 0x55555555 */
	static const t_f64 pS1 = -3.25565818622400915405e-01; /* 0xBFD4D612, 0x03EB6F7D */
	static const t_f64 pS2 = +2.01212532134862925881e-01; /* 0x3FC9C155, 0x0E884455 */
	static const t_f64 pS3 = -4.00555345006794114027e-02; /* 0xBFA48228, 0xB5688F3B */
	static const t_f64 pS4 = +7.91534994289814532176e-04; /* 0x3F49EFE0, 0x7501B288 */
	static const t_f64 pS5 = +3.47933107596021167570e-05; /* 0x3F023DE1, 0x0DFDF709 */
	static const t_f64 qS1 = -2.40339491173441421878e+00; /* 0xC0033A27, 0x1C8A2D4B */
	static const t_f64 qS2 = +2.02094576023350569471e+00; /* 0x40002AE5, 0x9C598AC8 */
	static const t_f64 qS3 = -6.88283971605453293030e-01; /* 0xBFE6066C, 0x1B8D0159 */
	static const t_f64 qS4 = +7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */
	t_f64 p, q;
	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	return p/q;
}

#if LIBCONFIG_USE_FLOAT80
t_f80	__invtrig_polynomial_f80(t_f80 z)
{
	static const t_f80 pS0 = +1.66666666666666666631e-01L;
	static const t_f80 pS1 = -4.16313987993683104320e-01L;
	static const t_f80 pS2 = +3.69068046323246813704e-01L;
	static const t_f80 pS3 = -1.36213932016738603108e-01L;
	static const t_f80 pS4 = +1.78324189708471965733e-02L;
	static const t_f80 pS5 = -2.19216428382605211588e-04L;
	static const t_f80 pS6 = -7.10526623669075243183e-06L;
	static const t_f80 qS1 = -2.94788392796209867269e+00L;
	static const t_f80 qS2 = +3.27309890266528636716e+00L;
	static const t_f80 qS3 = -1.68285799854822427013e+00L;
	static const t_f80 qS4 = +3.90699412641738801874e-01L;
	static const t_f80 qS5 = -3.14365703596053263322e-02L;
	t_f80 p, q;
	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*(pS5+z*pS6))))));
	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*(qS4+z*qS5))));
	return p/q;
}
#endif

#if LIBCONFIG_USE_FLOAT128
t_f128	__invtrig_polynomial_f128(t_f128 z)
{
	static const t_f128 pS0 = +1.66666666666666666666666666666700314e-01L;
	static const t_f128 pS1 = -7.32816946414566252574527475428622708e-01L;
	static const t_f128 pS2 = +1.34215708714992334609030036562143589e+00L;
	static const t_f128 pS3 = -1.32483151677116409805070261790752040e+00L;
	static const t_f128 pS4 = +7.61206183613632558824485341162121989e-01L;
	static const t_f128 pS5 = -2.56165783329023486777386833928147375e-01L;
	static const t_f128 pS6 = +4.80718586374448793411019434585413855e-02L;
	static const t_f128 pS7 = -4.42523267167024279410230886239774718e-03L;
	static const t_f128 pS8 = +1.44551535183911458253205638280410064e-04L;
	static const t_f128 pS9 = -2.10558957916600254061591040482706179e-07L;
	static const t_f128 qS1 = -4.84690167848739751544716485245697428e+00L;
	static const t_f128 qS2 = +9.96619113536172610135016921140206980e+00L;
	static const t_f128 qS3 = -1.13177895428973036660836798461641458e+01L;
	static const t_f128 qS4 = +7.74004374389488266169304117714658761e+00L;
	static const t_f128 qS5 = -3.25871986053534084709023539900339905e+00L;
	static const t_f128 qS6 = +8.27830318881232209752469022352928864e-01L;
	static const t_f128 qS7 = -1.18768052702942805423330715206348004e-01L;
	static const t_f128 qS8 = +8.32600764660522313269101537926539470e-03L;
	static const t_f128 qS9 = -1.99407384882605586705979504567947007e-04L;
	t_f128 p, q;
	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*(pS5+z*(pS6+z*(pS7+z*(pS8+z*pS9)))))))));
	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*(qS4+z*(qS5+z*(qS6+z*(qS7+z*(qS8+z*qS9))))))));
	return p/q;
}
#endif



/* exp(x)/2 for x >= log(FLT_MAX), slightly better than 0.5f*exp(x/2)*exp(x/2) */
t_f32	__expo2_f32(t_f32 x, t_f32 sign)
{
	/* k is such that k*ln2 has minimal relative error and x - kln2 > log(FLT_MIN) */
	static const int k = 235;
	static const t_f32 kln2 = 0x1.45c778p+7f;
	t_f32 scale;

	/* note that k is odd and scale*scale overflows */
	SET_F32_WORD(scale, (t_u32)(0x7f + k/2) << 23);
	/* exp(x - k ln2) * 2**(k-1) */
	/* in directed rounding correct sign before rounding or overflow is important */
	return F32_Exp(x - kln2) * (sign * scale) * scale;
}

/* exp(x)/2 for x >= log(DBL_MAX), slightly better than 0.5*exp(x/2)*exp(x/2) */
t_f64	__expo2_f64(t_f64 x, t_f64 sign)
{
	/* k is such that k*ln2 has minimal relative error and x - kln2 > log(DBL_MIN) */
	static const int k = 2043;
	static const t_f64 kln2 = 0x1.62066151add8bp+10;
	t_f64 scale;

	/* note that k is odd and scale*scale overflows */
	SET_F64_WORDS(scale, (t_u32)(0x3ff + k/2) << 20, 0);
	/* exp(x - k ln2) * 2**(k-1) */
	/* in directed rounding correct sign before rounding or overflow is important */
	return F64_Exp(x - kln2) * (sign * scale) * scale;
}



#endif
