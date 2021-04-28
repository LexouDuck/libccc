
#include <float.h> // TODO remove this after changing FLOAT_EPSILON macros

#include "libccc/float.h"
#include "libccc/math/math.h"



#define DEFINEFUNC_FLOAT(BITS) \
t_f##BITS	F##BITS(t_fixed mantissa, t_sint exponent)		\
{															\
	return (Float_Pow(2, exponent) *						\
		(t_f##BITS)(mantissa >> FIXED_BITS_FRACTIONPART));	\
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


#define DEFINEFUNC_FLOAT_GETEXP10(BITS, POWER) \
t_sint	F##BITS##_GetExp10(t_f##BITS number)				\
{															\
	return (F##BITS##_Truncate(F##BITS##_Log10(number)));	\
}
/*
	t_f##BITS	nearest;									\
	t_sint	power;											\
	t_sint	exponent;										\
	exponent = 0;											\
	power = POWER;											\
	if (number >= 2. ||										\
		number <= -2.)										\
	{														\
		while ((power /= 2) > 0)							\
		{													\
			if (number >= (nearest = Float_Pow(10, power)))	\
			{												\
				number /= nearest;							\
				exponent += power;							\
			}												\
		}													\
	}														\
	if ((number > 0 && number < 1.) ||						\
		(number < 0 && number > -1.))						\
	{														\
		while ((power /= 2) > 0)							\
		{													\
			if (number < Float_Pow(10, 1 - power))			\
			{												\
				number *= Float_Pow(10, power);				\
				exponent -= power;							\
			}												\
		}													\
	}														\
	return (exponent);										\
}
*/


DEFINEFUNC_FLOAT(			32)
DEFINEFUNC_FLOAT_GETEXP10(	32, 512) // 2**9

DEFINEFUNC_FLOAT(			64)
DEFINEFUNC_FLOAT_GETEXP10(	64, 4096) // 2**12

#ifdef	__float80
DEFINEFUNC_FLOAT(			80)
DEFINEFUNC_FLOAT_GETEXP10(	80, 4096) // 2**?
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT(			128)
DEFINEFUNC_FLOAT_GETEXP10(	128, 4096) // 2**?
#endif
