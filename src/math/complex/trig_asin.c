
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	asin(z) = -i*ln(iz + sqrt(1 - z^2))
s_complex	Complex_ArcSin(s_complex const* z)
{
	t_float	a = z->re;
	t_float	b = z->im;
	// w = iz + sqrt(1 - z^2)
	t_float	sq_re = 1. - (a * a) + (b * b);
	t_float	sq_im = -2. * a * b;
	t_float	radius = Float_Root2(sq_re * sq_re + sq_im * sq_im);
	t_float	root_re = Float_Root2((radius + sq_re) * 0.5);
	t_float	root_im = (sq_im < 0. ? -1. : +1.) * Float_Root2((radius - sq_re) * 0.5);
	t_float	w_re = root_re - b;
	t_float	w_im = root_im + a;
	// asin(z) = -i*ln(w) = arg(w) - i*ln|w|
	return ((s_complex)
	{
		.re = +Float_ArcTan2(w_im, w_re),
		.im = -Float_Log(Float_Root2(w_re * w_re + w_im * w_im)),
	});
}
