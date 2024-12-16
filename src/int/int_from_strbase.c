
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define INVALID_BASE_SIGNCHAR	-1
#define INVALID_BASE_DUPLICATE	-2

static
t_s32	String_Base_GetLength(t_char const* base)
{
	t_size	i;
	t_size	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (INVALID_BASE_SIGNCHAR);
		j = i;
		while (j--)
		{
			if (base[i] == base[j])
				return (INVALID_BASE_DUPLICATE);
		}
		++i;
	}
	return (i);
}

static
t_s32	String_Base_IsInBase(t_char const* base, t_size base_length, char c)
{
	t_size	i;

	i = 0;
	while (i < base_length)
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (ERROR);
}



#define DEFINEFUNC_UINT_FROMSTRBASE(BITS) \
t_size	U##BITS##_Parse_Base(t_u##BITS* dest, t_char const* str, t_char const* base, t_size n) \
{ \
	t_u##BITS	result; \
	t_u##BITS	tmp; \
	t_s32	digit; \
	t_size	length; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if CCCERROR((base == NULL), ERROR_NULLPOINTER, "numeric base string is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	digit = String_Base_GetLength(base); \
	if CCCERROR((digit == INVALID_BASE_SIGNCHAR), ERROR_INVALIDARGS, \
		"number base (\"%s\") cannot contain sign chars ('+' or '-')", base) \
		goto failure; \
	if CCCERROR((digit == INVALID_BASE_DUPLICATE), ERROR_INVALIDARGS, \
		"number base (\"%s\") must not have any duplicate characters", base) \
		goto failure; \
	if CCCERROR((digit < 2), ERROR_LENGTH2SMALL, \
		"number base (\"%s\") should be at least 2 chars long", base) \
		goto failure; \
	length = (t_size)digit; \
	i = 0; \
	while (i < n && !(str[i] == '+' || str[i] == '-')) \
	{ \
		digit = String_Base_IsInBase(base, length, str[i]); \
		if (digit >= 0) break; \
		if CCCERROR((!str[i] || !Char_IsSpace(str[i])), ERROR_PARSE, \
			"expected a number (with spaces/sign), but instead got \"%s\"", str) \
			goto failure; \
		++i; \
	} \
	if (str[i] == '+' || str[i] == '-') \
		++i; \
	result = 0; \
	while (i < n && str[i]) \
	{ \
		digit = String_Base_IsInBase(base, length, str[i++]); \
		if CCCERROR((digit < 0), ERROR_PARSE, \
			"digit char '%c' is not in number base \"%s\"", str[i - 1], base) \
			goto failure; \
		tmp = result * length + digit; \
		if CCCERROR((tmp < result), ERROR_RESULTRANGE, \
			#BITS"-bit unsigned integer overflow for \"%s\" with base \"%s\" at " SF_U##BITS, \
			str, base, U##BITS##_MAX) \
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
t_u##BITS	U##BITS##_FromString_Base(t_char const* str, t_char const* base) \
{ \
	t_u##BITS	result = U##BITS##_ERROR; \
	U##BITS##_Parse_Base(&result, str, base, 0); \
	return (result); \
}

DEFINEFUNC_UINT_FROMSTRBASE(8)
DEFINEFUNC_UINT_FROMSTRBASE(16)
DEFINEFUNC_UINT_FROMSTRBASE(32)
DEFINEFUNC_UINT_FROMSTRBASE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMSTRBASE(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRBASE(BITS) \
t_size	S##BITS##_Parse_Base(t_s##BITS* dest, t_char const* str, t_char const* base, t_size n) \
{ \
	t_u##BITS	result; \
	t_u##BITS	tmp; \
	t_bool	negative; \
	t_s32	digit; \
	t_size	length; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if CCCERROR((base == NULL), ERROR_NULLPOINTER, "numeric base string is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	digit = String_Base_GetLength(base); \
	if CCCERROR((digit == INVALID_BASE_SIGNCHAR), ERROR_INVALIDARGS, \
		"number base (\"%s\") cannot contain sign chars ('+' or '-')", base) \
		goto failure; \
	if CCCERROR((digit == INVALID_BASE_DUPLICATE), ERROR_INVALIDARGS, \
		"number base (\"%s\") must not have any duplicate characters", base) \
		goto failure; \
	if CCCERROR((digit < 2), ERROR_LENGTH2SMALL, \
		"number base (\"%s\") should be at least 2 chars long", base) \
		goto failure; \
	length = (t_size)digit; \
	i = 0; \
	while (i < n && !(str[i] == '+' || str[i] == '-')) \
	{ \
		digit = String_Base_IsInBase(base, length, str[i]); \
		if (digit >= 0) break; \
		if CCCERROR((!str[i] || !Char_IsSpace(str[i])), ERROR_PARSE, \
			"expected a number (with spaces/sign), but instead got \"%s\"", str) \
			goto failure; \
		++i; \
	} \
	negative = FALSE; \
	if (str[i] == '-') \
	{ \
		negative = TRUE; \
		++i; \
	} \
	else if (str[i] == '+') \
		++i; \
	result = 0; \
	while (i < n && str[i]) \
	{ \
		digit = String_Base_IsInBase(base, length, str[i++]); \
		if CCCERROR((digit < 0), ERROR_PARSE, \
			"digit char '%c' is not in number base \"%s\"", str[i - 1], base) \
			goto failure; \
		tmp = result * length + digit; \
		if CCCERROR((negative && tmp > (t_u##BITS)S##BITS##_MIN), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer underflow for \"%s\" with base \"%s\" at " SF_S##BITS,\
			str, base, S##BITS##_MIN) \
		{ \
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MIN) \
		} \
		if CCCERROR((!negative && tmp > (t_u##BITS)S##BITS##_MAX), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer overflow for \"%s\" with base \"%s\" at " SF_S##BITS,\
			str, base, S##BITS##_MAX) \
		{ \
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MAX) \
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
t_s##BITS	S##BITS##_FromString_Base(t_char const* str, t_char const* base) \
{ \
	t_s##BITS	result = S##BITS##_ERROR; \
	S##BITS##_Parse_Base(&result, str, base, 0); \
	return (result); \
}

DEFINEFUNC_SINT_FROMSTRBASE(8)
DEFINEFUNC_SINT_FROMSTRBASE(16)
DEFINEFUNC_SINT_FROMSTRBASE(32)
DEFINEFUNC_SINT_FROMSTRBASE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMSTRBASE(128)
#endif
