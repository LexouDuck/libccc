
void		matrix_inverse(t_matrix *matrix)
{
	t_vector	u;
	t_vector	v;
	t_vector	w;
	double		determinant;

	vector_set(&u, matrix->u.x, matrix->u.y, matrix->u.z);
	vector_set(&v, matrix->v.x, matrix->v.y, matrix->v.z);
	vector_set(&w, matrix->w.x, matrix->w.y, matrix->w.z);
	determinant = u.x * (v.y * w.z - v.z * w.y) -
		u.y * (v.x * w.z - v.z * w.x) +
		u.z * (v.x * w.y - v.y * w.x);
	determinant = 1 / determinant;
	matrix->u.x = (v.y * w.z - w.y * v.z) * determinant;
	matrix->u.y = (w.y * u.z - u.y * w.z) * determinant;
	matrix->u.z = (u.y * v.z - v.y * u.z) * determinant;
	matrix->v.x = (v.z * w.x - w.z * v.x) * determinant;
	matrix->v.y = (w.z * u.x - u.z * w.x) * determinant;
	matrix->v.z = (u.z * v.x - v.z * u.x) * determinant;
	matrix->w.x = (v.x * w.y - w.x * v.y) * determinant;
	matrix->w.y = (w.x * u.y - u.x * w.y) * determinant;
	matrix->w.z = (u.x * v.y - v.x * u.y) * determinant;
}
