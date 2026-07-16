
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



s_matrix2d	Matrix2D(s_vector2d const* u, s_vector2d const* v)
{
	return ((s_matrix2d)
	{
		.u = (u ? *u : (s_vector2d){ 0, 0 }),
		.v = (v ? *v : (s_vector2d){ 0, 0 }),
	});
}



s_matrix3d	Matrix3D(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w)
{
	return ((s_matrix3d)
	{
		.u = (u ? *u : (s_vector3d){ 0, 0, 0 }),
		.v = (v ? *v : (s_vector3d){ 0, 0, 0 }),
		.w = (w ? *w : (s_vector3d){ 0, 0, 0 }),
	});
}



s_matrix2d*	Matrix2D_New(s_vector2d const* u, s_vector2d const* v)
{
	s_matrix2d* result;

	result = (s_matrix2d*)Memory_New(sizeof(s_matrix2d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->u = (u ? *u : (s_vector2d){ 0, 0 });
	result->v = (v ? *v : (s_vector2d){ 0, 0 });
	return (result);
}



s_matrix3d*	Matrix3D_New(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w)
{
	s_matrix3d* result;

	result = (s_matrix3d*)Memory_New(sizeof(s_matrix3d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->u = (u ? *u : (s_vector3d){ 0, 0, 0 });
	result->v = (v ? *v : (s_vector3d){ 0, 0, 0 });
	result->w = (w ? *w : (s_vector3d){ 0, 0, 0 });
	return (result);
}


s_matrix4d	Matrix4D(s_vector4d const* u, s_vector4d const* v, s_vector4d const* w, s_vector4d const* t)
{
	return ((s_matrix4d)
	{
		.u = (u ? *u : (s_vector4d){ 0, 0, 0, 0 }),
		.v = (v ? *v : (s_vector4d){ 0, 0, 0, 0 }),
		.w = (w ? *w : (s_vector4d){ 0, 0, 0, 0 }),
		.t = (t ? *t : (s_vector4d){ 0, 0, 0, 0 }),
	});
}



s_matrix4d*	Matrix4D_New(s_vector4d const* u, s_vector4d const* v, s_vector4d const* w, s_vector4d const* t)
{
	s_matrix4d* result;

	result = (s_matrix4d*)Memory_New(sizeof(s_matrix4d));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->u = (u ? *u : (s_vector4d){ 0, 0, 0, 0 });
	result->v = (v ? *v : (s_vector4d){ 0, 0, 0, 0 });
	result->w = (w ? *w : (s_vector4d){ 0, 0, 0, 0 });
	result->t = (t ? *t : (s_vector4d){ 0, 0, 0, 0 });
	return (result);
}


s_matrix	Matrix(t_uint rows, t_uint cols, t_float const* values)
{
	s_matrix result = MATRIX_NULL;

	if (rows == 0 || cols == 0)
		return (result);
	result.values = (t_float*)Memory_New(rows * cols * sizeof(t_float));
	if CCCERROR((result.values == NULL), ERROR_ALLOCFAILURE, NULL)
		return (MATRIX_NULL);
	result.rows = rows;
	result.cols = cols;
	if (values != NULL)
		Memory_Copy(result.values, values, rows * cols * sizeof(t_float));
	return (result);
}



s_matrix*	Matrix_New(t_uint rows, t_uint cols, t_float const* values)
{
	s_matrix* result;

	result = (s_matrix*)Memory_New(sizeof(s_matrix));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	*result = Matrix(rows, cols, values);
	if CCCERROR((rows != 0 && cols != 0 && result->values == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Delete((void**)&result);
		return (NULL);
	}
	return (result);
}
