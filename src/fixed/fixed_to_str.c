
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
