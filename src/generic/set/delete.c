
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Set_Free(T)(s_set(T)* set)
{
	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return;
	if (set->items != NULL)
	{
		Memory_Free(set->items);
	}
	Memory_Free(set);
}



_GENERIC()
void	Set_Free_F(T)(s_set(T)* set, void (*del)(T item))
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return;
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	for (i = 0; i < set->length; ++i)
	{
		del(set->items[i]);
	}
	Set_Free(T)(set);
}



_GENERIC()
void	Set_Delete(T)(s_set(T)* *a_set)
{
	if CCCERROR((a_set == NULL), ERROR_NULLPOINTER, "set address given is NULL")
		return;
	Set_Free(T)(*a_set);
	*a_set = NULL;
}



_GENERIC()
void	Set_Delete_F(T)(s_set(T)* *a_set, void (*del)(T item))
{
	if CCCERROR((a_set == NULL), ERROR_NULLPOINTER, "set address given is NULL")
		return;
	Set_Free_F(T)(*a_set, del);
	*a_set = NULL;
}
