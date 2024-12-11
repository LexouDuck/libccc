
#include "libccc/memory.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Ln, log)
#else
#define DEFINEFUNC_FLOAT_LN(BITS) \
/*																							\
	The following pair of functions return the natural logarithm of x.						\
	ln(x) = ln(x*2^n) = n*ln(2) + ln(x) with (1 <= x < 2) and (n = exp_b2)					\
	F##BITS##_EXPONENT_ZERO is exponent bits except the MSB for exponent:					\
	this corresponds precisely to an exponent of zero when unbiased.						\
*/																							\
static																						\
t_f##BITS	F##BITS##_Ln_TaylorSeries(t_f##BITS x)											\
{																							\
	t_f##BITS	result;																		\
	t_f##BITS	result_previous;															\
	t_f##BITS	power;																		\
	t_f##BITS	i;																			\
	/* Taylor series approximation method */												\
	i = 2.;																					\
	power = x;																				\
	result = x;																				\
	result_previous = NAN;																	\
	while (ABS(power) > FLOAT_APPROX)														\
	{																						\
		power *= x;																			\
		result += (((((t_sint)i % 2)) * 2.) - 1.) * (power / i);							\
		if (result == result_previous)														\
			break;																			\
		result_previous = result;															\
		++i;																				\
	}																						\
	return (result);																		\
}																							\
t_f##BITS	F##BITS##_Ln(t_f##BITS x)														\
{																							\
	static const t_f##BITS LN_3_2  = 0x1.9F323ECBF984Cp-2L;									\
	static const t_f##BITS DIV_2_3 = 0x1.5555555555556p-1L;									\
	t_f##BITS	result;																		\
	t_u64	tmp = 0;	/* a raw memory copy */												\
	t_u64	norm = 0;	/* the float x in x*2^n in raw memory */							\
	t_s32	exp_b2;																			\
	/* Taylor series approximation method */												\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)	return (NAN);							\
	if CCCERROR((x < 0.), ERROR_MATHDOMAIN, NULL)	return (NAN);							\
	if (x == 0.)																			\
		return (-INFINITY);																	\
	if (x == 1.)																			\
		return (0.);																		\
	if (x == INFINITY)																		\
		return (INFINITY);																	\
	if (x < 1. || 2. <= x)																	\
	{																						\
		Memory_Copy(&tmp, &x, sizeof(t_f##BITS));											\
		norm = (tmp & F##BITS##_MANTISSA_SIGNED) | F##BITS##_EXPONENT_ZERO;					\
		Memory_Copy(&x, &norm, sizeof(t_f##BITS));											\
		result = F##BITS##_Ln(x);															\
		exp_b2 = ((tmp << 1) >> (F##BITS##_MANTISSA_BITS + 1)) - F##BITS##_EXPONENT_BIAS;	\
		return (LN_2 * exp_b2 + result);													\
	}																						\
	if (1.9 <= x && x < 2.)																	\
		return (F##BITS##_Ln(x * DIV_2_3) + LN_3_2);										\
	result = F##BITS##_Ln_TaylorSeries(x - 1.);												\
	return (result);																		\
}

DEFINEFUNC_FLOAT_LN(32)
DEFINEFUNC_FLOAT_LN(64)
/* TODO fix this
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LN(128)
#endif
*/
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Log2, log2)
#else
#define DEFINEFUNC_FLOAT_LOG2(BITS) \
extern inline t_f##BITS	F##BITS##_Log2(t_f##BITS x)		\
{													\
	return (F##BITS##_Ln(x) / LN_2);				\
}

DEFINEFUNC_FLOAT_LOG2(32)
DEFINEFUNC_FLOAT_LOG2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG2(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Log10, log10)
#else
#define DEFINEFUNC_FLOAT_LOG10(BITS) \
extern inline t_f##BITS	F##BITS##_Log10(t_f##BITS x)	\
{													\
	return (F##BITS##_Ln(x) / LN_10);				\
}

DEFINEFUNC_FLOAT_LOG10(32)
DEFINEFUNC_FLOAT_LOG10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG10(128)
#endif

#endif



#define DEFINEFUNC_FLOAT_LOGN(BITS) \
extern inline t_f##BITS	F##BITS##_LogN(t_f##BITS x, t_f##BITS n)	\
{																\
	if (n == 2)													\
		return (F##BITS##_Log2(x));								\
	else if (n == 10)											\
		return (F##BITS##_Log10(x));							\
	else														\
		return (F##BITS##_Ln(x) / F##BITS##_Ln(n));				\
}

DEFINEFUNC_FLOAT_LOGN(32)
DEFINEFUNC_FLOAT_LOGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOGN(128)
#endif
