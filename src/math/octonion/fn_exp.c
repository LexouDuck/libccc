
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_octonion	Octonion_Exp(s_octonion const* o)
{
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	t_float	exp_s = Float_Exp(o->s);
	t_float	factor = (vector_norm == 0. ? exp_s :
		exp_s * Float_Sin(vector_norm) / vector_norm);
	return ((s_octonion)
	{
		.s = exp_s * Float_Cos(vector_norm),
		.i = o->i * factor,
		.j = o->j * factor,
		.k = o->k * factor,
		.l = o->l * factor,
		.m = o->m * factor,
		.n = o->n * factor,
		.o = o->o * factor,
	});
}
