
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `a + bi` within the plane spanned by `{1, v/b}`, so:
**	tan(a + v) = (sin(2a) + (v/b)*sinh(2b)) / (cos(2a) + cosh(2b))
*/
s_quaternion	Quaternion_Tan(s_quaternion const* q)
{
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	denominator = Float_Cos(2. * q->s) + Float_CosH(2. * vector_norm);
	t_float	factor = (vector_norm == 0. ? 0. :
		Float_SinH(2. * vector_norm) / (vector_norm * denominator));
	return ((s_quaternion)
	{
		.s = Float_Sin(2. * q->s) / denominator,
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
