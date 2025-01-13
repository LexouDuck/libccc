
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Root2, sqrt)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_ROOT2(BITS) \
t_f##BITS	F##BITS##_Root2(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((x < 0.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	/* Newton derivative approximation by iteration */ \
	static const t_s32	max_i = 4; \
	t_s32	i; \
	t_f##BITS	result; \
	t_f##BITS	previous; \
	if (IS_NAN(x) || x < 0.) \
		return (NAN); \
	if (x == 0.) \
		return (0.); \
	if (x == 1.) \
		return (1.); \
	i = F##BITS##_GetExp2(x); \
	result = (i < 0 ? 0.75 : 1.25); \
	result *= __root2pN_f##BITS(i); \
	previous = INFINITY; \
	i = 0; \
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX) \
	{ \
		previous = result; \
		result -= (result * result - x) / (2 * result); \
		if (++i == max_i) \
			break; \
	} \
	return (result); \
} \

DEFINEFUNC_FLOAT_ROOT2(32)
DEFINEFUNC_FLOAT_ROOT2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT2(128)
#endif



#if 0
#define F32_FASTSQRT_CONSTANT	0x5F375A86			// from the Quake III source code
#define F64_FASTSQRT_CONSTANT	0x5FE6EB50C7B537A9	// from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
	/* Fast Inverse square root (from the Quake III source code) */
	u_float_cast result = { x };
	t_float x_2;
	x_2 = result.value_float * 0.5;
	result.value_int = FLOAT_FASTSQRT_CONSTANT - (result.value_int >> 1);
	// TODO handle extended precision types
	result.value_float = result.value_float * (1.5 - (x_2 * result.value_float * result.value_float)); // 1st iteration
	result.value_float = result.value_float * (1.5 - (x_2 * result.value_float * result.value_float)); // 2nd iteration, this can be removed
	return (result.value_float * x);
#endif



#else

/* returns a*b*2^-32 - e, with error 0 <= e < 1.  */
static inline
t_u32 mul32(t_u32 a, t_u32 b)
{
	return (t_u64)a*b >> 32;
}

/* returns a*b*2^-64 - e, with error 0 <= e < 3.  */
static inline
t_u64 mul64(t_u64 a, t_u64 b)
{
	t_u64 ahi = a>>32;
	t_u64 alo = a&0xffffffff;
	t_u64 bhi = b>>32;
	t_u64 blo = b&0xffffffff;
	return ahi*bhi + (ahi*blo >> 32) + (alo*bhi >> 32);
}

#if LIBCONFIG_USE_FLOAT80 || LIBCONFIG_USE_FLOAT128

#define FENV_SUPPORT 1

typedef struct
{
	t_u64 hi;
	t_u64 lo;
} s_u128;

/* top: 16 bit sign+exponent, x: significand.  */
static inline
long double mkldbl(t_u64 top, s_u128 x)
{
	union ldshape u;
#if LDBL_MANT_DIG == 113
	u.i2.hi = x.hi;
	u.i2.lo = x.lo;
	u.i2.hi &= 0x0000ffffffffffff;
	u.i2.hi |= top << 48;
#elif LDBL_MANT_DIG == 64
	u.i.se = top;
	u.i.m = x.lo;
	/* force the top bit on non-zero (and non-subnormal) results.  */
	if (top & 0x7fff)
		u.i.m |= 0x8000000000000000;
#endif
	return u.f;
}

/* return: top 16 bit is sign+exp and following bits are the significand.  */
static inline
s_u128 asu128(long double x)
{
	union ldshape u = {.f=x};
	s_u128 r;
#if LDBL_MANT_DIG == 113
	r.hi = u.i2.hi;
	r.lo = u.i2.lo;
#elif LDBL_MANT_DIG == 64
	r.lo = u.i.m<<49;
	/* ignore the top bit: pseudo numbers are not handled. */
	r.hi = u.i.m>>15;
	r.hi &= 0x0000ffffffffffff;
	r.hi |= (t_u64)u.i.se << 48;
#endif
	return r;
}

