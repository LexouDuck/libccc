
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		String_Replace_Char(t_ascii const* str, t_ascii const char_old, t_ascii const char_new)
{
	t_ascii*	result;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	if (char_old == char_new)
		return (String_Duplicate(str));
	if (char_old == '\0')
		return (NULL);
	i = 0;
	while (str[i])
		++i;
	result = (t_ascii*)Memory_Allocate(i + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (str[i])
	{
		result[i] = (str[i] == char_old) ? char_new : str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_ascii*		String_Replace_Charset(t_ascii const* str, t_ascii const* cset_old, t_ascii const* cset_new)
{
	t_ascii*	result;
	t_size	i;
	t_size	j;
	int		c_index;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (cset_old == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (cset_new == NULL), return (NULL);)
	if (cset_old == cset_new)
		return (String_Duplicate(str));
	if (String_Length(cset_old) != String_Length(cset_new))
		return (NULL);
	i = 0;
	while (cset_old[i])
	{
		j = i;
		while (cset_old[++j])
			if (cset_old[i] == cset_old[j])
				return (NULL);
		++i;
	}
	result = (t_ascii*)Memory_Allocate(i + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (str[i])
	{
		if ((c_index = String_IndexOf_Char(cset_old, str[i])) >= 0)
			result[i] = cset_new[c_index];
		else
			result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_ascii*		String_Replace_String(t_ascii const* str, t_ascii const* str_old, t_ascii const* str_new)
{
	t_ascii*		result;
	t_ascii**	strarr;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (str_old == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (str_new == NULL), return (NULL);)
	if (str_old == str_new)
		return (String_Duplicate(str));
	strarr = String_Split_String(str, str_old);
	result = String_Join((t_ascii const**)strarr, str_new);
	StringArray_Delete(&strarr);
	return (result);
}



void		String_Replace_Char_InPlace(t_ascii* str, t_ascii const char_old, t_ascii const char_new)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	if (char_old == '\0')
		return;
	i = 0;
	while (str[i])
	{
		if (str[i] == char_old)
			str[i] = char_new;
		++i;
	}
}



void		String_Replace_Charset_InPlace(t_ascii* str, t_ascii const* cset_old, t_ascii const* cset_new)
{
	t_size	i;
	t_size	j;
	int		c_index;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (cset_old == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (cset_new == NULL), return;)
	if (String_Length(cset_old) != String_Length(cset_new))
		return;
	i = 0;
	while (cset_old[i])
	{
		j = i;
		while (cset_old[++j])
			if (cset_old[i] == cset_old[j])
				return;
		++i;
	}
	i = 0;
	while (str[i])
	{
		if ((c_index = String_IndexOf_Char(cset_old, str[i])) >= 0)
			str[i] = cset_new[c_index];
		++i;
	}
}



void	String_Replace_String_InPlace(t_ascii** a_str, t_ascii const* str_old, t_ascii const* str_new)
{
	t_ascii*	tmp;
	tmp = String_Replace_String(*a_str, str_old, str_new);
	String_Delete(a_str);
	*a_str = tmp;
}
