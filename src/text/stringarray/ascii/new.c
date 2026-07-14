
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_char**	StringArrayASCII_New(t_uint length)
{
	t_char**	result;

	result = (t_char**)Memory_New(sizeof(t_char*) * (length + 1));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	return (result);
}



t_char**	StringArrayASCII_New_C(t_uint y, t_size x, const t_char c)
{
	t_char**	result;
	t_uint	i;

	result = StringArrayASCII_New(y);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < y)
	{
		result[i] = StringASCII_New(x);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			result[i] = NULL;
			StringArrayASCII_Delete(&result);
			return (NULL);
		}
		Memory_Set(result[i], c, x);
		result[i][x] = '\0';
		++i;
	}
	result[y] = NULL;
	return (result);
}
