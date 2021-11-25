
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Copy,T_NAME)(
	s_list_T* dest,      t_uint dest_i,
	s_list_T const* src, t_uint src_i,
	t_uint n)
{
	s_list_T*	result;
	t_uint dest_length;
	t_uint src_length;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src  == NULL), return (NULL);)
	dest_length = CONCAT(List_Length,T_NAME)(dest);
	src_length  = CONCAT(List_Length,T_NAME)(src);
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
