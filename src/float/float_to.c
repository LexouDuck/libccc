
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
//MATH_DECL_OPERATOR_ROP(t_sint*, SplitExp, frexp)
#if LIBCONFIG_USE_FLOAT16
_INLINE() t_f16   F16_SplitExp  (t_f16  a, t_sint* b)   { int tmp;	t_f16  result = __builtin_frexpl (a, &tmp);	*b = (t_sint)tmp;	return (result); }
#endif
_INLINE() t_f32   F32_SplitExp  (t_f32  a, t_sint* b)   { int tmp;	t_f32  result = __builtin_frexpf (a, &tmp);	*b = (t_sint)tmp;	return (result); }

_INLINE() t_f64   F64_SplitExp  (t_f64  a, t_sint* b)   { int tmp;	t_f64  result = __builtin_frexp  (a, &tmp);	*b = (t_sint)tmp;	return (result); }
#if LIBCONFIG_USE_FLOAT80
_INLINE() t_f80   F80_SplitExp  (t_f80  a, t_sint* b)   { int tmp;	t_f80  result = __builtin_frexpl (a, &tmp);	*b = (t_sint)tmp;	return (result); }
#endif
#if LIBCONFIG_USE_FLOAT128
_INLINE() t_f128  F128_SplitExp (t_f128 a, t_sint* b)   { int tmp;	t_f128 result = __builtin_frexpl (a, &tmp);	*b = (t_sint)tmp;	return (result); }
#endif

#else
#define DEFINEFUNC_FLOAT_SPLITEXT(BITS) \
t_f##BITS	F##BITS##_SplitExp(t_f##BITS x, t_sint* exponent) \
{ \
	u_cast_f##BITS y = {x}; \
	t_sint ee = (y.as_u >> F##BITS##_MANTISSA_BITS) & (((t_sint)1 << F##BITS##_EXPONENT_BITS) - 1); \
	if (!ee) \
	{ \
		if (x) \
		{ \
			x = F##BITS##_SplitExp(x * 0x1p64, exponent); \
			*exponent -= 64; \
		} \
		else *exponent = 0; \
		return (x); \
	} \
	else if (ee == ((1 << F##BITS##_EXPONENT_BITS) - 1)) \
	{ \
		return (x); \
	} \
	*exponent = ee - (((t_sint)1 << (F##BITS##_EXPONENT_BITS - 1)) - 1); \
	y.as_u &= (t_u##BITS)F##BITS##_MANTISSA_SIGNED; \
	y.as_u |= (t_u##BITS)F##BITS##_EXPONENT_ZERO - ((t_u##BITS)1 << F##BITS##_MANTISSA_BITS); \
	return (y.as_f); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_SPLITEXT(16)
#endif
DEFINEFUNC_FLOAT_SPLITEXT(32)

DEFINEFUNC_FLOAT_SPLITEXT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SPLITEXT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SPLITEXT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DEFINE_OPERATOR_ROP_F32 (t_f32  *, SplitInt, modf)
MATH_DEFINE_OPERATOR_ROP_F64 (t_f64  *, SplitInt, modf)
MATH_DEFINE_OPERATOR_ROP_F80 (t_f80  *, SplitInt, modf)
MATH_DEFINE_OPERATOR_ROP_F128(t_f128 *, SplitInt, modf)
#else
#define DEFINEFUNC_FLOAT_SPLITINT(BITS) \
t_f##BITS	F##BITS##_SplitInt(t_f##BITS x, t_f##BITS* integral) \
{ \
	t_u##BITS mask; \
	u_cast_f##BITS u = {x}; \
	t_sint e = (t_sint)(u.as_u >> F##BITS##_MANTISSA_BITS & (F##BITS##_EXPONENT_MASK >> F##BITS##_MANTISSA_BITS)) - \
		(F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS); \
	/* no fractional part */ \
	if (e >= F##BITS##_MANTISSA_BITS) \
	{ \
		*integral = x; \
		if (F##BITS##_IsNaN(x)) \
			return (x); \
		u.as_u &= (t_u##BITS)1 << (BITS - 1); \
		return (u.as_f); \
	} \
	/* no integral part*/ \
	if (e < 0) \
	{ \
		u.as_u &= (t_u##BITS)1 << (BITS - 1); \
		*integral = u.as_f; \
		return (x); \
	} \
	mask = (t_u##BITS)-1 >> (F##BITS##_EXPONENT_BITS + 1) >> e; \
	if ((u.as_u & mask) == 0) \
	{ \
		*integral = x; \
		u.as_u &= (t_u##BITS)1 << (BITS - 1); \
		return (u.as_f); \
	} \
	u.as_u &= ~mask; \
	*integral = u.as_f; \
	return (x - u.as_f); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_SPLITINT(16)
#endif
DEFINEFUNC_FLOAT_SPLITINT(32)

DEFINEFUNC_FLOAT_SPLITINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SPLITINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SPLITINT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(CopySign, copysign)
#else
#define DEFINEFUNC_FLOAT_COPYSIGN(BITS) \
t_f##BITS F##BITS##_CopySign(t_f##BITS x, t_f##BITS y) \
{ \
	u_cast_f##BITS cast_x; \
	u_cast_f##BITS cast_y; \
	cast_x.as_f = x; \
	cast_y.as_f = y; \
	cast_x.as_u &= ~F##BITS##_SIGN_BIT_MASK; \
	cast_x.as_u |= cast_y.as_u & F##BITS##_SIGN_BIT_MASK; \
	return (cast_x.as_f); \
}

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_COPYSIGN(16)
#endif
DEFINEFUNC_FLOAT_COPYSIGN(32)

DEFINEFUNC_FLOAT_COPYSIGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COPYSIGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COPYSIGN(128)
#endif

#endif
