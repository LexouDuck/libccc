
#include "libccc/math/quaternion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion_Conjugate(s_quaternion const* q)
{
	return ((s_quaternion)
	{
		.s = +q->s,
		.i = -q->i,
		.j = -q->j,
		.k = -q->k,
	});
}

#ifdef __cplusplus
s_quaternion	operator ~ (s_quaternion const q)
{
	return Quaternion_Conjugate(q);
}
#endif
