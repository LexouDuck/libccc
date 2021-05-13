
#include "libccc/memory.h"



t_sint		Memory_Compare(void const* ptr1, void const* ptr2, t_size n)
{
	t_u8*	p1;
	t_u8*	p2;
	t_size	i;

	p1 = (t_u8*)ptr1;
	p2 = (t_u8*)ptr2;
	if (p1 == p2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER((p1 - p2), p1)
	LIBCONFIG_HANDLE_NULLPOINTER((p1 - p2), p2)
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}
