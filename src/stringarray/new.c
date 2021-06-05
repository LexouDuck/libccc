
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_char**	StringArray_New(t_uint length)
{
	t_char**	result;

	result = (t_char**)Memory_New(sizeof(t_char*) * (length + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	return (result);
}



t_char**	StringArray_New_C(t_uint y, t_size x, const t_char c)
{
	t_char**	result;
	t_uint	i;

	result = StringArray_New(y);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < y)
	{
		result[i] = String_New(x);
		HANDLE_ERROR(ALLOCFAILURE, (result[i] == NULL),
		{
			result[i] = NULL;
			StringArray_Delete(&result);
			return (NULL);
		})
		Memory_Set(result[i], c, x);
		result[i][x] = '\0';
		++i;
	}
	result[y] = NULL;
	return (result);
}
