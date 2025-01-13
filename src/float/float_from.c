
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_OPERATOR_ROP(t_sint, From, scalbn)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_FROM(BITS) \
t_f##BITS	F##BITS##_From(t_f##BITS mantissa, t_sint exponent) \
{ \
	t_s64 e; \
	u_cast_f##BITS cast; \
	cast.value_float = mantissa; \
	e = (cast.value_uint >> F##BITS##_MANTISSA_BITS) & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	e += exponent; \
	cast.value_uint = ((e & ((1 << F##BITS##_EXPONENT_BITS) - 1)) << F##BITS##_MANTISSA_BITS) | (cast.value_uint & F##BITS##_MANTISSA_SIGNED); \
	return (cast.value_float); \
} \

DEFINEFUNC_FLOAT_FROM(32)
DEFINEFUNC_FLOAT_FROM(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROM(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROM(128)
#endif



#else
#define DEFINEFUNC_FLOAT_FROM(BITS, EXP_MAX, EXP_MIN, BIG_EPSILON, APPLY) \
t_f##BITS	F##BITS##_From(t_f##BITS x, t_sint n) \
{ \
	u_cast_f##BITS u; \
	if (n > F##BITS##_EXPONENT_BIAS) \
	{ \
		x *= EXP_MAX; \
		n -= F##BITS##_EXPONENT_BIAS; \
		if (n > F##BITS##_EXPONENT_BIAS) \
		{ \
			x *= EXP_MAX; \
			n -= F##BITS##_EXPONENT_BIAS; \
			if (n > F##BITS##_EXPONENT_BIAS) \
				n = F##BITS##_EXPONENT_BIAS; \
		} \
	} \
	else if (n < -(F##BITS##_EXPONENT_BIAS - 1)) \
	{	/* avoid rounding in the subnormal range */ \
		x *= EXP_MIN * BIG_EPSILON; \
		n += (F##BITS##_EXPONENT_BIAS - 1) - (F##BITS##_MANTISSA_BITS + 1); \
		if (n < -(F##BITS##_EXPONENT_BIAS - 1)) \
		{ \
			x *= EXP_MIN * BIG_EPSILON; \
			n += (F##BITS##_EXPONENT_BIAS - 1) - (F##BITS##_MANTISSA_BITS + 1); \
			if (n < -(F##BITS##_EXPONENT_BIAS - 1)) \
				n = -(F##BITS##_EXPONENT_BIAS - 1); \
		} \
	} \
	APPLY \
	return x * u.value_float; \
} \

DEFINEFUNC_FLOAT_FROM(32,  0x1p127f   , 0x1p-126f   , 0x1p24f  , u.value_uint = (t_u32)(0x7f  + n) << 23;)
DEFINEFUNC_FLOAT_FROM(64,  0x1p1023   , 0x1p-1022   , 0x1p53   , u.value_uint = (t_u64)(0x3ff + n) << 52;)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROM(80,  0x1p16383L , 0x1p-16382L , 0x1p64L  , u.value_float = 1.0; u.value_uint.se = 0x3fff + n;)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROM(128, 0x1p16383L , 0x1p-16382L , 0x1p113L , u.value_float = 1.0; u.value_uint.se = 0x3fff + n;)
#endif

#endif



#define DEFINEFUNC_FLOAT_FROMUINT(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_FromUInt(t_uint number) \
{ \
	if (LIBCONFIG_UINT_INF && UInt_IsInf(number))	return (INF); \
	if (LIBCONFIG_UINT_NAN && UInt_IsNaN(number))	return (NAN); \
	return ((t_f##BITS)number); \
} \

DEFINEFUNC_FLOAT_FROMUINT(32)
DEFINEFUNC_FLOAT_FROMUINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMUINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMUINT(128)
#endif



#define DEFINEFUNC_FLOAT_FROMSINT(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_FromSInt(t_sint number) \
{ \
	if (LIBCONFIG_SINT_INF && SInt_IsInf(number))	return (INF * SGN(number)); \
	if (LIBCONFIG_SINT_NAN && SInt_IsNaN(number))	return (NAN); \
	return ((t_f##BITS)number); \
} \

DEFINEFUNC_FLOAT_FROMSINT(32)
DEFINEFUNC_FLOAT_FROMSINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMSINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMSINT(128)
#endif



#define DEFINEFUNC_FLOAT_FROMFIXED(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_FromFixed(t_fixed number) \
{ \
	if (LIBCONFIG_FIXED_INF && Fixed_IsInf(number))	return (INF * SGN(number)); \
	if (LIBCONFIG_FIXED_NAN && Fixed_IsNaN(number))	return (NAN); \
	return ((t_f##BITS)number / (t_f##BITS)FIXED_DENOMINATOR); \
} \

DEFINEFUNC_FLOAT_FROMFIXED(32)
DEFINEFUNC_FLOAT_FROMFIXED(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFIXED(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFIXED(128)
#endif
