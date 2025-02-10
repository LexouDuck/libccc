
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Gamma, tgamma)
#else

/*!
**	"A Precision Approximation of the Gamma Function" - Cornelius Lanczos (1964)
**	"Lanczos Implementation of the Gamma Function" - Paul Godfrey (2001)
**	"An Analysis of the Lanczos Gamma Approximation" - Glendon Ralph Pugh (2004)
**
**	approximation method:
**
**	Gamma(x) = (x + g - 0.5) ^ (x - 0.5) * (S(x) / exp(x + g - 0.5))
**	with
**	S(x) ~= [ a0 + a_1/(x+1) + a_2/(x+2) + a_3/(x+3) + ... + a_N/(x+N)
**
**	with a0, a1, a2, a3,.. aN constants which depend on g.
**
**	for x < 0 the following reflection formula is used:
**
**	Gamma(x)*Gamma(-x) = -pi/(x sin(pi x))
**
**	most ideas and constants are from boost and python
*/

#define N 12

static const
struct data_gamma_f64
{
	t_f64 pi;
	t_f64 g;
	t_f64 gmhalf;
	t_f64 Snum[N+1];
	t_f64 Sden[N+1];
	t_f64 fact[23];
}
data_gamma_f64 =
{
	.pi = 3.141592653589793238462643383279502884,
	.g = 6.024680040776729583740234375,
	.gmhalf = 5.524680040776729583740234375,
	.Snum =
	{
		23531376880.410759688572007674451636754734846804940,
		42919803642.649098768957899047001988850926355848959,
		35711959237.355668049440185451547166705960488635843,
		17921034426.037209699919755754458931112671403265390,
		6039542586.3520280050642916443072979210699388420708,
		1439720407.3117216736632230727949123939715485786772,
		248874557.86205415651146038641322942321632125127801,
		31426415.585400194380614231628318205362874684987640,
		2876370.6289353724412254090516208496135991145378768,
		186056.26539522349504029498971604569928220784236328,
		8071.6720023658162106380029022722506138218516325024,
		210.82427775157934587250973392071336271166969580291,
		2.5066282746310002701649081771338373386264310793408,
	},
	.Sden =
	{
		0,
		39916800,
		120543840,
		150917976,
		105258076,
		45995730,
		13339535,
		2637558,
		357423,
		32670,
		1925,
		66,
		1,
	},
	.fact = /* n! for small integer n */
	{
		1,
		1,
		2,
		6,
		24,
		120,
		720,
		5040.0,
		40320.0,
		362880.0,
		3628800.0,
		39916800.0,
		479001600.0,
		6227020800.0,
		87178291200.0,
		1307674368000.0,
		20922789888000.0,
		355687428096000.0,
		6402373705728000.0,
		121645100408832000.0,
		2432902008176640000.0,
		51090942171709440000.0,
		1124000727777607680000.0,
	},
};

/*!
**	sin(pi x) with x > 0x1p-100, if sin(pi*x)==0 the sign is arbitrary
*/
static
t_f64	sinpi(t_f64 x)
{
	int n;
	/* argument reduction: x = |x| mod 2 */
	/* spurious inexact when x is odd int */
	x = x * 0.5;
	x = 2 * (x - F64_Floor(x));
	/* reduce x into [-.25,.25] */
	n = 4 * x;
	n = (n+1)/2;
	x -= n * 0.5;
	x *= data_gamma_f64.pi;
	switch (n)
	{
		default: /* case 4 */
		case 0:	return +__sin_f64(+x, 0, 0);
		case 1:	return +__cos_f64(+x, 0);
		case 2:	return +__sin_f64(-x, 0, 0);
		case 3:	return -__cos_f64(+x, 0);
	}
}

/*!
**	S(x) rational function for positive x
*/
static
t_f64	S(t_f64 x)
{
	t_f64 num = 0, den = 0;
	int i;
	/* to avoid overflow handle large x differently */
	if (x < 8)
		for (i = N; i >= 0; i--)
		{
			num = num * x + data_gamma_f64.Snum[i];
			den = den * x + data_gamma_f64.Sden[i];
		}
	else
		for (i = 0; i <= N; i++)
		{
			num = num / x + data_gamma_f64.Snum[i];
			den = den / x + data_gamma_f64.Sden[i];
		}
	return (num / den);
}

