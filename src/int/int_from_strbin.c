
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTRBIN(BITS) \
t_size	U##BITS##_Parse_Bin(t_u##BITS* dest, t_char const* str, t_size n)			\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_size	i = 0;																	\
																					\
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")	\
		PARSE_RETURN(U##BITS##_ERROR)												\
	if (n == 0)																		\
		n = SIZE_MAX;																\
	while (i < n && str[i] && Char_IsSpace(str[i]))									\
	{																				\
		++i;																		\
	}																				\
	if CCCERROR(!(str[i] == '+' || Char_IsDigit_Bin(str[i])), ERROR_PARSE,			\
		"expected a number (with spaces/sign), but instead got \"%s\"", str)		\
		PARSE_RETURN(U##BITS##_ERROR);												\
	if (str[i] == '+')																\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'b')											\
		i += 2;																		\
	result = 0;																		\
	while (i < n && str[i] && Char_IsDigit_Bin(str[i]))								\
	{																				\
		tmp = result * 2 + (str[i++] - '0');										\
		if CCCERROR((tmp < result), ERROR_RESULTRANGE,								\
			#BITS"-bit unsigned integer overflow for \"%s\" at "SF_U##BITS,			\
			str, U##BITS##_MAX)														\
			LIBCONFIG_ERROR_PARSEROVERFLOW(U##BITS##_MAX)							\
		result = tmp;																\
	}																				\
	if (dest)	*dest = result;														\
	return (i);																		\
}																					\
inline t_u##BITS	U##BITS##_FromString_Bin(t_char const* str)						\
{																					\
	t_u##BITS	result = U##BITS##_ERROR;											\
	U##BITS##_Parse_Bin(&result, str, 0);											\
	return (result);																\
}

DEFINEFUNC_UINT_FROMSTRBIN(8)
DEFINEFUNC_UINT_FROMSTRBIN(16)
DEFINEFUNC_UINT_FROMSTRBIN(32)
DEFINEFUNC_UINT_FROMSTRBIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMSTRBIN(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRBIN(BITS) \
t_size	S##BITS##_Parse_Bin(t_s##BITS* dest, t_char const* str, t_size n)			\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_bool	negative;																\
	t_size	i = 0;																	\
																					\
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")	\
		PARSE_RETURN(S##BITS##_ERROR)												\
	if (n == 0)																		\
		n = SIZE_MAX;																\
	while (i < n && str[i] && Char_IsSpace(str[i]))									\
	{																				\
		++i;																		\
	}																				\
	if CCCERROR(!(str[i] == '+' || str[i] == '-' || Char_IsDigit_Bin(str[i])), ERROR_PARSE,	\
		"expected a number (with spaces/sign), but instead got \"%s\"", str)		\
		PARSE_RETURN(S##BITS##_ERROR);												\
	negative = FALSE;																\
	if (str[i] == '-')																\
	{																				\
		negative = TRUE;															\
		++i;																		\
	}																				\
	else if (str[i] == '+')															\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'b')											\
		i += 2;																		\
	result = 0;																		\
	while (i < n && str[i] && Char_IsDigit_Bin(str[i]))								\
	{																				\
		tmp = result * 2 + (str[i++] - '0');										\
		if CCCERROR((negative && tmp > (t_u##BITS)S##BITS##_MIN), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer underflow for \"%s\" at "SF_S##BITS,			\
			str, S##BITS##_MIN)														\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MIN)							\
		if CCCERROR((!negative && tmp > (t_u##BITS)S##BITS##_MAX), ERROR_RESULTRANGE,\
			#BITS"-bit signed integer overflow for \"%s\" at "SF_S##BITS,			\
			str, S##BITS##_MAX)														\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MAX)							\
		result = tmp;																\
	}																				\
	if (dest)	*dest = (negative ? -(t_s##BITS)result : (t_s##BITS)result);		\
	return (i);																		\
}																					\
inline t_s##BITS	S##BITS##_FromString_Bin(t_char const* str)						\
{																					\
	t_s##BITS	result = S##BITS##_ERROR;											\
	S##BITS##_Parse_Bin(&result, str, 0);											\
	return (result);																\
}

DEFINEFUNC_SINT_FROMSTRBIN(8)
DEFINEFUNC_SINT_FROMSTRBIN(16)
DEFINEFUNC_SINT_FROMSTRBIN(32)
DEFINEFUNC_SINT_FROMSTRBIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMSTRBIN(128)
#endif
