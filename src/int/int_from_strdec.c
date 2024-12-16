
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTRDEC(BITS) \
t_size	U##BITS##_Parse_Dec(t_u##BITS* dest, t_char const* str, t_size n) \
{ \
	t_u##BITS	result; \
	t_u##BITS	tmp; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	if CCCERROR(!(str[i] == '+' || Char_IsDigit(str[i])), ERROR_PARSE, \
		"expected a number (with spaces/sign), but instead got \"%s\"", str) \
		goto failure; \
	if (str[i] == '+') \
		++i; \
	result = 0; \
	while (i < n && str[i] && Char_IsDigit(str[i])) \
	{ \
		tmp = result * 10 + (str[i++] - '0'); \
		if CCCERROR((tmp < result), ERROR_RESULTRANGE, \
			#BITS"-bit unsigned integer overflow for \"%s\" at " SF_U##BITS, \
			str, U##BITS##_MAX) \
		{ \
			LIBCONFIG_ERROR_PARSEROVERFLOW(U##BITS##_MAX); \
		} \
		result = tmp; \
	} \
/*success:*/ \
	if (dest)	*dest = result; \
	return (i); \
failure: \
	if (dest)	*dest = U##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_u##BITS	U##BITS##_FromString_Dec(t_char const* str) \
{ \
	t_u##BITS	result = U##BITS##_ERROR; \
	U##BITS##_Parse_Dec(&result, str, 0); \
	return (result); \
}

DEFINEFUNC_UINT_FROMSTRDEC(8)
DEFINEFUNC_UINT_FROMSTRDEC(16)
DEFINEFUNC_UINT_FROMSTRDEC(32)
DEFINEFUNC_UINT_FROMSTRDEC(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMSTRDEC(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRDEC(BITS) \
t_size	S##BITS##_Parse_Dec(t_s##BITS* dest, t_char const* str, t_size n) \
{ \
	t_u##BITS	result; \
	t_u##BITS	tmp; \
	t_bool	negative; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])), ERROR_PARSE, \
		"expected a number (with spaces/sign), but instead got \"%s\"", str) \
		goto failure; \
	negative = FALSE; \
	if (str[i] == '-') \
	{ \
		negative = TRUE; \
		++i; \
	} \
	else if (str[i] == '+') \
		++i; \
	result = 0; \
	while (i < n && str[i] && Char_IsDigit(str[i])) \
	{ \
		tmp = result * 10 + (str[i++] - '0'); \
		if CCCERROR((negative && tmp > (t_u##BITS)S##BITS##_MIN), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer underflow for \"%s\" at " SF_S##BITS, \
			str, S##BITS##_MIN) \
		{ \
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MIN); \
		} \
		if CCCERROR((!negative && tmp > (t_u##BITS)S##BITS##_MAX), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer overflow for \"%s\" at " SF_S##BITS, \
			str, S##BITS##_MAX) \
		{ \
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MAX); \
		} \
		result = tmp; \
	} \
/*success:*/ \
	if (dest)	*dest = (negative ? -(t_s##BITS)result : (t_s##BITS)result); \
	return (i); \
failure: \
	if (dest)	*dest = S##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_s##BITS	S##BITS##_FromString_Dec(t_char const* str) \
{ \
	t_s##BITS	result = S##BITS##_ERROR; \
	S##BITS##_Parse_Dec(&result, str, 0); \
	return (result); \
}

DEFINEFUNC_SINT_FROMSTRDEC(8)
DEFINEFUNC_SINT_FROMSTRDEC(16)
DEFINEFUNC_SINT_FROMSTRDEC(32)
DEFINEFUNC_SINT_FROMSTRDEC(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMSTRDEC(128)
#endif
