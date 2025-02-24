
#include "libccc/memory.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint		Memory_Compare(void const* ptr1, void const* ptr2, t_size n)
{ return (memcmp(ptr1, ptr2, n)); }
#else
t_sint		Memory_Compare(void const* ptr1, void const* ptr2, t_size n)
{
	t_u8*	p1;
	t_u8*	p2;
	t_size	i;

	p1 = (t_u8*)ptr1;
	p2 = (t_u8*)ptr2;
	if (p1 == p2)
		return (0);
	if CCCERROR((p1 == NULL), ERROR_NULLPOINTER, NULL) return ((p1 - p2));
	if CCCERROR((p2 == NULL), ERROR_NULLPOINTER, NULL) return ((p1 - p2));
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	return (0);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool		Memory_Equals(void const* ptr1, void const* ptr2, t_size n)
{ return (memcmp(ptr1, ptr2, n) == 0); }
#else
t_bool		Memory_Equals(void const* ptr1, void const* ptr2, t_size n)
{
	t_u8*	p1;
	t_u8*	p2;
	t_size	i;

	p1 = (t_u8*)ptr1;
	p2 = (t_u8*)ptr2;
	if (p1 == p2)
		return (0);
	if CCCERROR((p1 == NULL), ERROR_NULLPOINTER, NULL) return ((p1 - p2));
	if CCCERROR((p2 == NULL), ERROR_NULLPOINTER, NULL) return ((p1 - p2));
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (FALSE);
		++i;
	}
	return (TRUE);
}
#endif
