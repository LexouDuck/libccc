
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(trunc, trunc)
#else
inline
t_float	c_trunc(t_float x)
{
	if (x == 0.)
		return (0.);
	return (x - c_fmod(x, 1.));
}
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(floor, floor)
#else
inline
t_float	c_floor(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - c_fmod(x, 1.) - 1.);
	return (x - c_fmod(x, 1.));
}
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ceil, ceil)
#else
inline
t_float	c_ceil(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - c_fmod(x, 1.));
	return (1 + x - c_fmod(x, 1.));
}
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(round, round)
#else
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
			(x - (1 - fraction)));
	else
		return (fraction < 0.5 ?
			(x - fraction) :
			(x + (1 - fraction)));
}
#endif
