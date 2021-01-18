
#include "libccc_memory.h"



t_u32		c_ptrarrlen(const void **a_ptrarr)
{
	t_u32		i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_ptrarr == NULL)
		return (0);
#endif
	i = 0;
	while (((void**)a_ptrarr)[i])
	{
		i++;
	}
	return (i);
}
