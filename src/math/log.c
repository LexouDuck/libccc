
#include "libccc/math/math.h"
#include "libccc/memory.h"



#if LIBCONFIG_USE_FAST_APPROX_MATH
/*
** The following pair of functions return the natural logarithm of x.
** ln(x) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** FLOAT_EXPONENT_ZERO is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_float	c_ln_taylor_series(t_float x)
{
	t_float	result;
	t_float	result_previous;
	t_float	power;
	t_float	i;

	i = 2.;
	power = x;
	result = x;
	result_previous = NAN;
	while (ABS(power) > FLOAT_APPROX)
	{
		power *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (power / i);
		if (result == result_previous)
			break ;
		result_previous = result;
		++i;
	}
	return (result);
}

t_float			c_ln(t_float x)
{
	static const t_float LN_3_2			= (t_float)0x1.9F323ECBF984Cp-2;
	static const t_float DIV_2_3		= (t_float)0x1.5555555555556p-1;
	t_float	result;
	t_u64	tmp = 0;	// a raw memory copy
	t_u64	norm = 0;	// the float x in x*2^n in raw memory
	t_s32	exp_b2;

	if (x < 0.)
		return (NAN);
	if (x == 0.)
		return (-INFINITY);
	if (x == 1.)
		return (0.);
	if (x == INFINITY)
		return (INFINITY);
	if (x < 1. || 2. <= x)
	{
		c_memcpy(&tmp, &x, sizeof(t_float));
		norm = (tmp & FLOAT_MANTISSA_SIGNED) | FLOAT_EXPONENT_ZERO;
		c_memcpy(&x, &norm, sizeof(t_float));
		result = c_ln(x);
		exp_b2 = ((tmp << 1) >> (FLOAT_MANTISSA_BITS + 1)) - FLOAT_EXPONENT_BIAS;
		return (LN_2 * exp_b2 + result);
	}
	if (1.9 <= x && x < 2.)
		return (c_ln(x * DIV_2_3) + LN_3_2);
	result = c_ln_taylor_series(x - 1.);
	return (result);
}
#else
MATH_DECL_REALFUNCTION(ln, log)
#endif



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline t_float	c_lg(t_float x)
{
	return (c_ln(x) / LN_2);
}
#else
MATH_DECL_REALFUNCTION(lg, log2)
#endif



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline t_float	c_log(t_float x)
{
	return (c_ln(x) / LN_10);
}
#else
MATH_DECL_REALFUNCTION(log, log10)
#endif



inline t_float	c_log_n(t_float x, t_float n)
{
	if (n == 2)
		return (Float_Log2(x));
	else if (n == 10)
		return (Float_Log10(x));
	else
		return (Float_Ln(x) / Float_Ln(n));
}
