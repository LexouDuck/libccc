
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any octonion `o = a + v` (with `v` its vector part, of norm `b`),
**	`o` behaves like the complex number `z = a + bi` within the plane spanned by `{1, v/b}`,
**	so we compute the complex principal value `asin(z) = -i*ln(iz + sqrt(1 - z^2))`
**	and map the imaginary part of the result back onto the `v/b` axis.
**	When `o` is a real octonion, the `i` axis is used by convention.
*/
s_octonion	Octonion_ArcSin(s_octonion const* o)
{
	t_float	a = o->s;
	t_float	b = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	// w = iz + sqrt(1 - z^2), with z = a + bi
	t_float	sq_re = 1. - (a * a) + (b * b);
	t_float	sq_im = -2. * a * b;
	t_float	radius = Float_Root2(sq_re * sq_re + sq_im * sq_im);
	t_float	root_re = Float_Root2((radius + sq_re) * 0.5);
	t_float	root_im = (sq_im < 0. ? -1. : +1.) * Float_Root2((radius - sq_re) * 0.5);
	t_float	w_re = root_re - b;
	t_float	w_im = root_im + a;
	// asin(z) = -i*ln(w) = arg(w) - i*ln|w|
	t_float	result_re = Float_ArcTan2(w_im, w_re);
	t_float	result_im = -Float_Log(Float_Root2(w_re * w_re + w_im * w_im));
	if (b == 0.)
		return ((s_octonion){ .s = result_re, .i = result_im, .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	t_float	factor = result_im / b;
	return ((s_octonion)
	{
		.s = result_re,
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
