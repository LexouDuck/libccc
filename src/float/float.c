
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_FROMINT(BITS) \
inline t_f##BITS	F##BITS##_FromInt(t_sint number)			\
{																\
	return ((t_f##BITS)number);									\
}

DEFINEFUNC_FLOAT_FROMINT(32)
DEFINEFUNC_FLOAT_FROMINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMINT(128)
#endif



#define DEFINEFUNC_FLOAT_FROMFIXED(BITS) \
inline t_f##BITS	F##BITS##_FromFixed(t_fixed number)			\
{																\
	return ((t_f##BITS)number / (t_f##BITS)FIXED_DENOMINATOR);	\
}

DEFINEFUNC_FLOAT_FROMFIXED(32)
DEFINEFUNC_FLOAT_FROMFIXED(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFIXED(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFIXED(128)
#endif



#define DEFINEFUNC_FLOAT_FROMFLOAT(BITS) \
inline t_f##BITS	F##BITS##_FromFloat(t_float number)			\
{																\
	return ((t_f##BITS)number);									\
}

DEFINEFUNC_FLOAT_FROMFLOAT(32)
DEFINEFUNC_FLOAT_FROMFLOAT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMFLOAT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMFLOAT(128)
#endif



#define DEFINEFUNC_FLOAT_FROM(BITS) \
t_f##BITS	F##BITS##_From(t_sint integer, t_sint exponent)		\
{																\
	return (integer * Float_Pow(2, exponent));					\
}

DEFINEFUNC_FLOAT_FROM(32)
DEFINEFUNC_FLOAT_FROM(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROM(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROM(128)
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_FUNCTION(t_sint, GetExp2, ilogb)
#else

#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS number)						\
{																\
	u_f##BITS##_cast	n;										\
	return (((n.value_uint & F##BITS##_EXPONENT) >>				\
		F##BITS##_MANTISSA_BITS) - F##BITS##_EXPONENT_BIAS);	\
}

DEFINEFUNC_FLOAT_GETEXP2(32)
DEFINEFUNC_FLOAT_GETEXP2(64)
/* TODO fix this
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GETEXP2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GETEXP2(128)
#endif
*/
#endif


#define DEFINEFUNC_FLOAT_GETEXP10(BITS) \
t_sint	F##BITS##_GetExp10(t_f##BITS number)					\
{																\
	return (F##BITS##_Trunc(F##BITS##_Log10(number)));			\
}

DEFINEFUNC_FLOAT_GETEXP10(32)
DEFINEFUNC_FLOAT_GETEXP10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GETEXP10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GETEXP10(128)
#endif
