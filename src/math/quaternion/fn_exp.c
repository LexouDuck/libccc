
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_Exp(s_quaternion const* q)
{
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	exp_s = Float_Exp(q->s);
	t_float	factor = (vector_norm == 0. ? exp_s :
		exp_s * Float_Sin(vector_norm) / vector_norm);
	return ((s_quaternion)
	{
		.s = exp_s * Float_Cos(vector_norm),
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
