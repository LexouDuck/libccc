
#ifndef __NOSTD__
	#include <stdlib.h>
#else
	float		strtof	(char const* str, char** str_end);
	double		strtod	(char const* str, char** str_end);
	long double	strtold	(char const* str, char** str_end);
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/pointer.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/math/int.h"
#include "libccc/math/float.h"
#include "libccc/text/char_unicode.h"

#include LIBCONFIG_ERROR_INCLUDE



//! The maximum amount of digits that can be printed to the mantissa
#define MAXLEN_MANTISSA	(64)



//! Returns 1 if the given 'number' is either NaN, or +/- infinity
static
t_float	Float_Parse_CheckSpecial(t_char const* str)
{
	t_char sign = *str;
	if (sign == '-' || sign == '+')
	{
		++str;
	}
	if (CharUTF32_FromUTF8((t_utf8*)str) == 0x221E) // infinity unicode char
	{
		if (!Char_IsSpace(str[3]) &&
			!Char_IsPunct(str[3]) &&
			str[3] != '\0')
			return (0.);
		if (sign == '-')	return (-INF);
		if (sign == '+')	return (+INF);
		return (INF);
	}
	if (String_Equals_N_IgnoreCase(str, "INFINITY", 8)) // lenient full-word
	{
		if (!Char_IsSpace(str[8]) &&
			!Char_IsPunct(str[8]) &&
			str[8] != '\0')
			return (0.);
		if (sign == '-')	return (-INF);
		if (sign == '+')	return (+INF);
		return (INF);
	}
	if (String_Equals_N_IgnoreCase(str, "INF", 3))
	{
		if (!Char_IsSpace(str[3]) &&
			!Char_IsPunct(str[3]) &&
			str[3] != '\0')
			return (0.);
		if (sign == '-')	return (-INF);
		if (sign == '+')	return (+INF);
		return (INF);
	}
	if (String_Equals_N_IgnoreCase(str, "NAN", 3))
	{
		if (!Char_IsSpace(str[3]) &&
			!Char_IsPunct(str[3]) &&
			str[3] != '\0')
			return (0.);
		if (sign == '-')	return (-NAN);
		if (sign == '+')	return (+NAN);
		return (NAN);
	}
	return (0.);
}

//! Returns `TRUE` if the given `str` contains any invalid characters for float parsing, or FALSE otherwise
static
t_bool	Float_Parse_CheckInvalid(t_char const* str)
{
	t_size	count_expon;
	t_size	count_signs;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (*str == '\0')
		return (ERROR);
	if (*str != '+' &&
		*str != '-' &&
		*str != '.' &&
		!Char_IsDigit(*str))
		return (ERROR);
	if (String_HasOnly(str, "+-0123456789.eE"))
		count_expon = String_Count_Charset(str, "eE");	// decimal
	else if (String_HasOnly(str, "xX+-0123456789aAbBcCdDeEfF.pP"))
		count_expon = String_Count_Charset(str, "pP");	// hexadecimal
	else if (String_HasOnly(str, "oO+-01234567.pP"))
		count_expon = String_Count_Charset(str, "pP");	// octal
	else if (String_HasOnly(str, "bB+-01.pP"))
		count_expon = String_Count_Charset(str, "pP");	// binary
	else return (ERROR);

	if (count_expon > 1)
		return (ERROR);
	count_signs = String_Count_Charset(str, "-+");
	if (count_expon)	{ if (count_signs > 2)	return (ERROR); }
	else				{ if (count_signs > 1)	return (ERROR); }
	return (OK);
}

