
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_EQUALS(BITS) \
_INLINE() \
t_bool	U##BITS##_Equals(t_u##BITS a, t_u##BITS b) \
{ \
	if (U##BITS##_IsNaN(a) || U##BITS##_IsNaN(b)) \
		return (FALSE); \
	return (a == b); \
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
t_bool	U##BITS##_EqualsApprox(t_u##BITS a, t_u##BITS b) \
{ \
	if (U##BITS##_IsNaN(a) || U##BITS##_IsNaN(b)) \
		return (FALSE); \
	return ((a < b ? b - a : a - b) <= MAX(a, b) * UINT_APPROX); \
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
t_bool	S##BITS##_Equals(t_s##BITS a, t_s##BITS b) \
{ \
	if (S##BITS##_IsNaN(a) || S##BITS##_IsNaN(b)) \
		return (FALSE); \
	return (a == b); \
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
t_bool	S##BITS##_EqualsApprox(t_s##BITS a, t_s##BITS b) \
{ \
	if (S##BITS##_IsNaN(a) || S##BITS##_IsNaN(b)) \
		return (FALSE); \
	t_s##BITS abs_a = S##BITS##_Abs(a); \
	t_s##BITS abs_b = S##BITS##_Abs(b); \
	return (S##BITS##_Abs(a - b) <= MAX(abs_a, abs_b) * SINT_APPROX); \
} \

DEFINEFUNC_SINT_APPROX(8)
DEFINEFUNC_SINT_APPROX(16)
DEFINEFUNC_SINT_APPROX(32)
DEFINEFUNC_SINT_APPROX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_APPROX(128)
#endif
