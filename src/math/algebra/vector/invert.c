
#include "libccc/math/algebra.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_vector2d		Vector2D_Invert(s_vector2d const* vector)
{
	s_vector2d result;

	result.x = -(vector->x);
	result.y = -(vector->y);
	return (result);
}



s_vector3d		Vector3D_Invert(s_vector3d const* vector)
{
	s_vector3d result;

	result.x = -(vector->x);
	result.y = -(vector->y);
	result.z = -(vector->z);
	return (result);
}
