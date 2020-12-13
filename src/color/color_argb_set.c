
#include "libft_color.h"



inline t_argb16	Color_ARGB16_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb16)(((a ? 1 : 0) << COLOR_ARGB16_A_BITINDEX) |
		((r & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_R_BITINDEX) |
		((g & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_G_BITINDEX) |
		((b & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_B_BITINDEX)));
}
inline t_argb16	Color_ARGB16_Set_A(t_argb16 color, t_bool a){ return ((color & ~COLOR_ARGB16_A) | (a << COLOR_ARGB16_A_BITINDEX)); }
inline t_argb16	Color_ARGB16_Set_R(t_argb16 color, t_u8 r)	{ return ((color & ~COLOR_ARGB16_R) | (r << COLOR_ARGB16_R_BITINDEX)); }
inline t_argb16	Color_ARGB16_Set_G(t_argb16 color, t_u8 g)	{ return ((color & ~COLOR_ARGB16_G) | (g << COLOR_ARGB16_G_BITINDEX)); }
inline t_argb16	Color_ARGB16_Set_B(t_argb16 color, t_u8 b)	{ return ((color & ~COLOR_ARGB16_B) | (b << COLOR_ARGB16_B_BITINDEX)); }



inline t_argb32	Color_ARGB32_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb32)(
		((a & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_A_BITINDEX) |
		((r & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_R_BITINDEX) |
		((g & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_G_BITINDEX) |
		((b & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_B_BITINDEX)));
}
inline t_argb32	Color_ARGB32_Set_A(t_argb32 color, t_u8 a)	{ return ((color & ~COLOR_ARGB32_A) | (a << COLOR_ARGB32_A_BITINDEX)); }
inline t_argb32	Color_ARGB32_Set_R(t_argb32 color, t_u8 r)	{ return ((color & ~COLOR_ARGB32_R) | (r << COLOR_ARGB32_R_BITINDEX)); }
inline t_argb32	Color_ARGB32_Set_G(t_argb32 color, t_u8 g)	{ return ((color & ~COLOR_ARGB32_G) | (g << COLOR_ARGB32_G_BITINDEX)); }
inline t_argb32	Color_ARGB32_Set_B(t_argb32 color, t_u8 b)	{ return ((color & ~COLOR_ARGB32_B) | (b << COLOR_ARGB32_B_BITINDEX)); }



inline s_argb	Color_ARGB_Set(t_float a, t_float r, t_float g, t_float b)
{
	s_argb result;

	if (a < 0.) result.a = 0.; else if (a > 1.) result.a = 1.; else result.a = a;
	if (r < 0.) result.r = 0.; else if (r > 1.) result.r = 1.; else result.r = r;
	if (g < 0.) result.g = 0.; else if (g > 1.) result.g = 1.; else result.g = g;
	if (b < 0.) result.b = 0.; else if (b > 1.) result.b = 1.; else result.b = b;
	return (result);
}
inline void		Color_ARGB_Set_A(s_argb* color, t_float a)	{ if (a < 0.) color->a = 0.; else if (a > 1.) color->a = 1.; else color->a = a; }
inline void		Color_ARGB_Set_R(s_argb* color, t_float r)	{ if (r < 0.) color->r = 0.; else if (r > 1.) color->r = 1.; else color->r = r; }
inline void		Color_ARGB_Set_G(s_argb* color, t_float g)	{ if (g < 0.) color->g = 0.; else if (g > 1.) color->g = 1.; else color->g = g; }
inline void		Color_ARGB_Set_B(s_argb* color, t_float b)	{ if (b < 0.) color->b = 0.; else if (b > 1.) color->b = 1.; else color->b = b; }
