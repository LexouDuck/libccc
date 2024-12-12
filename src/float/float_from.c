
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_OPERATOR_ROP(t_sint, From, ldexp)
#else
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

#endif



#define DEFINEFUNC_FLOAT_FROMINT(BITS) \
extern inline \
t_f##BITS	F##BITS##_FromInt(t_sint number) \
{ \
	return ((t_f##BITS)number); \
} \

DEFINEFUNC_FLOAT_FROMINT(32)
DEFINEFUNC_FLOAT_FROMINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMINT(128)
#endif



#define DEFINEFUNC_FLOAT_FROMFIXED(BITS) \
extern inline \
t_f##BITS	F##BITS##_FromFixed(t_fixed number) \
{ \
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



#define DEFINEFUNC_FLOAT_FROMFLOAT(BITS) \
extern inline \
t_f##BITS	F##BITS##_FromFloat(t_float number) \
{ \
	return ((t_f##BITS)number); \
} \

DEFINEFUNC_FLOAT_FROMFLOAT(32)
DEFINEFUNC_FLOAT_FROMFLOAT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFLOAT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(128)
#endif
