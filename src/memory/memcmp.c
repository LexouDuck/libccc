
#include "libccc_memory.h"



int		c_memcmp(void const *ptr1, void const *ptr2, t_size n)
{
	t_u8	*p1;
	t_u8	*p2;
	t_size	i;

	p1 = (t_u8 *)ptr1;
	p2 = (t_u8 *)ptr2;
#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (ptr1 == NULL || ptr2 == NULL)
	{
		if (ptr1 == ptr2)
			return (0);
		return ((ptr1 == NULL ? 0 : p1[0]) -
				(ptr2 == NULL ? 0 : p2[0]));
	}
#endif
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}
