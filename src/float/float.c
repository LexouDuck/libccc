
#include "libccc/float.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_FROMINT(BITS) \
inline t_f##BITS	F##BITS##_FromInt(t_sint number)						\
{																			\
	return ((t_f##BITS)number);												\
}

#define DEFINEFUNC_FLOAT_FROMFIXED(BITS) \
inline t_f##BITS	F##BITS##_FromFixed(t_fixed number)						\
{																			\
	return ((t_f##BITS)number);												\
}

#define DEFINEFUNC_FLOAT_FROMFLOAT(BITS) \
inline t_f##BITS	F##BITS##_FromFloat(t_float number)						\
{																			\
	return ((t_f##BITS)number);												\
}



#define DEFINEFUNC_FLOAT_FROM(BITS) \
t_f##BITS	F##BITS##_From(t_fixed mantissa, t_sint exponent)	\
{																\
	return (Float_Pow(2, exponent) *							\
		(t_f##BITS)(mantissa >> FIXED_BITS_FRACTIONPART));		\
}



#if LIBCONFIG_USE_FAST_APPROX_MATH
#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS number)																\
{																										\
	return ((((*((t_u##BITS*)&number)) & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);\
}
	DEFINEFUNC_FLOAT_GETEXP2(	32)
	DEFINEFUNC_FLOAT_GETEXP2(	64)
	#ifdef	__float80
	DEFINEFUNC_FLOAT_GETEXP2(	80)
	#endif
	#ifdef	__float128
	DEFINEFUNC_FLOAT_GETEXP2(	128)
	#endif
#else
MATH_DECL_FUNCTION(t_sint, getexp2, ilogb)
#endif


#define DEFINEFUNC_FLOAT_GETEXP10(BITS) \
t_sint	F##BITS##_GetExp10(t_f##BITS number)				\
{															\
	return (F##BITS##_Truncate(F##BITS##_Log10(number)));	\
}



DEFINEFUNC_FLOAT_FROMINT(	32)
DEFINEFUNC_FLOAT_FROMFIXED(	32)
DEFINEFUNC_FLOAT_FROMFLOAT(	32)
DEFINEFUNC_FLOAT_FROM(		32)
DEFINEFUNC_FLOAT_GETEXP10(	32)

DEFINEFUNC_FLOAT_FROMINT(	64)
DEFINEFUNC_FLOAT_FROMFIXED(	64)
DEFINEFUNC_FLOAT_FROMFLOAT(	64)
DEFINEFUNC_FLOAT_FROM(		64)
DEFINEFUNC_FLOAT_GETEXP10(	64)

#ifdef	__float80
DEFINEFUNC_FLOAT_FROMINT(	80)
DEFINEFUNC_FLOAT_FROMFIXED(	80)
DEFINEFUNC_FLOAT_FROMFLOAT(	80)
DEFINEFUNC_FLOAT_FROM(		80)
DEFINEFUNC_FLOAT_GETEXP10(	80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_FROMINT(	128)
DEFINEFUNC_FLOAT_FROMFIXED(	128)
DEFINEFUNC_FLOAT_FROMFLOAT(	128)
DEFINEFUNC_FLOAT_FROM(		128)
DEFINEFUNC_FLOAT_GETEXP10(	128)
#endif
