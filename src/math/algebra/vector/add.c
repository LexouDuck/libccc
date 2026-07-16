
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



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


s_vector4d	Vector4D_Add(s_vector4d const* v1, s_vector4d const* v2)
{
	s_vector4d result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	result.t = v1->t + v2->t;
	return (result);
}


s_vector	Vector_Add(s_vector const* v1, s_vector const* v2)
{
	s_vector result;
	t_uint i;

	if CCCERROR((v1 == NULL || v2 == NULL), ERROR_NULLPOINTER, NULL)
		return (VECTOR_NULL);
	if CCCERROR((v1->dims != v2->dims), ERROR_INVALIDARGS, 
		"vectors must have the same amount of dimensions to be added")
		return (VECTOR_NULL);
	result = Vector(v1->dims, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < v1->dims; ++i)
	{
		result.values[i] = v1->values[i] + v2->values[i];
	}
	return (result);
}
