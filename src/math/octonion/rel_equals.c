
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_bool	Octonion_Equals(s_octonion const* o1, s_octonion const* o2)
{
	return (
		(o1->s == o2->s) &&
		(o1->i == o2->i) &&
		(o1->j == o2->j) &&
		(o1->k == o2->k) &&
		(o1->l == o2->l) &&
		(o1->m == o2->m) &&
		(o1->n == o2->n) &&
		(o1->o == o2->o));
}

#ifdef __cplusplus
t_bool	operator == (s_octonion const o1, s_octonion const o2)
{
	return Octonion_Equals(o1, o2);
}
#endif
