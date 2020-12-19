
#include "libft_char.h"
#include "libft_convert.h"



#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	#define LIBFTCONFIG_HANDLE_NULLPOINTER_STR_TO_INT	if (str == NULL) return (0);
#else
	#define LIBFTCONFIG_HANDLE_NULLPOINTER_STR_TO_INT	
#endif



#define DEFINEFUNC_CONVERT_STR_TO_SINT(BITS) \
t_s##BITS	Convert_String_To_S##BITS(char const* str)					\
{																		\
	t_u##BITS	result;													\
	t_bool	negative;													\
	t_size	i;															\
LIBFTCONFIG_HANDLE_NULLPOINTER_STR_TO_INT								\
	i = 0;																\
	while (!(Char_IsDigit(str[i]) || str[i] == '+' || str[i] == '-'))	\
	{																	\
		if (!str[i] || !Char_IsSpace(str[i]))							\
			return (0);													\
		++i;															\
	}																	\
	negative = FALSE;													\
	if (str[i] == '-')													\
	{																	\
		negative = TRUE;												\
		++i;															\
	}																	\
	else if (str[i] == '+')												\
		++i;															\
	result = 0;															\
	while (str[i] && Char_IsDigit(str[i]))								\
		result = result * 10 + str[i++] - '0';							\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);			\
}																		\

DEFINEFUNC_CONVERT_STR_TO_SINT(8)
DEFINEFUNC_CONVERT_STR_TO_SINT(16)
DEFINEFUNC_CONVERT_STR_TO_SINT(32)
DEFINEFUNC_CONVERT_STR_TO_SINT(64)



#define DEFINEFUNC_CONVERT_STR_TO_UINT(BITS) \
t_u##BITS	Convert_String_To_U##BITS(char const* str)					\
{																		\
	t_u##BITS	result;													\
	t_size	i;															\
LIBFTCONFIG_HANDLE_NULLPOINTER_STR_TO_INT								\
	i = 0;																\
	while (!(Char_IsDigit(str[i]) || str[i] == '+'))					\
	{																	\
		if (!str[i] || !Char_IsSpace(str[i]))							\
			return (0);													\
		++i;															\
	}																	\
	if (str[i] == '+')													\
		++i;															\
	result = 0;															\
	while (str[i] && Char_IsDigit(str[i]))								\
	{																	\
		result = result * 10 + str[i] - '0';							\
		++i;															\
	}																	\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_STR_TO_UINT(8)
DEFINEFUNC_CONVERT_STR_TO_UINT(16)
DEFINEFUNC_CONVERT_STR_TO_UINT(32)
DEFINEFUNC_CONVERT_STR_TO_UINT(64)

