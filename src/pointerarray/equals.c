
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	PointerArray_Equals(void* const* ptrarr1, void* const* ptrarr2)
{
	t_uint	length1;
	t_uint	length2;

	if (ptrarr1 == ptrarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (ptrarr1 == NULL), return (ptrarr1 - ptrarr2);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr2 == NULL), return (ptrarr1 - ptrarr2);)
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	for (t_uint i = 0; (i < length1) && (i < length2); ++i)
	{
		if (ptrarr1[i] != ptrarr2[i])
			return (FALSE);
	}
	return (TRUE);
}


t_bool	PointerArray_Equals_N(void* const* ptrarr1, void* const* ptrarr2, t_uint n)
{
	t_uint	length1;
	t_uint	length2;

	if (ptrarr1 == ptrarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (ptrarr1 == NULL), return (ptrarr1 - ptrarr2);)
	HANDLE_ERROR(NULLPOINTER, (ptrarr2 == NULL), return (ptrarr1 - ptrarr2);)
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		if (ptrarr1[i] != ptrarr2[i])
			return (FALSE);
	}
	return (TRUE);
}
