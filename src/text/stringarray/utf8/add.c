
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Add(t_utf8** dest, t_utf8 const* str)
{
	t_utf8**	result;
	t_uint		length;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER,
		"destination string array given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string to add given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length((t_utf8 const* const*)dest);
	result = (t_utf8**)Memory_Reallocate(dest, (length + 2) * sizeof(t_utf8*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result[length] = StringUTF8_Duplicate(str);
	result[length + 1] = NULL;
	return (result);
}
