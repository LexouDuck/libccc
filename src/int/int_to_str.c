
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_TOSTR(BITS) \
_INLINE() \
t_char*	U##BITS##_ToString(t_u##BITS number) \
{ \
	return (U##BITS##_ToString_Dec(number)); \
} \

DEFINEFUNC_UINT_TOSTR(8)
DEFINEFUNC_UINT_TOSTR(16)
DEFINEFUNC_UINT_TOSTR(32)
DEFINEFUNC_UINT_TOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_TOSTR(128)
#endif



#define DEFINEFUNC_SINT_TOSTR(BITS) \
_INLINE() \
t_char*	S##BITS##_ToString(t_s##BITS number) \
{ \
	return (S##BITS##_ToString_Dec(number)); \
} \

DEFINEFUNC_SINT_TOSTR(8)
DEFINEFUNC_SINT_TOSTR(16)
DEFINEFUNC_SINT_TOSTR(32)
DEFINEFUNC_SINT_TOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_TOSTR(128)
#endif
