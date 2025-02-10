
#include "libccc/image/color.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_argb16	Color_ARGB16_Set(t_bool a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb16)(((a ? 1 : 0) << COLOR_ARGB16_A_BITINDEX) |
		((r & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_R_BITINDEX) |
		((g & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_G_BITINDEX) |
		((b & COLOR_ARGB16_CHANNEL) << COLOR_ARGB16_B_BITINDEX)));
}
_INLINE() t_argb16	Color_ARGB16_Set_A(t_argb16 color, t_bool a)	{ return (a ? (color | COLOR_ARGB16_A) : ((color & ~COLOR_ARGB16_A))); }
_INLINE() t_argb16	Color_ARGB16_Set_R(t_argb16 color, t_u8 r)	{ return ((color & ~COLOR_ARGB16_R) | ((r << COLOR_ARGB16_R_BITINDEX) & COLOR_ARGB16_R)); }
_INLINE() t_argb16	Color_ARGB16_Set_G(t_argb16 color, t_u8 g)	{ return ((color & ~COLOR_ARGB16_G) | ((g << COLOR_ARGB16_G_BITINDEX) & COLOR_ARGB16_G)); }
_INLINE() t_argb16	Color_ARGB16_Set_B(t_argb16 color, t_u8 b)	{ return ((color & ~COLOR_ARGB16_B) | ((b << COLOR_ARGB16_B_BITINDEX) & COLOR_ARGB16_B)); }



_INLINE()
t_argb32	Color_ARGB32_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb32)(
		((a & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_A_BITINDEX) |
		((r & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_R_BITINDEX) |
		((g & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_G_BITINDEX) |
		((b & COLOR_ARGB32_CHANNEL) << COLOR_ARGB32_B_BITINDEX)));
}
_INLINE() t_argb32	Color_ARGB32_Set_A(t_argb32 color, t_u8 a)	{ return ((color & ~COLOR_ARGB32_A) | (a << COLOR_ARGB32_A_BITINDEX)); }
_INLINE() t_argb32	Color_ARGB32_Set_R(t_argb32 color, t_u8 r)	{ return ((color & ~COLOR_ARGB32_R) | (r << COLOR_ARGB32_R_BITINDEX)); }
_INLINE() t_argb32	Color_ARGB32_Set_G(t_argb32 color, t_u8 g)	{ return ((color & ~COLOR_ARGB32_G) | (g << COLOR_ARGB32_G_BITINDEX)); }
_INLINE() t_argb32	Color_ARGB32_Set_B(t_argb32 color, t_u8 b)	{ return ((color & ~COLOR_ARGB32_B) | (b << COLOR_ARGB32_B_BITINDEX)); }



_INLINE()
s_argb	Color_ARGB_Set(t_float a, t_float r, t_float g, t_float b)
{
	s_argb result = COLOR_ARGB_NULL;
	Color_ARGB_Set_A(&result, a);
	Color_ARGB_Set_R(&result, r);
	Color_ARGB_Set_G(&result, g);
	Color_ARGB_Set_B(&result, b);
	return (result);
}
_INLINE() void	Color_ARGB_Set_A(s_argb* color, t_float a)	{ if (a < 0.) color->a = 0.; else if (a > 1.) color->a = 1.; else color->a = a; }
_INLINE() void	Color_ARGB_Set_R(s_argb* color, t_float r)	{ if (r < 0.) color->r = 0.; else if (r > 1.) color->r = 1.; else color->r = r; }
_INLINE() void	Color_ARGB_Set_G(s_argb* color, t_float g)	{ if (g < 0.) color->g = 0.; else if (g > 1.) color->g = 1.; else color->g = g; }
_INLINE() void	Color_ARGB_Set_B(s_argb* color, t_float b)	{ if (b < 0.) color->b = 0.; else if (b > 1.) color->b = 1.; else color->b = b; }



_INLINE()
s_ahsl	Color_AHSL_Set(t_float a, t_float h, t_float s, t_float l)
{
	s_ahsl result = COLOR_AHSL_NULL;
	Color_AHSL_Set_A(&result, a);
	Color_AHSL_Set_H(&result, h);
	Color_AHSL_Set_S(&result, s);
	Color_AHSL_Set_L(&result, l);
	return (result);
}
_INLINE() void	Color_AHSL_Set_A(s_ahsl* color, t_float a)	{ if (a < 0.) color->a   = 0.; else if (a > 1.) color->a   = 1.; else color->a   = a; }
_INLINE() void	Color_AHSL_Set_H(s_ahsl* color, t_float h)	{ if (h < 0.) color->hue = 0.; else { while (h > TAU) { h -= TAU; } color->hue = h; } }
_INLINE() void	Color_AHSL_Set_S(s_ahsl* color, t_float s)	{ if (s < 0.) color->sat = 0.; else if (s > 1.) color->sat = 1.; else color->sat = s; }
_INLINE() void	Color_AHSL_Set_L(s_ahsl* color, t_float l)	{ if (l < 0.) color->lum = 0.; else if (l > 1.) color->lum = 1.; else color->lum = l; }
