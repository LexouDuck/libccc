
#include "libccc/monad/list.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void*	List_Reduce(T)(s_list(T) const* list,
	void* (*f)(T item, void* acc))
{
	void*		accumulator = NULL;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		accumulator = f(list->item, accumulator);
		list = list->next;
	}
	return (accumulator);
}

_GENERIC()
void*	List_Reduce_I(T)(s_list(T) const* list,
	void* (*f)(T item, void* acc, t_uint index))
{
	void*		accumulator = NULL;
	t_uint		i = 0;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		accumulator = f(list->item, accumulator, i++);
		list = list->next;
	}
	return (accumulator);
}



_GENERIC()
void*	List_Fold(T)(s_list(T) const* list,
	void* (*f)(T item, void* acc), void* initial)
{
	void*		accumulator = initial;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		accumulator = f(list->item, accumulator);
		list = list->next;
	}
	return (accumulator);
}

_GENERIC()
void*	List_Fold_I(T)(s_list(T) const* list,
	void* (*f)(T item, void* acc, t_uint index), void* initial)
{
	void*		accumulator = initial;
	t_uint		i = 0;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (list == NULL), return (NULL);)
	while (list)
	{
		accumulator = f(list->item, accumulator, i++);
		list = list->next;
	}
	return (accumulator);
}
