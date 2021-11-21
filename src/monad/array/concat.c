
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Concat,T_NAME)(s_array_T const* array1, s_array_T const* array2)
{
	s_array_T*	result;

	result = CONCAT(Array_New,T_NAME)(array1->length + array2->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	return (result);
}



_GENERIC()
s_array_T*	CONCAT(Array_Append,T_NAME)(s_array_T* array1, s_array_T const* array2)
{
	s_array_T*	result;

	result = CONCAT(Array_New,T_NAME)(array1->length + array2->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	CONCAT(Array_Delete,T_NAME)(array1);
	return (result);
}



_GENERIC()
s_array_T*	CONCAT(Array_Prepend,T_NAME)(s_array_T const* array1, s_array_T* array2)
{
	s_array_T*	result;

	result = CONCAT(Array_New,T_NAME)(array1->length + array2->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	CONCAT(Array_Delete,T_NAME)(array2);
	return (result);
}



_GENERIC()
s_array_T*	CONCAT(Array_Merge,T_NAME)(s_array_T* array1, s_array_T* array2)
{
	s_array_T*	result;

	result = CONCAT(Array_New,T_NAME)(array1->length + array2->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	Memory_Copy(result->items, array1->items, array1->length);
	Memory_Copy(result->items + array1->length, array2->items, array2->length);
	CONCAT(Array_Delete,T_NAME)(array1);
	CONCAT(Array_Delete,T_NAME)(array2);
	return (result);
}
