
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MOD(BITS) \
t_u##BITS	U##BITS##_Mod(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) && U##BITS##_IsInf(y)), ERROR_MATHDOMAIN, \
		"result of infinite value divided by infinite value is undefined") \
		return (U##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, \
		"result of zero divided by zero is undefined by convention") \
		return (U##BITS##_ERROR); \
	if CCCERROR((y == 0), ERROR_MATHDOMAIN, \
		"cannot get modulo of zero") \
		return (U##BITS##_ERROR); \
	return (x % y); \
} \

DEFINEFUNC_UINT_MOD(8)
DEFINEFUNC_UINT_MOD(16)
DEFINEFUNC_UINT_MOD(32)
DEFINEFUNC_UINT_MOD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MOD(128)
#endif



#define DEFINEFUNC_SINT_MOD(BITS) \
t_s##BITS	S##BITS##_Mod(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) && S##BITS##_IsInf(y)), ERROR_MATHDOMAIN, \
		"result of infinite value divided by infinite value is undefined") \
		return (S##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, \
		"result of zero divided by zero is undefined by convention") \
		return (S##BITS##_ERROR); \
	if CCCERROR((y == 0), ERROR_MATHDOMAIN, \
		"cannot get modulo of zero") \
		return (S##BITS##_ERROR); \
	if (S##BITS##_IsInf(y))	\
		return (S##BITS##_Sgn(x) == S##BITS##_Sgn(y) ? x : y); \
	return (x % y); \
} \

DEFINEFUNC_SINT_MOD(8)
DEFINEFUNC_SINT_MOD(16)
DEFINEFUNC_SINT_MOD(32)
DEFINEFUNC_SINT_MOD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_MOD(128)
#endif



/*
(+) mod (+) = [0, +N]
(+) mod (-) = [-N, 0]
(-) mod (+) = [0, +N]
(-) mod (-) = [-N, 0]
*/

#ifdef __cplusplus
t_s8	operator % (t_s8   x, t_s8   y)	{ return S8_Mod(x, y); }
t_s16	operator % (t_s16  x, t_s16  y)	{ return S16_Mod(x, y); }
t_s32	operator % (t_s32  x, t_s32  y)	{ return S32_Mod(x, y); }
t_s64	operator % (t_s64  x, t_s64  y)	{ return S64_Mod(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator % (t_s128 x, t_s128 y)	{ return S128_Mod(x, y); }
#endif
#endif
