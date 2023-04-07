
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Round, round)
#else
#define DEFINEFUNC_FLOAT_ROUND(BITS) \
inline t_f##BITS	F##BITS##_Round(t_f##BITS x)	\
{													\
	t_f##BITS fraction = F##BITS##_Mod(x, 1.);		\
	if (x == 0.)									\
		return (0.);								\
	if (x < 0.)										\
		return (fraction < 0.5 ?					\
			(x + fraction) :						\
			(x - (1 - fraction)));					\
	else											\
		return (fraction < 0.5 ?					\
			(x - fraction) :						\
			(x + (1 - fraction)));					\
}

DEFINEFUNC_FLOAT_ROUND(32)
DEFINEFUNC_FLOAT_ROUND(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROUND(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROUND(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Trunc, trunc)
#else
#define DEFINEFUNC_FLOAT_TRUNC(BITS) \
inline t_f##BITS	F##BITS##_Trunc(t_f##BITS x)	\
{													\
	if (x == 0.)									\
		return (0.);								\
	return (x - F##BITS##_Mod(x, 1.));				\
}

DEFINEFUNC_FLOAT_TRUNC(32)
DEFINEFUNC_FLOAT_TRUNC(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TRUNC(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TRUNC(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Floor, floor)
#else
#define DEFINEFUNC_FLOAT_FLOOR(BITS) \
inline t_f##BITS	F##BITS##_Floor(t_f##BITS x)	\
{													\
	if (x == 0.)									\
		return (0.);								\
	if (x < 0.)										\
		return (x - F##BITS##_Mod(x, 1.) - 1.);		\
	return (x - F##BITS##_Mod(x, 1.));				\
}

DEFINEFUNC_FLOAT_FLOOR(32)
DEFINEFUNC_FLOAT_FLOOR(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FLOOR(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FLOOR(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Ceil, ceil)
#else
#define DEFINEFUNC_FLOAT_CEIL(BITS) \
inline t_f##BITS	F##BITS##_Ceil(t_f##BITS x)		\
{													\
	if (x == 0.)									\
		return (0.);								\
	if (x < 0.)										\
		return (x - F##BITS##_Mod(x, 1.));			\
	return (1 + x - F##BITS##_Mod(x, 1.));			\
}

DEFINEFUNC_FLOAT_CEIL(32)
DEFINEFUNC_FLOAT_CEIL(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_CEIL(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_CEIL(128)
#endif

#endif
