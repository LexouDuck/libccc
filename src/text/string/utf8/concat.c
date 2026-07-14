
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Concat(t_utf8 const* str1, t_utf8 const* str2)
{
	t_utf8*	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, "left-hand-side string given is NULL")
		return (NULL);
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, "right-hand-side string given is NULL")
		return (NULL);
	length1 = StringUTF8_Length(str1);
	length2 = StringUTF8_Length(str2);
	result = (t_utf8*)Memory_Allocate(length1 + length2 + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < length1; ++i)
	{
		result[i] = str1[i];
	}
	for (i = 0; i < length2; ++i)
	{
		result[length1 + i] = str2[i];
	}
	result[length1 + length2] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Append(t_utf8** a_dest, t_utf8 const* src)
{
	t_utf8*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (NULL);
	tmp = StringUTF8_Concat(*a_dest, src);
	StringUTF8_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_utf8*	StringUTF8_Prepend(t_utf8 const* src, t_utf8** a_dest)
{
	t_utf8*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to prepend given is NULL")
		return (NULL);
	tmp = StringUTF8_Concat(src, *a_dest);
	StringUTF8_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_utf8*	StringUTF8_Merge(t_utf8** a_str1, t_utf8** a_str2)
{
	t_utf8*	result;

	if CCCERROR((a_str1 == NULL), ERROR_NULLPOINTER, "left-hand-side string given is NULL")
		return (NULL);
	if CCCERROR((a_str2 == NULL), ERROR_NULLPOINTER, "right-hand-side string given is NULL")
		return (NULL);
	result = StringUTF8_Concat(*a_str1, *a_str2);
	StringUTF8_Delete(a_str1);
	StringUTF8_Delete(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}
