
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define PARSE_RETURN(VALUE) \
	if (dest)	*dest = (VALUE);	return (i);



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
t_size	U##BITS##_Parse_Base(t_u##BITS* dest, t_char const* str, t_char const* base)\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_s32	digit;																	\
	t_size	length;																	\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),										\
		PARSE_RETURN(U##BITS##_ERROR))												\
	HANDLE_ERROR(NULLPOINTER, (base == NULL),										\
		PARSE_RETURN(U##BITS##_ERROR))												\
	digit = String_Base_GetLength(base);											\
	HANDLE_ERROR_SF(INVALIDARGS, (digit == INVALID_BASE_SIGNCHAR),					\
		PARSE_RETURN(U##BITS##_ERROR),												\
		": number base (\"%s\") cannot contain sign chars ('+' or '-')", base)		\
	HANDLE_ERROR_SF(INVALIDARGS, (digit == INVALID_BASE_DUPLICATE),					\
		PARSE_RETURN(U##BITS##_ERROR),												\
		": number base (\"%s\") must not have any duplicate characters", base)		\
	HANDLE_ERROR_SF(LENGTH2SMALL, (digit < 2),										\
		PARSE_RETURN(U##BITS##_ERROR),												\
		", number base (\"%s\") should be at least 2 chars long", base)				\
	length = (t_size)digit;															\
	i = 0;																			\
	while (!(str[i] == '+' || str[i] == '-'))										\
	{																				\
		digit = String_Base_IsInBase(base, length, str[i]);							\
		if (digit >= 0) break;														\
		HANDLE_ERROR_SF(PARSE, (!str[i] || !Char_IsSpace(str[i])),					\
			PARSE_RETURN(U##BITS##_ERROR),											\
			": expected a number (with spaces/sign), but instead got \"%s\"", str)	\
		++i;																		\
	}																				\
	if (str[i] == '+' || str[i] == '-')												\
		++i;																		\
	result = 0;																		\
	while (str[i])																	\
	{																				\
		digit = String_Base_IsInBase(base, length, str[i++]);						\
		HANDLE_ERROR_SF(PARSE, (digit < 0),											\
			PARSE_RETURN(U##BITS##_ERROR),											\
			": digit char '%c' is not in number base \"%s\"", str[i - 1], base)		\
		tmp = result * length + digit;												\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result),								\
			LIBCONFIG_ERROR_PARSEROVERFLOW(U##BITS##_MAX),							\
			" (integer overflow for \"%s\" with base \"%s\" at "SF_S##BITS")",		\
			str, base, U##BITS##_MAX)												\
		result = tmp;																\
	}																				\
	if (dest)	*dest = result;														\
	return (i);																		\
}																					\
inline t_u##BITS	U##BITS##_FromString_Base(t_char const* str, t_char const* base)\
{																					\
	t_u##BITS	result = U##BITS##_ERROR;											\
	U##BITS##_Parse_Base(&result, str, base);										\
	return (result);																\
}																					\

DEFINEFUNC_UINT_FROMSTRBASE(8)
DEFINEFUNC_UINT_FROMSTRBASE(16)
DEFINEFUNC_UINT_FROMSTRBASE(32)
DEFINEFUNC_UINT_FROMSTRBASE(64)
#ifdef __int128
DEFINEFUNC_UINT_FROMSTRBASE(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRBASE(BITS) \
t_size	S##BITS##_Parse_Base(t_s##BITS* dest, t_char const* str, t_char const* base)\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_bool	negative;																\
	t_s32	digit;																	\
	t_size	length;																	\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),										\
		PARSE_RETURN(S##BITS##_ERROR))												\
	HANDLE_ERROR(NULLPOINTER, (base == NULL),										\
		PARSE_RETURN(S##BITS##_ERROR))												\
	digit = String_Base_GetLength(base);											\
	HANDLE_ERROR_SF(INVALIDARGS, (digit == INVALID_BASE_SIGNCHAR),					\
		PARSE_RETURN(S##BITS##_ERROR),												\
		": number base (\"%s\") cannot contain sign chars ('+' or '-')", base)		\
	HANDLE_ERROR_SF(INVALIDARGS, (digit == INVALID_BASE_DUPLICATE),					\
		PARSE_RETURN(S##BITS##_ERROR),												\
		": number base (\"%s\") must not have any duplicate characters", base)		\
	HANDLE_ERROR_SF(LENGTH2SMALL, (digit < 2),										\
		PARSE_RETURN(S##BITS##_ERROR),												\
		", number base (\"%s\") should be at least 2 chars long", base)				\
	length = (t_size)digit;															\
	i = 0;																			\
	while (!(str[i] == '+' || str[i] == '-'))										\
	{																				\
		digit = String_Base_IsInBase(base, length, str[i]);							\
		if (digit >= 0) break;														\
		HANDLE_ERROR_SF(PARSE, (!str[i] || !Char_IsSpace(str[i])),					\
			PARSE_RETURN(S##BITS##_ERROR),											\
			": expected a number (with spaces/sign), but instead got \"%s\"", str)	\
		++i;																		\
	}																				\
	negative = FALSE;																\
	if (str[i] == '-')																\
	{																				\
		negative = TRUE;															\
		++i;																		\
	}																				\
	else if (str[i] == '+')															\
		++i;																		\
	result = 0;																		\
	while (str[i])																	\
	{																				\
		digit = String_Base_IsInBase(base, length, str[i++]);						\
		HANDLE_ERROR_SF(PARSE, (digit < 0),											\
			PARSE_RETURN(S##BITS##_ERROR),											\
			": digit char '%c' is not in number base \"%s\"", str[i - 1], base)		\
		tmp = result * length + digit;												\
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (t_u##BITS)S##BITS##_MIN),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MIN),							\
			" (integer underflow for \"%s\" with base \"%s\" at "SF_S##BITS")",		\
			str, base, S##BITS##_MIN)												\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (t_u##BITS)S##BITS##_MAX),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(S##BITS##_MAX),							\
			" (integer overflow for \"%s\" with base \"%s\" at "SF_S##BITS")",		\
			str, base, S##BITS##_MAX)												\
		result = tmp;																\
	}																				\
	if (dest)	*dest = (negative ? -(t_s##BITS)result : (t_s##BITS)result);		\
	return (i);																		\
}																					\
inline t_s##BITS	S##BITS##_FromString_Base(t_char const* str, t_char const* base)\
{																					\
	t_s##BITS	result = S##BITS##_ERROR;											\
	S##BITS##_Parse_Base(&result, str, base);										\
	return (result);																\
}																					\

DEFINEFUNC_SINT_FROMSTRBASE(8)
DEFINEFUNC_SINT_FROMSTRBASE(16)
DEFINEFUNC_SINT_FROMSTRBASE(32)
DEFINEFUNC_SINT_FROMSTRBASE(64)
#ifdef __int128
DEFINEFUNC_SINT_FROMSTRBASE(128)
#endif
