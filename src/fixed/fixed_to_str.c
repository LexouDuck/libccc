
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_TOSTR(BITS) \
t_char*	Q##BITS##_ToString(t_q##BITS number) \
{ \
	t_s##BITS	n; \
	t_char*	result = NULL; \
	t_char*	tmp = NULL; \
 \
	if (Q##BITS##_IsNaN(number)) \
		return (String_Duplicate("NAN")); \
	if (Q##BITS##_IsInf(number)) \
		return (String_Duplicate((number._ < 0) ? "-INFINITY" : "+INFINITY")); \
	n = (t_s##BITS)(number._ / Q##BITS##_DENOM); \
	tmp = S##BITS##_ToString(n); \
	result = String_Append(&tmp, ".("); \
	n = (t_s##BITS)(number._ % Q##BITS##_DENOM); \
	tmp = S##BITS##_ToString(n); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, "/"); \
	n = (t_s##BITS)Q##BITS##_DENOM; \
	tmp = S##BITS##_ToString(n); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, ")"); \
	return (result); \
} \

DEFINEFUNC_FIXED_TOSTR(8)
DEFINEFUNC_FIXED_TOSTR(16)
DEFINEFUNC_FIXED_TOSTR(32)
DEFINEFUNC_FIXED_TOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR(128)
#endif



/*
**	The fixed-point number is represented as `INTEGER.(NUMERATOR/DENOMINATOR)`,
**	with each of the three numbers written in the target base (with prefix,
**	for the hex/oct/bin variants, so that the output is self-describing and
**	can be parsed back with the matching Q*_Parse_Hex/Oct/Bin function).
*/
#define DEFINEFUNC_FIXED_TOSTR_PREFIXED(BITS, SUFFIX) \
t_char*	Q##BITS##_ToString##SUFFIX(t_q##BITS number) \
{ \
	t_char*	result = NULL; \
	t_char*	tmp = NULL; \
 \
	if (Q##BITS##_IsNaN(number)) \
		return (String_Duplicate("NAN")); \
	if (Q##BITS##_IsInf(number)) \
		return (String_Duplicate((number._ < 0) ? "-INFINITY" : "+INFINITY")); \
	tmp = S##BITS##_ToString##SUFFIX((t_s##BITS)(number._ / Q##BITS##_DENOM), TRUE); \
	result = String_Append(&tmp, ".("); \
	tmp = S##BITS##_ToString##SUFFIX((t_s##BITS)(number._ % Q##BITS##_DENOM), TRUE); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, "/"); \
	tmp = S##BITS##_ToString##SUFFIX((t_s##BITS)Q##BITS##_DENOM, TRUE); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, ")"); \
	return (result); \
} \

DEFINEFUNC_FIXED_TOSTR_PREFIXED(8,   _Hex)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(16,  _Hex)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(32,  _Hex)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(64,  _Hex)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR_PREFIXED(128, _Hex)
#endif

DEFINEFUNC_FIXED_TOSTR_PREFIXED(8,   _Oct)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(16,  _Oct)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(32,  _Oct)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(64,  _Oct)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR_PREFIXED(128, _Oct)
#endif

DEFINEFUNC_FIXED_TOSTR_PREFIXED(8,   _Bin)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(16,  _Bin)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(32,  _Bin)
DEFINEFUNC_FIXED_TOSTR_PREFIXED(64,  _Bin)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR_PREFIXED(128, _Bin)
#endif



/*
**	NOTE: if the given `base` string contains any of the structural characters
**	used by the fixed-point number representation (ie: '.', '(', ')' or '/'),
**	then the resulting string cannot be unambiguously parsed back.
*/
#define DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(BITS) \
t_char*	Q##BITS##_ToString_Base(t_q##BITS number, t_char const* base) \
{ \
	t_char*	result = NULL; \
	t_char*	tmp = NULL; \
 \
	if (Q##BITS##_IsNaN(number)) \
		return (String_Duplicate("NAN")); \
	if (Q##BITS##_IsInf(number)) \
		return (String_Duplicate((number._ < 0) ? "-INFINITY" : "+INFINITY")); \
	tmp = S##BITS##_ToString_Base((t_s##BITS)(number._ / Q##BITS##_DENOM), base); \
	if (tmp == NULL) \
		return (NULL); \
	result = String_Append(&tmp, ".("); \
	tmp = S##BITS##_ToString_Base((t_s##BITS)(number._ % Q##BITS##_DENOM), base); \
	if (tmp == NULL) \
	{ \
		String_Delete(&result); \
		return (NULL); \
	} \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, "/"); \
	tmp = S##BITS##_ToString_Base((t_s##BITS)Q##BITS##_DENOM, base); \
	if (tmp == NULL) \
	{ \
		String_Delete(&result); \
		return (NULL); \
	} \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, ")"); \
	return (result); \
} \

DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(8)
DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(16)
DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(32)
DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR_CUSTOMBASE(128)
#endif
