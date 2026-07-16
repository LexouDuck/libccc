
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


t_float		Vector4D_Dot(s_vector4d const* v1, s_vector4d const* v2)
{
	t_float	result = 0;

	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	result += (v1->z * v2->z);
	result += (v1->t * v2->t);
	return (result);
}


t_float		Vector_Dot(s_vector const* v1, s_vector const* v2)
{
	t_float	result = 0;
	t_uint i;

	if CCCERROR((v1 == NULL || v2 == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((v1->dims != v2->dims), ERROR_INVALIDARGS, 
		"vectors must have the same amount of dimensions to compute a dot product")
		return (0);
	for (i = 0; i < v1->dims; ++i)
	{
		result += (v1->values[i] * v2->values[i]);
	}
	return (result);
}
