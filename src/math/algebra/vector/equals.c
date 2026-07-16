
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	Vector2D_Equals(s_vector2d const* v1, s_vector2d const* v2)
{
	return (
		(v1->x == v2->x) &&
		(v1->y == v2->y));
}



_INLINE()
t_bool	Vector3D_Equals(s_vector3d const* v1, s_vector3d const* v2)
{
	return (
		(v1->x == v2->x) &&
		(v1->y == v2->y) &&
		(v1->z == v2->z));
}


_INLINE()
t_bool	Vector4D_Equals(s_vector4d const* v1, s_vector4d const* v2)
{
	return (
		(v1->x == v2->x) &&
		(v1->y == v2->y) &&
		(v1->z == v2->z) &&
		(v1->t == v2->t));
}


t_bool	Vector_Equals(s_vector const* v1, s_vector const* v2)
{
	t_uint i;

	if CCCERROR((v1 == NULL || v2 == NULL), ERROR_NULLPOINTER, NULL)
		return (FALSE);
	if (v1->dims != v2->dims)
		return (FALSE);
	if (v1->values == v2->values)
		return (TRUE);
	if (v1->values == NULL || v2->values == NULL)
		return (FALSE);
	for (i = 0; i < v1->dims; ++i)
	{
		if (v1->values[i] != v2->values[i])
			return (FALSE);
	}
	return (TRUE);
}
