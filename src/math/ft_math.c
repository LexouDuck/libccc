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

/*
**	Useful when you want to square an expression optimally
*/
inline t_float		ft_sqr(t_float x)
{
	return (x * x);
}



/*
**	Core idea is that sqrt(x) == x^(1/2) and that x is a float so
**	x^(1/2) == (m * 2^n)^(1/2) == m^(1/2) * 2^(n * 1/2)
**	with m between 1 and 2, and thus a taylor series can be used.
**	NB: Watch the parity of n.
**	Based on Heron's algorithm.
*/
t_f32		ft_sqrt32(t_f32 x)
{
	t_f32		result = 1.f;
	t_f32		limit;
	t_s8		exp_b2;
	t_u32		norm = 0;	
	t_u32		a;
//	t_u32		b;

	if (x < 0)
		return (NAN);

	if (x < 1.f || 2.f <= x)
	{
		ft_memcpy(&norm, &x, sizeof(t_u32));
		exp_b2 = (t_s16)((norm << 1) >> (F32_MANTISSA_BITS + 1)) - F32_EXPONENT_BIAS;
		norm = (norm & F32_MANTISSA) | F32_EXPONENT_ZERO;
		ft_memcpy(&x, &norm, sizeof(t_u32));
		if (exp_b2 > 0)
		{
			if (exp_b2 % 2)
				result *= SQRT2;
			exp_b2 = exp_b2 / 2;
		}
		else
		{
			if (exp_b2 % 2)
				result *= INV_SQRT2;
			exp_b2 = exp_b2 / 2;
		}
		a = exp_b2 + F32_EXPONENT_BIAS;
		a = a << F32_MANTISSA_BITS;
// the following pragma disables warnings for type punning derefs
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
		result *= *(t_f32*)(&a);
// Resets the warning settings back to normal
#pragma GCC diagnostic pop
	}
/*
	norm = (norm & F32_MANTISSA) | 0x00800000;//corresponds to the hidden bit
	b = norm;
	norm = 3.f;
	a = 3.f;
	norm = b / norm;
	norm = (norm + a) >> 1;
	a = norm;
	norm = b / norm;
	norm = (norm + a) >> 1;
	a = norm;
	norm = b / norm;
	norm = (norm + a) >> 1;

//	a = (F32_MANTISSA_BITS + F32_EXPONENT_BIAS) << F32_MANT_BIT_NB;
	result *= norm * *(t_f32*)(&a);
*/
	limit = 1.5f;
	limit = 0.5 * (limit + x / limit);
	limit = 0.5 * (limit + x / limit);
	limit = 0.5 * (limit + x / limit);

	return (result * limit);
}



t_float				ft_fmod(t_float x, t_float y)
{
	t_float		a;
	t_s64		floor_a;

	a = x / y;
	floor_a = a;
	return (a - floor_a) * y;
}