/*

#define ASSEMBLE_FLOAT_SIMPLE(BITS) \
	mantissa &= F##BITS##_MANTISSA_SIGNED; \
	mantissa |= F##BITS##_EXPONENT_MASK & ((t_uintmax) \
		(exponent + F##BITS##_EXPONENT_BIAS) << F##BITS##_MANTISSA_BITS); \
	Memory_Copy(&result, &mantissa, sizeof(result)); \

#define ASSEMBLE_FLOAT_EXTEND(BITS) \
	Memory_Copy(&result, &mantissa, sizeof(result)); \
	exponent += F##BITS##_EXPONENT_BIAS; \
	Memory_Copy(&result + F##BITS##_MANTISSA_BITS / 8, &exponent, sizeof(result));
// TODO fix this ^

#define ASSEMBLE_FLOAT_32() \
		ASSEMBLE_FLOAT_SIMPLE(32)
#define ASSEMBLE_FLOAT_64() \
		ASSEMBLE_FLOAT_SIMPLE(64)
#define ASSEMBLE_FLOAT_80() \
		ASSEMBLE_FLOAT_EXTEND(80)
#define ASSEMBLE_FLOAT_128() \
		ASSEMBLE_FLOAT_EXTEND(128)

#define ASSEMBLE_FLOAT(BITS) \
		ASSEMBLE_FLOAT_##BITS()

*/

