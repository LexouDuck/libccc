
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_bool		String_Has(t_char const* str, t_char const* charset)
{
	t_size	i;
	t_size	c;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (FALSE);)
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



t_bool		String_HasOnly(t_char const* str, t_char const* charset)
{
	t_size	i;
	t_size	c;
	t_bool	match;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (FALSE);)
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
