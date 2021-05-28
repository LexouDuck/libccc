
#include "libccc/math/algebra.h"
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



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

	if (!(result = (s_matrix2d*)Memory_New(sizeof(s_matrix2d))))
		return (NULL);
	result->u = (u ? *u : (s_vector2d){ 0, 0 });
	result->v = (v ? *v : (s_vector2d){ 0, 0 });
	return (result);
}



s_matrix3d*	Matrix3D_New(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w)
{
	s_matrix3d* result;

	if (!(result = (s_matrix3d*)Memory_New(sizeof(s_matrix3d))))
		return (NULL);
	result->u = (u ? *u : (s_vector3d){ 0, 0, 0 });
	result->v = (v ? *v : (s_vector3d){ 0, 0, 0 });
	result->w = (w ? *w : (s_vector3d){ 0, 0, 0 });
	return (result);
}
