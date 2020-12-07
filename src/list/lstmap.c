
#include "libft_memory.h"
#include "libft_list.h"



static void	ft_lstmap_delete(void *content, t_size content_size)
{
	if (content && content_size > 0)
	{
		ft_memfree(content);
	}
}



s_list		*ft_lstmap(s_list *lst, s_list *(*f)(s_list *elem))
{
	s_list	*result;
	s_list	*current;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return (NULL);
#endif
	result = NULL;
	while (lst)
	{
		current = f(lst);
		if (current == NULL)
		{
			ft_lstdel(&result, ft_lstmap_delete);
			return (NULL);
		}
		ft_lstappend(&result, current);
		lst = lst->next;
	}
	return (result);
}



s_list		*ft_lstmapi(s_list *lst, s_list *(*f)(s_list *elem, t_u32 index))
{
	s_list	*result;
	s_list	*current;
	t_u32	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return (NULL);
#endif
	i = 0;
	while (lst)
	{
		current = f(lst, i);
		if (current == NULL)
		{
			ft_lstdel(&result, ft_lstmap_delete);
			return (NULL);
		}
		ft_lstappend(&result, current);
		lst = lst->next;
		++i;
	}
	return (result);
}
