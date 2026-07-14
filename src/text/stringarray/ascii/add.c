
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Add(t_char** dest, t_char const* str)
{
	t_char**	result;
	t_uint		length;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER,
		"destination string array given is NULL")
		return (NULL);
	if CCCERROR((str  == NULL), ERROR_NULLPOINTER,
		"string to add given is NULL")
		return (NULL);
	length = (StringArrayASCII_Length((t_char const**)dest));
	result = (t_char**)Memory_Reallocate(dest, (length + 2) * sizeof(t_char*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result[length] = StringASCII_Duplicate(str);
	result[length + 1] = NULL;
	return (result);
}
