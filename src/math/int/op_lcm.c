
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_LCM(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_LCM(t_u##BITS x, t_u##BITS y) \
{ \
	t_u##BITS gcd = U##BITS##_GCD(x, y); \
	if (gcd == 0) \
		gcd = 1; \
	return (x / gcd * y); \
} \

DEFINEFUNC_UINT_LCM(8)
DEFINEFUNC_UINT_LCM(16)
DEFINEFUNC_UINT_LCM(32)
DEFINEFUNC_UINT_LCM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_LCM(128)
#endif



#define DEFINEFUNC_SINT_LCM(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_LCM(t_s##BITS x, t_s##BITS y) \
{ \
	t_s##BITS gcd = S##BITS##_GCD(x, y); \
	if (gcd == 0) \
		gcd = 1; \
	return (x / gcd * y); \
} \

DEFINEFUNC_SINT_LCM(8)
DEFINEFUNC_SINT_LCM(16)
DEFINEFUNC_SINT_LCM(32)
DEFINEFUNC_SINT_LCM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_LCM(128)
#endif
