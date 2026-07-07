
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Set_Add(T)(s_set(T)* set, T item)
{
	T*	items;
	T*	found;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	found = Set_Find(T)(set, item);
	if (found != NULL)
		return (found); // the item is already contained in the set: nothing to do
	items = (T*)Memory_Reallocate(set->items, (set->length + 1) * sizeof(T));
	if CCCERROR((items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	set->items = items;
	set->items[set->length] = item;
	set->length += 1;
	return (&set->items[set->length - 1]);
}
