
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_sint		Memory_Compare(void const* ptr1, void const* ptr2, t_size n)
{
	t_u8*	p1;
	t_u8*	p2;
	t_size	i;

	p1 = (t_u8*)ptr1;
	p2 = (t_u8*)ptr2;
	if (p1 == p2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (p1 == NULL), return ((p1 - p2));)
	HANDLE_ERROR(NULLPOINTER, (p2 == NULL), return ((p1 - p2));)
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}
