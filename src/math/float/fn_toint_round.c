
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Round, round)
#else
#define DEFINEFUNC_FLOAT_ROUND(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Round(t_f##BITS x) \
{ \
	static const t_f##BITS toint = 1. / F##BITS##_EPSILON; \
	t_f##BITS y; \
	t_sint e; \
	u_cast_f##BITS cast; \
	cast.as_f = x; \
	e = (cast.as_u & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS; \
	if (e >= ((1 << (F##BITS##_EXPONENT_BITS - 1)) - 1) + F##BITS##_MANTISSA_BITS) \
		return x; \
	if (cast.as_u >> (BITS - 1)) \
		x = -x; \
	if (e < ((1 << (F##BITS##_EXPONENT_BITS - 1)) - 1) - 1) \
	{ \
		/* FORCE_EVAL(x + toint); */ \
		return (0 * cast.as_f); \
	} \
	y = x + toint - toint - x; \
	if (y > 0.5) \
		y = y + x - 1; \
	else if (y <= -0.5) \
		y = y + x + 1; \
	else \
		y = y + x; \
	if (cast.as_u >> (BITS - 1)) \
		y = -y; \
	return y; \
}

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_ROUND(16)
#endif
DEFINEFUNC_FLOAT_ROUND(32)

DEFINEFUNC_FLOAT_ROUND(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROUND(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROUND(128)
#endif

#endif
