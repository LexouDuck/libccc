
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_EQUALS(BITS) \
_INLINE() \
t_bool	F##BITS##_Equals(t_f##BITS x, t_f##BITS y) \
{ \
	return (x == y); \
} \

DEFINEFUNC_FLOAT_EQUALS(32)
DEFINEFUNC_FLOAT_EQUALS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EQUALS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EQUALS(128)
#endif



#define DEFINEFUNC_FLOAT_APPROX(BITS) \
_INLINE() \
t_bool	F##BITS##_EqualsApprox(t_f##BITS x, t_f##BITS y, t_f##BITS approx) \
{ \
	t_f##BITS abs_a = F##BITS##_Abs(x); \
	t_f##BITS abs_b = F##BITS##_Abs(y); \
	return (F##BITS##_Abs(x - y) <= F##BITS##_Max(abs_a, abs_b) * approx); \
} \

DEFINEFUNC_FLOAT_APPROX(32)
DEFINEFUNC_FLOAT_APPROX(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_APPROX(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_APPROX(128)
#endif
