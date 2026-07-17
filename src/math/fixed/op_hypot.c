
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The hypotenuse is computed exactly: the raw result is `isqrt(x² + y²)`
**	(in raw units), since `sqrt((x/D)² + (y/D)²) * D == sqrt(x² + y²)`.
**	The sum of squares is computed exactly over 2 words (it cannot overflow,
**	since both squares are below `2^(2*WB - 2)`).
*/

#define DEFINEFUNC_FIXED_HYPOT(BITS, WB) \
t_q##BITS	Q##BITS##_Hypotenuse(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(x) || Q##BITS##_IsInf(y)) \
		return (Q##BITS##_MAX); \
	t_u##WB const	abs_x = __FIXEDMATH_UABS(BITS, WB, x._); \
	t_u##WB const	abs_y = __FIXEDMATH_UABS(BITS, WB, y._); \
	t_u##WB	x_hi; \
	t_u##WB	x_lo; \
	t_u##WB	y_hi; \
	t_u##WB	y_lo; \
	__fixedmath_umul_##WB(abs_x, abs_x, &x_hi, &x_lo); \
	__fixedmath_umul_##WB(abs_y, abs_y, &y_hi, &y_lo); \
	t_u##WB const	sum_lo = x_lo + y_lo; \
	t_u##WB const	sum_hi = x_hi + y_hi + (sum_lo < x_lo ? 1 : 0); \
	t_u##WB const	q = __fixedmath_usqrt_##WB(sum_hi, sum_lo); \
	if CCCERROR((q > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"positive overflow for fixed-point hypotenuse (as t_q"#BITS")") \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) \
		return (Q##BITS##_MAX); \
	} \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_HYPOT(8, 64)
DEFINEFUNC_FIXED_HYPOT(16, 64)
DEFINEFUNC_FIXED_HYPOT(32, 64)
DEFINEFUNC_FIXED_HYPOT(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_HYPOT(128, 128)
#endif
