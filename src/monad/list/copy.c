
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Copy(T)(
	s_list(T)* dest,      t_uint dest_i,
	s_list(T) const* src, t_uint src_i,
	t_uint n)
{
	s_list(T)*	result;
	t_uint dest_length;
	t_uint src_length;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src  == NULL), return (NULL);)
	dest_length = List_Length(T)(dest);
	src_length  = List_Length(T)(src);
	HANDLE_ERROR(INDEX2LARGE, (dest_i >= dest_length),    return (NULL);)
	HANDLE_ERROR(INDEX2LARGE, ( src_i >=  src_length),    return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (dest_i + n > dest_length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, ( src_i + n >  src_length), return (NULL);)
	if (n == 0)
		n = src_length - src_i;
	result = dest;
	while (dest && n--)
	{
		dest->item = src->item;
		dest = dest->next;
		src = src->next;
	}
	return (result);
}
