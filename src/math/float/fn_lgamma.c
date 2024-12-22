
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(LnGamma, lgamma)
#else

/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
** Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/

#if 0
{
	.pi = +3.1415927410e+00, /* 0x40490fdb */
	.a =
	{
		+7.7215664089e-02, /* 0x3d9e233f */
		+3.2246702909e-01, /* 0x3ea51a66 */
		+6.7352302372e-02, /* 0x3d89f001 */
		+2.0580807701e-02, /* 0x3ca89915 */
		+7.3855509982e-03, /* 0x3bf2027e */
		+2.8905137442e-03, /* 0x3b3d6ec6 */
		+1.1927076848e-03, /* 0x3a9c54a1 */
		+5.1006977446e-04, /* 0x3a05b634 */
		+2.2086278477e-04, /* 0x39679767 */
		+1.0801156895e-04, /* 0x38e28445 */
		+2.5214456400e-05, /* 0x37d383a2 */
		+4.4864096708e-05, /* 0x383c2c75 */
	},
	.tc = +1.4616321325e+00, /* 0x3fbb16c3 */
	.tf = -1.2148628384e-01, /* 0xbdf8cdcd */
	/* .tt = -(tail of tf) */
	.tt = +6.6971006518e-09, /* 0x31e61c52 */
	.t =
	{
		+4.8383611441e-01, /* 0x3ef7b95e */
		-1.4758771658e-01, /* 0xbe17213c */
		+6.4624942839e-02, /* 0x3d845a15 */
		-3.2788541168e-02, /* 0xbd064d47 */
		+1.7970675603e-02, /* 0x3c93373d */
		-1.0314224288e-02, /* 0xbc28fcfe */
		+6.1005386524e-03, /* 0x3bc7e707 */
		-3.6845202558e-03, /* 0xbb7177fe */
		+2.2596477065e-03, /* 0x3b141699 */
		-1.4034647029e-03, /* 0xbab7f476 */
		+8.8108185446e-04, /* 0x3a66f867 */
		-5.3859531181e-04, /* 0xba0d3085 */
		+3.1563205994e-04, /* 0x39a57b6b */
		-3.1275415677e-04, /* 0xb9a3f927 */
		+3.3552918467e-04, /* 0x39afe9f7 */
	},
	.u =
	{
		-7.7215664089e-02, /* 0xbd9e233f */
		+6.3282704353e-01, /* 0x3f2200f4 */
		+1.4549225569e+00, /* 0x3fba3ae7 */
		+9.7771751881e-01, /* 0x3f7a4bb2 */
		+2.2896373272e-01, /* 0x3e6a7578 */
		+1.3381091878e-02, /* 0x3c5b3c5e */
	},
	.v =
	{
		+1.0,
		+2.4559779167e+00, /* 0x401d2ebe */
		+2.1284897327e+00, /* 0x4008392d */
		+7.6928514242e-01, /* 0x3f44efdf */
		+1.0422264785e-01, /* 0x3dd572af */
		+3.2170924824e-03, /* 0x3b52d5db */
	},
	.s =
	{
		-7.7215664089e-02, /* 0xbd9e233f */
		+2.1498242021e-01, /* 0x3e5c245a */
		+3.2577878237e-01, /* 0x3ea6cc7a */
		+1.4635047317e-01, /* 0x3e15dce6 */
		+2.6642270386e-02, /* 0x3cda40e4 */
		+1.8402845599e-03, /* 0x3af135b4 */
		+3.1947532989e-05, /* 0x3805ff67 */
	},
	.r =
	{
		+1.0,
		+1.3920053244e+00, /* 0x3fb22d3b */
		+7.2193557024e-01, /* 0x3f38d0c5 */
		+1.7193385959e-01, /* 0x3e300f6e */
		+1.8645919859e-02, /* 0x3c98bf54 */
		+7.7794247773e-04, /* 0x3a4beed6 */
		+7.3266842264e-06, /* 0x36f5d7bd */
	},
	.w =
	{
		+4.1893854737e-01, /* 0x3ed67f1d */
		+8.3333335817e-02, /* 0x3daaaaab */
		-2.7777778450e-03, /* 0xbb360b61 */
		+7.9365057172e-04, /* 0x3a500cfd */
		-5.9518753551e-04, /* 0xba1c065c */
		+8.3633989561e-04, /* 0x3a5b3dd2 */
		-1.6309292987e-03; /* 0xbad5c4e8 */
	},
};
#endif

/* sin(pi*x) assuming x > 2^-100, if sin(pi*x)==0 the sign is arbitrary */
static
float F32_sin_pi(float x)
{
	t_f64 y;
	int n;
	/* spurious inexact if odd int */
	x = 2*(x*0.5f - F32_Floor(x*0.5f)); /* x mod 2.0 */

	n = (int)(x*4);
	n = (n+1)/2;
	y = x - n*0.5f;
	y *= PI;
	switch (n)
	{
		case 0:	return +__sin_f32(+y);
		case 1:	return +__cos_f32(+y, 0);
		case 2:	return +__sin_f32(-y);
		case 3:	return -__cos_f32(+y, 0);
		default:
			return NAN;
	}
}

