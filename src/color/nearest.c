
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

	LIBCONFIG_HANDLE_NULLPOINTER(colors, NULL)
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

	LIBCONFIG_HANDLE_NULLPOINTER(colors, NULL)
	min_diff = U32_MAX;
	result = NULL;
	while (n--)
	{
		diff = Color_ARGB32_Difference(target, colors[n]);
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
	t_u32 diff;
	t_u32 min_diff;
	s_argb const* result;

	LIBCONFIG_HANDLE_NULLPOINTER(colors, NULL)
	min_diff = U32_MAX;
	result = NULL;
	while (n--)
	{
		diff = Color_ARGB32_Difference(
			Color_ARGB_To_ARGB32(&target),
			Color_ARGB_To_ARGB32(&colors[n]));
		if (diff < min_diff)
		{
			min_diff = diff;
			result = &colors[n];
		}
	}
	return (result);
}

// TODO AHSL_GetNearest
