
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float		Vector2D_Norm(s_vector2d const* vector)
{
	t_float	tmp;
	t_float	sum;

	sum = 0;
	tmp = vector->x;	tmp *= tmp;	sum += tmp;
	tmp = vector->y;	tmp *= tmp;	sum += tmp;
	return (sum);
}



t_float		Vector3D_Norm(s_vector3d const* vector)
{
	t_float	tmp;
	t_float	sum;

	sum = 0;
	tmp = vector->x;	tmp *= tmp;	sum += tmp;
	tmp = vector->y;	tmp *= tmp;	sum += tmp;
	tmp = vector->z;	tmp *= tmp;	sum += tmp;
	return (sum);
}


t_float		Vector4D_Norm(s_vector4d const* vector)
{
	t_float	tmp;
	t_float	sum;

	sum = 0;
	tmp = vector->x;	tmp *= tmp;	sum += tmp;
	tmp = vector->y;	tmp *= tmp;	sum += tmp;
	tmp = vector->z;	tmp *= tmp;	sum += tmp;
	tmp = vector->t;	tmp *= tmp;	sum += tmp;
	return (sum);
}


t_float		Vector_Norm(s_vector const* vector)
{
	t_float	tmp;
	t_float	sum;
	t_uint i;

	if CCCERROR((vector == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	sum = 0;
	for (i = 0; i < vector->dims; ++i)
	{
		tmp = vector->values[i];
		tmp *= tmp;
		sum += tmp;
	}
	return (sum);
}
