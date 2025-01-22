
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvCosH, acosh)
#elif LIBCONFIG_USE_CCC_MATH
// fast sqrt approximation for [+1,+20] and natural log for the rest
// score: 5.00	for [+1,+50]-> 250 tests
#define DEFINEFUNC_FLOAT_INVCOSH(BITS) \
t_f##BITS	F##BITS##_InvCosH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((x < 1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if (x < 20) \
		return (1.37 * F##BITS##_Root2(x - 1) - 0.122 * (x - 1)); \
	else \
		return (F##BITS##_Log(x - 1) + INV_SQRT_2); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_INVCOSH(16)
#endif
DEFINEFUNC_FLOAT_INVCOSH(32)

DEFINEFUNC_FLOAT_INVCOSH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVCOSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVCOSH(128)
#endif



#else



/* acosh(x) = log(x + sqrt(x*x-1)) */
/* acosh(x) = log(x + sqrt(x*x-1)) */
/* acosh(x) = log(x + sqrt(x*x-1)) */

	/* x < 1 domain error is handled in the called functions */

t_f32	F32_InvCosH(t_f32 x)
{
	union {t_f32 f; t_u32 i;} u = {x};
	int e = (u.i & F32_EXPONENT_MASK) >> F32_MANTISSA_BITS;

	if (e & (1 << F32_EXPONENT_BITS))
		/* x < 0 or x = -0, invalid */
		return (x - x) / (x - x);
	if (e < (F32_EXPONENT_ZERO >> F32_MANTISSA_BITS) + 1)
		/* |x| < 2, invalid if x < 1, up to 2ulp error in [1,1.125] */
		return F32_Log(1 + (x-1 + F32_Root2((x-1)*(x-1)+2*(x-1))));
	if (e < (F32_EXPONENT_ZERO >> F32_MANTISSA_BITS) + 12)
		/* 2 <= x < 0x1p12 */
		return F32_Log(2*x - 1/(x+F32_Root2(x*x-1)));
	/* x >= 0x1p12 or x <= -2 or nan */
	return F32_Log(x) + 0.693147180559945309417232121458176568f;
}

t_f64	F64_InvCosH(t_f64 x)
{
	union {t_f64 f; t_u64 i;} u = {x};
	int e = (u.i & F64_EXPONENT_MASK) >> F64_MANTISSA_BITS;

	if (x < 0) // if (e & (1 << F64_EXPONENT_BITS))
		/* x < 0 or x = -0, invalid */
		return (x - x) / (x - x);
	if (e < (F64_EXPONENT_ZERO >> F64_MANTISSA_BITS) + 1)
		/* |x| < 2, up to 2ulp error in [1,1.125] */
		return F64_Log(1 + (x - 1 + F64_Root2((x - 1) * (x - 1) + 2 * (x - 1))));
	if (e < (F64_EXPONENT_ZERO >> F64_MANTISSA_BITS) + 26)
		/* |x| < 0x1p26 */
		return F64_Log(2 * x - 1 / (x + F64_Root2(x * x - 1)));
	/* |x| >= 0x1p26 or nan */
	return F64_Log(x) + 0.693147180559945309417232121458176568;
}

#if LIBCONFIG_USE_FLOAT80
t_f80	F80_InvCosH(t_f80 x)
{
	union ldshape u = {x};
	int e = u.i.se;

	if (e & (1 << F80_EXPONENT_BITS))
		/* x < 0 or x = -0, invalid */
		return (x - x) / (x - x);
	if (e < (F80_EXPONENT_ZERO >> F80_MANTISSA_BITS) + 1)
		/* 0 <= x < 2, invalid if x < 1 */
		return F80_Log(1 + (x-1 + F80_Root2((x-1)*(x-1)+2*(x-1))));
	if (e < (F80_EXPONENT_ZERO >> F80_MANTISSA_BITS) + 32)
		/* 2 <= x < 0x1p32 */
		return F80_Log(2*x - 1/(x+F80_Root2(x*x-1)));
	/* 0x1p32 <= x or nan */
	return F80_Log(x) + 0.693147180559945309417232121458176568L;
}
#endif

#if LIBCONFIG_USE_FLOAT128
t_f128	F128_InvCosH(t_f128 x)
{
	union ldshape u = {x};
	int e = u.i.se;

	if (e & (1 << F128_EXPONENT_BITS))
		/* x < 0 or x = -0, invalid */
		return (x - x) / (x - x);
	if (e < (F128_EXPONENT_ZERO >> F128_MANTISSA_BITS) + 1)
		/* 0 <= x < 2, invalid if x < 1 */
		return F128_Log(1 + (x-1 + F128_Root2((x-1)*(x-1)+2*(x-1))));
	if (e < (F128_EXPONENT_ZERO >> F128_MANTISSA_BITS) + 32)
		/* 2 <= x < 0x1p32 */
		return F128_Log(2*x - 1/(x+F128_Root2(x*x-1)));
	/* 0x1p32 <= x or nan */
	return F128_Log(x) + 0.693147180559945309417232121458176568L;
}
#endif



#endif
