
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The power function is computed with integer-only arithmetic:
**	- for integer exponents, exact exponentiation by squaring (with `Q_Mul`,
**	  which saturates on overflow)
**	- for fractional exponents (only valid for `x > 0`), via the base-2
**	  logarithm/exponential cores: `x^y = 2^(y * log2(x))`, with the exponent
**	  carried as a signed q54 value (accurate to ~16 significant digits)
**	The IEEE-754 special cases are followed: `x^0 == 1` and `1^y == 1` (even
**	for `NAN`/`INF` arguments), `(-1)^±INF == 1`, etc.
*/

#define DEFINEFUNC_FIXED_POW(BITS, WB) \
t_q##BITS	Q##BITS##_Pow(t_q##BITS x, t_q##BITS y) \
{ \
	if (y._ == 0) /* IEEE: `x ^ 0 == 1` for any `x`, even NAN/INF */ \
		return ((t_q##BITS){ (t_s##BITS)Q##BITS##_DENOM }); \
	if (x._ == (t_s##BITS)Q##BITS##_DENOM) /* IEEE: `1 ^ y == 1` for any `y`, even NAN/INF */ \
		return ((t_q##BITS){ (t_s##BITS)Q##BITS##_DENOM }); \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(y)) \
	{ \
		if (x._ == -(t_s##BITS)Q##BITS##_DENOM) /* IEEE: `(-1) ^ ±INF == 1` */ \
			return ((t_q##BITS){ (t_s##BITS)Q##BITS##_DENOM }); \
		t_bool const	abs_lt_one = (Q##BITS##_Abs(x)._ < (t_s##BITS)Q##BITS##_DENOM); \
		if (abs_lt_one == (y._ > 0)) \
			return ((t_q##BITS){ 0 }); \
		return (Q##BITS##_MAX); \
	} \
	if (Q##BITS##_IsInf(x)) \
	{ \
		if (y._ < 0) \
			return ((t_q##BITS){ 0 }); \
		if (x._ < 0 && (y._ % (t_s##BITS)Q##BITS##_DENOM == 0) && (((y._ / (t_s##BITS)Q##BITS##_DENOM) & 1) != 0)) \
			return (Q##BITS##_MIN); /* `(-INF) ^ y == -INF` for positive odd integer `y` */ \
		return (Q##BITS##_MAX); \
	} \
	if (y._ % (t_s##BITS)Q##BITS##_DENOM == 0) \
	{	/* integer exponent: exact exponentiation by squaring */ \
		if (x._ == 0) \
			return ((y._ > 0) ? (t_q##BITS){ 0 } : Q##BITS##_MAX); /* IEEE: `0 ^ y == +INF` for negative `y` */ \
		t_q##BITS	base = x; \
		t_q##BITS	result = (t_q##BITS){ (t_s##BITS)Q##BITS##_DENOM }; \
		t_u##WB	n = __FIXEDMATH_UABS(BITS, WB, (t_s##BITS)(y._ / (t_s##BITS)Q##BITS##_DENOM)); \
		while (n > 0) \
		{ \
			if (n & 1) \
				result = Q##BITS##_Mul(result, base); \
			n >>= 1; \
			if (n > 0) \
				base = Q##BITS##_Mul(base, base); \
		} \
		if (y._ < 0) \
			return (Q##BITS##_Div((t_q##BITS){ (t_s##BITS)Q##BITS##_DENOM }, result)); \
		return (result); \
	} \
	/* fractional exponent */ \
	if CCCERROR((x._ < 0), ERROR_MATHDOMAIN, \
		"negative value raised to fractional power is undefined") \
		return (Q##BITS##_ERROR); \
	if (x._ == 0) \
		return ((y._ > 0) ? (t_q##BITS){ 0 } : Q##BITS##_MAX); /* IEEE: `0 ^ y == +INF` for negative `y` */ \
	/* compute `e = y * log2(x)`, as a signed q54 value */ \
	t_s64 const	log2_x = __fixedmath_log2_##WB((t_u##WB)(t_u##BITS)x._) - __fixedmath_log2_##WB((t_u##WB)Q##BITS##_DENOM); \
	t_u##WB const	abs_y = __FIXEDMATH_UABS(BITS, WB, y._); \
	t_u##WB const	abs_l = (log2_x < 0) ? (t_u##WB)(t_u64)-log2_x : (t_u##WB)(t_u64)log2_x; \
	t_u##WB	hi; \
	t_u##WB	lo; \
	t_bool	overflow; \
	__fixedmath_umul_##WB(abs_y, abs_l, &hi, &lo); \
	t_u##WB	e_mag = __fixedmath_udiv_##WB(hi, lo, (t_u##WB)Q##BITS##_DENOM, &overflow); \
	if (overflow || e_mag > ((t_u##WB)1 << 62)) \
		e_mag = ((t_u##WB)1 << 62); /* clamp: the exponential core will saturate/underflow anyway */ \
	t_bool const	e_negative = ((y._ < 0) != (log2_x < 0)); \
	t_s64 const	e_q54 = (e_negative ? -(t_s64)(t_u64)e_mag : (t_s64)(t_u64)e_mag); \
	t_u##WB const	q = __fixedmath_exp2_##WB(e_q54, (t_u##WB)Q##BITS##_DENOM, (t_u##WB)(t_u##BITS)Q##BITS##_MAX._ - (LIBCONFIG_FIXED_INF ? 1 : 0), &overflow); \
	if CCCERROR((overflow), ERROR_RESULTRANGE, \
		"positive overflow for fixed-point power (as t_q"#BITS")") \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) \
		return (Q##BITS##_MAX); \
	} \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_POW(8, 64)
DEFINEFUNC_FIXED_POW(16, 64)
DEFINEFUNC_FIXED_POW(32, 64)
DEFINEFUNC_FIXED_POW(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_POW(128, 128)
#endif



#ifdef __cplusplus
t_q8	operator ^ (t_q8   x, t_q8   y)	{ return Q8_Pow(x, y); }
t_q16	operator ^ (t_q16  x, t_q16  y)	{ return Q16_Pow(x, y); }
t_q32	operator ^ (t_q32  x, t_q32  y)	{ return Q32_Pow(x, y); }
t_q64	operator ^ (t_q64  x, t_q64  y)	{ return Q64_Pow(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator ^ (t_q128 x, t_q128 y)	{ return Q128_Pow(x, y); }
#endif
#endif
