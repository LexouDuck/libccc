
/*
**	Functions used from <stdio.h>:
**	-	char*	asprintf(char* dest, char const* format, ...);
*/
#define _GNU_SOURCE
#include <stdio.h>

#include "libft_string.h"
#include "libft_math.h"
#include "libft_convert.h"



char		*ft_f32_to_str(t_f32 number)
{
	char*	result = NULL;

	asprintf(&result, "%g", number);
	return (result);
}

char		*ft_f32_to_hexstr(t_f32 number)
{
	char*	result = NULL;

	asprintf(&result, "%#a", number);
	return (result);
}

char		*ft_f64_to_str(t_f64 number)
{
	char*	result = NULL;

	asprintf(&result, "%lg", number);
	return (result);
}

char		*ft_f64_to_hexstr(t_f64 number)
{
	char*	result = NULL;

	asprintf(&result, "%#la", number);
	return (result);
}



t_bool		ft_float_to_str_checkspecial(t_f32 number, char **result)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (result == NULL)
		return (FALSE);
#endif
	if (IS_NAN(number))
	{
		*result = ft_strdup("NaN");
		return (TRUE);
	}
	else if (IS_INFINITY(number))
	{
		*result = (number < 0 ?
			ft_strdup("-INFINITY") :
			ft_strdup("+INFINITY"));
		return (TRUE);
	}
	return (FALSE);
}
