
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/pointer.h"



t_bool	Bool_FromString(char const* str)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (FALSE);
#endif
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
