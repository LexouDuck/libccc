
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_LCM(BITS) \
inline t_u##BITS	U##BITS##_LCM(t_u##BITS a, t_u##BITS b) \
{ \
	return (a / U##BITS##_GCD(a, b) * b); \
} \

DEFINEFUNC_UINT_LCM(8)
DEFINEFUNC_UINT_LCM(16)
DEFINEFUNC_UINT_LCM(32)
DEFINEFUNC_UINT_LCM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_LCM(128)
#endif



#define DEFINEFUNC_SINT_LCM(BITS) \
inline t_s##BITS	S##BITS##_LCM(t_s##BITS a, t_s##BITS b) \
{ \
	return (a / S##BITS##_GCD(a, b) * b); \
} \

DEFINEFUNC_SINT_LCM(8)
DEFINEFUNC_SINT_LCM(16)
DEFINEFUNC_SINT_LCM(32)
DEFINEFUNC_SINT_LCM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_LCM(128)
#endif
