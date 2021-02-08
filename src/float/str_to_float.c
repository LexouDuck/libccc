
/*
**	Functions used from <stdlib.h>: (only when LIBCONFIG_USE_FAST_APPROX_MATH is 0)
**	-	double	atof(char* str);
*/
#include <stdlib.h>

#include "libccc/float.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/math/math.h"



#if LIBCONFIG_HANDLE_NULLPOINTERS
	#define LIBCONFIG_HANDLE_NULLPOINTER_STR_TO_FLOAT	if (str == NULL) return (0);
#else
	#define LIBCONFIG_HANDLE_NULLPOINTER_STR_TO_FLOAT	
#endif



//! Returns 1 if the given 'number' is either NaN, or +/- infinity
t_float	Float_FromString_CheckSpecial(char const* str)
{
	char sign = str[0];
	if (sign == '-' || sign == '+')
		++str;
	if (String_Equals_IgnoreCase(str, "NAN") ||
		String_Equals_IgnoreCase(str, "NOTANUMBER") ||
		String_Equals_IgnoreCase(str, "NOT A NUMBER"))
	{
		return (NAN);
	}
	if (String_Equals_IgnoreCase(str, "INF") ||
		String_Equals_IgnoreCase(str, "INFINITY") ||
		UTF8_Get((t_utf8*)str) == 0x221E) // infinity unicode char
	{
		return (sign == '-' ?
			-INFINITY :
			+INFINITY);
	}
	return (0.);
}

//! Returns TRUE if the given 'str' contains any invalid characters for float parsing, or FALSE otherwise
static t_bool	Float_FromString_CheckInvalid(char const* str)
{
	t_size	count_p;
	t_size	count_e;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (TRUE);
#endif
	if (str[0] == '\0')
		return (TRUE);
	if (str[0] != '+' &&
		str[0] != '-' &&
		str[0] != '.' &&
		!Char_IsDigit(str[0]))
		return (TRUE);
	count_p = String_Count_Char(str, 'p') + String_Count_Char(str, 'P');
	count_e = String_Count_Char(str, 'e') + String_Count_Char(str, 'E');
	if ((count_p > 1) ||
		(count_p == 0 && count_e > 1) ||
		!String_HasOnly(str, "0123456789ABCDEFabcdef.+-XPxp"))
		return (TRUE);
	return (FALSE);
}



