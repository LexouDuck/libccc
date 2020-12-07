
#include "libft_list.h"



s_list	*ft_lstcpy(s_list *lst)
{
	s_list	*result;
	s_list	*result_lst;
	s_list	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	result = ft_lstnew(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(lst->item, lst->item_size);
		result_lst->next = tmp;
		lst = lst->next;
		result_lst = result_lst->next;
	}
	return (result);
}
