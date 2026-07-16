
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_Log(s_quaternion const* q)
{
	t_float	norm = Quaternion_Norm(q);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot compute the logarithm of a zero quaternion")
		return (QUATERNION_ERROR);
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	t_float	angle = Float_ArcTan2(vector_norm, q->s);
	if (vector_norm == 0.)
	{	// real quaternion: by convention, use the `i` axis (only matters when `q->s < 0`)
		return ((s_quaternion)
		{
			.s = Float_Log(norm),
			.i = angle,
			.j = 0.,
			.k = 0.,
		});
	}
	t_float	factor = angle / vector_norm;
	return ((s_quaternion)
	{
		.s = Float_Log(norm),
		.i = q->i * factor,
		.j = q->j * factor,
		.k = q->k * factor,
	});
}
