
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_sint	PointerArray_Compare(void const* const* ptrarr1, void const* const* ptrarr2,
	t_sint (*compare)(void const* ptr1, void const* ptr2))
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (ptrarr1 == ptrarr2)
		return (0);
	if CCCERROR((ptrarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side pointer array given is NULL")
		return ((ptrarr1 - ptrarr2));
	if CCCERROR((ptrarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side pointer array given is NULL")
		return ((ptrarr1 - ptrarr2));
	length1 = PointerArray_Length((void const* const*)ptrarr1);
	length2 = PointerArray_Length((void const* const*)ptrarr2);
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



t_sint	PointerArray_Compare_N(void const* const* ptrarr1, void const* const* ptrarr2,
	t_sint (*compare)(void const* ptr1, void const* ptr2), t_uint n)
{
	t_sint	result;
	t_uint	length1;
	t_uint	length2;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (ptrarr1 == ptrarr2)
		return (0);
	if CCCERROR((ptrarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side pointer array given is NULL")
		return ((ptrarr1 - ptrarr2));
	if CCCERROR((ptrarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side pointer array given is NULL")
		return ((ptrarr1 - ptrarr2));
	length1 = PointerArray_Length((void const* const*)ptrarr1);
	length2 = PointerArray_Length((void const* const*)ptrarr2);
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
