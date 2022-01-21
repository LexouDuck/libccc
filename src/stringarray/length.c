
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint		StringArray_Length(t_char const* const* strarr)
{
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}



t_size		StringArray_TotalLength(t_char const* const* strarr, t_uint n)
{
	t_size	result;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	result = 0;
	i = 0;
	while (strarr[i] && i < n)
	{
		result += String_Length(strarr[i]);
		++i;
	}
	return (result);
}
