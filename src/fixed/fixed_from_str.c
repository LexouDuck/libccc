
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/string.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FROMSTR(BASE, BITS, ISDIGIT) \
t_size	Q##BITS##_Parse##BASE(t_q##BITS *dest, t_char const* str, t_size n) \
{ \
	t_s##BITS	result = 0; \
	t_s##BITS	numerator = 0; \
	t_s##BITS	denominator = 1; \
	t_q##BITS	fraction = (t_q##BITS){ 0 }; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (str[i] == '(') \
	{ \
		++i; \
		goto fraction; \
	} \
/*integer:*/ \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || ISDIGIT(str[i])), ERROR_PARSE, \
		"expected a number (with spaces/sign), but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse##BASE(&result, str + i, n - i); \
/*separator:*/ \
	if (str[i] == '.')	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (i >= n || str[i] == '\0')	goto success; \
	if CCCERROR(!(str[i] == '+' || str[i] == '('), ERROR_PARSE, \
		"expected a fractional part separator char, but instead got \"%s\"", str) \
		goto failure; \
	if (str[i] == '(') \
		++i; \
fraction: \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || ISDIGIT(str[i])), ERROR_PARSE, \
		"expected a fraction numerator, but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse##BASE(&numerator, str + i, n - i); \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '/'), ERROR_PARSE, \
		"expected a fraction '/' separator char, but instead got \"%s\"", str) \
		goto failure; \
	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || ISDIGIT(str[i])), ERROR_PARSE, \
		"expected a fraction denominator, but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse##BASE(&denominator, str + i, n - i); \
	if CCCERROR((denominator == 0), ERROR_MATHDOMAIN, \
		"fraction denominator cannot be zero \"%s\"", str) \
		goto failure; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (str[i] == ')') \
		++i; \
	fraction = Q##BITS##_From(numerator, denominator); \
