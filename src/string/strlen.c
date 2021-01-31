
#include "libccc/string.h"



inline t_size	c_strlen(char const *str)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (str[i])
		++i;
	return (i);
}
