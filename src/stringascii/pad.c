
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		String_Pad(t_ascii const* str, t_ascii c, t_size size)
{
	t_ascii*	result;
	t_size	offset;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	result = (t_ascii*)Memory_Allocate(size + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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



t_ascii*		String_Pad_L(t_ascii const* str, t_ascii c, t_size size)
{
	t_ascii*	result;
	t_size	offset;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	result = (t_ascii*)Memory_Allocate(size + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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



t_ascii*		String_Pad_R(t_ascii const* str, t_ascii c, t_size size)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = String_Length(str);
	if (size == length)
		return (String_Duplicate(str));
	result = (t_ascii*)Memory_Allocate(size + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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
