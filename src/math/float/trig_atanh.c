
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvTanH, atanh)
#else
// taylor series approximation
// score: 4.81	for [-1,+1]-> 200 tests
#define DEFINEFUNC_FLOAT_INVTANH(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x)								\
{																		\
	static const t_f##BITS p = 0.6232;									\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) return (NAN);		\
	if CCCERROR((F##BITS##_Abs(x) > 1.), ERROR_MATHDOMAIN, NULL)		\
		return (NAN);													\
	if (x == 0)															\
		return (0);														\
	if (x < -0.6)	return (+F##BITS##_Ln(p * +x + p) * 0.5);			\
	if (x > +0.6)	return (-F##BITS##_Ln(p * -x + p) * 0.5);			\
	t_f##BITS result = x / (1 - 0.418 * F##BITS##_Abs(x));				\
	t_f##BITS power = x * x * x;										\
	result += (-1.5 * power);	power *= (x * x);						\
	result += (+4.4 * power);	power *= (x * x);						\
	result += (-2.4 * power);	power *= (x * x);						\
	result += (-5.8 * power);											\
	return (result);													\
}

DEFINEFUNC_FLOAT_INVTANH(32)
DEFINEFUNC_FLOAT_INVTANH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVTANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVTANH(128)
#endif

#endif
