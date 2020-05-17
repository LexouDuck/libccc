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
	t_s64	result = 0;

	ft_memcpy((t_u8*)&result, &x, sizeof(t_float));
	return (((result & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);
}
#else
MATH_DECL_FUNCTION(t_s32, getexp, logb)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_fabs(t_float x)
{
	t_u64	tmp;

	ft_memcpy(&tmp, &x, sizeof(t_float));
	if (tmp & FLOAT_SIGNED)
		return ((t_float)(tmp & ~FLOAT_SIGNED));
	return (x);
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
	t_float result = 1;
	while (abs(n) > FLOAT_BIAS)
	{
		if (abs(n & 1) > FLOAT_BIAS)
		{
			result *= x;
			n -= 1;
		}
		x *= x;
		n /= 2;
	}
	return (result);
/*
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
*/
}

#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_pow(t_float x, t_float y)
{
	if (y == 0.)
		return (1.);
	if (x <= 0.)
		return (0.);
//	return (ft_exp(y * ft_ln(x)));
	union {
		t_float d;
		t_s32 a[2];
	} u = { x };
	u.a[1] = (t_s32)(y * (u.a[1] - 1072632447) + 1072632447);
	u.a[0] = 0;
	return (u.d);
}
#else
MATH_DECL_REALOPERATOR(pow, pow)
#endif



/*
**	Some SQRT(2)^n lookup tables for quick newton method initial guess
*/
#if (defined _FLOAT_80_ || defined _FLOAT_128_)
	#define POWERS_LENGTH	16
#else
	#define POWERS_LENGTH	12
#endif
static t_float	ft_sqrt_2_pow_n(t_s32 n)
{
	static const t_float powers_pos[POWERS_LENGTH] =
	{
		SQRT_2,
		(t_float)0x1.0p+1,
		(t_float)0x1.0p+2,
		(t_float)0x1.0p+4,
		(t_float)0x1.0p+8,
		(t_float)0x1.0p+16,
		(t_float)0x1.0p+32,
		(t_float)0x1.0p+64,
		(t_float)0x1.0p+128,
		(t_float)0x1.0p+256,
		(t_float)0x1.0p+512,
#if (defined _FLOAT_80_ || defined _FLOAT_128_)
		(t_float)0x1.0p+1024,
		(t_float)0x1.0p+2048,
		(t_float)0x1.0p+4096,
		(t_float)0x1.0p+8192,
#endif
		INFINITY,
	};
	static const t_float powers_neg[POWERS_LENGTH] =
	{
		INV_SQRT_2,
		(t_float)0x1.0p-1,
		(t_float)0x1.0p-2,
		(t_float)0x1.0p-4,
		(t_float)0x1.0p-8,
		(t_float)0x1.0p-16,
		(t_float)0x1.0p-32,
		(t_float)0x1.0p-64,
		(t_float)0x1.0p-128,
		(t_float)0x1.0p-256,
		(t_float)0x1.0p-512,
#if (defined _FLOAT_80_ || defined _FLOAT_128_)
		(t_float)0x1.0p-1024,
		(t_float)0x1.0p-2048,
		(t_float)0x1.0p-4096,
		(t_float)0x1.0p+8192,
#endif
		0.,
	};
	if (n > 0 && (n >> 11))
		return (INFINITY);
	const t_float* powers = powers_pos;
	if (n == 0)
		return (1.);
	else if (n < 0)
	{
		n = -n;
		powers = powers_neg;
	}
	t_float result = 1.;
	if (n & 0x0001) { result *= powers[0x0]; }
	if (n & 0x0002) { result *= powers[0x1]; }
	if (n & 0x0004) { result *= powers[0x2]; }
	if (n & 0x0008) { result *= powers[0x3]; }
	if (n & 0x0010) { result *= powers[0x4]; }
	if (n & 0x0020) { result *= powers[0x5]; }
	if (n & 0x0040) { result *= powers[0x6]; }
	if (n & 0x0080) { result *= powers[0x7]; }
#if (defined _FLOAT_64_ || defined _FLOAT_80_ || _FLOAT_128_)
	if (n & 0x0100) { result *= powers[0x8]; }
	if (n & 0x0200) { result *= powers[0x9]; }
	if (n & 0x0400) { result *= powers[0xA]; }
#endif
#if (defined _FLOAT_80_ || defined _FLOAT_128_)
	if (n & 0x0800) { result *= powers[0xB]; }
	if (n & 0x1000) { result *= powers[0xC]; }
	if (n & 0x2000) { result *= powers[0xD]; }
	if (n & 0x4000) { result *= powers[0xE]; }
#endif
	return (result);
}



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float	ft_sqrt(t_float x)
{
//	Newton derivative approximation by iteration
	static const t_s32	i_max = 6;
	t_s32	i;
	t_float	result;
	t_float	previous;

	if (IS_NAN(x) || x < 0.)
		return (NAN);
	if (x == 0.)
		return (0.);
	if (x == 1.)
		return (1.);
	i = ft_getexp(x);
	result = (i < 0 ? 0.75 : 1.25) * ft_sqrt_2_pow_n(i);
	previous = INFINITY;
	i = 0;
	while (ABS(result - previous) > FLOAT_BIAS)
	{
		previous = result;
		result -= (result * result - x) / (2 * result);
		if (++i == i_max)
			break;
	}
	return (result);
}
#else
MATH_DECL_REALFUNCTION(sqrt, sqrt)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float	ft_cbrt(t_float x)
{
//	Newton derivative approximation by iteration
	static const t_s32	i_max = 6;
	t_s32	i;
	t_float square;
	t_float	result;
	t_float	previous;

	if (IS_NAN(x))
		return (NAN);
	if (x == 0)
		return (0);
	if (ABS(x) == 1.)
		return (SIGN(x));
	i = ft_getexp(x);
	result = SIGN(x) * (i < 0 ? 0.75 : 1.25) * ft_sqrt_2_pow_n(i * 2 / 3);
	previous = INFINITY;
	i = 0;
	while (ABS(result - previous) > FLOAT_BIAS)
	{
		previous = result;
		square = result * result;
		result -= (result * square - x) / (3 * square);
		if (++i == i_max)
			break;
	}
	return (result);
}
#else
MATH_DECL_REALFUNCTION(cbrt, cbrt)
#endif



t_float	ft_nrt(t_float x, t_u8 n)
{
//	Newton derivative approximation by iteration
	static const t_s32	i_max = 6;
	t_s32	i;
	t_float	result;
	t_float	previous;
	t_float	power;

	if (IS_NAN(x) || n == 0)
		return (NAN);
	if (n == 1)
		return (x);
	if (x == 0)
		return (0);
	if (ABS(x) == 1.)
		return (SIGN(x));
	if (n % 2 == 0 && x < 0)
		return (NAN);
	i = ft_getexp(x);
	result = SIGN(x) * (i < 0 ? 1 : 1.25) * ft_sqrt_2_pow_n(i * 2 / n);
	previous = 0.;
	i = 0;
	n -= 1;
	while (ABS(result - previous) > FLOAT_BIAS)
	{
		previous = result;
		power = result;
		for (t_u32 j = 1; j < n; ++j)
		{
			power *= result;
		}
		result -= (power * result - x) / ((n + 1) * power);
		if (++i == i_max)
			break;
	}
	return (result);
}
