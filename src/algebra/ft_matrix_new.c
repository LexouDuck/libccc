
t_matrix	*matrix_new(t_vector *u, t_vector *v, t_vector *w, t_vector *t)
{
	t_matrix	*result;

	if (!(result = (t_matrix *)malloc(sizeof(t_matrix))))
		return (NULL);
	result->u = (u ? *u : (t_vector){0, 0, 0});
	result->v = (v ? *v : (t_vector){0, 0, 0});
	result->w = (w ? *w : (t_vector){0, 0, 0});
	result->t = (t ? *t : (t_vector){0, 0, 0});
	return (result);
}
