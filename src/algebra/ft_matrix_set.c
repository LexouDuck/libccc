
inline void	matrix_set(t_matrix *result, t_vector *u, t_vector *v, t_vector *w)
{
	result->u = *u;
	result->v = *v;
	result->w = *w;
	result->t = (t_vector){0, 0, 0};
}
