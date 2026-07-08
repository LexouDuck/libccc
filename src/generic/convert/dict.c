
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/generic/convert.h"

#include LIBCONFIG_ERROR_INCLUDE



//! NOTE: the foreign generic symbols used by this file must be in "declaration"
//! form (see the note in "libccc/generic/convert.h" for a detailed explanation)
//!@{
#undef	s_array
#undef	s_dict
#undef	s_keyval
#undef	KeyVal
#undef	KeyVal_Free
#define	s_array(X)		CONCAT(s_array_,	X##_NAME)
#define	s_dict(X)		CONCAT(s_dict_,	X##_NAME)
#define	s_keyval(X)		CONCAT(s_keyval_,	X##_NAME)
#define	KeyVal(X)		CONCAT(KeyVal_,	X##_NAME)
#define	KeyVal_Free(X)	CONCAT(KeyVal_Free_,	X##_NAME)
//!@}



_GENERIC()
s_keyval(T)*	Dict_ToArray(T)(s_dict(T) const* dict)
{
	s_keyval(T)*	result;
	t_uint	i;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	// NOTE: one extra pair is allocated (and zero-filled by Memory_New()):
	// it serves as the terminator pair, with its `.key` being `NULL`
	result = (s_keyval(T)*)Memory_New((dict->length + 1) * sizeof(s_keyval(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < dict->length; ++i)
	{
		// NOTE: KeyVal() duplicates the given key string
		result[i] = KeyVal(T)(dict->items[i].key, dict->items[i].value);
		if CCCERROR((result[i].key == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			while (i--)
			{
				KeyVal_Free(T)(&result[i]);
			}
			Memory_Free(result);
			return (NULL);
		}
	}
	return (result);
}



_GENERIC()
t_char**	Dict_ToArray_Keys(T)(s_dict(T) const* dict)
{
	t_char**	result;
	t_uint	i;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	// NOTE: one extra pointer is allocated (and zero-filled by Memory_New()):
	// it serves as the `NULL` terminator of the resulting string array
	result = (t_char**)Memory_New((dict->length + 1) * sizeof(t_char*));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < dict->length; ++i)
	{
		result[i] = String_Duplicate(dict->items[i].key);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			while (i--)
			{
				String_Delete(&result[i]);
			}
			Memory_Free(result);
			return (NULL);
		}
	}
	return (result);
}



_GENERIC()
s_array(T)*	Dict_ToArray_Values(T)(s_dict(T) const* dict)
{
	s_array(T)*	result;
	t_uint	i;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (dict->length == 0)
		return (result); // an empty dict converts to an empty array
	result->items = (T*)Memory_Allocate(dict->length * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	// NOTE: the values are copied in the dict's storage order (insertion order)
	for (i = 0; i < dict->length; ++i)
	{
		result->items[i] = dict->items[i].value;
	}
	result->length = dict->length;
	return (result);
}



//! NOTE: restore the foreign generic symbols to their normal user-facing form
//!@{
#undef	s_array
#undef	s_dict
#undef	s_keyval
#undef	KeyVal
#undef	KeyVal_Free
#define	s_array(T)		CONCAT(s_array_,	T)
#define	s_dict(T)		CONCAT(s_dict_,	T)
#define	s_keyval(T)		CONCAT(s_keyval_,	T)
#define	KeyVal(T)		CONCAT(KeyVal_,	T)
#define	KeyVal_Free(T)	CONCAT(KeyVal_Free_,	T)
//!@}
