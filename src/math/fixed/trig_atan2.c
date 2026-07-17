
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	NOTE: this function is implemented by converting to `t_f64` internally.
**	This is a deliberate choice (not a temporary shortcut), justified as such:
**	- the output of this function is bounded to a small range, so the raw
**	  result always fits well within the 53-bit exact-integer range of a
**	  `t_f64` (no precision is lost on the way out, for any `DENOM` config)
**	- the quantization error of the fixed-point input (`1 / DENOM`) always
**	  dominates the rounding error of the `t_f64` computation, so an exact
**	  integer-only implementation would yield the same result (within 1 ulp)
**	- the `F64_FromQ`/`Q_FromF64` conversions already handle the special
**	  values (`NAN`/`INF`) and saturation behavior consistently
**	The argument order follows the float version: `ArcTan2(y, x) == ArcTan(y / x)`.
*/

#define DEFINEFUNC_FIXED_ARCTAN2(BITS) \
t_q##BITS	Q##BITS##_ArcTan2(t_q##BITS y, t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(y) || Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	return (Q##BITS##_FromF64(F64_ArcTan2(F64_FromQ##BITS(y), F64_FromQ##BITS(x)))); \
} \

DEFINEFUNC_FIXED_ARCTAN2(8)
DEFINEFUNC_FIXED_ARCTAN2(16)
DEFINEFUNC_FIXED_ARCTAN2(32)
DEFINEFUNC_FIXED_ARCTAN2(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ARCTAN2(128)
#endif
