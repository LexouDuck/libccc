
void		vector_normalize(t_vector *vector)
{
	float		length;

	length = vector_length(vector);
	if (length > 0)
	{
		length = 1 / sqrt(length);
		vector->x *= length;
		vector->y *= length;
		vector->z *= length;
	}
}
