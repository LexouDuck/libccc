
#include "libccc/memory.h"
#include "libccc/array/list.h"



void	List_Remove(s_list* *a_lst, void (*del)(void*, t_size))
{
//	s_list* prev;
	s_list* next;
	s_list* lst;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	del(lst->item, lst->item_size);
//	prev = lst->prev;
	next = lst->next;
	Memory_Free(lst);
	*a_lst = next;
//	if (next)
//		next->prev = prev;
}



void	List_Delete(s_list* *a_lst, void (*del)(void*, t_size))
{
//	s_list* prev;
	s_list* next;
	s_list* lst;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	while (lst)
	{
		del(lst->item, lst->item_size);
//		prev = lst->prev;
		next = lst->next;
		Memory_Free(lst);
		lst = next;
//		if (next)
//			next->prev = prev;
	}
	*a_lst = NULL;
}



void	List_Pop(s_list* *a_lst, void (*del)(void*, t_size))
{
	s_list* lst;
	s_list* lst_prev;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst_prev = NULL;
	lst = *a_lst;
	while (lst)
	{
		if (lst->next == NULL)
		{
			del((lst)->item, (lst)->item_size);
			Memory_Free(lst);
			if (lst_prev)
				lst_prev->next = NULL;
			return ;
		}
		lst_prev = lst;
		lst = lst->next;
	}
}


