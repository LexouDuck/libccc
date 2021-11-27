
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	List_Free(T)(s_list(T)* list)
{
	s_list(T)*	next;
	s_list(T)*	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
	i = list;
	while (i)
	{
		next = i->next;
		Memory_Free(i);
		i = next;
	}
}



_GENERIC()
void	List_Free_F(T)(s_list(T)* list, void (*delete)(T* item))
{
	s_list(T)*	next;
	s_list(T)*	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	i = list;
	while (i)
	{
		next = i->next;
		delete(&i->item);
		Memory_Free(i);
		i = next;
	}
}
