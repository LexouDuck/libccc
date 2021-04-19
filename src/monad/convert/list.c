
#include "libccc/memory.h"
#include "libccc/monad/list.h"
#include "libccc/monad/array.h"

/*

void**	List_To_PointerArray(s_list const** a_lst)
{
	s_list const* lst;
	void**	result;
	t_size	length;
	t_u32	count;
	t_u32	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL)
		return (NULL);
#endif
	lst = *a_lst;
	count = List_Size(lst);
	length = (count + 1) * sizeof(void *);
	if (!(result = (void**)Memory_Alloc(length)))
		return (NULL);
	i = 0;
	while (lst && i < count)
	{
		result[i] = lst->item;
		lst = lst->next;
		++i;
	}
	result[i] = NULL;
	return (result);
}



s_array	List_To_Array(s_list const** a_lst)
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
	if (!(result.items = (void*)Memory_Alloc(result.item_count * result.item_size)))
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
*/