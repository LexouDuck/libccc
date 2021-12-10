
#include "libccc/color.h"
#include "libccc/sys/io.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



t_u8	IO_GetColor(t_argb32 color)
{
	t_float factor = (5. / COLOR_ARGB32_CHANNEL);
	t_u8 r = Color_ARGB32_Get_R(color);
	t_u8 g = Color_ARGB32_Get_G(color);
	t_u8 b = Color_ARGB32_Get_B(color);
	t_s32 delta = (COLOR_ARGB32_CHANNEL / 100.);
	t_s32 ansi;
	if ((b - delta <= r && r <= b + delta) &&
		(g - delta <= r && r <= g + delta) &&
		(r - delta <= g && g <= r + delta) &&
		(b - delta <= g && g <= b + delta) &&
		(r - delta <= b && b <= r + delta) &&
		(g - delta <= b && b <= g + delta))
	{
		ansi = 232 + (t_s32)Float_Round(b * factor * 4.8);
		if (ansi >= 256) ansi = 15;
	}
	else ansi = 16 +
		(t_s32)Float_Round(r * factor) * 36 +
		(t_s32)Float_Round(g * factor) * 6 +
		(t_s32)Float_Round(b * factor);
	return ((t_u8)ansi);
}
