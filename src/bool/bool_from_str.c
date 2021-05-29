
#include "libccc/char.h"
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_bool	Bool_FromString(t_char const* str)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (FALSE);)
	i = 0;
	while (str[i] && Char_IsSpace(str[i]))
		++i;
	if (!str[i])
		return (FALSE);
	if (Char_IsDigit(str[i]) && S64_FromString(str + i))
		return (TRUE);
	if ((str[i + 0] == 'T' || str[i + 0] == 't') &&
		(str[i + 1] == 'R' || str[i + 1] == 'r') &&
		(str[i + 2] == 'U' || str[i + 2] == 'u') &&
		(str[i + 3] == 'E' || str[i + 3] == 'e'))
		return (TRUE);
	return (FALSE);
}