success: \
	if CCCERROR((result > (t_s##BITS)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)), ERROR_RESULTRANGE, \
		"fixed-point overflow for integer part at " SF_S##BITS, (t_s##BITS)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MAX) \
		if (dest)	*dest = Q##BITS##_MAX; \
		return (i); \
	} \
	if CCCERROR((result < (t_s##BITS)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM)), ERROR_RESULTRANGE, \
		"fixed-point underflow for integer part at " SF_S##BITS, (t_s##BITS)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM)) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MIN) \
		if (dest)	*dest = Q##BITS##_MIN; \
		return (i); \
	} \
	result = (t_s##BITS)(result * Q##BITS##_DENOM); \
	if CCCERROR((fraction._ >= 0 ? \
		(result > (t_s##BITS)(Q##BITS##_MAX_VAL._ - fraction._)) : \
		(result < (t_s##BITS)(Q##BITS##_MIN_VAL._ - fraction._))), ERROR_RESULTRANGE, \
		"fixed-point %s overflow for fraction part", ((fraction._ < 0) ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW((fraction._ < 0) ? Q##BITS##_MIN : Q##BITS##_MAX) \
		if (dest)	*dest = ((fraction._ < 0) ? Q##BITS##_MIN : Q##BITS##_MAX); \
		return (i); \
	} \
	if (dest)	*dest = (t_q##BITS){ (t_s##BITS)(result + fraction._) }; \
	return (i); \
failure: \
	if (dest)	*dest = Q##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_q##BITS	Q##BITS##_FromString##BASE(t_char const* str) \
{ \
	t_q##BITS	result = Q##BITS##_ERROR; \
	Q##BITS##_Parse##BASE(&result, str, 0); \
	return (result); \
} \

DEFINEFUNC_FIXED_FROMSTR(,		8, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	8, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	8, Char_IsDigit_Hex)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	8, Char_IsDigit_Oct)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	8, Char_IsDigit_Bin)

DEFINEFUNC_FIXED_FROMSTR(,		16, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	16, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	16, Char_IsDigit_Hex)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	16, Char_IsDigit_Oct)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	16, Char_IsDigit_Bin)

DEFINEFUNC_FIXED_FROMSTR(,		32, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	32, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	32, Char_IsDigit_Hex)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	32, Char_IsDigit_Oct)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	32, Char_IsDigit_Bin)

DEFINEFUNC_FIXED_FROMSTR(,		64, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	64, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	64, Char_IsDigit_Hex)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	64, Char_IsDigit_Oct)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	64, Char_IsDigit_Bin)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMSTR(,		128, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	128, Char_IsDigit)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	128, Char_IsDigit_Hex)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	128, Char_IsDigit_Oct)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	128, Char_IsDigit_Bin)
#endif



/*
**	These two helper functions are copies of the file-local (`static`) helpers
**	defined in `src/int/int_from_strbase.c`.
*/

//! Checks that the given number `base` string is valid, and returns its length (or a negative error code)
static
t_s32	Fixed_Base_GetLength(t_char const* base)
{
	t_size	i;
	t_size	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (-1);
		j = i;
		while (j--)
		{
			if (base[i] == base[j])
				return (-2);
		}
		++i;
	}
	return (i);
}

//! Returns the digit value of the char `c` in the given number `base`, or a negative value if `c` is not in the base
static
t_s32	Fixed_Base_IsInBase(t_char const* base, t_size base_length, char c)
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

//! Returns the length of the number token (optional sign + in-base chars) at the start of `str`, or `0` if there are no in-base chars
static
t_size	Fixed_Parse_Base_ScanToken(t_char const* str, t_size n, t_char const* base, t_size base_length)
{
	t_size	i = 0;
	t_size	digits = 0;

	if (i < n && (str[i] == '+' || str[i] == '-'))
		++i;
	while (i < n && str[i] && Fixed_Base_IsInBase(base, base_length, str[i]) >= 0)
	{
		++i;
		++digits;
	}
	return ((digits == 0) ? 0 : i);
}

/*
**	NOTE: if the given `base` string contains any of the structural characters
**	used by the fixed-point number representation (ie: '.', '(', ')' or '/'),
**	then this function cannot unambiguously parse the number components.
*/
#define DEFINEFUNC_FIXED_FROMSTRBASE(BITS) \
t_size	Q##BITS##_Parse_Base(t_q##BITS *dest, t_char const* str, t_char const* base, t_size n) \
{ \
	t_s##BITS	result = 0; \
	t_s##BITS	numerator = 0; \
	t_s##BITS	denominator = 1; \
	t_q##BITS	fraction = (t_q##BITS){ 0 }; \
	t_size	i = 0; \
	t_size	token; \
	t_s32	base_length; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL") \
		goto failure; \
	if CCCERROR((base == NULL), ERROR_NULLPOINTER, "numeric base string given is NULL") \
		goto failure; \
	base_length = Fixed_Base_GetLength(base); \
	if CCCERROR((base_length < 2), ERROR_INVALIDARGS, \
		"invalid number base given \"%s\"", base) \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (str[i] == '(') \
	{ \
		++i; \
		goto fraction; \
	} \
/*integer:*/ \
	token = Fixed_Parse_Base_ScanToken(str + i, n - i, base, (t_size)base_length); \
	if CCCERROR((token == 0), ERROR_PARSE, \
		"expected a number (with spaces/sign), but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse_Base(&result, str + i, base, token); \
/*separator:*/ \
	if (str[i] == '.')	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (i >= n || str[i] == '\0')	goto success; \
	if CCCERROR(!(str[i] == '+' || str[i] == '('), ERROR_PARSE, \
		"expected a fractional part separator char, but instead got \"%s\"", str) \
		goto failure; \
	if (str[i] == '(') \
		++i; \
fraction: \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	token = Fixed_Parse_Base_ScanToken(str + i, n - i, base, (t_size)base_length); \
	if CCCERROR((token == 0), ERROR_PARSE, \
		"expected a fraction numerator, but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse_Base(&numerator, str + i, base, token); \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '/'), ERROR_PARSE, \
		"expected a fraction '/' separator char, but instead got \"%s\"", str) \
		goto failure; \
	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	token = Fixed_Parse_Base_ScanToken(str + i, n - i, base, (t_size)base_length); \
	if CCCERROR((token == 0), ERROR_PARSE, \
		"expected a fraction denominator, but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse_Base(&denominator, str + i, base, token); \
	if CCCERROR((denominator == 0), ERROR_MATHDOMAIN, \
		"fraction denominator cannot be zero \"%s\"", str) \
		goto failure; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (str[i] == ')') \
		++i; \
	fraction = Q##BITS##_From(numerator, denominator); \
success: \
	if CCCERROR((result > (t_s##BITS)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)), ERROR_RESULTRANGE, \
		"fixed-point overflow for integer part at " SF_S##BITS, (t_s##BITS)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MAX) \
		if (dest)	*dest = Q##BITS##_MAX; \
		return (i); \
	} \
	if CCCERROR((result < (t_s##BITS)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM)), ERROR_RESULTRANGE, \
		"fixed-point underflow for integer part at " SF_S##BITS, (t_s##BITS)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM)) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MIN) \
		if (dest)	*dest = Q##BITS##_MIN; \
		return (i); \
	} \
	result = (t_s##BITS)(result * Q##BITS##_DENOM); \
	if CCCERROR((fraction._ >= 0 ? \
		(result > (t_s##BITS)(Q##BITS##_MAX_VAL._ - fraction._)) : \
		(result < (t_s##BITS)(Q##BITS##_MIN_VAL._ - fraction._))), ERROR_RESULTRANGE, \
		"fixed-point %s overflow for fraction part", ((fraction._ < 0) ? "negative" : "positive")) \
	{ \
		LIBCONFIG_ERROR_PARSEROVERFLOW((fraction._ < 0) ? Q##BITS##_MIN : Q##BITS##_MAX) \
		if (dest)	*dest = ((fraction._ < 0) ? Q##BITS##_MIN : Q##BITS##_MAX); \
		return (i); \
	} \
	if (dest)	*dest = (t_q##BITS){ (t_s##BITS)(result + fraction._) }; \
	return (i); \
failure: \
	if (dest)	*dest = Q##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_q##BITS	Q##BITS##_FromString_Base(t_char const* str, t_char const* base) \
{ \
	t_q##BITS	result = Q##BITS##_ERROR; \
	Q##BITS##_Parse_Base(&result, str, base, 0); \
	return (result); \
} \

DEFINEFUNC_FIXED_FROMSTRBASE(8)
DEFINEFUNC_FIXED_FROMSTRBASE(16)
DEFINEFUNC_FIXED_FROMSTRBASE(32)
DEFINEFUNC_FIXED_FROMSTRBASE(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMSTRBASE(128)
#endif
