
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



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


s_vector4d		Vector4D_Invert(s_vector4d const* vector)
{
	s_vector4d result;

	result.x = -(vector->x);
	result.y = -(vector->y);
	result.z = -(vector->z);
	result.t = -(vector->t);
	return (result);
}


s_vector	Vector_Invert(s_vector const* vector)
{
	s_vector result;
	t_uint i;

	if CCCERROR((vector == NULL), ERROR_NULLPOINTER, NULL)
		return (VECTOR_NULL);
	result = Vector(vector->dims, NULL);
	if (result.values == NULL)
		return (result);
	for (i = 0; i < vector->dims; ++i)
	{
		result.values[i] = -(vector->values[i]);
	}
	return (result);
}
