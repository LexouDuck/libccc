
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/memory.h"
#include "libccc/pointer.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
t_char*	Size_ToString(t_size number)
{
	return (U64_ToString(number));
}



inline
t_char*	Size_ToString_Hex(t_size number)
{
	return (U64_ToString_Hex(number, TRUE));
}



t_char*	Size_ToString_Pretty(t_size number)
{
	static t_char const* units[] = { "B\0", "KB", "MB", "GB", "TB", "PB", "EB" };
	t_uint unit = 0;
	t_float mantissa = (t_float)number;
	while (mantissa >= 1024 && unit < 5)
	{
		unit++;
		mantissa /= 1024;
	}
	return (String_Format("%.2f%s", mantissa, units[unit]));
}
