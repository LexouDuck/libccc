
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Floor, floor)
#else

/*
"A Precision Approximation of the Gamma Function" - Cornelius Lanczos (1964)
"Lanczos Implementation of the Gamma Function" - Paul Godfrey (2001)
"An Analysis of the Lanczos Gamma Approximation" - Glendon Ralph Pugh (2004)

approximation method:

                        (x - 0.5)         S(x)
Gamma(x) = (x + g - 0.5)         *  ----------------
                                    exp(x + g - 0.5)

with
                 a1      a2      a3            aN
S(x) ~= [ a0 + ----- + ----- + ----- + ... + ----- ]
               x + 1   x + 2   x + 3         x + N

with a0, a1, a2, a3,.. aN constants which depend on g.

for x < 0 the following reflection formula is used:

Gamma(x)*Gamma(-x) = -pi/(x sin(pi x))

most ideas and constants are from boost and python
*/

static const double pi = 3.141592653589793238462643383279502884;

/* sin(pi x) with x > 0x1p-100, if sin(pi*x)==0 the sign is arbitrary */
static
double sinpi(double x)
{
	int n;
	/* argument reduction: x = |x| mod 2 */
	/* spurious inexact when x is odd int */
	x = x * 0.5;
	x = 2 * (x - floor(x));
	/* reduce x into [-.25,.25] */
	n = 4 * x;
	n = (n+1)/2;
	x -= n * 0.5;
	x *= pi;
	switch (n)
	{
		default: /* case 4 */
		case 0:	return +__sin(x, 0, 0);
		case 1:	return +__cos(x, 0);
		case 2:	return +__sin(-x, 0, 0);
		case 3:	return -__cos(x, 0);
	}
}

#define N 12
//static const double g = 6.024680040776729583740234375;
static const double gmhalf = 5.524680040776729583740234375;
static const double Snum[N+1] =
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
};
static const double Sden[N+1] =
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
};
/* n! for small integer n */
static const double fact[] =
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
};

/* S(x) rational function for positive x */
static double S(double x)
{
	t_f64 num = 0, den = 0;
	int i;
	/* to avoid overflow handle large x differently */
	if (x < 8)
		for (i = N; i >= 0; i--)
		{
			num = num * x + Snum[i];
			den = den * x + Sden[i];
		}
	else
		for (i = 0; i <= N; i++)
		{
			num = num / x + Snum[i];
			den = den / x + Sden[i];
		}
	return num/den;
}

double tgamma(double x)
{
	union {double f; uint64_t i;} u = {x};
	double absx, y;
	t_f64 dy, z, r;
	uint32_t ix = u.i>>32 & 0x7fffffff;
	int sign = u.i>>63;
	/* special cases */
	if (ix >= 0x7ff00000)
		/* tgamma(nan)=nan, tgamma(inf)=inf, tgamma(-inf)=nan with invalid */
		return x + INFINITY;
	if (ix < (0x3ff-54)<<20)
		/* |x| < 2^-54: tgamma(x) ~ 1/x, +-0 raises div-by-zero */
		return 1/x;
	/* integer arguments */
	/* raise inexact when non-integer */
	if (x == floor(x))
	{
		if (sign)
			return 0/0.0;
		if (x <= sizeof fact/sizeof *fact)
			return fact[(int)x - 1];
	}
	/* x >= 172: tgamma(x)=inf with overflow */
	/* x =< -184: tgamma(x)=+-0 with underflow */
	if (ix >= 0x40670000)
	{ /* |x| >= 184 */
		if (sign)
		{
			FORCE_EVAL((float)(0x1p-126/x));
			if (floor(x) * 0.5 == floor(x * 0.5))
				return 0;
			return -0.0;
		}
		x *= 0x1p1023;
		return x;
	}
	absx = sign ? -x : x;
	/* handle the error of x + g - 0.5 */
	y = absx + gmhalf;
	if (absx > gmhalf)
	{
		dy = y - absx;
		dy -= gmhalf;
	}
	else
	{
		dy = y - gmhalf;
		dy -= absx;
	}
	z = absx - 0.5;
	r = S(absx) * exp(-y);
	if (x < 0)
	{
		/* reflection formula for negative x */
		/* sinpi(absx) is not 0, integers are already handled */
		r = -pi / (sinpi(absx) * absx * r);
		dy = -dy;
		z = -z;
	}
	r += dy * (gmhalf+0.5) * r / y;
	z = pow(y, 0.5*z);
	y = r * z * z;
	return y;
}

