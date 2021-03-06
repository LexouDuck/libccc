
#include "libccc/math/math.h"
#include "libccc/color.h"



t_argb16 const*		Color_ARGB16_GetNearest(
	t_argb16 target,
	t_argb16 const* colors,
	t_size n)
{
	t_u16 diff;
	t_u16 min_diff;
	t_argb16 const* result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = U16_MAX;
	result = NULL;
	while (n--)
	{
		diff = Color_ARGB16_Difference(target, colors[n]);
		if (diff < min_diff)
		{
			min_diff = diff;
			result = &colors[n];
		}
	}
	return (result);
}



t_argb32 const*		Color_ARGB32_GetNearest(
	t_argb32 target,
	t_argb32 const* colors,
	t_size n)
{
	t_u32 diff;
	t_u32 min_diff;
	t_argb32 const* result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = U32_MAX;
	result = NULL;
	while (n--)
	{
		diff = Color_ARGB16_Difference(target, colors[n]);
		if (diff < min_diff)
		{
			min_diff = diff;
			result = &colors[n];
		}
	}
	return (result);
}



s_argb const*		Color_ARGB_GetNearest(
	s_argb target,
	s_argb const* colors,
	t_size n)
{
	t_s16 r;
	t_s16 g;
	t_s16 b;
	t_s16 min_diff;
	s_argb const* result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = 3.0;
	result = NULL;
	while (n--)
	{
		r = target.r - colors[n].r;
		g = target.g - colors[n].g;
		b = target.b - colors[n].b;
		r = ABS(r);
		g = ABS(g);
		b = ABS(b);
		if ((r + g + b) < min_diff)
		{
			min_diff = (r + g + b);
			result = &colors[n];
		}
	}
	return (result);
}

// TODO AHSL_GetNearest
