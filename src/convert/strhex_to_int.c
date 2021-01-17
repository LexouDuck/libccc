
#include "libccc_char.h"
#include "libccc_convert.h"



#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	#define LIBCCCCONFIG_HANDLE_NULLPOINTER_STR_TO_INT	if (str == NULL) return (0);
#else
	#define LIBCCCCONFIG_HANDLE_NULLPOINTER_STR_TO_INT	
#endif



static inline int	Convert_HexString_To_UInt_GetDigit(char c)
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
t_u##BITS				Convert_HexString_To_U##BITS(char const *str)			\
{																				\
	t_u##BITS	result;															\
	t_size	i;																	\
LIBCCCCONFIG_HANDLE_NULLPOINTER_STR_TO_INT										\
	i = 0;																		\
	while (!(str[i] == '+' ||													\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		if (!str[i] || !Char_IsSpace(str[i]))									\
			return (0);															\
		++i;																	\
	}																			\
	if (str[i] == '+')															\
		++i;																	\
	else if (str[i] == '0' && str[i + 1] == 'x')								\
		i += 2;																	\
	result = 0;																	\
	while (str[i] && (															\
		('0' <= str[i] && str[i] <= '9') ||										\
		('A' <= str[i] && str[i] <= 'F') ||										\
		('a' <= str[i] && str[i] <= 'f')))										\
	{																			\
		result = result * 16 + Convert_HexString_To_UInt_GetDigit(str[i]);		\
		++i;																	\
	}																			\
	return (result);															\
}																				\

DEFINEFUNC_CONVERT_STRHEX_TO_UINT(8)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(16)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(32)
DEFINEFUNC_CONVERT_STRHEX_TO_UINT(64)
