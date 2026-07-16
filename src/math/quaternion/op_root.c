
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_quaternion	Quaternion_RootN(s_quaternion const* q, t_u8 n)
{
	if CCCERROR((n == 0), ERROR_MATHDOMAIN,
		"cannot compute the zero-th root of a quaternion")
		return (QUATERNION_ERROR);
	if (n == 1)
		return (*q);
	return (Quaternion_Pow(q, 1. / (t_float)n));
}
