
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"



char*		String_Replace_Char(char const* str, char const old, char const new)
{
	char*	result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (String_Duplicate(str));
	if (str == NULL)
		return (NULL);
#endif
	if (old == '\0')
		return (NULL);
	i = 0;
	while (str[i])
		++i;
	if (!(result = (char*)Memory_Alloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = (str[i] == old) ? new : str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



char*		String_Replace_Charset(char const* str, char const* old, char const* new)
{
	char*	result;
	t_size	i;
	t_size	j;
	int		c_index;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (String_Duplicate(str));
	if (str == NULL || old == NULL || new == NULL)
		return (NULL);
#endif
	if (String_Length(old) != String_Length(new))
		return (NULL);
	i = 0;
	while (old[i])
	{
		j = i;
		while (old[++j])
			if (old[i] == old[j])
				return (NULL);
		++i;
	}
	if (!(result = (char*)Memory_Alloc(i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if ((c_index = String_Find_CharIndex(old, str[i])) >= 0)
			result[i] = new[c_index];
		else
			result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



char*		String_Replace_String(char const* str, char const* old, char const* new)
{
	char*	result;
	char**	strarr;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (old == new)
		return (String_Duplicate(str));
	if (str == NULL || old == NULL || new == NULL)
		return (NULL);
#endif
	strarr = String_Split_String(str, old);
	result = StringArray_Fold((char const**)strarr, new);
	StringArray_Delete(&strarr);
	return (result);
}



void		String_Replace_Char_InPlace(char* str, char const old, char const new)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return ;
#endif
	if (old == '\0')
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == old)
			str[i] = new;
		++i;
	}
}



void		String_Replace_Charset_InPlace(char* str, char const* old, char const* new)
{
	t_size	i;
	t_size	j;
	int		c_index;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || old == NULL || new == NULL)
		return ;
#endif
	if (String_Length(old) != String_Length(new))
		return ;
	i = 0;
	while (old[i])
	{
		j = i;
		while (old[++j])
			if (old[i] == old[j])
				return ;
		++i;
	}
	i = 0;
	while (str[i])
	{
		if ((c_index = String_Find_CharIndex(old, str[i])) >= 0)
			str[i] = new[c_index];
		++i;
	}
}



void	String_Replace_String_InPlace(char* *a_str, char const* old, char const* new)
{
	char	*tmp;
	tmp = String_Replace_String(*a_str, old, new);
	String_Delete(a_str);
	*a_str = tmp;
}
