
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	NOTE: this function is implemented by converting to `t_f64` internally.
**	This is a deliberate choice (not a temporary shortcut), justified as such:
**	- the quantization error of the fixed-point input (`1 / DENOM`) always
**	  dominates the rounding error of the `t_f64` computation for any result
**	  which fits in the 53-bit exact-integer range of a `t_f64`; and beyond
**	  that range, the function grows so steeply that the result saturates
**	  after a tiny input interval anyway
**	- the `F64_FromQ`/`Q_FromF64` conversions already handle the special
**	  values (`NAN`/`INF`) and saturation/overflow behavior consistently
*/

#define DEFINEFUNC_FIXED_COSH(BITS) \
t_q##BITS	Q##BITS##_CosH(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	return (Q##BITS##_FromF64(F64_CosH(F64_FromQ##BITS(x)))); \
} \

DEFINEFUNC_FIXED_COSH(8)
DEFINEFUNC_FIXED_COSH(16)
DEFINEFUNC_FIXED_COSH(32)
DEFINEFUNC_FIXED_COSH(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_COSH(128)
#endif
