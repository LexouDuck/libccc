
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_SGN(BITS) \
extern inline \
t_f##BITS	F##BITS##_Sgn(t_f##BITS x) \
{ \
	return (SGN(x)); \
} \

DEFINEFUNC_FLOAT_SGN(32)
DEFINEFUNC_FLOAT_SGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SGN(128)
#endif
