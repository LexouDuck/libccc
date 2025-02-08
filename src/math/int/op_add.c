
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_ADD(BITS) \
t_u##BITS	U##BITS##_Add(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((x > U##BITS##_MAX - y),ERROR_RESULTRANGE, \
		"positive overflow for " SF_U##BITS " + " SF_U##BITS " = " SF_U##BITS " (as t_u"#BITS")", x, y, (t_u##BITS)(x + y)) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MAX) } \
	return (x + y); \
} \

DEFINEFUNC_UINT_ADD(8)
DEFINEFUNC_UINT_ADD(16)
DEFINEFUNC_UINT_ADD(32)
DEFINEFUNC_UINT_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ADD(128)
#endif



#define DEFINEFUNC_SINT_ADD(BITS) \
t_s##BITS	S##BITS##_Add(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if (x && y && SGN(x) == SGN(y)) \
	{ \
		if CCCERROR((x > S##BITS##_MAX - y), ERROR_RESULTRANGE, \
			"positive overflow for " SF_S##BITS " + " SF_S##BITS " = " SF_S##BITS " (as t_s"#BITS")", x, y, (t_s##BITS)(x + y)) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX) } \
		if CCCERROR((x < S##BITS##_MIN - y), ERROR_RESULTRANGE, \
			"negative overflow for " SF_S##BITS " + " SF_S##BITS " = " SF_S##BITS " (as t_s"#BITS")", x, y, (t_s##BITS)(x + y)) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MIN) } \
	} \
	return (x + y); \
} \

DEFINEFUNC_SINT_ADD(8)
DEFINEFUNC_SINT_ADD(16)
DEFINEFUNC_SINT_ADD(32)
DEFINEFUNC_SINT_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ADD(128)
#endif



/*
(+) + (+) = [0, +2N] => (x > MAX - y)
(+) + (-) = [-N, +N]
(-) + (+) = [-N, +N]
(-) + (-) = [-2N, 0] => (x < MIN - y)
*/

#ifdef __cplusplus
t_s8	operator + (t_s8   x, t_s8   y)	{ return S8_Add(x, y); }
t_s16	operator + (t_s16  x, t_s16  y)	{ return S16_Add(x, y); }
t_s32	operator + (t_s32  x, t_s32  y)	{ return S32_Add(x, y); }
t_s64	operator + (t_s64  x, t_s64  y)	{ return S64_Add(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator + (t_s128 x, t_s128 y)	{ return S128_Add(x, y); }
#endif
#endif