static
float F32_lgammaf_r(float x, int *signgamp)
{
	static const float
	pi  = +3.1415927410e+00, /* 0x40490fdb */

	a0  = +7.7215664089e-02, /* 0x3d9e233f */
	a1  = +3.2246702909e-01, /* 0x3ea51a66 */
	a2  = +6.7352302372e-02, /* 0x3d89f001 */
	a3  = +2.0580807701e-02, /* 0x3ca89915 */
	a4  = +7.3855509982e-03, /* 0x3bf2027e */
	a5  = +2.8905137442e-03, /* 0x3b3d6ec6 */
	a6  = +1.1927076848e-03, /* 0x3a9c54a1 */
	a7  = +5.1006977446e-04, /* 0x3a05b634 */
	a8  = +2.2086278477e-04, /* 0x39679767 */
	a9  = +1.0801156895e-04, /* 0x38e28445 */
	a10 = +2.5214456400e-05, /* 0x37d383a2 */
	a11 = +4.4864096708e-05, /* 0x383c2c75 */

	tc  = +1.4616321325e+00, /* 0x3fbb16c3 */
	tf  = -1.2148628384e-01, /* 0xbdf8cdcd */
	/* tt = -(tail of tf) */
	tt  = +6.6971006518e-09, /* 0x31e61c52 */

	t0  = +4.8383611441e-01, /* 0x3ef7b95e */
	t1  = -1.4758771658e-01, /* 0xbe17213c */
	t2  = +6.4624942839e-02, /* 0x3d845a15 */
	t3  = -3.2788541168e-02, /* 0xbd064d47 */
	t4  = +1.7970675603e-02, /* 0x3c93373d */
	t5  = -1.0314224288e-02, /* 0xbc28fcfe */
	t6  = +6.1005386524e-03, /* 0x3bc7e707 */
	t7  = -3.6845202558e-03, /* 0xbb7177fe */
	t8  = +2.2596477065e-03, /* 0x3b141699 */
	t9  = -1.4034647029e-03, /* 0xbab7f476 */
	t10 = +8.8108185446e-04, /* 0x3a66f867 */
	t11 = -5.3859531181e-04, /* 0xba0d3085 */
	t12 = +3.1563205994e-04, /* 0x39a57b6b */
	t13 = -3.1275415677e-04, /* 0xb9a3f927 */
	t14 = +3.3552918467e-04, /* 0x39afe9f7 */

	u0  = -7.7215664089e-02, /* 0xbd9e233f */
	u1  = +6.3282704353e-01, /* 0x3f2200f4 */
	u2  = +1.4549225569e+00, /* 0x3fba3ae7 */
	u3  = +9.7771751881e-01, /* 0x3f7a4bb2 */
	u4  = +2.2896373272e-01, /* 0x3e6a7578 */
	u5  = +1.3381091878e-02, /* 0x3c5b3c5e */

	v1  = +2.4559779167e+00, /* 0x401d2ebe */
	v2  = +2.1284897327e+00, /* 0x4008392d */
	v3  = +7.6928514242e-01, /* 0x3f44efdf */
	v4  = +1.0422264785e-01, /* 0x3dd572af */
	v5  = +3.2170924824e-03, /* 0x3b52d5db */

	s0  = -7.7215664089e-02, /* 0xbd9e233f */
	s1  = +2.1498242021e-01, /* 0x3e5c245a */
	s2  = +3.2577878237e-01, /* 0x3ea6cc7a */
	s3  = +1.4635047317e-01, /* 0x3e15dce6 */
	s4  = +2.6642270386e-02, /* 0x3cda40e4 */
	s5  = +1.8402845599e-03, /* 0x3af135b4 */
	s6  = +3.1947532989e-05, /* 0x3805ff67 */

	r1  = +1.3920053244e+00, /* 0x3fb22d3b */
	r2  = +7.2193557024e-01, /* 0x3f38d0c5 */
	r3  = +1.7193385959e-01, /* 0x3e300f6e */
	r4  = +1.8645919859e-02, /* 0x3c98bf54 */
	r5  = +7.7794247773e-04, /* 0x3a4beed6 */
	r6  = +7.3266842264e-06, /* 0x36f5d7bd */

	w0  = +4.1893854737e-01, /* 0x3ed67f1d */
	w1  = +8.3333335817e-02, /* 0x3daaaaab */
	w2  = -2.7777778450e-03, /* 0xbb360b61 */
	w3  = +7.9365057172e-04, /* 0x3a500cfd */
	w4  = -5.9518753551e-04, /* 0xba1c065c */
	w5  = +8.3633989561e-04, /* 0x3a5b3dd2 */
	w6  = -1.6309292987e-03; /* 0xbad5c4e8 */

	union {float f; uint32_t i;} u = {x};
	float t,y,z,nadj,p,p1,p2,p3,q,r,w;
	uint32_t ix;
	int i,sign;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = u.i>>31;
	ix = u.i & 0x7fffffff;
	if (ix >= 0x7f800000)
		return x*x;
	if (ix < 0x35000000)
	{	/* |x| < 2**-21, return -log(|x|) */
		if (sign)
		{
			*signgamp = -1;
			x = -x;
		}
		return -F32_Ln(x);
	}
	if (sign)
	{
		x = -x;
		t = F32_sin_pi(x);
		if (t == 0.0f) /* -integer */
			return 1.0f/(x-x);
		if (t > 0.0f)
			*signgamp = -1;
		else
			t = -t;
		nadj = F32_Ln(pi/(t*x));
	}
	/* purge off 1 and 2 */
	if (ix == 0x3f800000 || ix == 0x40000000)
		r = 0;
	/* for x < 2.0 */
	else if (ix < 0x40000000)
	{
		if (ix <= 0x3f666666)
		{	/* lgamma(x) = lgamma(x+1)-log(x) */
			r = -F32_Ln(x);
			if (ix >= 0x3f3b4a20)
			{
				y = 1.0f - x;
				i = 0;
			}
			else if (ix >= 0x3e6d3308)
			{
				y = x - (tc-1.0f);
				i = 1;
			}
			else
			{
				y = x;
				i = 2;
			}
		}
		else
		{
			r = 0.0f;
			if (ix >= 0x3fdda618)
			{	/* [1.7316,2] */
				y = 2.0f - x;
				i = 0;
			}
			else if (ix >= 0x3F9da620)
			{	/* [1.23,1.73] */
				y = x - tc;
				i = 1;
			}
			else
			{
				y = x - 1.0f;
				i = 2;
			}
		}
		switch(i)
		{
			case 0:
				z = y*y;
				p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*a10))));
				p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*a11)))));
				p = y*p1+p2;
				r += p - 0.5f*y;
				break;
			case 1:
				z = y*y;
				w = z*y;
				p1 = t0+w*(t3+w*(t6+w*(t9 +w*t12)));    /* parallel comp */
				p2 = t1+w*(t4+w*(t7+w*(t10+w*t13)));
				p3 = t2+w*(t5+w*(t8+w*(t11+w*t14)));
				p = z*p1-(tt-w*(p2+y*p3));
				r += (tf + p);
				break;
			case 2:
				p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*u5)))));
				p2 = 1.0f+y*(v1+y*(v2+y*(v3+y*(v4+y*v5))));
				r += -0.5f*y + p1/p2;
				break;
		}
	}
	else if (ix < 0x41000000) /* x < 8.0 */
	{
		i = (int)x;
		y = x - (float)i;
		p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
		q = 1.0f+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*r6)))));
		r = 0.5f*y+p/q;
		z = 1.0f;    /* lgamma(1+s) = log(s) + lgamma(s) */
		switch (i)
		{
			case 7: z *= y + 6.0f;  /* FALLTHRU */
			case 6: z *= y + 5.0f;  /* FALLTHRU */
			case 5: z *= y + 4.0f;  /* FALLTHRU */
			case 4: z *= y + 3.0f;  /* FALLTHRU */
			case 3: z *= y + 2.0f;  /* FALLTHRU */
				r += F32_Ln(z);
				break;
		}
	}
	else if (ix < 0x5c800000) /* 8.0 <= x < 2**58 */
	{
		t = F32_Ln(x);
		z = 1.0f/x;
		y = z*z;
		w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*w6)))));
		r = (x-0.5f)*(t-1.0f)+w;
	}
	else /* 2**58 <= x <= inf */
		r =  x*(F32_Ln(x)-1.0f);
	if (sign)
		r = nadj - r;
	return r;
}

