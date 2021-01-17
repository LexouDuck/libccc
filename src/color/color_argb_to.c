
#include "libccc_color.h"



t_argb32	Color_ARGB16_To_ARGB32(t_argb16 color)
{
	static const t_float factor = (float)COLOR_ARGB32_CHANNEL / (float)COLOR_ARGB16_CHANNEL;
	t_argb32 result;

	result = (color & COLOR_ARGB16_A) ? COLOR_ARGB32_A : 0;
	result |= (t_argb32)(Color_ARGB16_Get_R(color) * factor);
	result |= (t_argb32)(Color_ARGB16_Get_G(color) * factor);
	result |= (t_argb32)(Color_ARGB16_Get_B(color) * factor);
	return (result);
}

s_argb		Color_ARGB16_To_ARGB(t_argb16 color)
{
	static const t_float factor = 1. / (float)COLOR_ARGB16_CHANNEL;
	s_argb result;

	result.a = (Color_ARGB16_Get_A(color) ? 1. : 0.);
	result.r = (Color_ARGB16_Get_R(color) * factor);
	result.g = (Color_ARGB16_Get_G(color) * factor);
	result.b = (Color_ARGB16_Get_B(color) * factor);
	return (result);
}



t_argb16	Color_ARGB32_To_ARGB16(t_argb32 color)
{
	t_argb16 result;

	result = (color & COLOR_ARGB32_A) ? COLOR_ARGB16_A : 0;
	result |= (Color_ARGB16_Get_R(color) >> 3) << COLOR_ARGB16_R_BITINDEX;
	result |= (Color_ARGB16_Get_G(color) >> 3) << COLOR_ARGB16_G_BITINDEX;
	result |= (Color_ARGB16_Get_B(color) >> 3) << COLOR_ARGB16_B_BITINDEX;
	return (result);
}

s_argb		Color_ARGB32_To_ARGB(t_argb32 color)
{
	static const t_float factor = 1. / (float)COLOR_ARGB32_CHANNEL;
	s_argb result;

	result.a = (Color_ARGB16_Get_A(color) * factor);
	result.r = (Color_ARGB16_Get_R(color) * factor);
	result.g = (Color_ARGB16_Get_G(color) * factor);
	result.b = (Color_ARGB16_Get_B(color) * factor);
	return (result);
}



t_argb16	Color_ARGB_To_ARGB16(s_argb const* color)
{
	static const t_float factor = (float)COLOR_ARGB16_CHANNEL;
	t_argb16 result;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (color == NULL)
		return (0);
#endif
	result = (t_argb16)((color->a > 0) ? COLOR_ARGB16_A : 0);
	result |= (t_argb16)(color->r * factor) << COLOR_ARGB16_R_BITINDEX;
	result |= (t_argb16)(color->g * factor) << COLOR_ARGB16_G_BITINDEX;
	result |= (t_argb16)(color->b * factor) << COLOR_ARGB16_B_BITINDEX;
	return (result);
}

t_argb32	Color_ARGB_To_ARGB32(s_argb const* color)
{
	static const t_float factor = (float)COLOR_ARGB32_CHANNEL;
	t_argb32 result = 0;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (color == NULL)
		return (0);
#endif
	result |= (t_argb32)(color->a * factor) << COLOR_ARGB32_A_BITINDEX;
	result |= (t_argb32)(color->r * factor) << COLOR_ARGB32_R_BITINDEX;
	result |= (t_argb32)(color->g * factor) << COLOR_ARGB32_G_BITINDEX;
	result |= (t_argb32)(color->b * factor) << COLOR_ARGB32_B_BITINDEX;
	return (result);
}
