
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	cosh(a + bi) = cosh(a)*cos(b) + i*sinh(a)*sin(b)
s_complex	Complex_CosH(s_complex const* z)
{
	return ((s_complex)
	{
		.re = Float_CosH(z->re) * Float_Cos(z->im),
		.im = Float_SinH(z->re) * Float_Sin(z->im),
	});
}
