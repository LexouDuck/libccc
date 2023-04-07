
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float		Vector2D_Dot(s_vector2d const* v1, s_vector2d const* v2)
{
	t_float	result = 0;

	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	return (result);
}

t_float		Vector3D_Dot(s_vector3d const* v1, s_vector3d const* v2)
{
	t_float	result = 0;

	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	result += (v1->z * v2->z);
	return (result);
}
