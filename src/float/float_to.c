
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_OPERATOR_ROP(int*, SplitExp, frexp)
#else
#define DEFINEFUNC_FLOAT_SPLITEXT(BITS, MASK, LSHIFT) \
t_f##BITS	F##BITS##_SplitExp(t_f##BITS x, t_sint* exponent) \
{ \
	u_cast_f##BITS y = {x}; \
	t_sint ee = y.value_uint >> F##BITS##_MANTISSA_BITS & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
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
	*exponent = ee - MASK; \
	y.value_uint &= (t_u##BITS)F##BITS##_MANTISSA_SIGNED; \
	y.value_uint |= (t_u##BITS)MASK << LSHIFT; \
	return (y.value_float); \
} \

DEFINEFUNC_FLOAT_SPLITEXT(32, 0x7E, 24)
DEFINEFUNC_FLOAT_SPLITEXT(64, 0x3FE, 52)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SPLITEXT(80, 0x3FFE, 64)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SPLITEXT(128, 0x3FFE, 112)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_OPERATOR_ROP(t_f64*, SplitInt, modf)
#else
#define DEFINEFUNC_FLOAT_SPLITINT(BITS) \
t_f##BITS	F##BITS##_SplitInt(t_f##BITS x, t_f##BITS* integral) \
{ \
	t_u##BITS mask; \
	u_cast_f##BITS u = {x}; \
	t_sint e = (t_sint)(u.value_uint >> F##BITS##_MANTISSA_BITS & (F##BITS##_EXPONENT >> F##BITS##_MANTISSA_BITS)) - \
		(F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS); \
	/* no fractional part */ \
	if (e >= F##BITS##_MANTISSA_BITS) \
	{ \
		*integral = x; \
		if (IS_NAN(x)) \
			return (x); \
		u.value_uint &= (t_u##BITS)1 << (BITS - 1); \
		return (u.value_float); \
	} \
	/* no integral part*/ \
	if (e < 0) \
	{ \
		u.value_uint &= (t_u##BITS)1 << (BITS - 1); \
		*integral = u.value_float; \
		return (x); \
	} \
	mask = (t_u##BITS)-1 >> (F##BITS##_EXPONENT_BITS + 1) >> e; \
	if ((u.value_uint & mask) == 0) \
	{ \
		*integral = x; \
		u.value_uint &= (t_u##BITS)1 << (BITS - 1); \
		return (u.value_float); \
	} \
	u.value_uint &= ~mask; \
	*integral = u.value_float; \
	return (x - u.value_float); \
} \

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
	cast_x.value_float = x; \
	cast_y.value_float = y; \
	cast_x.value_uint &= ~F##BITS##_SIGNED; \
	cast_x.value_uint |= cast_y.value_uint & F##BITS##_SIGNED; \
	return (cast_x.value_float); \
}

DEFINEFUNC_FLOAT_COPYSIGN(32)
DEFINEFUNC_FLOAT_COPYSIGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COPYSIGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COPYSIGN(128)
#endif

#endif
