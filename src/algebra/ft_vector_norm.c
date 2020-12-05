
float		vector_length(t_vector const *vector)
{
	float	tmp;
	float	sum;

	sum = 0;
	tmp = vector->x;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->y;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->z;
	tmp *= tmp;
	sum += tmp;
	return (sum);
}
