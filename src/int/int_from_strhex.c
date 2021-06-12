
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



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



#define DEFINEFUNC_UINT_FROMSTRHEX(BITS) \
t_u##BITS	U##BITS##_FromString_Hex(t_char const* str)								\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)							\
	while (*str && Char_IsSpace(*str))												\
	{																				\
		++str;																		\
	}																				\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || Char_IsDigit_Hex(*str)),				\
		return (0);,																\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	if (str[i] == '+')																\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'x')											\
		i += 2;																		\
	result = 0;																		\
	while (str[i] && (																\
		('0' <= str[i] && str[i] <= '9') ||											\
		('A' <= str[i] && str[i] <= 'F') ||											\
		('a' <= str[i] && str[i] <= 'f')))											\
	{																				\
		tmp = result * 16 + GetDigit_FromString_Hex(str[i++]);						\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result),								\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_U##BITS")", str, U##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	return (result);																\
}																					\

DEFINEFUNC_UINT_FROMSTRHEX(8)
DEFINEFUNC_UINT_FROMSTRHEX(16)
DEFINEFUNC_UINT_FROMSTRHEX(32)
DEFINEFUNC_UINT_FROMSTRHEX(64)
#ifdef __int128
DEFINEFUNC_UINT_FROMSTRHEX(128)
#endif



#define DEFINEFUNC_SINT_FROMSTRHEX(BITS) \
t_s##BITS	S##BITS##_FromString_Hex(t_char const* str)								\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_bool	negative;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)							\
	while (*str && Char_IsSpace(*str))												\
	{																				\
		++str;																		\
	}																				\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || *str == '-' || Char_IsDigit_Hex(*str)),	\
		return (0);,																\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	if (str[i] == '-')																\
	{																				\
		negative = TRUE;															\
		++i;																		\
	}																				\
	else if (str[i] == '+')															\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'x')											\
		i += 2;																		\
	result = 0;																		\
	while (str[i] && Char_IsDigit_Hex(str[i]))										\
	{																				\
		tmp = result * 16 + GetDigit_FromString_Hex(str[i++]);						\
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (t_u##BITS)-S##BITS##_MIN),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN),							\
			" (integer underflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MIN)	\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (t_u##BITS)S##BITS##_MAX),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);						\
}																					\

DEFINEFUNC_SINT_FROMSTRHEX(8)
DEFINEFUNC_SINT_FROMSTRHEX(16)
DEFINEFUNC_SINT_FROMSTRHEX(32)
DEFINEFUNC_SINT_FROMSTRHEX(64)
#ifdef __int128
DEFINEFUNC_SINT_FROMSTRHEX(128)
#endif
