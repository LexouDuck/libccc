
#include "libccc/memory.h"
#include "libccc/text/format.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArrayUTF8_RemoveAt(t_utf8** strarr, t_uint index)
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	if CCCERROR((length <= index), ERROR_INDEX2LARGE,
		"index given (" SF_UINT ") is beyond end of string array (length: " SF_UINT ")",
		index, length)
		return;
	for (i = index; i < length; ++i)
	{	// NB: this also shifts the `NULL` terminator into place
		strarr[i] = strarr[i + 1];
	}
}



void	StringArrayUTF8_RemoveAt_F(t_utf8** strarr, t_uint index, void (*del)(t_utf8*))
{
	t_uint	length;
	t_uint	i;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	length = StringArrayUTF8_Length((t_utf8 const* const*)strarr);
	if CCCERROR((length <= index), ERROR_INDEX2LARGE,
		"index given (" SF_UINT ") is beyond end of string array (length: " SF_UINT ")",
		index, length)
		return;
	del(strarr[index]);
	for (i = index; i < length; ++i)
	{	// NB: this also shifts the `NULL` terminator into place
		strarr[i] = strarr[i + 1];
	}
}
