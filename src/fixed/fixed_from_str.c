
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/string.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FROMSTR(BASE, BITS) \
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
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])), ERROR_PARSE, \
		"expected a number (with spaces/sign), but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse##BASE(&result, str + i, n - i); \
/*separator:*/ \
	if (str[i] == '.')	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if (str[i] == '\0')	goto success; \
	if CCCERROR(!(str[i] == '+' || str[i] == '('), ERROR_PARSE, \
		"expected a fractional part separator char, but instead got \"%s\"", str) \
		goto failure; \
	if (str[i] == '(') \
		++i; \
fraction: \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])), ERROR_PARSE, \
		"expected a fraction numerator, but instead got \"%s\"", str) \
		goto failure; \
	i += S##BITS##_Parse##BASE(&numerator, str + i, n - i); \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '/'), ERROR_PARSE, \
		"expected a fraction '/' separator char, but instead got \"%s\"", str) \
		goto failure; \
	++i; \
	while (i < n && str[i] && Char_IsSpace(str[i]))	{ ++i; } \
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])), ERROR_PARSE, \
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

DEFINEFUNC_FIXED_FROMSTR(,		8)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	8)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	8)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	8)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	8)

DEFINEFUNC_FIXED_FROMSTR(,		16)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	16)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	16)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	16)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	16)

DEFINEFUNC_FIXED_FROMSTR(,		32)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	32)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	32)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	32)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	32)

DEFINEFUNC_FIXED_FROMSTR(,		64)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	64)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	64)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	64)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_FROMSTR(,		128)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	128)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	128)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	128)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	128)
#endif
