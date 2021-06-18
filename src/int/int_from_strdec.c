
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define PARSE_RETURN(VALUE) \
	{	if (dest)	*dest = (VALUE);	return (i);	}



#define DEFINEFUNC_UINT_FROMSTRDEC(BITS) \
t_size	U##BITS##_Parse_Dec(t_u##BITS* dest, t_char const* str)						\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),										\
		PARSE_RETURN(U##BITS##_ERROR))												\
	while (str[i] && Char_IsSpace(str[i]))											\
	{																				\
		++i;																		\
	}																				\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || Char_IsDigit(str[i])),				\
		PARSE_RETURN(U##BITS##_ERROR),												\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	if (str[i] == '+')																\
		++i;																		\
	result = 0;																		\
	while (str[i] && Char_IsDigit(str[i]))											\
	{																				\
		tmp = result * 10 + (str[i++] - '0');										\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result),								\
			LIBCONFIG_ERROR_PARSEROVERFLOW(U##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_U##BITS")", str, U##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	if (dest)	*dest = result;														\
	return (i);																		\
}																					\
inline t_u##BITS	U##BITS##_FromString_Dec(t_char const* str)						\
{																					\
	t_u##BITS	result = U##BITS##_ERROR;											\
	U##BITS##_Parse_Dec(&result, str);												\
	return (result);																\
}																					\

DEFINEFUNC_UINT_FROMSTRDEC(8)
DEFINEFUNC_UINT_FROMSTRDEC(16)
DEFINEFUNC_UINT_FROMSTRDEC(32)
DEFINEFUNC_UINT_FROMSTRDEC(64)
#ifdef __int128
DEFINEFUNC_UINT_FROMSTRDEC(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRDEC(BITS) \
t_size	S##BITS##_Parse_Dec(t_s##BITS* dest, t_char const* str)						\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_bool	negative;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),										\
		PARSE_RETURN(S##BITS##_ERROR))												\
	while (str[i] && Char_IsSpace(str[i]))											\
	{																				\
		++i;																		\
	}																				\
	HANDLE_ERROR_SF(PARSE,															\
		!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),					\
		PARSE_RETURN(S##BITS##_ERROR),												\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	negative = FALSE;																\
	if (str[i] == '-')																\
	{																				\
		negative = TRUE;															\
		++i;																		\
	}																				\
	else if (str[i] == '+')															\
		++i;																		\
	result = 0;																		\
	while (str[i] && Char_IsDigit(str[i]))											\
	{																				\
		tmp = result * 10 + (str[i++] - '0');										\
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (t_u##BITS)S##BITS##_MIN),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MIN),							\
			" (integer underflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MIN)	\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (t_u##BITS)S##BITS##_MAX),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	if (dest)	*dest = (negative ? -(t_s##BITS)result : (t_s##BITS)result);		\
	return (i);																		\
}																					\
inline t_s##BITS	S##BITS##_FromString_Dec(t_char const* str)						\
{																					\
	t_s##BITS	result = S##BITS##_ERROR;											\
	S##BITS##_Parse_Dec(&result, str);												\
	return (result);																\
}																					\

DEFINEFUNC_SINT_FROMSTRDEC(8)
DEFINEFUNC_SINT_FROMSTRDEC(16)
DEFINEFUNC_SINT_FROMSTRDEC(32)
DEFINEFUNC_SINT_FROMSTRDEC(64)
#ifdef __int128
DEFINEFUNC_SINT_FROMSTRDEC(128)
#endif
