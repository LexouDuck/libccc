
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



DEFINEFUNC_FLOAT(32)

DEFINEFUNC_FLOAT(64)

#ifdef	__float80
DEFINEFUNC_FLOAT(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT(128)
#endif



t_bool	Float(t_float a, t_float b)
{
	return (CONCAT(TYPE_FLOAT,_Equals)(a, b));
}
