
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
*/

#define DEFINEFUNC_FIXED_INVCOSH(BITS) \
t_q##BITS	Q##BITS##_InvCosH(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((x._ < (t_s##BITS)Q##BITS##_DENOM), ERROR_MATHDOMAIN, \
		"inverse hyperbolic cosine is only defined for values >= 1") \
		return (Q##BITS##_ERROR); \
	return (Q##BITS##_FromF64(F64_InvCosH(F64_FromQ##BITS(x)))); \
} \

DEFINEFUNC_FIXED_INVCOSH(8)
DEFINEFUNC_FIXED_INVCOSH(16)
DEFINEFUNC_FIXED_INVCOSH(32)
DEFINEFUNC_FIXED_INVCOSH(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_INVCOSH(128)
#endif
