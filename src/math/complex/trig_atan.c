
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	atan(z) = -(i/2)*ln((1 + iz) / (1 - iz))
s_complex	Complex_ArcTan(s_complex const* z)
{
	t_float	a = z->re;
	t_float	b = z->im;
	// w = (1 + iz) / (1 - iz)
	t_float	num_re = 1. - b;
	t_float	num_im = +a;
	t_float	den_re = 1. + b;
	t_float	den_im = -a;
	t_float	den_norm = (den_re * den_re) + (den_im * den_im);
	t_float	w_re = (num_re * den_re + num_im * den_im) / den_norm;
	t_float	w_im = (num_im * den_re - num_re * den_im) / den_norm;
	// atan(z) = -(i/2)*ln(w) = arg(w)/2 - (i/2)*ln|w|
	return ((s_complex)
	{
		.re = +Float_ArcTan2(w_im, w_re) * 0.5,
		.im = -Float_Log(Float_Root2(w_re * w_re + w_im * w_im)) * 0.5,
	});
}
