
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(List_Delete,T_NAME)(s_list_T* list)
{
	s_list_T*	next;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
	i = list;
	while (i)
	{
		next = i->next;
		Memory_Free(i);
		i = next;
	}
	list = NULL;
}



_GENERIC()
void	CONCAT(List_Delete_F,T_NAME)(s_list_T* list, void (*delete)(T* item))
{
	s_list_T*	next;
	s_list_T*	i;

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
	list = NULL;
}
