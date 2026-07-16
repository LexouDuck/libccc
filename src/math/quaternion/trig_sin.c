
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any quaternion `q = a + v` (with `v` its vector part, of norm `b`),
**	`q` behaves like the complex number `a + bi` within the plane spanned by `{1, v/b}`, so:
**	sin(a + v) = sin(a)*cosh(b) + (v/b)*cos(a)*sinh(b)
*/
s_quaternion	Quaternion_Sin(s_quaternion const* q)
{
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	factor = (vector_norm == 0. ? 0. :
		Float_Cos(q->s) * Float_SinH(vector_norm) / vector_norm);
	return ((s_quaternion)
	{
		.s = Float_Sin(q->s) * Float_CosH(vector_norm),
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
