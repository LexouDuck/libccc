
#include "libccc/memory.h"
#include "libccc/monad/list.h"

/*

s_list_T*	List_Remove(s_list_T* list, t_uint index)
{
//	s_list_T* prev;
	s_list_T* next;
	s_list_T* i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return ;
#endif
	i = list;
	del(lst->item, lst->item_size);
//	prev = lst->prev;
	next = lst->next;
	Memory_Free(lst);
	*a_lst = next;
//	if (next)
//		next->prev = prev;
	return (list);
}



s_list_T*	List_RemoveAll(s_list_T* list, T target)
{
//	s_list_T* prev;
	s_list_T* next;
	s_list_T* i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (list == NULL)
		return ;
#endif
	i = list;
	del(lst->item, lst->item_size);
//	prev = lst->prev;
	next = lst->next;
	Memory_Free(lst);
	*a_lst = next;
//	if (next)
//		next->prev = prev;
	return (list);
}
*/