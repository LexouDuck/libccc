
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Mod, fmod)
#else
#define DEFINEFUNC_FLOAT_MOD(BITS) \
t_f##BITS	F##BITS##_Mod(t_f##BITS a, t_f##BITS b) \
{ \
	t_f##BITS abs_a; \
	t_f##BITS abs_b; \
	t_f##BITS dividend; \
	t_f##BITS divisor; \
	t_s64 expo_a; \
	t_s64 expo_b; \
	if (IS_NAN(a) || IS_NAN(b)) \
		return (a + b); \
	else if (IS_INF(a) || (b == 0.0)) \
		return (NAN); \
	abs_a = F##BITS##_Abs(a); \
	abs_b = F##BITS##_Abs(b); \
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
		return F##BITS##_CopySign(dividend, a); \
	} \
	else \
	{ \
		return (a); \
	} \
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
