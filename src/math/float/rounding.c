
#include "libccc/math/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



// TODO implement c_round



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_trunc(t_float x)
{
	if (x == 0.)
		return (0.);
	return (x - c_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(trunc, trunc)
#endif



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_floor(t_float x)
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



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_ceil(t_float x)
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



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_round(t_float x)
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
