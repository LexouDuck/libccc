
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Concat(T)(s_array(T) const* array1, s_array(T) const* array2)
{
	s_array(T)*	result;

	if CCCERROR((array1 == NULL && array2 == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, "left-hand-side array given is NULL")
		return (Array_Duplicate(T)(array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, "right-hand-side array given is NULL")
		return (Array_Duplicate(T)(array1));
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Append(T)(s_array(T)* array1, s_array(T) const* array2)
{
	s_array(T)*	result;

	if CCCERROR((array1 == NULL && array2 == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, "destination array given is NULL")
		return (Array_Duplicate(T)(array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, "array to append given is NULL")
		return (Array_Duplicate(T)(array1));
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array1);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Prepend(T)(s_array(T) const* array1, s_array(T)* array2)
{
	s_array(T)*	result;

	if CCCERROR((array1 == NULL && array2 == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, "array to prepend given is NULL")
		return (Array_Duplicate(T)(array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, "destination array given is NULL")
		return (Array_Duplicate(T)(array1));
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array2);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Merge(T)(s_array(T)* array1, s_array(T)* array2)
{
	s_array(T)*	result;

	if CCCERROR((array1 == NULL && array2 == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, "left-hand-side array given is NULL")
		return (Array_Duplicate(T)(array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, "right-hand-side array given is NULL")
		return (Array_Duplicate(T)(array1));
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array1);
	Array_Free(T)(array2);
	return (result);
}
