
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Floor, floor)
#else
#define DEFINEFUNC_FLOAT_FLOOR(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Floor(t_f##BITS x) \
{ \
	static const t_f##BITS toint = 1. / F##BITS##_EPSILON; \
	t_f##BITS y; \
	u_cast_f##BITS cast = {x}; \
	int e = cast.value_uint >> F##BITS##_MANTISSA_BITS & (F##BITS##_EXPONENT_MASK >> F##BITS##_MANTISSA_BITS); \
	if (e >= (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) + F##BITS##_MANTISSA_BITS || x == 0) \
		return x; \
	/* y = int(x) - x, where int(x) is an integer neighbor of x */ \
	if (cast.value_uint >> (BITS - 1)) \
		y = x - toint + toint - x; \
	else \
		y = x + toint - toint - x; \
	/* special case because of non-nearest rounding modes */ \
	if (e <= (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) - 1) \
	{ \
		/* FORCE_EVAL(y); */ \
		return (cast.value_uint >> (BITS - 1)) ? -1. : 0.; \
	} \
	if (y > 0) \
		return x + y - 1; \
	return x + y; \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FLOOR(16)
#endif
DEFINEFUNC_FLOAT_FLOOR(32)

DEFINEFUNC_FLOAT_FLOOR(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FLOOR(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FLOOR(128)
#endif

#endif
