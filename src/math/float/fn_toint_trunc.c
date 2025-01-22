
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Trunc, trunc)
#else
#define DEFINEFUNC_FLOAT_TRUNC(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Trunc(t_f##BITS x) \
{ \
	t_u##BITS mantissa; \
	u_cast_f##BITS cast = {x}; \
	t_s##BITS e = (t_s##BITS)(cast.value_uint >> F##BITS##_MANTISSA_BITS & (F##BITS##_EXPONENT_MASK >> F##BITS##_MANTISSA_BITS)) - \
			(F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) + (F##BITS##_EXPONENT_BITS + 1); \
	if (e >= F##BITS##_MANTISSA_BITS + (F##BITS##_EXPONENT_BITS + 1)) \
		return x; \
	if (e < (F##BITS##_EXPONENT_BITS + 1)) \
		e = 1; \
	mantissa = (t_u##BITS)-1 >> e; \
	if ((cast.value_uint & mantissa) == 0) \
		return x; \
	/* FORCE_EVAL(x + 0x1p120f); */ \
	cast.value_uint &= ~mantissa; \
	return cast.value_float; \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_TRUNC(16)
#endif
DEFINEFUNC_FLOAT_TRUNC(32)

DEFINEFUNC_FLOAT_TRUNC(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TRUNC(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TRUNC(128)
#endif

#endif
