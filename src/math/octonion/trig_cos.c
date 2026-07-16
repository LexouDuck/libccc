
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	For any octonion `o = a + v` (with `v` its vector part, of norm `b`),
**	`o` behaves like the complex number `a + bi` within the plane spanned by `{1, v/b}`, so:
**	cos(a + v) = cos(a)*cosh(b) - (v/b)*sin(a)*sinh(b)
*/
s_octonion	Octonion_Cos(s_octonion const* o)
{
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	t_float	factor = (vector_norm == 0. ? 0. :
		-Float_Sin(o->s) * Float_SinH(vector_norm) / vector_norm);
	return ((s_octonion)
	{
		.s = Float_Cos(o->s) * Float_CosH(vector_norm),
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
