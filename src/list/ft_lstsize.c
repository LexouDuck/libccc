
#include "libft_list.h"



t_u32	ft_lstsize(s_list *lst)
{
	t_u32 result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (0);
#endif
	result = 0;
	while (lst)
	{
		++result;
		lst = lst->next;
	}
	return (result);
}
/*
**	if (lst == NULL)
**		return (0);
*/
