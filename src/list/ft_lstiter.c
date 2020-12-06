
#include "libft_list.h"



void	ft_lstiter(s_list *lst, void (*f)(s_list *elem))
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return ;
#endif
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}



void	ft_lstiteri(s_list *lst, void (*f)(s_list *elem, t_u32 index))
{
	t_u32 i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (lst)
	{
		f(lst, i);
		lst = lst->next;
		++i;
	}
}
