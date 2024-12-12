
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Hypotenuse, hypot)
#else
#define DEFINEFUNC_FLOAT_HYPOT(BITS, N_HUGE, N_TINY, N_ADD, N_SUB, SPLIT) \
static \
void	__sq##BITS(t_f##BITS* hi, t_f##BITS* lo, t_f##BITS x) \
{ \
	t_f##BITS xh; \
	t_f##BITS xl; \
	t_f##BITS xc; \
	xc = (t_f##BITS)x * SPLIT; \
	xh = x - xc + xc; \
	xl = x - xh; \
	*hi = (t_f##BITS)(x * x); \
	*lo = xh*xh - (*hi) + 2*xh*xl + xl*xl; \
} \
t_f##BITS	F##BITS##_Hypotenuse(t_f##BITS x, t_f##BITS y) \
{ \
	u_cast_f##BITS ux = {x}; \
	u_cast_f##BITS uy = {y}; \
	u_cast_f##BITS ut; \
	int ex; \
	int ey; \
	t_f##BITS hx; \
	t_f##BITS hy; \
	t_f##BITS lx; \
	t_f##BITS ly; \
	t_f##BITS z; \
	/* arrange |x| >= |y| */ \
	ux.value_uint &= (t_u##BITS)-1 >> 1; \
	uy.value_uint &= (t_u##BITS)-1 >> 1; \
	if (ux.value_uint < uy.value_uint) \
	{ \
		ut = ux; \
		ux = uy; \
		uy = ut; \
	} \
	/* special cases */ \
	ex = ux.value_uint >> F##BITS##_MANTISSA_BITS; \
	ey = uy.value_uint >> F##BITS##_MANTISSA_BITS; \
	x = ux.value_float; \
	y = uy.value_float; \
	/* note: hypot(inf,nan) == inf */ \
	if (ey == (F##BITS##_EXPONENT >> F##BITS##_MANTISSA_BITS)) \
		return y; \
	if (ex == (F##BITS##_EXPONENT >> F##BITS##_MANTISSA_BITS) || uy.value_uint == 0) \
		return x; \
	/* note: hypot(x,y) ~= x + y*y/x/2 with inexact for small y/x */ \
	/* 64 difference is enough for ld80 double_t */ \
	if (ex - ey > BITS) \
		return x + y; \
	/* precise sqrt argument in nearest rounding mode without overflow */ \
	/* xh*xh must not overflow and xl*xl must not underflow in sq */ \
	z = 1; \
	if (ex > (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) + N_ADD) \
	{ \
		z = N_HUGE; \
		x *= N_TINY; \
		y *= N_TINY; \
	} \
	else if (ey < (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) - N_SUB) \
	{ \
		z = N_TINY; \
		x *= N_HUGE; \
		y *= N_HUGE; \
	} \
	__sq##BITS(&hx, &lx, x); \
	__sq##BITS(&hy, &ly, y); \
	return (z * F##BITS##_Root2(ly + lx + hy + hx)); \
} \

DEFINEFUNC_FLOAT_HYPOT(32, 0x1p90, 0x1p-90, 60, 60, (0x1p27+1))
DEFINEFUNC_FLOAT_HYPOT(64, 0x1p700, 0x1p-700, 510, 450, (0x1p32+1))
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_HYPOT(80, 0x1p10000, 0x1p-10000, 8000, 8000, (0x1p32L+1))
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_HYPOT(128, 0x1p10000, 0x1p-10000, 8000, 8000, (0x1p57L+1))
#endif

#endif
