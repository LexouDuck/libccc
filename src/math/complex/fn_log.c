
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Log(s_complex const* z)
{
	t_float	norm = Complex_Norm(z);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot compute the logarithm of a zero complex number")
		return (COMPLEX_ERROR);
	return ((s_complex)
	{
		.re = Float_Log(norm),
		.im = Float_ArcTan2(z->im, z->re),
	});
}
