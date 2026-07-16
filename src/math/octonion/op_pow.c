
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_Pow(s_octonion const* o, t_float power)
{
	t_float	norm = Octonion_Norm(o);
	if (norm == 0.)
	{
		if (power > 0.)
			return (OCTONION_NULL);
		if (power == 0.)
			return ((s_octonion){ .s = 1., .i = 0., .j = 0., .k = 0. });
		if CCCERROR((power < 0.), ERROR_MATHDOMAIN,
			"cannot raise a zero octonion to a negative power")
			return (OCTONION_ERROR);
	}
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	t_float	angle = power * Float_ArcTan2(vector_norm, o->s);
	t_float	norm_pow = Float_Pow(norm, power);
	t_float	scal = norm_pow * Float_Cos(angle);
	t_float	vect = norm_pow * Float_Sin(angle);
	if (vector_norm == 0.)
	{	// real octonion: by convention, use the `i` axis (only matters when `o->s < 0`)
		return ((s_octonion)
		{
			.s = scal,
			.i = vect,
			.j = 0.,
			.k = 0.,
			.l = 0.,
			.m = 0.,
			.n = 0.,
			.o = 0.,
		});
	}
	t_float	factor = vect / vector_norm;
	return ((s_octonion)
	{
		.s = scal,
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
