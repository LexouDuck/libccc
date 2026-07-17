
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The natural exponential is computed with integer-only arithmetic, via the
**	base-2 exponential core: `exp(x) = 2^(x * log2(e))`, with the exponent
**	carried as a signed q54 value.
*/

#define DEFINEFUNC_FIXED_EXP(BITS, WB) \
t_q##BITS	Q##BITS##_Exp(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(x)) \
		return ((x._ > 0) ? Q##BITS##_MAX : (t_q##BITS){ 0 }); \
	/* compute `e = x * log2(e)`, i.e. `raw * LOG2E_Q54 / DENOM`, as a signed q54 value */ \
	t_u##WB const	abs_x = __FIXEDMATH_UABS(BITS, WB, x._); \
	t_u##WB	hi; \
	t_u##WB	lo; \
	t_bool	overflow; \
	__fixedmath_umul_##WB(abs_x, (t_u##WB)(t_u64)__FIXEDMATH_LOG2E_Q54, &hi, &lo); \
	t_u##WB	e_mag = __fixedmath_udiv_##WB(hi, lo, (t_u##WB)Q##BITS##_DENOM, &overflow); \
	if (overflow || e_mag > ((t_u##WB)1 << 62)) \
		e_mag = ((t_u##WB)1 << 62); /* clamp: the exponential core will saturate/underflow anyway */ \
	t_s64 const	e_q54 = ((x._ < 0) ? -(t_s64)(t_u64)e_mag : (t_s64)(t_u64)e_mag); \
	t_u##WB const	q = __fixedmath_exp2_##WB(e_q54, (t_u##WB)Q##BITS##_DENOM, (t_u##WB)(t_u##BITS)Q##BITS##_MAX._ - (LIBCONFIG_FIXED_INF ? 1 : 0), &overflow); \
	if CCCERROR((overflow), ERROR_RESULTRANGE, \
		"positive overflow for fixed-point exponential (as t_q"#BITS")") \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) \
		return (Q##BITS##_MAX); \
	} \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_EXP(8, 64)
DEFINEFUNC_FIXED_EXP(16, 64)
DEFINEFUNC_FIXED_EXP(32, 64)
DEFINEFUNC_FIXED_EXP(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_EXP(128, 128)
#endif
