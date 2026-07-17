
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MUL(BITS, WB) \
t_q##BITS	Q##BITS##_Mul(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((Q##BITS##_IsInf(x) && y._ == 0) || (Q##BITS##_IsInf(y) && x._ == 0), ERROR_MATHDOMAIN, \
		"result of infinite value multiplied by 0 is undefined") \
		return (Q##BITS##_ERROR); \
	else if (Q##BITS##_IsInf(x))	return (t_q##BITS){ (t_s##BITS)(x._ * S##BITS##_Sgn(y._)) }; \
	else if (Q##BITS##_IsInf(y))	return (t_q##BITS){ (t_s##BITS)(y._ * S##BITS##_Sgn(x._)) }; \
	if CCCERROR( \
		!LIBCONFIG_FIXED_INF && \
		!LIBCONFIG_FIXED_NAN && \
		((x._ == Q##BITS##_MIN._ && y._ == -1) || (y._ == Q##BITS##_MIN._ && x._ == -1)), ERROR_RESULTRANGE, \
		"positive overflow when attempting to get inverse of minimum value for t_q"#BITS": " SF_Q##BITS, Q##BITS##_MIN) \
	{	LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX);	} \
	/* compute `|x| * |y| / DENOM` exactly, using a full-width (2-word) intermediate product */ \
	t_bool const	negative = ((x._ < 0) != (y._ < 0)); \
	t_u##WB const	abs_x = __FIXEDMATH_UABS(BITS, WB, x._); \
	t_u##WB const	abs_y = __FIXEDMATH_UABS(BITS, WB, y._); \
	t_u##WB	hi; \
	t_u##WB	lo; \
	t_bool	overflow; \
	__fixedmath_umul_##WB(abs_x, abs_y, &hi, &lo); \
	t_u##WB const	q = __fixedmath_udiv_##WB(hi, lo, (t_u##WB)Q##BITS##_DENOM, &overflow); \
	if CCCERROR((overflow || q > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"%s overflow for fixed-point multiplication (as t_q"#BITS")", (negative ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (negative ? Q##BITS##_MIN : Q##BITS##_MAX)) \
		return (negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (negative) \
		return (t_q##BITS){ (t_s##BITS)-(t_s##WB)q }; \
	return (t_q##BITS){ (t_s##BITS)q }; \
} \

DEFINEFUNC_FIXED_MUL(8, 64)
DEFINEFUNC_FIXED_MUL(16, 64)
DEFINEFUNC_FIXED_MUL(32, 64)
DEFINEFUNC_FIXED_MUL(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MUL(128, 128)
#endif



#ifdef __cplusplus
t_q8	operator * (t_q8   x, t_q8   y)	{ return Q8_Mul(x, y); }
t_q16	operator * (t_q16  x, t_q16  y)	{ return Q16_Mul(x, y); }
t_q32	operator * (t_q32  x, t_q32  y)	{ return Q32_Mul(x, y); }
t_q64	operator * (t_q64  x, t_q64  y)	{ return Q64_Mul(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator * (t_q128 x, t_q128 y)	{ return Q128_Mul(x, y); }
#endif
#endif