#if 0
double __lgamma_r(double x, int *sign)
{
	double r, absx;

	*sign = 1;

	/* special cases */
	if (!isfinite(x))
		/* lgamma(nan)=nan, lgamma(+-inf)=inf */
		return x*x;

	/* integer arguments */
	if (x == floor(x) && x <= 2)
	{
		/* n <= 0: lgamma(n)=inf with divbyzero */
		/* n == 1,2: lgamma(n)=0 */
		if (x <= 0)
			return 1/0.0;
		return 0;
	}

	absx = fabs(x);

	/* lgamma(x) ~ -log(|x|) for tiny |x| */
	if (absx < 0x1p-54)
	{
		*sign = 1 - 2*!!signbit(x);
		return -log(absx);
	}

	/* use tgamma for smaller |x| */
	if (absx < 128)
	{
		x = tgamma(x);
		*sign = 1 - 2*!!signbit(x);
		return log(fabs(x));
	}

	/* second term (log(S)-g) could be more precise here.. */
	/* or with stirling: (|x|-0.5)*(log(|x|)-1) + poly(1/|x|) */
	r = (absx-0.5)*(log(absx+gmhalf)-1) + (log(S(absx)) - (gmhalf+0.5));
	if (x < 0)
	{
		/* reflection formula for negative x */
		x = sinpi(absx);
		*sign = 2*!!signbit(x) - 1;
		r = log(pi/(fabs(x)*absx)) - r;
	}
	return r;
}

weak_alias(__lgamma_r, lgamma_r);
#endif

/*
 * Copyright (c) 2008 Stephen L. Moshier <steve@moshier.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 *      Gamma function
 *
 *
 * SYNOPSIS:
 *
 * long double x, y, tgammal();
 *
 * y = tgammal( x );
 *
 *
 * DESCRIPTION:
 *
 * Returns gamma function of the argument.  The result is
 * correctly signed.
 *
 * Arguments |x| <= 13 are reduced by recurrence and the function
 * approximated by a rational function of degree 7/8 in the
 * interval (2,3).  Large arguments are handled by Stirling's
 * formula. Large negative arguments are made positive using
 * a reflection formula.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     -40,+40      10000       3.6e-19     7.9e-20
 *    IEEE    -1755,+1755   10000       4.8e-18     6.5e-19
 *
 * Accuracy for large arguments is dominated by error in powl().
 *
 */

/*
tgamma(x+2) = tgamma(x+2) P(x)/Q(x)
0 <= x <= 1
Relative error
n=7, d=8
Peak error =  1.83e-20
Relative error spread =  8.4e-23
*/
static const long double P[8] =
{
	+4.212760487471622013093E-5L,
	+4.542931960608009155600E-4L,
	+4.092666828394035500949E-3L,
	+2.385363243461108252554E-2L,
	+1.113062816019361559013E-1L,
	+3.629515436640239168939E-1L,
	+8.378004301573126728826E-1L,
	+1.000000000000000000009E0L,
};
static const long double Q[9] =
{
	-1.397148517476170440917E-5L,
	+2.346584059160635244282E-4L,
	-1.237799246653152231188E-3L,
	-7.955933682494738320586E-4L,
	+2.773706565840072979165E-2L,
	-4.633887671244534213831E-2L,
	-2.243510905670329164562E-1L,
	+4.150160950588455434583E-1L,
	+9.999999999999999999908E-1L,
};

/*
static const long double P[] =
{
-3.01525602666895735709e0L,
-3.25157411956062339893e1L,
-2.92929976820724030353e2L,
-1.70730828800510297666e3L,
-7.96667499622741999770e3L,
-2.59780216007146401957e4L,
-5.99650230220855581642e4L,
-7.15743521530849602425e4L
};
static const long double Q[] =
{
+1.00000000000000000000e0L,
-1.67955233807178858919e1L,
+8.85946791747759881659e1L,
+5.69440799097468430177e1L,
-1.98526250512761318471e3L,
+3.31667508019495079814e3L,
+1.60577839621734713377e4L,
-2.97045081369399940529e4L,
-7.15743521530849602412e4L
};
*/
#define MAXGAML 1755.455L
/*static const long double LOGPI = 1.14472988584940017414L;*/

