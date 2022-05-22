
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Sub(void* const* ptrarr, t_uint index, t_uint n)
{
	void**		result;
	t_uint		length;
	t_uint		i;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	length = PointerArray_Length((void const* const*)ptrarr);
	if CCCERROR((index > length), ERROR_INDEX2LARGE,
		"subsection start index "SF_UINT" is greater than pointer array length: "SF_UINT, index, length)
		return (NULL);
	if CCCERROR((index + n > length), ERROR_LENGTH2LARGE,
		"subsection end index "SF_UINT" is greater than pointer array length: "SF_UINT, index + n, length)
		return (NULL);
	result = PointerArray_New(n, NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = ptrarr[index + i];
		++i;
	}
	result[i] = NULL;
	return (result);
}
