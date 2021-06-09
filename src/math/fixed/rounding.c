
#include "libccc/fixed.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ROUND(BITS) \
inline t_q##BITS	Q##BITS##_Round(t_q##BITS number)						\
{																			\
	t_q##BITS fraction = (number & (FIXED_MASK_FRACTIONPART));				\
	if (fraction < FIXED_MAX_FRACTIONPART / 2)								\
		return (number - fraction);											\
	else return (number + (FIXED_MAX_FRACTIONPART - fraction));				\
}



#define DEFINEFUNC_FIXED_TRUNC(BITS) \
inline t_q##BITS	Q##BITS##_Truncate(t_q##BITS number)									\
{																							\
	return ((t_q##BITS)((number >> FIXED_BITS_FRACTIONPART) << FIXED_BITS_FRACTIONPART));	\
} // TODO fix this



#define DEFINEFUNC_FIXED_FLOOR(BITS) \
// TODO

#define DEFINEFUNC_FIXED_CEIL(BITS) \
// TODO



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
