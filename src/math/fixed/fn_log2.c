
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The base-2 logarithm is computed with integer-only arithmetic, via the
**	base-2 logarithm core: `log2(x) = log2(raw) - log2(DENOM)`, carried as a
**	signed q54 value, then scaled by `DENOM` (truncated toward zero, like all
**	fixed-point results).
*/

#define DEFINEFUNC_FIXED_LOG2(BITS, WB) \
t_q##BITS	Q##BITS##_Log2(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((x._ < 0), ERROR_MATHDOMAIN, \
		"logarithm of negative value is undefined") \
		return (Q##BITS##_ERROR); \
	if (x._ == 0) \
		return (Q##BITS##_MIN); /* log2(0) == -INFINITY */ \
	if (Q##BITS##_IsInf(x)) \
		return (Q##BITS##_MAX); \
	t_s64 const	l = __fixedmath_log2_##WB((t_u##WB)(t_u##BITS)x._) - __fixedmath_log2_##WB((t_u##WB)Q##BITS##_DENOM); \
	/* the raw result is `l * DENOM / 2^54`, truncated toward zero */ \
	t_bool const	negative = (l < 0); \
	t_u64 const	abs_l = (negative ? (t_u64)-l : (t_u64)l); \
	t_u##WB	hi; \
	t_u##WB	lo; \
	__fixedmath_umul_##WB((t_u##WB)abs_l, (t_u##WB)Q##BITS##_DENOM, &hi, &lo); \
	t_u##WB const	q = (lo >> 54) | (hi << (WB - 54)); \
	if CCCERROR(((hi >> 54) != 0 || q > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"%s overflow for fixed-point base-2 logarithm (as t_q"#BITS")", (negative ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (negative ? Q##BITS##_MIN : Q##BITS##_MAX)) \
		return (negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (negative) \
		return ((t_q##BITS){ (t_s##BITS)-(t_s##WB)q }); \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_LOG2(8, 64)
DEFINEFUNC_FIXED_LOG2(16, 64)
DEFINEFUNC_FIXED_LOG2(32, 64)
DEFINEFUNC_FIXED_LOG2(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_LOG2(128, 128)
#endif
