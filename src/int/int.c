
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_INT_FROMINT(BITS) \
inline t_s##BITS	S##BITS##_FromInt(t_sint number)						\
{																			\
	return ((t_s##BITS)number);												\
}

#define DEFINEFUNC_INT_FROMFIXED(BITS) \
inline t_s##BITS	S##BITS##_FromFixed(t_fixed number)						\
{																			\
	return ((t_s##BITS)number);												\
}

#define DEFINEFUNC_INT_FROMFLOAT(BITS) \
inline t_s##BITS	S##BITS##_FromFloat(t_float number)						\
{																			\
	return ((t_s##BITS)number);												\
}



DEFINEFUNC_INT_FROMINT(		16)
DEFINEFUNC_INT_FROMFIXED(	16)
DEFINEFUNC_INT_FROMFLOAT(	16)

DEFINEFUNC_INT_FROMINT(		32)
DEFINEFUNC_INT_FROMFIXED(	32)
DEFINEFUNC_INT_FROMFLOAT(	32)

DEFINEFUNC_INT_FROMINT(		64)
DEFINEFUNC_INT_FROMFIXED(	64)
DEFINEFUNC_INT_FROMFLOAT(	64)

#ifdef __int128
DEFINEFUNC_INT_FROMINT(		128)
DEFINEFUNC_INT_FROMFIXED(	128)
DEFINEFUNC_INT_FROMFLOAT(	128)
#endif
