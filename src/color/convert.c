
#include "libccc/color.h"
#include "libccc/math/math.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_ahsl		Color_ARGB_To_AHSL(s_argb const* color)
{
	static const t_float factor = TAU / 6.;
	s_ahsl result = {0};
	s_argb c;
	t_float min = 1.;
	t_float max = 0.;
	t_float chroma;

	HANDLE_ERROR(NULLPOINTER, (color == NULL), return (result);)
	c = *color;
	result.a = c.a;
	// get min and max channel values
	if (min > c.r)	{ min = c.r; }	if (max < c.r)	{ max = c.r; }
	if (min > c.g)	{ min = c.g; }	if (max < c.g)	{ max = c.g; }
	if (min > c.b)	{ min = c.b; }	if (max < c.b)	{ max = c.b; }
	chroma = max - min;
	result.lum = (max + min);
	if (result.lum == 0)
		result.sat = 0;
	else if (result.lum <= 1.)
		result.sat = chroma / (result.lum);
	else
		result.sat = chroma / (2. - result.lum);
	result.lum *= 0.5;
	if (chroma > 0)
	{
		if (max == c.r) result.hue = (c.g - c.b) / chroma + (c.g < c.b ? 6. : 0.) + 0.;
		if (max == c.g) result.hue = (c.b - c.r) / chroma + (c.b < c.r ? 6. : 0.) + 2.;
		if (max == c.b) result.hue = (c.r - c.g) / chroma + (c.r < c.g ? 6. : 0.) + 4.;
		// since hue is expressed as a number in interval [0,6], scale it to interval [0,PI*2]
		result.hue *= factor;
	}
	else result.hue = 0; // TODO maybe NAN ? since it is a division by 0, mathematically speaking
	return (result);
}



s_argb		Color_AHSL_To_ARGB(s_ahsl const* color)
{
	static const t_float factor = 1. / TAU;
	static const t_float third1 = 1. / 3.;
	static const t_float third2 = 2. / 3.;
	s_argb result = {0};
	s_ahsl c;
	t_float tmp1;
	t_float tmp2;

	HANDLE_ERROR(NULLPOINTER, (color == NULL), return (result);)
	c = *color;
	result.a = c.a;
	if (c.sat == 0)
	{
		result.r = c.lum;
		result.g = c.lum;
		result.b = c.lum;
		return (result);
	}
	if (c.lum <= 0.5)
		tmp1 = c.lum * (1. + c.sat);
	else tmp1 = c.lum + c.sat - (c.lum * c.sat);
	tmp2 = (2. * c.lum) - tmp1;
	c.hue *= factor; // scale hue (radian angle) to be in interval [0,1]
	result.r = c.hue + third1;
	     if (result.r * 6. < 1.)	result.r = tmp2 + (tmp1 - tmp2) * 6 * result.r;
	else if (result.r * 2. < 1.)	result.r = tmp1;
	else if (result.r * 3. < 2.)	result.r = tmp2 + (tmp1 - tmp2) * 6 * (third2 - result.r);
	else							result.r = tmp2;
	result.g = c.hue;
	     if (result.g * 6. < 1.)	result.g = tmp2 + (tmp1 - tmp2) * 6 * result.g;
	else if (result.g * 2. < 1.)	result.g = tmp1;
	else if (result.g * 3. < 2.)	result.g = tmp2 + (tmp1 - tmp2) * 6 * (third2 - result.g);
	else							result.g = tmp2;
	result.b = c.hue - third1;
	     if (result.b * 6. < 1.)	result.b = tmp2 + (tmp1 - tmp2) * 6 * result.b;
	else if (result.b * 2. < 1.)	result.b = tmp1;
	else if (result.b * 3. < 2.)	result.b = tmp2 + (tmp1 - tmp2) * 6 * (third2 - result.b);
	else							result.b = tmp2;
	return (result);
}
