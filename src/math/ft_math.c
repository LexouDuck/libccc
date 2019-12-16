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

#include "../../libft_math.h"
#include "../../libft_memory.h"



inline t_float	ft_floor(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - ft_fmod(x, 1.) - 1.);
	return (x - ft_fmod(x, 1.));
}

inline t_float	ft_ceil(t_float x)
{
	if (x == 0.)
		return (0.);
	if (x < 0.)
		return (x - ft_fmod(x, 1.));
	return (1 + x - ft_fmod(x, 1.));
}



inline t_float	ft_fmod(t_float x, t_float y)
{
	t_float		a;
	t_s64		floor_a;

	a = x / y;
	floor_a = a;
	return ((a - floor_a) * y);
}



inline t_float		ft_pow(t_float x, t_float y)
{
	if (y == 0.)
		return (1.);
	if (x <= 0.)
		return (0.);
	return (ft_exp(y * ft_ln(x)));
}



static t_s32	ft_float_get_exponent(t_float x)
{
	t_s64	result = 0;

	FT_MemoryCopy((t_u8*)&result, &x, sizeof(t_float));
	return (((result & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);
}

/*
**	Some SQRT(2)^n lookup tables for quick newton method initial guess
*/
static t_float	ft_sqrt_2_pow_n(t_s32 n)
{
	static const t_float powers_pos[12] =
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
		INFINITY,
	};
	static const t_float powers_neg[12] =
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
	if (n & 0x001) { result *= powers[0x0]; }
	if (n & 0x002) { result *= powers[0x1]; }
	if (n & 0x004) { result *= powers[0x2]; }
	if (n & 0x008) { result *= powers[0x3]; }
	if (n & 0x010) { result *= powers[0x4]; }
	if (n & 0x020) { result *= powers[0x5]; }
	if (n & 0x040) { result *= powers[0x6]; }
	if (n & 0x080) { result *= powers[0x7]; }
#ifdef _FLOAT_64_
	if (n & 0x100) { result *= powers[0x8]; }
	if (n & 0x200) { result *= powers[0x9]; }
	if (n & 0x400) { result *= powers[0xA]; }
#endif
	return (result);
}



inline t_float	ft_sqrt(t_float x)
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
	i = ft_float_get_exponent(x);
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



inline t_float	ft_cbrt(t_float x)
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
	i = ft_float_get_exponent(x);
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



inline t_float	ft_nrt(t_float x, t_u8 n)
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
	i = ft_float_get_exponent(x);
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
