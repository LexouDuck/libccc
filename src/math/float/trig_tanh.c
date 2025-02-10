
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



/* tanh(x) = (exp(x) - exp(-x))/(exp(x) + exp(-x))
**         = (exp(2*x) - 1)/(exp(2*x) - 1 + 2)
**         = (1 - exp(-2*x))/(exp(-2*x) - 1 + 2)
*/

t_f32	F32_TanH(t_f32 x)
{
	u_cast_f32 u = {x};
	t_u32 w;
	int sign;
	t_f32 t;

	/* x = |x| */
	sign = u.as_u >> 31;
	u.as_u &= 0x7fffffff;
	x = u.as_f;
	w = u.as_u;

	if (w > 0x3f0c9f54)
	{
		/* |x| > log(3)/2 ~= 0.5493 or nan */
		if (w > 0x41200000)
		{
			/* |x| > 10 */
			t = 1 + 0/x;
		}
		else
		{
			t = F32_Exp(2*x) - 1;
			t = 1 - 2/(t+2);
		}
	}
	else if (w > 0x3e82c578)
	{
		/* |x| > log(5/3)/2 ~= 0.2554 */
		t = F32_Exp(2*x) - 1;
		t = t/(t+2);
	}
	else if (w >= 0x00800000)
	{
		/* |x| >= 0x1p-126 */
		t = F32_Exp(-2*x) - 1;
		t = -t/(t+2);
	}
	else
	{
		/* |x| is subnormal */
		/*FORCE_EVAL(x*x);*/
		t = x;
	}
	return sign ? -t : t;
}

t_f64	F64_TanH(t_f64 x)
{
	u_cast_f64 u = {x};
	t_u32 w;
	int sign;
	t_f64 t;

	/* x = |x| */
	sign = u.as_u >> 63;
	u.as_u &= (t_u64)-1/2;
	x = u.as_f;
	w = u.as_u >> 32;

	if (w > 0x3fe193ea)
	{
		/* |x| > log(3)/2 ~= 0.5493 or nan */
		if (w > 0x40340000)
		{
			/* |x| > 20 or nan */
			/* note: this branch avoids raising overflow */
			t = 1 - 0/x;
		}
		else
		{
			t = F64_Exp(2*x) - 1;
			t = 1 - 2/(t+2);
		}
	}
	else if (w > 0x3fd058ae)
	{
		/* |x| > log(5/3)/2 ~= 0.2554 */
		t = F64_Exp(2*x) - 1;
		t = t/(t+2);
	}
	else if (w >= 0x00100000)
	{
		/* |x| >= 0x1p-1022, up to 2ulp error in [0.1,0.2554] */
		t = F64_Exp(-2*x) - 1;
		t = -t/(t+2);
	}
	else
	{
		/* |x| is subnormal */
		/* note: the branch above would not raise underflow in [0x1p-1023,0x1p-1022) */
		/*FORCE_EVAL((t_f32)x);*/
		t = x;
	}
	return sign ? -t : t;
}

#define DEFINEFUNC_FLOAT_TANH(BITS) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned ex = u.i.se & 0x7fff; \
	unsigned sign = u.i.se & 0x8000; \
	t_u32 w; \
	t_f80 t; \
 \
	/* x = |x| */ \
	u.i.se = ex; \
	x = u.f; \
	w = u.i.m >> 32; \
	if (ex > 0x3ffe || (ex == 0x3ffe && w > 0x8c9f53d5)) \
	{ \
		/* |x| > log(3)/2 ~= 0.5493 or nan */ \
		if (ex >= 0x3fff+5) \
		{ \
			/* |x| >= 32 */ \
			t = 1 + 0/(x + 0x1p-120f); \
		} \
		else \
		{ \
			t = F##BITS##_Exp(2*x) - 1; \
			t = 1 - 2/(t+2); \
		} \
	} \
	else if (ex > 0x3ffd || (ex == 0x3ffd && w > 0x82c577d4)) \
	{ \
		/* |x| > log(5/3)/2 ~= 0.2554 */ \
		t = F##BITS##_Exp(2*x) - 1; \
		t = t/(t+2); \
	} \
	else \
	{ \
		/* |x| is small */ \
		t = F##BITS##_Exp(-2*x) - 1; \
		t = -t/(t+2); \
	} \
	return sign ? -t : t; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TANH(128)
#endif



#endif
