
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_Inverse(s_octonion const* o)
{
	t_float	norm_squared = (
		(o->s * o->s) +
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	if CCCERROR((norm_squared == 0.), ERROR_MATHDOMAIN,
		"cannot compute inverse of a zero octonion")
		return (OCTONION_ERROR);
	return ((s_octonion)
	{
		.s = +o->s / norm_squared,
		.i = -o->i / norm_squared,
		.j = -o->j / norm_squared,
		.k = -o->k / norm_squared,
		.l = -o->l / norm_squared,
		.m = -o->m / norm_squared,
		.n = -o->n / norm_squared,
		.o = -o->o / norm_squared,
	});
}

#ifdef __cplusplus
s_octonion	operator ! (s_octonion const o)
{
	return Octonion_Inverse(o);
}
#endif
