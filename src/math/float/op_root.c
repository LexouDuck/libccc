
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALOPERATOR(RootN, rootn)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_ROOTN(BITS) \
t_f##BITS	F##BITS##_RootN(t_f##BITS x, t_u8 n) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((n % 2 == 0 && x < 0), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	/* Newton derivative approximation by iteration */ \
	static const t_s32	max_i = 4; \
	t_s32	i; \
	t_f##BITS	result; \
	t_f##BITS	previous; \
	t_f##BITS	power; \
	if (n == 0) \
		return (NAN); \
	if (n == 1) \
		return (x); \
	if (x == 0) \
		return (0); \
	if (F##BITS##_Abs(x) == 1.) \
		return (SGN(x)); \
	i = F##BITS##_GetExp2(x); \
	result = SGN(x) * (i < 0 ? 1 : 1.25); \
	result *= __root2pN_f##BITS(i * 2 / (t_s32)n); \
	previous = 0.; \
	i = 0; \
	n -= 1; \
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX) \
	{ \
		previous = result; \
		power = result; \
		for (t_u32 j = 1; j < n; ++j) \
		{ \
			power *= result; \
		} \
		result -= (power * result - x) / ((n + 1) * power); \
		if (++i == max_i) \
			break; \
	} \
	return (result); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_ROOTN(16)
#endif
DEFINEFUNC_FLOAT_ROOTN(32)

DEFINEFUNC_FLOAT_ROOTN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOTN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOTN(128)
#endif

#else



#endif
