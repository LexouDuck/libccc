/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/ft_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_memory.h"



#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_s32	ft_getexp(t_float x)
{
	u_float_cast	result;

	result.value_float = x;
	return (((result.value_int & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);
}
#else
MATH_DECL_FUNCTION(t_s32, getexp, logb)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_fabs(t_float x)
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



#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_fmod(t_float x, t_float y)
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



// TODO round

#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_trunc(t_float x)
{
	if (x == 0.)
		return (0.);
	return (x - ft_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(trunc, trunc)
#endif

#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_floor(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - ft_fmod(x, 1.) - 1.);
	return (x - ft_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(floor, floor)
#endif

#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_ceil(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - ft_fmod(x, 1.));
	return (1 + x - ft_fmod(x, 1.));
}
#else
MATH_DECL_REALFUNCTION(ceil, ceil)
#endif



t_float			ft_pow_n(t_float x, t_int n)
{
	t_float	tmp;

	if (n == 0)
		return (1.);
	tmp = ft_pow_n(x, n / 2);
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
	while (ft_fabs(n) > FLOAT_BIAS)
	{
		if (ft_fabs(n & 1) > FLOAT_BIAS)
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

#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_pow(t_float x, t_float y)
{
	return (ft_exp(y * ft_ln(x)));
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
