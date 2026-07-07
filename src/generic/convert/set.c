
#include "libccc/memory.h"
#include "libccc/generic/convert.h"

#include LIBCONFIG_ERROR_INCLUDE



//! NOTE: the foreign generic symbols used by this file must be in "declaration"
//! form (see the note in "libccc/generic/convert.h" for a detailed explanation)
//!@{
#undef	s_array
#undef	s_list
#undef	s_set
#undef	List_Item
#undef	List_Delete
#define	s_array(X)		CONCAT(s_array_,	X##_NAME)
#define	s_list(X)		CONCAT(s_list_,	X##_NAME)
#define	s_set(X)		CONCAT(s_set_,	X##_NAME)
#define	List_Item(X)	CONCAT(List_Item_,	X##_NAME)
#define	List_Delete(X)	CONCAT(List_Delete_,	X##_NAME)
//!@}



_GENERIC()
s_array(T)*	Set_ToArray(T)(s_set(T) const* set)
{
	s_array(T)*	result;
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (set->length == 0)
		return (result); // an empty set converts to an empty array
	result->items = (T*)Memory_Allocate(set->length * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	// NOTE: the given set already holds unique values, so they can simply be
	// copied (in the set's internal storage order, which is an implementation detail)
	for (i = 0; i < set->length; ++i)
	{
		result->items[i] = set->items[i];
	}
	result->length = set->length;
	return (result);
}



_GENERIC()
s_list(T)*	Set_ToList(T)(s_set(T) const* set)
{
	s_list(T)*	result;
	s_list(T)*	node;
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	// NOTE: an empty set converts to an empty list (ie: a `NULL` pointer, with no error)
	result = NULL;
	// the chain is built backwards (from the last item to the first), so that
	// each new node can simply be linked in front of the current chain head
	for (i = set->length; i > 0; --i)
	{
		node = List_Item(T)(set->items[i - 1]);
		if CCCERROR((node == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			if (result != NULL)
				List_Delete(T)(&result);
			return (NULL);
		}
		node->next = result;
#if LIBCONFIG_LIST_DOUBLYLINKED
		if (result != NULL)
			result->prev = node;
#endif
		result = node;
	}
	return (result);
}



//! NOTE: restore the foreign generic symbols to their normal user-facing form
//!@{
#undef	s_array
#undef	s_list
#undef	s_set
#undef	List_Item
#undef	List_Delete
#define	s_array(T)		CONCAT(s_array_,	T)
#define	s_list(T)		CONCAT(s_list_,	T)
#define	s_set(T)		CONCAT(s_set_,	T)
#define	List_Item(T)	CONCAT(List_Item_,	T)
#define	List_Delete(T)	CONCAT(List_Delete_,	T)
//!@}