t_f32	F32_LnGamma(t_f32 x)
{
	int __signgam;
	return F32_lgammaf_r(x, &__signgam);
}

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

/*! lgamma_r(x, signgamp)
** Reentrant version of the logarithm of the Gamma function
** with user provide pointer for the sign of Gamma(x).
**
** Method:
**   1. Argument Reduction for 0 < x <= 8
**      Since gamma(1+s)=s*gamma(s), for x in [0,8], we may
**      reduce x to a number in [1.5,2.5] by
**              lgamma(1+s) = log(s) + lgamma(s)
**      for example,
**              lgamma(7.3) = log(6.3) + lgamma(6.3)
**                          = log(6.3*5.3) + lgamma(5.3)
**                          = log(6.3*5.3*4.3*3.3*2.3) + lgamma(2.3)
**   2. Polynomial approximation of lgamma around its
**      minimun ymin=1.461632144968362245 to maintain monotonicity.
**      On [ymin-0.23, ymin+0.27] (i.e., [1.23164,1.73163]), use
**              Let z = x-ymin;
**              lgamma(x) = -1.214862905358496078218 + z^2*poly(z)
**      where
**              poly(z) is a 14 degree polynomial.
**   2. Rational approximation in the primary interval [2,3]
**      We use the following approximation:
**              s = x-2.0;
**              lgamma(x) = 0.5*s + s*P(s)/Q(s)
**      with accuracy
**              |P/Q - (lgamma(x)-0.5s)| < 2**-61.71
**      Our algorithms are based on the following observation
**
**                             zeta(2)-1    2    zeta(3)-1    3
** lgamma(2+s) = s*(1-Euler) + --------- * s  -  --------- * s  + ...
**                                 2                 3
**
**      where Euler = 0.5771... is the Euler constant, which is very
**      close to 0.5.
**
**   3. For x>=8, we have
**      lgamma(x)~(x-0.5)log(x)-x+0.5*log(2pi)+1/(12x)-1/(360x**3)+....
**      (better formula:
**         lgamma(x)~(x-0.5)*(log(x)-1)-.5*(log(2pi)-1) + ...)
**      Let z = 1/x, then we approximation
**              f(z) = lgamma(x) - (x-0.5)(log(x)-1)
**      by
**                                  3       5             11
**              w = w0 + w1*z + w2*z  + w3*z  + ... + w6*z
**      where
**              |w - f(z)| < 2**-58.74
**
**   4. For negative x, since (G is gamma function)
**              -x*G(-x)*G(x) = pi/sin(pi*x),
**      we have
**              G(x) = pi/(sin(pi*x)*(-x)*G(-x))
**      since G(-x) is positive, sign(G(x)) = sign(sin(pi*x)) for x<0
**      Hence, for x<0, signgam = sign(sin(pi*x)) and
**              lgamma(x) = log(|Gamma(x)|)
**                        = log(pi/(|x*sin(pi*x)|)) - lgamma(-x);
**      Note: one should avoid compute pi*(-x) directly in the
**            computation of sin(pi*(-x)).
**
**   5. Special Cases
**              lgamma(2+s) ~ s*(1-Euler) for tiny s
**              lgamma(1) = lgamma(2) = 0
**              lgamma(x) ~ -log(|x|) for tiny x
**              lgamma(0) = lgamma(neg.integer) = inf and raise divide-by-zero
**              lgamma(inf) = inf
**              lgamma(-inf) = inf (bug for bug compatible with C99!?)
**
*/



