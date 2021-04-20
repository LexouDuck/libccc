
#include <float.h> // TODO remove this after changing FLOAT_EPSILON macros

#include "libccc/float.h"
#include "libccc/math/math.h"



#define DEFINEFUNC_FLOAT_EQUALS(BITS) \
t_bool	F##BITS##_Equals(t_f##BITS a, t_f##BITS b)					\
{																	\
	t_f##BITS abs_a = ABS(a);										\
	t_f##BITS abs_b = ABS(b);										\
	return (ABS(a - b) <= MAX(abs_a, abs_b) * F##BITS##_EPSILON);	\
}																	\


DEFINEFUNC_FLOAT_EQUALS(32)
DEFINEFUNC_FLOAT_EQUALS(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_EQUALS(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_EQUALS(128)
#endif




#define TYPE_FLOAT	CONCAT(F,LIBCONFIG_BITS_FLOAT)

t_bool	Float_Equals(t_float a, t_float b)
{
	return (CONCAT(TYPE_FLOAT,_Equals)(a, b));
}
