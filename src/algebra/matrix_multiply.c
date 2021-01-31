
#include "libccc/math/algebra.h"



s_matrix2d	Matrix2D_Multiply(s_matrix2d const* m1, s_matrix2d const* m2)
{
	s_matrix2d result;
	s_vector2d tmp;

	tmp = m1->u;
	result.u = (s_vector2d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y),
	};
	tmp = m1->v;
	result.v = (s_vector2d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y),
	};
	return (result);
}



s_matrix3d	Matrix3D_Multiply(s_matrix3d const* m1, s_matrix3d const* m2)
{
	s_matrix3d result;
	s_vector3d tmp;

	tmp = m1->u;
	result.u = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	tmp = m1->v;
	result.v = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	tmp = m1->w;
	result.w = (s_vector3d)
	{
		(tmp.x * m2->u.x) + (tmp.y * m2->v.x) + (tmp.z * m2->w.x),
		(tmp.x * m2->u.y) + (tmp.y * m2->v.y) + (tmp.z * m2->w.y),
		(tmp.x * m2->u.z) + (tmp.y * m2->v.z) + (tmp.z * m2->w.z),
	};
	return (result);
}
