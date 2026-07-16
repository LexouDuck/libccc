
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_RootN(s_octonion const* o, t_u8 n)
{
	if CCCERROR((n == 0), ERROR_MATHDOMAIN,
		"cannot compute the zero-th root of a octonion")
		return (OCTONION_ERROR);
	if (n == 1)
		return (*o);
	return (Octonion_Pow(o, 1. / (t_float)n));
}
