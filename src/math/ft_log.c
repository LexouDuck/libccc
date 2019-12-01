/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/ft_log.c                                      :+:      :+:    :+:   */
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
** The following pair of functions return the natural logarithm of f.
** ln(f) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** F32_EXPONENT_ZERO = 0x3F800... is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_f32	ft_ln32_taylor_series(t_f32 x)
{
	t_f32	result;
	t_f32	prev_res;
	t_f32	powx;
	t_f32	i;

	i = 2.f;
	powx = x;
	result = x;
	while (powx != 0.f)
	{
		powx *= x;
		result += (((((int)i % 2)) * 2) - 1.f) * (powx / i);
		if (result == prev_res)
			break ;
		prev_res = result;
		++i;
	}
	return (result);
}

t_f32			ft_ln32(t_f32 x)
{
	t_f32	result;
	t_u32	tmp;
	t_u32	norm;
	t_s32	exp_b2;

	if (x < 0.f)
		return (NAN);
	if (x == 0.f)
		return (-INFINITY);
	if (x == 1.f)
		return (0.f);
	if (x == INFINITY)
		return (INFINITY);
	if (x < 1.f || 2.f <= x)
	{
		ft_memcpy(&tmp, &x, sizeof(t_u32));
		norm = (tmp & F32_MANTISSA_SIGNED) | F32_EXPONENT_ZERO;
		ft_memcpy(&x, &norm, sizeof(t_u32));
		result = ft_ln32(x);
		exp_b2 = ((tmp << 1) >> (F32_MANTISSA_BITS + 1)) - F32_EXPONENT_BIAS;
		return (LN2 * exp_b2 + result);
	}
	if (1.9f <= x && x < 2.f)
		return (ft_ln32(x * DIV_2_BY_3) + LN_3DIV2);
	result = ft_ln32_taylor_series(x - 1.f);
	return (result);
}



/*
** The following pair of functions return the natural logarithm of lf.
** ln(lf) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** F64_EXPONENT_ZERO = 0x3FF00... is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_f64	ft_ln64_taylor_series(t_f64 x)
{
	t_f64	result;
	t_f64	prev_res;
	t_f64	powx;
	t_f64	i;

	i = 2.;
	powx = x;
	result = x;
	while (powx != 0.)
	{
		powx *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (powx / i);
		if (result == prev_res)
			break ;
		prev_res = result;
		++i;
	}
	return (result);
}

t_f64			ft_ln64(t_f64 lf)
{
	t_f64	result;
	t_u64	tmp; //a raw memory copy
	t_u64	norm; //the float x in x*2^n in raw memory
	t_s32	exp_b2;

	if (lf < 0.)
		return (NAN);
	if (lf == 0.)
		return (-INFINITY);
	if (lf == 1.)
		return (0.);
	if (lf == INFINITY)
		return (INFINITY);
	if (lf < 1. || 2. <= lf)
	{
		ft_memcpy(&tmp, &lf, sizeof(t_u64));
		norm = (tmp & F64_MANTISSA_SIGNED) | F64_EXPONENT_ZERO;
		ft_memcpy(&lf, &norm, sizeof(t_u64));
		result = ft_ln64(lf);
		exp_b2 = ((tmp << 1) >> (F64_MANTISSA_BITS + 1)) - F64_EXPONENT_BIAS;
		return (LN2 * exp_b2 + result);
	}
	if (1.9 <= lf && lf < 2.)
		return (ft_ln64(lf * DIV_2_BY_3) + LN_3DIV2);
	result = ft_ln64_taylor_series(lf - 1.);
	return (result);
}



#ifdef _FLOAT_32_
	inline t_float			ft_ln(t_float x)
	{
		return (ft_ln32(x));
	}
#endif
#ifdef _FLOAT_64_
	inline t_float			ft_ln(t_float x)
	{
		return (ft_ln64(x));
	}
#endif



inline t_float				ft_lg(t_float x)
{
	return ft_ln(x) / ((t_float)(LN2));
}



inline t_float				ft_log(t_float x)
{
	return ft_ln(x) / ((t_float)(LN10));
}



inline t_float				ft_logn(t_float x, t_float n)
{
	if (n == 2)
		return ft_lg(x);
	else if (n == 10)
		return ft_log(x);
	else
		return ft_ln(x) / ft_ln(n);
}
