
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FROMINT(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_FromInt(t_sint number) \
{ \
	return ((t_q##BITS)(number * FIXED_DENOMINATOR)); \
} \

DEFINEFUNC_FIXED_FROMINT(16)
DEFINEFUNC_FIXED_FROMINT(32)
DEFINEFUNC_FIXED_FROMINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMINT(128)
#endif

// TODO fix this to be multi-type
#define DEFINEFUNC_FIXED_FROMFIXED(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_FromFixed(t_fixed number) \
{ \
	return ((t_q##BITS)(number)); \
} \

DEFINEFUNC_FIXED_FROMFIXED(16)
DEFINEFUNC_FIXED_FROMFIXED(32)
DEFINEFUNC_FIXED_FROMFIXED(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMFIXED(128)
#endif

#define DEFINEFUNC_FIXED_FROMFLOAT(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_FromFloat(t_float number) \
{ \
	if (number > Float_FromFixed((t_fixed)Q##BITS##_MAX))	return (Q##BITS##_MAX); \
	if (number < Float_FromFixed((t_fixed)Q##BITS##_MIN))	return (Q##BITS##_MIN); \
	return ( \
		(t_q##BITS)(Float_Trunc(number) * FIXED_DENOMINATOR) + \
		(t_q##BITS)(Float_Mod(number, 1))); \
} \

DEFINEFUNC_FIXED_FROMFLOAT(16)
DEFINEFUNC_FIXED_FROMFLOAT(32)
DEFINEFUNC_FIXED_FROMFLOAT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMFLOAT(128)
#endif



#define DEFINEFUNC_FIXED_FROM(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_From( \
	t_s##BITS numerator, \
	t_s##BITS denominator) \
{ \
	if CCCERROR((denominator == 0), ERROR_MATHDOMAIN, \
		"fraction denominator should never be zero") \
		return (0); \
	if (denominator == FIXED_DENOMINATOR) \
		return ((t_q##BITS)numerator); \
	return ((numerator * FIXED_DENOMINATOR) / denominator); \
} \

DEFINEFUNC_FIXED_FROM(16)
DEFINEFUNC_FIXED_FROM(32)
DEFINEFUNC_FIXED_FROM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROM(128)
#endif



#define DEFINEFUNC_FIXED_INTEGERPART(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_IntegerPart(t_q##BITS number) \
{ \
	return (number / FIXED_DENOMINATOR); \
} \

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
	return (number % FIXED_DENOMINATOR); \
} \

DEFINEFUNC_FIXED_FRACTIONPART(16)
DEFINEFUNC_FIXED_FRACTIONPART(32)
DEFINEFUNC_FIXED_FRACTIONPART(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FRACTIONPART(128)
#endif