static inline
s_u128 add64(s_u128 a, t_u64 b)
{
	s_u128 r;
	r.lo = a.lo + b;
	r.hi = a.hi;
	if (r.lo < a.lo)
		r.hi++;
	return r;
}

static inline
s_u128 add128(s_u128 a, s_u128 b)
{
	s_u128 r;
	r.lo = a.lo + b.lo;
	r.hi = a.hi + b.hi;
	if (r.lo < a.lo)
		r.hi++;
	return r;
}

static inline
s_u128 sub64(s_u128 a, t_u64 b)
{
	s_u128 r;
	r.lo = a.lo - b;
	r.hi = a.hi;
	if (a.lo < b)
		r.hi--;
	return r;
}

static inline
s_u128 sub128(s_u128 a, s_u128 b)
{
	s_u128 r;
	r.lo = a.lo - b.lo;
	r.hi = a.hi - b.hi;
	if (a.lo < b.lo)
		r.hi--;
	return r;
}

/* a<<n, 0 <= n <= 127 */
static inline
s_u128 lsh(s_u128 a, int n)
{
	if (n == 0)
		return a;
	if (n >= 64)
	{
		a.hi = a.lo<<(n-64);
		a.lo = 0;
	} else
	{
		a.hi = (a.hi<<n) | (a.lo>>(64-n));
		a.lo = a.lo<<n;
	}
	return a;
}

/* a>>n, 0 <= n <= 127 */
static inline
s_u128 rsh(s_u128 a, int n)
{
	if (n == 0)
		return a;
	if (n >= 64)
	{
		a.lo = a.hi>>(n-64);
		a.hi = 0;
	} else
	{
		a.lo = (a.lo>>n) | (a.hi<<(64-n));
		a.hi = a.hi>>n;
	}
	return a;
}

/* returns a*b exactly.  */
static inline
s_u128 mul64_128(t_u64 a, t_u64 b)
{
	s_u128 r;
	t_u64 ahi = a>>32;
	t_u64 alo = a&0xffffffff;
	t_u64 bhi = b>>32;
	t_u64 blo = b&0xffffffff;
	t_u64 lo1 = ((ahi*blo)&0xffffffff) + ((alo*bhi)&0xffffffff) + (alo*blo>>32);
	t_u64 lo2 = (alo*blo)&0xffffffff;
	r.hi = ahi*bhi + (ahi*blo>>32) + (alo*bhi>>32) + (lo1>>32);
	r.lo = (lo1<<32) + lo2;
	return r;
}

/* returns a*b*2^-128 - e, with error 0 <= e < 7.  */
static inline
s_u128 mul128(s_u128 a, s_u128 b)
{
	s_u128 hi = mul64_128(a.hi, b.hi);
	t_u64 m1 = mul64(a.hi, b.lo);
	t_u64 m2 = mul64(a.lo, b.hi);
	return add64(add64(hi, m1), m2);
}

/* returns a*b % 2^128.  */
static inline
s_u128 mul128_tail(s_u128 a, s_u128 b)
{
	s_u128 lo = mul64_128(a.lo, b.lo);
	lo.hi += a.hi*b.lo + a.lo*b.hi;
	return lo;
}

#else

#ifndef FENV_SUPPORT
#define FENV_SUPPORT	0
#endif

#endif

/* see sqrt.c for more detailed comments.  */

