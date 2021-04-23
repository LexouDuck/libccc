
#include "libccc/math/math.h"
#include "libccc/memory.h"



#if LIBCONFIG_USE_FAST_APPROX_MATH
t_float			c_intpow(t_float x, t_sint n)
{
	t_float	tmp;

	if (n == 0)
		return (1.);
	tmp = c_pow_n(x, n / 2);
	if ((n % 2) == 0)
	{
		return (tmp * tmp);
	}
	else
	{
		if (n > 0)
			return (tmp * tmp * x);
		else
			return (tmp * tmp / x);
	}
/*
	t_float result = 1;
	while (c_fabs(n) > FLOAT_APPROX)
	{
		if (c_fabs(n & 1) > FLOAT_APPROX)
		{
			result *= x;
			n -= 1;
		}
		x *= x;
		n /= 2;
	}
	return (result);
*/
}
#else
//MATH_DECL_REALOPERATOR(intpow, pow)
// TODO fix this
#endif



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline t_float	c_pow(t_float x, t_float y)
{
	return (c_exp(y * c_ln(x)));
/*
	u_float_cast result;

	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.v_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
*/
}
#else
MATH_DECL_REALOPERATOR(pow, pow)
#endif
