
#include "libccc/int.h"
#include "libccc/pointer.h"



inline
char*	Pointer_ToString(void const* ptr)
{
	return (U64_ToString((t_uintptr)ptr));
}



inline
char*	Pointer_ToString_Hex(void const* ptr)
{
	return (U64_ToString_Hex((t_uintptr)ptr));
}
