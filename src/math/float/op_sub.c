
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_SUB(BITS) \
inline t_f##BITS	F##BITS##_Sub(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a - b);											\
}



DEFINEFUNC_FLOAT_SUB(32)

DEFINEFUNC_FLOAT_SUB(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_SUB(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_SUB(128)
#endif
