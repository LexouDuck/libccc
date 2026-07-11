/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/info.c                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#include "libccc/text/regex.h"
#include "libccc/text/string/utf8.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	Regex_GetGroupAmount(s_regex const* regex)
{
	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (0);
	return (regex->groups);
}

t_utf8 const*	Regex_GetGroupName(s_regex const* regex, t_uint index)
{
	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (NULL);
	if (index == 0 || index > regex->groups || regex->names == NULL)
		return (NULL);
	return (regex->names[index - 1]);
}

t_sint	Regex_GetGroupIndex(s_regex const* regex, t_utf8 const* name)
{
	t_uint	i;

	if CCCERROR((regex == NULL), ERROR_NULLPOINTER, "regex given is NULL")
		return (ERROR);
	if CCCERROR((name == NULL), ERROR_NULLPOINTER, "group name given is NULL")
		return (ERROR);
	if (regex->names == NULL)
		return (ERROR);
	for (i = 0; i < regex->groups; ++i)
	{
		if (regex->names[i] && StringUTF8_Equals(regex->names[i], name))
			return ((t_sint)(i + 1));
	}
	return (ERROR);
}
