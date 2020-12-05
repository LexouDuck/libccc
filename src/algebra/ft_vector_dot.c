
float		vector_scalar(t_vector *v1, t_vector *v2)
{
	float	result;

	result = 0;
	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	result += (v1->z * v2->z);
	return (result);
}
