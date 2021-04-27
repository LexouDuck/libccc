
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"



#define DEFINEFUNC_CONVERT_STROCT_TO_UINT(BITS) \
t_u##BITS	U##BITS##_FromString_Oct(char const* str)					\
{																		\
	t_u##BITS	result;													\
	t_size	i;															\
																		\
	LIBCONFIG_HANDLE_NULLPOINTER(0, str)								\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)					\
		continue;														\
	if (!(str[i] == '+' || Char_IsDigit_Oct(str[i])))					\
		return (0);														\
	if (str[i] == '+')													\
		++i;															\
	if (str[i] == '0' && str[i + 1] == 'o')								\
		i += 2;															\
	result = 0;															\
	while (str[i] && Char_IsDigit_Oct(str[i]))							\
	{																	\
		result = result * 8 + (str[i] - '0');							\
		++i;															\
	}																	\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_STROCT_TO_UINT(8)
DEFINEFUNC_CONVERT_STROCT_TO_UINT(16)
DEFINEFUNC_CONVERT_STROCT_TO_UINT(32)
DEFINEFUNC_CONVERT_STROCT_TO_UINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STROCT_TO_UINT(128)
#endif



#define DEFINEFUNC_CONVERT_STROCT_TO_SINT(BITS) \
t_s##BITS	S##BITS##_FromString_Oct(char const* str)					\
{																		\
	t_u##BITS	result;													\
	t_bool	negative;													\
	t_size	i;															\
																		\
	LIBCONFIG_HANDLE_NULLPOINTER(0, str)								\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)					\
		continue;														\
	if (!(str[i] == '+' || str[i] == '-' || Char_IsDigit_Oct(str[i])))	\
		return (0);														\
	negative = FALSE;													\
	if (str[i] == '-')													\
	{																	\
		negative = TRUE;												\
		++i;															\
	}																	\
	else if (str[i] == '+')												\
		++i;															\
	if (str[i] == '0' && str[i + 1] == 'o')								\
		i += 2;															\
	result = 0;															\
	while (str[i] && Char_IsDigit_Oct(str[i]))							\
	{																	\
		result = result * 8 + (str[i++] - '0');							\
	}																	\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);			\
}																		\

DEFINEFUNC_CONVERT_STROCT_TO_SINT(8)
DEFINEFUNC_CONVERT_STROCT_TO_SINT(16)
DEFINEFUNC_CONVERT_STROCT_TO_SINT(32)
DEFINEFUNC_CONVERT_STROCT_TO_SINT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STROCT_TO_SINT(128)
#endif
