
#include "libft_color.h"



inline t_argb16	ft_color_argb16_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb16)(((a ? 1 : 0) << COLOR_ARGB16_A_BITINDEX) |
		((r & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_R_BITINDEX) |
		((g & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_G_BITINDEX) |
		((b & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_B_BITINDEX)));
}

inline t_argb16	ft_color_argb16_set_a(t_argb16 color, t_u8 a)	{ return ((color & ~COLOR_ARGB16_A) | (a << COLOR_ARGB16_A_BITINDEX)); }
inline t_argb16	ft_color_argb16_set_r(t_argb16 color, t_u8 r)	{ return ((color & ~COLOR_ARGB16_R) | (r << COLOR_ARGB16_R_BITINDEX)); }
inline t_argb16	ft_color_argb16_set_g(t_argb16 color, t_u8 g)	{ return ((color & ~COLOR_ARGB16_G) | (g << COLOR_ARGB16_G_BITINDEX)); }
inline t_argb16	ft_color_argb16_set_b(t_argb16 color, t_u8 b)	{ return ((color & ~COLOR_ARGB16_B) | (b << COLOR_ARGB16_B_BITINDEX)); }



inline t_argb32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb32)(
		((a & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_A_BITINDEX) |
		((r & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_R_BITINDEX) |
		((g & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_G_BITINDEX) |
		((b & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_B_BITINDEX)));
}

inline t_argb32	ft_color_argb32_set_a(t_argb32 color, t_u8 a)	{ return ((color & ~COLOR_ARGB32_A) | (a << COLOR_ARGB32_A_BITINDEX)); }
inline t_argb32	ft_color_argb32_set_r(t_argb32 color, t_u8 r)	{ return ((color & ~COLOR_ARGB32_R) | (r << COLOR_ARGB32_R_BITINDEX)); }
inline t_argb32	ft_color_argb32_set_g(t_argb32 color, t_u8 g)	{ return ((color & ~COLOR_ARGB32_G) | (g << COLOR_ARGB32_G_BITINDEX)); }
inline t_argb32	ft_color_argb32_set_b(t_argb32 color, t_u8 b)	{ return ((color & ~COLOR_ARGB32_B) | (b << COLOR_ARGB32_B_BITINDEX)); }
