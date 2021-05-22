
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_vector2d*	Vector2D_New(t_float x, t_float y)
{
	s_vector2d* result;

	if (!(result = (s_vector2d*)Memory_Alloc(sizeof(s_vector2d))))
		return (NULL);
	result->x = x;
	result->y = y;
	return (result);
}



s_vector3d*	Vector3D_New(t_float x, t_float y, t_float z)
{
	s_vector3d* result;

	if (!(result = (s_vector3d*)Memory_Alloc(sizeof(s_vector3d))))
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}
