
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `a + bi` within the plane spanned by `{1, v/b}`, so:
**	tanh(a + v) = (sinh(2a) + (v/b)*sin(2b)) / (cosh(2a) + cos(2b))
*/
s_quaternion	Quaternion_TanH(s_quaternion const* q)
{
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	denominator = Float_CosH(2. * q->s) + Float_Cos(2. * vector_norm);
	t_float	factor = (vector_norm == 0. ? 0. :
		Float_Sin(2. * vector_norm) / (vector_norm * denominator));
	return ((s_quaternion)
	{
		.s = Float_SinH(2. * q->s) / denominator,
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
