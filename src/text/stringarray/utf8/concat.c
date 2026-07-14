
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Concat(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2)
{
	t_utf8**	result;
	t_uint	length1;
	t_uint	length2;
	t_uint	i;

	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side string array given is NULL")
		return (NULL);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side string array given is NULL")
		return (NULL);
	length1 = StringArrayUTF8_Length(strarr1);
	length2 = StringArrayUTF8_Length(strarr2);
	result = StringArrayUTF8_New(length1 + length2);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = StringUTF8_Duplicate(strarr1[i]);
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = StringUTF8_Duplicate(strarr2[i]);
		++i;
	}
	result[length1 + length2] = NULL;
	return (result);
}



t_utf8**	StringArrayUTF8_Append(t_utf8** *a_dest, t_utf8 const* const* src)
{
	t_utf8**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string array address is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to append given is NULL")
		return (NULL);
	tmp = StringArrayUTF8_Concat((t_utf8 const* const*)*a_dest, src);
	StringArrayUTF8_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_utf8**	StringArrayUTF8_Prepend(t_utf8 const* const* src, t_utf8** *a_dest)
{
	t_utf8**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string array address is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to prepend given is NULL")
		return (NULL);
	tmp = StringArrayUTF8_Concat(src, (t_utf8 const* const*)*a_dest);
	StringArrayUTF8_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_utf8**	StringArrayUTF8_Merge(t_utf8** *a_strarr1, t_utf8** *a_strarr2)
{
	t_utf8**	result;

	if CCCERROR((a_strarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side string array given is NULL")
		return (NULL);
	if CCCERROR((a_strarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side string array given is NULL")
		return (NULL);
	result = StringArrayUTF8_Concat((t_utf8 const* const*)*a_strarr1, (t_utf8 const* const*)*a_strarr2);
	StringArrayUTF8_Delete(a_strarr1);
	StringArrayUTF8_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}
