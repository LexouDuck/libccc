
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_RootN(s_complex const* z, t_u8 n)
{
	if CCCERROR((n == 0), ERROR_MATHDOMAIN,
		"cannot compute the zero-th root of a complex number")
		return (COMPLEX_ERROR);
	if (n == 1)
		return (*z);
	return (Complex_Pow(z, 1. / (t_float)n));
}
