
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvSinH, asinh)
#else
// fast sigmoid approximation for [-20,+20] and natural log for the rest
// score: 9.09	for [-40,+40]-> 200 tests
#define DEFINEFUNC_FLOAT_INVSINH(BITS) \
t_f##BITS	F##BITS##_InvSinH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	else if (x < -20)	return (-F##BITS##_Ln(-x - 1) - INV_SQRT_2); \
	else if (x > +20)	return (+F##BITS##_Ln(+x - 1) + INV_SQRT_2); \
	else \
		return (x / (1 + F##BITS##_Abs(-0.22103915 * x))); \
} \

DEFINEFUNC_FLOAT_INVSINH(32)
DEFINEFUNC_FLOAT_INVSINH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVSINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVSINH(128)
#endif

#endif
