/*============================================================================*\
||                                            ______________________________  ||
||  src/text/regex/delete.c                  |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#include "libccc/memory.h"
#include "libccc/text/regex.h"

#include "regex_private.h"

#include LIBCONFIG_ERROR_INCLUDE



void	Regex_Delete(s_regex* *a_regex)
{
	s_regex*		regex;
	s_rxcompiled*	compiled;
	t_uint			i;

	if CCCERROR((a_regex == NULL), ERROR_NULLPOINTER, "regex address given is NULL")
		return;
	regex = *a_regex;
	if (regex == NULL)
		return;
	if (regex->pattern)
		Memory_Free(regex->pattern);
	if (regex->names)
	{
		for (i = 0; i < regex->groups; ++i)
		{
			if (regex->names[i])
				Memory_Free(regex->names[i]);
		}
		Memory_Free(regex->names);
	}
	compiled = (s_rxcompiled*)regex->compiled;
	if (compiled)
	{
		RX_DeleteAST(compiled->allocs);
		Memory_Free(compiled);
	}
	Memory_Free(regex);
	*a_regex = NULL;
}
