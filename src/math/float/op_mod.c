
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Mod, fmod)
#else
#define DEFINEFUNC_FLOAT_MOD(BITS) \
inline t_f##BITS	F##BITS##_Mod(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a - (F##BITS##_Round(a / b) * b));				\
}

DEFINEFUNC_FLOAT_MOD(32)
DEFINEFUNC_FLOAT_MOD(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_MOD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_MOD(128)
#endif

#endif
