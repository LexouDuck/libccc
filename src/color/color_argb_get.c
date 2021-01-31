
#include "libccc/color.h"



inline t_u8		c_color_argb16_get_a(t_argb16 color)	{ return ((t_u8)((color >> COLOR_ARGB16_A_BITINDEX) ? 1 : 0)); }
inline t_u8		c_color_argb16_get_r(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_R_BITINDEX))); }
inline t_u8		c_color_argb16_get_g(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_G_BITINDEX))); }
inline t_u8		c_color_argb16_get_b(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_B_BITINDEX))); }



inline t_u8		c_color_argb32_get_a(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_A_BITINDEX))); }
inline t_u8		c_color_argb32_get_r(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_R_BITINDEX))); }
inline t_u8		c_color_argb32_get_g(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_G_BITINDEX))); }
inline t_u8		c_color_argb32_get_b(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_B_BITINDEX))); }
