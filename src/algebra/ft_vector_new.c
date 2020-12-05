
t_vector	*vector_new(float x, float y, float z)
{
	t_vector *result;

	if (!(result = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}