/* sin(pi*x) assuming x > 2^-100, if sin(pi*x)==0 the sign is arbitrary */
static
t_f64 F64_sin_pi(t_f64 x)
{
	int n;

	/* spurious inexact if odd int */
	x = 2.0*(x*0.5 - F64_Floor(x*0.5));  /* x mod 2.0 */

	n = (int)(x*4.0);
	n = (n+1)/2;
	x -= n*0.5f;
	x *= PI;

	switch (n)
	{
	default: /* case 4: */
	case 0: return +__sin_f64(+x, 0.0, 0);
	case 1: return +__cos_f64(+x, 0.0);
	case 2: return +__sin_f64(-x, 0.0, 0);
	case 3: return -__cos_f64(+x, 0.0);
	}
}

static
t_f64 F64_lgamma_r(t_f64 x, int *signgamp)
{
	static const double
	pi  = +3.14159265358979311600e+00, /* 0x400921FB, 0x54442D18 */

	a0  = +7.72156649015328655494e-02, /* 0x3FB3C467, 0xE37DB0C8 */
	a1  = +3.22467033424113591611e-01, /* 0x3FD4A34C, 0xC4A60FAD */
	a2  = +6.73523010531292681824e-02, /* 0x3FB13E00, 0x1A5562A7 */
	a3  = +2.05808084325167332806e-02, /* 0x3F951322, 0xAC92547B */
	a4  = +7.38555086081402883957e-03, /* 0x3F7E404F, 0xB68FEFE8 */
	a5  = +2.89051383673415629091e-03, /* 0x3F67ADD8, 0xCCB7926B */
	a6  = +1.19270763183362067845e-03, /* 0x3F538A94, 0x116F3F5D */
	a7  = +5.10069792153511336608e-04, /* 0x3F40B6C6, 0x89B99C00 */
	a8  = +2.20862790713908385557e-04, /* 0x3F2CF2EC, 0xED10E54D */
	a9  = +1.08011567247583939954e-04, /* 0x3F1C5088, 0x987DFB07 */
	a10 = +2.52144565451257326939e-05, /* 0x3EFA7074, 0x428CFA52 */
	a11 = +4.48640949618915160150e-05, /* 0x3F07858E, 0x90A45837 */

	tc  = +1.46163214496836224576e+00, /* 0x3FF762D8, 0x6356BE3F */
	tf  = -1.21486290535849611461e-01, /* 0xBFBF19B9, 0xBCC38A42 */
	/* tt = -(tail of tf) */
	tt  = -3.63867699703950536541e-18, /* 0xBC50C7CA, 0xA48A971F */

	t0  = +4.83836122723810047042e-01, /* 0x3FDEF72B, 0xC8EE38A2 */
	t1  = -1.47587722994593911752e-01, /* 0xBFC2E427, 0x8DC6C509 */
	t2  = +6.46249402391333854778e-02, /* 0x3FB08B42, 0x94D5419B */
	t3  = -3.27885410759859649565e-02, /* 0xBFA0C9A8, 0xDF35B713 */
	t4  = +1.79706750811820387126e-02, /* 0x3F9266E7, 0x970AF9EC */
	t5  = -1.03142241298341437450e-02, /* 0xBF851F9F, 0xBA91EC6A */
	t6  = +6.10053870246291332635e-03, /* 0x3F78FCE0, 0xE370E344 */
	t7  = -3.68452016781138256760e-03, /* 0xBF6E2EFF, 0xB3E914D7 */
	t8  = +2.25964780900612472250e-03, /* 0x3F6282D3, 0x2E15C915 */
	t9  = -1.40346469989232843813e-03, /* 0xBF56FE8E, 0xBF2D1AF1 */
	t10 = +8.81081882437654011382e-04, /* 0x3F4CDF0C, 0xEF61A8E9 */
	t11 = -5.38595305356740546715e-04, /* 0xBF41A610, 0x9C73E0EC */
	t12 = +3.15632070903625950361e-04, /* 0x3F34AF6D, 0x6C0EBBF7 */
	t13 = -3.12754168375120860518e-04, /* 0xBF347F24, 0xECC38C38 */
	t14 = +3.35529192635519073543e-04, /* 0x3F35FD3E, 0xE8C2D3F4 */

	u0  = -7.72156649015328655494e-02, /* 0xBFB3C467, 0xE37DB0C8 */
	u1  = +6.32827064025093366517e-01, /* 0x3FE4401E, 0x8B005DFF */
	u2  = +1.45492250137234768737e+00, /* 0x3FF7475C, 0xD119BD6F */
	u3  = +9.77717527963372745603e-01, /* 0x3FEF4976, 0x44EA8450 */
	u4  = +2.28963728064692451092e-01, /* 0x3FCD4EAE, 0xF6010924 */
	u5  = +1.33810918536787660377e-02, /* 0x3F8B678B, 0xBF2BAB09 */

	v1  = +2.45597793713041134822e+00, /* 0x4003A5D7, 0xC2BD619C */
	v2  = +2.12848976379893395361e+00, /* 0x40010725, 0xA42B18F5 */
	v3  = +7.69285150456672783825e-01, /* 0x3FE89DFB, 0xE45050AF */
	v4  = +1.04222645593369134254e-01, /* 0x3FBAAE55, 0xD6537C88 */
	v5  = +3.21709242282423911810e-03, /* 0x3F6A5ABB, 0x57D0CF61 */

	s0  = -7.72156649015328655494e-02, /* 0xBFB3C467, 0xE37DB0C8 */
	s1  = +2.14982415960608852501e-01, /* 0x3FCB848B, 0x36E20878 */
	s2  = +3.25778796408930981787e-01, /* 0x3FD4D98F, 0x4F139F59 */
	s3  = +1.46350472652464452805e-01, /* 0x3FC2BB9C, 0xBEE5F2F7 */
	s4  = +2.66422703033638609560e-02, /* 0x3F9B481C, 0x7E939961 */
	s5  = +1.84028451407337715652e-03, /* 0x3F5E26B6, 0x7368F239 */
	s6  = +3.19475326584100867617e-05, /* 0x3F00BFEC, 0xDD17E945 */

	r1  = +1.39200533467621045958e+00, /* 0x3FF645A7, 0x62C4AB74 */
	r2  = +7.21935547567138069525e-01, /* 0x3FE71A18, 0x93D3DCDC */
	r3  = +1.71933865632803078993e-01, /* 0x3FC601ED, 0xCCFBDF27 */
	r4  = +1.86459191715652901344e-02, /* 0x3F9317EA, 0x742ED475 */
	r5  = +7.77942496381893596434e-04, /* 0x3F497DDA, 0xCA41A95B */
	r6  = +7.32668430744625636189e-06, /* 0x3EDEBAF7, 0xA5B38140 */

	w0  = +4.18938533204672725052e-01, /* 0x3FDACFE3, 0x90C97D69 */
	w1  = +8.33333333333329678849e-02, /* 0x3FB55555, 0x5555553B */
	w2  = -2.77777777728775536470e-03, /* 0xBF66C16C, 0x16B02E5C */
	w3  = +7.93650558643019558500e-04, /* 0x3F4A019F, 0x98CF38B6 */
	w4  = -5.95187557450339963135e-04, /* 0xBF4380CB, 0x8C0FE741 */
	w5  = +8.36339918996282139126e-04, /* 0x3F4B67BA, 0x4CDAD5D1 */
	w6  = -1.63092934096575273989e-03; /* 0xBF5AB89D, 0x0B9E43E4 */

	union {t_f64 f; uint64_t i;} u = {x};
	t_f64 t,y,z,nadj,p,p1,p2,p3,q,r,w;
	uint32_t ix;
	int sign,i;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = u.i>>63;
	ix = u.i>>32 & 0x7fffffff;
	if (ix >= 0x7ff00000)
		return x*x;
	if (ix < (0x3ff-70)<<20)
	{	/* |x|<2**-70, return -F64_Ln(|x|) */
		if(sign)
		{
			x = -x;
			*signgamp = -1;
		}
		return -F64_Ln(x);
	}
	if (sign)
	{
		x = -x;
		t = F64_sin_pi(x);
		if (t == 0.0) /* -integer */
			return 1.0/(x-x);
		if (t > 0.0)
			*signgamp = -1;
		else
			t = -t;
		nadj = F64_Ln(pi/(t*x));
	}

	/* purge off 1 and 2 */
	if ((ix == 0x3ff00000 || ix == 0x40000000) && (uint32_t)u.i == 0)
		r = 0;
	/* for x < 2.0 */
	else if (ix < 0x40000000)
	{
		if (ix <= 0x3feccccc)
		{   /* lgamma(x) = lgamma(x+1)-F64_Ln(x) */
			r = -F64_Ln(x);
			if (ix >= 0x3FE76944)
			{
				y = 1.0 - x;
				i = 0;
			}
			else if (ix >= 0x3FCDA661)
			{
				y = x - (tc-1.0);
				i = 1;
			}
			else
			{
				y = x;
				i = 2;
			}
		}
		else
		{
			r = 0.0;
			if (ix >= 0x3FFBB4C3)
			{	/* [1.7316,2] */
				y = 2.0 - x;
				i = 0;
			}
			else if(ix >= 0x3FF3B4C4)
			{	/* [1.23,1.73] */
				y = x - tc;
				i = 1;
			}
			else
			{
				y = x - 1.0;
				i = 2;
			}
		}
		switch (i)
		{
		case 0:
			z = y*y;
			p1 = a0+z*(a2+z*(a4+z*(a6+z*(a8+z*a10))));
			p2 = z*(a1+z*(a3+z*(a5+z*(a7+z*(a9+z*a11)))));
			p = y*p1+p2;
			r += (p-0.5*y);
			break;
		case 1:
			z = y*y;
			w = z*y;
			p1 = t0+w*(t3+w*(t6+w*(t9 +w*t12)));    /* parallel comp */
			p2 = t1+w*(t4+w*(t7+w*(t10+w*t13)));
			p3 = t2+w*(t5+w*(t8+w*(t11+w*t14)));
			p = z*p1-(tt-w*(p2+y*p3));
			r += tf + p;
			break;
		case 2:
			p1 = y*(u0+y*(u1+y*(u2+y*(u3+y*(u4+y*u5)))));
			p2 = 1.0+y*(v1+y*(v2+y*(v3+y*(v4+y*v5))));
			r += -0.5*y + p1/p2;
		}
	}
	else if (ix < 0x40200000)
	{	/* x < 8.0 */
		i = (int)x;
		y = x - (t_f64)i;
		p = y*(s0+y*(s1+y*(s2+y*(s3+y*(s4+y*(s5+y*s6))))));
		q = 1.0+y*(r1+y*(r2+y*(r3+y*(r4+y*(r5+y*r6)))));
		r = 0.5*y+p/q;
		z = 1.0;    /* lgamma(1+s) = F64_Ln(s) + lgamma(s) */
		switch (i)
		{
		case 7: z *= y + 6.0;  /* FALLTHRU */
		case 6: z *= y + 5.0;  /* FALLTHRU */
		case 5: z *= y + 4.0;  /* FALLTHRU */
		case 4: z *= y + 3.0;  /* FALLTHRU */
		case 3: z *= y + 2.0;  /* FALLTHRU */
			r += F64_Ln(z);
			break;
		}
	}
	else if (ix < 0x43900000)
	{	/* 8.0 <= x < 2**58 */
		t = F64_Ln(x);
		z = 1.0/x;
		y = z*z;
		w = w0+z*(w1+y*(w2+y*(w3+y*(w4+y*(w5+y*w6)))));
		r = (x-0.5)*(t-1.0)+w;
	}
	else                         /* 2**58 <= x <= inf */
		r =  x*(F64_Ln(x)-1.0);
	if (sign)
		r = nadj - r;
	return r;
}

