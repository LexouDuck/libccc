
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ROOT3(BITS) \
t_q##BITS	Q##BITS##_Root3(t_q##BITS x) \
{ \
	/* TODO: implement */ \
	return (Q##BITS##_FromF64(F64_Root3(F64_FromQ##BITS(x)))); \
} \

DEFINEFUNC_FIXED_ROOT3(8)
DEFINEFUNC_FIXED_ROOT3(16)
DEFINEFUNC_FIXED_ROOT3(32)
DEFINEFUNC_FIXED_ROOT3(64)
#if LIBCONFIG_USE_INT138
DEFINEFUNC_FIXED_ROOT3(128)
#endif
