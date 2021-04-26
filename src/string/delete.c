
#include "libccc/memory.h"
#include "libccc/string.h"



inline void	c_strdel(t_char* *a_str)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL)
		return;
#endif
	if (*a_str)
	{
		c_memfree(*a_str);
		*a_str = NULL;
	}
}
