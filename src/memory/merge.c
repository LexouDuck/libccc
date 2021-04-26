
#include "libccc/memory.h"



void*		Memory_Join(
	void const* ptr1, t_size length1,
	void const* ptr2, t_size length2)
{
	t_u8*	result;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(ptr1, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(ptr2, NULL)
	if (!(result = Memory_Alloc(length1 + length2 + 1)))
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = ((t_u8*)ptr1)[i];
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = ((t_u8*)ptr2)[i];
		++i;
	}
	result[length1 + length2] = '\0';
	return (result);
}



void*	Memory_Append(
	void* *a_dest,	 t_size dest_length,
	void const* src, t_size src_length)
{
	void*	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(a_dest, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(src, NULL)
	tmp = Memory_Join(
		*a_dest, dest_length,
		src, src_length);
	Memory_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void*	Memory_Prepend(
	void const* src, t_size src_length,
	void* *a_dest,	 t_size dest_length)
{
	void*	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(a_dest, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(src, NULL)
	tmp = Memory_Join(
		src, src_length,
		*a_dest, dest_length);
	Memory_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



void*	Memory_Merge(
	void* *a_ptr1, t_size length1,
	void* *a_ptr2, t_size length2)
{
	void*	result;

	LIBCONFIG_HANDLE_NULLPOINTER(a_ptr1, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(a_ptr2, NULL)
	result = Memory_Join(
		*a_ptr1, length1,
		*a_ptr2, length2);
	Memory_Delete(a_ptr1);
	Memory_Delete(a_ptr2);
	*a_ptr1 = result;
	*a_ptr2 = result;
	return (result);
}
