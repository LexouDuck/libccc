
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_UINT_NAN
#define DEFINEFUNC_UINT_ISNAN(BITS) \
_INLINE() \
t_bool	U##BITS##_IsNaN(t_u##BITS x) \
{ \
	return (x == U##BITS##_NAN); \
} \

#else
#define DEFINEFUNC_UINT_ISNAN(BITS) \
_INLINE() \
t_bool	U##BITS##_IsNaN(t_u##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_UINT_ISNAN(8)
DEFINEFUNC_UINT_ISNAN(16)
DEFINEFUNC_UINT_ISNAN(32)
DEFINEFUNC_UINT_ISNAN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ISNAN(128)
#endif



#if LIBCONFIG_SINT_NAN
#define DEFINEFUNC_SINT_ISNAN(BITS) \
_INLINE() \
t_bool	S##BITS##_IsNaN(t_s##BITS x) \
{ \
	return (x == S##BITS##_NAN); \
} \

#else
#define DEFINEFUNC_SINT_ISNAN(BITS) \
_INLINE() \
t_bool	S##BITS##_IsNaN(t_s##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_SINT_ISNAN(8)
DEFINEFUNC_SINT_ISNAN(16)
DEFINEFUNC_SINT_ISNAN(32)
DEFINEFUNC_SINT_ISNAN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ISNAN(128)
#endif
