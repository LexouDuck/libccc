
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_MUL(BITS) \
inline t_f##BITS	F##BITS##_Mul(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a * b);											\
}



DEFINEFUNC_FLOAT_MUL(32)

DEFINEFUNC_FLOAT_MUL(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_MUL(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_MUL(128)
#endif
