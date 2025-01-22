
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_LT(BITS) \
_INLINE() \
t_bool	Q##BITS##_LessThan(t_q##BITS a, t_q##BITS b) \
{ \
	return (a._ < b._); \
} \

DEFINEFUNC_FIXED_LT(8)
DEFINEFUNC_FIXED_LT(16)
DEFINEFUNC_FIXED_LT(32)
DEFINEFUNC_FIXED_LT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_LT(128)
#endif

#ifdef __cplusplus
t_bool	operator < (t_q8   x, t_q8   y)	{ return Q8_LessThan(x, y); }
t_bool	operator < (t_q16  x, t_q16  y)	{ return Q16_LessThan(x, y); }
t_bool	operator < (t_q32  x, t_q32  y)	{ return Q32_LessThan(x, y); }
t_bool	operator < (t_q64  x, t_q64  y)	{ return Q64_LessThan(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator < (t_q128 x, t_q128 y)	{ return Q128_LessThan(x, y); }
#endif
#endif



#define DEFINEFUNC_FIXED_LTE(BITS) \
_INLINE() \
t_bool	Q##BITS##_LessThanOrEqual(t_q##BITS a, t_q##BITS b) \
{ \
	return (a._ <= b._); \
} \

DEFINEFUNC_FIXED_LTE(8)
DEFINEFUNC_FIXED_LTE(16)
DEFINEFUNC_FIXED_LTE(32)
DEFINEFUNC_FIXED_LTE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_LTE(128)
#endif

#ifdef __cplusplus
t_bool	operator <= (t_q8   x, t_q8   y)	{ return Q8_LessThanOrEqual(x, y); }
t_bool	operator <= (t_q16  x, t_q16  y)	{ return Q16_LessThanOrEqual(x, y); }
t_bool	operator <= (t_q32  x, t_q32  y)	{ return Q32_LessThanOrEqual(x, y); }
t_bool	operator <= (t_q64  x, t_q64  y)	{ return Q64_LessThanOrEqual(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator <= (t_q128 x, t_q128 y)	{ return Q128_LessThanOrEqual(x, y); }
#endif
#endif



#define DEFINEFUNC_FIXED_GT(BITS) \
_INLINE() \
t_bool	Q##BITS##_GreaterThan(t_q##BITS a, t_q##BITS b) \
{ \
	return (a._ > b._); \
} \

DEFINEFUNC_FIXED_GT(8)
DEFINEFUNC_FIXED_GT(16)
DEFINEFUNC_FIXED_GT(32)
DEFINEFUNC_FIXED_GT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_GT(128)
#endif

#ifdef __cplusplus
t_bool	operator > (t_q8   x, t_q8   y)	{ return Q8_GreaterThan(x, y); }
t_bool	operator > (t_q16  x, t_q16  y)	{ return Q16_GreaterThan(x, y); }
t_bool	operator > (t_q32  x, t_q32  y)	{ return Q32_GreaterThan(x, y); }
t_bool	operator > (t_q64  x, t_q64  y)	{ return Q64_GreaterThan(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator > (t_q128 x, t_q128 y)	{ return Q128_GreaterThan(x, y); }
#endif
#endif



#define DEFINEFUNC_FIXED_GTE(BITS) \
_INLINE() \
t_bool	Q##BITS##_GreaterThanOrEqual(t_q##BITS a, t_q##BITS b) \
{ \
	return (a._ >= b._); \
} \

DEFINEFUNC_FIXED_GTE(8)
DEFINEFUNC_FIXED_GTE(16)
DEFINEFUNC_FIXED_GTE(32)
DEFINEFUNC_FIXED_GTE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_GTE(128)
#endif

#ifdef __cplusplus
t_bool	operator >= (t_q8   x, t_q8   y)	{ return Q8_GreaterThanOrEqual(x, y); }
t_bool	operator >= (t_q16  x, t_q16  y)	{ return Q16_GreaterThanOrEqual(x, y); }
t_bool	operator >= (t_q32  x, t_q32  y)	{ return Q32_GreaterThanOrEqual(x, y); }
t_bool	operator >= (t_q64  x, t_q64  y)	{ return Q64_GreaterThanOrEqual(x, y); }
#if LIBCONFIG_USE_INT128
t_bool	operator >= (t_q128 x, t_q128 y)	{ return Q128_GreaterThanOrEqual(x, y); }
#endif
#endif
