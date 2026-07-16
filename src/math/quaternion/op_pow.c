
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_Pow(s_quaternion const* q, t_float power)
{
	t_float	norm = Quaternion_Norm(q);
	if (norm == 0.)
	{
		if (power > 0.)
			return (QUATERNION_NULL);
		if (power == 0.)
			return ((s_quaternion){ .s = 1., .i = 0., .j = 0., .k = 0. });
		if CCCERROR((power < 0.), ERROR_MATHDOMAIN,
			"cannot raise a zero quaternion to a negative power")
			return (QUATERNION_ERROR);
	}
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	angle = power * Float_ArcTan2(vector_norm, q->s);
	t_float	norm_pow = Float_Pow(norm, power);
	t_float	scal = norm_pow * Float_Cos(angle);
	t_float	vect = norm_pow * Float_Sin(angle);
	if (vector_norm == 0.)
	{	// real quaternion: by convention, use the `i` axis (only matters when `q->s < 0`)
		return ((s_quaternion)
		{
			.s = scal,
			.i = vect,
			.j = 0.,
			.k = 0.,
		});
	}
	t_float	factor = vect / vector_norm;
	return ((s_quaternion)
	{
		.s = scal,
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
