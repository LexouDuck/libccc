
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
	cast.as_f = mantissa; \
	e = (cast.as_u >> F##BITS##_MANTISSA_BITS) & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	e += exponent; \
	cast.as_u = ((e & ((1 << F##BITS##_EXPONENT_BITS) - 1)) << F##BITS##_MANTISSA_BITS) | (cast.as_u & F##BITS##_MANTISSA_SIGNED); \
	return (cast.as_f); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROM(16)
#endif
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
	return x * u.as_f; \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROM(16,  0x1p15f    , 0x1p-14f    , 0x1p11f  , u.as_u = (t_u16)(((1 << (F16_EXPONENT_BITS - 1)) - 1) + n) << F16_MANTISSA_BITS;)
#endif
DEFINEFUNC_FLOAT_FROM(32,  0x1p127f   , 0x1p-126f   , 0x1p24f  , u.as_u = (t_u32)(((1 << (F32_EXPONENT_BITS - 1)) - 1) + n) << F32_MANTISSA_BITS;)

DEFINEFUNC_FLOAT_FROM(64,  0x1p1023   , 0x1p-1022   , 0x1p53   , u.as_u = (t_u64)(((1 << (F64_EXPONENT_BITS - 1)) - 1) + n) << F64_MANTISSA_BITS;)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROM(80,  0x1p16383L , 0x1p-16382L , 0x1p64L  , u.as_f = 1.0; u.as_u.se = 0x3fff + n;)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROM(128, 0x1p16383L , 0x1p-16382L , 0x1p113L , u.as_f = 1.0; u.as_u.se = 0x3fff + n;)
#endif

#endif



#define DEFINEFUNC_FLOAT_FROMUINT(BITS, FROM) \
_INLINE() \
t_f##BITS	F##BITS##_FromU##FROM(t_u##FROM number) \
{ \
	if (U##FROM##_IsNaN(number))	return (NAN); \
	if (U##FROM##_IsInf(number))	return (INF); \
	return ((t_f##BITS)number); \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMUINT(16, 8)
DEFINEFUNC_FLOAT_FROMUINT(16, 16)
DEFINEFUNC_FLOAT_FROMUINT(16, 32)
DEFINEFUNC_FLOAT_FROMUINT(16, 64)
#endif
DEFINEFUNC_FLOAT_FROMUINT(32, 8)
DEFINEFUNC_FLOAT_FROMUINT(32, 16)
DEFINEFUNC_FLOAT_FROMUINT(32, 32)
DEFINEFUNC_FLOAT_FROMUINT(32, 64)

DEFINEFUNC_FLOAT_FROMUINT(64, 8)
DEFINEFUNC_FLOAT_FROMUINT(64, 16)
DEFINEFUNC_FLOAT_FROMUINT(64, 32)
DEFINEFUNC_FLOAT_FROMUINT(64, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMUINT(80, 8)
DEFINEFUNC_FLOAT_FROMUINT(80, 16)
DEFINEFUNC_FLOAT_FROMUINT(80, 32)
DEFINEFUNC_FLOAT_FROMUINT(80, 64)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMUINT(128, 8)
DEFINEFUNC_FLOAT_FROMUINT(128, 16)
DEFINEFUNC_FLOAT_FROMUINT(128, 32)
DEFINEFUNC_FLOAT_FROMUINT(128, 64)
#endif
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FLOAT_FROMUINT(32, 128)
DEFINEFUNC_FLOAT_FROMUINT(64, 128)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMUINT(80, 128)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMUINT(128, 128)
#endif
#endif



#define DEFINEFUNC_FLOAT_FROMSINT(BITS, FROM) \
_INLINE() \
t_f##BITS	F##BITS##_FromS##FROM(t_s##FROM number) \
{ \
	if (S##FROM##_IsNaN(number))	return (NAN); \
	if (S##FROM##_IsInf(number))	return (INF * (t_f##BITS)S##FROM##_Sgn(number)); \
	return ((t_f##BITS)number); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMSINT(16, 8)
DEFINEFUNC_FLOAT_FROMSINT(16, 16)
DEFINEFUNC_FLOAT_FROMSINT(16, 32)
DEFINEFUNC_FLOAT_FROMSINT(16, 64)
#endif
DEFINEFUNC_FLOAT_FROMSINT(32, 8)
DEFINEFUNC_FLOAT_FROMSINT(32, 16)
DEFINEFUNC_FLOAT_FROMSINT(32, 32)
DEFINEFUNC_FLOAT_FROMSINT(32, 64)

DEFINEFUNC_FLOAT_FROMSINT(64, 8)
DEFINEFUNC_FLOAT_FROMSINT(64, 16)
DEFINEFUNC_FLOAT_FROMSINT(64, 32)
DEFINEFUNC_FLOAT_FROMSINT(64, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMSINT(80, 8)
DEFINEFUNC_FLOAT_FROMSINT(80, 16)
DEFINEFUNC_FLOAT_FROMSINT(80, 32)
DEFINEFUNC_FLOAT_FROMSINT(80, 64)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMSINT(128, 8)
DEFINEFUNC_FLOAT_FROMSINT(128, 16)
DEFINEFUNC_FLOAT_FROMSINT(128, 32)
DEFINEFUNC_FLOAT_FROMSINT(128, 64)
#endif
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FLOAT_FROMSINT(32, 128)
DEFINEFUNC_FLOAT_FROMSINT(64, 128)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMSINT(80, 128)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMSINT(128, 128)
#endif
#endif



#define DEFINEFUNC_FLOAT_FROMFIXED(BITS, FROM) \
_INLINE() \
t_f##BITS	F##BITS##_FromQ##FROM(t_q##FROM number) \
{ \
	if (Q##FROM##_IsNaN(number))	return (NAN); \
	if (Q##FROM##_IsInf(number))	return (INF * (t_f##BITS)Q##FROM##_Sgn(number)._); \
	return ((t_f##BITS)number._ / (t_f##BITS)Q##FROM##_DENOM); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFIXED(16, 8)
DEFINEFUNC_FLOAT_FROMFIXED(16, 16)
DEFINEFUNC_FLOAT_FROMFIXED(16, 32)
DEFINEFUNC_FLOAT_FROMFIXED(16, 64)
#endif
DEFINEFUNC_FLOAT_FROMFIXED(32, 8)
DEFINEFUNC_FLOAT_FROMFIXED(32, 16)
DEFINEFUNC_FLOAT_FROMFIXED(32, 32)
DEFINEFUNC_FLOAT_FROMFIXED(32, 64)

DEFINEFUNC_FLOAT_FROMFIXED(64, 8)
DEFINEFUNC_FLOAT_FROMFIXED(64, 16)
DEFINEFUNC_FLOAT_FROMFIXED(64, 32)
DEFINEFUNC_FLOAT_FROMFIXED(64, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFIXED(80, 8)
DEFINEFUNC_FLOAT_FROMFIXED(80, 16)
DEFINEFUNC_FLOAT_FROMFIXED(80, 32)
DEFINEFUNC_FLOAT_FROMFIXED(80, 64)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFIXED(128, 8)
DEFINEFUNC_FLOAT_FROMFIXED(128, 16)
DEFINEFUNC_FLOAT_FROMFIXED(128, 32)
DEFINEFUNC_FLOAT_FROMFIXED(128, 64)
#endif
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FLOAT_FROMFIXED(32, 128)
DEFINEFUNC_FLOAT_FROMFIXED(64, 128)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFIXED(80, 128)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFIXED(128, 128)
#endif
#endif



#define DEFINEFUNC_FLOAT_FROMFLOAT(BITS, FROM) \
_INLINE() \
t_f##BITS	F##BITS##_FromF##FROM(t_f##FROM number) \
{ \
	if CCCERROR((!F##FROM##_IsInf(number) && F##BITS##_IsInf((t_f##BITS)number)), ERROR_RESULTRANGE, \
		#BITS"-bit floating-point %s overflow for " SF_F##FROM, \
		((number < 0) ? "negative" : "positive"), number) \
		return ((t_f##BITS)number); \
	if CCCERROR((number != 0. && (t_f##BITS)number == 0.), ERROR_RESULTRANGE, \
		#BITS"-bit floating-point %s underflow for " SF_F##FROM, \
		((number < 0) ? "negative" : "positive"), number) \
		return ((t_f##BITS)number); \
	return ((t_f##BITS)number); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFLOAT(16, 16)

DEFINEFUNC_FLOAT_FROMFLOAT(16, 32)

DEFINEFUNC_FLOAT_FROMFLOAT(16, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFLOAT(16, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(16, 128)
#endif
#endif

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFLOAT(32, 16)
#endif
DEFINEFUNC_FLOAT_FROMFLOAT(32, 32)

DEFINEFUNC_FLOAT_FROMFLOAT(32, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFLOAT(32, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(32, 128)
#endif

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFLOAT(64, 16)
#endif
DEFINEFUNC_FLOAT_FROMFLOAT(64, 32)

DEFINEFUNC_FLOAT_FROMFLOAT(64, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFLOAT(64, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(64, 128)
#endif

#if LIBCONFIG_USE_FLOAT80
#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFLOAT(80, 16)
#endif
DEFINEFUNC_FLOAT_FROMFLOAT(80, 32)
DEFINEFUNC_FLOAT_FROMFLOAT(80, 64)
DEFINEFUNC_FLOAT_FROMFLOAT(80, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_FROMFLOAT(128, 16)
#endif
DEFINEFUNC_FLOAT_FROMFLOAT(128, 32)
DEFINEFUNC_FLOAT_FROMFLOAT(128, 64)
DEFINEFUNC_FLOAT_FROMFLOAT(128, 128)
#endif

#if LIBCONFIG_USE_FLOAT80 && LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(80, 128)
DEFINEFUNC_FLOAT_FROMFLOAT(128, 80)
#endif
