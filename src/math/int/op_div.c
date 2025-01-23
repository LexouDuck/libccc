
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
	if CCCERROR((U##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
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
	if CCCERROR((S##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
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
