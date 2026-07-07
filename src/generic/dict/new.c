
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_dict(T)*	Dict_New(T)(void)
{
	s_dict(T)*	result;

	result = (s_dict(T)*)Memory_New(sizeof(s_dict(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	return (result); // an empty (but valid) dictionary
}
