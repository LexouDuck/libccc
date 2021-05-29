
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"

#include LIBCONFIG_HANDLE_INCLUDE



#define DEFINEFUNC_CONVERT_STR_TO_UINT(BITS) \
t_u##BITS	U##BITS##_FromString(t_char const* str)							\
{																			\
	t_u##BITS	result;														\
	t_u##BITS	tmp;														\
	t_size	i;																\
																			\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)					\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)						\
		continue;															\
	HANDLE_ERROR(PARSE,														\
		!(str[i] == '+' || Char_IsDigit(str[i])),							\
		return (0);)														\
	if (str[i] == '+')														\
		++i;																\
	result = 0;																\
	while (str[i] && Char_IsDigit(str[i]))									\
	{																		\
		tmp = result * 10 + (str[i++] - '0');								\
		HANDLE_ERROR(RESULTRANGE, (tmp < result), LIBCONFIG_HANDLE_OVERFLOW)\
		result = tmp;														\
	}																		\
	return (result);														\
}																			\

DEFINEFUNC_CONVERT_STR_TO_UINT(8)
DEFINEFUNC_CONVERT_STR_TO_UINT(16)
DEFINEFUNC_CONVERT_STR_TO_UINT(32)
DEFINEFUNC_CONVERT_STR_TO_UINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STR_TO_UINT(128)
#endif



#define DEFINEFUNC_CONVERT_STR_TO_SINT(BITS) \
t_s##BITS	S##BITS##_FromString(t_char const* str)							\
{																			\
	t_u##BITS	result;														\
	t_u##BITS	tmp;														\
	t_bool	negative;														\
	t_size	i;																\
																			\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)					\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)						\
		continue;															\
	HANDLE_ERROR(PARSE,														\
		!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),			\
		return (0);)														\
	negative = FALSE;														\
	if (str[i] == '-')														\
	{																		\
		negative = TRUE;													\
		++i;																\
	}																		\
	else if (str[i] == '+')													\
		++i;																\
	result = 0;																\
	while (str[i] && Char_IsDigit(str[i]))									\
	{																		\
		tmp = result * 10 + (str[i++] - '0');								\
		HANDLE_ERROR(RESULTRANGE, (tmp < result), LIBCONFIG_HANDLE_OVERFLOW)\
		result = tmp;														\
	}																		\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);				\
}																			\

DEFINEFUNC_CONVERT_STR_TO_SINT(8)
DEFINEFUNC_CONVERT_STR_TO_SINT(16)
DEFINEFUNC_CONVERT_STR_TO_SINT(32)
DEFINEFUNC_CONVERT_STR_TO_SINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STR_TO_SINT(128)
#endif
