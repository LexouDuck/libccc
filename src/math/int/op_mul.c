
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MUL(BITS) \
t_u##BITS	U##BITS##_Mul(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) && y == 0) || (U##BITS##_IsInf(y) && x == 0), ERROR_MATHDOMAIN, \
		"result of infinite value multiplied by 0 is undefined") \
		return (U##BITS##_ERROR); \
	else if (S##BITS##_IsInf(x) || S##BITS##_IsInf(y)) \
		return (U##BITS##_MAX); \
	if CCCERROR( \
		(x != 0 && x != 1) && \
		(y != 0 && y != 1) && \
		(Memory_GetMSB(x) + Memory_GetMSB(y) >= BITS), ERROR_RESULTRANGE, \
		"positive overflow for " SF_U##BITS " * " SF_U##BITS " = " SF_U##BITS " (as t_u"#BITS")", x, y, (t_u##BITS)(x * y)) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MAX) } \
	return (x * y); \
} \

DEFINEFUNC_UINT_MUL(8)
DEFINEFUNC_UINT_MUL(16)
DEFINEFUNC_UINT_MUL(32)
DEFINEFUNC_UINT_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MUL(128)
#endif



#define DEFINEFUNC_SINT_MUL(BITS) \
t_s##BITS	S##BITS##_Mul(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) && y == 0) || (S##BITS##_IsInf(y) && x == 0), ERROR_MATHDOMAIN, \
		"result of infinite value multiplied by 0 is undefined") \
		return (S##BITS##_ERROR); \
	else if (S##BITS##_IsInf(x))	return (x * S##BITS##_Sgn(y)); \
	else if (S##BITS##_IsInf(y))	return (y * S##BITS##_Sgn(x)); \
	if CCCERROR( \
		(x != 0 && x != 1) && \
		(y != 0 && y != 1) && \
		(Memory_GetMSB(S##BITS##_Abs(x)) + Memory_GetMSB(S##BITS##_Abs(y)) >= BITS), ERROR_RESULTRANGE, \
		"%s overflow for " SF_S##BITS " * " SF_S##BITS " = " SF_S##BITS " (as t_s"#BITS")", (S##BITS##_Sgn(x) == S##BITS##_Sgn(y) ? "positive" : "negative"), x, y, (t_s##BITS)(x * y)) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, (S##BITS##_Sgn(x) == S##BITS##_Sgn(y)) ? S##BITS##_MAX : S##BITS##_MIN) } \
	if CCCERROR( \
		!LIBCONFIG_SINT_INF && \
		!LIBCONFIG_SINT_NAN && \
		((x == S##BITS##_MIN && y == -1) || (y == S##BITS##_MIN && x == -1)), ERROR_RESULTRANGE, \
		"positive overflow when attempting to get inverse of minimum value for t_s"#BITS": " SF_S##BITS, S##BITS##_MIN) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX) } \
	return (x * y); \
} \

DEFINEFUNC_SINT_MUL(8)
DEFINEFUNC_SINT_MUL(16)
DEFINEFUNC_SINT_MUL(32)
DEFINEFUNC_SINT_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_MUL(128)
#endif



/*
(+) * (+) = [0, +N²] => ()
(+) * (-) = [-N², 0] => ()
(-) * (+) = [-N², 0] => ()
(-) * (-) = [0, +N²] => ()
*/

/*
#ifdef __cplusplus
t_s8	operator * (t_s8   x, t_s8   y)	{ return S8_Mul(x, y); }
t_s16	operator * (t_s16  x, t_s16  y)	{ return S16_Mul(x, y); }
t_s32	operator * (t_s32  x, t_s32  y)	{ return S32_Mul(x, y); }
t_s64	operator * (t_s64  x, t_s64  y)	{ return S64_Mul(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator * (t_s128 x, t_s128 y)	{ return S128_Mul(x, y); }
#endif
#endif
*/
