
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvSinH, asinh)
#elif LIBCONFIG_USE_CCC_MATH
// fast sigmoid approximation for [-20,+20] and natural log for the rest
// score: 9.09	for [-40,+40]-> 200 tests
#define DEFINEFUNC_FLOAT_INVSINH(BITS) \
t_f##BITS	F##BITS##_InvSinH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	else if (x < -20)	return (-F##BITS##_Log(-x - 1) - INV_SQRT_2); \
	else if (x > +20)	return (+F##BITS##_Log(+x - 1) + INV_SQRT_2); \
	else \
		return (x / (1 + F##BITS##_Abs(-0.22103915 * x))); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_INVSINH(16)
#endif
DEFINEFUNC_FLOAT_INVSINH(32)

DEFINEFUNC_FLOAT_INVSINH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVSINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVSINH(128)
#endif



#else

/* asinh(x) = sign(x)*log(|x|+sqrt(x*x+1)) ~= x - x^3/6 + o(x^5) */
/* asinh(x) = sign(x)*log(|x|+sqrt(x*x+1)) ~= x - x^3/6 + o(x^5) */
/* asinh(x) = sign(x)*log(|x|+sqrt(x*x+1)) ~= x - x^3/6 + o(x^5) */

t_f32	F32_InvSinH(t_f32 x)
{
	u_cast_f32 u = {x};
	t_u32 i = u.as_u & 0x7FFFFFFF;
	unsigned s = u.as_u >> 31;

	/* |x| */
	u.as_u = i;
	x = u.as_f;

	if (i >= 0x3F800000 + (12<<23))
	{	/* |x| >= 0x1p12 or inf or nan */
		x = F32_Log(x) + 0.693147180559945309417232121458176568f;
	}
	else if (i >= 0x3F800000 + (1<<23))
	{	/* |x| >= 2 */
		x = F32_Log(2*x + 1/(F32_Root2(x*x+1)+x));
	}
	else if (i >= 0x3F800000 - (12<<23))
	{	/* |x| >= 0x1p-12, up to 1.6ulp error in [0.125,0.5] */
		x = F32_Log(1 + (x + x*x/(F32_Root2(x*x+1)+1)));
	}
	else
	{	/* |x| < 0x1p-12, raise inexact if x!=0 */
		/*FORCE_EVAL(x + 0x1p120f);*/
	}
	return s ? -x : x;
}

t_f64	F64_InvSinH(t_f64 x)
{
	u_cast_f64 u = {x};
	unsigned e = u.as_u >> 52 & 0x7FF;
	unsigned s = u.as_u >> 63;

	/* |x| */
	u.as_u &= (t_u64)-1/2;
	x = u.as_f;

	if (e >= 0x3FF + 26)
	{	/* |x| >= 0x1p26 or inf or nan */
		x = F64_Log(x) + 0.693147180559945309417232121458176568;
	}
	else if (e >= 0x3FF + 1)
	{	/* |x| >= 2 */
		x = F64_Log(2*x + 1/(F64_Root2(x*x+1)+x));
	}
	else if (e >= 0x3FF - 26)
	{	/* |x| >= 0x1p-26, up to 1.6ulp error in [0.125,0.5] */
		x = F64_Log(1 + (x + x*x/(F64_Root2(x*x+1)+1)));
	}
	else
	{	/* |x| < 0x1p-26, raise inexact if x != 0 */
		/*FORCE_EVAL(x + 0x1p120f);*/
	}
	return s ? -x : x;
}

#if LIBCONFIG_USE_FLOAT80
t_f80	F80_InvSinH(t_f80 x)
{
	union ldshape u = {x};
	unsigned e = u.i.se & 0x7FFF;
	unsigned s = u.i.se >> 15;

	/* |x| */
	u.i.se = e;
	x = u.f;

	if (e >= 0x3FFF + 32)
	{	/* |x| >= 0x1p32 or inf or nan */
		x = F80_Log(x) + 0.693147180559945309417232121458176568L;
	}
	else if (e >= 0x3FFF + 1)
	{	/* |x| >= 2 */
		x = F80_Log(2*x + 1/(F80_Root2(x*x+1)+x));
	}
	else if (e >= 0x3FFF - 32)
	{	/* |x| >= 0x1p-32 */
		x = F80_Log(1 + (x + x*x/(F80_Root2(x*x+1)+1)));
	}
	else
	{	/* |x| < 0x1p-32, raise inexact if x!=0 */
		/*FORCE_EVAL(x + 0x1p120f);*/
	}
	return s ? -x : x;
}
#endif

#if LIBCONFIG_USE_FLOAT128
t_f128	F128_InvSinH(t_f128 x)
{
	union ldshape u = {x};
	unsigned e = u.i.se & 0x7FFF;
	unsigned s = u.i.se >> 15;

	/* |x| */
	u.i.se = e;
	x = u.f;

	if (e >= 0x3FFF + 32)
	{	/* |x| >= 0x1p32 or inf or nan */
		x = F128_Log(x) + 0.693147180559945309417232121458176568L;
	}
	else if (e >= 0x3FFF + 1)
	{	/* |x| >= 2 */
		x = F128_Log(2*x + 1/(F128_Root2(x*x+1)+x));
	}
	else if (e >= 0x3FFF - 32)
	{	/* |x| >= 0x1p-32 */
		x = F128_Log(1 + (x + x*x/(F128_Root2(x*x+1)+1)));
	}
	else
	{	/* |x| < 0x1p-32, raise inexact if x!=0 */
		/*FORCE_EVAL(x + 0x1p120f);*/
	}
	return s ? -x : x;
}
#endif



#endif
