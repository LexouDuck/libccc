
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ROOT2(BITS) \
t_q##BITS	Q##BITS##_Root2(t_q##BITS x) \
{ \
	/* TODO: implement */ \
	return (Q##BITS##_FromF64(F64_Root2(F64_FromQ##BITS(x)))); \
} \

DEFINEFUNC_FIXED_ROOT2(8)
DEFINEFUNC_FIXED_ROOT2(16)
DEFINEFUNC_FIXED_ROOT2(32)
DEFINEFUNC_FIXED_ROOT2(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROOT2(128)
#endif
