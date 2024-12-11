
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Pow, pow)
#else
#define DEFINEFUNC_MATH_FLOAT_POW(BITS) \
extern inline t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y)	\
{															\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)			\
		return (NAN);										\
	return (F##BITS##_Exp(y * F##BITS##_Ln(x)));			\
}
// crazy approximate method
#if 0
	u_float_cast result;
	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.value_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
#endif

DEFINEFUNC_MATH_FLOAT_POW(32)
DEFINEFUNC_MATH_FLOAT_POW(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_MATH_FLOAT_POW(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_MATH_FLOAT_POW(128)
#endif

#endif



#define DEFINEFUNC_MATH_FLOAT_INTPOW(BITS) \
t_f##BITS	F##BITS##_IntPow(t_f##BITS x, t_sint n)		\
{														\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)		\
		return (NAN);									\
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
// lame and slow iterative method
#if 0
	t_f##BITS result = 1;
	while (F##BITS##_Abs(n) > FLOAT_APPROX)
	{
		if (F##BITS##_Abs(n & 1) > FLOAT_APPROX)
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
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_MATH_FLOAT_INTPOW(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_MATH_FLOAT_INTPOW(128)
#endif
