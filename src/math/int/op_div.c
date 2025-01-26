
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_DIV(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Div(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) && U##BITS##_IsInf(y)), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	if (U##BITS##_IsInf(x))	return (U##BITS##_MAX); \
	if (U##BITS##_IsInf(y))	return (0); \
	if (y == 0)	return (LIBCONFIG_UINT_INF ? U##BITS##_MAX : U##BITS##_ERROR); \
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
_INLINE() \
t_s##BITS	S##BITS##_Div(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) && S##BITS##_IsInf(y)), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR(((x == 0) && (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	if (S##BITS##_IsInf(x))	return (S##BITS##_MAX * (S##BITS##_Sgn(x) * S##BITS##_Sgn(y))); \
	if (S##BITS##_IsInf(y))	return (            0 * (S##BITS##_Sgn(x) * S##BITS##_Sgn(y))); \
	if (y == 0)	return (LIBCONFIG_SINT_INF ? (S##BITS##_MAX * S##BITS##_Sgn(x)) : S##BITS##_ERROR); \
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