t_f32 F32_Root2(t_f32 x)
{
	t_u32 ix, m, m1, m0, even, ey;

	ix = AS_U32(x);
	if (predict_false(ix - 0x00800000 >= 0x7f800000 - 0x00800000))
	{
		/* x < 0x1p-126 or inf or nan.  */
		if (ix * 2 == 0)
			return x;
		if (ix == 0x7f800000)
			return x;
		if (ix > 0x7f800000)
			return __math_invalidf(x);
		/* x is subnormal, normalize it.  */
		ix = AS_U32(x * 0x1p23f);
		ix -= 23 << 23;
	}

	/* x = 4^e m; with int e and m in [1, 4).  */
	even = ix & 0x00800000;
	m1 = (ix << 8) | 0x80000000;
	m0 = (ix << 7) & 0x7fffffff;
	m = even ? m0 : m1;

	/* 2^e is the exponent part of the return value.  */
	ey = ix >> 1;
	ey += 0x3f800000 >> 1;
	ey &= 0x7f800000;

	/* compute r ~ 1/sqrt(m), s ~ sqrt(m) with 2 goldschmidt iterations.  */
	static const t_u32 three = 0xc0000000;
	t_u32 r, s, d, u, i;
	i = (ix >> 17) % 128;
	r = (t_u32)__rsqrt_tab[i] << 16;
	/* |r*sqrt(m) - 1| < 0x1p-8 */
	s = mul32(m, r);
	/* |s/sqrt(m) - 1| < 0x1p-8 */
	d = mul32(s, r);
	u = three - d;
	r = mul32(r, u) << 1;
	/* |r*sqrt(m) - 1| < 0x1.7bp-16 */
	s = mul32(s, u) << 1;
	/* |s/sqrt(m) - 1| < 0x1.7bp-16 */
	d = mul32(s, r);
	u = three - d;
	s = mul32(s, u);
	/* -0x1.03p-28 < s/sqrt(m) - 1 < 0x1.fp-31 */
	s = (s - 1)>>6;
	/* s < sqrt(m) < s + 0x1.08p-23 */

	/* compute nearest rounded result.  */
	t_u32 d0, d1, d2;
	t_f32 y, t;
	d0 = (m << 16) - s*s;
	d1 = s - d0;
	d2 = d1 + s + 1;
	s += d1 >> 31;
	s &= 0x007fffff;
	s |= ey;
	y = AS_F32(s);
	if (FENV_SUPPORT)
	{
		/* handle rounding and inexact exception. */
		t_u32 tiny = predict_false(d2==0) ? 0 : 0x01000000;
		tiny |= (d1^d2) & 0x80000000;
		t = AS_F32(tiny);
		y = (t_f32)(y + t);
	}
	return y;
}

