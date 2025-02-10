
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE

// TODO: handle overflows

#define DEFINEFUNC_FIXED_ROOTN(BITS) \
t_q##BITS	Q##BITS##_RootN(t_q##BITS x, t_u8 n) \
{ \
	if (n == 2)	return Q##BITS##_Root2(x); \
	if (n == 3)	return Q##BITS##_Root3(x); \
	return (Q##BITS##_Pow(x, Q##BITS##_Div((t_q##BITS){ 1 }, Q##BITS##_FromU8(n)))); \
} \

DEFINEFUNC_FIXED_ROOTN(8)
DEFINEFUNC_FIXED_ROOTN(16)
DEFINEFUNC_FIXED_ROOTN(32)
DEFINEFUNC_FIXED_ROOTN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROOTN(128)
#endif
