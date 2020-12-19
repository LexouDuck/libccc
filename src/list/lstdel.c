
#include "libft_memory.h"
#include "libft_list.h"



void	List_Remove(s_list* *a_lst, void (*del)(void*, t_size))
{
//	s_list* prev;
	s_list* next;
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	if (*a_lst)
	{
		del((*a_lst)->item, (*a_lst)->item_size);
//		prev = (*a_lst)->prev;
		next = (*a_lst)->next;
		Memory_Free(*a_lst);
		*a_lst = next;
//		if (next)
//			next->prev = prev;
	}
}



void	List_Delete(s_list* *a_lst, void (*del)(void*, t_size))
{
	s_list* lst;
	s_list* next;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	while (lst)
	{
		del(lst->item, lst->item_size);
		next = lst->next;
		Memory_Free(lst);
		lst = next;
	}
	*a_lst = NULL;
}



void	List_Pop(s_list* *a_lst, void (*del)(void*, t_size))
{
	s_list	*lst;
	s_list	*lst_prev;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	lst_prev = NULL;
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


