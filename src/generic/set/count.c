
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	Set_Length(T)(s_set(T) const* set)
{
	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (0);
	return (set->length);
}
