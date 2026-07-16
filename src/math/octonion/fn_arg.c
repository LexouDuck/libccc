
#include "libccc/math/octonion.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float	Octonion_Arg(s_octonion const* o)
{
	t_float	vector_norm = Float_Root2(
		(o->i * o->i) +
		(o->j * o->j) +
		(o->k * o->k) +
		(o->l * o->l) +
		(o->m * o->m) +
		(o->n * o->n) +
		(o->o * o->o));
	if CCCERROR((o->s == 0. && vector_norm == 0.), ERROR_MATHDOMAIN,
		"cannot compute the argument of a zero octonion")
		return (NAN);
	return (Float_ArcTan2(vector_norm, o->s));
}
