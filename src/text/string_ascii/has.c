
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool		String_Has(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;
	t_size	c;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (FALSE);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (FALSE);
	i = 0;
	while (str[i])
	{
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
				return (TRUE);
			++c;
		}
		++i;
	}
	return (FALSE);
}



t_bool		String_HasOnly(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;
	t_size	c;
	t_bool	match;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (FALSE);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (FALSE);
	i = 0;
	while (str[i])
	{
		match = FALSE;
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
			{
				match = TRUE;
				break;
			}
			++c;
		}
		if (match == FALSE)
			return (FALSE);
		++i;
	}
	return (TRUE);
}
