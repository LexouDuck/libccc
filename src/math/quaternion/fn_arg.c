
#include "libccc/math/quaternion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float	Quaternion_Arg(s_quaternion const* q)
{
	t_float	vector_norm = Float_Root2(
		(q->i * q->i) +
		(q->j * q->j) +
		(q->k * q->k));
	if CCCERROR((q->s == 0. && vector_norm == 0.), ERROR_MATHDOMAIN,
		"cannot compute the argument of a zero quaternion")
		return (NAN);
	return (Float_ArcTan2(vector_norm, q->s));
}
