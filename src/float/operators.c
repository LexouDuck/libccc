
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



#define DEFINEFUNC_FLOAT_ADD(BITS) \
inline t_bool	F##BITS##_Add(t_f##BITS a, t_f##BITS b)	\
{														\
	return (a + b);										\
}														\



#define DEFINEFUNC_FLOAT_SUB(BITS) \
inline t_bool	F##BITS##_Sub(t_f##BITS a, t_f##BITS b)	\
{														\
	return (a - b);										\
}														\



#define DEFINEFUNC_FLOAT_MUL(BITS) \
inline t_bool	F##BITS##_Mul(t_f##BITS a, t_f##BITS b)	\
{														\
	return (a * b);										\
}														\



#define DEFINEFUNC_FLOAT_DIV(BITS) \
inline t_bool	F##BITS##_Div(t_f##BITS a, t_f##BITS b)	\
{														\
	return (a / b);										\
}														\



DEFINEFUNC_FLOAT_EQUALS(32)
DEFINEFUNC_FLOAT_ADD(32)
DEFINEFUNC_FLOAT_SUB(32)
DEFINEFUNC_FLOAT_MUL(32)
DEFINEFUNC_FLOAT_DIV(32)

DEFINEFUNC_FLOAT_EQUALS(64)
DEFINEFUNC_FLOAT_ADD(64)
DEFINEFUNC_FLOAT_SUB(64)
DEFINEFUNC_FLOAT_MUL(64)
DEFINEFUNC_FLOAT_DIV(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_EQUALS(80)
DEFINEFUNC_FLOAT_ADD(80)
DEFINEFUNC_FLOAT_SUB(80)
DEFINEFUNC_FLOAT_MUL(80)
DEFINEFUNC_FLOAT_DIV(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_EQUALS(128)
DEFINEFUNC_FLOAT_ADD(128)
DEFINEFUNC_FLOAT_SUB(128)
DEFINEFUNC_FLOAT_MUL(128)
DEFINEFUNC_FLOAT_DIV(128)
#endif




#define TYPE_FLOAT	CONCAT(F,LIBCONFIG_BITS_FLOAT)

t_bool	Float_Equals(t_float a, t_float b)
{
	return (CONCAT(TYPE_FLOAT,_Equals)(a, b));
}
