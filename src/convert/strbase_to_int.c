
#include "libft_char.h"
#include "libft_convert.h"



#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	#define LIBFTCONFIG_HANDLE_NULLPOINTER_STRBASE_TO_INT \
		if (str == NULL) return (0);	\
		if (base == NULL) return (0);	\

#else
	#define LIBFTCONFIG_HANDLE_NULLPOINTER_STRBASE_TO_INT	
#endif



static t_size	Convert_BaseString_GetLength(char const* base, t_bool sign)
{
	t_size	i;
	t_size	j;

	i = 0;
	while (base[i])
	{
		if (sign && (base[i] == '+' || base[i] == '-'))
			return (0);
		j = i - 1;
		while (j != (t_size)-1)
		{
			if (base[i] == base[j])
				return (0);
			--j;
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}

static t_s32	Convert_BaseString_IsInBase(char const* base, t_size base_length, char c)
{
	t_size	i;

	i = 0;
	while (i < base_length)
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}



#define DEFINEFUNC_CONVERT_STRBASE_TO_SINT(BITS) \
t_s##BITS	Convert_BaseString_To_S##BITS(char const* str, char const* base)	\
{																				\
	t_u##BITS	result;															\
	t_bool	negative;															\
	t_s32	digit;																\
	t_size	length;																\
	t_size	i;																	\
LIBFTCONFIG_HANDLE_NULLPOINTER_STRBASE_TO_INT									\
	length = Convert_BaseString_GetLength(base, FALSE);							\
	if (length == 0)															\
		return (0);																\
	i = 0;																		\
	while (!(str[i] == '+' || str[i] == '-'))									\
	{																			\
		digit = Convert_BaseString_IsInBase(base, length, str[i]);				\
		if (digit >= 0) break;													\
		if (!str[i] || !Char_IsSpace(str[i]))									\
			return (0);															\
		++i;																	\
	}																			\
	negative = FALSE;															\
	if (str[i] == '-')															\
	{																			\
		negative = TRUE;														\
		++i;																	\
	}																			\
	else if (str[i] == '+')														\
		++i;																	\
	result = 0;																	\
	while (str[i])																\
	{																			\
		digit = Convert_BaseString_IsInBase(base, length, str[i]);				\
		if (digit < 0) break;													\
		result = result * length + digit;										\
		++i;																	\
	}																			\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);					\
}																				\

DEFINEFUNC_CONVERT_STRBASE_TO_SINT(8)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(16)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(32)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(64)



#define DEFINEFUNC_CONVERT_STRBASE_TO_UINT(BITS) \
t_u##BITS	Convert_BaseString_To_U##BITS(char const* str, char const* base)	\
{																				\
	t_u##BITS	result;															\
	t_s32	digit;																\
	t_size	length;																\
	t_size	i;																	\
LIBFTCONFIG_HANDLE_NULLPOINTER_STRBASE_TO_INT									\
	length = Convert_BaseString_GetLength(base, FALSE);							\
	if (length == 0)															\
		return (0);																\
	i = 0;																		\
	while (!(str[i] == '+' || str[i] == '-'))									\
	{																			\
		digit = Convert_BaseString_IsInBase(base, length, str[i]);				\
		if (digit >= 0) break;													\
		if (!str[i] || !Char_IsSpace(str[i]))									\
			return (0);															\
		++i;																	\
	}																			\
	if (str[i] == '+' || str[i] == '-')											\
		++i;																	\
	result = 0;																	\
	while (str[i])																\
	{																			\
		digit = Convert_BaseString_IsInBase(base, length, str[i]);				\
		if (digit < 0) break;													\
		result = result * length + digit;										\
		++i;																	\
	}																			\
	return (result);															\
}																				\

DEFINEFUNC_CONVERT_STRBASE_TO_UINT(8)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(16)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(32)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(64)
