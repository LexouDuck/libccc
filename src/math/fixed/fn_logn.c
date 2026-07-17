
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The base-`n` logarithm is computed with integer-only arithmetic, as the
**	ratio of two base-2 logarithms: `logn(x, n) = log2(x) / log2(n)`.
**	Since both logarithms are signed q54 values, the raw result is simply
**	`trunc((log2(x) * DENOM) / log2(n))` (the q54 scales cancel out), computed
**	exactly with a full-width multiplication and 2-word division.
**	The special cases follow the quotient semantics of `±INF` and zero values
**	(e.g. `logn(x, 1)` is an infinity, since `log2(1) == 0`).
*/

#define DEFINEFUNC_FIXED_LOGN(BITS, WB) \
t_q##BITS	Q##BITS##_LogN(t_q##BITS x, t_q##BITS n) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(n)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((x._ < 0 || n._ < 0), ERROR_MATHDOMAIN, \
		"logarithm of negative value is undefined") \
		return (Q##BITS##_ERROR); \
	t_bool const	x_is_zero = (x._ == 0);	t_bool const	x_is_inf = Q##BITS##_IsInf(x); \
	t_bool const	n_is_zero = (n._ == 0);	t_bool const	n_is_inf = Q##BITS##_IsInf(n); \
	if CCCERROR(((x_is_zero || x_is_inf) && (n_is_zero || n_is_inf)), ERROR_MATHDOMAIN, \
		"result of infinite logarithm divided by infinite logarithm is undefined") \
		return (Q##BITS##_ERROR); \
	if (n_is_zero || n_is_inf) /* `log2(n)` is infinite, and `log2(x)` is finite: the ratio is zero */ \
		return ((t_q##BITS){ 0 }); \
	t_s64 const	l_n = __fixedmath_log2_##WB((t_u##WB)(t_u##BITS)n._) - __fixedmath_log2_##WB((t_u##WB)Q##BITS##_DENOM); \
	if (x_is_zero || x_is_inf) \
	{	/* `log2(x)` is infinite (`-INF` for zero, `+INF` for infinity): the ratio is infinite */ \
		if CCCERROR((l_n == 0), ERROR_MATHDOMAIN, \
			"infinite logarithm in base 1 is undefined") \
			return (Q##BITS##_ERROR); \
		t_bool const	result_negative = (x_is_zero != (l_n < 0)); \
		return (result_negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	t_s64 const	l_x = __fixedmath_log2_##WB((t_u##WB)(t_u##BITS)x._) - __fixedmath_log2_##WB((t_u##WB)Q##BITS##_DENOM); \
	if (l_n == 0) \
	{	/* `log2(n)` is zero (`n == 1`): the ratio is infinite (or undefined for `x == 1`) */ \
		if CCCERROR((l_x == 0), ERROR_MATHDOMAIN, \
			"logarithm of 1 in base 1 is undefined") \
			return (Q##BITS##_ERROR); \
		return ((l_x < 0) ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (l_x == 0) \
		return ((t_q##BITS){ 0 }); \
	/* the raw result is `trunc(l_x * DENOM / l_n)` (the q54 scales cancel out) */ \
	t_bool const	negative = ((l_x < 0) != (l_n < 0)); \
	t_u##WB const	abs_l_x = (t_u##WB)(t_u64)((l_x < 0) ? -l_x : l_x); \
	t_u##WB const	abs_l_n = (t_u##WB)(t_u64)((l_n < 0) ? -l_n : l_n); \
	t_u##WB	hi; \
	t_u##WB	lo; \
	t_bool	overflow; \
	__fixedmath_umul_##WB(abs_l_x, (t_u##WB)Q##BITS##_DENOM, &hi, &lo); \
	t_u##WB const	q = __fixedmath_udiv_##WB(hi, lo, abs_l_n, &overflow); \
	if CCCERROR((overflow || q > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"%s overflow for fixed-point base-n logarithm (as t_q"#BITS")", (negative ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (negative ? Q##BITS##_MIN : Q##BITS##_MAX)) \
		return (negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (negative) \
		return ((t_q##BITS){ (t_s##BITS)-(t_s##WB)q }); \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_LOGN(8, 64)
DEFINEFUNC_FIXED_LOGN(16, 64)
DEFINEFUNC_FIXED_LOGN(32, 64)
DEFINEFUNC_FIXED_LOGN(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_LOGN(128, 128)
#endif
