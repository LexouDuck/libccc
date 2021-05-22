
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/pointer.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_size	Size_FromString(t_char const* str)
{
	t_size	result;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	i = 0;
	while (!(str[i] == '+' || Char_IsDigit(str[i])))
	{
		if (!str[i] || !Char_IsSpace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && Char_IsDigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		++i;
	}
	return (result);
}
