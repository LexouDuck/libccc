
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_float	Matrix2D_Determinant(s_matrix2d const* matrix)
{
	return (
		matrix->u.x * matrix->v.y -
		matrix->u.y * matrix->v.x);
}



_INLINE()
t_float	Matrix3D_Determinant(s_matrix3d const* matrix)
{
	return (
		matrix->u.x * (matrix->v.y * matrix->w.z - matrix->v.z * matrix->w.y) -
		matrix->u.y * (matrix->v.x * matrix->w.z - matrix->v.z * matrix->w.x) +
		matrix->u.z * (matrix->v.x * matrix->w.y - matrix->v.y * matrix->w.x));
}
