
#include "libccc/monad/list.h"



t_u32	List_Size(s_list_T const* lst)
{
	t_u32 result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
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
