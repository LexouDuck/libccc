
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	tan(a + bi) = (sin(2a) + i*sinh(2b)) / (cos(2a) + cosh(2b))
s_complex	Complex_Tan(s_complex const* z)
{
	t_float	denominator = Float_Cos(2. * z->re) + Float_CosH(2. * z->im);
	return ((s_complex)
	{
		.re = Float_Sin (2. * z->re) / denominator,
		.im = Float_SinH(2. * z->im) / denominator,
	});
}
