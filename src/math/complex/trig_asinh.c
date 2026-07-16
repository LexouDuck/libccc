
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	asinh(z) = ln(z + sqrt(z^2 + 1))
s_complex	Complex_InvSinH(s_complex const* z)
{
	t_float	a = z->re;
	t_float	b = z->im;
	// sqrt(z^2 + 1)
	t_float	sq_re = (a * a) - (b * b) + 1.;
	t_float	sq_im = 2. * a * b;
	t_float	radius = Float_Root2(sq_re * sq_re + sq_im * sq_im);
	t_float	root_re = Float_Root2((radius + sq_re) * 0.5);
	t_float	root_im = (sq_im < 0. ? -1. : +1.) * Float_Root2((radius - sq_re) * 0.5);
	// w = z + sqrt(z^2 + 1)
	t_float	w_re = a + root_re;
	t_float	w_im = b + root_im;
	// asinh(z) = ln(w) = ln|w| + i*arg(w)
	return ((s_complex)
	{
		.re = Float_Log(Float_Root2(w_re * w_re + w_im * w_im)),
		.im = Float_ArcTan2(w_im, w_re),
	});
}
