
#include "libft_list.h"



s_list*	List_Get(s_list const* lst, t_u32 index)
{
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	i = 0;
	while (i < index)
	{
		if (lst->next == NULL)
			return (NULL);
		else
			lst = lst->next;
		++i;
	}
	return ((s_list*)lst);
}



s_list*	List_Find(s_list const* lst, void const* query)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (query == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->item == query)
			return ((s_list*)lst);
		lst = lst->next;
	}
	return (NULL);
}
