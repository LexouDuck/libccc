
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_SGN(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Sgn(t_u##BITS x) \
{ \
	if CCCERROR((x == U##BITS##_ERROR), ERROR_MATHDOMAIN, NULL) \
		return (U##BITS##_ERROR); \
	return (x == 0 ? 0 : 1); \
} \

DEFINEFUNC_UINT_SGN(8)
DEFINEFUNC_UINT_SGN(16)
DEFINEFUNC_UINT_SGN(32)
DEFINEFUNC_UINT_SGN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_SGN(128)
#endif



#define DEFINEFUNC_SINT_SGN(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Sgn(t_s##BITS x) \
{ \
	if CCCERROR((x == S##BITS##_ERROR), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (x == 0 ? 0 : (x < 0 ? -1 : +1)); \
} \

DEFINEFUNC_SINT_SGN(8)
DEFINEFUNC_SINT_SGN(16)
DEFINEFUNC_SINT_SGN(32)
DEFINEFUNC_SINT_SGN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_SGN(128)
#endif
