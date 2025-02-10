
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_SUB(BITS) \
t_u##BITS	U##BITS##_Sub(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) && U##BITS##_IsInf(y)), ERROR_RESULTRANGE, \
		"result of subtracting infinite values is undefined") \
		return (U##BITS##_ERROR); \
	else if (U##BITS##_IsInf(x))	return (x); \
	if CCCERROR((x < y), ERROR_RESULTRANGE, \
		"negative overflow for " SF_U##BITS " - " SF_U##BITS " = " SF_U##BITS " (as t_u"#BITS")", x, y, (t_u##BITS)(x - y)) \
	{	LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MIN);	} \
	return (x - y); \
} \

DEFINEFUNC_UINT_SUB(8)
DEFINEFUNC_UINT_SUB(16)
DEFINEFUNC_UINT_SUB(32)
DEFINEFUNC_UINT_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_SUB(128)
#endif



#define DEFINEFUNC_SINT_SUB(BITS) \
t_s##BITS	S##BITS##_Sub(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) && S##BITS##_IsInf(y)) && S##BITS##_Sgn(x) == S##BITS##_Sgn(y), ERROR_RESULTRANGE, \
		"result of subtracting infinite values of identical sign is undefined") \
		return (S##BITS##_ERROR); \
	else if (S##BITS##_IsInf(x))	return (x); \
	else if (S##BITS##_IsInf(y))	return (-y); \
	if (x && y && S##BITS##_Sgn(x) != S##BITS##_Sgn(y)) \
	{ \
		if CCCERROR((x > S##BITS##_MAX + y), ERROR_RESULTRANGE, \
			"positive overflow for " SF_S##BITS " - " SF_S##BITS " = " SF_S##BITS " (as t_s"#BITS")", x, y, (t_s##BITS)(x - y)) \
		{	LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX);	} \
		if CCCERROR((x < S##BITS##_MIN + y), ERROR_RESULTRANGE, \
			"negative overflow for " SF_S##BITS " - " SF_S##BITS " = " SF_S##BITS " (as t_s"#BITS")", x, y, (t_s##BITS)(x - y)) \
		{	LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MIN);	} \
	} \
	return (x - y); \
} \

DEFINEFUNC_SINT_SUB(8)
DEFINEFUNC_SINT_SUB(16)
DEFINEFUNC_SINT_SUB(32)
DEFINEFUNC_SINT_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_SUB(128)
#endif



/*
(+) - (+) = [-N, +N]
(+) - (-) = [0, +2N] => (x > MAX + y)
(-) - (+) = [-2N, 0] => (x < MIN + y)
(-) - (-) = [-N, +N]
*/

/*
#ifdef __cplusplus
t_s8	operator - (t_s8   x, t_s8   y)	{ return S8_Sub(x, y); }
t_s16	operator - (t_s16  x, t_s16  y)	{ return S16_Sub(x, y); }
t_s32	operator - (t_s32  x, t_s32  y)	{ return S32_Sub(x, y); }
t_s64	operator - (t_s64  x, t_s64  y)	{ return S64_Sub(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator - (t_s128 x, t_s128 y)	{ return S128_Sub(x, y); }
#endif
#endif
*/
