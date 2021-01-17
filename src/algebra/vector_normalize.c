
#include "libccc_algebra.h"



s_vector2d	Vector2D_Normalize(s_vector2d const* vector)
{
	s_vector2d result = {0};
	t_float	norm;

	norm = Vector2D_Norm(vector);
	if (norm > 0)
	{
		norm = 1 / Math_SquareRoot(norm); // TODO InvSqRt function ?
		result.x = vector->x * norm;
		result.y = vector->y * norm;
	}
	return (result);
}



s_vector3d	Vector3D_Normalize(s_vector3d const* vector)
{
	s_vector3d result = {0};
	t_float	norm;

	norm = Vector3D_Norm(vector);
	if (norm > 0)
	{
		norm = 1 / Math_SquareRoot(norm); // TODO InvSqRt function ?
		result.x = vector->x * norm;
		result.y = vector->y * norm;
		result.z = vector->z * norm;
	}
	return (result);
}
