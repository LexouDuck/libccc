
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	Matrix2D_Equals(s_matrix2d const* m1, s_matrix2d const* m2)
{
	return (
		(m1->u.x == m2->u.x) && (m1->u.y == m2->u.y) &&
		(m1->v.x == m2->v.x) && (m1->v.y == m2->v.y));
}



_INLINE()
t_bool	Matrix3D_Equals(s_matrix3d const* m1, s_matrix3d const* m2)
{
	return (
		(m1->u.x == m2->u.x) && (m1->u.y == m2->u.y) && (m1->u.z == m2->u.z) &&
		(m1->v.x == m2->v.x) && (m1->v.y == m2->v.y) && (m1->v.z == m2->v.z) &&
		(m1->w.x == m2->w.x) && (m1->w.y == m2->w.y) && (m1->w.z == m2->w.z));
}


_INLINE()
t_bool	Matrix4D_Equals(s_matrix4d const* m1, s_matrix4d const* m2)
{
	return (
		(m1->u.x == m2->u.x) && (m1->u.y == m2->u.y) && (m1->u.z == m2->u.z) && (m1->u.t == m2->u.t) &&
		(m1->v.x == m2->v.x) && (m1->v.y == m2->v.y) && (m1->v.z == m2->v.z) && (m1->v.t == m2->v.t) &&
		(m1->w.x == m2->w.x) && (m1->w.y == m2->w.y) && (m1->w.z == m2->w.z) && (m1->w.t == m2->w.t) &&
		(m1->t.x == m2->t.x) && (m1->t.y == m2->t.y) && (m1->t.z == m2->t.z) && (m1->t.t == m2->t.t));
}


t_bool	Matrix_Equals(s_matrix const* m1, s_matrix const* m2)
{
	t_uint i;
	t_uint length;

	if CCCERROR((m1 == NULL || m2 == NULL), ERROR_NULLPOINTER, NULL)
		return (FALSE);
	if (m1->rows != m2->rows || m1->cols != m2->cols)
		return (FALSE);
	if (m1->values == m2->values)
		return (TRUE);
	if (m1->values == NULL || m2->values == NULL)
		return (FALSE);
	length = m1->rows * m1->cols;
	for (i = 0; i < length; ++i)
	{
		if (m1->values[i] != m2->values[i])
			return (FALSE);
	}
	return (TRUE);
}
