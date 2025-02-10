
#include "libccc/math.h"
#include "libccc/image/color.h"

#include LIBCONFIG_ERROR_INCLUDE



t_u16	Color_ARGB16_Difference(t_argb16 c1, t_argb16 c2)
{
	t_u16 delta_r = S16_Abs(Color_ARGB16_Get_R(c1) - Color_ARGB16_Get_R(c2));	delta_r *= delta_r;
	t_u16 delta_g = S16_Abs(Color_ARGB16_Get_G(c1) - Color_ARGB16_Get_G(c2));	delta_g *= delta_g;
	t_u16 delta_b = S16_Abs(Color_ARGB16_Get_B(c1) - Color_ARGB16_Get_B(c2));	delta_b *= delta_b;
	if ((Color_ARGB16_Get_R(c1) + Color_ARGB16_Get_R(c2) / 2) < (COLOR_ARGB16_CHANNEL + 1) / 2)
		return  (2 * delta_r + 4 * delta_g + 3 * delta_b);
	else return (3 * delta_r + 4 * delta_g + 2 * delta_b);
}



t_u32	Color_ARGB32_Difference(t_argb32 c1, t_argb32 c2)
{
	t_u32 delta_r = S32_Abs(Color_ARGB32_Get_R(c1) - Color_ARGB32_Get_R(c2));	delta_r *= delta_r;
	t_u32 delta_g = S32_Abs(Color_ARGB32_Get_G(c1) - Color_ARGB32_Get_G(c2));	delta_g *= delta_g;
	t_u32 delta_b = S32_Abs(Color_ARGB32_Get_B(c1) - Color_ARGB32_Get_B(c2));	delta_b *= delta_b;
	if ((Color_ARGB32_Get_R(c1) + Color_ARGB32_Get_R(c2) / 2) < (COLOR_ARGB32_CHANNEL + 1) / 2)
		return  (2 * delta_r + 4 * delta_g + 3 * delta_b);
	else return (3 * delta_r + 4 * delta_g + 2 * delta_b);
}
