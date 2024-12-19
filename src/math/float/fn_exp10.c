
#include "libccc/memory.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALFUNCTION(Exp10, exp10)
#else
#define DEFINEFUNC_FLOAT_EXP10(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Exp10(t_f##BITS x) \
{ \
	static const t_f##BITS p10[] = \
	{ \
		1e-15, \
		1e-14, \
		1e-13, \
		1e-12, \
		1e-11, \
		1e-10, \
		1e-9, \
		1e-8, \
		1e-7, \
		1e-6, \
		1e-5, \
		1e-4, \
		1e-3, \
		1e-2, \
		1e-1, \
		1e0, \
		1e+1, \
		1e+2, \
		1e+3, \
		1e+4, \
		1e+5, \
		1e+6, \
		1e+7, \
		1e+8, \
		1e+9, \
		1e+10, \
		1e+11, \
		1e+12, \
		1e+13, \
		1e+14, \
		1e+15, \
	}; \
	t_f##BITS n, y = F##BITS##_SplitInt(x, &n); \
	u_cast_f##BITS u = {n}; \
	/* fabs(n) < 16 without raising invalid on NaN */ \
	if (((u.value_uint & F##BITS##_EXPONENT) >> F##BITS##_MANTISSA_BITS) < ((1 << (F##BITS##_EXPONENT_BITS - 1)) - 1) + 4) \
	{ \
		if (!y) \
			return (p10[(int)n + 15]); \
		y = F##BITS##_Exp2((t_f##BITS)3.32192809488736234787031942948939 * y); \
		return (y * p10[(int)n + 15]); \
	} \
	return (F##BITS##_Pow(10.0, x)); \
} \

DEFINEFUNC_FLOAT_EXP10(32)
DEFINEFUNC_FLOAT_EXP10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP10(128)
#endif

#endif
