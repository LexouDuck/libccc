
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_float	Quaternion_Norm(s_quaternion const* q)
{
	return (Float_Root2(
		(q->s * q->s) +
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k)));
}
