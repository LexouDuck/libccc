
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	acosh(z) = ln(z + sqrt(z - 1) * sqrt(z + 1))
s_complex	Complex_InvCosH(s_complex const* z)
{
	t_float	a = z->re;
	t_float	b = z->im;
	// sqrt(z - 1)
	t_float	radius1 = Float_Root2((a - 1.) * (a - 1.) + b * b);
	t_float	root1_re = Float_Root2((radius1 + (a - 1.)) * 0.5);
	t_float	root1_im = (b < 0. ? -1. : +1.) * Float_Root2((radius1 - (a - 1.)) * 0.5);
	// sqrt(z + 1)
	t_float	radius2 = Float_Root2((a + 1.) * (a + 1.) + b * b);
	t_float	root2_re = Float_Root2((radius2 + (a + 1.)) * 0.5);
	t_float	root2_im = (b < 0. ? -1. : +1.) * Float_Root2((radius2 - (a + 1.)) * 0.5);
	// w = z + sqrt(z - 1) * sqrt(z + 1)
	t_float	w_re = a + (root1_re * root2_re - root1_im * root2_im);
	t_float	w_im = b + (root1_re * root2_im + root1_im * root2_re);
	// acosh(z) = ln(w) = ln|w| + i*arg(w)
	return ((s_complex)
	{
		.re = Float_Log(Float_Root2(w_re * w_re + w_im * w_im)),
		.im = Float_ArcTan2(w_im, w_re),
	});
}
