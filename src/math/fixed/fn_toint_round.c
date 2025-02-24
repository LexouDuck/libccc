
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ROUND(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Round(t_q##BITS number) \
{ \
	t_q##BITS fraction = Q##BITS##_FractionPart(number); \
	if (fraction._ < Q##BITS##_DENOM / 2) \
		return (t_q##BITS){ (t_s##BITS)(number._ - fraction._) }; \
	else return (t_q##BITS){ (t_s##BITS)(number._ + (Q##BITS##_DENOM - fraction._)) }; \
} \

DEFINEFUNC_FIXED_ROUND(8)
DEFINEFUNC_FIXED_ROUND(16)
DEFINEFUNC_FIXED_ROUND(32)
DEFINEFUNC_FIXED_ROUND(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROUND(128)
#endif