#define DEFINEFUNC_FLOAT_FROMSTR(BITS) \
t_size	F##BITS##_Parse(t_f##BITS *dest, t_char const* str, t_size n) \
{ \
	t_char const* s = NULL; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	for (i = 0; (i < n && str[i]); ++i) \
	{ \
		if (str[i] == '0') \
			s = str + i; \
	} \
	if (s && s[0] && s[0] == '0') \
	{ \
		switch (s[1]) \
		{ \
			case 'x': return (F##BITS##_Parse_Hex(dest, str, n - i)); \
			case 'o': return (F##BITS##_Parse_Oct(dest, str, n - i)); \
			case 'b': return (F##BITS##_Parse_Bin(dest, str, n - i)); \
		} \
	} \
	return (F##BITS##_Parse_Dec(dest, str, n - i)); \
failure: \
	if (dest)	*dest = F##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_f##BITS	F##BITS##_FromString(t_char const* str) \
{ \
	t_f##BITS	result = F##BITS##_ERROR; \
	F##BITS##_Parse(&result, str, 0); \
	return (result); \
} \



#define DEFINEFUNC_FLOAT_FROMSTRDEC(BITS) \
t_size	F##BITS##_Parse_Dec(t_f##BITS *dest, t_char const* str, t_size n) \
{ \
	t_f##BITS	result; \
	t_char const* str_mantissa; \
	t_char const* str_exponent; \
	t_size		frac_digits; \
	t_bool		negative; \
	t_s16		exponent; \
	t_char*		tmp; \
	t_size	i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	result = Float_Parse_CheckSpecial(str + i); \
	if (result != 0.) \
		goto success; \
	if (Float_Parse_CheckInvalid(str + i)) \
		goto failure; \
	if (!(str[i] == '+' || str[i] == '-' || str[i] == '.' || Char_IsDigit(str[i]))) \
		goto failure; \
if (!LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && !LIBCONFIG_USE_STD_MATH) {} /* stdlib wrappers */\
else if (BITS == 32) { result = strtof(str + i, &tmp);	i += (tmp - str);	goto success; } \
else if (BITS == 64) { result = strtod(str + i, &tmp);	i += (tmp - str);	goto success; } \
else				 { result = strtold(str + i, &tmp);	i += (tmp - str);	goto success; } \
	negative = FALSE; \
	if (str[i] == '-') \
	{ \
		negative = TRUE; \
		++i; \
	} \
	else if (str[i] == '+') \
		++i; \
	str_mantissa = str + i; \
	result = 0.; \
	while (i < n && str[i] && Char_IsDigit(str[i])) \
	{ \
		result = result * 10 + (str[i++] - '0'); \
	} \
	exponent = 0; \
	str_exponent = String_Find_Charset(str + i, "eE"); \
	if (str_exponent) \
	{ \
		++str_exponent; \
		i = S16_Parse_Dec(&exponent, str_exponent, n); \
		i = ((i + str_exponent) - str); \
		if (exponent > F##BITS##_EXPONENT_BIAS) \
		{ \
			result = (negative ? -INFINITY : INFINITY); \
			goto success; \
		} \
		else if (exponent < 1 - F##BITS##_EXPONENT_BIAS) \
		{ \
			result = (0.); \
			goto success; \
		} \
	} \
	tmp = String_Find_Char(str_mantissa, '.'); \
	if (tmp && (frac_digits = String_Length(++tmp)) > 0) \
		exponent -= frac_digits; \
	if (String_Length(str_mantissa) > MAXLEN_MANTISSA) \
		exponent += String_Length(str_mantissa) - MAXLEN_MANTISSA; \
	result *= F##BITS##_Pow(10., exponent) * (negative ? -1 : 1); \
success: \
	if (dest)	*dest = result; \
	return (i); \
failure: \
	if (dest)	*dest = F##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_f##BITS	F##BITS##_FromString_Dec(t_char const* str) \
{ \
	t_f##BITS	result = F##BITS##_ERROR; \
	F##BITS##_Parse_Dec(&result, str, 0); \
	return (result); \
} \



#define DEFINEFUNC_FLOAT_FROMSTRHEX(BITS) \
t_size	F##BITS##_Parse_Hex(t_f##BITS *dest, t_char const* str, t_size n) \
{ \
	t_f##BITS	result; \
	t_char const* str_mantissa; \
	t_char const* str_exponent; \
	t_bool		negative; \
	t_u64		mantissa; \
	t_s16		exponent; \
	t_char*		tmp; \
	t_size		i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	result = Float_Parse_CheckSpecial(str + i); \
	if (result != 0.) \
		goto success; \
	if (Float_Parse_CheckInvalid(str + i)) \
		goto failure; \
	if (!(str[i] == '+' || str[i] == '-' || str[i] == '.' || Char_IsDigit_Hex(str[i]))) \
		goto failure; \
	negative = (str[i] == '-'); \
	str_mantissa = (negative || str[i] == '+') ? \
		(str + i + 1) : (str + i); \
	result = (negative ? -1. : +1.); \
	tmp = String_Remove(str_mantissa, "."); \
	if (String_HasOnly(tmp, "0")) \
	{ \
		Memory_Free(tmp); \
		result *= 0.; \
		goto success; \
	} \
	i += U64_Parse_Hex(&mantissa, tmp, n - i); \
	result *= (mantissa * F##BITS##_INIT_VALUE) * \
		Float_Pow(2., (String_Length(tmp) - 1) * 4); \
	str_exponent = String_Find_Charset(str + i, "pP"); \
	if (str_exponent) \
	{ \
		++str_exponent; \
		i += S16_Parse_Hex(&exponent, str_exponent, n); \
	} \
	else exponent = 0; \
	if (exponent > F##BITS##_EXPONENT_BIAS) \
	{ \
		result = ((negative ? -1. : 1.) / 0.); \
		goto success; \
	} \
	else if (exponent < 1 - F##BITS##_EXPONENT_BIAS) \
	{ \
		result = (0.); \
		goto success; \
	} \
	Memory_Copy(&mantissa, &result, \
		SInt_Min(sizeof(t_uintmax), sizeof(result))); \
	/*ASSEMBLE_FLOAT(BITS)*/ \
	mantissa = Memory_GetBits(&result, 0, F##BITS##_MANTISSA_BITS); \
/*	Memory_Clear(&result, sizeof(result));	*/ \
	Memory_SetBits(&result, \
		F##BITS##_EXPONENT_BITS + 1, \
		F##BITS##_MANTISSA_BITS, mantissa); \
	Memory_SetBits(&result, 1, \
		F##BITS##_EXPONENT_BITS, exponent); \
	/*ASSEMBLE_FLOAT(BITS)*/ \
	Memory_Free(tmp); \
success: \
	if (dest)	*dest = result; \
	return (i); \
failure: \
	if (dest)	*dest = F##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_f##BITS	F##BITS##_FromString_Hex(t_char const* str) \
{ \
	t_f##BITS	result = F##BITS##_ERROR; \
	F##BITS##_Parse_Hex(&result, str, 0); \
	return (result); \
} \



#define DEFINEFUNC_FLOAT_FROMSTROCT(BITS) \
t_size	F##BITS##_Parse_Oct(t_f##BITS *dest, t_char const* str, t_size n) \
{ \
	t_f##BITS	result; \
	t_size		i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	result = Float_Parse_CheckSpecial(str + i); \
	if (result != 0.) \
		goto success; \
	if (Float_Parse_CheckInvalid(str + i)) \
		goto failure; \
	if (!(str[i] == '+' || str[i] == '-' || str[i] == '.' || Char_IsDigit_Oct(str[i]))) \
		goto failure; \
/* TODO */ \
success: \
	if (dest)	*dest = result; \
	return (0); \
failure: \
	if (dest)	*dest = F##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_f##BITS	F##BITS##_FromString_Oct(t_char const* str) \
{ \
	t_f##BITS	result = F##BITS##_ERROR; \
	F##BITS##_Parse_Oct(&result, str, 0); \
	return (result); \
} \



#define DEFINEFUNC_FLOAT_FROMSTRBIN(BITS) \
t_size	F##BITS##_Parse_Bin(t_f##BITS *dest, t_char const* str, t_size n) \
{ \
	t_f##BITS	result; \
	t_size		i = 0; \
 \
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL") \
		goto failure; \
	if (n == 0) \
		n = SIZE_MAX; \
	while (i < n && str[i] && Char_IsSpace(str[i])) \
	{ \
		++i; \
	} \
	result = Float_Parse_CheckSpecial(str + i); \
	if (result != 0.) \
		goto success; \
	if (Float_Parse_CheckInvalid(str + i)) \
		goto failure; \
	if (!(str[i] == '+' || str[i] == '-' || str[i] == '.' || Char_IsDigit_Bin(str[i]))) \
		goto failure; \
/* TODO */ \
success: \
	if (dest)	*dest = NAN; \
	return (0); \
failure: \
	if (dest)	*dest = F##BITS##_ERROR; \
	return (i); \
} \
_INLINE() \
t_f##BITS	F##BITS##_FromString_Bin(t_char const* str) \
{ \
	t_f##BITS	result = F##BITS##_ERROR; \
	F##BITS##_Parse_Bin(&result, str, 0); \
	return (result); \
} \



DEFINEFUNC_FLOAT_FROMSTR(   32)
DEFINEFUNC_FLOAT_FROMSTRDEC(32)
DEFINEFUNC_FLOAT_FROMSTRHEX(32)
DEFINEFUNC_FLOAT_FROMSTROCT(32)
DEFINEFUNC_FLOAT_FROMSTRBIN(32)
//DEFINEFUNC_FLOAT_FROMSTRBASE(32)

DEFINEFUNC_FLOAT_FROMSTR(   64)
DEFINEFUNC_FLOAT_FROMSTRDEC(64)
DEFINEFUNC_FLOAT_FROMSTRHEX(64)
DEFINEFUNC_FLOAT_FROMSTROCT(64)
DEFINEFUNC_FLOAT_FROMSTRBIN(64)
//DEFINEFUNC_FLOAT_FROMSTRBASE(64)

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FROMSTR(   80)
DEFINEFUNC_FLOAT_FROMSTRDEC(80)
DEFINEFUNC_FLOAT_FROMSTRHEX(80)
DEFINEFUNC_FLOAT_FROMSTROCT(80)
DEFINEFUNC_FLOAT_FROMSTRBIN(80)
//DEFINEFUNC_FLOAT_FROMSTRBASE(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FROMSTR(   128)
DEFINEFUNC_FLOAT_FROMSTRDEC(128)
DEFINEFUNC_FLOAT_FROMSTRHEX(128)
DEFINEFUNC_FLOAT_FROMSTROCT(128)
DEFINEFUNC_FLOAT_FROMSTRBIN(128)
//DEFINEFUNC_FLOAT_FROMSTRBASE(128)
#endif
