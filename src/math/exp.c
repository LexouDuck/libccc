
#include "libccc/math/math.h"



#if LIBCONFIG_USE_FAST_APPROX_MATH
t_float		c_exp(t_float x)
{
	if (x < -10.)
		return (0.);
	t_float result = x + 8.;
	result *= x + 56;
	result *= x + 336;
	result *= x + 1680;
	result *= x + 6720;
	result *= x + 20160;
	result *= x + 40320;
	result *= x + 40320;
	result *= 2.4801587301e-5;
	return (result);
/*	inf loop ??
	u_float_cast result = { x };

	result.value_int = (1512775 * result.value_int + 1072632447);
#if LIBCONFIG_BITS_FLOAT == 32
	result.value_int <<= 16;
#endif
#if LIBCONFIG_BITS_FLOAT == 64
	result.value_int <<= 32;
#endif
#if LIBCONFIG_BITS_FLOAT == 80
	result.value_int <<= 40;
#endif
#if LIBCONFIG_BITS_FLOAT == 128
	result.value_int <<= 64;
#endif
	return (result.value_float);
*/
/*	precise but slow
	t_float		result;
	t_float		result_prev;
	t_float		acc_x;
	t_float		acc_i;
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
*/
}
#else
MATH_DECL_REALFUNCTION(exp, exp)
#endif
