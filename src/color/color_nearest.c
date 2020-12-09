
#include "libft_color.h"



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
			result = &colors[n];
		}
	}
	return (result);
}



t_argb32*		ft_color_argb32_nearest(
	t_argb32 target,
	t_argb32* colors,
	t_size n)
{
	t_s16 r;
	t_s16 g;
	t_s16 b;
	t_s16 min_diff;
	t_argb32* result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = S16_MAX;
	result = NULL;
	while (n--)
	{
		r = ft_color_argb32_get_r(target) - ft_color_argb32_get_r(colors[n]);
		g = ft_color_argb32_get_g(target) - ft_color_argb32_get_g(colors[n]);
		b = ft_color_argb32_get_b(target) - ft_color_argb32_get_b(colors[n]);
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((r + g + b) < min_diff)
		{
			min_diff = (r + g + b);
			result = &colors[n];
		}
	}
	return (result);
}



s_argb*		ft_color_argb_nearest(
	s_argb target,
	s_argb* colors,
	t_size n)
{
	t_s16 r;
	t_s16 g;
	t_s16 b;
	t_s16 min_diff;
	s_argb* result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = S16_MAX;
	result = NULL;
	while (n--)
	{
		r = target.r - colors[n].r;
		g = target.g - colors[n].g;
		b = target.b - colors[n].b;
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((r + g + b) < min_diff)
		{
			min_diff = (r + g + b);
			result = &colors[n];
		}
	}
	return (result);
}
