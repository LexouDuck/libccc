/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random/ft_random.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include "libft_random.h"



static t_u32		U32Random = DEFAULT_SEED;



inline static t_u32	ft_random_32bit_shuffle(t_u32 n)
{
	n = (n << 12) ^ (n >> 20);
	return (36969 * (n & 0xFFFF) + (n >> 16));
}

inline void			ft_random_set_seed(t_u32 seed)
{
	U32Random = seed;
}

inline void			ft_random_renew_seed(void)
{
	U32Random = ft_random_32bit_shuffle(time(NULL));
}



inline t_u32		ft_random(void)
{
	U32Random = (CEIL_SQRT_MOD * ft_random_32bit_shuffle(U32Random) + OFFSET) & MODULUS;
	return (U32Random);
}

inline t_u32		ft_random_0_to_pow2n(t_u32 n)
{
	return (ft_random() & ((0x1 << n) - 1));
}

inline t_u32		ft_random_0_to_n(t_u32 n)
{
	return (ft_random() % n);
}

inline t_int		ft_random_int_a_to_b(t_int a, t_int b)
{
	if (a < b)
		return (ft_random_0_to_n(b - a) + a);
	else
		return (ft_random_0_to_n(a - b) + b);
}

inline t_float		ft_random_float_0_to_1(void)
{
	return (((t_float)ft_random()) / MODULUS);
}

inline t_float		ft_random_float_a_to_b(t_float a, t_float b)
{
	if (a < b)
		return (ft_random_float_0_to_1() * (b - a) + a);
	else
		return (ft_random_float_0_to_1() * (a - b) + b);
}
