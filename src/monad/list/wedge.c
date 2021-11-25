
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Wedge,T_NAME)(s_list_T* dest, s_list_T const* src, t_uint index)
{
	s_list_T*	before;
	s_list_T*	after;
	s_list_T*	elem;
	s_list_T*	new;

	//HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	new = CONCAT(List_Duplicate,T_NAME)(src);
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
			", index given ("SF_UINT") is beyond the end of the destination list (length: "SF_UINT")",
			index, CONCAT(List_Length,T_NAME)(dest))
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
