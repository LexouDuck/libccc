
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion_Div(s_quaternion const* q1, s_quaternion const* q2)
{
	t_float divisor;

	divisor = 1. / (
		(q2->s * q2->s) +
		(q2->i * q2->i) +
		(q2->j * q2->j) +
		(q2->k * q2->k));
	return ((s_quaternion)
	{
		.s = (q1->s * q2->s + q1->i * q2->i + q1->j * q2->j + q1->k * q2->k) * divisor,
		.i = (q1->i * q2->s - q1->s * q2->i - q1->j * q2->k + q1->k * q2->j) * divisor,
		.j = (q1->j * q2->s - q1->s * q2->j - q1->k * q2->i + q1->i * q2->k) * divisor,
		.k = (q1->k * q2->s - q1->s * q2->k - q1->i * q2->j + q1->j * q2->i) * divisor,
	});
}

#ifdef __cplusplus
s_quaternion	operator / (s_quaternion const q1, s_quaternion const q2)
{
	return Quaternion_Div(q1, q2);
}
#endif
