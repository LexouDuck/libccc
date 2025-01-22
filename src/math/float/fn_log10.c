
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Log10, log10)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_LOG10(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Log10(t_f##BITS x) \
{ \
	return (F##BITS##_Log(x) / LN_10); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_LOG10(16)
#endif
DEFINEFUNC_FLOAT_LOG10(32)

DEFINEFUNC_FLOAT_LOG10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG10(128)
#endif



#else

static const
struct data_log10_f32
{
	t_f32	ivln10hi;
	t_f32	ivln10lo;
	t_f32	log10_2hi;
	t_f32	log10_2lo;
	t_f32	lg[5];
}
__data_log10_f32 =
{
	.ivln10hi  =  4.3432617188e-01, /* 0x3ede6000 */
	.ivln10lo  = -3.1689971365e-05, /* 0xb804ead9 */
	.log10_2hi =  3.0102920532e-01, /* 0x3e9a2080 */
	.log10_2lo =  7.9034151668e-07, /* 0x355427db */
	/* |(log(1+s)-log(1-s))/s - Lg(s)| < 2**-34.24 (~[-4.95e-11, 4.97e-11]). */
	.lg =
	{
		0x1.0p0,
		0xAAAAAA.0p-24, /* 0.66666662693 */
		0xCCCE13.0p-25, /* 0.40000972152 */
		0x91E9EE.0p-25, /* 0.28498786688 */
		0xF89E26.0p-26, /* 0.24279078841 */
	},
};

t_f32	F32_Log10(t_f32 x)
{
	union {t_f32 f; t_u32 i;} u = {x};
	t_f32 hfsq,f,s,s2,s4,R,t1,t2,dk,hi,lo;
	t_u32 ix;
	int k;

	ix = u.i;
	k = 0;
	if (ix < 0x00800000 || ix >> 31) /* x < 2**-126  */
	{
		if (ix << 1 == 0)
			return -1 / (x * x); /* log(+-0)=-inf */
		if (ix >> 31)
			return (x - x) / 0.0f; /* log(-#) = NaN */
		/* subnormal number, scale up x */
		k -= 25;
		x *= 0x1p25f;
		u.f = x;
		ix = u.i;
	}
	else if (ix >= 0x7F800000)
		return x;
	else if (ix == 0x3F800000)
		return 0;
	/* reduce x into [sqrt(2)/2, sqrt(2)] */
	ix += 0x3F800000 - 0x3F3504F3;
	k += (int)(ix >> 23) - 0x7F;
	ix = (ix & 0x007FFFFF) + 0x3F3504F3;
	u.i = ix;
	x = u.f;

	f = x - 1.0f;
	s = f / (2.0f + f);
	s2 = s * s;
	s4 = s2 * s2;
	t1= s4 * (__data_log10_f32.lg[2] + s4 * __data_log10_f32.lg[4]);
	t2= s2 * (__data_log10_f32.lg[1] + s4 * __data_log10_f32.lg[3]);
	R = t2 + t1;
	hfsq = 0.5f * f * f;

	hi = f - hfsq;
	u.f = hi;
	u.i &= 0xFFFFF000;
	hi = u.f;
	lo = f - hi - hfsq + s * (hfsq + R);
	dk = k;
	return (
		__data_log10_f32.log10_2lo * dk +
		__data_log10_f32.ivln10lo * (lo + hi) +
		__data_log10_f32.ivln10hi * lo +
		__data_log10_f32.ivln10hi * hi +
		__data_log10_f32.log10_2hi * dk);
}


/*
** Return the base 10 logarithm of x.  See log.c for most comments.
**
** Reduce x to 2^k (1+f) and calculate r = log(1+f) - f + f*f/2
** as in log.c, then combine and scale in extra precision:
**    log10(x) = (f - f*f/2 + r)/log(10) + k*log10(2)
*/

static const
struct data_log10_f64
{
	t_f64	ivln10hi;
	t_f64	ivln10lo;
	t_f64	log10_2hi;
	t_f64	log10_2lo;
	t_f64	lg[8];
}
__data_log10_f64 =
{
	.ivln10hi  = 4.34294481878168880939e-01, /* 0x3FDBCB7B, 0x15200000 */
	.ivln10lo  = 2.50829467116452752298e-11, /* 0x3DBB9438, 0xCA9AADD5 */
	.log10_2hi = 3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
	.log10_2lo = 3.69423907715893078616e-13, /* 0x3D59FEF3, 0x11F12B36 */
	.lg =
	{
		0x1.0p0,
		6.666666666666735130e-01, /* 3FE55555 55555593 */
		3.999999999940941908e-01, /* 3FD99999 9997FA04 */
		2.857142874366239149e-01, /* 3FD24924 94229359 */
		2.222219843214978396e-01, /* 3FCC71C5 1D8E78AF */
		1.818357216161805012e-01, /* 3FC74664 96CB03DE */
		1.531383769920937332e-01, /* 3FC39A09 D078C69F */
		1.479819860511658591e-01, /* 3FC2F112 DF3E5244 */
	},
};

t_f64	F64_Log10(t_f64 x)
{
	union {t_f64 f; t_u64 i;} u = {x};
	t_f64 hfsq,f,s,s2,s4,w,R,t1,t2,dk,y,hi,lo,val_hi,val_lo;
	t_u32 hx;
	int k;

	hx = u.i>>32;
	k = 0;
	if (hx < 0x00100000 || hx >> 31)
	{
		if (u.i << 1 == 0)
			return -1 / (x * x); /* log(+-0)=-inf */
		if (hx >> 31)
			return (x - x) / 0.0; /* log(-#) = NaN */
		/* subnormal number, scale x up */
		k -= 54;
		x *= 0x1p54;
		u.f = x;
		hx = u.i>>32;
	}
	else if (hx >= 0x7FF00000)
		return x;
	else if (hx == 0x3FF00000 && u.i << 32 == 0)
		return 0;

	/* reduce x into [sqrt(2)/2, sqrt(2)] */
	hx += 0x3FF00000 - 0x3FE6A09E;
	k += (int)(hx >> 20) - 0x3FF;
	hx = (hx & 0x000FFFFF) + 0x3FE6A09E;
	u.i = (t_u64)hx << 32 | (u.i & 0xFFFFFFFF);
	x = u.f;

	f = x - 1.0;
	hfsq = 0.5 * f * f;
	s = f / (2.0 + f);
	s2 = s * s;
	s4 = s2 * s2;
	t1 = s4 * (__data_log10_f64.lg[2] + s4 * (__data_log10_f64.lg[4] + s4 * __data_log10_f64.lg[6]));
	t2 = s2 * (__data_log10_f64.lg[1] + s4 * (__data_log10_f64.lg[3] + s4 * (__data_log10_f64.lg[5] + s4 * __data_log10_f64.lg[7])));
	R = t2 + t1;

	/* See log2.c for details. */
	/* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
	hi = f - hfsq;
	u.f = hi;
	u.i &= (t_u64)-1<<32;
	hi = u.f;
	lo = f - hi - hfsq + s*(hfsq+R);

	/* val_hi+val_lo ~ log10(1+f) + k*log10(2) */
	val_hi = hi*__data_log10_f64.ivln10hi;
	dk = k;
	y = dk*__data_log10_f64.log10_2hi;
	val_lo = dk*__data_log10_f64.log10_2lo + (lo+hi)*__data_log10_f64.ivln10lo + lo*__data_log10_f64.ivln10hi;

	/*
	**	Extra precision in for adding y is not strictly needed
	**	since there is no very large cancellation near x = sqrt(2) or
	**	x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
	**	with some parallelism and it reduces the error for many args.
	*/
	w = y + val_hi;
	val_lo += (y - w) + val_hi;
	val_hi = w;

	return val_lo + val_hi;
}


/*
**      Common logarithm, t_f80 precision
**
**
** SYNOPSIS:
**
** t_f80 x, y, log10l();
**
** y = log10l( x );
**
**
** DESCRIPTION:
**
** Returns the base 10 logarithm of x.
**
** The argument is separated into its exponent and fractional
** parts.  If the exponent is between -1 and +1, the logarithm
** of the fraction is approximated by
**
**     log(1+x) = x - 0.5 x**2 + x**3 P(x)/Q(x).
**
** Otherwise, setting  z = 2(x-1)/x+1),
**
**     log(x) = z + z**3 P(z)/Q(z).
**
**
** ACCURACY:
**
**                      Relative error:
** arithmetic   domain     # trials      peak         rms
**    IEEE      0.5, 2.0     30000      9.0e-20     2.6e-20
**    IEEE     exp(+-10000)  30000      6.0e-20     2.3e-20
**
** In the tests over the interval exp(+-10000), the logarithms
** of the random arguments were uniformly distributed over
** [-10000, +10000].
**
** ERROR MESSAGES:
**
** log singularity:  x = 0; returns MINLOG
** log domain:       x < 0; returns MINLOG
*/

#define DEFINEFUNC_FLOAT_LOG10(BITS) \
static const \
struct data_log10_f##BITS \
{ \
	t_f##BITS	P[7]; \
	t_f##BITS	Q[8]; \
	t_f##BITS	R[4]; \
	t_f##BITS	S[4]; \
	t_f##BITS	L102A; \
	t_f##BITS	L102B; \
	t_f##BITS	L10EA; \
	t_f##BITS	L10EB; \
	t_f##BITS	SQRTH; \
} \
__data_log10_f##BITS = \
{ \
	/* Coefficients for log(1+x) = x - x**2/2 + x**3 P(x)/Q(x) \
	** 1/sqrt(2) <= x < sqrt(2) \
	** Theoretical peak relative error = 6.2e-22 \
	*/ \
	.P = \
	{ \
		+4.9962495940332550844739e-1L, \
		+1.0767376367209449010438e+1L, \
		+7.7671073698359539859595e+1L, \
		+2.5620629828144409632571e+2L, \
		+4.2401812743503691187826e+2L, \
		+3.4258224542413922935104e+2L, \
		+1.0747524399916215149070e+2L, \
	}, \
	.Q = \
	{ \
		+1.0000000000000000000000e+0L, \
		+2.3479774160285863271658e+1L, \
		+1.9444210022760132894510e+2L, \
		+7.7952888181207260646090e+2L, \
		+1.6911722418503949084863e+3L, \
		+2.0307734695595183428202e+3L, \
		+1.2695660352705325274404e+3L, \
		+3.2242573199748645407652e+2L, \
	}, \
	/* Coefficients for log(x) = z + z^3 P(z^2)/Q(z^2), \
	** where z = 2(x-1)/(x+1) \
	** 1/sqrt(2) <= x < sqrt(2) \
	** Theoretical peak relative error = 6.16e-22 \
	*/ \
	.R = \
	{ \
		+1.9757429581415468984296e-3L, \
		-7.1990767473014147232598e-1L, \
		+1.0777257190312272158094e+1L, \
		-3.5717684488096787370998e+1L, \
	}, \
	.S = \
	{ \
		+1.0000000000000000000000e+0L, \
		-2.6201045551331104417768e+1L, \
		+1.9361891836232102174846e+2L, \
		-4.2861221385716144629696e+2L, \
	}, \
	/* log10(2) */ \
	.L102A = 0.3125L, \
	.L102B = -1.1470004336018804786261e-2L, \
	/* log10(e) */ \
	.L10EA = 0.5L, \
	.L10EB = -6.5705518096748172348871e-2L, \
 \
	.SQRTH = 0.70710678118654752440L, \
}; \
 \
t_f##BITS	F##BITS##_Log10(t_f##BITS x) \
{ \
	t_f##BITS y, z; \
	int e; \
 \
	if (IS_NAN(x)) \
		return x; \
	if(x <= 0.0) \
	{ \
		if(x == 0.0) \
			return -1.0 / (x*x); \
		return (x - x) / 0.0; \
	} \
	if (x == INFINITY) \
		return INFINITY; \
	/* separate mantissa from exponent */ \
	/* Note, frexp is used so that denormal numbers \
	**	will be handled properly. \
	*/ \
	x = F##BITS##_SplitExp(x, &e); \
	/* \
	logarithm using log(x) = z + z**3 P(z)/Q(z), \
	where z = 2(x-1)/x+1) \
	*/ \
	if (e > 2 || e < -2) \
	{ \
		if (x < __data_log10_f##BITS.SQRTH) /* 2(2x-1)/(2x+1) */ \
		{ \
			e -= 1; \
			z = x - 0.5; \
			y = 0.5 * z + 0.5; \
		} \
		else /*  2 (x-1)/(x+1)   */ \
		{ \
			z = x - 0.5; \
			z -= 0.5; \
			y = 0.5 * x  + 0.5; \
		} \
		x = z / y; \
		z = x*x; \
		y = x * (z * __polynomial_f##BITS(z, __data_log10_f##BITS.R, 3) / __polynomial_f##BITS(z, __data_log10_f##BITS.S, 3)); \
		goto done; \
	} \
	/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */ \
	if (x < SQRTH) \
	{ \
		e -= 1; \
		x = 2.0*x - 1.0; \
	} \
	else \
	{ \
		x = x - 1.0; \
	} \
	z = x*x; \
	y = x * (z * __polynomial_f##BITS(x, __data_log10_f##BITS.P, 6) / __polynomial_f##BITS(x, __data_log10_f##BITS.Q, 7)); \
	y = y - 0.5*z; \
 \
done: \
	/* Multiply log of fraction by log10(e) and base 2 exponent by log10(2). \
	** ***CAUTION*** \
	** This sequence of operations is critical and it may \
	** be horribly defeated by some compiler optimizers. \
	*/ \
	z = y * __data_log10_f##BITS.L10EB; \
	z += x * __data_log10_f##BITS.L10EB; \
	z += e * __data_log10_f##BITS.L102B; \
	z += y * __data_log10_f##BITS.L10EA; \
	z += x * __data_log10_f##BITS.L10EA; \
	z += e * __data_log10_f##BITS.L102A; \
	return z; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG10(128)
#endif



#endif
