
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



s_vector2d	Vector2D_Normalize(s_vector2d const* vector)
{
	s_vector2d result = VECTOR2D_NULL;
	t_float	norm;

	norm = Vector2D_Norm(vector);
	if (norm > 0)
	{
		norm = 1 / Float_SquareRoot(norm); // TODO InvSqRt function ?
		result.x = vector->x * norm;
		result.y = vector->y * norm;
	}
	return (result);
}



s_vector3d	Vector3D_Normalize(s_vector3d const* vector)
{
	s_vector3d result = VECTOR3D_NULL;
	t_float	norm;

	norm = Vector3D_Norm(vector);
	if (norm > 0)
	{
		norm = 1 / Float_SquareRoot(norm); // TODO InvSqRt function ?
		result.x = vector->x * norm;
		result.y = vector->y * norm;
		result.z = vector->z * norm;
	}
	return (result);
}
