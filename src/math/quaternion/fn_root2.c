
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion_Root2(s_quaternion const* q)
{
	return (Quaternion_Pow(q, 0.5));
}