t_f64 F64_Root2(t_f64 x)
{
	t_u64 ix, top, m;

	/* special case handling.  */
	ix = AS_U64(x);
	top = ix >> 52;
	if (predict_false(top - 0x001 >= 0x7ff - 0x001))
	{
		/* x < 0x1p-1022 or inf or nan.  */
		if (ix * 2 == 0)
			return x;
		if (ix == 0x7ff0000000000000)
			return x;
		if (ix > 0x7ff0000000000000)
			return __math_invalid(x);
		/* x is subnormal, normalize it.  */
		ix = AS_U64(x * 0x1p52);
		top = ix >> 52;
		top -= 52;
	}

	/* argument reduction:
	   x = 4^e m; with integer e, and m in [1, 4)
	   m: fixed point representation [2.62]
	   2^e is the exponent part of the result.  */
	int even = top & 1;
	m = (ix << 11) | 0x8000000000000000;
	if (even) m >>= 1;
	top = (top + 0x3ff) >> 1;

	/* approximate r ~ 1/sqrt(m) and s ~ sqrt(m) when m in [1,4)

	   initial estimate:
	   7bit table lookup (1bit exponent and 6bit significand).

	   iterative approximation:
	   using 2 goldschmidt iterations with 32bit int arithmetics
	   and a final iteration with 64bit int arithmetics.

	   details:

	   the relative error (e = r0 sqrt(m)-1) of a linear estimate
	   (r0 = a m + b) is |e| < 0.085955 ~ 0x1.6p-4 at best,
	   a table lookup is faster and needs one less iteration
	   6 bit lookup table (128b) gives |e| < 0x1.f9p-8
	   7 bit lookup table (256b) gives |e| < 0x1.fdp-9
	   for single and t_f64 prec 6bit is enough but for quad
	   prec 7bit is needed (or modified iterations). to avoid
	   one more iteration >=13bit table would be needed (16k).

	   a newton-raphson iteration for r is
	     w = r*r
	     u = 3 - m*w
	     r = r*u/2
	   can use a goldschmidt iteration for s at the end or
	     s = m*r

	   first goldschmidt iteration is
	     s = m*r
	     u = 3 - s*r
	     r = r*u/2
	     s = s*u/2
	   next goldschmidt iteration is
	     u = 3 - s*r
	     r = r*u/2
	     s = s*u/2
	   and at the end r is not computed only s.

	   they use the same amount of operations and converge at the
	   same quadratic rate, i.e. if
	     r1 sqrt(m) - 1 = e, then
	     r2 sqrt(m) - 1 = -3/2 e^2 - 1/2 e^3
	   the advantage of goldschmidt is that the mul for s and r
	   are independent (computed in parallel), however it is not
	   "self synchronizing": it only uses the input m in the
	   first iteration so rounding errors accumulate. at the end
	   or when switching to larger precision arithmetics rounding
	   errors dominate so the first iteration should be used.

	   the fixed point representations are
	     m: 2.30 r: 0.32, s: 2.30, d: 2.30, u: 2.30, three: 2.30
	   and after switching to 64 bit
	     m: 2.62 r: 0.64, s: 2.62, d: 2.62, u: 2.62, three: 2.62  */

	static const t_u64 three = 0xc0000000;
	t_u64 r, s, d, u, i;

	i = (ix >> 46) % 128;
	r = (t_u32)__rsqrt_tab[i] << 16;
	/* |r sqrt(m) - 1| < 0x1.fdp-9 */
	s = mul32(m>>32, r);
	/* |s/sqrt(m) - 1| < 0x1.fdp-9 */
	d = mul32(s, r);
	u = three - d;
	r = mul32(r, u) << 1;
	/* |r sqrt(m) - 1| < 0x1.7bp-16 */
	s = mul32(s, u) << 1;
	/* |s/sqrt(m) - 1| < 0x1.7bp-16 */
	d = mul32(s, r);
	u = three - d;
	r = mul32(r, u) << 1;
	/* |r sqrt(m) - 1| < 0x1.3704p-29 (measured worst-case) */
	r = r << 32;
	s = mul64(m, r);
	d = mul64(s, r);
	u = (three<<32) - d;
	s = mul64(s, u);  /* repr: 3.61 */
	/* -0x1p-57 < s - sqrt(m) < 0x1.8001p-61 */
	s = (s - 2) >> 9; /* repr: 12.52 */
	/* -0x1.09p-52 < s - sqrt(m) < -0x1.fffcp-63 */

	/* s < sqrt(m) < s + 0x1.09p-52,
	   compute nearest rounded result:
	   the nearest result to 52 bits is either s or s+0x1p-52,
	   we can decide by comparing (2^52 s + 0.5)^2 to 2^104 m.  */
	t_u64 d0, d1, d2;
	t_f64 y, t;
	d0 = (m << 42) - s*s;
	d1 = s - d0;
	d2 = d1 + s + 1;
	s += d1 >> 63;
	s &= 0x000fffffffffffff;
	s |= top << 52;
	y = AS_F64(s);
	if (FENV_SUPPORT)
	{
		/* handle rounding modes and inexact exception:
		   only (s+1)^2 == 2^42 m case is exact otherwise
		   add a tiny value to cause the fenv effects.  */
		t_u64 tiny = predict_false(d2==0) ? 0 : 0x0010000000000000;
		tiny |= (d1^d2) & 0x8000000000000000;
		t = AS_F64(tiny);
		y = (t_f64)(y + t);
	}
	return y;
}

