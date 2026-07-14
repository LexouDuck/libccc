
#include "libccc/text/format.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8* const*	StringArrayUTF8_Find(t_utf8* const* strarr, t_utf8 const* str)
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	for (i = 0; i < length; ++i)
	{
		if (StringUTF8_Equals(strarr[i], str))
			return (&(strarr[i]));
	}
	if CCCERROR(TRUE, ERROR_NOTFOUND,
		"no string matching \"%s\" found in string array of length " SF_UINT, str, length)
		return (NULL);
	return (NULL);
}



t_utf8* const*	StringArrayUTF8_Find_F(t_utf8* const* strarr, t_bool (*match)(t_utf8 const* str))
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	for (i = 0; i < length; ++i)
	{
		if (match(strarr[i]))
			return (&(strarr[i]));
	}
	if CCCERROR(TRUE, ERROR_NOTFOUND,
		"no matching string found in string array of length " SF_UINT, length)
		return (NULL);
	return (NULL);
}



t_sint	StringArrayUTF8_IndexOf(t_utf8 const* const* strarr, t_utf8 const* str)
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (ERROR);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		if (StringUTF8_Equals(strarr[i], str))
			return ((t_sint)i);
	}
	if CCCERROR(TRUE, ERROR_NOTFOUND,
		"no string matching \"%s\" found in string array of length " SF_UINT, str, length)
		return (ERROR);
	return (ERROR);
}



t_sint	StringArrayUTF8_IndexOf_F(t_utf8 const* const* strarr, t_bool (*match)(t_utf8 const* str))
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (ERROR);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (ERROR);
	length = StringArrayUTF8_Length(strarr);
	for (i = 0; i < length; ++i)
	{
		if (match(strarr[i]))
			return ((t_sint)i);
	}
	if CCCERROR(TRUE, ERROR_NOTFOUND,
		"no matching string found in string array of length " SF_UINT, length)
		return (ERROR);
	return (ERROR);
}
