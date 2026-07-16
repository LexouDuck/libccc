
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any octonion `o = a + v` (with `v` its vector part, of norm `b`),
**	`o` behaves like the complex number `a + bi` within the plane spanned by `{1, v/b}`, so:
**	tan(a + v) = (sin(2a) + (v/b)*sinh(2b)) / (cos(2a) + cosh(2b))
*/
s_octonion	Octonion_Tan(s_octonion const* o)
{
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	t_float	denominator = Float_Cos(2. * o->s) + Float_CosH(2. * vector_norm);
	t_float	factor = (vector_norm == 0. ? 0. :
		Float_SinH(2. * vector_norm) / (vector_norm * denominator));
	return ((s_octonion)
	{
		.s = Float_Sin(2. * o->s) / denominator,
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
