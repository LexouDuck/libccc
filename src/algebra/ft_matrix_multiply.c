
#include "libft_algebra.h"



void		matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	t_vector	*vector;

	vector = &m1->u;
	vector_set(&m1->u,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
	vector = &m1->v;
	vector_set(&m1->v,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
	vector = &m1->w;
	vector_set(&m1->w,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
}
