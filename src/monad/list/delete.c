
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
void	List_Free_F(T)(s_list(T)* list, void (*del)(T* item))
{
	s_list(T)*	next;
	s_list(T)*	i;

	HANDLE_ERROR(NULLPOINTER, (list == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (del  == NULL), return;)
	i = list;
	while (i)
	{
		next = i->next;
		del(&i->item);
		Memory_Free(i);
		i = next;
	}
}



_GENERIC()
void	List_Delete(T)(s_list(T)* *a_list)
{
	s_list(T)*	next;
	s_list(T)*	i;

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
void	List_Delete_F(T)(s_list(T)* *a_list, void (*del)(T* item))
{
	s_list(T)*	next;
	s_list(T)*	i;

	HANDLE_ERROR(NULLPOINTER, (del     == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (a_list  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_list == NULL), return;)
	i = *a_list;
	while (i)
	{
		next = i->next;
		del(&i->item);
		Memory_Free(i);
		i = next;
	}
	*a_list = NULL;
}
