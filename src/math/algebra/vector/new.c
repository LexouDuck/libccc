
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
s_vector2d	Vector2D(t_float x, t_float y)
{
	return ((s_vector2d)
	{
		.x = x,
		.y = y,
	});
}



inline
s_vector3d	Vector3D(t_float x, t_float y, t_float z)
{
	return ((s_vector3d)
	{
		.x = x,
		.y = y,
		.z = z,
	});
}



s_vector2d*	Vector2D_New(t_float x, t_float y)
{
	s_vector2d* result;

	result = (s_vector2d*)Memory_Allocate(sizeof(s_vector2d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->x = x;
	result->y = y;
	return (result);
}



s_vector3d*	Vector3D_New(t_float x, t_float y, t_float z)
{
	s_vector3d* result;

	result = (s_vector3d*)Memory_Allocate(sizeof(s_vector3d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}
