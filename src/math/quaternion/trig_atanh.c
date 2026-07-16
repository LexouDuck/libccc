
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `z = a + bi` within the plane spanned by `{1, v/b}`,
**	so we compute the complex principal value `atanh(z) = (1/2)*ln((1 + z) / (1 - z))`
**	and map the imaginary part of the result back onto the `v/b` axis.
**	When `q` is a real quaternion, the `i` axis is used by convention.
*/
s_quaternion	Quaternion_InvTanH(s_quaternion const* q)
{
	t_float	a = q->s;
	t_float	b = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	// w = (1 + z) / (1 - z), with z = a + bi
	t_float	num_re = 1. + a;
	t_float	num_im = +b;
	t_float	den_re = 1. - a;
	t_float	den_im = -b;
	t_float	den_norm = (den_re * den_re) + (den_im * den_im);
	t_float	w_re = (num_re * den_re + num_im * den_im) / den_norm;
	t_float	w_im = (num_im * den_re - num_re * den_im) / den_norm;
	// atanh(z) = ln(w)/2 = ln|w|/2 + (i/2)*arg(w)
	t_float	result_re = Float_Log(Float_Root2(w_re * w_re + w_im * w_im)) * 0.5;
	t_float	result_im = Float_ArcTan2(w_im, w_re) * 0.5;
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
