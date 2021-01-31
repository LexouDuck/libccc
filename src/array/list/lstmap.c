
#include "libccc/memory.h"
#include "libccc/array/list.h"



static void	List_Map_Delete(void* item, t_size item_size)
{
	if (item && item_size > 0)
	{
		Memory_Free(item);
	}
}



s_list*		List_Map(s_list* lst, s_list *(*f)(s_list* elem))
{
	s_list	*result;
	s_list	*current;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return (NULL);
#endif
	result = NULL;
	while (lst)
	{
		current = f(lst);
		if (current == NULL)
		{
			List_Delete(&result, List_Map_Delete);
			return (NULL);
		}
		List_Append(&result, current);
		lst = lst->next;
	}
	return (result);
}



s_list*		List_Map_I(s_list* lst, s_list *(*f)(s_list* elem, t_u32 index))
{
	s_list	*result;
	s_list	*current;
	t_u32	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return (NULL);
#endif
	i = 0;
	while (lst)
	{
		current = f(lst, i);
		if (current == NULL)
		{
			List_Delete(&result, List_Map_Delete);
			return (NULL);
		}
		List_Append(&result, current);
		lst = lst->next;
		++i;
	}
	return (result);
}
