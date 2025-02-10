
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MUL(BITS) \
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
		(x._ != 0 && x._ != 1) && \
		(y._ != 0 && y._ != 1) && \
		(Memory_GetMSB(Q##BITS##_Abs(x)._) + Memory_GetMSB(Q##BITS##_Abs(y)._) >= BITS), ERROR_RESULTRANGE, \
		"%s overflow for " SF_Q##BITS " * " SF_Q##BITS " = " SF_Q##BITS " (as t_q"#BITS")", (Q##BITS##_Sgn(x)._ == Q##BITS##_Sgn(y)._ ? "positive" : "negative"), x._, y._, (t_s##BITS)(x._ * y._)) \
	{	LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (Q##BITS##_Sgn(x)._ == Q##BITS##_Sgn(y)._) ? Q##BITS##_MAX : Q##BITS##_MIN);	} \
	if CCCERROR( \
		!LIBCONFIG_FIXED_INF && \
		!LIBCONFIG_FIXED_NAN && \
		((x._ == Q##BITS##_MIN._ && y._ == -1) || (y._ == Q##BITS##_MIN._ && x._ == -1)), ERROR_RESULTRANGE, \
		"positive overflow when attempting to get inverse of minimum value for t_q"#BITS": " SF_Q##BITS, Q##BITS##_MIN) \
	{	LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX);	} \
	return (t_q##BITS){ (t_s##BITS)((x._ * y._) / Q##BITS##_DENOM) }; \
} \

DEFINEFUNC_FIXED_MUL(8)
DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MUL(128)
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
