
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_EQUALS(BITS) \
extern inline \
t_bool	F##BITS##_Equals(t_f##BITS a, t_f##BITS b) \
{ \
	return (a == b); \
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
extern inline \
t_bool	F##BITS##_EqualsApprox(t_f##BITS a, t_f##BITS b) \
{ \
	t_f##BITS abs_a = ABS(a); \
	t_f##BITS abs_b = ABS(b); \
	return (ABS(a - b) <= MAX(abs_a, abs_b) * FLOAT_APPROX); \
} \

DEFINEFUNC_FLOAT_APPROX(32)
DEFINEFUNC_FLOAT_APPROX(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_APPROX(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_APPROX(128)
#endif
