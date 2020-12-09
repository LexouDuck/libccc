
#include "libft_color.h"



t_argb16	Color_ARGB_To_ARGB16(s_argb color)
{
	static const t_float	factor = (float)COLOR_ARGB32_CHANNEL / (float)COLOR_ARGB16_CHANNEL;
	t_u32					result;

	result = (color & COLOR_ARGB16_A) ? COLOR_ARGB32_A : 0;
	result |= (t_u32)(ft_color_argb16_get_r(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_g(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_b(color) * factor);
	return (result);
}



t_argb32	Color_ARGB_To_ARGB32(s_argb color)
{
	static const t_float	factor = (float)COLOR_ARGB32_CHANNEL / (float)COLOR_ARGB16_CHANNEL;
	t_u32					result;

	result = (color & COLOR_ARGB16_A) ? COLOR_ARGB32_A : 0;
	result |= (t_u32)(ft_color_argb16_get_r(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_g(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_b(color) * factor);
	return (result);
}
