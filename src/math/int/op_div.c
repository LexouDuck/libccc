
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_DIV(BITS) \
t_u##BITS	U##BITS##_Div(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) && U##BITS##_IsInf(y)), ERROR_MATHDOMAIN, \
		"result of infinite value divided by infinite value is undefined") \
		return (U##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, \
		"result of zero divided by zero is undefined by convention") \
		return (U##BITS##_ERROR); \
	if CCCERROR((!LIBCONFIG_UINT_INF && y == 0), ERROR_MATHDOMAIN, \
		"cannot divide by zero unless infinite value is configured") \
		return (U##BITS##_ERROR); \
	if (y == 0)	return (U##BITS##_MAX); \
	if (U##BITS##_IsInf(x))	return (U##BITS##_MAX); \
	if (U##BITS##_IsInf(y))	return (0); \
	return (x / y); \
} \

DEFINEFUNC_UINT_DIV(8)
DEFINEFUNC_UINT_DIV(16)
DEFINEFUNC_UINT_DIV(32)
DEFINEFUNC_UINT_DIV(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_DIV(128)
#endif



#define DEFINEFUNC_SINT_DIV(BITS) \
t_s##BITS	S##BITS##_Div(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) && S##BITS##_IsInf(y)), ERROR_MATHDOMAIN, \
		"result of infinite value divided by infinite value is undefined") \
		return (S##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, \
		"result of zero divided by zero is undefined by convention") \
		return (S##BITS##_ERROR); \
	if CCCERROR((!LIBCONFIG_SINT_INF && y == 0), ERROR_MATHDOMAIN, \
		"cannot divide by zero unless infinite value is configured") \
		return (S##BITS##_ERROR); \
	if CCCERROR( \
		!LIBCONFIG_SINT_INF && \
		!LIBCONFIG_SINT_NAN && \
		(x == S##BITS##_MIN && y == -1), ERROR_RESULTRANGE, \
		"positive overflow when attempting to get inverse of minimum value for t_s"#BITS": " SF_S##BITS, S##BITS##_MIN) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX) \
		return (S##BITS##_MIN); \
	} \
	if (y == 0) \
		return ((S##BITS##_MAX * S##BITS##_Sgn(x))); \
	if (S##BITS##_IsInf(x)) \
		return ((S##BITS##_Sgn(x) * S##BITS##_Sgn(y)) * S##BITS##_MAX); \
	if (S##BITS##_IsInf(y)) \
		return (0); \
	return (x / y); \
} \

DEFINEFUNC_SINT_DIV(8)
DEFINEFUNC_SINT_DIV(16)
DEFINEFUNC_SINT_DIV(32)
DEFINEFUNC_SINT_DIV(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_DIV(128)
#endif



/*
(+) / (+) = [0, +N]
(+) / (-) = [-N, 0]
(-) / (+) = [-N, 0]
(-) / (-) = [0, +N]
*/

#ifdef __cplusplus
t_s8	operator / (t_s8   x, t_s8   y)	{ return S8_Div(x, y); }
t_s16	operator / (t_s16  x, t_s16  y)	{ return S16_Div(x, y); }
t_s32	operator / (t_s32  x, t_s32  y)	{ return S32_Div(x, y); }
t_s64	operator / (t_s64  x, t_s64  y)	{ return S64_Div(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator / (t_s128 x, t_s128 y)	{ return S128_Div(x, y); }
#endif
#endif
