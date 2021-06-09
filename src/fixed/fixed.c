
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE

#define DEFINEFUNC_FIXED_FROMINT(BITS) \
inline t_q##BITS	Q##BITS##_FromInt(t_sint number)						\
{																			\
	return ((t_q##BITS)(number * FIXED_DENOMINATOR));						\
}

#define DEFINEFUNC_FIXED_FROMFIXED(BITS) \
inline t_q##BITS	Q##BITS##_FromFixed(t_fixed number)						\
{																			\
	return ((t_q##BITS)(number));											\
}

#define DEFINEFUNC_FIXED_FROMFLOAT(BITS) \
inline t_q##BITS	Q##BITS##_FromFloat(t_float number)						\
{																			\
	if (number > Float_FromFixed(Q##BITS##_MAX))	return (Q##BITS##_MAX);	\
	if (number < Float_FromFixed(Q##BITS##_MIN))	return (Q##BITS##_MIN);	\
	return (																\
		(t_q##BITS)(Float_Truncate(number) * FIXED_DENOMINATOR) +			\
		(t_q##BITS)(Float_Mod(number, 1))									\
	);																		\
}



#define DEFINEFUNC_FIXED_FROM(BITS) \
inline t_q##BITS	Q##BITS##_From(											\
	t_s##BITS numerator,													\
	t_s##BITS denominator)													\
{																			\
	if (denominator == FIXED_DENOMINATOR)									\
		return ((t_q##BITS)numerator);										\
	return ((numerator * denominator) / FIXED_DENOMINATOR);					\
}



#define DEFINEFUNC_FIXED_INTEGERPART(BITS) \
inline t_q##BITS	Q##BITS##_IntegerPart(t_q##BITS number)					\
{																			\
	return (number / FIXED_DENOMINATOR * FIXED_DENOMINATOR);				\
}

#define DEFINEFUNC_FIXED_FRACTIONPART(BITS) \
inline t_q##BITS	Q##BITS##_FractionPart(t_q##BITS number)				\
{																			\
	return (number % FIXED_DENOMINATOR);									\
}



DEFINEFUNC_FIXED_FROMINT(		16)
DEFINEFUNC_FIXED_FROMFIXED(		16)
DEFINEFUNC_FIXED_FROMFLOAT(		16)
DEFINEFUNC_FIXED_FROM(			16)
DEFINEFUNC_FIXED_INTEGERPART(	16)
DEFINEFUNC_FIXED_FRACTIONPART(	16)

DEFINEFUNC_FIXED_FROMINT(		32)
DEFINEFUNC_FIXED_FROMFIXED(		32)
DEFINEFUNC_FIXED_FROMFLOAT(		32)
DEFINEFUNC_FIXED_FROM(			32)
DEFINEFUNC_FIXED_INTEGERPART(	32)
DEFINEFUNC_FIXED_FRACTIONPART(	32)

DEFINEFUNC_FIXED_FROMINT(		64)
DEFINEFUNC_FIXED_FROMFIXED(		64)
DEFINEFUNC_FIXED_FROMFLOAT(		64)
DEFINEFUNC_FIXED_FROM(			64)
DEFINEFUNC_FIXED_INTEGERPART(	64)
DEFINEFUNC_FIXED_FRACTIONPART(	64)

#ifdef __int128
DEFINEFUNC_FIXED_FROMINT(		128)
DEFINEFUNC_FIXED_FROMFIXED(		128)
DEFINEFUNC_FIXED_FROMFLOAT(		128)
DEFINEFUNC_FIXED_FROMFRACTION(	128)
DEFINEFUNC_FIXED_INTEGERPART(	128)
DEFINEFUNC_FIXED_FRACTIONPART(	128)
#endif
