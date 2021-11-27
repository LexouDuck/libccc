
#include "libccc/memory.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Add(t_char** dest, t_char const* str)
{
	t_char**	result;
	t_uint		length;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (str  == NULL), return (NULL);)
	length = (StringArray_Length((t_char const**)dest));
	result = (t_char**)Memory_Reallocate(dest, (length + 1) * sizeof(t_char*));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	result[length] = String_Duplicate(str);
	return (result);
}
