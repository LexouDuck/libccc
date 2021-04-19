
#include "libccc/memory.h"
#include "libccc/monad/list.h"



void	List_Delete(s_list_T* *a_list)
{
//	s_list_T* prev;
	s_list_T* next;
	s_list_T* i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_list == NULL)
		return ;
#endif
	i = *a_list;
	while (i)
	{
//		prev = i->prev;
		next = i->next;
		Memory_Free(i);
		i = next;
//		if (next)
//			next->prev = prev;
	}
	*a_list = NULL;
}
