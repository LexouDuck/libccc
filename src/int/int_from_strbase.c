
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"

#include LIBCONFIG_HANDLE_INCLUDE



static t_size	String_Base_GetLength(t_char const* base)
{
	t_size	i;
	t_size	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i;
		while (j--)
		{
			if (base[i] == base[j])
				return (0);
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}

static t_s32	String_Base_IsInBase(t_char const* base, t_size base_length, char c)
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
t_s##BITS	S##BITS##_FromString_Base(t_char const* str, t_char const* base)	\
{																				\
	t_u##BITS	result;															\
	t_bool	negative;															\
	t_s32	digit;																\
	t_size	length;																\
	t_size	i;																	\
																				\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)						\
	HANDLE_ERROR(NULLPOINTER, (base == NULL), return (0);)						\
	length = String_Base_GetLength(base);										\
	if (length == 0)															\
		return (0);																\
	i = 0;																		\
	while (!(str[i] == '+' || str[i] == '-'))									\
	{																			\
		digit = String_Base_IsInBase(base, length, str[i]);						\
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
		digit = String_Base_IsInBase(base, length, str[i]);						\
		if (digit < 0) return (0);												\
		result = result * length + digit;										\
		++i;																	\
	}																			\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);					\
}																				\

DEFINEFUNC_CONVERT_STRBASE_TO_SINT(8)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(16)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(32)
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRBASE_TO_SINT(128)
#endif



#define DEFINEFUNC_CONVERT_STRBASE_TO_UINT(BITS) \
t_u##BITS	U##BITS##_FromString_Base(t_char const* str, t_char const* base)	\
{																				\
	t_u##BITS	result;															\
	t_s32	digit;																\
	t_size	length;																\
	t_size	i;																	\
																				\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)						\
	HANDLE_ERROR(NULLPOINTER, (base == NULL), return (0);)						\
	length = String_Base_GetLength(base);										\
	if (length == 0)															\
		return (0);																\
	i = 0;																		\
	while (!(str[i] == '+' || str[i] == '-'))									\
	{																			\
		digit = String_Base_IsInBase(base, length, str[i]);						\
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
		digit = String_Base_IsInBase(base, length, str[i]);						\
		if (digit < 0) return (0);												\
		result = result * length + digit;										\
		++i;																	\
	}																			\
	return (result);															\
}																				\

DEFINEFUNC_CONVERT_STRBASE_TO_UINT(8)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(16)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(32)
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRBASE_TO_UINT(128)
#endif
