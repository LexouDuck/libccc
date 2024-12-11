
#include "libccc/image/color.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline t_u8		Color_ARGB16_Get_A(t_argb16 color)	{ return ((t_u8)((color >> COLOR_ARGB16_A_BITINDEX) ? 1 : 0)); }
extern inline t_u8		Color_ARGB16_Get_R(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_R_BITINDEX))); }
extern inline t_u8		Color_ARGB16_Get_G(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_G_BITINDEX))); }
extern inline t_u8		Color_ARGB16_Get_B(t_argb16 color)	{ return ((t_u8)(COLOR_ARGB16_CHANNEL & (color >> COLOR_ARGB16_B_BITINDEX))); }



extern inline t_u8		Color_ARGB32_Get_A(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_A_BITINDEX))); }
extern inline t_u8		Color_ARGB32_Get_R(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_R_BITINDEX))); }
extern inline t_u8		Color_ARGB32_Get_G(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_G_BITINDEX))); }
extern inline t_u8		Color_ARGB32_Get_B(t_argb32 color)	{ return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> COLOR_ARGB32_B_BITINDEX))); }
