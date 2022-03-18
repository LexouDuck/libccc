
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Wedge(T)(s_list(T)* dest, s_list(T) const* src, t_uint index)
{
	s_list(T)*	before;
	s_list(T)*	after;
	s_list(T)*	elem;
	s_list(T)*	new;

	//HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	new = List_Duplicate(T)(src);
	HANDLE_ERROR(ALLOCFAILURE, (new == NULL), return (dest);)
	if (dest == NULL || index == 0)
	{
		elem = new;
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
			new->prev = elem;
		}
#endif
		return (new);
	}
	elem = dest;
	for (t_uint i = 0; i < index; ++i)
	{
		HANDLE_ERROR_SF(INDEX2LARGE, (elem == NULL), return (NULL);,
			"index given ("SF_UINT") is beyond the end of the destination list (length: "SF_UINT")",
			index, List_Length(T)(dest))
		before = elem;
		elem = elem->next;
	}
	after = elem;
#if LIBCONFIG_LIST_DOUBLYLINKED
	new->prev = before;
	elem = new;
	while (elem->next)
	{
		elem = elem->next;
	}
	after->prev = elem;
#endif
	before->next = new;
	elem = new;
	while (elem->next)
	{
		elem = elem->next;
	}
	elem->next = after;
	return (dest);
}
