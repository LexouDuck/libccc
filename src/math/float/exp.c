
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Exp, exp)
#else
#define DEFINEFUNC_FLOAT_EXP(BITS) \
t_f##BITS		F##BITS##_Exp(t_f##BITS x)				\
{														\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)	\
	if (x < -10.)										\
		return (0.);									\
	t_f##BITS result = (x + 8.);						\
	result *= (x + 56.);								\
	result *= (x + 336.);								\
	result *= (x + 1680.);								\
	result *= (x + 6720.);								\
	result *= (x + 20160.);								\
	result *= (x + 40320.);								\
	result *= (x + 40320.);								\
	result *= 2.4801587301e-5;							\
	return (result);									\
}

#if 0 // crazy fast approximate method TODO: fix infinite loop ??
	u_float_cast result = { x };

	result.value_int = (1512775 * result.value_int + 1072632447);
	result.value_int <<= (BITS / 2);
	return (result.value_float);
#endif

#if 0 // precise but slow iterative method
	t_f##BITS		result;
	t_f##BITS		result_prev;
	t_f##BITS		acc_x;
	t_f##BITS		acc_i;
	t_u32		i;

	if (x < 100.)
		return (0.);
	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	result_prev = 0.;
	while (ABS(result - result_prev) > FLOAT_APPROX)
	{
		result_prev = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
#endif

DEFINEFUNC_FLOAT_EXP(32)
DEFINEFUNC_FLOAT_EXP(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP(128)
#endif

#endif
