
#include "libccc/memory.h"
#include "libccc/stringarray.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArray_Remove(t_char** strarr, t_char const* str)
{
	t_sint	index;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	index = PointerArray_IndexOf((void const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArray_RemoveAt(strarr, index);
}



void	StringArray_Remove_F(t_char** strarr, t_char const* str,
	void (*delete)(t_char*))
{
	t_sint	index;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	index = PointerArray_IndexOf((void const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArray_RemoveAt_F(strarr, index, delete);
}



void	StringArray_RemoveAll(t_char** strarr, t_char const* str)
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	length = StringArray_Length((t_char const**)strarr);
	if (length == 0)
		return;
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (strarr[i] == str)
		{
			++amount;
		}
	}
	if (length == amount)
	{
		strarr[0] = NULL;
		return;
	}
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (strarr[i] == str)
		{
			++amount;
			continue;
		}
		strarr[i] = strarr[i + amount];
	}
	strarr[i] = NULL;
}



void	StringArray_RemoveAll_F(t_char** strarr, t_char const* str,
	void (*delete)(t_char*))
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (str    == NULL), return;)
	length = StringArray_Length((t_char const**)strarr);
	if (strarr[0] == NULL)
		return;
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (strarr[i] == str)
		{
			++amount;
		}
	}
	if (length == amount)
	{
		strarr[0] = NULL;
		return;
	}
	amount = 0;
	for (i = 0; i < length; ++i)
	{
		if (strarr[i] == str)
		{
			delete(strarr[i]);
			++amount;
			continue;
		}
		strarr[i] = strarr[i + amount];
	}
	strarr[i] = NULL;
}
