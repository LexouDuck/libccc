
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMUINT(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_FromUInt(t_uint number) \
{ \
	if (UInt_IsNaN(number)) \
		return (U##BITS##_ERROR); \
	return ((t_u##BITS)number); \
} \

DEFINEFUNC_UINT_FROMUINT(16)
DEFINEFUNC_UINT_FROMUINT(32)
DEFINEFUNC_UINT_FROMUINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMUINT(128)
#endif



#define DEFINEFUNC_UINT_FROMSINT(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_FromSInt(t_sint number) \
{ \
	if (SInt_IsNaN(number)) \
		return (U##BITS##_ERROR); \
	return ((t_u##BITS)number); \
} \

DEFINEFUNC_UINT_FROMSINT(16)
DEFINEFUNC_UINT_FROMSINT(32)
DEFINEFUNC_UINT_FROMSINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMSINT(128)
#endif



#define DEFINEFUNC_UINT_FROMFIXED(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_FromFixed(t_fixed number) \
{ \
	if (Fixed_IsNaN(number)) \
		return (U##BITS##_ERROR); \
	return ((t_u##BITS)(number / FIXED_DENOMINATOR)); \
} \

DEFINEFUNC_UINT_FROMFIXED(16)
DEFINEFUNC_UINT_FROMFIXED(32)
DEFINEFUNC_UINT_FROMFIXED(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMFIXED(128)
#endif



#define DEFINEFUNC_UINT_FROMFLOAT(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_FromFloat(t_float number) \
{ \
	if (Float_IsNaN(number)) \
		return (U##BITS##_ERROR); \
	return ((t_u##BITS)number); \
} \

DEFINEFUNC_UINT_FROMFLOAT(16)
DEFINEFUNC_UINT_FROMFLOAT(32)
DEFINEFUNC_UINT_FROMFLOAT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMFLOAT(128)
#endif




#define DEFINEFUNC_SINT_FROMUINT(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_FromUInt(t_uint number) \
{ \
	if (UInt_IsNaN(number)) \
		return (S##BITS##_ERROR); \
	return ((t_s##BITS)number); \
} \

DEFINEFUNC_SINT_FROMUINT(16)
DEFINEFUNC_SINT_FROMUINT(32)
DEFINEFUNC_SINT_FROMUINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMUINT(128)
#endif



#define DEFINEFUNC_SINT_FROMSINT(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_FromSInt(t_sint number) \
{ \
	if (SInt_IsNaN(number)) \
		return (S##BITS##_ERROR); \
	return ((t_s##BITS)number); \
} \

DEFINEFUNC_SINT_FROMSINT(16)
DEFINEFUNC_SINT_FROMSINT(32)
DEFINEFUNC_SINT_FROMSINT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMSINT(128)
#endif



#define DEFINEFUNC_SINT_FROMFIXED(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_FromFixed(t_fixed number) \
{ \
	if (Fixed_IsNaN(number)) \
		return (S##BITS##_ERROR); \
	return ((t_s##BITS)(number / FIXED_DENOMINATOR)); \
} \

DEFINEFUNC_SINT_FROMFIXED(16)
DEFINEFUNC_SINT_FROMFIXED(32)
DEFINEFUNC_SINT_FROMFIXED(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMFIXED(128)
#endif



#define DEFINEFUNC_SINT_FROMFLOAT(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_FromFloat(t_float number) \
{ \
	if (Float_IsNaN(number)) \
		return (S##BITS##_ERROR); \
	return ((t_s##BITS)number); \
} \

DEFINEFUNC_SINT_FROMFLOAT(16)
DEFINEFUNC_SINT_FROMFLOAT(32)
DEFINEFUNC_SINT_FROMFLOAT(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMFLOAT(128)
#endif
