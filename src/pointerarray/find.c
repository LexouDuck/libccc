
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void* const*	PointerArray_Find(void* const* ptrarr, void const* ptr)
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
			return (&(ptrarr[i]));
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}


void* const*	PointerArray_Find_F(void* const* ptrarr, t_bool (*match)(void const* ptr))
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (match(ptrarr[i]))
			return (&(ptrarr[i]));
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
}


t_sint	PointerArray_IndexOf(void* const* ptrarr, void const* ptr)
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (ERROR);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (ptrarr[i] == ptr)
			return (i);
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}


t_sint	PointerArray_IndexOf_F(void* const* ptrarr, t_bool (*match)(void const* ptr))
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (ERROR);)
	length = PointerArray_Length(ptrarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (match(ptrarr[i]))
			return (i);
	}
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}
