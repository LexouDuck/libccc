
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	Vector2D_Equals(s_vector2d const* v1, s_vector2d const* v2)
{
	return (
		(v1->x == v2->x) &&
		(v1->y == v2->y));
}



_INLINE()
t_bool	Vector3D_Equals(s_vector3d const* v1, s_vector3d const* v2)
{
	return (
		(v1->x == v2->x) &&
		(v1->y == v2->y) &&
		(v1->z == v2->z));
}
