
#include "libccc_memory.h"



void	*c_memnew(t_size size)
{
	t_u8	*result;
	t_size	i;

	if (!(result = (t_u8 *)c_memalloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		++i;
	}
	return ((void *)result);
}



void	*c_memcnew(t_size size, char c)
{
	t_u8	*result;
	t_size	i;

	if (!(result = (t_u8 *)c_memalloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	return ((void *)result);
}
