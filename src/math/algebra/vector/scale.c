
#include "libccc/math/algebra.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_vector2d	Vector2D_Scale(s_vector2d const* vector, t_float scale)
{
	s_vector2d result;

	result.x = vector->x * scale;
	result.y = vector->y * scale;
	return (result);
}



s_vector3d	Vector3D_Scale(s_vector3d const* vector, t_float scale)
{
	s_vector3d result;

	result.x = vector->x * scale;
	result.y = vector->y * scale;
	result.z = vector->z * scale;
	return (result);
}
