
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_Free(T)(s_array(T)* array)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return;
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
	Memory_Free(array);
}



_GENERIC()
void	Array_Free_F(T)(s_array(T)* array, void (*del)(T* item))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return;
	for (t_uint i = 0; i < array->length; ++i)
	{
		del(&array->items[i]);
	}
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
	Memory_Free(array);
}



_GENERIC()
void	Array_Delete(T)(s_array(T)* *a_array)
{
	if CCCERROR((a_array  == NULL), ERROR_NULLPOINTER, "array address given is NULL")
		return;
	if CCCERROR((*a_array == NULL), ERROR_NULLPOINTER, NULL)
		return;
	Memory_Free((*a_array)->items);
	(*a_array)->items = NULL;
	(*a_array)->length = 0;
	Memory_Free(*a_array);
	(*a_array) = NULL;
}



_GENERIC()
void	Array_Delete_F(T)(s_array(T)* *a_array, void (*del)(T* item))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((a_array  == NULL), ERROR_NULLPOINTER, "array address given is NULL")
		return;
	if CCCERROR((*a_array == NULL), ERROR_NULLPOINTER, NULL)
		return;
	for (t_uint i = 0; i < (*a_array)->length; ++i)
	{
		del(&(*a_array)->items[i]);
	}
	Memory_Free((*a_array)->items);
	(*a_array)->items = NULL;
	(*a_array)->length = 0;
	Memory_Free(*a_array);
	(*a_array) = NULL;
}
