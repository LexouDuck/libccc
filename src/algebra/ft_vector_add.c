
#include "libft_algebra.h"



s_vector2d	Vector2D_Add(s_vector2d const* v1, s_vector2d const* v2)
{
	s_vector2d result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	return (result);
}



s_vector3d	Vector3D_Add(s_vector3d const* v1, s_vector3d const* v2)
{
	s_vector3d result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	return (result);
}
