
char		*vector_tostr(t_vector *vector, int i)
{
	t_uple	x;
	t_uple	y;
	t_uple	z;
	char	*result;

	x.elements = ft_ftoa(vector->x, i);
	y.elements = ft_ftoa(vector->y, i);
	z.elements = ft_ftoa(vector->z, i);
	x.length = ft_strlen(x.elements);
	y.length = ft_strlen(y.elements);
	z.length = ft_strlen(z.elements);
	if (!(result = (char *)malloc(x.length + y.length + z.length + 7)))
		return (NULL);
	i = 0;
	result[i++] = '(';
	if (ft_memcpy(result + i, x.elements, x.length) && (i += x.length + 2))
		free(x.elements);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, y.elements, y.length) && (i += y.length + 2))
		free(y.elements);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, z.elements, z.length) && (i += z.length + 2))
		free(z.elements);
	ft_memcpy(result + i - 2, ")\0", 2);
	return (result);
}