#define DEFINEFUNC_STR_TO_FLOAT(BITS) \
t_f##BITS			F##BITS##_FromString(char const *str)					\
{																			\
	t_f##BITS	result;														\
LIBCONFIG_HANDLE_NULLPOINTER_STR_TO_FLOAT									\
	while (*str && Char_IsSpace(*str))										\
		++str;																\
	result = Float_FromString_CheckSpecial(str);							\
	if (result != 0.)														\
		return (result);													\
	if (Float_FromString_CheckInvalid(str))									\
		return (NAN);														\
	else if (String_Equals_N(str, "0b", 2))									\
		return (F##BITS##_FromString_Bin(str));								\
	else if (String_Equals_N(str, "0x", 2))									\
		return (F##BITS##_FromString_Hex(str));								\
	else if (String_Find_Charset(str, "eE") == NULL)						\
		return (F##BITS##_FromString_Dec(str));								\
	else																	\
		return (F##BITS##_FromString_Exp(str));								\
}																			\



#define DEFINEFUNC_STREXP_TO_FLOAT(BITS) \
t_f##BITS	F##BITS##_FromString_Exp(char const *str)						\
{																			\
	t_f##BITS	result;														\
	t_bool		negative;													\
	char const* str_mantissa;												\
	char const* str_exponent;												\
LIBCONFIG_HANDLE_NULLPOINTER_STR_TO_FLOAT									\
	while (*str && Char_IsSpace(*str))										\
		++str;																\
	result = Float_FromString_CheckSpecial(str);							\
	if (result != 0.)														\
		return (result);													\
	if (Float_FromString_CheckInvalid(str))									\
		return (NAN);														\
	negative = (str[0] == '-');												\
	str_mantissa = (negative || str[0] == '+') ? str + 1 : str;				\
	str_exponent = String_Find_Charset(str, "eE");							\
	if (str_exponent)	++str_exponent;										\
\
	t_s16		exponent;													\
	t_size		frac_digits;												\
	char*		tmp;														\
	if (!(tmp = String_Remove(str_mantissa, ".")))							\
		return (NAN);														\
	if (String_Length(tmp) > MAXDIGITS_64BIT)								\
		tmp[MAXDIGITS_64BIT] = '\0';										\
	result = (t_f##BITS)S64_FromString(tmp);								\
	Memory_Free(tmp);														\
	if (!(exponent = 0) && str_exponent)									\
	{																		\
		exponent = S16_FromString(str_exponent);							\
		if (exponent > F##BITS##_EXPONENT_BIAS)								\
			return (negative ? -INFINITY : INFINITY);						\
		else if (exponent < 1 - F##BITS##_EXPONENT_BIAS)					\
			return (0.);													\
	}																		\
	tmp = String_Find_Char(str_mantissa, '.');								\
	if (tmp && (frac_digits = String_Length(++tmp)) > 0)					\
		exponent -= frac_digits;											\
	if (String_Length(str_mantissa) > MAXDIGITS_64BIT)						\
		exponent += String_Length(str_mantissa) - MAXDIGITS_64BIT;			\
	return (result * Math_Pow(10., exponent));								\
}																			\



#define DEFINEFUNC_STRDEC_TO_FLOAT(BITS) \
inline t_f##BITS	F##BITS##_FromString_Dec(char const* str)				\
{																			\
	t_f##BITS	result = Float_FromString_CheckSpecial(str);				\
	if (result != 0.)														\
		return (result);													\
	char*	tmp;															\
	if (!(tmp = String_Remove(str, ".")))									\
		return (NAN);														\
	if (String_Length(tmp) > MAXDIGITS_64BIT)								\
		tmp[MAXDIGITS_64BIT] = '\0';										\
	result = (t_f##BITS)S64_FromString(tmp);								\
	Memory_Free(tmp);														\
	return (result);														\
}																			\



#define DEFINEFUNC_STRHEX_TO_FLOAT(BITS) \
t_f##BITS	F##BITS##_FromString_Hex(char const* str)						\
{																			\
	t_f##BITS	result;														\
	t_bool		negative;													\
	char const* str_mantissa;												\
	char const* str_exponent;												\
LIBCONFIG_HANDLE_NULLPOINTER_STR_TO_FLOAT									\
	while (*str && Char_IsSpace(*str))										\
		++str;																\
	result = Float_FromString_CheckSpecial(str);							\
	if (result != 0.)														\
		return (result);													\
	if (Float_FromString_CheckInvalid(str))									\
		return (NAN);														\
	negative = (str[0] == '-');												\
	str_mantissa = (negative || str[0] == '+') ? str + 1 : str;				\
	str_exponent = String_Find_Charset(str, "pP");							\
	if (str_exponent)	++str_exponent;										\
\
	t_u##BITS	mantissa;													\
	t_s16		exponent;													\
	char*		tmp;														\
	result = (negative ? -1. : 1.);											\
	tmp = String_Remove(str_mantissa, ".");									\
	if (String_Equals(tmp, "0") || String_Equals(tmp, "00"))				\
	{																		\
		Memory_Free(tmp);													\
		return (0. * result);												\
	}																		\
	mantissa = U64_FromString_Hex(tmp);										\
	result *= (mantissa * F##BITS##_INIT_VALUE) *							\
		Math_Pow(2., (String_Length(tmp) - 1) * 4);							\
	exponent = S16_FromString(str_exponent);								\
	if (exponent > F##BITS##_EXPONENT_BIAS)									\
		return ((negative ? -1. : 1.) / 0.);								\
	else if (exponent < 1 - F##BITS##_EXPONENT_BIAS)						\
		return (0.);														\
	Memory_Copy(&mantissa, &result, sizeof(result));						\
	mantissa &= F##BITS##_MANTISSA_SIGNED;									\
	mantissa |= F##BITS##_EXPONENT & ((t_u##BITS)							\
		(exponent + F##BITS##_EXPONENT_BIAS) << F##BITS##_MANTISSA_BITS);	\
	Memory_Copy(&result, &mantissa, sizeof(result));						\
	Memory_Free(tmp);														\
	return (result);														\
}																			\



// TODO Float_ToString_Bin()
#define DEFINEFUNC_STRBIN_TO_FLOAT(BITS) \
t_f##BITS	F##BITS##_FromString_Bin(char const* str)						\
{ return (str == NULL ? NAN : 0.); }



DEFINEFUNC_STR_TO_FLOAT(   32)
DEFINEFUNC_STREXP_TO_FLOAT(32)
DEFINEFUNC_STRDEC_TO_FLOAT(32)
DEFINEFUNC_STRHEX_TO_FLOAT(32)
DEFINEFUNC_STRBIN_TO_FLOAT(32)

DEFINEFUNC_STR_TO_FLOAT(   64)
DEFINEFUNC_STREXP_TO_FLOAT(64)
DEFINEFUNC_STRDEC_TO_FLOAT(64)
DEFINEFUNC_STRHEX_TO_FLOAT(64)
DEFINEFUNC_STRBIN_TO_FLOAT(64)

#ifdef __float80
DEFINEFUNC_STR_TO_FLOAT(   80)
DEFINEFUNC_STREXP_TO_FLOAT(80)
DEFINEFUNC_STRDEC_TO_FLOAT(80)
DEFINEFUNC_STRHEX_TO_FLOAT(80)
DEFINEFUNC_STRBIN_TO_FLOAT(80)
#endif

#ifdef __float128
DEFINEFUNC_STR_TO_FLOAT(   128)
DEFINEFUNC_STREXP_TO_FLOAT(128)
DEFINEFUNC_STRDEC_TO_FLOAT(128)
DEFINEFUNC_STRHEX_TO_FLOAT(128)
DEFINEFUNC_STRBIN_TO_FLOAT(128)
#endif



#define TYPE_FLOAT	CONCAT(F,LIBCONFIG_BITS_FLOAT)

inline t_float	Float_FromString    (char const* str)	{ return (CONCAT(TYPE_FLOAT,_FromString    )(str)); }
inline t_float	Float_FromString_Exp(char const* str)	{ return (CONCAT(TYPE_FLOAT,_FromString_Exp)(str)); }
inline t_float	Float_FromString_Dec(char const* str)	{ return (CONCAT(TYPE_FLOAT,_FromString_Dec)(str)); }
inline t_float	Float_FromString_Hex(char const* str)	{ return (CONCAT(TYPE_FLOAT,_FromString_Hex)(str)); }
inline t_float	Float_FromString_Bin(char const* str)	{ return (CONCAT(TYPE_FLOAT,_FromString_Bin)(str)); }
