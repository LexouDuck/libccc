
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion_Add(s_quaternion const* q1, s_quaternion const* q2)
{
	return ((s_quaternion)
	{
		.s = q1->s + q2->s,
		.i = q1->i + q2->i,
		.j = q1->j + q2->j,
		.k = q1->k + q2->k,
	});
}

#ifdef __cplusplus
s_quaternion	operator + (s_quaternion const q1, s_quaternion const q2)
{
	return Quaternion_Add(q1, q2);
}
#endif
