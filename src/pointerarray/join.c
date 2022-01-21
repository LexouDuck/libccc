
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Join(void* const** ptrarrs, void* const* sep)
{
	void**	result;
	t_uint	total;
	t_uint	length_strarrs;
	t_uint	length_sep;
	t_uint	index;

	HANDLE_ERROR(NULLPOINTER, (ptrarrs == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (sep     == NULL), return (NULL);)
	if (ptrarrs[0] == NULL)
		return (PointerArray_New(0, NULL));
	total = 0;
	length_sep = PointerArray_Length((void const* const*)sep);
	length_strarrs = 0;
	while (ptrarrs[length_strarrs])
	{
		total += PointerArray_Length((void const* const*)ptrarrs[length_strarrs]);
		++length_strarrs;
		if (ptrarrs[length_strarrs])
			total += length_sep;
	}
	result = PointerArray_New(total, NULL);
	index = 0;
	for (t_uint i = 0; i < length_strarrs; ++i)
	{
		for (t_uint j = 0; ptrarrs[i][j]; ++j)
		{
			result[index++] = ptrarrs[i][j];
		}
		if (index == total)
			break;
		for (t_uint j = 0; j < length_sep; ++j)
		{
			result[index++] = sep[j];
		}
	}
	return (result);
}
