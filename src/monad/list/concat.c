
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_list_T*	CONCAT(List_Concat,T_NAME)(s_list_T const* list1, s_list_T const* list2)
{
	s_list_T*	result;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list1 == NULL && list2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (List_Duplicate(list2));)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (List_Duplicate(list1));)
	result = List_Duplicate(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_Append,T_NAME)(s_list_T* list1, s_list_T const* list2)
{
	s_list_T*	result;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list1 == NULL && list2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (List_Duplicate(list2));)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (List_Duplicate(list1));)
	result = List_Duplicate(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Delete(list1);
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_Prepend,T_NAME)(s_list_T const* list1, s_list_T* list2)
{
	s_list_T*	result;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list1 == NULL && list2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (List_Duplicate(list2));)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (List_Duplicate(list1));)
	result = List_Duplicate(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Delete(list2);
	return (result);
}



_GENERIC()
s_list_T*	CONCAT(List_Merge,T_NAME)(s_list_T* list1, s_list_T* list2)
{
	s_list_T*	result;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list1 == NULL && list2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list1 == NULL), return (List_Duplicate(list2));)
	HANDLE_ERROR(NULLPOINTER, (list2 == NULL), return (List_Duplicate(list1));)
	result = List_Duplicate(list1);
	i = result;
	while (i->next)
	{
		i = i->next;
	}
	i->next = List_Duplicate(list2);
#if LIBCONFIG_LIST_DOUBLYLINKED
	i->next->prev = i;
	result->prev = i;
#endif
	List_Delete(list1);
	List_Delete(list2);
	return (result);
}
