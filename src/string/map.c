
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	c_strmap(t_char const* str, t_char (*f)(t_char c))
{
	t_char*	result;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (t_char* )c_memalloc(length + 1)))
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



t_char*	c_strmapi(t_char const* str, t_char (*f)(t_char c, t_size index))
{
	t_char*	result;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (!(result = (t_char* )c_memalloc(length + 1)))
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



t_char*	c_strmap_inplace(t_char* *a_str, t_char (*f)(t_char))
{
	t_char*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL || *a_str == NULL || f == NULL)
		return (NULL);
#endif
	tmp = c_strmap(*a_str, f);
	c_strdel(a_str);
	*a_str = tmp;
	return (tmp);
}
