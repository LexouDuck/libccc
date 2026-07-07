
#include "libccc/memory.h"
#include "libccc/generic/convert.h"

#include LIBCONFIG_ERROR_INCLUDE



//! NOTE: the foreign generic symbols used by this file must be in "declaration"
//! form (see the note in "libccc/generic/convert.h" for a detailed explanation)
//!@{
#undef	s_array
#undef	s_list
#define	s_array(X)	CONCAT(s_array_,	X##_NAME)
#define	s_list(X)	CONCAT(s_list_,	X##_NAME)
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



//! NOTE: restore the foreign generic symbols to their normal user-facing form
//!@{
#undef	s_array
#undef	s_list
#define	s_array(T)	CONCAT(s_array_,	T)
#define	s_list(T)	CONCAT(s_list_,	T)
//!@}
