
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(TanH, tanh)
#elif LIBCONFIG_USE_CCC_MATH
// fast sigmoid approximation
// score: 0.84 for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_TANH(BITS) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	t_f##BITS n = 1 - 0.37 * (abs_x / (1 + abs_x)); \
	if (n < 0.7) \
		n = 0.7; \
	n -= abs_x / (1 + abs_x); \
	if (n < 0.) \
		n = 0.; \
	return (x / (n + abs_x)); \
} \

// fast sigmoid approximation for [-1,+1], and exponential approximation for the rest
// score: 1.95	for [-6,+6]-> 250 tests
#if 0
	else if (x < -1.)
		return (+F##BITS##_Exp(1.43378091 * x) - 1);
	else if (x > 1.)
		return (-F##BITS##_Exp(-1.43378091 * x) + 1);
	else
		return ((2 * x) / (1.6260705 + F##BITS##_Abs(x)));
#endif

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_TANH(16)
#endif
DEFINEFUNC_FLOAT_TANH(32)

DEFINEFUNC_FLOAT_TANH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TANH(128)
#endif



#else



/* tanh(x)
	= (exp(x) - exp(-x))/(exp(x) + exp(-x))
	= (exp(2*x) - 1)/(exp(2*x) - 1 + 2)
	= (1 - exp(-2*x))/(exp(-2*x) - 1 + 2)
*/

#define DEFINEFUNC_FLOAT_TANH(BITS, CONSTANT, C_0c5493, C_0c2554, C_1p2m1022) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x) \
{ \
	u_cast_f##BITS u = {x}; \
	t_u32 w; \
	int sign; \
	t_f##BITS result; \
	/* x = |x| */ \
	sign = u.as_u >> (BITS - 1); \
	u.as_u &= (~(t_u##BITS)0 >> 1); \
	x = u.as_f; \
	w = u.as_u >> (BITS - 32); \
	if (w > C_0c5493) /* |x| > log(3)/2 ~= 0.5493 or nan */ \
	{ \
		if (w > CONSTANT) /* f32:(|x| > 10) or f64:(|x| > 20) or nan */ \
		{	/* note: this branch avoids raising overflow */ \
			result = 1 - 0/x; \
		} \
		else \
		{ \
			result = F##BITS##_Exp(2*x) - 1; \
			result = 1 - 2 / (result + 2); \
		} \
	} \
	else if (w > C_0c2554) /* |x| > log(5/3)/2 ~= 0.2554 */ \
	{ \
		result = F##BITS##_Exp(2*x) - 1; \
		result = result / (result + 2); \
	} \
	else if (x > 0x1p-41) /* |x| >= 0x1p-1022, up to 2ulp error in [0.1,0.2554] */ \
	{ \
		result = F64_Exp(-2*x) - 1; \
		result = -result / (result + 2); \
	} \
	else if (w >= C_1p2m1022) /* |x| >= 0x1p-1022, up to 2ulp error in [0.1,0.2554] */ \
	{ \
		result = x; \
	} \
	else /* |x| is subnormal */ \
	{	/* note: the branch above would not raise underflow in [0x1p-1023,0x1p-1022) */ \
		/*FORCE_EVAL((t_f32)x);*/ \
		result = x; \
	} \
	return (sign ? -result : result); \
} \

DEFINEFUNC_FLOAT_TANH(32, 0x41200000, 0x3F0C9F54, 0x3E82C578, 0x00800000)
DEFINEFUNC_FLOAT_TANH(64, 0x40340000, 0x3FE193EA, 0x3FD058AE, 0x00100000)



#define DEFINEFUNC_FLOAT_TANH_LD(BITS, CONSTANT, C_0c5493, C_0c2554) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned ex = u.i.se & 0x7FFF; \
	unsigned sign = u.i.se & 0x8000; \
	t_u32 w; \
	t_f80 result; \
 \
	/* x = |x| */ \
	u.i.se = ex; \
	x = u.f; \
	w = u.i.m >> 32; \
	if (ex > 0x3FFE || (ex == 0x3FFE && w > C_0c5493)) /* |x| > log(3)/2 ~= 0.5493 or nan */ \
	{ \
		if (ex >= CONSTANT) /* |x| >= 32 */ \
		{ \
			result = 1 + 0/(x + 0x1p-120f); \
		} \
		else \
		{ \
			result = F##BITS##_Exp(2*x) - 1; \
			result = 1 - 2 / (result + 2); \
		} \
	} \
	else if (ex > 0x3FFD || (ex == 0x3FFD && w > C_0c2554)) /* |x| > log(5/3)/2 ~= 0.2554 */ \
	{ \
		result = F##BITS##_Exp(2*x) - 1; \
		result = result / (result + 2); \
	} \
	else /* |x| is small */ \
	{ \
		result = F##BITS##_Exp(-2*x) - 1; \
		result = -result / (result + 2); \
	} \
	return (sign ? -result : result); \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TANH_LD(80, 0x3FFF+5, 0x8C9F53D5, 0x82C577D4)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TANH_LD(128, 0x3FFF+5, 0x8C9F53D5, 0x82C577D4)
#endif



#endif
