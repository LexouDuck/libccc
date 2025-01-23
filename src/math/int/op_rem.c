
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_REM(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Rem(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (U##BITS##_ERROR); \
	if CCCERROR((U##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	return (x % y); \
} \

DEFINEFUNC_UINT_REM(8)
DEFINEFUNC_UINT_REM(16)
DEFINEFUNC_UINT_REM(32)
DEFINEFUNC_UINT_REM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_REM(128)
#endif



#define DEFINEFUNC_SINT_REM(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Rem(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (S##BITS##_ERROR); \
	if CCCERROR((S##BITS##_IsInf(x) || (y == 0)), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (S##BITS##_Abs(x) % S##BITS##_Abs(y)) * S##BITS##_Sgn(x); \
} \

DEFINEFUNC_SINT_REM(8)
DEFINEFUNC_SINT_REM(16)
DEFINEFUNC_SINT_REM(32)
DEFINEFUNC_SINT_REM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_REM(128)
#endif

/*
(+) rem (+) = [0, +N]
(+) rem (-) = [0, +N]
(-) rem (+) = [-N, 0]
(-) rem (-) = [-N, 0]
*/
