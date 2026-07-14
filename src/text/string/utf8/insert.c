
#include "libccc/memory.h"
#include "libccc/text/format.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Insert(t_utf8 const* dest, t_utf8 const* src, t_size index)
{
	t_utf8*	result;
	t_size	len_dst;
	t_size	len_src;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (NULL);
	len_dst = StringUTF8_Length(dest);
	len_src = StringUTF8_Length(src);
	if CCCERROR((index > len_dst), ERROR_INDEX2LARGE,
		"should be " SF_SIZE " or less, but got " SF_SIZE, len_dst, index)
		return (NULL);
	result = (t_utf8*)Memory_Allocate(len_dst + len_src + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < index; ++i)
	{
		result[i] = dest[i];
	}
	for (i = 0; i < len_src; ++i)
	{
		result[index + i] = src[i];
	}
	for (i = index; i < len_dst; ++i)
	{
		result[len_src + i] = dest[i];
	}
	result[len_dst + len_src] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Insert_InPlace(t_utf8** a_dest, t_utf8 const* src, t_u32 index)
{
	t_utf8*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (NULL);
	tmp = StringUTF8_Insert(*a_dest, src, index);
	StringUTF8_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
