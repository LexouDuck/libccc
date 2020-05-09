/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_f64.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h> // TODO make powf implementation and remove this

#include "libft_convert.h"
#include "libft_memory.h"
#include "libft_string.h"



/*
** Has some negligible error (beyond the seventh decimal digit; imprecision
** linked to input)
*/

static t_f64	ft_str_to_f64_expon(char const *s_mant, char const *s_exp)
{
	t_f64		result;
	t_s16		exponent;
	size_t		frac_digits;
	char		*tmp;

	if (!(tmp = ft_strremove(s_mant, ".")))
		return (NAN);
	if (ft_strlen(tmp) > 18)
		tmp[18] = '\0';
	result = (t_f64)ft_str_to_s64(tmp);
	free(tmp);
	if (!(exponent = 0) && s_exp)
	{
		exponent = ft_str_to_s16(s_exp);
		if (exponent > F64_EXPONENT_BIAS)
			return (s_mant[0] == '-' ? -INFINITY : INFINITY);
		else if (exponent < 1 - F64_EXPONENT_BIAS)
			return (0.);
	}
	tmp = ft_strchr(s_mant, '.');
	if (tmp && (frac_digits = ft_strlen(++tmp)) > 0)
		exponent -= frac_digits;
	if (ft_strlen(s_mant) > 18)
		exponent += ft_strlen(s_mant) - 18;
	return (result * powf(10., exponent));
}

static t_f64	ft_str_to_f64_hexfp(
	char const *s_mant,
	char const *s_exp,
	int sign)
{
	t_f64		result;
	t_s16		exponent;
	t_u64		mant;
	char		*tmp;

	result = sign ? -1. : 1.;
	tmp = ft_strremove(s_mant, ".");
	if (ft_strequ(tmp, "0") || ft_strequ(tmp, "00"))
	{
		free(tmp);
		return (0. * result);
	}
	mant = ft_hex_to_u64(tmp);
	result *= mant * F64_INIT_VALUE * powf(2., (ft_strlen(tmp) - 1) * 4);
	if ((exponent = ft_str_to_s16(s_exp)) > F64_EXPONENT_BIAS)
		return ((sign ? -1. : 1.) / 0.);
	else if (exponent < 1 - F64_EXPONENT_BIAS)
		return (0.);
	ft_memcpy(&mant, &result, sizeof(result));
	mant &= F64_MANTISSA_SIGNED;
	mant |= F64_EXPONENT &
		((t_u64)(exponent + F64_EXPONENT_BIAS) << F64_MANTISSA_BITS);
	ft_memcpy(&result, &mant, sizeof(result));
	free(tmp);
	return (result);
}

t_f64			ft_str_to_f64(char const *str)
{
	t_f64	result;
	char	*tmp;
	char	*hexfp;
	char	*exponent;
	int		mode;

	result = NAN;
	if (ft_str_to_float_checkinvalid(str, &tmp))
		return (result);
	if (tmp[0] == 'I' || (tmp[1] == 'I' && (tmp[0] == '-' || tmp[0] == '+')))
	{
		free(tmp);
		return (tmp[0] == '-' ? -INFINITY : INFINITY);
	}
	hexfp = ft_strchr(tmp, 'X');
	if ((exponent = ft_strchr(tmp, (hexfp ? 'P' : 'E'))))
		*(exponent++) = '\0';
	if (!(mode = (hexfp != NULL) + (exponent != NULL)))
		result = ft_str_to_f64_expon(tmp, NULL);
	else if (mode == 1)
		result = ft_str_to_f64_expon(tmp, exponent);
	else if (mode == 2)
		result = ft_str_to_f64_hexfp(hexfp + 1, exponent, tmp[0] == '-');
	free(tmp);
	return (result);
}
