
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_TRUNC(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Trunc(t_q##BITS number) \
{ \
	return (number & ~Q##BITS##_FractionPart(number)); \
} \

DEFINEFUNC_FIXED_TRUNC(16)
DEFINEFUNC_FIXED_TRUNC(32)
DEFINEFUNC_FIXED_TRUNC(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TRUNC(128)
#endif
