
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	sinh(a + bi) = sinh(a)*cos(b) + i*cosh(a)*sin(b)
s_complex	Complex_SinH(s_complex const* z)
{
	return ((s_complex)
	{
		.re = Float_SinH(z->re) * Float_Cos(z->im),
		.im = Float_CosH(z->re) * Float_Sin(z->im),
	});
}
