
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MOD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Mod(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	if (U##BITS##_IsInf(y))	return (x); \
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
_INLINE() \
t_s##BITS	S##BITS##_Mod(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	if (S##BITS##_IsInf(y))	return (S##BITS##_Sgn(x) == S##BITS##_Sgn(y) ? x : y); \
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
