
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArrayUTF8_Iterate(t_utf8** strarr,
	t_utf8* (*f)(t_utf8* str))
{
	t_utf8*	tmp;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	i = 0;
	while (strarr[i])
	{
		tmp = f(strarr[i]);
		if (tmp != strarr[i])
			StringUTF8_Delete(strarr + i);
		strarr[i] = tmp;
		++i;
	}
}



void	StringArrayUTF8_Iterate_I(t_utf8** strarr,
	t_utf8* (*f)(t_utf8* str, t_uint index))
{
	t_utf8*	tmp;
	t_uint	i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	i = 0;
	while (strarr[i])
	{
		tmp = f(strarr[i], i);
		if (tmp != strarr[i])
			StringUTF8_Delete(strarr + i);
		strarr[i] = tmp;
		++i;
	}
}
