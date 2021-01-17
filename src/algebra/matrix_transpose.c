
#include "libccc_algebra.h"



s_matrix2d	Matrix2D_Transpose(s_matrix2d const* matrix)
{
	s_matrix2d result;

	result.u.x = matrix->u.x;
	result.u.y = matrix->v.x;

	result.v.x = matrix->u.y;
	result.v.y = matrix->v.y;
	return (result);
}



s_matrix3d	Matrix3D_Transpose(s_matrix3d const* matrix)
{
	s_matrix3d result;

	result.u.x = matrix->u.x;
	result.u.y = matrix->v.x;
	result.u.z = matrix->w.x;

	result.v.x = matrix->u.y;
	result.v.y = matrix->v.y;
	result.v.z = matrix->w.y;

	result.w.x = matrix->u.z;
	result.w.y = matrix->v.z;
	result.w.z = matrix->w.z;
	return (result);
}
