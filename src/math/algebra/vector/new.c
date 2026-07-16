
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_vector2d	Vector2D(t_float x, t_float y)
{
	return ((s_vector2d)
	{
		.x = x,
		.y = y,
	});
}



_INLINE()
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


_INLINE()
s_vector4d	Vector4D(t_float x, t_float y, t_float z, t_float t)
{
	return ((s_vector4d)
	{
		.x = x,
		.y = y,
		.z = z,
		.t = t,
	});
}



s_vector4d*	Vector4D_New(t_float x, t_float y, t_float z, t_float t)
{
	s_vector4d* result;

	result = (s_vector4d*)Memory_Allocate(sizeof(s_vector4d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	result->t = t;
	return (result);
}


s_vector	Vector(t_uint dims, t_float const* values)
{
	s_vector result = VECTOR_NULL;

	if (dims == 0)
		return (result);
	result.values = (t_float*)Memory_New(dims * sizeof(t_float));
	if CCCERROR((result.values == NULL), ERROR_ALLOCFAILURE, NULL)
		return (VECTOR_NULL);
	result.dims = dims;
	if (values != NULL)
		Memory_Copy(result.values, values, dims * sizeof(t_float));
	return (result);
}



s_vector*	Vector_New(t_uint dims, t_float const* values)
{
	s_vector* result;

	result = (s_vector*)Memory_New(sizeof(s_vector));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	*result = Vector(dims, values);
	if CCCERROR((dims != 0 && result->values == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Delete((void**)&result);
		return (NULL);
	}
	return (result);
}
