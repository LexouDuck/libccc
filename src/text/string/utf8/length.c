
#include "libccc/text/string/ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_size	StringUTF8_Length(t_utf8 const* str)
{ return (strlen((char const*)str)); }
#else
t_size	StringUTF8_Length(t_utf8 const* str)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	i = 0;
	while (str[i])
	{
		++i;
	}
	return (i);
}
#endif



t_size	StringUTF8_Length_N(t_utf8 const* str, t_size n)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		++i;
	}
	return (i);
}



t_size	StringUTF8_Chars(t_utf8 const* str)
{
	t_size	result;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	result = 0;
	i = 0;
	while (str[i])
	{
		++result;
		i += CharUTF8_Length(str + i);
	}
	return (result);
}



t_size	StringUTF8_Chars_N(t_utf8 const* str, t_size n)
{
	t_size	result;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	result = 0;
	i = 0;
	while (str[i] && result < n)
	{
		++result;
		i += CharUTF8_Length(str + i);
	}
	return (result);
}
