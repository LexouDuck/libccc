
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Pow(s_complex const* z, t_float power)
{
	t_float	norm = Complex_Norm(z);
	if (norm == 0.)
	{
		if (power > 0.)
			return (COMPLEX_NULL);
		if (power == 0.)
			return ((s_complex){ .re = 1., .im = 0. });
		if CCCERROR((power < 0.), ERROR_MATHDOMAIN,
			"cannot raise a zero complex number to a negative power")
			return (COMPLEX_ERROR);
	}
	t_float	angle = power * Float_ArcTan2(z->im, z->re);
	t_float	norm_pow = Float_Pow(norm, power);
	return ((s_complex)
	{
		.re = norm_pow * Float_Cos(angle),
		.im = norm_pow * Float_Sin(angle),
	});
}
