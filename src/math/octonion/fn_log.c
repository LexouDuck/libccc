
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_Log(s_octonion const* o)
{
	t_float	norm = Octonion_Norm(o);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot compute the logarithm of a zero octonion")
		return (OCTONION_ERROR);
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	t_float	angle = Float_ArcTan2(vector_norm, o->s);
	if (vector_norm == 0.)
	{	// real octonion: by convention, use the `i` axis (only matters when `o->s < 0`)
		return ((s_octonion)
		{
			.s = Float_Log(norm),
			.i = angle,
			.j = 0.,
			.k = 0.,
			.l = 0.,
			.m = 0.,
			.n = 0.,
			.o = 0.,
		});
	}
	t_float	factor = angle / vector_norm;
	return ((s_octonion)
	{
		.s = Float_Log(norm),
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
