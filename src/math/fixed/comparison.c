
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_EQUALS(BITS) \
inline t_bool	F##BITS##_Equals(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a == b);										\
}															\



#define DEFINEFUNC_FLOAT_APPROX(BITS) \
t_bool	F##BITS##_EqualsApprox(t_f##BITS a, t_f##BITS b)	\
{															\
	t_f##BITS abs_a = ABS(a);								\
	t_f##BITS abs_b = ABS(b);								\
	return (ABS(a - b) <= MAX(abs_a, abs_b) * FLOAT_APPROX);\
}															\



DEFINEFUNC_FLOAT_EQUALS(32)
DEFINEFUNC_FLOAT_APPROX(32)

DEFINEFUNC_FLOAT_EQUALS(64)
DEFINEFUNC_FLOAT_APPROX(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_EQUALS(80)
DEFINEFUNC_FLOAT_APPROX(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_EQUALS(128)
DEFINEFUNC_FLOAT_APPROX(128)
#endif
