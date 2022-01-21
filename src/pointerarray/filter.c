
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Filter(void* const* ptrarr, t_bool (*filter)(void const* ptr))
{
	void**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length((void const* const*)ptrarr);
	if (length == 0 || ptrarr == NULL)
		return ((void**)Memory_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (NULL);)
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(ptrarr[i]);
		if (tmp[i])
			++result_length;
	}
	result = PointerArray_New(result_length, NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (result);)
	if (result_length == 0)
		return (result);
	t_uint	index = 0;
	for (i = 0; i < length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = ptrarr[i];
		}
		if (index >= result_length)
			break;
	}
	Memory_Free(tmp);
	return (result);
}


void**	PointerArray_Filter_I(void* const* ptrarr, t_bool (*filter)(void const* ptr, t_uint index))
{
	void**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (filter == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length((void const* const*)ptrarr);
	if (length == 0 || ptrarr == NULL)
		return ((void**)Memory_New(sizeof(void*)));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return (NULL);)
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(ptrarr[i], i);
		if (tmp[i])
			++result_length;
	}
	result = PointerArray_New(result_length, NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (result);)
	if (result_length == 0)
		return (result);
	t_uint	index = 0;
	for (i = 0; i < length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = ptrarr[i];
		}
		if (index >= result_length)
			break;
	}
	Memory_Free(tmp);
	return (result);
}
