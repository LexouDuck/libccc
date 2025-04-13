
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	Quaternion_Equals(s_quaternion const* q1, s_quaternion const* q2)
{
	return ((q1->s == q2->s) &&
			(q1->i == q2->i) &&
			(q1->j == q2->j) &&
			(q1->k == q2->k));
}

#ifdef __cplusplus
t_bool	operator == (s_quaternion const q1, s_quaternion const q2)
{
	return Quaternion_Equals(q1, q2);
}
#endif
