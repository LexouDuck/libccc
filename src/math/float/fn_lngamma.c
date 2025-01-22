
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(LnGamma, lgamma)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_LNGAMMA(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Hypotenuse(t_f##BITS x) \
{ \
	return F##BITS##_Log(F##BITS##_Abs(F##BITS##_Gamma(x))); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_LNGAMMA(16)
#endif
DEFINEFUNC_FLOAT_LNGAMMA(32)

DEFINEFUNC_FLOAT_LNGAMMA(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LNGAMMA(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LNGAMMA(128)
#endif



#else


/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
** Conversion to t_f32 by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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
t_f32 F32_sin_pi(t_f32 x)
{
	t_f64	y;
	t_sint	n;
	/* spurious inexact if odd int */
	x = 2 * (x * 0.5f - F32_Floor(x * 0.5f)); /* x mod 2.0 */
	n = (t_sint)(x * 4);
	n = (n + 1) / 2;
	y = x - n * 0.5f;
	y *= PI;
	switch (n)
	{
		case 0:	return +__sin_f32(+y);
		case 1:	return +__cos_f32(+y);
		case 2:	return +__sin_f32(-y);
		case 3:	return -__cos_f32(+y);
		default:return +__sin_f32(+y);
	}
}

struct data_lgamma_f32
{
	t_f32	pi;
	t_f32	tc;
	t_f32	tf;
	t_f32	tt;
	t_f32	a[12];
	t_f32	t[15];
	t_f32	u[6];
	t_f32	v[9];
	t_f32	s[7];
	t_f32	r[7];
	t_f32	w[7];
};

static
t_f32 F32_lgammaf_r(t_f32 x, int *signgamp)
{
	static const
	struct data_lgamma_f32 __data_lgamma_f32 =
	{
		.pi = +3.1415927410e+00, /* 0x40490fdb */
		.tc = +1.4616321325e+00, /* 0x3fbb16c3 */
		.tf = -1.2148628384e-01, /* 0xbdf8cdcd */
		.tt = +6.6971006518e-09, /* 0x31e61c52 */ /* tt = -(tail of tf) */
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
			+1.0000000000e+00,
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
			+1.0000000000e+00,
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
			-1.6309292987e-03, /* 0xbad5c4e8 */
		},
	};
	union {t_f32 f; t_u32 i;} u = {x};
	t_f32	t,y,z,p,p1,p2,p3,q,r,w;
	t_f32	nadj = NAN;
	t_u32	ix;
	t_sint	i;
	t_bool	sign;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = (u.i >> 31);
	ix = u.i & ~F32_SIGN_BIT_MASK;
	if (ix >= F32_EXPONENT_MASK)
		return x*x;
	if (ix < 0x35000000) /* |x| < 2**-21, return -log(|x|) */
	{
		if (sign)
		{
			*signgamp = -1;
			x = -x;
		}
		return -F32_Log(x);
	}
	if (sign)
	{
		x = -x;
		t = F32_sin_pi(x);
		if (t == 0.0f) /* -integer */
			return 1.0f / (x - x);
		if (t > 0.0f)
			*signgamp = -1;
		else
			t = -t;
		nadj = F32_Log(__data_lgamma_f32.pi / (t * x));
	}
	/* purge off 1 and 2 */
	if (ix == 0x3F800000 || ix == 0x40000000)
		r = 0;
	else if (ix < 0x40000000) /* for x < 2.0 */
	{
		if (ix <= 0x3F666666)
		{	/* lgamma(x) = lgamma(x+1)-log(x) */
			r = -F32_Log(x);
			if (ix >= 0x3F3B4A20)
			{
				y = 1.0f - x;
				i = 0;
			}
			else if (ix >= 0x3E6D3308)
			{
				y = x - (__data_lgamma_f32.tc-1.0f);
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
			if (ix >= 0x3FDDA618)
			{	/* [1.7316,2] */
				y = 2.0f - x;
				i = 0;
			}
			else if (ix >= 0x3F9DA620)
			{	/* [1.23,1.73] */
				y = x - __data_lgamma_f32.tc;
				i = 1;
			}
			else
			{
				y = x - 1.0f;
				i = 2;
			}
		}
		switch (i)
		{
			case 0:
				z = y*y;
				p1 = __data_lgamma_f32.a[0] + z *
					(__data_lgamma_f32.a[2] + z *
					(__data_lgamma_f32.a[4] + z *
					(__data_lgamma_f32.a[6] + z *
					(__data_lgamma_f32.a[8] + z *
					(__data_lgamma_f32.a[10])))));
				p2 = z *
					(__data_lgamma_f32.a[1] + z *
					(__data_lgamma_f32.a[3] + z *
					(__data_lgamma_f32.a[5] + z *
					(__data_lgamma_f32.a[7] + z *
					(__data_lgamma_f32.a[9] + z *
					(__data_lgamma_f32.a[11]))))));
				p = y * p1 + p2;
				r += p - 0.5f*y;
				break;
			case 1:
				z = y * y;
				w = z * y;
				p1 = __data_lgamma_f32.t[0] + w *
					(__data_lgamma_f32.t[3] + w *
					(__data_lgamma_f32.t[6] + w *
					(__data_lgamma_f32.t[9] + w *
					(__data_lgamma_f32.t[12]))));    /* parallel comp */
				p2 = __data_lgamma_f32.t[1] + w *
					(__data_lgamma_f32.t[4] + w *
					(__data_lgamma_f32.t[7] + w *
					(__data_lgamma_f32.t[10]+ w *
					(__data_lgamma_f32.t[13]))));
				p3 = __data_lgamma_f32.t[2] + w *
					(__data_lgamma_f32.t[5] + w *
					(__data_lgamma_f32.t[8] + w *
					(__data_lgamma_f32.t[11]+ w *
					(__data_lgamma_f32.t[14]))));
				p = z * p1 - (__data_lgamma_f32.tt - w * (p2 + y * p3));
				r += (__data_lgamma_f32.tf + p);
				break;
			case 2:
				p1 = y *
					(__data_lgamma_f32.u[0] + y *
					(__data_lgamma_f32.u[1] + y *
					(__data_lgamma_f32.u[2] + y *
					(__data_lgamma_f32.u[3] + y *
					(__data_lgamma_f32.u[4] + y *
					(__data_lgamma_f32.u[5]))))));
				p2 = 1.0f + y *
					(__data_lgamma_f32.v[1] + y *
					(__data_lgamma_f32.v[2] + y *
					(__data_lgamma_f32.v[3] + y *
					(__data_lgamma_f32.v[4] + y *
					(__data_lgamma_f32.v[5])))));
				r += -0.5f * y + p1 / p2;
				break;
		}
	}
	else if (ix < 0x41000000) /* x < 8.0 */
	{
		i = (int)x;
		y = x - (t_f32)i;
		p = y *
			(__data_lgamma_f32.s[0] + y *
			(__data_lgamma_f32.s[1] + y *
			(__data_lgamma_f32.s[2] + y *
			(__data_lgamma_f32.s[3] + y *
			(__data_lgamma_f32.s[4] + y *
			(__data_lgamma_f32.s[5] + y *
			(__data_lgamma_f32.s[6])))))));
		q = 1.0f + y *
			(__data_lgamma_f32.r[1] + y *
			(__data_lgamma_f32.r[2] + y *
			(__data_lgamma_f32.r[3] + y *
			(__data_lgamma_f32.r[4] + y *
			(__data_lgamma_f32.r[5] + y *
			(__data_lgamma_f32.r[6]))))));
		r = 0.5f * y + p / q;
		z = 1.0f;    /* lgamma(1+s) = log(s) + lgamma(s) */
		switch (i)
		{
			case 7: z *= y + 6.0f;  /* FALLTHRU */
			case 6: z *= y + 5.0f;  /* FALLTHRU */
			case 5: z *= y + 4.0f;  /* FALLTHRU */
			case 4: z *= y + 3.0f;  /* FALLTHRU */
			case 3: z *= y + 2.0f;  /* FALLTHRU */
				r += F32_Log(z);
				break;
		}
	}
	else if (ix < 0x5c800000) /* 8.0 <= x < 2**58 */
	{
		t = F32_Log(x);
		z = 1.0f / x;
		y = z*z;
		w = (__data_lgamma_f32.w[0] + z *
			(__data_lgamma_f32.w[1] + y *
			(__data_lgamma_f32.w[2] + y *
			(__data_lgamma_f32.w[3] + y *
			(__data_lgamma_f32.w[4] + y *
			(__data_lgamma_f32.w[5] + y *
			(__data_lgamma_f32.w[6])))))));
		r = (x - 0.5f) * (t - 1.0f) + w;
	}
	else /* 2**58 <= x <= inf */
		r =  x * (F32_Log(x) - 1.0f);
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
**                         = log(6.3*5.3) + lgamma(5.3)
**                         = log(6.3*5.3*4.3*3.3*2.3) + lgamma(2.3)
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
**              w = w[0] + w[1]*z + w[2]*z  + w[3]*z  + ... + w[6]*z
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
**                       = log(pi/(|x*sin(pi*x)|)) - lgamma(-x);
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

struct data_lgamma_f64
{
	t_f64	pi;
	t_f64	tc;
	t_f64	tf;
	t_f64	tt;
	t_f64	a[12];
	t_f64	t[15];
	t_f64	u[6];
	t_f64	v[9];
	t_f64	s[7];
	t_f64	r[7];
	t_f64	w[7];
};

static
t_f64 F64_lgamma_r(t_f64 x, int *signgamp)
{
	static const
	struct data_lgamma_f64 __data_lgamma_f64 =
	{
		.pi = +3.14159265358979311600e+00, /* 0x400921FB, 0x54442D18 */
		.tc = +1.46163214496836224576e+00, /* 0x3FF762D8, 0x6356BE3F */
		.tf = -1.21486290535849611461e-01, /* 0xBFBF19B9, 0xBCC38A42 */
		.tt = -3.63867699703950536541e-18, /* 0xBC50C7CA, 0xA48A971F */ /* tt = -(tail of tf) */
		.a =
		{
			+7.72156649015328655494e-02, /* 0x3FB3C467, 0xE37DB0C8 */
			+3.22467033424113591611e-01, /* 0x3FD4A34C, 0xC4A60FAD */
			+6.73523010531292681824e-02, /* 0x3FB13E00, 0x1A5562A7 */
			+2.05808084325167332806e-02, /* 0x3F951322, 0xAC92547B */
			+7.38555086081402883957e-03, /* 0x3F7E404F, 0xB68FEFE8 */
			+2.89051383673415629091e-03, /* 0x3F67ADD8, 0xCCB7926B */
			+1.19270763183362067845e-03, /* 0x3F538A94, 0x116F3F5D */
			+5.10069792153511336608e-04, /* 0x3F40B6C6, 0x89B99C00 */
			+2.20862790713908385557e-04, /* 0x3F2CF2EC, 0xED10E54D */
			+1.08011567247583939954e-04, /* 0x3F1C5088, 0x987DFB07 */
			+2.52144565451257326939e-05, /* 0x3EFA7074, 0x428CFA52 */
			+4.48640949618915160150e-05, /* 0x3F07858E, 0x90A45837 */
		},
		.t =
		{
			+4.83836122723810047042e-01, /* 0x3FDEF72B, 0xC8EE38A2 */
			-1.47587722994593911752e-01, /* 0xBFC2E427, 0x8DC6C509 */
			+6.46249402391333854778e-02, /* 0x3FB08B42, 0x94D5419B */
			-3.27885410759859649565e-02, /* 0xBFA0C9A8, 0xDF35B713 */
			+1.79706750811820387126e-02, /* 0x3F9266E7, 0x970AF9EC */
			-1.03142241298341437450e-02, /* 0xBF851F9F, 0xBA91EC6A */
			+6.10053870246291332635e-03, /* 0x3F78FCE0, 0xE370E344 */
			-3.68452016781138256760e-03, /* 0xBF6E2EFF, 0xB3E914D7 */
			+2.25964780900612472250e-03, /* 0x3F6282D3, 0x2E15C915 */
			-1.40346469989232843813e-03, /* 0xBF56FE8E, 0xBF2D1AF1 */
			+8.81081882437654011382e-04, /* 0x3F4CDF0C, 0xEF61A8E9 */
			-5.38595305356740546715e-04, /* 0xBF41A610, 0x9C73E0EC */
			+3.15632070903625950361e-04, /* 0x3F34AF6D, 0x6C0EBBF7 */
			-3.12754168375120860518e-04, /* 0xBF347F24, 0xECC38C38 */
			+3.35529192635519073543e-04, /* 0x3F35FD3E, 0xE8C2D3F4 */
		},
		.u =
		{
			-7.72156649015328655494e-02, /* 0xBFB3C467, 0xE37DB0C8 */
			+6.32827064025093366517e-01, /* 0x3FE4401E, 0x8B005DFF */
			+1.45492250137234768737e+00, /* 0x3FF7475C, 0xD119BD6F */
			+9.77717527963372745603e-01, /* 0x3FEF4976, 0x44EA8450 */
			+2.28963728064692451092e-01, /* 0x3FCD4EAE, 0xF6010924 */
			+1.33810918536787660377e-02, /* 0x3F8B678B, 0xBF2BAB09 */
		},
		.v =
		{
			+1.00000000000000000000e+00,
			+2.45597793713041134822e+00, /* 0x4003A5D7, 0xC2BD619C */
			+2.12848976379893395361e+00, /* 0x40010725, 0xA42B18F5 */
			+7.69285150456672783825e-01, /* 0x3FE89DFB, 0xE45050AF */
			+1.04222645593369134254e-01, /* 0x3FBAAE55, 0xD6537C88 */
			+3.21709242282423911810e-03, /* 0x3F6A5ABB, 0x57D0CF61 */
		},
		.s =
		{
			-7.72156649015328655494e-02, /* 0xBFB3C467, 0xE37DB0C8 */
			+2.14982415960608852501e-01, /* 0x3FCB848B, 0x36E20878 */
			+3.25778796408930981787e-01, /* 0x3FD4D98F, 0x4F139F59 */
			+1.46350472652464452805e-01, /* 0x3FC2BB9C, 0xBEE5F2F7 */
			+2.66422703033638609560e-02, /* 0x3F9B481C, 0x7E939961 */
			+1.84028451407337715652e-03, /* 0x3F5E26B6, 0x7368F239 */
			+3.19475326584100867617e-05, /* 0x3F00BFEC, 0xDD17E945 */
		},
		.r =
		{
			+1.00000000000000000000e+00,
			+1.39200533467621045958e+00, /* 0x3FF645A7, 0x62C4AB74 */
			+7.21935547567138069525e-01, /* 0x3FE71A18, 0x93D3DCDC */
			+1.71933865632803078993e-01, /* 0x3FC601ED, 0xCCFBDF27 */
			+1.86459191715652901344e-02, /* 0x3F9317EA, 0x742ED475 */
			+7.77942496381893596434e-04, /* 0x3F497DDA, 0xCA41A95B */
			+7.32668430744625636189e-06, /* 0x3EDEBAF7, 0xA5B38140 */
		},
		.w =
		{
			+4.18938533204672725052e-01, /* 0x3FDACFE3, 0x90C97D69 */
			+8.33333333333329678849e-02, /* 0x3FB55555, 0x5555553B */
			-2.77777777728775536470e-03, /* 0xBF66C16C, 0x16B02E5C */
			+7.93650558643019558500e-04, /* 0x3F4A019F, 0x98CF38B6 */
			-5.95187557450339963135e-04, /* 0xBF4380CB, 0x8C0FE741 */
			+8.36339918996282139126e-04, /* 0x3F4B67BA, 0x4CDAD5D1 */
			-1.63092934096575273989e-03, /* 0xBF5AB89D, 0x0B9E43E4 */
		},
	};
	union {t_f64 f; t_u64 i;} u = {x};
	t_f64 t,y,z,nadj,p,p1,p2,p3,q,r,w;
	t_u32 ix;
	int sign,i;

	/* purge off +-inf, NaN, +-0, tiny and negative arguments */
	*signgamp = 1;
	sign = u.i>>63;
	ix = u.i>>32 & 0x7fffffff;
	if (ix >= 0x7ff00000)
		return x*x;
	if (ix < (0x3ff-70)<<20)
	{	/* |x|<2**-70, return -F64_Log(|x|) */
		if(sign)
		{
			x = -x;
			*signgamp = -1;
		}
		return -F64_Log(x);
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
		nadj = F64_Log(__data_lgamma_f64.pi/(t*x));
	}

	/* purge off 1 and 2 */
	if ((ix == 0x3ff00000 || ix == 0x40000000) && (t_u32)u.i == 0)
		r = 0;
	/* for x < 2.0 */
	else if (ix < 0x40000000)
	{
		if (ix <= 0x3feccccc)
		{   /* lgamma(x) = lgamma(x+1)-F64_Log(x) */
			r = -F64_Log(x);
			if (ix >= 0x3FE76944)
			{
				y = 1.0 - x;
				i = 0;
			}
			else if (ix >= 0x3FCDA661)
			{
				y = x - (__data_lgamma_f64.tc-1.0);
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
				y = x - __data_lgamma_f64.tc;
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
			z = y * y;
			p1 = __data_lgamma_f64.a[0] + z *
				(__data_lgamma_f64.a[2] + z *
				(__data_lgamma_f64.a[4] + z *
				(__data_lgamma_f64.a[6] + z *
				(__data_lgamma_f64.a[8] + z *
				(__data_lgamma_f64.a[10])))));
			p2 = z *
				(__data_lgamma_f64.a[1] + z *
				(__data_lgamma_f64.a[3] + z *
				(__data_lgamma_f64.a[5] + z *
				(__data_lgamma_f64.a[7] + z *
				(__data_lgamma_f64.a[9] + z *
				(__data_lgamma_f64.a[11]))))));
			p = y * p1 + p2;
			r += (p - 0.5 * y);
			break;
		case 1:
			z = y * y;
			w = z * y;
			p1 = __data_lgamma_f64.t[0] + w *
			 	(__data_lgamma_f64.t[3] + w *
				(__data_lgamma_f64.t[6] + w *
				(__data_lgamma_f64.t[9] + w *
				(__data_lgamma_f64.t[12]))));    /* parallel comp */
			p2 = __data_lgamma_f64.t[1] + w *
			 	(__data_lgamma_f64.t[4] + w *
				(__data_lgamma_f64.t[7] + w *
				(__data_lgamma_f64.t[10]+ w *
				(__data_lgamma_f64.t[13]))));
			p3 = __data_lgamma_f64.t[2] + w *
			 	(__data_lgamma_f64.t[5] + w *
				(__data_lgamma_f64.t[8] + w *
				(__data_lgamma_f64.t[11]+ w *
				(__data_lgamma_f64.t[14]))));
			p = z * p1 - (__data_lgamma_f64.tt - w * (p2 + y * p3));
			r += __data_lgamma_f64.tf + p;
			break;
		case 2:
			p1 = y *
				(__data_lgamma_f64.u[0] + y *
				(__data_lgamma_f64.u[1] + y *
				(__data_lgamma_f64.u[2] + y *
				(__data_lgamma_f64.u[3] + y *
				(__data_lgamma_f64.u[4] + y *
				(__data_lgamma_f64.u[5]))))));
			p2 = 1.0 + y *
				(__data_lgamma_f64.v[1] + y *
				(__data_lgamma_f64.v[2] + y *
				(__data_lgamma_f64.v[3] + y *
				(__data_lgamma_f64.v[4] + y *
				(__data_lgamma_f64.v[5])))));
			r += -0.5*y + p1/p2;
		}
	}
	else if (ix < 0x40200000)
	{	/* x < 8.0 */
		i = (int)x;
		y = x - (t_f64)i;
		p = y *
			(__data_lgamma_f64.s[0] + y *
			(__data_lgamma_f64.s[1] + y *
			(__data_lgamma_f64.s[2] + y *
			(__data_lgamma_f64.s[3] + y *
			(__data_lgamma_f64.s[4] + y *
			(__data_lgamma_f64.s[5] + y *
			(__data_lgamma_f64.s[6])))))));
		q = 1.0+y*
			(__data_lgamma_f64.r[1] + y *
			(__data_lgamma_f64.r[2] + y *
			(__data_lgamma_f64.r[3] + y *
			(__data_lgamma_f64.r[4] + y *
			(__data_lgamma_f64.r[5] + y *
			(__data_lgamma_f64.r[6]))))));
		r = 0.5*y+p/q;
		z = 1.0;    /* lgamma(1+s) = F64_Log(s) + lgamma(s) */
		switch (i)
		{
		case 7: z *= y + 6.0;  /* FALLTHRU */
		case 6: z *= y + 5.0;  /* FALLTHRU */
		case 5: z *= y + 4.0;  /* FALLTHRU */
		case 4: z *= y + 3.0;  /* FALLTHRU */
		case 3: z *= y + 2.0;  /* FALLTHRU */
			r += F64_Log(z);
			break;
		}
	}
	else if (ix < 0x43900000)
	{	/* 8.0 <= x < 2**58 */
		t = F64_Log(x);
		z = 1.0/x;
		y = z*z;
		w = (__data_lgamma_f64.w[0] + z *
			(__data_lgamma_f64.w[1] + y *
			(__data_lgamma_f64.w[2] + y *
			(__data_lgamma_f64.w[3] + y *
			(__data_lgamma_f64.w[4] + y *
			(__data_lgamma_f64.w[5] + y *
			(__data_lgamma_f64.w[6])))))));
		r = (x-0.5)*(t-1.0)+w;
	}
	else                         /* 2**58 <= x <= inf */
		r =  x*(F64_Log(x)-1.0);
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
**                         = log(6.3*5.3) + lgamma(5.3)
**                         = log(6.3*5.3*4.3*3.3*2.3) + lgamma(2.3)
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
**              w = w[0] + w[1]*z + w[2]*z  + w[3]*z  + ... + w[6]*z
**
**   4. For negative x, since (G is gamma function)
**              -x*G(-x)*G(x) = pi/sin(pi*x),
**      we have
**              G(x) = pi/(sin(pi*x)*(-x)*G(-x))
**      since G(-x) is positive, sign(G(x)) = sign(sin(pi*x)) for x<0
**      Hence, for x<0, signgam = sign(sin(pi*x)) and
**              lgamma(x) = log(|Gamma(x)|)
**                       = log(pi/(|x*sin(pi*x)|)) - lgamma(-x);
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
t_f80 F80_sin_pi(t_f80 x)
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

struct data_lgamma_f80
{
	t_f80	pi;
	t_f80	tc;
	t_f80	tf;
	t_f80	tt;
	t_f80	a[6];
	t_f80	b[6];
	t_f80	g[7];
	t_f80	h[7];
	t_f80	u[7];
	t_f80	v[7];
	t_f80	s[7];
	t_f80	r[8];
	t_f80	w[8];
};

static
t_f80 F80_lgammal_r(t_f80 x, int *sg)
{
	static const
	struct data_lgamma_f80 __data_lgamma_f80 =
	{
		.pi = +3.14159265358979323846264L,
		.tc = +1.4616321449683623412626595423257213284682E0L,
		.tf = -1.2148629053584961146050602565082954242826E-1, /* t_f64 precision */
		.tt = +3.3649914684731379602768989080467587736363E-18L, /* tt = (tail of tf), i.e. tf + tt has extended precision. */
		/* lgam ( 1.4616321449683623412626595423257213284682E0 ) = -1.2148629053584960809551455717769158215135617312999903886372437313313530E-1 */
		.a =
		{
			/* lgam(1+x) = 0.5 x + x a(x)/b(x) | -0.268402099609375 <= x <= 0 | peak relative error 6.6e-22 */
			-6.343246574721079391729402781192128239938e+2L,
			+1.856560238672465796768677717168371401378e+3L,
			+2.404733102163746263689288466865843408429e+3L,
			+8.804188795790383497379532868917517596322e+2L,
			+1.135361354097447729740103745999661157426e+2L,
			+3.766956539107615557608581581190400021285e+0L,
		},
		.b =
		{
			+8.214973713960928795704317259806842490498e+3L,
			+1.026343508841367384879065363925870888012e+4L,
			+4.553337477045763320522762343132210919277e+3L,
			+8.506975785032585797446253359230031874803e+2L,
			+6.042447899703295436820744186992189445813e+1L,
			+1.000000000000000000000000000000000000000e+0L,
		},
		.g =
		{
			/* lgam (x + tc) = tf + tt + x g(x)/h(x) | -0.230003726999612341262659542325721328468 <= x <= 0.2699962730003876587373404576742786715318 | peak relative error 2.1e-21 */
			3.645529916721223331888305293534095553827e-18L,
			5.126654642791082497002594216163574795690e+3L,
			8.828603575854624811911631336122070070327e+3L,
			5.464186426932117031234820886525701595203e+3L,
			1.455427403530884193180776558102868592293e+3L,
			1.541735456969245924860307497029155838446e+2L,
			4.335498275274822298341872707453445815118e+0L,
		},
		.h =
		{
			1.059584930106085509696730443974495979641e+4L,
			2.147921653490043010629481226937850618860e+4L,
			1.643014770044524804175197151958100656728e+4L,
			5.869021995186925517228323497501767586078e+3L,
			9.764244777714344488787381271643502742293e+2L,
			6.442485441570592541741092969581997002349e+1L,
			1.000000000000000000000000000000000000000e+0L,
		},
		.u =
		{
			/* lgam (x+1) = -0.5 x + x u(x)/v(x) | -0.100006103515625 <= x <= 0.231639862060546875 | peak relative error 1.3e-21 */
			-8.886217500092090678492242071879342025627e+1L,
			+6.840109978129177639438792958320783599310e+2L,
			+2.042626104514127267855588786511809932433e+3L,
			+1.911723903442667422201651063009856064275e+3L,
			+7.447065275665887457628865263491667767695e+2L,
			+1.132256494121790736268471016493103952637e+2L,
			+4.484398885516614191003094714505960972894e+0L,
		},
		.v =
		{
			+1.150830924194461522996462401210374632929e+3L,
			+3.399692260848747447377972081399737098610e+3L,
			+3.786631705644460255229513563657226008015e+3L,
			+1.966450123004478374557778781564114347876e+3L,
			+4.741359068914069299837355438370682773122e+2L,
			+4.508989649747184050907206782117647852364e+1L,
			+1.000000000000000000000000000000000000000e+0L,
		},
		.s =
		{
			/* lgam (x+2) = .5 x + x s(x)/r(x) | 0 <= x <= 1 | peak relative error 7.2e-22 */
			+1.454726263410661942989109455292824853344e+6L,
			-3.901428390086348447890408306153378922752e+6L,
			-6.573568698209374121847873064292963089438e+6L,
			-3.319055881485044417245964508099095984643e+6L,
			-7.094891568758439227560184618114707107977e+5L,
			-6.263426646464505837422314539808112478303e+4L,
			-1.684926520999477529949915657519454051529e+3L,
		},
		.r =
		{
			-1.883978160734303518163008696712983134698e+7L,
			-2.815206082812062064902202753264922306830e+7L,
			-1.600245495251915899081846093343626358398e+7L,
			-4.310526301881305003489257052083370058799e+6L,
			-5.563807682263923279438235987186184968542e+5L,
			-3.027734654434169996032905158145259713083e+4L,
			-4.501995652861105629217250715790764371267e+2L,
			+1.000000000000000000000000000000000000000e+0L,
		},
		.w =
		{
			/* lgam(x) = ( x - 0.5 ) * log(x) - x + LS2PI + 1/x w(1/x^2) | x >= 8 | Peak relative error 1.51e-21 */
			+4.189385332046727417803e-1L, /* LS2PI - 0.5 */
			+8.333333333333331447505e-2L,
			-2.777777777750349603440e-3L,
			+7.936507795855070755671e-4L,
			-5.952345851765688514613e-4L,
			+8.412723297322498080632e-4L,
			-1.880801938119376907179e-3L,
			+4.885026142432270781165e-3L,
		},
	};
	t_f80 t, y, z, nadj, p, p1, p2, q, r, w;
	union ldshape u = {x};
	t_u32 ix = (u.i.se & 0x7fffU)<<16 | u.i.m>>48;
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
		return -F80_Log(x);
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
		nadj = F80_Log(pi / (t * x));
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
			r = -F80_Log(x);
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
			else /* x < 0.23 */
			{
				y = x;
				i = 2;
			}
		}
		else
		{
			r = 0.0;
			if (ix >= 0x3fffdda6)
			{	/* 1.73162841796875 | [1.7316,2] */
				y = x - 2.0;
				i = 0;
			}
			else if (ix >= 0x3fff9da6)
			{	/* 1.23162841796875 | [1.23,1.73] */
				y = x - tc;
				i = 1;
			}
			else /* [0.9, 1.23] */
			{
				y = x - 1.0;
				i = 2;
			}
		}
		switch (i)
		{
		case 0:
			p1 = __data_lgamma_f80.a[0] + y * 
				(__data_lgamma_f80.a[1] + y * 
				(__data_lgamma_f80.a[2] + y * 
				(__data_lgamma_f80.a[3] + y * 
				(__data_lgamma_f80.a[4] + y *
				(__data_lgamma_f80.a[5])))));
			p2 = __data_lgamma_f80.b[0] + y * 
				(__data_lgamma_f80.b[1] + y * 
				(__data_lgamma_f80.b[2] + y * 
				(__data_lgamma_f80.b[3] + y * 
				(__data_lgamma_f80.b[4] + y))));
			r += 0.5 * y + y * p1/p2;
			break;
		case 1:
			p1 = __data_lgamma_f80.g[0] + y * 
				(__data_lgamma_f80.g[1] + y * 
				(__data_lgamma_f80.g[2] + y * 
				(__data_lgamma_f80.g[3] + y * 
				(__data_lgamma_f80.g[4] + y * 
				(__data_lgamma_f80.g[5] + y *
				(__data_lgamma_f80.g[6]))))));
			p2 = __data_lgamma_f80.h[0] + y * 
				(__data_lgamma_f80.h[1] + y * 
				(__data_lgamma_f80.h[2] + y * 
				(__data_lgamma_f80.h[3] + y * 
				(__data_lgamma_f80.h[4] + y * 
				(__data_lgamma_f80.h[5] + y)))));
			p = tt + y * p1/p2;
			r += (tf + p);
			break;
		case 2:
			p1 = y * 
				(__data_lgamma_f80.u[0] + y * 
				(__data_lgamma_f80.u[1] + y * 
				(__data_lgamma_f80.u[2] + y * 
				(__data_lgamma_f80.u[3] + y * 
				(__data_lgamma_f80.u[4] + y * 
				(__data_lgamma_f80.u[5] + y *
				(__data_lgamma_f80.u[6])))))));
			p2 =
				(__data_lgamma_f80.v[0] + y *) 
				(__data_lgamma_f80.v[1] + y * 
				(__data_lgamma_f80.v[2] + y * 
				(__data_lgamma_f80.v[3] + y * 
				(__data_lgamma_f80.v[4] + y * 
				(__data_lgamma_f80.v[5] + y)))));
			r += (-0.5 * y + p1 / p2);
		}
	}
	else if (ix < 0x40028000)
	{	/* 8.0 */
		/* x < 8.0 */
		i = (int)x;
		y = x - (t_f64)i;
		p = y * 
			(__data_lgamma_f80.s[0] + y * 
			(__data_lgamma_f80.s[1] + y * 
			(__data_lgamma_f80.s[2] + y * 
			(__data_lgamma_f80.s[3] + y * 
			(__data_lgamma_f80.s[4] + y * 
			(__data_lgamma_f80.s[5] + y *
			(__data_lgamma_f80.s[6])))))));
		q = (__data_lgamma_f80.r[0] + y * 
			(__data_lgamma_f80.r[1] + y * 
			(__data_lgamma_f80.r[2] + y * 
			(__data_lgamma_f80.r[3] + y * 
			(__data_lgamma_f80.r[4] + y * 
			(__data_lgamma_f80.r[5] + y * 
			(__data_lgamma_f80.r[6] + y)))))));
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
				r += F80_Log(z);
				break;
		}
	}
	else if (ix < 0x40418000)
	{	/* 2^66 */
		/* 8.0 <= x < 2**66 */
		t = F80_Log(x);
		z = 1.0 / x;
		y = z * z;
		w = (__data_lgamma_f80.w[0] + z * 
			(__data_lgamma_f80.w[1] + y * 
			(__data_lgamma_f80.w[2] + y * 
			(__data_lgamma_f80.w[3] + y * 
			(__data_lgamma_f80.w[4] + y * 
			(__data_lgamma_f80.w[5] + y * 
			(__data_lgamma_f80.w[6] + y *
			(__data_lgamma_f80.w[7])))))));
		r = (x - 0.5) * (t - 1.0) + w;
	}
	else /* 2**66 <= x <= inf */
		r = x * (F80_Log(x) - 1.0);
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
