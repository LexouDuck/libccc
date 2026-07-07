
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Removes the item at the given `index` by moving the last item into its slot
/*!
**	NOTE: a set is unordered, so a removal is done by simply moving the last
**	item into the removed slot (and shrinking the buffer by one item).
**	NOTE: this static helper is named with an explicit `CONCAT` (rather than
**	being declared in "set.h"), since it is internal to this file only.
*/
#define Set_RemoveAtIndex	CONCAT(__Set_RemoveAtIndex_, T_NAME)
static void	Set_RemoveAtIndex(s_set(T)* set, t_uint index)
{
	T*	items;

	set->items[index] = set->items[set->length - 1];
	set->length -= 1;
	if (set->length == 0)
	{
		Memory_Free(set->items);
		set->items = NULL;
	}
	else
	{
		items = (T*)Memory_Reallocate(set->items, set->length * sizeof(T));
		if (items != NULL) // NOTE: if shrinking fails, the set simply keeps its old (larger) buffer
			set->items = items;
	}
}



_GENERIC()
s_set(T)*	Set_Remove(T)(s_set(T)* set, T item)
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		if (T_EQUALS(set->items[i], item))
			break;
	}
	if (i == set->length)
		return (set); // the item is not contained in the set: nothing to do
	Set_RemoveAtIndex(set, i);
	return (set);
}



_GENERIC()
s_set(T)*	Set_Remove_F(T)(s_set(T)* set, T item, void (*del)(T item))
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		if (T_EQUALS(set->items[i], item))
			break;
	}
	if (i == set->length)
		return (set); // the item is not contained in the set: nothing to do
	// NOTE: `del` must be called before the removal, but the item must not be
	// compared again afterwards (`T_EQUALS()` could dereference the deleted item)
	del(set->items[i]);
	Set_RemoveAtIndex(set, i);
	return (set);
}


#undef Set_RemoveAtIndex
