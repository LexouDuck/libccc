
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `z = a + bi` within the plane spanned by `{1, v/b}`,
**	so we compute the complex principal value `acosh(z) = ln(z + sqrt(z - 1) * sqrt(z + 1))`
**	and map the imaginary part of the result back onto the `v/b` axis.
**	When `q` is a real quaternion, the `i` axis is used by convention.
*/
s_quaternion	Quaternion_InvCosH(s_quaternion const* q)
{
	t_float	a = q->s;
	t_float	b = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	// sqrt(z - 1), with z = a + bi
	t_float	radius1 = Float_Root2((a - 1.) * (a - 1.) + b * b);
	t_float	root1_re = Float_Root2((radius1 + (a - 1.)) * 0.5);
	t_float	root1_im = (b < 0. ? -1. : +1.) * Float_Root2((radius1 - (a - 1.)) * 0.5);
	// sqrt(z + 1)
	t_float	radius2 = Float_Root2((a + 1.) * (a + 1.) + b * b);
	t_float	root2_re = Float_Root2((radius2 + (a + 1.)) * 0.5);
	t_float	root2_im = (b < 0. ? -1. : +1.) * Float_Root2((radius2 - (a + 1.)) * 0.5);
	// w = z + sqrt(z - 1) * sqrt(z + 1)
	t_float	w_re = a + (root1_re * root2_re - root1_im * root2_im);
	t_float	w_im = b + (root1_re * root2_im + root1_im * root2_re);
	// acosh(z) = ln(w) = ln|w| + i*arg(w)
	t_float	result_re = Float_Log(Float_Root2(w_re * w_re + w_im * w_im));
	t_float	result_im = Float_ArcTan2(w_im, w_re);
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