#if LIBCONFIG_USE_FLOAT16
t_f16	F16_Gamma(t_f16 x)
{
	return (t_f16)F64_Gamma((t_f64)x);
}
#endif

t_f32	F32_Gamma(t_f32 x)
{
	return (t_f32)F64_Gamma((t_f64)x);
}

t_f64	F64_Gamma(t_f64 x)
{
	u_cast_f64 u = {x};
	t_f64 abs_x, y;
	t_f64 dy, z, r;
	t_u32 ix = u.as_u >> 32 & 0x7FFFFFFF;
	t_sint sign = u.as_u >> 63;
	/* special cases */
	if (ix >= 0x7FF00000) /* tgamma(nan)=nan, tgamma(inf)=inf, tgamma(-inf)=nan with invalid */
		return x + INFINITY;
	if (x == 0.0)
		return (F64_CopySign(INFINITY, x));
	if (ix < (0x3FF-54)<<20) /* |x| < 2^-54: tgamma(x) ~ 1/x, +-0 raises div-by-zero */
		return (1 / x);
	/* integer arguments */
	/* raise inexact when non-integer */
	if (x == F64_Floor(x))
	{
		if (sign)
			return (0 / 0.0);
		if (x <= sizeof(data_gamma_f64.fact) / sizeof(*data_gamma_f64.fact))
			return data_gamma_f64.fact[(int)x - 1];
	}
	/* x >= +172: tgamma(x)=inf with overflow */
	/* x =< -184: tgamma(x)=+-0 with underflow */
	if (ix >= 0x40670000) /* |x| >= 184 */
	{
		if (sign)
		{
			/* FORCE_EVAL((t_f32)(0x1p-126/x)); */
			if (F64_Floor(x) * 0.5 == F64_Floor(x * 0.5))
				return 0;
			return -0.0;
		}
		x *= 0x1p1023;
		return x;
	}
	abs_x = sign ? -x : x;
	/* handle the error of x + g - 0.5 */
	y = abs_x + data_gamma_f64.gmhalf;
	if (abs_x > data_gamma_f64.gmhalf)
	{
		dy = y - abs_x;
		dy -= data_gamma_f64.gmhalf;
	}
	else
	{
		dy = y - data_gamma_f64.gmhalf;
		dy -= abs_x;
	}
	z = abs_x - 0.5;
	r = S(abs_x) * F64_Exp(-y);
	if (x < 0)
	{
		/* reflection formula for negative x */
		/* sinpi(abs_x) is not 0, integers are already handled */
		r = -data_gamma_f64.pi / (sinpi(abs_x) * abs_x * r);
		dy = -dy;
		z = -z;
	}
	r += dy * (data_gamma_f64.gmhalf + 0.5) * r / y;
	z = F64_Pow(y, 0.5*z);
	y = r * z * z;
	return y;
}


/*
** Copyright (c) 2008 Stephen L. Moshier <steve@moshier.net>
**
** Permission to use, copy, modify, and distribute this software for any
** purpose with or without fee is hereby granted, provided that the above
** copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
** ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
** OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*! Γ(x) Gamma function
**
** SYNOPSIS:
**
** t_f##BITS x, y, tgammal();
**
** y = tgammal( x );
**
**
** DESCRIPTION:
**
** Returns gamma function of the argument.  The result is correctly signed.
**
** Arguments |x| <= 13 are reduced by recurrence and the function
** approximated by a rational function of degree 7/8 in the interval (2,3).
** Large arguments are handled by Stirling's formula.
** Large negative arguments are made positive using a reflection formula.
**
**
** ACCURACY:
**
**                      Relative error:
** arithmetic   domain     # trials      peak         rms
**    IEEE     -40,+40      10000       3.6e-19     7.9e-20
**    IEEE    -1755,+1755   10000       4.8e-18     6.5e-19
**
** Accuracy for large arguments is dominated by error in powl().
*/

