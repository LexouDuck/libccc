
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Root3, cbrt)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_ROOT3(BITS) \
t_f##BITS	F##BITS##_Root3(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	/* Newton derivative approximation by iteration */ \
	static const t_s32	max_i = 4; \
	t_s32	i; \
	t_f##BITS	square; \
	t_f##BITS	result; \
	t_f##BITS	previous; \
	if (x == 0) \
		return (0); \
	if (F##BITS##_Abs(x) == 1.) \
		return (SGN(x)); \
	i = F##BITS##_GetExp2(x); \
	result = SGN(x) * (i < 0 ? 0.75 : 1.25); \
	result *= __root2pN_f##BITS(i * 2 / 3); \
	previous = INFINITY; \
	i = 0; \
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX) \
	{ \
		previous = result; \
		square = result * result; \
		result -= (result * square - x) / (3 * square); \
		if (++i == max_i) \
			break; \
	} \
	return (result); \
} \

DEFINEFUNC_FLOAT_ROOT3(32)
DEFINEFUNC_FLOAT_ROOT3(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT3(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT3(128)
#endif

#else

/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
** Copyright (c) 2009-2011, Bruce D. Evans, Steven G. Kargl, David Schultz.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
**
** Optimized by Bruce D. Evans.
*/

t_f32	F32_Root3(t_f32 x)
{
	static const unsigned B1 = 709958130; /* B1 = (127-127.0/3-0.03306235651)*2**23 */
	static const unsigned B2 = 642849266; /* B2 = (127-127.0/3-24/3-0.03306235651)*2**23 */

	t_f64 r,t;
	union {t_f32 f; t_u32 i;} u = {x};
	t_u32 hx = u.i & 0X7FFFFFFF;

	if (hx >= 0X7F800000)  /* cbrt(NaN,INF) is itself */
		return x + x;
	/* rough cbrt to 5 bits */
	if (hx < 0x00800000)
	{  /* zero or subnormal? */
		if (hx == 0)
			return x;  /* cbrt(+-0) is itself */
		u.f = x*0x1p24f;
		hx = u.i & 0X7FFFFFFF;
		hx = hx/3 + B2;
	}
	else
		hx = hx/3 + B1;
	u.i &= 0x80000000;
	u.i |= hx;
	/* First step Newton iteration (solving t*t-x/t == 0) to 16 bits. */
	/* In t_f64 precision so that its terms can be arranged for efficiency without causing overflow or underflow. */
	t = u.f;
	r = t*t*t;
	t = t*((t_f64)x+x+r)/(x+r+r);
	/* Second step Newton iteration to 47 bits.  In t_f64 precision for efficiency and accuracy. */
	r = t*t*t;
	t = t*((t_f64)x+x+r)/(x+r+r);
	/* rounding to 24 bits is perfect in round-to-nearest mode */
	return t;
}




t_f64	F64_Root3(t_f64 x)
{
	static const t_u32 B1 = 715094163; /* B1 = (1023-1023/3-0.03306235651)*2**20 */
	static const t_u32 B2 = 696219795; /* B2 = (1023-1023/3-54/3-0.03306235651)*2**20 */
	/* |1/cbrt(x) - p(x)| < 2**-23.5 (~[-7.93e-8, 7.929e-8]). */
	static const t_f64 P0 = +1.87595182427177009643;  /* 0X3FFE03E6, 0X0F61E692 */
	static const t_f64 P1 = -1.88497979543377169875;  /* 0xbffe28e0, 0X92F02420 */
	static const t_f64 P2 = +1.621429720105354466140; /* 0X3FF9F160, 0X4A49D6C2 */
	static const t_f64 P3 = -0.758397934778766047437; /* 0xbfe844cb, 0xbee751d9 */
	static const t_f64 P4 = +0.145996192886612446982; /* 0X3FC2B000, 0xd4e4edd7 */
	union {t_f64 f; t_u64 i;} u = {x};
	t_f64 r,s,t,w;
	t_u32 hx = u.i>>32 & 0X7FFFFFFF;

	if (hx >= 0X7FF00000)  /* cbrt(NaN,INF) is itself */
		return x+x;
	/*
	**	Rough cbrt to 5 bits:
	**	   cbrt(2**e*(1+m) ~= 2**(e/3)*(1+(e%3+m)/3)
	**	where e is integral and >= 0, m is real and in [0, 1), and "/" and
	**	"%" are integer division and modulus with rounding towards minus
	**	infinity.  The RHS is always >= the LHS and has a maximum relative
	**	error of about 1 in 16.  Adding a bias of -0.03306235651 to the
	**	(e%3+m)/3 term reduces the error to about 1 in 32. With the IEEE
	**	floating point representation, for finite positive normal values,
	**	ordinary integer divison of the value in bits magically gives
	**	almost exactly the RHS of the above provided we first subtract the
	**	exponent bias (1023 for doubles) and later add it back.  We do the
	**	subtraction virtually to keep e >= 0 so that ordinary integer
	**	division rounds towards minus infinity; this is also efficient.
	*/
	if (hx < 0x00100000)
	{	/* zero or subnormal? */
		u.f = x*0x1p54;
		hx = u.i>>32 & 0X7FFFFFFF;
		if (hx == 0)
			return x;  /* cbrt(0) is itself */
		hx = hx/3 + B2;
	}
	else
		hx = hx/3 + B1;
	u.i &= 1ULL<<63;
	u.i |= (t_u64)hx << 32;
	t = u.f;
	/*
	New cbrt to 23 bits: cbrt(x) = t*cbrt(x/t**3) ~= t*P(t**3/x)
	where P(r) is a polynomial of degree 4 that approximates 1/cbrt(r) to within 2**-23.5 when |r - 1| < 1/10.
	The rough approximation has produced t such than |t/cbrt(x) - 1| ~< 1/32,
	and cubing this gives us bounds for r = t**3/x.
	*/
	/* Try to optimize for parallel evaluation as in __tanf.c. */
	r = (t*t)*(t/x);
	t = t*((P0+r*(P1+r*P2))+((r*r)*r)*(P3+r*P4));

	/*
	**	Round t away from zero to 23 bits (sloppily except for ensuring that
	**	the result is larger in magnitude than cbrt(x) but not much more than
	**	2 23-bit ulps larger).  With rounding towards zero, the error bound
	**	would be ~5/6 instead of ~4/6.  With a maximum error of 2 23-bit ulps
	**	in the rounded t, the infinite-precision error in the Newton
	**	approximation barely affects third digit in the final error
	**	0.667; the error in the rounded t can be up to about 3 23-bit ulps
	**	before the final error is larger than 0.667 ulps.
	*/
	u.f = t;
	u.i = (u.i + 0x80000000) & 0xffffffffc0000000ULL;
	t = u.f;

	/* one step Newton iteration to 53 bits with error < 0.667 ulps */
	s = t*t;         /* t*t is exact */
	r = x/s;         /* error <= 0.5 ulps; |r| < |t| */
	w = t+t;         /* t+t is exact */
	r = (r-t)/(w+r); /* r-t is exact; w+r ~= 3*t */
	t = t+t*r;       /* error <= 0.5 + 0.5/3 + epsilon */
	return t;
}



#define DEFINEFUNC_FLOAT_ROOT3(BITS) \
t_f##BITS	F##BITS##_Root3(t_f##BITS x) \
{ \
	static const unsigned B1 = 709958130; /* B1 = (127-127.0/3-0.03306235651)*2**23 */ \
	union ldshape u = {x}, v; \
	union {t_f32 f; t_u32 i;} uft; \
	t_f##BITS r, s, t, w; \
	t_f64 dr, dt, dx; \
	t_f32 ft; \
	int e = u.i.se & 0X7FFF; \
	int sign = u.i.se & 0x8000; \
 \
	/* \
	**	If x = +-Inf, then cbrt(x) = +-Inf. \
	**	If x = NaN, then cbrt(x) = NaN. \
	*/ \
	if (e == 0X7FFF) \
		return x + x; \
	if (e == 0) \
	{ \
		/* Adjust subnormal numbers. */ \
		u.f *= 0x1p120; \
		e = u.i.se & 0X7FFF; \
		/* If x = +-0, then cbrt(x) = +-0. */ \
		if (e == 0) \
			return x; \
		e -= 120; \
	} \
	e -= 0X3FFF; \
	u.i.se = 0X3FFF; \
	x = u.f; \
	switch (e % 3) \
	{ \
	case 1: \
	case -2: \
		x *= 2; \
		e--; \
		break; \
	case 2: \
	case -1: \
		x *= 4; \
		e -= 2; \
		break; \
	} \
	v.f = 1.0; \
	v.i.se = sign | (0X3FFF + e/3); \
	/* \
	**	The following is the guts of s_cbrtf, with the handling of \
	**	special values removed and extra care for accuracy not taken, \
	**	but with most of the extra accuracy not discarded. \
	*/ \
	/* ~5-bit estimate: */ \
	uft.f = x; \
	uft.i = (uft.i & 0X7FFFFFFF)/3 + B1; \
	ft = uft.f; \
	/* ~16-bit estimate: */ \
	dx = x; \
	dt = ft; \
	dr = dt * dt * dt; \
	dt = dt * (dx + dx + dr) / (dx + dr + dr); \
	/* ~47-bit estimate: */ \
	dr = dt * dt * dt; \
	dt = dt * (dx + dx + dr) / (dx + dr + dr); \
	/* behavior is explained below */ \
	t = ROUND_DT; \
	/* \
	**	Final step Newton iteration to 64 or 113 bits with \
	**	error < 0.667 ulps \
	*/ \
	s = t*t;         /* t*t is exact */ \
	r = x/s;         /* error <= 0.5 ulps; |r| < |t| */ \
	w = t+t;         /* t+t is exact */ \
	r = (r-t)/(w+r); /* r-t is exact; w+r ~= 3*t */ \
	t = t+t*r;       /* error <= 0.5 + 0.5/3 + epsilon */ \
	t *= v.f; \
	return t; \
} \

/*
**	dt is cbrtl(x) to ~47 bits (after x has been reduced to 1 <= x < 8).
**	Round it away from zero to 32 bits (32 so that t*t is exact, and
**	away from zero for technical reasons).
*/
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT3(80, dt + (0x1.0p32L + 0x1.0p-31L) - 0x1.0p32)
#endif

/*
**	Round dt away from zero to 47 bits.  Since we don't trust the 47,
**	add 2 47-bit ulps instead of 1 to round up.  Rounding is slow and
**	might be avoidable in this case, since on most machines dt will
**	have been evaluated in 53-bit precision and the technical reasons
**	for rounding up might not apply to either case in cbrtl() since
**	dt is much more accurate than needed.
*/
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT3(128, dt + 0x2.0p-46 + 0x1.0p60L - 0x1.0p60)
#endif



#endif