/* Stirling's formula for the gamma function
tgamma(x) = sqrt(2 pi) x^(x-.5) exp(-x) (1 + 1/x P(1/x))
z(x) = x
13 <= x <= 1024
Relative error
n=8, d=0
Peak error =  9.44e-21
Relative error spread =  8.8e-4
*/
static const long double STIR[9] =
{
	+7.147391378143610789273E-4L,
	-2.363848809501759061727E-5L,
	-5.950237554056330156018E-4L,
	+6.989332260623193171870E-5L,
	+7.840334842744753003862E-4L,
	-2.294719747873185405699E-4L,
	-2.681327161876304418288E-3L,
	+3.472222222230075327854E-3L,
	+8.333333333333331800504E-2L,
};

#define MAXSTIR 1024.0L
static const long double SQTPI = 2.50662827463100050242E0L;

/* 1/tgamma(x) = z P(z)
 * z(x) = 1/x
 * 0 < x < 0.03125
 * Peak relative error 4.2e-23
 */
static const long double S[9] =
{
	-1.193945051381510095614E-3L,
	+7.220599478036909672331E-3L,
	-9.622023360406271645744E-3L,
	-4.219773360705915470089E-2L,
	+1.665386113720805206758E-1L,
	-4.200263503403344054473E-2L,
	-6.558780715202540684668E-1L,
	+5.772156649015328608253E-1L,
	+1.000000000000000000000E0L,
};

/* 1/tgamma(-x) = z P(z)
 * z(x) = 1/x
 * 0 < x < 0.03125
 * Peak relative error 5.16e-23
 * Relative error spread =  2.5e-24
 */
static const long double SN[9] =
{
	+1.133374167243894382010E-3L,
	+7.220837261893170325704E-3L,
	+9.621911155035976733706E-3L,
	-4.219773343731191721664E-2L,
	-1.665386113944413519335E-1L,
	-4.200263503402112910504E-2L,
	+6.558780715202536547116E-1L,
	+5.772156649015328608727E-1L,
	-1.000000000000000000000E0L,
};

static const long double PIL = 3.1415926535897932384626L;

/* Gamma function computed by Stirling's formula.
 */
static
long double stirf(long double x)
{
	long double y, w, v;

	w = 1.0/x;
	/* For large x, use rational coefficients from the analytical expansion.  */
	if (x > 1024.0)
		w = (((((6.97281375836585777429E-5L * w
			+ 7.84039221720066627474E-4L) * w
			- 2.29472093621399176955E-4L) * w
			- 2.68132716049382716049E-3L) * w
			+ 3.47222222222222222222E-3L) * w
			+ 8.33333333333333333333E-2L) * w
			+ 1.0;
	else
		w = 1.0 + w * __polevll(w, STIR, 8);
	y = expl(x);
	if (x > MAXSTIR) /* Avoid overflow in pow() */
	{
		v = powl(x, 0.5L * x - 0.25L);
		y = v * (v / y);
	}
	else
	{
		y = powl(x, x - 0.5L) / y;
	}
	y = SQTPI * y * w;
	return y;
}

long double tgammal(long double x)
{
	long double p, q, z;

	if (!isfinite(x))
		return x + INFINITY;
	q = fabsl(x);
	if (q > 13.0)
	{
		if (x < 0.0)
		{
			p = floorl(q);
			z = q - p;
			if (z == 0)
				return 0 / z;
			if (q > MAXGAML)
			{
				z = 0;
			}
			else
			{
				if (z > 0.5)
				{
					p += 1.0;
					z = q - p;
				}
				z = q * sinl(PIL * z);
				z = fabsl(z) * stirf(q);
				z = PIL/z;
			}
			if (0.5 * p == floorl(q * 0.5))
				z = -z;
		}
		else if (x > MAXGAML)
		{
			z = x * 0x1p16383L;
		}
		else
		{
			z = stirf(x);
		}
		return z;
	}
	z = 1.0;
	while (x >= 3.0)
	{
		x -= 1.0;
		z *= x;
	}
	while (x < -0.03125L)
	{
		z /= x;
		x += 1.0;
	}
	if (x <= 0.03125L)
		goto small;
	while (x < 2.0)
	{
		z /= x;
		x += 1.0;
	}
	if (x == 2.0)
		return z;
	x -= 2.0;
	p = __polevll(x, P, 7);
	q = __polevll(x, Q, 8);
	z = z * p / q;
	return z;
small:
	/* z==1 if x was originally +-0 */
	if (x == 0 && z != 1)
		return x / x;
	if (x < 0.0)
	{
		x = -x;
		q = z / (x * __polevll(x, SN, 8));
	}
	else
		q = z / (x * __polevll(x, S, 8));
	return q;
}



#if LIBCONFIG_USE_FLOAT128
#warning "not implemented"
#endif



#endif
