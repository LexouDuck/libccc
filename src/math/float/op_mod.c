
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Mod, fmod)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_MOD(BITS) \
t_f##BITS	F##BITS##_Mod(t_f##BITS x, t_f##BITS y) \
{ \
	t_f##BITS abs_a; \
	t_f##BITS abs_b; \
	t_f##BITS dividend; \
	t_f##BITS divisor; \
	t_s64 expo_a; \
	t_s64 expo_b; \
	if CCCERROR((IS_NAN(x) || IS_NAN(y)), ERROR_NANARGUMENT, NULL) \
		return (x + y); \
	if CCCERROR((IS_INF(x) || (y == 0.)), ERROR_MATHDOMAIN, NULL) \
		return (F##BITS##_ERROR); \
	abs_a = F##BITS##_Abs(x); \
	abs_b = F##BITS##_Abs(y); \
	if (abs_a >= abs_b) \
	{ \
		dividend = abs_a; \
		expo_a = F##BITS##_GetExp2(abs_a); \
		expo_b = F##BITS##_GetExp2(abs_b); \
		divisor = F##BITS##_From(abs_b, expo_a - expo_b); \
		if (divisor <= dividend * 0.5) \
		{ \
			divisor += divisor; \
		} \
		while (divisor >= abs_b) \
		{ \
			if (dividend >= divisor) \
			{ \
				dividend -= divisor; \
			} \
			divisor *= 0.5; \
		} \
		return (F##BITS##_CopySign(dividend, x)); \
	} \
	else \
	{ \
		return (x); \
	} \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_MOD(16)
#endif
DEFINEFUNC_FLOAT_MOD(32)

DEFINEFUNC_FLOAT_MOD(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_MOD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_MOD(128)
#endif



#else

#define DEFINEFUNC_FLOAT_MOD(BITS) \
t_f##BITS	F##BITS##_Mod(t_f##BITS x, t_f##BITS y) \
{ \
	union { t_f##BITS f; t_u##BITS i; } ux = {x}, uy = {y}; \
	int ex = (ux.i & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS; \
	int ey = (uy.i & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS; \
	t_u##BITS sx = ux.i & F##BITS##_SIGN_BIT_MASK; \
	t_u##BITS uxi = ux.i; /* `uxi` should be `ux.i`, but then gcc wrongly adds float load/store to inner loops ruining performance and code size */ \
	t_u##BITS i; \
 \
	if (uy.i << 1 == 0 || ex == 0xff || F##BITS##_IsNaN(x) || F##BITS##_IsNaN(y) || F##BITS##_IsInf(x)) \
		return (x * y) / (x * y); \
	if (uxi << 1 <= uy.i << 1) \
	{ \
		if (uxi << 1 == uy.i << 1) \
			return (0 * x); \
		return (x); \
	} \
	/* normalize x and y */ \
	if (!ex) \
	{ \
		for (i = uxi << (F##BITS##_EXPONENT_BITS + 1); i >> (BITS - 1) == 0; ex--, i <<= 1); \
		uxi <<= -ex + 1; \
	} \
	else \
	{ \
		uxi &= -(t_u##BITS)1 >> (F##BITS##_EXPONENT_BITS + 1); \
		uxi |= (t_u##BITS)1 << F##BITS##_MANTISSA_BITS; \
	} \
	if (!ey) \
	{ \
		for (i = uy.i << (F##BITS##_EXPONENT_BITS + 1); i >> (BITS - 1) == 0; ey--, i <<= 1); \
		uy.i <<= -ey + 1; \
	} \
	else \
	{ \
		uy.i &= -(t_u##BITS)1 >> (F##BITS##_EXPONENT_BITS + 1); \
		uy.i |= (t_u##BITS)1 << F##BITS##_MANTISSA_BITS; \
	} \
	/* x mod y */ \
	for (; ex > ey; ex--) \
	{ \
		i = uxi - uy.i; \
		if (i >> (BITS - 1) == 0) \
		{ \
			if (i == 0) \
				return (0 * x); \
			uxi = i; \
		} \
		uxi <<= 1; \
	} \
	i = uxi - uy.i; \
	if (i >> (BITS - 1) == 0) \
	{ \
		if (i == 0) \
			return (0 * x); \
		uxi = i; \
	} \
	for (; uxi>>F##BITS##_MANTISSA_BITS == 0; uxi <<= 1, ex--); \
	/* scale result up */ \
	if (ex > 0) \
	{ \
		uxi -= (t_u##BITS)1 << F##BITS##_MANTISSA_BITS; \
		uxi |= (t_u##BITS)ex << F##BITS##_MANTISSA_BITS; \
	} \
	else \
	{ \
		uxi >>= -ex + 1; \
	} \
	uxi |= sx; \
	ux.i = uxi; \
	return (ux.f); \
} \

DEFINEFUNC_FLOAT_MOD(32)
DEFINEFUNC_FLOAT_MOD(64)



#if LIBCONFIG_USE_FLOAT80
t_f80	F80_Mod(t_f80 x, t_f80 y)
{
	union ldshape ux = {x}, uy = {y};
	int ex = ux.i.se & 0x7fff;
	int ey = uy.i.se & 0x7fff;
	int sx = ux.i.se & 0x8000;

	if (y == 0 || isnan(y) || ex == 0x7fff)
		return (x*y)/(x*y);
	ux.i.se = ex;
	uy.i.se = ey;
	if (ux.f <= uy.f)
	{
		if (ux.f == uy.f)
			return 0*x;
		return x;
	}
	/* normalize x and y */
	if (!ex)
	{
		ux.f *= 0x1p120f;
		ex = ux.i.se - 120;
	}
	if (!ey)
	{
		uy.f *= 0x1p120f;
		ey = uy.i.se - 120;
	}
	/* x mod y */
	t_u64 i, mx, my;
	mx = ux.i.m;
	my = uy.i.m;
	for (; ex > ey; ex--)
	{
		i = mx - my;
		if (mx >= my)
		{
			if (i == 0)
				return 0*x;
			mx = 2*i;
		}
		else if (2*mx < mx)
		{
			mx = 2*mx - my;
		}
		else
		{
			mx = 2*mx;
		}
	}
	i = mx - my;
	if (mx >= my)
	{
		if (i == 0)
			return 0*x;
		mx = i;
	}
	for (; mx >> 63 == 0; mx *= 2, ex--);
	ux.i.m = mx;
	/* scale result */
	if (ex <= 0)
	{
		ux.i.se = (ex+120)|sx;
		ux.f *= 0x1p-120f;
	}
	else
		ux.i.se = ex|sx;
	return ux.f;
}
#endif

#if LIBCONFIG_USE_FLOAT128
t_f128	F128_Mod(t_f128 x, t_f128 y)
{
	union ldshape ux = {x}, uy = {y};
	int ex = ux.i.se & 0x7fff;
	int ey = uy.i.se & 0x7fff;
	int sx = ux.i.se & 0x8000;

	if (y == 0 || isnan(y) || ex == 0x7fff)
		return (x*y)/(x*y);
	ux.i.se = ex;
	uy.i.se = ey;
	if (ux.f <= uy.f)
	{
		if (ux.f == uy.f)
			return 0*x;
		return x;
	}
	/* normalize x and y */
	if (!ex)
	{
		ux.f *= 0x1p120f;
		ex = ux.i.se - 120;
	}
	if (!ey)
	{
		uy.f *= 0x1p120f;
		ey = uy.i.se - 120;
	}
	/* x mod y */
	t_u64 hi, lo, xhi, xlo, yhi, ylo;
	xhi = (ux.i2.hi & -1ull>>16) | 1ull<<48;
	yhi = (uy.i2.hi & -1ull>>16) | 1ull<<48;
	xlo = ux.i2.lo;
	ylo = uy.i2.lo;
	for (; ex > ey; ex--)
	{
		hi = xhi - yhi;
		lo = xlo - ylo;
		if (xlo < ylo)
			hi -= 1;
		if (hi >> 63 == 0)
		{
			if ((hi|lo) == 0)
				return 0*x;
			xhi = 2*hi + (lo>>63);
			xlo = 2*lo;
		}
		else
		{
			xhi = 2*xhi + (xlo>>63);
			xlo = 2*xlo;
		}
	}
	hi = xhi - yhi;
	lo = xlo - ylo;
	if (xlo < ylo)
		hi -= 1;
	if (hi >> 63 == 0)
	{
		if ((hi|lo) == 0)
			return 0*x;
		xhi = hi;
		xlo = lo;
	}
	for (; xhi >> 48 == 0; xhi = 2*xhi + (xlo>>63), xlo = 2*xlo, ex--);
	ux.i2.hi = xhi;
	ux.i2.lo = xlo;
	/* scale result */
	if (ex <= 0)
	{
		ux.i.se = (ex+120)|sx;
		ux.f *= 0x1p-120f;
	}
	else
		ux.i.se = ex|sx;
	return ux.f;
}
#endif



#endif
