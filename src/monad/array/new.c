
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



#if 0
_GENERIC()
s_array(T)	CONCAT(Array,T_NAME)(t_uint n)
{
	s_array(T)	result;

	result.length = n;
	result.items = NULL;
	if (n == 0)
		return (result);
	result.items = (T*)Memory_Allocate(sizeof(T) * n);
	if CCCERROR((result.items == NULL), ERROR_ALLOCFAILURE, NULL)
	return (result);
	for (t_uint i = 0; i < n; ++i)
	{
		result.items[i] = T_NULL;
	}
	return (result);
}
#endif



_GENERIC()
s_array(T)*	Array_New(T)(t_uint n, T value)
{
	s_array(T)*	result;

	result = (s_array(T)*)Memory_New(sizeof(s_array(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->length = n;
	result->items = NULL;
	if (n == 0)
		return (result);
	result->items = (T*)Memory_New(n * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Delete((void**)&result);
		return (NULL);
	}
	for (t_uint i = 0; i < n; ++i)
	{
		result->items[i] = value;
	}
	return (result);
}
