
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_Normalize(s_octonion const* o)
{
	t_float	norm = Octonion_Norm(o);
	if CCCERROR((norm == 0.), ERROR_MATHDOMAIN,
		"cannot normalize a zero octonion")
		return (OCTONION_ERROR);
	return ((s_octonion)
	{
		.s = o->s / norm,
		.i = o->i / norm,
		.j = o->j / norm,
		.k = o->k / norm,
		.l = o->l / norm,
		.m = o->m / norm,
		.n = o->n / norm,
		.o = o->o / norm,
	});
}
