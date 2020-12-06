
#include "libft_memory.h"
#include "libft_string.h"



char	*ft_strnew(t_size n)
{
	char	*result;
	t_size	i;

	if (!(result = (char *)ft_memalloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = '\0';
		++i;
	}
	result[n] = '\0';
	return (result);
}



char	*ft_strcnew(t_size n, char c)
{
	char	*result;
	t_size	i;

	if (!(result = (char *)ft_memalloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		++i;
	}
	result[n] = '\0';
	return (result);
}
