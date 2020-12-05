
void		vector_transform(t_vector *vector, t_matrix *matrix)
{
	float		x;
	float		y;
	float		z;
	t_vector	*tmp;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	tmp = &matrix->t;
	if (tmp->x || tmp->y || tmp->z)
		vector_set(vector, tmp->x, tmp->y, tmp->z);
	else
		vector_set(vector, 0, 0, 0);
	tmp = &matrix->u;
	vector->x += (x * tmp->x);
	vector->y += (x * tmp->y);
	vector->z += (x * tmp->z);
	tmp = &matrix->v;
	vector->x += (y * tmp->x);
	vector->y += (y * tmp->y);
	vector->z += (y * tmp->z);
	tmp = &matrix->w;
	vector->x += (z * tmp->x);
	vector->y += (z * tmp->y);
	vector->z += (z * tmp->z);
}
