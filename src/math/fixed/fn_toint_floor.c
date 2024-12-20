
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FLOOR(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Floor(t_q##BITS number) \
{ \
	return ((number < 0) ? \
		(number + Q##BITS##_FractionPart(number)) : \
		(number - Q##BITS##_FractionPart(number))); \
} \

DEFINEFUNC_FIXED_FLOOR(16)
DEFINEFUNC_FIXED_FLOOR(32)
DEFINEFUNC_FIXED_FLOOR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FLOOR(128)
#endif
