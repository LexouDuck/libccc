
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The square root is computed exactly: the raw result is `isqrt(v * DENOM)`
**	(with `v` being the raw input value), since
**	`trunc(sqrt(v / DENOM) * DENOM) == floor(sqrt(v * DENOM))` exactly.
*/

#define DEFINEFUNC_FIXED_ROOT2(BITS, WB) \
t_q##BITS	Q##BITS##_Root2(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((x._ < 0), ERROR_MATHDOMAIN, \
		"square root of negative value is undefined") \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(x)) \
		return (x); \
	t_u##WB	hi; \
	t_u##WB	lo; \
	__fixedmath_umul_##WB((t_u##WB)(t_u##BITS)x._, (t_u##WB)Q##BITS##_DENOM, &hi, &lo); \
	t_u##WB const	q = __fixedmath_usqrt_##WB(hi, lo); \
	if CCCERROR((q > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"positive overflow for fixed-point square root (as t_q"#BITS")") \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) \
		return (Q##BITS##_MAX); \
	} \
	return ((t_q##BITS){ (t_s##BITS)q }); \
} \

DEFINEFUNC_FIXED_ROOT2(8, 64)
DEFINEFUNC_FIXED_ROOT2(16, 64)
DEFINEFUNC_FIXED_ROOT2(32, 64)
DEFINEFUNC_FIXED_ROOT2(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROOT2(128, 128)
#endif
