
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Wedge(T)(s_list(T)* dest, s_list(T) const* src, t_uint index)
{
	s_list(T)*	before;
	s_list(T)*	after;
	s_list(T)*	elem;
	s_list(T)*	newitem;

//	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination list given is NULL")
//		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "list to insert given is NULL")
		return (NULL);
	newitem = List_Duplicate(T)(src);
	if CCCERROR((newitem == NULL), ERROR_ALLOCFAILURE, NULL)
		return (dest);
	if (dest == NULL || index == 0)
	{
		elem = newitem;
		while (elem->next)
		{
			elem = elem->next;
		}
		elem->next = dest;
#if LIBCONFIG_LIST_DOUBLYLINKED
		if (dest)
		{
			elem = dest;
			while (elem->next)
			{
				elem = elem->next;
			}
			newitem->prev = elem;
		}
#endif
		return (newitem);
	}
	elem = dest;
	for (t_uint i = 0; i < index; ++i)
	{
		if CCCERROR((elem == NULL), ERROR_INDEX2LARGE, 
			"index given ("SF_UINT") is beyond the end of the destination list (length: "SF_UINT")",
			index, List_Length(T)(dest))
			return (NULL);
		before = elem;
		elem = elem->next;
	}
	after = elem;
#if LIBCONFIG_LIST_DOUBLYLINKED
	newitem->prev = before;
	elem = newitem;
	while (elem->next)
	{
		elem = elem->next;
	}
	after->prev = elem;
#endif
	before->next = newitem;
	elem = newitem;
	while (elem->next)
	{
		elem = elem->next;
	}
	elem->next = after;
	return (dest);
}
