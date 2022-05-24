
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Insert(t_ascii const* dest, t_ascii const* src, t_size offset)
{
	t_ascii*	result;
	t_size	len_dst;
	t_size	len_src;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (NULL);
	len_dst = String_Length(dest);
	len_src = String_Length(src);
	result = (t_ascii*)Memory_Allocate(len_dst + len_src + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = (t_size)-1;
	while (++i < offset)
		result[i] = dest[i];
	--i;
	while (++i < len_src)
		result[i] = src[i - offset];
	--i;
	while (++i < len_dst)
		result[i] = dest[i - len_src];
	result[i] = '\0';
	return (result);
}



t_ascii*	String_Insert_InPlace(t_ascii** a_dest, t_ascii const* src, t_u32 index)
{
	t_ascii*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (NULL);
	tmp = String_Sub(*a_dest, 0, index);
	String_Append(&tmp, src);
	String_Append(&tmp, (*a_dest) + index);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