#define DEFINEFUNC_FLOAT_GAMMA_LD(BITS) \
/* \
tgamma(x+2) = tgamma(x+2) P(x)/Q(x) \
0 <= x <= 1 \
Relative error \
n=7, d=8 \
Peak error =  1.83e-20 \
Relative error spread =  8.4e-23 \
*/ \
static const \
struct data_gamma_f##BITS \
{ \
	t_f##BITS p[8]; \
	t_f##BITS q[9]; \
	t_f##BITS stir; \
	t_f##BITS maxgaml; \
	t_f##BITS maxstir; \
	t_f##BITS sqtpi; \
	t_f##BITS s[9]; \
	t_f##BITS sn[9]; \
	t_f##BITS pil; \
} \
__data_gamma_f##BITS = \
{ \
	.p = \
	{ \
		+4.212760487471622013093e-5L, \
		+4.542931960608009155600e-4L, \
		+4.092666828394035500949e-3L, \
		+2.385363243461108252554e-2L, \
		+1.113062816019361559013e-1L, \
		+3.629515436640239168939e-1L, \
		+8.378004301573126728826e-1L, \
		+1.000000000000000000009e+0L, \
	}, \
	.q = \
	{ \
		-1.397148517476170440917e-5L, \
		+2.346584059160635244282e-4L, \
		-1.237799246653152231188e-3L, \
		-7.955933682494738320586e-4L, \
		+2.773706565840072979165e-2L, \
		-4.633887671244534213831e-2L, \
		-2.243510905670329164562e-1L, \
		+4.150160950588455434583e-1L, \
		+9.999999999999999999908e-1L, \
	}, \
/* \
	.p = \
	{ \
		-3.01525602666895735709e+0L, \
		-3.25157411956062339893e+1L, \
		-2.92929976820724030353e+2L, \
		-1.70730828800510297666e+3L, \
		-7.96667499622741999770e+3L, \
		-2.59780216007146401957e+4L, \
		-5.99650230220855581642e+4L, \
		-7.15743521530849602425e+4L, \
	}; \
	.q = \
	{ \
		+1.00000000000000000000e+0L, \
		-1.67955233807178858919e+1L, \
		+8.85946791747759881659e+1L, \
		+5.69440799097468430177e+1L, \
		-1.98526250512761318471e+3L, \
		+3.31667508019495079814e+3L, \
		+1.60577839621734713377e+4L, \
		-2.97045081369399940529e+4L, \
		-7.15743521530849602412e+4L, \
	}; \
*/ \
	.maxgaml = 1755.455L, \
	.logpi = 1.14472988584940017414L, \
/* \
Stirling's formula for the gamma function \
tgamma(x) = sqrt(2 pi) x^(x-.5) exp(-x) (1 + 1/x P(1/x)) \
z(x) = x \
13 <= x <= 1024 \
Relative error \
n=8, d=0 \
Peak error =  9.44e-21 \
Relative error spread =  8.8e-4 \
*/ \
	.stir = \
	{ \
		+7.147391378143610789273e-4L, \
		-2.363848809501759061727e-5L, \
		-5.950237554056330156018e-4L, \
		+6.989332260623193171870e-5L, \
		+7.840334842744753003862e-4L, \
		-2.294719747873185405699e-4L, \
		-2.681327161876304418288e-3L, \
		+3.472222222230075327854e-3L, \
		+8.333333333333331800504e-2L, \
	}, \
	.maxstir = 1024.0L, \
	.sqtpi = 2.50662827463100050242e+0L, \
	/* \
	1/tgamma(x) = z P(z) \
	z(x) = 1/x \
	0 < x < 0.03125 \
	Peak relative error 4.2e-23 \
	*/ \
	.s = \
	{ \
		-1.193945051381510095614e-3L, \
		+7.220599478036909672331e-3L, \
		-9.622023360406271645744e-3L, \
		-4.219773360705915470089e-2L, \
		+1.665386113720805206758e-1L, \
		-4.200263503403344054473e-2L, \
		-6.558780715202540684668e-1L, \
		+5.772156649015328608253e-1L, \
		+1.000000000000000000000e+0L, \
	}, \
	/* \
	1/tgamma(-x) = z P(z) \
	z(x) = 1/x \
	0 < x < 0.03125 \
	Peak relative error 5.16e-23 \
	Relative error spread =  2.5e-24 \
	*/ \
	.sn = \
	{ \
		+1.133374167243894382010e-3L, \
		+7.220837261893170325704e-3L, \
		+9.621911155035976733706e-3L, \
		-4.219773343731191721664e-2L, \
		-1.665386113944413519335e-1L, \
		-4.200263503402112910504e-2L, \
		+6.558780715202536547116e-1L, \
		+5.772156649015328608727e-1L, \
		-1.000000000000000000000e+0L, \
	}, \
	.pil = 3.1415926535897932384626L, \
}; \
 \
