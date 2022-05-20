
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Insert(t_ascii const* dest, t_ascii const* src, t_size offset)
{
	t_ascii*	result;
	t_size	len_dst;
	t_size	len_src;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	len_dst = String_Length(dest);
	len_src = String_Length(src);
	result = (t_ascii*)Memory_Allocate(len_dst + len_src + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = String_Sub(*a_dest, 0, index);
	String_Append(&tmp, src);
	String_Append(&tmp, (*a_dest) + index);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
