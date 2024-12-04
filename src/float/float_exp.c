
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_OPERATOR_ROP(int*, Split, frexp)
#else
#define DEFINEFUNC_FLOAT_SPLIT(BITS, MASK, LSHIFT) \
t_f##BITS	F##BITS##_Split(t_f##BITS x, t_sint* exponent) \
{ \
	u_cast_f##BITS y = {x}; \
	t_sint ee = y.value_uint >> F##BITS##_MANTISSA_BITS & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	if (!ee) \
	{ \
		if (x) \
		{ \
			x = F##BITS##_Split(x * 0x1p64, exponent); \
			*exponent -= 64; \
		} \
		else *exponent = 0; \
		return x; \
	} \
	else if (ee == ((1 << F##BITS##_EXPONENT_BITS) - 1)) \
	{ \
		return x; \
	} \
	*exponent = ee - MASK; \
	y.value_uint &= (t_u##BITS)F##BITS##_MANTISSA_SIGNED; \
	y.value_uint |= (t_u##BITS)MASK << LSHIFT; \
	return (y.value_float); \
} \

DEFINEFUNC_FLOAT_SPLIT(32, 0x7E, 24)
DEFINEFUNC_FLOAT_SPLIT(64, 0x3FE, 52)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SPLIT(80, 0x3FFE, 64)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SPLIT(128, 0x3FFE, 112)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_FUNCTION(t_sint, GetExp2, ilogb)
#else

#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS number) \
{ \
	u_cast_f##BITS	cast; \
	cast.value_float = number; \
	return (((cast.value_uint & F##BITS##_EXPONENT) >> F##BITS##_MANTISSA_BITS) - F##BITS##_EXPONENT_BIAS);	\
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
