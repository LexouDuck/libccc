
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE

// TODO: handle overflows

#define DEFINEFUNC_UINT_ROOTN(BITS) \
t_u##BITS	U##BITS##_RootN(t_u##BITS x, t_u8 n) \
{ \
	if (n == 2)	return U##BITS##_Root2(x); \
	if (n == 3)	return U##BITS##_Root3(x); \
	return (U##BITS##_FromF64(F64_Pow(F64_FromU##BITS(x), F64_Div(1, F64_FromU8(n))))); \
} \

DEFINEFUNC_UINT_ROOTN(8)
DEFINEFUNC_UINT_ROOTN(16)
DEFINEFUNC_UINT_ROOTN(32)
DEFINEFUNC_UINT_ROOTN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ROOTN(128)
#endif



#define DEFINEFUNC_SINT_ROOTN(BITS) \
t_s##BITS	S##BITS##_RootN(t_s##BITS x, t_u8 n) \
{ \
	if (n == 2)	return S##BITS##_Root2(x); \
	if (n == 3)	return S##BITS##_Root3(x); \
	return (S##BITS##_FromF64(F64_Pow(F64_FromS##BITS(x), F64_Div(1, F64_FromU8(n))))); \
} \

DEFINEFUNC_SINT_ROOTN(8)
DEFINEFUNC_SINT_ROOTN(16)
DEFINEFUNC_SINT_ROOTN(32)
DEFINEFUNC_SINT_ROOTN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ROOTN(128)
#endif
