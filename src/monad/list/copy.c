
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

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, NULL)	return (NULL);
	if CCCERROR((src  == NULL), ERROR_NULLPOINTER, NULL)	return (NULL);
	dest_length = List_Length(T)(dest);
	src_length  = List_Length(T)(src);
	if CCCERROR((dest_i >= dest_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i >=  src_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR((dest_i + n > dest_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i + n >  src_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
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
