
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_SINT_FROMINT(BITS) \
extern inline t_s##BITS	S##BITS##_FromInt(t_sint number)						\
{																			\
	return ((t_s##BITS)number);												\
}

DEFINEFUNC_SINT_FROMINT(16)
DEFINEFUNC_SINT_FROMINT(32)
DEFINEFUNC_SINT_FROMINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMINT(128)
#endif



#define DEFINEFUNC_SINT_FROMFIXED(BITS) \
extern inline t_s##BITS	S##BITS##_FromFixed(t_fixed number)						\
{																			\
	return ((t_s##BITS)(number / FIXED_DENOMINATOR));						\
}

DEFINEFUNC_SINT_FROMFIXED(16)
DEFINEFUNC_SINT_FROMFIXED(32)
DEFINEFUNC_SINT_FROMFIXED(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMFIXED(128)
#endif



#define DEFINEFUNC_SINT_FROMFLOAT(BITS) \
extern inline t_s##BITS	S##BITS##_FromFloat(t_float number)						\
{																			\
	return ((t_s##BITS)number);												\
}

DEFINEFUNC_SINT_FROMFLOAT(16)
DEFINEFUNC_SINT_FROMFLOAT(32)
DEFINEFUNC_SINT_FROMFLOAT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMFLOAT(128)
#endif
