
#include "libccc_memory.h"
#include "libccc_string.h"



inline void	c_strdel(char **a_str)
{
#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL)
		return ;
#endif
	if (*a_str)
	{
		c_memfree(*a_str);
		*a_str = NULL;
	}
}
