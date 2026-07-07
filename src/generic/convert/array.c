
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
#undef	Set_New
#undef	Set_Add
#undef	Set_Free
#define	s_array(X)		CONCAT(s_array_,	X##_NAME)
#define	s_list(X)		CONCAT(s_list_,	X##_NAME)
#define	s_set(X)		CONCAT(s_set_,	X##_NAME)
#define	List_Item(X)	CONCAT(List_Item_,	X##_NAME)
#define	List_Delete(X)	CONCAT(List_Delete_,	X##_NAME)
#define	Set_New(X)		CONCAT(Set_New_,	X##_NAME)
#define	Set_Add(X)		CONCAT(Set_Add_,	X##_NAME)
#define	Set_Free(X)		CONCAT(Set_Free_,	X##_NAME)
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



_GENERIC()
s_set(T)*	Array_ToSet(T)(s_array(T) const* array)
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (NULL);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS,
		"array given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	// NOTE: Set_Add() ignores any duplicate values: the resulting set
	// can have a smaller `length` than the given array
	for (i = 0; i < array->length; ++i)
	{
		if (Set_Add(T)(result, array->items[i]) == NULL)
		{
			Set_Free(T)(result);
			return (NULL);
		}
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
#undef	Set_New
#undef	Set_Add
#undef	Set_Free
#define	s_array(T)		CONCAT(s_array_,	T)
#define	s_list(T)		CONCAT(s_list_,	T)
#define	s_set(T)		CONCAT(s_set_,	T)
#define	List_Item(T)	CONCAT(List_Item_,	T)
#define	List_Delete(T)	CONCAT(List_Delete_,	T)
#define	Set_New(T)		CONCAT(Set_New_,	T)
#define	Set_Add(T)		CONCAT(Set_Add_,	T)
#define	Set_Free(T)		CONCAT(Set_Free_,	T)
//!@}
