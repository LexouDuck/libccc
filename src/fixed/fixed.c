
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math.h"
#include "libccc/math/float.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_INTEGERPART(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_IntegerPart(t_q##BITS number) \
{ \
	if (Q##BITS##_IsNaN(number)) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(number)) \
		return (number); \
	number._ = (t_s##BITS)((number._ / Q##BITS##_DENOM) * Q##BITS##_DENOM); \
	return (number); \
} \

DEFINEFUNC_FIXED_INTEGERPART(8)
DEFINEFUNC_FIXED_INTEGERPART(16)
DEFINEFUNC_FIXED_INTEGERPART(32)
DEFINEFUNC_FIXED_INTEGERPART(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_INTEGERPART(128)
#endif

#define DEFINEFUNC_FIXED_FRACTIONPART(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_FractionPart(t_q##BITS number) \
{ \
	if (Q##BITS##_IsNaN(number)) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(number)) \
		return ((t_q##BITS){ 0 }); \
	number._ %= Q##BITS##_DENOM; \
	return (number); \
} \

DEFINEFUNC_FIXED_FRACTIONPART(8)
DEFINEFUNC_FIXED_FRACTIONPART(16)
DEFINEFUNC_FIXED_FRACTIONPART(32)
DEFINEFUNC_FIXED_FRACTIONPART(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FRACTIONPART(128)
#endif
