
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*		String_Pad(t_char const* str, t_char c, t_size size)
{
	t_char*	result;
	t_size	offset;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	if (!(result = (t_char*)Memory_Alloc(size + 1)))
		return (NULL);
	result[size] = '\0';
	i = 0;
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	i = 0;
	if (size < length)
	{
		offset = (length - size) / 2;
		while (offset + i < length && i < size)
		{
			result[i] = str[offset + i];
			++i;
		}
	}
	else
	{
		offset = (size - length) / 2;
		while (i < length && offset + i < size)
		{
			result[offset + i] = str[i];
			++i;
		}
	}
	return (result);
}



t_char*		String_Pad_L(t_char const* str, t_char c, t_size size)
{
	t_char*	result;
	t_size	offset;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	if (!(result = (t_char*)Memory_Alloc(size + 1)))
		return (NULL);
	result[size] = '\0';
	if (size < length)
	{
		i = size;
		while (i--)
		{
			--length;
			result[i] = str[length];
		}
		return (result);
	}
	offset = size - length;
	i = 0;
	while (i < offset)
	{
		result[i] = c;
		++i;
	}
	while (i < size)
	{
		length = (i - offset);
		if (str[length] == '\0')
			break;
		result[i] = str[length];
		++i;
	}
	return (result);
}



t_char*		String_Pad_R(t_char const* str, t_char c, t_size size)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	if (!(result = (t_char*)Memory_Alloc(size + 1)))
		return (NULL);
	result[size] = '\0';
	i = 0;
	while (i < size && str[i])
	{
		result[i] = str[i];
		++i;
	}
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	return (result);
}
