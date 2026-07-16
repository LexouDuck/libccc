
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any octonion `o = a + v` (with `v` its vector part, of norm `b`),
**	`o` behaves like the complex number `z = a + bi` within the plane spanned by `{1, v/b}`,
**	so we compute the complex principal value `atan(z) = -(i/2)*ln((1 + iz) / (1 - iz))`
**	and map the imaginary part of the result back onto the `v/b` axis.
**	When `o` is a real octonion, the `i` axis is used by convention.
*/
s_octonion	Octonion_ArcTan(s_octonion const* o)
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
	// w = (1 + iz) / (1 - iz), with z = a + bi
	t_float	num_re = 1. - b;
	t_float	num_im = +a;
	t_float	den_re = 1. + b;
	t_float	den_im = -a;
	t_float	den_norm = (den_re * den_re) + (den_im * den_im);
	t_float	w_re = (num_re * den_re + num_im * den_im) / den_norm;
	t_float	w_im = (num_im * den_re - num_re * den_im) / den_norm;
	// atan(z) = -(i/2)*ln(w) = arg(w)/2 - (i/2)*ln|w|
	t_float	result_re = Float_ArcTan2(w_im, w_re) * 0.5;
	t_float	result_im = -Float_Log(Float_Root2(w_re * w_re + w_im * w_im)) * 0.5;
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
