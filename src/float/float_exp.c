
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_FUNCTION(t_sint, GetExp2, ilogb)
#else

#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS number) \
{ \
	u_cast_f##BITS	cast; \
	cast.value_float = number; \
	return (((cast.value_uint & F##BITS##_EXPONENT) >> F##BITS##_MANTISSA_BITS) - F##BITS##_EXPONENT_BIAS); \
} \

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
t_sint	F##BITS##_GetExp10(t_f##BITS number) \
{ \
	return (F##BITS##_Trunc(F##BITS##_Log10(number))); \
} \

DEFINEFUNC_FLOAT_GETEXP10(32)
DEFINEFUNC_FLOAT_GETEXP10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GETEXP10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GETEXP10(128)
#endif
