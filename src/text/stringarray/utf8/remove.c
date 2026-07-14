
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Returns the index of the first string in `strarr` whose content equals `str` (or `ERROR` if absent), without logging
static
t_sint	StringArrayUTF8_Remove_IndexOf(t_utf8 const* const* strarr, t_utf8 const* str)
{
	t_uint	i;

	for (i = 0; strarr[i]; ++i)
	{
		if (StringUTF8_Equals(strarr[i], str))
			return ((t_sint)i);
	}
	return (ERROR);
}



void	StringArrayUTF8_Remove(t_utf8** strarr, t_utf8 const* str)
{
	t_sint	index;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	index = StringArrayUTF8_Remove_IndexOf((t_utf8 const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArrayUTF8_RemoveAt(strarr, (t_uint)index);
}



void	StringArrayUTF8_Remove_F(t_utf8** strarr, t_utf8 const* str, void (*del)(t_utf8*))
{
	t_sint	index;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	index = StringArrayUTF8_Remove_IndexOf((t_utf8 const* const*)strarr, str);
	if (index == ERROR)
		return;
	StringArrayUTF8_RemoveAt_F(strarr, (t_uint)index, del);
}



void	StringArrayUTF8_RemoveAll(t_utf8** strarr, t_utf8 const* str)
{
	t_uint	i;
	t_uint	amount;
	t_uint	length;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER,
		"string given is NULL, which is used for the string array terminator")
		return;
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	if (length == 0)
		return;
	amount = 0;
	for (i = 0; i + amount < length; ++i)
	{
		while (i + amount < length && StringUTF8_Equals(strarr[i + amount], str))
		{
			++amount;
		}
		if (i + amount < length)
			strarr[i] = strarr[i + amount];
	}
	strarr[length - amount] = NULL;
}



void	StringArrayUTF8_RemoveAll_F(t_utf8** strarr, t_utf8 const* str, void (*del)(t_utf8*))
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
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	if (length == 0)
		return;
	amount = 0;
	for (i = 0; i + amount < length; ++i)
	{
		while (i + amount < length && StringUTF8_Equals(strarr[i + amount], str))
		{
			del(strarr[i + amount]);
			++amount;
		}
		if (i + amount < length)
			strarr[i] = strarr[i + amount];
	}
	strarr[length - amount] = NULL;
}
