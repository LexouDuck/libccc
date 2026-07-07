
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Set_Iterate(T)(s_set(T)* set, void (*f)(T item))
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return;
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	for (i = 0; i < set->length; ++i)
	{
		f(set->items[i]);
	}
}



_GENERIC()
void	Set_Iterate_I(T)(s_set(T)* set, void (*f)(T item, t_uint index))
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return;
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	for (i = 0; i < set->length; ++i)
	{
		f(set->items[i], i);
	}
}
