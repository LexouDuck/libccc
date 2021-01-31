
#include "libccc/math/math.h"
#include "libccc/memory.h"



#if LIBCONFIG_FAST_APPROX_MATH
inline t_s32	c_getexp(t_float x)
{
	u_float_cast	result;

	result.value_float = x;
	return (((result.value_int & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);
}
#else
MATH_DECL_FUNCTION(t_s32, getexp, logb)
#endif



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_fabs(t_float x)
{
	u_float_cast	result;

	result.value_float = x;
	if (result.value_int & FLOAT_SIGNED)
	{
		result.value_int &= ~FLOAT_SIGNED;
		return (result.value_float);
	}
	return (result.value_float);
}
#else
MATH_DECL_REALFUNCTION(fabs, fabs)
#endif



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_fmod(t_float x, t_float y)
{
	t_float		a;
	t_s64		floor_a;

	a = x / y;
	floor_a = (t_s64)a;
	return ((a - (t_float)floor_a) * y);
}
#else
MATH_DECL_REALOPERATOR(fmod, fmod)
#endif



// TODO implement c_round



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_trunc(t_float x)
{
	if (x == 0.)
		return (0.);
	return (x - c_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(trunc, trunc)
#endif



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_floor(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - c_fmod(x, 1.) - 1.);
	return (x - c_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(floor, floor)
#endif



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_ceil(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - c_fmod(x, 1.));
	return (1 + x - c_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(ceil, ceil)
#endif



#if LIBCONFIG_FAST_APPROX_MATH
inline t_float	c_round(t_float x)
{
	t_float fraction;

	fraction = c_fmod(x, 1.);
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (fraction < 0.5 ?
			(x + fraction) :
			(x - (1 - fraction));
	else
		return (fraction < 0.5 ?
			(x - fraction) :
			(x + (1 - fraction));
}
#else
MATH_DECL_REALFUNCTION(round, round)
#endif
