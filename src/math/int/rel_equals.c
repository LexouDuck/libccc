
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_EQUALS(BITS) \
_INLINE() \
t_bool	U##BITS##_Equals(t_u##BITS x, t_u##BITS y) \
{ \
	if (U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)) \
		return (FALSE); \
	return (x == y); \
} \

DEFINEFUNC_UINT_EQUALS(8)
DEFINEFUNC_UINT_EQUALS(16)
DEFINEFUNC_UINT_EQUALS(32)
DEFINEFUNC_UINT_EQUALS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_EQUALS(128)
#endif

#define DEFINEFUNC_UINT_APPROX(BITS) \
_INLINE() \
t_bool	U##BITS##_EqualsApprox(t_u##BITS x, t_u##BITS y, t_u##BITS approx) \
{ \
	if (U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)) \
		return (FALSE); \
	return ((x < y ? y - x : x - y) <= MAX(x, y) * approx); \
} \

DEFINEFUNC_UINT_APPROX(8)
DEFINEFUNC_UINT_APPROX(16)
DEFINEFUNC_UINT_APPROX(32)
DEFINEFUNC_UINT_APPROX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_APPROX(128)
#endif



#define DEFINEFUNC_SINT_EQUALS(BITS) \
_INLINE() \
t_bool	S##BITS##_Equals(t_s##BITS x, t_s##BITS y) \
{ \
	if (S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)) \
		return (FALSE); \
	return (x == y); \
} \

DEFINEFUNC_SINT_EQUALS(8)
DEFINEFUNC_SINT_EQUALS(16)
DEFINEFUNC_SINT_EQUALS(32)
DEFINEFUNC_SINT_EQUALS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_EQUALS(128)
#endif

#define DEFINEFUNC_SINT_APPROX(BITS) \
_INLINE() \
t_bool	S##BITS##_EqualsApprox(t_s##BITS x, t_s##BITS y, t_s##BITS approx) \
{ \
	if (S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)) \
		return (FALSE); \
	t_s##BITS abs_a = S##BITS##_Abs(x); \
	t_s##BITS abs_b = S##BITS##_Abs(y); \
	return (S##BITS##_Abs(x - y) <= MAX(abs_a, abs_b) * approx); \
} \

DEFINEFUNC_SINT_APPROX(8)
DEFINEFUNC_SINT_APPROX(16)
DEFINEFUNC_SINT_APPROX(32)
DEFINEFUNC_SINT_APPROX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_APPROX(128)
#endif
