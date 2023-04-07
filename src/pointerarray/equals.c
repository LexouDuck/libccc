
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	PointerArray_Equals(void const* const* ptrarr1, void const* const* ptrarr2)
{
	t_uint	length1;
	t_uint	length2;

	if (ptrarr1 == ptrarr2)
		return (TRUE);
	if CCCERROR((ptrarr1 == NULL), ERROR_NULLPOINTER, NULL)	return (FALSE);
	if CCCERROR((ptrarr2 == NULL), ERROR_NULLPOINTER, NULL)	return (FALSE);
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	for (t_uint i = 0; (i < length1) && (i < length2); ++i)
	{
		if (ptrarr1[i] != ptrarr2[i])
			return (FALSE);
	}
	return (TRUE);
}


t_bool	PointerArray_Equals_N(void const* const* ptrarr1, void const* const* ptrarr2, t_uint n)
{
	t_uint	length1;
	t_uint	length2;

	if (ptrarr1 == ptrarr2)
		return (TRUE);
	if CCCERROR((ptrarr1 == NULL), ERROR_NULLPOINTER, NULL)	return (FALSE);
	if CCCERROR((ptrarr2 == NULL), ERROR_NULLPOINTER, NULL)	return (FALSE);
	length1 = PointerArray_Length(ptrarr1);
	length2 = PointerArray_Length(ptrarr2);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		if (ptrarr1[i] != ptrarr2[i])
			return (FALSE);
	}
	return (TRUE);
}
