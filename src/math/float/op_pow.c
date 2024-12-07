
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Pow, pow)
#elif 1 // LIBCONFIG_USE_CCC_MATH

#if 1
// crazy approximate method
#define DEFINEFUNC_MATH_FLOAT_POW(BITS, HALF, MAGIC) \
t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
    union { t_f##BITS f; t_s##HALF i[2]; } u = { x }; \
    u.i[1] = (t_s##HALF)(y * (t_f##BITS)(u.i[1] - MAGIC) + MAGIC); \
    u.i[0] = 0; \
    return u.f; \
} \

DEFINEFUNC_MATH_FLOAT_POW(32, 16, 1064866816)
DEFINEFUNC_MATH_FLOAT_POW(64, 32, 1072632447)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_MATH_FLOAT_POW(80, 40, ?)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_MATH_FLOAT_POW(128, 64, ?)
#endif

#endif

#if 0
	u_float_cast result;
	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.value_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
#endif

// lame exp*ln method
#if 0 
	return (F##BITS##_Exp(y * F##BITS##_Ln(x)));
#endif



#else

#error "not implemented"

#endif
