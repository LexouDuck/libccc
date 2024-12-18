
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_TOSTR(BITS) \
t_char*	Q##BITS##_ToString(t_q##BITS number) \
{ \
	t_s##BITS	n; \
	t_char*	result = NULL; \
	t_char*	tmp = NULL; \
 \
	n = Q##BITS##_IntegerPart(number); \
	tmp = S##BITS##_ToString(n); \
	result = String_Append(&tmp, ".("); \
	n = Q##BITS##_FractionPart(number); \
	tmp = S##BITS##_ToString(n); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, "/"); \
	n = FIXED_DENOMINATOR; \
	tmp = S##BITS##_ToString(n); \
	result = String_Merge(&result, &tmp); \
	result = String_Append(&result, ")"); \
	return (result); \
} \
/*
	return (String_Format( \
		SF_S##BITS ".(" SF_S##BITS "/" SF_S##BITS ")", \
		(t_s##BITS)Q##BITS##_IntegerPart(number), \
		(t_s##BITS)Q##BITS##_FractionPart(number), \
		(t_s##BITS)(FIXED_DENOMINATOR)) \
	); \
*/

DEFINEFUNC_FIXED_TOSTR(16)
DEFINEFUNC_FIXED_TOSTR(32)
DEFINEFUNC_FIXED_TOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TOSTR(128)
#endif
