
#include "libccc_memory.h"
#include "libccc_list.h"



s_list*	List_Copy(s_list const* lst)
{
	s_list	*result;
	s_list	*result_lst;
	s_list	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	result = List_New(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = List_New(lst->item, lst->item_size);
//		tmp->prev = result_lst;
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}



s_list*	List_Duplicate(s_list const* lst)
{
	s_list	*result;
	s_list	*result_lst;
	s_list	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	result = List_New(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = List_New(lst->item, lst->item_size);
		tmp->item = Memory_Duplicate(lst->item, lst->item_size);
//		tmp->prev = result_lst;
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}
