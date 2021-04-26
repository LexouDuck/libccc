
#include "libccc/string.h"



inline void	c_strset(t_char* str, t_char c)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return;
#endif
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}
