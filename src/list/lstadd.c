
#include "libft_list.h"



void	List_Prepend(s_list* *a_lst, s_list* elem)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return;
#endif
	if (*a_lst == NULL)
	{
		*a_lst = elem;
		return;
	}
//	elem->prev = NULL;
	elem->next = *a_lst;
	*a_lst = elem;
}



void	List_Append(s_list* *a_lst, s_list* elem)
{
	s_list*	lst;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return;
#endif
	if (*a_lst == NULL)
	{
		*a_lst = elem;
		return;
	}
	lst = *a_lst;
	while (lst->next)
	{
		lst = lst->next;
	}
//	elem->prev = lst;
	lst->next = elem;
}



void	List_Insert(s_list* *a_lst, s_list* elem, t_u32 index)
{
	s_list*	lst;
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return ;
#endif
	lst = *a_lst;
	if (lst == NULL || index == 0)
	{
		*a_lst = elem;
		if (elem == NULL || elem->next == NULL)
			return ;
//		elem->prev = NULL;
		elem->next = lst->next;
		return ;
	}
	i = 0;
	while (++i < index && lst->next)
	{
		lst = lst->next;
	}
//	elem->prev = lst;
	elem->next = lst->next;
	lst->next = elem;
}
