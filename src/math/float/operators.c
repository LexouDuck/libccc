
#include "libccc/float.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_ADD(BITS) \
inline t_f##BITS	F##BITS##_Add(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a + b);											\
}															\



#define DEFINEFUNC_FLOAT_SUB(BITS) \
inline t_f##BITS	F##BITS##_Sub(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a - b);											\
}															\



#define DEFINEFUNC_FLOAT_MUL(BITS) \
inline t_f##BITS	F##BITS##_Mul(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a * b);											\
}															\



#define DEFINEFUNC_FLOAT_DIV(BITS) \
inline t_f##BITS	F##BITS##_Div(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a / b);											\
}															\



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_fabs(t_float x)
{
	u_float_cast	result;

	result.value_float = x;
	if (result.value_int & FLOAT_SIGNED)
	{
		result.value_int &= ~FLOAT_SIGNED;
	}
	return (result.value_float);
}
#else
MATH_DECL_REALFUNCTION(abs, fabs)
#endif



#if LIBCONFIG_USE_FAST_APPROX_MATH
inline
t_float	c_fmod(t_float x, t_float y)
{
	t_float		a;
	t_s64		floor_a;

	a = x / y;
	floor_a = (t_s64)a;
	return ((a - (t_float)floor_a) * y);
}
#else
MATH_DECL_REALOPERATOR(mod, fmod)
#endif

#define DEFINEFUNC_FLOAT_EQUALS(BITS) \
inline t_bool	F##BITS##_Equals(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a == b);										\
}															\



#define DEFINEFUNC_FLOAT_EQUALSAPPROX(BITS) \
t_bool	F##BITS##_EqualsApprox(t_f##BITS a, t_f##BITS b)	\
{															\
	t_f##BITS abs_a = ABS(a);								\
	t_f##BITS abs_b = ABS(b);								\
	return (ABS(a - b) <= MAX(abs_a, abs_b) * FLOAT_APPROX);\
}															\



DEFINEFUNC_FLOAT_ADD(32)
DEFINEFUNC_FLOAT_SUB(32)
DEFINEFUNC_FLOAT_MUL(32)
DEFINEFUNC_FLOAT_DIV(32)
DEFINEFUNC_FLOAT_EQUALS(32)
DEFINEFUNC_FLOAT_EQUALSAPPROX(32)

DEFINEFUNC_FLOAT_ADD(64)
DEFINEFUNC_FLOAT_SUB(64)
DEFINEFUNC_FLOAT_MUL(64)
DEFINEFUNC_FLOAT_DIV(64)
DEFINEFUNC_FLOAT_EQUALS(64)
DEFINEFUNC_FLOAT_EQUALSAPPROX(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_ADD(80)
DEFINEFUNC_FLOAT_SUB(80)
DEFINEFUNC_FLOAT_MUL(80)
DEFINEFUNC_FLOAT_DIV(80)
DEFINEFUNC_FLOAT_EQUALS(80)
DEFINEFUNC_FLOAT_EQUALSAPPROX(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_ADD(128)
DEFINEFUNC_FLOAT_SUB(128)
DEFINEFUNC_FLOAT_MUL(128)
DEFINEFUNC_FLOAT_DIV(128)
DEFINEFUNC_FLOAT_EQUALS(128)
DEFINEFUNC_FLOAT_EQUALSAPPROX(128)
#endif