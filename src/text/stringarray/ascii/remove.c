
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArrayASCII_Remove(t_char** strarr, t_char const* str)
{
	t_sint	index;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	index = PointerArray_IndexOf((void const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArrayASCII_RemoveAt(strarr, index);
}



void	StringArrayASCII_Remove_F(t_char** strarr, t_char const* str, void (*del)(t_char*))
{
	t_sint	index;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	index = PointerArray_IndexOf((void const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArrayASCII_RemoveAt_F(strarr, index, del);
}



void	StringArrayASCII_RemoveAll(t_char** strarr, t_char const* str)
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	length = StringArrayASCII_Length((t_char const**)strarr);
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



void	StringArrayASCII_RemoveAll_F(t_char** strarr, t_char const* str, void (*del)(t_char*))
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	length = StringArrayASCII_Length((t_char const**)strarr);
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
			del(strarr[i]);
			++amount;
			continue;
		}
		strarr[i] = strarr[i + amount];
	}
	strarr[i] = NULL;
}
