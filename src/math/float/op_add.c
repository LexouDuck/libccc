
#include "libccc/float.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_ADD(BITS) \
inline t_f##BITS	F##BITS##_Add(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a + b);											\
}



DEFINEFUNC_FLOAT_ADD(32)

DEFINEFUNC_FLOAT_ADD(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_ADD(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_ADD(128)
#endif
