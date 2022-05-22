
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list(T)*	List_Concat(T)(s_list(T) const* list1, s_list(T) const* list2)
{
	s_list(T)*	result;
	s_list(T)*	i;

	if CCCERROR((list1 == NULL && list2 == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list2));
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list1));
	result = List_Duplicate(T)(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(T)(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	return (result);
}



_GENERIC()
s_list(T)*	List_Append(T)(s_list(T)* list1, s_list(T) const* list2)
{
	s_list(T)*	result;
	s_list(T)*	i;

	if CCCERROR((list1 == NULL && list2 == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list2));
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list1));
	result = List_Duplicate(T)(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(T)(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Free(T)(list1);
	return (result);
}



_GENERIC()
s_list(T)*	List_Prepend(T)(s_list(T) const* list1, s_list(T)* list2)
{
	s_list(T)*	result;
	s_list(T)*	i;

	if CCCERROR((list1 == NULL && list2 == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list2));
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list1));
	result = List_Duplicate(T)(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(T)(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Free(T)(list2);
	return (result);
}



_GENERIC()
s_list(T)*	List_Merge(T)(s_list(T)* list1, s_list(T)* list2)
{
	s_list(T)*	result;
	s_list(T)*	i;

	if CCCERROR((list1 == NULL && list2 == NULL), ERROR_NULLPOINTER, NULL) return (NULL);
	if CCCERROR((list1 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list2));
	if CCCERROR((list2 == NULL), ERROR_NULLPOINTER, NULL) return (List_Duplicate(T)(list1));
	result = List_Duplicate(T)(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(T)(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Free(T)(list1);
	List_Free(T)(list2);
	return (result);
}
