
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_GCD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_GCD(t_u##BITS a, t_u##BITS b) \
{ \
	if (a && b) \
		while ((a %= b) && (b %= a)); \
	return (a | b); \
} \

DEFINEFUNC_UINT_GCD(8)
DEFINEFUNC_UINT_GCD(16)
DEFINEFUNC_UINT_GCD(32)
DEFINEFUNC_UINT_GCD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_GCD(128)
#endif



#define DEFINEFUNC_SINT_GCD(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_GCD(t_s##BITS a, t_s##BITS b) \
{ \
	if (a && b) \
		while ((a %= b) && (b %= a)); \
	return (a | b); \
} \

DEFINEFUNC_SINT_GCD(8)
DEFINEFUNC_SINT_GCD(16)
DEFINEFUNC_SINT_GCD(32)
DEFINEFUNC_SINT_GCD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_GCD(128)
#endif
