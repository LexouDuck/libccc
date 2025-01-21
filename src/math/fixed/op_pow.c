
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE

// TODO: handle overflows

#define DEFINEFUNC_FIXED_POW(BITS) \
t_q##BITS	Q##BITS##_Pow(t_q##BITS x, t_q##BITS y) \
{ \
	/* TODO: implement */ \
	return (Q##BITS##_FromF64(F64_Pow(F64_FromQ##BITS(x), F64_FromQ##BITS(y)))); \
} \

DEFINEFUNC_FIXED_POW(16)
DEFINEFUNC_FIXED_POW(32)
DEFINEFUNC_FIXED_POW(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_POW(128)
#endif

/*
(+) * (+) = [0, +aᵇ] => ()
(-) * (+) = [-aᵇ, 0] => ()
(+) * (-) = [-aᵇ, 0] => ()
(-) * (-) = [0, +aᵇ] => ()
*/
