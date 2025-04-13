
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Normalize(s_complex const* z)
{
	t_float	norm = Complex_Norm(z);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot normalize a zero complex")
		return (COMPLEX_ERROR);
	return ((s_complex)
	{
		.re = z->re / norm,
		.im = z->im / norm,
	});
}
