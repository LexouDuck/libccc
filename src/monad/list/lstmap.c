
#include "libccc/memory.h"
#include "libccc/monad/list.h"

/*

s_list_T*		List_Map(s_list_T* lst, s_list_T *(*f)(s_list_T* elem))
{
	s_list_T	*result;
	s_list_T	*current;

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



s_list_T*		List_Map_I(s_list_T* lst, s_list_T *(*f)(s_list_T* elem, t_u32 index))
{
	s_list_T	*result;
	s_list_T	*current;
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
*/