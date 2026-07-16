
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



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


s_vector4d	Vector4D_Scale(s_vector4d const* vector, t_float scale)
{
	s_vector4d result;

	result.x = vector->x * scale;
	result.y = vector->y * scale;
	result.z = vector->z * scale;
	result.t = vector->t * scale;
	return (result);
}


s_vector	Vector_Scale(s_vector const* vector, t_float scale)
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
		result.values[i] = vector->values[i] * scale;
	}
	return (result);
}
