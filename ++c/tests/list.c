
#include "libccc_memory.h"
#include "libccc_list.h"



#ifndef __LIBCCC_LIST_H
#define __LIBCCC_LIST_H




__inline__
s_list<T>*	New(T item, t_size item_size)
{
	__asm__ {""}
	int __restrict__ a;
	int b = 0b1101;
	int o = 0o777;
	typeof(a) _a;
	s_list<T>* result;

	if (!(result = (s_list<T>*)Memory_Alloc(sizeof(s_list<T>))))
		return (NULL);
//	result->prev = NULL;
	result->next = NULL;
	result->item_size = (item ? item_size : 0);
	result->item = item;
	return (result);
}



void	Prepend(s_list<T>* *a_lst, s_list<T>* elem)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return;
#endif
	if (*a_lst == NULL)
	{
		*a_lst = elem;
		return;
	}
//	elem->prev = NULL;
	elem->next = *a_lst;
	*a_lst = elem;
}



void	Append(s_list<T>* *a_lst, s_list<T>* elem)
{
	s_list<T>*	lst;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return;
#endif
	if (*a_lst == NULL)
	{
		*a_lst = elem;
		return;
	}
	lst = *a_lst;
	while (lst->next)
	{
		lst = lst->next;
	}
//	elem->prev = lst;
	lst->next = elem;
}



void	Insert(s_list<T>* *a_lst, s_list<T>* elem, t_u32 index)
{
	s_list<T>*	lst;
	t_u32	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || elem == NULL)
		return ;
#endif
	lst = *a_lst;
	if (lst == NULL || index == 0)
	{
		*a_lst = elem;
		if (elem == NULL || elem->next == NULL)
			return ;
//		elem->prev = NULL;
		elem->next = lst->next;
		return ;
	}
	i = 0;
	while (++i < index && lst->next)
	{
		lst = lst->next;
	}
//	elem->prev = lst;
	elem->next = lst->next;
	lst->next = elem;
}



s_list<T>*	Copy(s_list<T> const* lst)
{
	s_list<T>	*result;
	s_list<T>	*result_lst;
	s_list<T>	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	result = New(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = New(lst->item, lst->item_size);
//		tmp->prev = result_lst;
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}



s_list<T>*	Duplicate(s_list<T> const* lst)
{
	s_list<T>	*result;
	s_list<T>	*result_lst;
	s_list<T>	*tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	result = New(lst->item, lst->item_size);
	result_lst = result;
	lst = lst->next;
	while (lst)
	{
		tmp = New(lst->item, lst->item_size);
		tmp->item = Memory_Duplicate(lst->item, lst->item_size);
//		tmp->prev = result_lst;
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}



void	Remove(s_list<T>* *a_lst, void (*del)(T, t_size))
{
//	s_list<T>* prev;
	s_list<T>* next;
	s_list<T>* lst;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	del(lst->item, lst->item_size);
//	prev = lst->prev;
	next = lst->next;
	Memory_Free(lst);
	*a_lst = next;
//	if (next)
//		next->prev = prev;
}



void	Delete(s_list<T>* *a_lst, void (*del)(T, t_size))
{
//	s_list<T>* prev;
	s_list<T>* next;
	s_list<T>* lst;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst = *a_lst;
	while (lst)
	{
		del(lst->item, lst->item_size);
//		prev = lst->prev;
		next = lst->next;
		Memory_Free(lst);
		lst = next;
//		if (next)
//			next->prev = prev;
	}
	*a_lst = NULL;
}



void	Pop(s_list<T>* *a_lst, void (*del)(T, t_size))
{
	s_list<T>* lst;
	s_list<T>* lst_prev;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL || del == NULL)
		return ;
#endif
	lst_prev = NULL;
	lst = *a_lst;
	while (lst)
	{
		if (lst->next == NULL)
		{
			del((lst)->item, (lst)->item_size);
			Memory_Free(lst);
			if (lst_prev)
				lst_prev->next = NULL;
			return ;
		}
		lst_prev = lst;
		lst = lst->next;
	}
}



t_u32	Size(s_list<T> const* lst)
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



s_list<T>*	Get(s_list<T> const* lst, t_u32 index)
{
	t_u32	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	i = 0;
	while (i < index)
	{
		if (lst->next == NULL)
			return (NULL);
		else
			lst = lst->next;
		++i;
	}
	return ((s_list<T>*)lst);
}



s_list<T>*	Find(s_list<T> const* lst, void const* query)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (query == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->item == query)
			return ((s_list<T>*)lst);
		lst = lst->next;
	}
	return (NULL);
}



s_list<T>*		Sub(s_list<T>* lst, t_u32 index, t_u32 n)
{
	s_list<T>*	result;
	s_list<T>*	result_lst;
	s_list<T>*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL)
		return (NULL);
#endif
	if (n == 0)
		return (NULL);
	while (lst && index--)
		lst = lst->next;
	if (lst == NULL)
		return (NULL);
	result = New(lst->item, lst->item_size);
	if (result == NULL)
		return (NULL);
	result_lst = result;
	lst = lst->next;
	while (lst && n--)
	{
		tmp = New(lst->item, lst->item_size);
		result_lst->next = tmp;
		result_lst = result_lst->next;
		lst = lst->next;
	}
	return (result);
}



void	Iterate(s_list<T>* lst, void (*f)(s_list<T>* elem))
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return ;
#endif
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}



void	Iterate_I(s_list<T>* lst, void (*f)(s_list<T>* elem, t_u32 index))
{
	t_u32 i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (lst == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (lst)
	{
		f(lst, i);
		lst = lst->next;
		++i;
	}
}



static void	Map_Delete(T item, t_size item_size)
{
	if (item && item_size > 0)
	{
		Memory_Free(item);
	}
}



s_list<T>*		Map(s_list<T>* lst, s_list<T> *(*f)(s_list<T>* elem))
{
	s_list<T>	*result;
	s_list<T>	*current;

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
			Delete(&result, Map_Delete);
			return (NULL);
		}
		Append(&result, current);
		lst = lst->next;
	}
	return (result);
}



s_list<T>*		Map_I(s_list<T>* lst, s_list<T> *(*f)(s_list<T>* elem, t_u32 index))
{
	s_list<T>	*result;
	s_list<T>	*current;
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
			Delete(&result, Map_Delete);
			return (NULL);
		}
		Append(&result, current);
		lst = lst->next;
		++i;
	}
	return (result);
}



T*	To_PointerArray(s_list<T> const** a_lst)
{
	s_list<T> const* lst;
	T*	result;
	t_size	length;
	t_u32	count;
	t_u32	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_lst == NULL)
		return (NULL);
#endif
	lst = *a_lst;
	count = Size(lst);
	length = (count + 1) * sizeof(void *);
	if (!(result = (T*)Memory_Alloc(length)))
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



s_array	To_Array(s_list<T> const** a_lst)
{
	s_list<T> const* lst;
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
	if (!(result.items = (T*)Memory_Alloc(result.item_count * result.item_size)))
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

#endif /* __LIBCCC_LIST_H */
