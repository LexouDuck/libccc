
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	atanh(z) = (1/2)*ln((1 + z) / (1 - z))
s_complex	Complex_InvTanH(s_complex const* z)
{
	t_float	a = z->re;
	t_float	b = z->im;
	// w = (1 + z) / (1 - z)
	t_float	num_re = 1. + a;
	t_float	num_im = +b;
	t_float	den_re = 1. - a;
	t_float	den_im = -b;
	t_float	den_norm = (den_re * den_re) + (den_im * den_im);
	t_float	w_re = (num_re * den_re + num_im * den_im) / den_norm;
	t_float	w_im = (num_im * den_re - num_re * den_im) / den_norm;
	// atanh(z) = ln(w)/2 = ln|w|/2 + (i/2)*arg(w)
	return ((s_complex)
	{
		.re = Float_Log(Float_Root2(w_re * w_re + w_im * w_im)) * 0.5,
		.im = Float_ArcTan2(w_im, w_re) * 0.5,
	});
}
