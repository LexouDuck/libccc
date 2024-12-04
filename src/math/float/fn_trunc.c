
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Trunc, trunc)
#else
#define DEFINEFUNC_FLOAT_TRUNC(BITS) \
extern inline \
t_f##BITS	F##BITS##_Trunc(t_f##BITS x) \
{ \
	t_u##BITS mantissa; \
	u_cast_f##BITS cast = {x}; \
	t_sint e = (t_sint)(cast.value_uint >> F##BITS##_MANTISSA_BITS & (F##BITS##_EXPONENT >> F##BITS##_MANTISSA_BITS)) - (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) + 12; \
	if (e >= F##BITS##_MANTISSA_BITS + F##BITS##_EXPONENT_BITS) \
		return x; \
	if (e < F##BITS##_EXPONENT_BITS) \
		e = 1; \
	mantissa = -1ull >> e; \
	if ((cast.value_uint & mantissa) == 0) \
		return x; \
	/* FORCE_EVAL(x + 0x1p120f); */ \
	cast.value_uint &= ~mantissa; \
	return cast.value_float; \
} \

DEFINEFUNC_FLOAT_TRUNC(32)
DEFINEFUNC_FLOAT_TRUNC(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TRUNC(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TRUNC(128)
#endif

#endif
