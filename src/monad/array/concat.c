
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Concat(T)(s_array(T) const* array1, s_array(T) const* array2)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array1 == NULL && array2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array1 == NULL), return (Array_Duplicate(T)(array2));)
	HANDLE_ERROR(NULLPOINTER, (array2 == NULL), return (Array_Duplicate(T)(array1));)
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Append(T)(s_array(T)* array1, s_array(T) const* array2)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array1 == NULL && array2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array1 == NULL), return (Array_Duplicate(T)(array2));)
	HANDLE_ERROR(NULLPOINTER, (array2 == NULL), return (Array_Duplicate(T)(array1));)
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array1);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Prepend(T)(s_array(T) const* array1, s_array(T)* array2)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array1 == NULL && array2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array1 == NULL), return (Array_Duplicate(T)(array2));)
	HANDLE_ERROR(NULLPOINTER, (array2 == NULL), return (Array_Duplicate(T)(array1));)
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array2);
	return (result);
}



_GENERIC()
s_array(T)*	Array_Merge(T)(s_array(T)* array1, s_array(T)* array2)
{
	s_array(T)*	result;

	HANDLE_ERROR(NULLPOINTER, (array1 == NULL && array2 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array1 == NULL), return (Array_Duplicate(T)(array2));)
	HANDLE_ERROR(NULLPOINTER, (array2 == NULL), return (Array_Duplicate(T)(array1));)
	result = Array_New(T)(array1->length + array2->length, T_NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	Array_Free(T)(array1);
	Array_Free(T)(array2);
	return (result);
}
