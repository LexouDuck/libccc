
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_Normalize(s_quaternion const* q)
{
	t_float	norm = Quaternion_Norm(q);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot normalize a zero quaternion")
		return (QUATERNION_ERROR);
	return ((s_quaternion)
	{
		.s = q->s / norm,
		.i = q->i / norm,
		.j = q->j / norm,
		.k = q->k / norm,
	});
}
