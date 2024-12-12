
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(ArcTan2, atan2)
#else
#define DEFINEFUNC_FLOAT_ARCTAN2(BITS) \
t_f##BITS	F##BITS##_ArcTan2(t_f##BITS y, t_f##BITS x) \
{ \
	if CCCERROR((IS_NAN(x) || IS_NAN(y)), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	static const t_f##BITS pi_lo = 1.2246467991473531772E-16; \
	if (y == 0.0) \
		return ((x < 0 ? PI : 0) * SGN(x)); \
	if (x == 0.0) \
		return (PI_HALF * SGN(y)); \
	if (IS_INFINITY(x)) \
	{ \
		if (IS_INFINITY(y)) \
			return ((x < 0 ? 3 * PI_QUARTER : PI_QUARTER) * SGN(y)); \
		else \
			return ((x < 0 ? PI : 0) * SGN(y)); \
	} \
	if (IS_INFINITY(y)) \
		return (PI_HALF * SGN(y)); \
	if (x == 1.0) \
		return (F##BITS##_ArcTan(y)); \
	t_s32 exp_x = F##BITS##_GetExp2(x); \
	t_s32 exp_y = F##BITS##_GetExp2(y); \
	t_f##BITS result = F##BITS##_Abs(y / x); \
	if ((exp_y - exp_x) > 60)		/* |y / x| > +2^60 */ \
		result = PI_HALF + 0.5 * pi_lo; \
	else if ((exp_y - exp_x) < -60)	/* |y| / x < -2^60 */ \
		result = 0.0; \
	else \
		result = F##BITS##_ArcTan(result); \
	if (x < 0) \
		return ((PI - (result - pi_lo)) * SGN(y)); \
	else \
		return (y < 0 ? -result : result); \
} \

DEFINEFUNC_FLOAT_ARCTAN2(32)
DEFINEFUNC_FLOAT_ARCTAN2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCTAN2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCTAN2(128)
#endif

#endif