t_f64	F64_LnGamma(t_f64 x)
{
	int __signgam;
	return F64_lgamma_r(x, &__signgam);
}



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
/*! lgammal(x)
** Reentrant version of the logarithm of the Gamma function
** with user provide pointer for the sign of Gamma(x).
**
** Method:
**   1. Argument Reduction for 0 < x <= 8
**      Since gamma(1+s)=s*gamma(s), for x in [0,8], we may
**      reduce x to a number in [1.5,2.5] by
**              lgamma(1+s) = log(s) + lgamma(s)
**      for example,
**              lgamma(7.3) = log(6.3) + lgamma(6.3)
**                          = log(6.3*5.3) + lgamma(5.3)
**                          = log(6.3*5.3*4.3*3.3*2.3) + lgamma(2.3)
**   2. Polynomial approximation of lgamma around its
**      minimun ymin=1.461632144968362245 to maintain monotonicity.
**      On [ymin-0.23, ymin+0.27] (i.e., [1.23164,1.73163]), use
**              Let z = x-ymin;
**              lgamma(x) = -1.214862905358496078218 + z^2*poly(z)
**   2. Rational approximation in the primary interval [2,3]
**      We use the following approximation:
**              s = x-2.0;
**              lgamma(x) = 0.5*s + s*P(s)/Q(s)
**      Our algorithms are based on the following observation
**
**                             zeta(2)-1    2    zeta(3)-1    3
** lgamma(2+s) = s*(1-Euler) + --------- * s  -  --------- * s  + ...
**                                 2                 3
**
**      where Euler = 0.5771... is the Euler constant, which is very
**      close to 0.5.
**
**   3. For x>=8, we have
**      lgamma(x)~(x-0.5)log(x)-x+0.5*log(2pi)+1/(12x)-1/(360x**3)+....
**      (better formula:
**         lgamma(x)~(x-0.5)*(log(x)-1)-.5*(log(2pi)-1) + ...)
**      Let z = 1/x, then we approximation
**              f(z) = lgamma(x) - (x-0.5)(log(x)-1)
**      by
**                                  3       5             11
**              w = w0 + w1*z + w2*z  + w3*z  + ... + w6*z
**
**   4. For negative x, since (G is gamma function)
**              -x*G(-x)*G(x) = pi/sin(pi*x),
**      we have
**              G(x) = pi/(sin(pi*x)*(-x)*G(-x))
**      since G(-x) is positive, sign(G(x)) = sign(sin(pi*x)) for x<0
**      Hence, for x<0, signgam = sign(sin(pi*x)) and
**              lgamma(x) = log(|Gamma(x)|)
**                        = log(pi/(|x*sin(pi*x)|)) - lgamma(-x);
**      Note: one should avoid compute pi*(-x) directly in the
**            computation of sin(pi*(-x)).
**
**   5. Special Cases
**              lgamma(2+s) ~ s*(1-Euler) for tiny s
**              lgamma(1)=lgamma(2)=0
**              lgamma(x) ~ -log(x) for tiny x
**              lgamma(0) = lgamma(inf) = inf
**              lgamma(-integer) = +-inf
**
*/

