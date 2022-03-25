
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArray_RemoveAt(t_char** strarr, t_uint index)
{
	t_char**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	length = StringArray_Length((t_char const**)strarr);
	HANDLE_ERROR_SF(INDEX2LARGE, (length <= index), return;,
		"index given ("SF_UINT") is beyond end of string array (length: "SF_UINT")",
		index, length)
	length -= 1;
	if (length == 0)
	{
		Memory_Free(strarr);
		strarr = NULL;
		return;
	}
//	result = (t_char const**)String_Allocate(sizeof(t_char const*) * length);
//	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	result = strarr;
	for (t_uint i = index; i < length; ++i)
	{
		result[i] = strarr[i + 1];
	}
//	String_Free(strarr);
//	strarr = result;
}


void	StringArray_RemoveAt_F(t_char** strarr, t_uint index, void (*del)(t_char*))
{
	t_char**	result;
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (del == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	length = StringArray_Length((t_char const**)strarr);
	HANDLE_ERROR_SF(INDEX2LARGE, (length <= index), return;,
		"index given ("SF_UINT") is beyond end of string array (length: "SF_UINT")",
		index, length)
	length -= 1;
	if (length == 0)
	{
		Memory_Free(strarr);
		strarr = NULL;
		return;
	}
//	result = (t_char const**)String_Allocate(length * sizeof(t_char const*));
//	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	result = strarr;
	for (t_uint i = index; i < length; ++i)
	{
		if (i == index)
		{
			del(strarr[i]);
			result[i] = strarr[i + 1];
		}
		else result[i] = strarr[i + 1];
	}
//	String_Free(strarr);
//	strarr = result;
}
