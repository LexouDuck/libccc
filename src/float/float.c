
#include <float.h> // TODO remove this after changing FLOAT_EPSILON macros

#include "libccc/float.h"
#include "libccc/math/math.h"



#define DEFINEFUNC_FLOAT(BITS) \
t_f##BITS	F##BITS(t_fixed mantissa, t_sint exponent)		\
{															\
	return ((t_f##BITS)(mantissa >> FIXED_BITS_FRACTIONPART) * Math_Pow(2, exponent));	\
}															\



DEFINEFUNC_FLOAT(32)

DEFINEFUNC_FLOAT(64)

#ifdef	__float80
DEFINEFUNC_FLOAT(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT(128)
#endif