#if LIBCONFIG_USE_FLOAT80
/* sin(pi*x) assuming x > 2^-1000, if sin(pi*x)==0 the sign is arbitrary */
static
long double F80_sin_pi(long double x)
{
	int n;
	/* spurious inexact if odd int */
	x *= 0.5;
	x = 2.0*(x - F80_Floor(x));  /* x mod 2.0 */
	n = (int)(x*4.0);
	n = (n+1)/2;
	x -= n*0.5f;
	x *= PI;
	switch (n)
	{
		default: /* case 4: */
		case 0: return +__sin_f80(+x, 0.0, 0);
		case 1: return +__cos_f80(+x, 0.0);
		case 2: return +__sin_f80(-x, 0.0, 0);
		case 3: return -__cos_f80(+x, 0.0);
	}
}

static
long double F80_lgammal_r(long double x, int *sg)
{
	static const long double
	pi = 3.14159265358979323846264L,

	/* lgam(1+x) = 0.5 x + x a(x)/b(x) | -0.268402099609375 <= x <= 0 | peak relative error 6.6e-22 */
	a0 = -6.343246574721079391729402781192128239938E2L,
	a1 = +1.856560238672465796768677717168371401378E3L,
	a2 = +2.404733102163746263689288466865843408429E3L,
	a3 = +8.804188795790383497379532868917517596322E2L,
	a4 = +1.135361354097447729740103745999661157426E2L,
	a5 = +3.766956539107615557608581581190400021285E0L,

	b0 = +8.214973713960928795704317259806842490498E3L,
	b1 = +1.026343508841367384879065363925870888012E4L,
	b2 = +4.553337477045763320522762343132210919277E3L,
	b3 = +8.506975785032585797446253359230031874803E2L,
	b4 = +6.042447899703295436820744186992189445813E1L,
	/* b5 = +1.000000000000000000000000000000000000000E0 */


	tc = +1.4616321449683623412626595423257213284682E0L,
	tf = -1.2148629053584961146050602565082954242826E-1, /* double precision */
	/* tt = (tail of tf), i.e. tf + tt has extended precision. */
	tt = 3.3649914684731379602768989080467587736363E-18L,
	/* lgam ( 1.4616321449683623412626595423257213284682E0 ) = -1.2148629053584960809551455717769158215135617312999903886372437313313530E-1 */

	/* lgam (x + tc) = tf + tt + x g(x)/h(x) | -0.230003726999612341262659542325721328468 <= x <= 0.2699962730003876587373404576742786715318 | peak relative error 2.1e-21 */
	g0 = 3.645529916721223331888305293534095553827E-18L,
	g1 = 5.126654642791082497002594216163574795690E3L,
	g2 = 8.828603575854624811911631336122070070327E3L,
	g3 = 5.464186426932117031234820886525701595203E3L,
	g4 = 1.455427403530884193180776558102868592293E3L,
	g5 = 1.541735456969245924860307497029155838446E2L,
	g6 = 4.335498275274822298341872707453445815118E0L,

	h0 = 1.059584930106085509696730443974495979641E4L,
	h1 = 2.147921653490043010629481226937850618860E4L,
	h2 = 1.643014770044524804175197151958100656728E4L,
	h3 = 5.869021995186925517228323497501767586078E3L,
	h4 = 9.764244777714344488787381271643502742293E2L,
	h5 = 6.442485441570592541741092969581997002349E1L,
/*	h6 = 1.000000000000000000000000000000000000000E0L, */

	/* lgam (x+1) = -0.5 x + x u(x)/v(x) | -0.100006103515625 <= x <= 0.231639862060546875 | peak relative error 1.3e-21 */
	u0 = -8.886217500092090678492242071879342025627E1L,
	u1 = +6.840109978129177639438792958320783599310E2L,
	u2 = +2.042626104514127267855588786511809932433E3L,
	u3 = +1.911723903442667422201651063009856064275E3L,
	u4 = +7.447065275665887457628865263491667767695E2L,
	u5 = +1.132256494121790736268471016493103952637E2L,
	u6 = +4.484398885516614191003094714505960972894E0L,

	v0 = +1.150830924194461522996462401210374632929E3L,
	v1 = +3.399692260848747447377972081399737098610E3L,
	v2 = +3.786631705644460255229513563657226008015E3L,
	v3 = +1.966450123004478374557778781564114347876E3L,
	v4 = +4.741359068914069299837355438370682773122E2L,
	v5 = +4.508989649747184050907206782117647852364E1L,
/*	v6 = +1.000000000000000000000000000000000000000E0L, */

	/* lgam (x+2) = .5 x + x s(x)/r(x) | 0 <= x <= 1 | peak relative error 7.2e-22 */
	s0 = +1.454726263410661942989109455292824853344E6L,
	s1 = -3.901428390086348447890408306153378922752E6L,
	s2 = -6.573568698209374121847873064292963089438E6L,
	s3 = -3.319055881485044417245964508099095984643E6L,
	s4 = -7.094891568758439227560184618114707107977E5L,
	s5 = -6.263426646464505837422314539808112478303E4L,
	s6 = -1.684926520999477529949915657519454051529E3L,

	r0 = -1.883978160734303518163008696712983134698E7L,
	r1 = -2.815206082812062064902202753264922306830E7L,
	r2 = -1.600245495251915899081846093343626358398E7L,
	r3 = -4.310526301881305003489257052083370058799E6L,
	r4 = -5.563807682263923279438235987186184968542E5L,
	r5 = -3.027734654434169996032905158145259713083E4L,
	r6 = -4.501995652861105629217250715790764371267E2L,
/*	r6 = +1.000000000000000000000000000000000000000E0L, */

	/* lgam(x) = ( x - 0.5 ) * log(x) - x + LS2PI + 1/x w(1/x^2) | x >= 8 | Peak relative error 1.51e-21
	w0 = LS2PI - 0.5 */
	w0 = +4.189385332046727417803e-1L,
	w1 = +8.333333333333331447505E-2L,
	w2 = -2.777777777750349603440E-3L,
	w3 = +7.936507795855070755671E-4L,
	w4 = -5.952345851765688514613E-4L,
	w5 = +8.412723297322498080632E-4L,
	w6 = -1.880801938119376907179E-3L,
	w7 = +4.885026142432270781165E-3L;

	long double t, y, z, nadj, p, p1, p2, q, r, w;
	union ldshape u = {x};
	uint32_t ix = (u.i.se & 0x7fffU)<<16 | u.i.m>>48;
	int sign = u.i.se >> 15;
	int i;

	*sg = 1;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	if (ix >= 0x7fff0000)
		return x * x;
	if (ix < 0x3fc08000)
	{	/* |x|<2**-63, return -log(|x|) */
		if (sign)
		{
			*sg = -1;
			x = -x;
		}
		return -F80_Ln(x);
	}
	if (sign)
	{
		x = -x;
		t = F80_sin_pi(x);
		if (t == 0.0)
			return 1.0 / (x-x); /* -integer */
		if (t > 0.0)
			*sg = -1;
		else
			t = -t;
		nadj = F80_Ln(pi / (t * x));
	}

	/* purge off 1 and 2 (so the sign is ok with downward rounding) */
	if ((ix == 0x3fff8000 || ix == 0x40008000) && u.i.m == 0)
	{
		r = 0;
	}
	else if (ix < 0x40008000)
	{	/* x < 2.0 */
		if (ix <= 0x3ffee666)
		{	/* 8.99993896484375e-1 */
			/* lgamma(x) = lgamma(x+1) - log(x) */
			r = -F80_Ln(x);
			if (ix >= 0x3ffebb4a)
			{	/* 7.31597900390625e-1 */
				y = x - 1.0;
				i = 0;
			}
			else if (ix >= 0x3ffced33)
			{	/* 2.31639862060546875e-1 */
				y = x - (tc - 1.0);
				i = 1;
			}
			else { /* x < 0.23 */
				y = x;
				i = 2;
			}
		}
		else
		{
			r = 0.0;
			if (ix >= 0x3fffdda6)
			{	/* 1.73162841796875 */
				/* [1.7316,2] */
				y = x - 2.0;
				i = 0;
			}
			else if (ix >= 0x3fff9da6)
			{	/* 1.23162841796875 */
				/* [1.23,1.73] */
				y = x - tc;
				i = 1;
			}
			else
			{
				/* [0.9, 1.23] */
				y = x - 1.0;
				i = 2;
			}
		}
		switch (i)
		{
		case 0:
			p1 = a0 + y * (a1 + y * (a2 + y * (a3 + y * (a4 + y * a5))));
			p2 = b0 + y * (b1 + y * (b2 + y * (b3 + y * (b4 + y))));
			r += 0.5 * y + y * p1/p2;
			break;
		case 1:
			p1 = g0 + y * (g1 + y * (g2 + y * (g3 + y * (g4 + y * (g5 + y * g6)))));
			p2 = h0 + y * (h1 + y * (h2 + y * (h3 + y * (h4 + y * (h5 + y)))));
			p = tt + y * p1/p2;
			r += (tf + p);
			break;
		case 2:
			p1 = y * (u0 + y * (u1 + y * (u2 + y * (u3 + y * (u4 + y * (u5 + y * u6))))));
			p2 = v0 + y * (v1 + y * (v2 + y * (v3 + y * (v4 + y * (v5 + y)))));
			r += (-0.5 * y + p1 / p2);
		}
	}
	else if (ix < 0x40028000)
	{	/* 8.0 */
		/* x < 8.0 */
		i = (int)x;
		y = x - (double)i;
		p = y * (s0 + y * (s1 + y * (s2 + y * (s3 + y * (s4 + y * (s5 + y * s6))))));
		q = r0 + y * (r1 + y * (r2 + y * (r3 + y * (r4 + y * (r5 + y * (r6 + y))))));
		r = 0.5 * y + p / q;
		z = 1.0;
		/* lgamma(1+s) = log(s) + lgamma(s) */
		switch (i)
		{
			case 7:	z *= (y + 6.0); /* FALLTHRU */
			case 6:	z *= (y + 5.0); /* FALLTHRU */
			case 5:	z *= (y + 4.0); /* FALLTHRU */
			case 4:	z *= (y + 3.0); /* FALLTHRU */
			case 3:	z *= (y + 2.0); /* FALLTHRU */
				r += F80_Ln(z);
				break;
		}
	}
	else if (ix < 0x40418000)
	{	/* 2^66 */
		/* 8.0 <= x < 2**66 */
		t = F80_Ln(x);
		z = 1.0 / x;
		y = z * z;
		w = w0 + z * (w1 + y * (w2 + y * (w3 + y * (w4 + y * (w5 + y * (w6 + y * w7))))));
		r = (x - 0.5) * (t - 1.0) + w;
	}
	else /* 2**66 <= x <= inf */
		r = x * (F80_Ln(x) - 1.0);
	if (sign)
		r = nadj - r;
	return r;
}

t_f80	F80_LnGamma(t_f80 x)
{
	int __signgam;
	return F80_lgammal_r(x, &__signgam);
}
#endif

#if LIBCONFIG_USE_FLOAT128
t_f128	F128_LnGamma(t_f128 x)
{
	int __signgam;
	return F80_lgammal_r(x, &__signgam);
}
#endif



#endif
