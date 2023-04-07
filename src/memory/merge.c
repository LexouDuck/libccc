
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void*		Memory_Concat(
	void const* ptr1, t_size length1,
	void const* ptr2, t_size length2)
{
	t_u8*	result;
	t_size	i;

	if CCCERROR((ptr1 == NULL), ERROR_NULLPOINTER, "left-hand-side pointer given is NULL")
		return (NULL);
	if CCCERROR((ptr2 == NULL), ERROR_NULLPOINTER, "right-hand-side pointer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_Allocate(length1 + length2 + 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
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

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "buffer to append given is NULL")
		return (NULL);
	tmp = Memory_Concat(
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

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination address given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "buffer to append given is NULL")
		return (NULL);
	tmp = Memory_Concat(
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

	if CCCERROR((a_ptr1 == NULL), ERROR_NULLPOINTER, "left-hand-side pointer address given is NULL")
		return (NULL);
	if CCCERROR((a_ptr2 == NULL), ERROR_NULLPOINTER, "right-hand-side pointer address given is NULL")
		return (NULL);
	result = Memory_Concat(
		*a_ptr1, length1,
		*a_ptr2, length2);
	Memory_Delete(a_ptr1);
	Memory_Delete(a_ptr2);
	*a_ptr1 = result;
	*a_ptr2 = result;
	return (result);
}
