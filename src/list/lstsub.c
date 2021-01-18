
#include "libccc_list.h"



s_list*		List_Sub(s_list* lst, t_u32 index, t_u32 n)
{
	s_list*	result;
	s_list*	result_lst;
	s_list*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (n == 0)
		return (NULL);
	while (lst && index--)
		lst = lst->next;
	if (lst == NULL)
		return (NULL);
	result = List_New(lst->item, lst->item_size);
	if (result == NULL)
		return (NULL);
	result_lst = result;
	lst = lst->next;
	while (lst && n--)
	{
		tmp = List_New(lst->item, lst->item_size);
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}
