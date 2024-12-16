
#include "libccc/int.h"
#include "libccc/pointer.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_char*	Pointer_ToString(void const* ptr)
{
	return (U64_ToString((t_uintptr)ptr));
}



_INLINE()
t_char*	Pointer_ToString_Hex(void const* ptr)
{
	return (U64_ToString_Hex((t_uintptr)ptr, TRUE));
}
