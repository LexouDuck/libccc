
#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	Memory_Join(void const** ptrarr, t_size const* lengths,
	void const* separator, t_size separator_length)
{
	t_u8*	result;
	t_uint	amount;
	t_size	total;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	if CCCERROR((lengths == NULL), ERROR_NULLPOINTER, "lengths array given is NULL")
		return (NULL);
	if CCCERROR((separator == NULL), ERROR_NULLPOINTER, "separator given is NULL")
		return (NULL);
	amount = PointerArray_Length(ptrarr);
	if (amount == 0)
		return (String_Duplicate(""));
	total = 0;
	for (t_uint i = 0; i < amount; ++i)
	{
		total += lengths[i];
	}
	if (amount > 0)
		total += separator_length * (amount - 1);
	result = Memory_New(total * sizeof(t_u8));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	total = 0;
	for (t_uint i = 0; i < amount; ++i)
	{
		for (t_uint index = 0; index < lengths[i]; ++index)
		{
			result[total + index] = ((t_u8*)ptrarr[i])[index];
		}
		total += lengths[i];
		if (i == amount - 1)
			break;
		for (t_uint index = 0; index < separator_length; ++index)
		{
			result[total + index] = ((t_u8*)separator)[index];
		}
		total += separator_length;
	}
	return (result);
}
