
/*
**	Functions used from <stdlib.h>: (only when LIBFTCONFIG_FAST_APPROX_MATH is 0)
**	-	double	atof(char* str);
*/
#include <stdlib.h>

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_math.h"
#include "libft_convert.h"



#if LIBFTCONFIG_FAST_APPROX_MATH
/*
**	Has some approximation/error margin (beyond the seventh decimal digit;
**	the exact amount of imprecision depends on the input)
*/

static t_f32	ft_str_to_f32_expon(char const *s_mant, char const *s_exp)
{
	t_f32		result;
	t_s16		exponent;
	t_size		frac_digits;
	char		*tmp;

	if (!(tmp = ft_strremove(s_mant, ".")))
		return (NAN);
	if (ft_strlen(tmp) > 18)
		tmp[18] = '\0';
	result = (t_f32)ft_str_to_s64(tmp);
	ft_memfree(tmp);
	if (!(exponent = 0) && s_exp)
	{
		exponent = ft_str_to_s16(s_exp);
		if (exponent > F32_EXPONENT_BIAS)
			return (s_mant[0] == '-' ? -INFINITY : INFINITY);
		else if (exponent < 1 - F32_EXPONENT_BIAS)
			return (0.);
	}
	tmp = ft_strchr(s_mant, '.');
	if (tmp && (frac_digits = ft_strlen(++tmp)) > 0)
		exponent -= frac_digits;
	if (ft_strlen(s_mant) > 18)
		exponent += ft_strlen(s_mant) - 18;
	return (result * ft_pow(10., exponent));
}

static t_f32	ft_str_to_f32_hexfp(
	char const *s_mant,
	char const *s_exp,
	int sign)
{
	t_f32		result;
	t_s16		exponent;
	t_u32		mant;
	char		*tmp;

	result = sign ? -1. : 1.;
	tmp = ft_strremove(s_mant, ".");
	if (ft_strequ(tmp, "0") || ft_strequ(tmp, "00"))
	{
		ft_memfree(tmp);
		return (0. * result);
	}
	mant = ft_hex_to_u32(tmp);
	result *= mant * F32_INIT_VALUE * ft_pow(2., (ft_strlen(tmp) - 1) * 4);
	if ((exponent = ft_str_to_s16(s_exp)) > F32_EXPONENT_BIAS)
		return ((sign ? -1. : 1.) / 0.);
	else if (exponent < 1 - F32_EXPONENT_BIAS)
		return (0.);
	ft_memcpy(&mant, &result, sizeof(result));
	mant &= F32_MANTISSA_SIGNED;
	mant |= F32_EXPONENT &
		((t_u32)(exponent + F32_EXPONENT_BIAS) << F32_MANTISSA_BITS);
	ft_memcpy(&result, &mant, sizeof(result));
	ft_memfree(tmp);
	return (result);
}

t_f32			ft_str_to_f32(char const *str)
{
	t_f32	result;
	char	*tmp;
	char	*hexfp;
	char	*exponent;
	int		mode;

	result = NAN;
	if (ft_str_to_float_checkinvalid(str, &tmp))
		return (result);
	if (tmp[0] == 'I' || (tmp[1] == 'I' && (tmp[0] == '-' || tmp[0] == '+')))
	{
		mode = (tmp[0] == '-');
		ft_memfree(tmp);
		return (mode ? -INFINITY : INFINITY);
	}
	hexfp = ft_strchr(tmp, 'X');
	if ((exponent = ft_strchr(tmp, (hexfp ? 'P' : 'E'))))
		*(exponent++) = '\0';
	if (!(mode = (hexfp != NULL) + (exponent != NULL)))
		result = ft_str_to_f32_expon(tmp, NULL);
	else if (mode == 1)
		result = ft_str_to_f32_expon(tmp, exponent);
	else if (mode == 2)
		result = ft_str_to_f32_hexfp(hexfp + 1, exponent, tmp[0] == '-');
	ft_memfree(tmp);
	return (result);
}

#else

inline t_f32	ft_str_to_f32(char const *str)
{
	return (atof(str));
}

#endif
