
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_SUB(BITS) \
t_q##BITS	Q##BITS##_Sub(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((Q##BITS##_IsInf(x) && Q##BITS##_IsInf(y)) && Q##BITS##_Sgn(x)._ == Q##BITS##_Sgn(y)._, ERROR_RESULTRANGE, \
		"result of subtracting infinite values of identical sign is undefined") \
		return (Q##BITS##_ERROR); \
	else if (Q##BITS##_IsInf(x))	return (x); \
	else if (Q##BITS##_IsInf(y))	return (t_q##BITS){ (t_s##BITS)(-y._) }; \
	if (x._ && y._ && SGN(x._) != SGN(y._)) \
	{ \
		if CCCERROR((x._ > Q##BITS##_MAX._ + y._), ERROR_RESULTRANGE, \
			"positive overflow for " SF_Q##BITS " - " SF_Q##BITS " = " SF_Q##BITS " (as t_q"#BITS")", x._, y._, (t_s##BITS)(x._ - y._)) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX) } \
		if CCCERROR((x._ < Q##BITS##_MIN._ + y._), ERROR_RESULTRANGE, \
			"negative overflow for " SF_Q##BITS " - " SF_Q##BITS " = " SF_Q##BITS " (as t_q"#BITS")", x._, y._, (t_s##BITS)(x._ - y._)) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MIN) } \
	} \
	t_s##BITS i1 = (x._ / Q##BITS##_DENOM); \
	t_s##BITS i2 = (y._ / Q##BITS##_DENOM); \
	if CCCERROR((i2 < 0) && (i1 > (Q##BITS##_MAX._ / Q##BITS##_DENOM) + i2), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX); } \
	if CCCERROR((i2 > 0) && (i1 < (Q##BITS##_MIN._ / Q##BITS##_DENOM) + i2), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MIN); } \
	return (t_q##BITS){ (t_s##BITS)(x._ - y._) }; \
} \

DEFINEFUNC_FIXED_SUB(8)
DEFINEFUNC_FIXED_SUB(16)
DEFINEFUNC_FIXED_SUB(32)
DEFINEFUNC_FIXED_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_SUB(128)
#endif



#ifdef __cplusplus
t_q8	operator - (t_q8   x, t_q8   y)	{ return Q8_Sub(x, y); }
t_q16	operator - (t_q16  x, t_q16  y)	{ return Q16_Sub(x, y); }
t_q32	operator - (t_q32  x, t_q32  y)	{ return Q32_Sub(x, y); }
t_q64	operator - (t_q64  x, t_q64  y)	{ return Q64_Sub(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator - (t_q128 x, t_q128 y)	{ return Q128_Sub(x, y); }
#endif
#endif
