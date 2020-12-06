
#include "libft_memory.h"
#include "libft_string.h"
#include "libft_math.h"
#include "libft_convert.h"



static char		*ft_f32_to_str_decim(t_f32 number, t_u8 precision)
{
	char	*result;
	char	digits[32];
	t_u8	i;
	t_u64	n;

	i = precision + 1;
	while (--i)
		number *= 10;
	n = (t_u64)(number < 0 ? -number : number);
	while (n > 0 || i < precision)
	{
		digits[i++] = (n % 10) + '0';
		n /= 10;
		if (i == precision && (digits[i++] = '.'))
			if (n == 0 && number != 0)
				digits[i++] = '0';
	}
	if (!(result = (char *)ft_memalloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

static t_s16	ft_f32_to_str_getexponent(t_f32 *number)
{
	t_f32	nearest;
	t_s16	power;
	t_s16	exponent;

	exponent = 0;
	power = 256 * 2;
	if (*number >= FLOAT_THRESHOLD_HUGE ||
		*number <= -FLOAT_THRESHOLD_HUGE)
		while ((power /= 2) > 0)
			if (*number >= (nearest = ft_pow(10, power)))
			{
				*number /= nearest;
				exponent += power;
			}
	if ((*number > 0 && *number <= FLOAT_THRESHOLD_TINY) ||
		(*number < 0 && *number >= -FLOAT_THRESHOLD_TINY))
		while ((power /= 2) > 0)
			if (*number < ft_pow(10, 1 - power))
			{
				*number *= ft_pow(10, power);
				exponent -= power;
			}
	return (exponent);
}

static char		*ft_f32_to_str_expon(t_f32 number, t_u8 precision,
	char **result_exp, char **result_mant)
{
	char	*result;
	t_size	i;
	t_bool	sign;

	sign = (number < 0);
	number = (sign ? -number : number);
	if (!(*result_exp = ft_s16_to_str(ft_f32_to_str_getexponent(&number))) ||
		!(*result_mant = ft_f32_to_str_decim(number, precision)) ||
		!(result = (char *)ft_memalloc(ft_strlen(*result_mant) + ft_strlen(*result_exp) + 2 + (t_u8)sign)))
	{
		return (NULL);
	}
	i = 0;
	if (sign)
		result[i++] = '-';
	ft_strcpy(result + i, *result_mant);
	i += ft_strlen(*result_mant);
	result[i++] = 'e';
	ft_strcpy(result + i, *result_exp);
	i += ft_strlen(*result_exp);
	result[i] = '\0';
	return (result);
}

char			*ft_f32_to_str_p(t_f32 number, t_u8 precision)
{
	char	*result;
	char	*result_exp;
	char	*result_mant;

	result = NULL;
	result_exp = NULL;
	result_mant = NULL;
	if (ft_float_to_str_checkspecial(number, &result))
		return (result);
	if (number >= FLOAT_THRESHOLD_HUGE || number <= -FLOAT_THRESHOLD_HUGE ||
		(number > 0 && number <= FLOAT_THRESHOLD_TINY) ||
		(number < 0 && number >= -FLOAT_THRESHOLD_TINY))
		result = ft_f32_to_str_expon(number, precision,
			&result_exp, &result_mant);
	else
		result = ft_f32_to_str_decim(number, precision);
	if (result_exp)
		ft_memfree(result_exp);
	if (result_mant)
		ft_memfree(result_mant);
	return (result);
}
