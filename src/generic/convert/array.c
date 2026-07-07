
#include "libccc/memory.h"
#include "libccc/generic/convert.h"

#include LIBCONFIG_ERROR_INCLUDE



//! NOTE: the foreign generic symbols used by this file must be in "declaration"
//! form (see the note in "libccc/generic/convert.h" for a detailed explanation)
//!@{
#undef	s_array
#undef	s_list
#undef	List_Item
#undef	List_Delete
#define	s_array(X)		CONCAT(s_array_,	X##_NAME)
#define	s_list(X)		CONCAT(s_list_,	X##_NAME)
#define	List_Item(X)	CONCAT(List_Item_,	X##_NAME)
#define	List_Delete(X)	CONCAT(List_Delete_,	X##_NAME)
//!@}



_GENERIC()
s_list(T)*	Array_ToList(T)(s_array(T) const* array)
{
	s_list(T)*	result;
	s_list(T)*	node;
	t_uint	i;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS,
		"array given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	// NOTE: an empty array converts to an empty list (ie: a `NULL` pointer, with no error)
	result = NULL;
	// the chain is built backwards (from the last item to the first), so that
	// each new node can simply be linked in front of the current chain head
	for (i = array->length; i > 0; --i)
	{
		node = List_Item(T)(array->items[i - 1]);
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
#undef	List_Item
#undef	List_Delete
#define	s_array(T)		CONCAT(s_array_,	T)
#define	s_list(T)		CONCAT(s_list_,	T)
#define	List_Item(T)	CONCAT(List_Item_,	T)
#define	List_Delete(T)	CONCAT(List_Delete_,	T)
//!@}
