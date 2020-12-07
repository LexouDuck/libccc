
#include "libft_color.h"



inline t_u8		ft_color_argb16_get_a(t_argb16 color)
{
	return ((t_u8)((color >> 15) ? 1 : 0));
}

inline t_u8		ft_color_argb16_get_r(t_argb16 color)
{
	return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> 10)));
}

inline t_u8		ft_color_argb16_get_g(t_argb16 color)
{
	return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> 5)));
}

inline t_u8		ft_color_argb16_get_b(t_argb16 color)
{
	return ((t_u8)(COLOR_ARGB16_CHANNEL & color));
}

t_argb16*		ft_color_argb16_nearest(
	t_argb16 target,
	t_argb16* colors,
	t_size n)
{
	t_s16 r;
	t_s16 g;
	t_s16 b;
	t_s16 min_diff;
	t_argb16* result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = S16_MAX;
	result = NULL;
	while (n--)
	{
		r = ft_color_argb16_get_r(target) - ft_color_argb16_get_r(colors[n]);
		g = ft_color_argb16_get_g(target) - ft_color_argb16_get_g(colors[n]);
		b = ft_color_argb16_get_b(target) - ft_color_argb16_get_b(colors[n]);
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((r + g + b) < min_diff)
		{
			min_diff = (r + g + b);
			result = (colors + n);
		}
	}
	return (result);
}
