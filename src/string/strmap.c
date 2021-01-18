
#include "libccc_memory.h"
#include "libccc_string.h"



char	*c_strmap(char const *str, char (*f)(char))
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)c_memalloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}



char	*c_strmapi(char const *str, char (*f)(t_size, char))
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (char *)c_memalloc(length + 1)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(i, str[i]);
		++i;
	}
	result[i] = '\0';
	return (result);
}



char	*c_strmap_inplace(char **a_str, char (*f)(char))
{
	char	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL || *a_str == NULL || f == NULL)
		return (NULL);
#endif
	tmp = c_strmap(*a_str, f);
	c_strdel(a_str);
	*a_str = tmp;
	return (tmp);
}
