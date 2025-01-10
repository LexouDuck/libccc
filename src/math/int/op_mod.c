
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MOD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Mod(t_u##BITS a, t_u##BITS b) \
{ \
	if CCCERROR((b == 0), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	return (a % b); \
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
t_s##BITS	S##BITS##_Mod(t_s##BITS a, t_s##BITS b) \
{ \
	if CCCERROR((b == 0), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (S##BITS##_Abs(a) % S##BITS##_Abs(b)) * S##BITS##_Sgn(b); \
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
