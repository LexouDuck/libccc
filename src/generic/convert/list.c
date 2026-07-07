
#include "libccc/memory.h"
#include "libccc/generic/convert.h"

#include LIBCONFIG_ERROR_INCLUDE



//! NOTE: the foreign generic symbols used by this file must be in "declaration"
//! form (see the note in "libccc/generic/convert.h" for a detailed explanation)
//!@{
#undef	s_array
#undef	s_list
#undef	s_set
#undef	Set_New
#undef	Set_Add
#undef	Set_Free
#define	s_array(X)	CONCAT(s_array_,	X##_NAME)
#define	s_list(X)	CONCAT(s_list_,	X##_NAME)
#define	s_set(X)	CONCAT(s_set_,	X##_NAME)
#define	Set_New(X)	CONCAT(Set_New_,	X##_NAME)
#define	Set_Add(X)	CONCAT(Set_Add_,	X##_NAME)
#define	Set_Free(X)	CONCAT(Set_Free_,	X##_NAME)
//!@}



_GENERIC()
s_array(T)*	List_ToArray(T)(s_list(T) const* list)
{
	s_array(T)*	result;
	s_list(T) const*	elem;
	t_uint	length;
	t_uint	i;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	length = 0;
	for (elem = list; elem != NULL; elem = elem->next)
	{
		length += 1;
	}
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->items = (T*)Memory_Allocate(length * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	i = 0;
	for (elem = list; elem != NULL; elem = elem->next)
	{
		result->items[i++] = elem->item;
	}
	result->length = length;
	return (result);
}



_GENERIC()
s_set(T)*	List_ToSet(T)(s_list(T) const* list)
{
	s_set(T)*	result;
	s_list(T) const*	elem;

	if CCCERROR((list == NULL), ERROR_NULLPOINTER, "list given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	// NOTE: Set_Add() ignores any duplicate values: the resulting set
	// can have a smaller `length` than the given list
	for (elem = list; elem != NULL; elem = elem->next)
	{
		if (Set_Add(T)(result, elem->item) == NULL)
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
#undef	Set_New
#undef	Set_Add
#undef	Set_Free
#define	s_array(T)	CONCAT(s_array_,	T)
#define	s_list(T)	CONCAT(s_list_,	T)
#define	s_set(T)	CONCAT(s_set_,	T)
#define	Set_New(T)	CONCAT(Set_New_,	T)
#define	Set_Add(T)	CONCAT(Set_Add_,	T)
#define	Set_Free(T)	CONCAT(Set_Free_,	T)
//!@}
