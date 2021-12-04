
#include "libccc/math/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Pow, pow)
#else
#define DEFINEFUNC_MATH_FLOAT_POW(BITS) \
inline t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y)	\
{															\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)		\
	return (F##BITS##_Exp(y * F##BITS##_Ln(x)));			\
}
#if 0 // crazy approximate method
	u_float_cast result;

	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.v_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
#endif

DEFINEFUNC_MATH_FLOAT_POW(32)
DEFINEFUNC_MATH_FLOAT_POW(64)
#ifdef	__float80
DEFINEFUNC_MATH_FLOAT_POW(80)
#endif
#ifdef	__float128
DEFINEFUNC_MATH_FLOAT_POW(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
// TODO fix this
//MATH_DECL_REALOPERATOR(IntPow, pow)
#else
#define DEFINEFUNC_MATH_FLOAT_INTPOW(BITS) \
t_f##BITS	F##BITS##_IntPow(t_f##BITS x, t_sint n)		\
{														\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)	\
	t_f##BITS	tmp;									\
	if (n == 0)											\
		return (1.);									\
	tmp = F##BITS##_IntPow(x, n / 2);					\
	if ((n % 2) == 0)									\
	{													\
		return (tmp * tmp);								\
	}													\
	else												\
	{													\
		if (n > 0)										\
			return (tmp * tmp * x);						\
		else											\
			return (tmp * tmp / x);						\
	}													\
}
#if 0 // lame and slow iterative method
	t_float result = 1;
	while (c_fabs(n) > FLOAT_APPROX)
	{
		if (c_fabs(n & 1) > FLOAT_APPROX)
		{
			result *= x;
			n -= 1;
		}
		x *= x;
		n /= 2;
	}
	return (result);
#endif

DEFINEFUNC_MATH_FLOAT_INTPOW(32)
DEFINEFUNC_MATH_FLOAT_INTPOW(64)
#ifdef	__float80
DEFINEFUNC_MATH_FLOAT_INTPOW(80)
#endif
#ifdef	__float128
DEFINEFUNC_MATH_FLOAT_INTPOW(128)
#endif

#endif
