
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcCos, acos)
#else
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#define DEFINEFUNC_FLOAT_ARCCOS(BITS) \
t_f##BITS	F##BITS##_ArcCos(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((F##BITS##_Abs(x) > 1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if (F##BITS##_Abs(x) == 1.) \
		return (INFINITY * SGN(x)); \
	t_f##BITS result = PI_HALF; \
	t_f##BITS power = x; \
	result += power * -1.;			power *= (x * x); \
	result += power * -0.0584;		power *= (x * x); \
	result += power * -0.6852;		power *= (x * x); \
	result += power * +1.16616;		power *= (x * x); \
	result += power * -0.9933563268; \
	return (result); \
} \

// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((-0.8047926 * x * x - 0.766) * x + PI_HALF); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCCOS(32)
DEFINEFUNC_FLOAT_ARCCOS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCCOS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCCOS(128)
#endif

#endif
