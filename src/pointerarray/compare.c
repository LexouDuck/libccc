
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sint	PointerArray_Compare(void* const* ptrarr1, void* const* ptrarr2,
	t_sint (*compare)(void const* ptr1, void const* ptr2))
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	HANDLE_ERROR(NULLPOINTER, (compare == NULL), return (0);)
	if (ptrarr1 == ptrarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (ptrarr1 == NULL), return ((ptrarr1 - ptrarr2));)
	HANDLE_ERROR(NULLPOINTER, (ptrarr2 == NULL), return ((ptrarr1 - ptrarr2));)
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	if (length1 == length2 && ptrarr1 == ptrarr2)
		return (0);
	for (t_uint i = 0; (i < length1) && (i < length2); ++i)
	{
		result = compare(ptrarr1[i], ptrarr2[i]);
		if (result)
			return (result);
	}
	return (0);
}



t_sint	PointerArray_Compare_N(void* const* ptrarr1, void* const* ptrarr2,
	t_sint (*compare)(void const* ptr1, void const* ptr2), t_uint n)
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	HANDLE_ERROR(NULLPOINTER, (compare == NULL), return (0);)
	if (ptrarr1 == ptrarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (ptrarr1 == NULL), return ((ptrarr1 - ptrarr2));)
	HANDLE_ERROR(NULLPOINTER, (ptrarr2 == NULL), return ((ptrarr1 - ptrarr2));)
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	if (length1 == length2 && ptrarr1 == ptrarr2)
		return (0);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		result = compare(ptrarr1[i], ptrarr2[i]);
		if (result)
			return (result);
	}
	return (0);
}
