
#include "libccc/memory.h"
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_FromMemory(T)(T* ptr, t_uint n)
{
	s_list(T)*	result = NULL;
	s_list(T)*	tail = NULL;
	s_list(T)*	elem;

	if CCCERROR((ptr == NULL && n > 0), ERROR_NULLPOINTER, "memory buffer given is NULL")
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		elem = List_Item(T)(ptr[i]);
		if CCCERROR((elem == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			List_Free(T)(result);
			return (NULL);
		}
		if (result == NULL)
			result = elem;
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->prev = tail;
#endif
			tail->next = elem;
		}
		tail = elem;
	}
	return (result);
}

_GENERIC()
T*	List_ToMemory(T)(s_list(T) const* list)
{
	T*	result;
	t_uint	length;
	t_uint	i;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	length = List_Length(T)(list);
	if (length == 0)
		return (NULL); // an empty list yields no memory buffer
	result = (T*)Memory_Allocate(length * sizeof(T));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (list && i < length)
	{
		result[i++] = list->item;
		list = list->next;
	}
	return (result);
}



_GENERIC()
s_list(T)*	List_FromPointerArray(T)(T const* const* ptrarr)
{
	s_list(T)*	result = NULL;
	s_list(T)*	tail = NULL;
	s_list(T)*	elem;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	for (t_uint i = 0; ptrarr[i]; ++i)
	{
		elem = List_Item(T)(*(ptrarr[i]));
		if CCCERROR((elem == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			List_Free(T)(result);
			return (NULL);
		}
		if (result == NULL)
			result = elem;
		else
		{
#if LIBCONFIG_LIST_DOUBLYLINKED
			elem->prev = tail;
#endif
			tail->next = elem;
		}
		tail = elem;
	}
	return (result);
}

_GENERIC()
void**	List_ToPointerArray(T)(s_list(T) const* list)
{
	void**	result;
	t_uint	length;
	t_uint	i;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	length = List_Length(T)(list);
	result = (void**)Memory_Allocate((length + 1) * sizeof(void*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	// NOTE: the pointers stored refer to the items held within the given `list`:
	// the underlying item data is not copied, so these pointers are only valid
	// for as long as the given `list` (and each of its elements) stays alive.
	i = 0;
	while (list && i < length)
	{
		result[i++] = (void*)&(((s_list(T)*)list)->item);
		list = list->next;
	}
	result[i] = NULL;
	return (result);
}
