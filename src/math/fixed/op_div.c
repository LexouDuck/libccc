
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_DIV(BITS) \
t_q##BITS	Q##BITS##_Div(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((Q##BITS##_IsInf(x) && Q##BITS##_IsInf(y)), ERROR_MATHDOMAIN, \
		"result of infinite value divided by infinite value is undefined") \
		return (Q##BITS##_ERROR); \
	if CCCERROR(((x._ == 0) && (y._ == 0)), ERROR_MATHDOMAIN, \
		"result of zero divided by zero is undefined by convention") \
		return (Q##BITS##_ERROR); \
	if CCCERROR((!LIBCONFIG_FIXED_INF && y._ == 0), ERROR_MATHDOMAIN, \
		"cannot divide by zero unless infinite value is configured") \
		return (Q##BITS##_ERROR); \
	if CCCERROR( \
		!LIBCONFIG_FIXED_INF && \
		!LIBCONFIG_FIXED_NAN && \
		(x._ == Q##BITS##_MIN._ && y._ == -1), ERROR_RESULTRANGE, \
		"positive overflow when attempting to get inverse of minimum value for t_s"#BITS": " SF_Q##BITS, Q##BITS##_MIN) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) \
		return (Q##BITS##_MIN); \
	} \
	if (y._ == 0) \
		return ((t_q##BITS){ (t_s##BITS)(Q##BITS##_MAX._ * S##BITS##_Sgn(x._)) }); \
	if (Q##BITS##_IsInf(x)) \
		return (t_q##BITS){ (t_s##BITS)((S##BITS##_Sgn(x._) * S##BITS##_Sgn(y._)) * Q##BITS##_MAX._) }; \
	if (Q##BITS##_IsInf(y)) \
		return (t_q##BITS){ 0 }; \
	if (y._ == x._) \
		return ((t_q##BITS){ Q##BITS##_DENOM }); \
	if (y._ <= Q##BITS##_DENOM) \
		return (t_q##BITS){ (t_s##BITS)(x._ * (Q##BITS##_DENOM / y._) ) }; \
	return (t_q##BITS){ (t_s##BITS)(x._ / y._) }; \
} \

DEFINEFUNC_FIXED_DIV(8)
DEFINEFUNC_FIXED_DIV(16)
DEFINEFUNC_FIXED_DIV(32)
DEFINEFUNC_FIXED_DIV(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_DIV(128)
#endif



#ifdef __cplusplus
t_q8	operator / (t_q8   x, t_q8   y)	{ return Q8_Div(x, y); }
t_q16	operator / (t_q16  x, t_q16  y)	{ return Q16_Div(x, y); }
t_q32	operator / (t_q32  x, t_q32  y)	{ return Q32_Div(x, y); }
t_q64	operator / (t_q64  x, t_q64  y)	{ return Q64_Div(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator / (t_q128 x, t_q128 y)	{ return Q128_Div(x, y); }
#endif
#endif
