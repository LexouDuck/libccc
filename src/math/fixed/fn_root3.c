
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include "fixed_math_private.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	The cube root is computed exactly: the raw result is `icbrt(v * DENOM^2)`
**	(with `v` being the raw magnitude of the input), since
**	`trunc(cbrt(v / DENOM) * DENOM) == floor(cbrt(v * DENOM^2))` exactly.
**	The value `v * DENOM^2` can span up to 3 words, so the cube root is found
**	bit-by-bit (building the result from its highest bit down, cubing each
**	candidate over 3 words, exactly).
*/

#define DEFINEFUNC_FIXED_ROOT3(BITS, WB) \
static \
void	__fixedmath_cube_##BITS(t_u##WB r, t_u##WB* w2, t_u##WB* w1, t_u##WB* w0) \
{ \
	t_u##WB	sq_hi; \
	t_u##WB	sq_lo; \
	t_u##WB	a1; \
	t_u##WB	a0; \
	t_u##WB	b1; \
	t_u##WB	b0; \
	__fixedmath_umul_##WB(r, r, &sq_hi, &sq_lo); \
	__fixedmath_umul_##WB(r, sq_lo, &a1, &a0); \
	__fixedmath_umul_##WB(r, sq_hi, &b1, &b0); \
	*w0 = a0; \
	*w1 = a1 + b0; \
	*w2 = b1 + (*w1 < a1 ? 1 : 0); \
} \
t_q##BITS	Q##BITS##_Root3(t_q##BITS x) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if (Q##BITS##_IsInf(x)) \
		return (x); \
	if (x._ == 0) \
		return ((t_q##BITS){ 0 }); \
	t_bool const	negative = (x._ < 0); \
	t_u##WB const	abs_x = __FIXEDMATH_UABS(BITS, WB, x._); \
	/* compute `N = |x| * DENOM^2`, exactly over 3 words */ \
	t_u##WB	d_hi; \
	t_u##WB	d_lo; \
	t_u##WB	a1; \
	t_u##WB	a0; \
	t_u##WB	b1; \
	t_u##WB	b0; \
	__fixedmath_umul_##WB((t_u##WB)Q##BITS##_DENOM, (t_u##WB)Q##BITS##_DENOM, &d_hi, &d_lo); \
	__fixedmath_umul_##WB(abs_x, d_lo, &a1, &a0); \
	__fixedmath_umul_##WB(abs_x, d_hi, &b1, &b0); \
	t_u##WB const	n0 = a0; \
	t_u##WB const	n1 = a1 + b0; \
	t_u##WB const	n2 = b1 + (n1 < a1 ? 1 : 0); \
	/* find `floor(cbrt(N))`, bit by bit, from the highest possible bit down */ \
	t_u8	length; /* total bit length of the 3-word value N */ \
	if (n2 != 0)		length = (t_u8)(2 * WB + __fixedmath_msb_##WB(n2) + 1); \
	else if (n1 != 0)	length = (t_u8)(WB + __fixedmath_msb_##WB(n1) + 1); \
	else				length = (t_u8)(__fixedmath_msb_##WB(n0) + 1); \
	t_u8 const	start = (t_u8)((length + 2) / 3); \
	t_u##WB	result = 0; \
	for (t_u8 i = start + 1; i-- > 0; ) \
	{ \
		if (i >= WB) \
			continue; \
		t_u##WB const	candidate = result | ((t_u##WB)1 << i); \
		t_u##WB	c2; \
		t_u##WB	c1; \
		t_u##WB	c0; \
		__fixedmath_cube_##BITS(candidate, &c2, &c1, &c0); \
		if (c2 < n2 || (c2 == n2 && (c1 < n1 || (c1 == n1 && c0 <= n0)))) \
			result = candidate; \
	} \
	if CCCERROR((result > (t_u##WB)(t_u##BITS)Q##BITS##_MAX._), ERROR_RESULTRANGE, \
		"%s overflow for fixed-point cube root (as t_q"#BITS")", (negative ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (negative ? Q##BITS##_MIN : Q##BITS##_MAX)) \
		return (negative ? Q##BITS##_MIN : Q##BITS##_MAX); \
	} \
	if (negative) \
		return ((t_q##BITS){ (t_s##BITS)-(t_s##WB)result }); \
	return ((t_q##BITS){ (t_s##BITS)result }); \
} \

DEFINEFUNC_FIXED_ROOT3(8, 64)
DEFINEFUNC_FIXED_ROOT3(16, 64)
DEFINEFUNC_FIXED_ROOT3(32, 64)
DEFINEFUNC_FIXED_ROOT3(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ROOT3(128, 128)
#endif
