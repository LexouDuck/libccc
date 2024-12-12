
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
extern inline t_f32	F32_RemQuo(t_f32 a, t_f32 b, t_sint* quotient)	{ return (__builtin_remquof(a, b, quotient)); }
extern inline t_f64	F64_RemQuo(t_f64 a, t_f64 b, t_sint* quotient)	{ return (__builtin_remquo(a, b, quotient)); }
#if LIBCONFIG_USE_FLOAT80
extern inline t_f80	F80_RemQuo(t_f80 a, t_f80 b, t_sint* quotient)	{ return (__builtin_remquol(a, b, quotient)); }
#endif
#if LIBCONFIG_USE_FLOAT128
extern inline t_f128	F128_RemQuo(t_f128 a, t_f128 b, t_sint* quotient)	{ return (__builtin_remquol(a, b, quotient)); }
#endif
#else
#define DEFINEFUNC_FLOAT_REMQUO(BITS) \
t_f##BITS	F##BITS##_RemQuo(t_f##BITS x, t_f##BITS y, t_sint* quotient) \
{ \
	u_cast_f##BITS ux = {x}; \
	u_cast_f##BITS uy = {y}; \
	int ex = ux.value_uint >> F##BITS##_MANTISSA_BITS & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	int ey = uy.value_uint >> F##BITS##_MANTISSA_BITS & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	int sx = ux.value_uint >> (BITS - 1); \
	int sy = uy.value_uint >> (BITS - 1); \
	t_u32 q; \
	t_u##BITS i; \
	t_u##BITS uxi = ux.value_uint; \
	*quotient = 0; \
	if (uy.value_uint << 1 == 0 || IS_NAN(y) || ex == ((1 << F##BITS##_EXPONENT_BITS) - 1)) \
		return (x*y)/(x*y); \
	if (ux.value_uint << 1 == 0) \
		return x; \
	/* normalize x and y */ \
	if (!ex) \
	{ \
		for (i = uxi << (F##BITS##_EXPONENT_BITS + 1); i >> (BITS - 1) == 0; ex--, i <<= 1); \
		uxi <<= -ex + 1; \
	} \
	else \
	{ \
		uxi &= (t_u##BITS)-1 >> (F##BITS##_EXPONENT_BITS + 1); \
		uxi |= (t_u##BITS)+1 << F##BITS##_MANTISSA_BITS; \
	} \
	if (!ey) \
	{ \
		for (i = uy.value_uint << (F##BITS##_EXPONENT_BITS + 1); i >> (BITS - 1) == 0; ey--, i <<= 1); \
		uy.value_uint <<= -ey + 1; \
	} \
	else \
	{ \
		uy.value_uint &= (t_u##BITS)-1 >> (F##BITS##_EXPONENT_BITS + 1); \
		uy.value_uint |= (t_u##BITS)+1 << F##BITS##_MANTISSA_BITS; \
	} \
	q = 0; \
	if (ex < ey) \
	{ \
		if (ex+1 == ey) \
			goto end; \
		return x; \
	} \
	/* x mod y */ \
	for (; ex > ey; ex--) \
	{ \
		i = uxi - uy.value_uint; \
		if (i >> (BITS - 1) == 0) \
		{ \
			uxi = i; \
			q++; \
		} \
		uxi <<= 1; \
		q <<= 1; \
	} \
	i = uxi - uy.value_uint; \
	if (i >> (BITS - 1) == 0) \
	{ \
		uxi = i; \
		q++; \
	} \
	if (uxi == 0) \
		ex = -(t_s##BITS)((sizeof(t_f##BITS) * 8) / 16); \
	else \
		for (; uxi >> F##BITS##_MANTISSA_BITS == 0; uxi <<= 1, ex--); \
end: \
	/* scale result and decide between |x| and |x|-|y| */ \
	if (ex > 0) \
	{ \
		uxi -= (t_u##BITS)+1 << F##BITS##_MANTISSA_BITS; \
		uxi |= (t_u##BITS)ex << F##BITS##_MANTISSA_BITS; \
	} \
	else \
	{ \
		uxi >>= -ex + 1; \
	} \
	ux.value_uint = uxi; \
	x = ux.value_float; \
	if (sy) \
		y = -y; \
	if (ex == ey || (ex+1 == ey && (2*x > y || (2*x == y && q%2)))) \
	{ \
		x -= y; \
		q++; \
	} \
	q &= 0x7fffffff; \
	*quotient = sx^sy ? -(t_sint)q : (t_sint)q; \
	return sx ? -x : x; \
} \

DEFINEFUNC_FLOAT_REMQUO(32)
DEFINEFUNC_FLOAT_REMQUO(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_REMQUO(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_REMQUO(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Rem, drem)
#else
#define DEFINEFUNC_FLOAT_REM(BITS) \
extern inline \
t_f##BITS F##BITS##_Rem(t_f##BITS x, t_f##BITS y) \
{ \
	t_s##BITS q; \
	return F##BITS##_RemQuo(x, y, &q); \
} \

DEFINEFUNC_FLOAT_REM(32)
DEFINEFUNC_FLOAT_REM(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_REM(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_REM(128)
#endif

#endif
