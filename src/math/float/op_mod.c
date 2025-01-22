
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Mod, fmod)
#else
#define DEFINEFUNC_FLOAT_MOD(BITS) \
t_f##BITS	F##BITS##_Mod(t_f##BITS x, t_f##BITS y) \
{ \
	t_f##BITS abs_a; \
	t_f##BITS abs_b; \
	t_f##BITS dividend; \
	t_f##BITS divisor; \
	t_s64 expo_a; \
	t_s64 expo_b; \
	if (IS_NAN(x) || IS_NAN(y)) \
		return (x + y); \
	else if (IS_INF(x) || (y == 0.0)) \
		return (NAN); \
	abs_a = F##BITS##_Abs(x); \
	abs_b = F##BITS##_Abs(y); \
	if (abs_a >= abs_b) \
	{ \
		dividend = abs_a; \
		expo_a = F##BITS##_GetExp2(abs_a); \
		expo_b = F##BITS##_GetExp2(abs_b); \
		divisor = F##BITS##_From(abs_b, expo_a - expo_b); \
		if (divisor <= dividend * 0.5) \
		{ \
			divisor += divisor; \
		} \
		while (divisor >= abs_b) \
		{ \
			if (dividend >= divisor) \
			{ \
				dividend -= divisor; \
			} \
			divisor *= 0.5; \
		} \
		return F##BITS##_CopySign(dividend, x); \
	} \
	else \
	{ \
		return (x); \
	} \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_MOD(16)
#endif
DEFINEFUNC_FLOAT_MOD(32)

DEFINEFUNC_FLOAT_MOD(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_MOD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_MOD(128)
#endif

#endif
