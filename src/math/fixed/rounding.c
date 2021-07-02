
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ROUND(BITS) \
inline t_q##BITS	Q##BITS##_Round(t_q##BITS number)			\
{																\
	t_q##BITS fraction = Q##BITS##_FractionPart(number);		\
	if (fraction < FIXED_DENOMINATOR / 2)						\
		return (number - fraction);								\
	else return (number + (FIXED_DENOMINATOR - fraction));		\
}



#define DEFINEFUNC_FIXED_TRUNC(BITS) \
inline t_q##BITS	Q##BITS##_Truncate(t_q##BITS number)		\
{																\
	return (number & ~Q##BITS##_FractionPart(number));			\
} // TODO test this



#define DEFINEFUNC_FIXED_FLOOR(BITS) \
inline t_q##BITS	Q##BITS##_Floor(t_q##BITS number)			\
{																\
	return ((number < 0) ?										\
		(number + Q##BITS##_FractionPart(number)) :				\
		(number - Q##BITS##_FractionPart(number)));				\
} // TODO test this



#define DEFINEFUNC_FIXED_CEIL(BITS) \
inline t_q##BITS	Q##BITS##_Ceiling(t_q##BITS number)			\
{																\
	return ((number < 0) ?										\
		(number - (FIXED_DENOMINATOR - Q##BITS##_FractionPart(number))) :	\
		(number + (FIXED_DENOMINATOR - Q##BITS##_FractionPart(number))));	\
} // TODO test this



DEFINEFUNC_FIXED_ROUND(	16)
DEFINEFUNC_FIXED_TRUNC(	16)
DEFINEFUNC_FIXED_FLOOR(	16)
DEFINEFUNC_FIXED_CEIL(	16)

DEFINEFUNC_FIXED_ROUND(	32)
DEFINEFUNC_FIXED_TRUNC(	32)
DEFINEFUNC_FIXED_FLOOR(	32)
DEFINEFUNC_FIXED_CEIL(	32)

DEFINEFUNC_FIXED_ROUND(	64)
DEFINEFUNC_FIXED_TRUNC(	64)
DEFINEFUNC_FIXED_FLOOR(	64)
DEFINEFUNC_FIXED_CEIL(	64)

#ifdef __int128
DEFINEFUNC_FIXED_ROUND(	128)
DEFINEFUNC_FIXED_TRUNC(	128)
DEFINEFUNC_FIXED_FLOOR(	128)
DEFINEFUNC_FIXED_CEIL(	128)
#endif
