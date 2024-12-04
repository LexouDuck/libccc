
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(CopySign, copysign)
#else
#define DEFINEFUNC_FLOAT_COPYSIGN(BITS) \
t_f##BITS F##BITS##_CopySign(t_f##BITS x, t_f##BITS y) \
{ \
	u_cast_f##BITS cast_x; \
	u_cast_f##BITS cast_y; \
	cast_x.value_float = x; \
	cast_y.value_float = y; \
	cast_x.value_uint &= ~F##BITS##_SIGNED; \
	cast_x.value_uint |= cast_y.value_uint & F##BITS##_SIGNED; \
	return (cast_x.value_float); \
}

DEFINEFUNC_FLOAT_COPYSIGN(32)
DEFINEFUNC_FLOAT_COPYSIGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COPYSIGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COPYSIGN(128)
#endif

#endif
