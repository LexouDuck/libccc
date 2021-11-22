
#include "libccc/memory.h"
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(List_Delete,T_NAME)(s_list_T* *a_list)
{
	s_list_T*	next;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (a_list  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_list == NULL), return;)
	i = *a_list;
	while (i)
	{
		next = i->next;
		Memory_Free(i);
		i = next;
	}
	*a_list = NULL;
}



_GENERIC()
void	CONCAT(List_Delete_F,T_NAME)(s_list_T* *a_list, void (*delete)(T* item))
{
	s_list_T*	next;
	s_list_T*	i;

	HANDLE_ERROR(NULLPOINTER, (delete  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (a_list  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_list == NULL), return;)
	i = *a_list;
	while (i)
	{
		next = i->next;
		delete(&i->item);
		Memory_Free(i);
		i = next;
	}
	*a_list = NULL;
}