/*! \
**	Gamma function computed by Stirling's formula. \
*/ \
static \
t_f##BITS	F##BITS##_Gamma_StirlingFormula(t_f##BITS x) \
{ \
	t_f##BITS y, w, v; \
 \
	w = 1.0/x; \
	/* For large x, use rational coefficients from the analytical expansion.  */ \
	if (x > 1024.0) \
		w = (((((6.97281375836585777429e-5L * w \
			+ 7.84039221720066627474e-4L) * w \
			- 2.29472093621399176955e-4L) * w \
			- 2.68132716049382716049e-3L) * w \
			+ 3.47222222222222222222e-3L) * w \
			+ 8.33333333333333333333e-2L) * w \
			+ 1.0; \
	else \
		w = 1.0 + w * __polynomial_f##BITS(w, data_gamma_f##BITS.stir, 8); \
	y = F##BITS##_Exp(x); \
	if (x > data_gamma_f##BITS.maxstir) /* Avoid overflow in pow() */ \
	{ \
		v = F##BITS##_Pow(x, 0.5L * x - 0.25L); \
		y = v * (v / y); \
	} \
	else \
	{ \
		y = F##BITS##_Pow(x, x - 0.5L) / y; \
	} \
	y = data_gamma_f##BITS.sqtpi * y * w; \
	return y; \
} \
 \
t_f##BITS	F##BITS##_Gamma(t_f##BITS x) \
{ \
	t_f##BITS p, q, z, abs_x; \
 \
	if (IS_INF(x)) \
		return x + INFINITY; \
	abs_x = F##BITS##_Abs(x); \
	if (abs_x > 13.0) \
	{ \
		if (x < 0.0) \
		{ \
			p = F##BITS##_Floor(abs_x); \
			z = abs_x - p; \
			if (z == 0) \
				return 0 / z; \
			if (abs_x > data_gamma_f##BITS.maxgaml) \
			{ \
				z = 0; \
			} \
			else \
			{ \
				if (z > 0.5) \
				{ \
					p += 1.0; \
					z = abs_x - p; \
				} \
				z = abs_x * F##BITS##_Sin(data_gamma_f##BITS.pil * z); \
				z = F##BITS##_Abs(z) * F##BITS##_Gamma_StirlingFormula(abs_x); \
				z = data_gamma_f##BITS.pil / z; \
			} \
			if (0.5 * p == F##BITS##_Floor(abs_x * 0.5)) \
				z = -z; \
		} \
		else if (x > data_gamma_f##BITS.maxgaml) \
		{ \
			z = x * 0x1p16383L; \
		} \
		else \
		{ \
			z = F##BITS##_Gamma_StirlingFormula(x); \
		} \
		return z; \
	} \
	z = 1.0; \
	while (x >= 3.0) \
	{ \
		x -= 1.0; \
		z *= x; \
	} \
	while (x < -0.03125L) \
	{ \
		z /= x; \
		x += 1.0; \
	} \
	if (x <= 0.03125L) \
		goto small; \
	while (x < 2.0) \
	{ \
		z /= x; \
		x += 1.0; \
	} \
	if (x == 2.0) \
		return z; \
	x -= 2.0; \
	p = __polynomial_f##BITS(x, __data_gamma_f##BITS.p, 7); \
	q = __polynomial_f##BITS(x, __data_gamma_f##BITS.q, 8); \
	z = z * p / q; \
	return z; \
small: \
	/* z==1 if x was originally +-0 */ \
	if (x == 0 && z != 1) \
		return x / x; \
	if (x < 0.0) \
	{ \
		x = -x; \
		q = z / (x * __polynomial_f##BITS(x, __data_gamma_f##BITS.sn, 8)); \
	} \
	else \
	{ \
		q = z / (x * __polynomial_f##BITS(x, __data_gamma_f##BITS.s, 8)); \
	} \
	return q; \
} \



#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GAMMA_LD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GAMMA_LD(128)
#endif



#endif
