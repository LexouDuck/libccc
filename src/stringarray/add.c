
#include "libccc/memory.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Add(t_char** dest, t_char const* str)
{
	t_char**	result;
	t_uint		length;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER,
		"destination string array given is NULL")
		return (NULL);
	if CCCERROR((str  == NULL), ERROR_NULLPOINTER,
		"string to add given is NULL")
		return (NULL);
	length = (StringArray_Length((t_char const**)dest));
	result = (t_char**)Memory_Reallocate(dest, (length + 1) * sizeof(t_char*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result[length] = String_Duplicate(str);
	return (result);
}
