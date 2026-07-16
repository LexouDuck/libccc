
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_octonion	Octonion_Root3(s_octonion const* o)
{
	return (Octonion_Pow(o, 1. / 3.));
}
