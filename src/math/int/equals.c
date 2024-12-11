
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_EQUALS(BITS) \
extern inline t_bool	U##BITS##_Equals(t_u##BITS a, t_u##BITS b)		\
{																\
	return (a == b);											\
}
#define DEFINEFUNC_SINT_EQUALS(BITS) \
extern inline t_bool	S##BITS##_Equals(t_s##BITS a, t_s##BITS b)		\
{																\
	return (a == b);											\
}



#define DEFINEFUNC_UINT_APPROX(BITS) \
extern inline t_bool	U##BITS##_EqualsApprox(t_u##BITS a, t_u##BITS b)\
{																\
	return ((a < b ? b - a : a - b) <= MAX(a, b) * UINT_APPROX);\
}
#define DEFINEFUNC_SINT_APPROX(BITS) \
t_bool	S##BITS##_EqualsApprox(t_s##BITS a, t_s##BITS b)		\
{																\
	t_s##BITS abs_a = ABS(a);									\
	t_s##BITS abs_b = ABS(b);									\
	return (ABS(a - b) <= MAX(abs_a, abs_b) * SINT_APPROX);		\
}



DEFINEFUNC_UINT_EQUALS(8)
DEFINEFUNC_SINT_EQUALS(8)
DEFINEFUNC_UINT_APPROX(8)
DEFINEFUNC_SINT_APPROX(8)

DEFINEFUNC_UINT_EQUALS(16)
DEFINEFUNC_SINT_EQUALS(16)
DEFINEFUNC_UINT_APPROX(16)
DEFINEFUNC_SINT_APPROX(16)

DEFINEFUNC_UINT_EQUALS(32)
DEFINEFUNC_SINT_EQUALS(32)
DEFINEFUNC_UINT_APPROX(32)
DEFINEFUNC_SINT_APPROX(32)

DEFINEFUNC_UINT_EQUALS(64)
DEFINEFUNC_SINT_EQUALS(64)
DEFINEFUNC_UINT_APPROX(64)
DEFINEFUNC_SINT_APPROX(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_EQUALS(128)
DEFINEFUNC_SINT_EQUALS(128)
DEFINEFUNC_UINT_APPROX(128)
DEFINEFUNC_SINT_APPROX(128)
#endif
