/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_random.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_RANDOM_H
#define __LIBFT_RANDOM_H
/*! @file libft_random.h
**	This header defines some simple pseudo-random number generator functions.
**	@addtogroup libft_random
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*! @file libft_random.h
** Random number generator. Modulus is 2^31
**
** - OFFSET and MODULUS are mutually prime.
** - CEIL_SQRT_MOD % 4 should be = 1 because MODULUS is a multiple of 4
** - For all P prime divisors of MODULUS, a % p = 1
** - OFFSET should be small compared to the two other parameters
** - The bitwise & is applied, which explains the choice of modulus to be
**		2^31 - 1 in implementation (could also be called RAND_MAX)
**
** Basic RNG formula is:
**		new_nb = (CEIL_SQRT_MOD  * old_nb + OFFSET) % MODULUS
*/

#define DEFAULT_SEED	0x93E21FD5

#define MODULUS			0x7FFFFFFF		
#define CEIL_SQRT_MOD	46341
#define OFFSET			2835



/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Random_SetSeed		ft_random_set_seed
#define Random_RefreshSeed	ft_random_renew_seed

#define Random				ft_random
#define Random_Pow2n		ft_random_0_to_pow2n
#define Random_n			ft_random_0_to_n
#define RandomInt_a_b		ft_random_int_a_to_b
#define RandomFloat_0_1		ft_random_float_0_to_1
#define RandomFloat_a_b		ft_random_float_a_to_b



/*
** ************************************************************************** *|
**                               Random Functions                             *|
** ************************************************************************** *|
*/

t_u32		ft_random_32bit_shuffle(t_u32 n);

void		ft_random_set_seed(t_u32 seed);
void		ft_random_renew_seed(void);

t_u32		ft_random(void);
t_u32		ft_random_0_to_pow2n(t_u32 n);
t_u32		ft_random_0_to_n(t_u32 n);
t_int		ft_random_int_a_to_b(t_int a, t_int b);
t_float		ft_random_float_0_to_1(void);
t_float		ft_random_float_a_to_b(t_float a, t_float b);



/*! @} */
HEADER_END
#endif
