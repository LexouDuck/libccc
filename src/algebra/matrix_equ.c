
#include "libccc_algebra.h"



inline t_bool	Matrix2D_Equals(s_matrix2d const* m1, s_matrix2d const* m2)
{
	return (
		(m1->u.x == m2->u.x) && (m1->u.y == m2->u.y) &&
		(m1->v.x == m2->v.x) && (m1->v.y == m2->v.y));
}



inline t_bool	Matrix3D_Equals(s_matrix3d const* m1, s_matrix3d const* m2)
{
	return (
		(m1->u.x == m2->u.x) && (m1->u.y == m2->u.y) && (m1->u.z == m2->u.z) &&
		(m1->v.x == m2->v.x) && (m1->v.y == m2->v.y) && (m1->v.z == m2->v.z) &&
		(m1->w.x == m2->w.x) && (m1->w.y == m2->w.y) && (m1->w.z == m2->w.z));
}
