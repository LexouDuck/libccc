
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



static
inline
int	GetDigit_FromString_Hex(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}



#define DEFINEFUNC_CONVERT_STRHEX_TO_UINT(BITS) \
t_u##BITS	U##BITS##_FromString_Hex(t_char const* str)							\
{																				\
	t_u##BITS	result;															\
	t_u##BITS	tmp;															\
	t_size	i;																	\
																				\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)						\
	i = 0;																		\
	while (!(str[i] == '+' ||													\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		HANDLE_ERROR_SF(PARSE, (!str[i] || !Char_IsSpace(str[i])),				\
			return (0);,														\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)	\
		++i;																	\
	}																			\
	if (str[i] == '+')															\
		++i;																	\
	if (str[i] == '0' && str[i + 1] == 'x')										\
		i += 2;																	\
	result = 0;																	\
	while (str[i] && (															\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		tmp = result * 16 + GetDigit_FromString_Hex(str[i++]);					\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result), LIBCONFIG_HANDLE_OVERFLOW,	\
		" (integer overflow for \"%s\" at "SF_U##BITS")", str, U##BITS##_MAX)	\
		result = tmp;															\
	}																			\
	return (result);															\
}																				\

DEFINEFUNC_CONVERT_STRHEX_TO_UINT(8)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(16)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(32)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(128)
#endif



#define DEFINEFUNC_CONVERT_STRHEX_TO_SINT(BITS) \
t_s##BITS	S##BITS##_FromString_Hex(t_char const* str)							\
{																				\
	t_u##BITS	result;															\
	t_u##BITS	tmp;															\
	t_bool	negative;															\
	t_size	i;																	\
																				\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)						\
	i = 0;																		\
	while (!(str[i] == '+' || str[i] == '+' ||									\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		HANDLE_ERROR_SF(PARSE, (!str[i] || !Char_IsSpace(str[i])),				\
			return (0);,														\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)	\
		++i;																	\
	}																			\
	if (str[i] == '-')															\
	{																			\
		negative = TRUE;														\
		++i;																	\
	}																			\
	else if (str[i] == '+')														\
		++i;																	\
	if (str[i] == '0' && str[i + 1] == 'x')										\
		i += 2;																	\
	result = 0;																	\
	while (str[i] && (															\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		tmp = result * 16 + GetDigit_FromString_Hex(str[i++]);					\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result), LIBCONFIG_HANDLE_OVERFLOW,	\
		" (integer overflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MAX)	\
		result = tmp;															\
	}																			\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);					\
}																				\

DEFINEFUNC_CONVERT_STRHEX_TO_SINT(8)
DEFINEFUNC_CONVERT_STRHEX_TO_SINT(16)
DEFINEFUNC_CONVERT_STRHEX_TO_SINT(32)
DEFINEFUNC_CONVERT_STRHEX_TO_SINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRHEX_TO_SINT(128)
#endif