/* see sqrt.c for detailed comments.  */

#define DEFINEFUNC_FLOAT_ROOT2(BITS) \
t_f##BITS F##BITS##_Root2(t_f##BITS x) \
{ \
	s_u128 ix, ml; \
	t_u64 top; \
 \
	ix = asu128(x); \
	top = ix.hi >> 48; \
	if (predict_false(top - 0x0001 >= 0x7fff - 0x0001)) \
	{ \
		/* x < 0x1p-16382 or inf or nan.  */ \
		if (2*ix.hi == 0 && ix.lo == 0) \
			return x; \
		if (ix.hi == 0x7fff000000000000 && ix.lo == 0) \
			return x; \
		if (top >= 0x7fff) \
			return __math_invalidl(x); \
		/* x is subnormal, normalize it.  */ \
		ix = asu128(x * 0x1p112); \
		top = ix.hi >> 48; \
		top -= 112; \
	} \
 \
	/* x = 4^e m; with int e and m in [1, 4) */ \
	int even = top & 1; \
	ml = lsh(ix, 15); \
	ml.hi |= 0x8000000000000000; \
	if (even) ml = rsh(ml, 1); \
	top = (top + 0x3fff) >> 1; \
 \
	/* r ~ 1/sqrt(m) */ \
	const t_u64 three = 0xc0000000; \
	t_u64 r, s, d, u, i; \
	i = (ix.hi >> 42) % 128; \
	r = (t_u32)__rsqrt_tab[i] << 16; \
	/* |r sqrt(m) - 1| < 0x1p-8 */ \
	s = mul32(ml.hi>>32, r); \
	d = mul32(s, r); \
	u = three - d; \
	r = mul32(u, r) << 1; \
	/* |r sqrt(m) - 1| < 0x1.7bp-16, switch to 64bit */ \
	r = r<<32; \
	s = mul64(ml.hi, r); \
	d = mul64(s, r); \
	u = (three<<32) - d; \
	r = mul64(u, r) << 1; \
	/* |r sqrt(m) - 1| < 0x1.a5p-31 */ \
	s = mul64(u, s) << 1; \
	d = mul64(s, r); \
	u = (three<<32) - d; \
	r = mul64(u, r) << 1; \
	/* |r sqrt(m) - 1| < 0x1.c001p-59, switch to 128bit */ \
 \
	const s_u128 threel = {.hi=three<<32, .lo=0}; \
	s_u128 rl, sl, dl, ul; \
	rl.hi = r; \
	rl.lo = 0; \
	sl = mul128(ml, rl); \
	dl = mul128(sl, rl); \
	ul = sub128(threel, dl); \
	sl = mul128(ul, sl); /* repr: 3.125 */ \
	/* -0x1p-116 < s - sqrt(m) < 0x3.8001p-125 */ \
	sl = rsh(sub64(sl, 4), 125-(LDBL_MANT_DIG-1)); \
	/* s < sqrt(m) < s + 1 ULP + tiny */ \
 \
	t_f##BITS y; \
	s_u128 d2, d1, d0; \
	d0 = sub128(lsh(ml, 2*(LDBL_MANT_DIG-1)-126), mul128_tail(sl,sl)); \
	d1 = sub128(sl, d0); \
	d2 = add128(add64(sl, 1), d1); \
	sl = add64(sl, d1.hi >> 63); \
	y = mkldbl(top, sl); \
	if (FENV_SUPPORT) \
	{ \
		/* handle rounding modes and inexact exception.  */ \
		top = predict_false((d2.hi|d2.lo)==0) ? 0 : 1; \
		top |= ((d1.hi^d2.hi)&0x8000000000000000) >> 48; \
		y += mkldbl(top, (s_u128){0}); \
	} \
	return y; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT2(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT2(128)
#endif



#endif
