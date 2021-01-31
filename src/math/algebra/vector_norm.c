
#include "libccc/math/algebra.h"



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
