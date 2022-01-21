
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MOD(BITS) \
inline t_u##BITS	U##BITS##_Mod(t_u##BITS a, t_u##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (U##BITS##_ERROR);)	\
	return (a % b);													\
}

#define DEFINEFUNC_SINT_MOD(BITS) \
inline t_s##BITS	S##BITS##_Mod(t_s##BITS a, t_s##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (S##BITS##_ERROR);)	\
	return (a % b);													\
}

/*
(+) % (+) = [0, +N]
(+) % (-) = [-N, 0]
(-) % (+) = [-N, 0]
(-) % (-) = [0, +N]
*/



DEFINEFUNC_UINT_MOD(8)
DEFINEFUNC_SINT_MOD(8)

DEFINEFUNC_UINT_MOD(16)
DEFINEFUNC_SINT_MOD(16)

DEFINEFUNC_UINT_MOD(32)
DEFINEFUNC_SINT_MOD(32)

DEFINEFUNC_UINT_MOD(64)
DEFINEFUNC_SINT_MOD(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MOD(128)
DEFINEFUNC_SINT_MOD(128)
#endif
