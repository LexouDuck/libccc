
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The n-th root is computed with integer-only arithmetic, via the base-2
**	logarithm/exponential cores: `rootn(x) = 2^(log2(x) / n)`, with the
**	exponent carried as a signed q54 value. The `n == 2` and `n == 3` cases
**	delegate to the exact `Root2`/`Root3` functions.
*/

#define DEFINEFUNC_FIXED_ROOTN(BITS, WB) \
t_q##BITS	Q##BITS##_RootN(t_q##BITS x, t_u8 n) \
{ \
	if CCCERROR((n == 0), ERROR_MATHDOMAIN, \
		"cannot get 0-th root of a number") \
		return (Q##BITS##_ERROR); \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if (n == 1)	return (x); \
	if (n == 2)	return (Q##BITS##_Root2(x)); \
	if (n == 3)	return (Q##BITS##_Root3(x)); \
	if CCCERROR((x._ < 0 && (n & 1) == 0), ERROR_MATHDOMAIN, \
		"even root of negative value is undefined") \
		return (Q##BITS##_ERROR); \
	if (x._ == 0) \
		return ((t_q##BITS){ 0 }); \
	if (Q##BITS##_IsInf(x)) \
		return (x); /* odd `n` preserves the sign, even `n` was handled above */ \
	t_bool const	negative = (x._ < 0); \
	t_u##WB const	abs_x = __FIXEDMATH_UABS(BITS, WB, x._); \
	/* compute `e = log2(|x|) / n`, as a signed q54 value */ \
	t_s64 const	log2_x = __fixedmath_log2_##WB(abs_x) - __fixedmath_log2_##WB((t_u##WB)Q##BITS##_DENOM); \
	t_s64 const	e_q54 = (log2_x / (t_s64)n); \
	t_bool	overflow; \
	t_u##WB const	q = __fixedmath_exp2_##WB(e_q54, (t_u##WB)Q##BITS##_DENOM, (t_u##WB)(t_u##BITS)Q##BITS##_MAX._ - (LIBCONFIG_FIXED_INF ? 1 : 0), &overflow); \
	if CCCERROR((overflow), ERROR_RESULTRANGE, \
		"%s overflow for fixed-point n-th root (as t_q"#BITS")", (negative ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (negative ? Q##BITS##_MIN : Q##BITS##_MAX)) \
		return (negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (negative) \
		return ((t_q##BITS){ (t_s##BITS)-(t_s##WB)q }); \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_ROOTN(8, 64)
DEFINEFUNC_FIXED_ROOTN(16, 64)
DEFINEFUNC_FIXED_ROOTN(32, 64)
DEFINEFUNC_FIXED_ROOTN(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROOTN(128, 128)
#endif
