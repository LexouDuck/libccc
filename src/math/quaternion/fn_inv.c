
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_Inverse(s_quaternion const* q)
{
	t_float	norm_squared = (
		(q->s * q->s) +
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	if CCCERROR((norm_squared == 0.), ERROR_MATHDOMAIN,
		"cannot compute inverse of a zero quaternion")
		return (QUATERNION_ERROR);
	return ((s_quaternion)
	{
		.s = +q->s / norm_squared,
		.i = -q->i / norm_squared,
		.j = -q->j / norm_squared,
		.k = -q->k / norm_squared,
	});
}

#ifdef __cplusplus
s_quaternion	operator ! (s_quaternion const q)
{
	return Quaternion_Inverse(q);
}
#endif
