
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_EQUALS(BITS) \
_INLINE() \
t_bool	Q##BITS##_Equals(t_q##BITS x, t_q##BITS y) \
{ \
	if (Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)) \
		return (FALSE); \
	return (x._ == y._); \
} \

DEFINEFUNC_FIXED_EQUALS(16)
DEFINEFUNC_FIXED_EQUALS(32)
DEFINEFUNC_FIXED_EQUALS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_EQUALS(128)
#endif

#ifdef __cplusplus
t_bool	operator == (t_q16	x, t_q16	y)	{ return Q16_Equals(x, y); }
t_bool	operator == (t_q32	x, t_q32	y)	{ return Q32_Equals(x, y); }
t_bool	operator == (t_q64	x, t_q64	y)	{ return Q64_Equals(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator == (t_q128	x, t_q128	y)	{ return Q128_Equals(x, y); }
#endif
#endif



#define DEFINEFUNC_FIXED_APPROX(BITS) \
_INLINE() \
t_bool	Q##BITS##_EqualsApprox(t_q##BITS x, t_q##BITS y, t_q##BITS approx) \
{ \
	if (Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)) \
		return (FALSE); \
	t_q##BITS abs_a = Q##BITS##_Abs(x); \
	t_q##BITS abs_b = Q##BITS##_Abs(y); \
	return (Q##BITS##_Abs(Q##BITS##_Sub(x, y))._ <= Q##BITS##_Max(abs_a, abs_b)._ * approx); \
} \

DEFINEFUNC_FIXED_APPROX(16)
DEFINEFUNC_FIXED_APPROX(32)
DEFINEFUNC_FIXED_APPROX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_APPROX(128)
#endif

/*
#ifdef __cplusplus
t_bool	operator ~= (t_q16	x, t_q16	y)	{ return Q16_EqualsApprox(x, y); }
t_bool	operator ~= (t_q32	x, t_q32	y)	{ return Q32_EqualsApprox(x, y); }
t_bool	operator ~= (t_q64	x, t_q64	y)	{ return Q64_EqualsApprox(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator ~= (t_q128	x, t_q128	y)	{ return Q128_EqualsApprox(x, y); }
#endif
#endif
*/
