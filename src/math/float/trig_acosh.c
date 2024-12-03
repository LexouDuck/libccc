
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvCosH, acosh)
#else
// fast sqrt approximation for [+1,+20] and natural log for the rest
// score: 5.00	for [+1,+50]-> 250 tests
#define DEFINEFUNC_FLOAT_INVCOSH(BITS) \
t_f##BITS	F##BITS##_InvCosH(t_f##BITS x)								\
{																		\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)	return (NAN);		\
	if CCCERROR((x < 1.), ERROR_MATHDOMAIN, NULL)	return (NAN);		\
	if (x < 20)															\
		return (1.37 * F##BITS##_Root2(x - 1) - 0.122 * (x - 1));		\
	else																\
		return (F##BITS##_Ln(x - 1) + INV_SQRT_2);						\
}

DEFINEFUNC_FLOAT_INVCOSH(32)
DEFINEFUNC_FLOAT_INVCOSH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVCOSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVCOSH(128)
#endif

#endif
