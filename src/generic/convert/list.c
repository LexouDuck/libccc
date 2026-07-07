
#include "libccc/memory.h"
#include "libccc/generic/array.h"
#include "libccc/generic/list.h"

#include LIBCONFIG_ERROR_INCLUDE


#if 0
s_array	List_ToArray(s_list const** a_lst)
{
	s_list const* lst;
	s_array result;
	t_size	count;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || *a_lst == NULL)
		return (ARRAY_NULL);
#endif
	lst = *a_lst;
	result.item_size = lst->item_size;
	count = 0;
	while (lst && ++count)
	{
		lst = lst->next;
		if (lst->item_size != result.item_size)
			return (ARRAY_NULL);
	}
	result.item_count = (count + 1);
	result.items = (void*)Memory_Allocate(result.item_count * result.item_size);
	if CCCERROR((result.items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ARRAY_NULL);
	i = 0;
	while (lst && ++i < count)
	{
		Memory_Copy((t_u8*)result.items + (i * result.item_size),
			lst->item, result.item_size);
		lst = lst->next;
	}
//	Memory_Clear(result + (i * result.item_size), result.item_size);
	return (result);
}
#endif
