
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `z = a + bi` within the plane spanned by `{1, v/b}`,
**	so we compute the complex principal value `asin(z) = -i*ln(iz + sqrt(1 - z^2))`
**	and map the imaginary part of the result back onto the `v/b` axis.
**	When `q` is a real quaternion, the `i` axis is used by convention.
*/
s_quaternion	Quaternion_ArcSin(s_quaternion const* q)
{
	t_float	a = q->s;
	t_float	b = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
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
		return ((s_quaternion){ .s = result_re, .i = result_im, .j = 0., .k = 0. });
	t_float	factor = result_im / b;
	return ((s_quaternion)
	{
		.s = result_re,
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
