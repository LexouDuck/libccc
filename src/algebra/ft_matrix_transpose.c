
#include "libft_algebra.h"



inline void	matrix_transpose(t_matrix *matrix)
{
	float tmp;

	tmp = matrix->u.y;
	matrix->u.y = matrix->v.x;
	matrix->v.x = tmp;
	tmp = matrix->v.z;
	matrix->v.z = matrix->w.y;
	matrix->w.y = tmp;
	tmp = matrix->u.z;
	matrix->u.z = matrix->w.x;
	matrix->w.x = tmp;
}
