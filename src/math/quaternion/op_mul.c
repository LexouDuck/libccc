
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion_Mul(s_quaternion const* q1, s_quaternion const* q2)
{
	return ((s_quaternion)
	{
		.s = q1->s * q2->s - q1->i * q2->i - q1->j * q2->j - q1->k * q2->k,
		.i = q1->s * q2->i + q1->i * q2->s + q1->j * q2->k - q1->k * q2->j,
		.j = q1->s * q2->j - q1->i * q2->k + q1->j * q2->s + q1->k * q2->i,
		.k = q1->s * q2->k + q1->i * q2->j - q1->j * q2->i + q1->k * q2->s,
	});
}

#ifdef __cplusplus
s_quaternion	operator * (s_quaternion const q1, s_quaternion const q2)
{
	return Quaternion_Mul(q1, q2);
}
#endif
