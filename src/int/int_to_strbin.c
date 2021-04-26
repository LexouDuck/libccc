
#include "libccc/int.h"
#include "libccc/memory.h"



#define DEFINEFUNC_CONVERT_UINT_TO_STRBIN(BITS) \
char*	U##BITS##_ToString_Bin(t_u##BITS number, t_bool prefix)			\
{																		\
	char*	result;														\
	t_u8	digits[BITS];												\
	t_u8	i;															\
	t_u##BITS	n;														\
																		\
	n = number;															\
	i = 0;																\
	while (n > 0)														\
	{																	\
		digits[i++] = n % 2;											\
		n /= 2;															\
	}																	\
	if (i == 0)															\
		digits[i++] = 0;												\
	if (!(result = (char*)Memory_Alloc((prefix ? 2 : 0) + i + 1)))		\
		return (NULL);													\
	n = 0;																\
	if (prefix)															\
	{																	\
		result[n] = '0';												\
		result[n] = 'b';												\
	}																	\
	while (i--)															\
		result[n++] = digits[i] ? '1' : '0';							\
	result[n] = '\0';													\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_UINT_TO_STRBIN(8)
DEFINEFUNC_CONVERT_UINT_TO_STRBIN(16)
DEFINEFUNC_CONVERT_UINT_TO_STRBIN(32)
DEFINEFUNC_CONVERT_UINT_TO_STRBIN(64)
#ifdef __int128
DEFINEFUNC_CONVERT_UINT_TO_STRBIN(128)
#endif



#define DEFINEFUNC_CONVERT_SINT_TO_STRBIN(BITS) \
char*	S##BITS##_ToString_Bin(t_s##BITS number, t_bool prefix)			\
{																		\
	char*	result;														\
	t_u8	digits[BITS];												\
	t_u8	i;															\
	t_u##BITS	n;														\
																		\
	if (number < 0)														\
		n = -number;													\
	else n = number;													\
	i = 0;																\
	while (n > 0)														\
	{																	\
		digits[i++] = n % 2;											\
		n /= 2;															\
	}																	\
	if (!(result = (char*)Memory_Alloc((prefix ? 2 : 0) + i + 1)))		\
		return (NULL);													\
	n = 0;																\
	if (number < 0) 	result[n++] = '-';								\
	if (number == 0)	result[n++] = '0';								\
	if (prefix)															\
	{																	\
		result[n++] = '0';												\
		result[n++] = 'b';												\
	}																	\
	while (i--)															\
		result[n++] = digits[i] ? '1' : '0';							\
	result[n] = '\0';													\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_SINT_TO_STRBIN(8)
DEFINEFUNC_CONVERT_SINT_TO_STRBIN(16)
DEFINEFUNC_CONVERT_SINT_TO_STRBIN(32)
DEFINEFUNC_CONVERT_SINT_TO_STRBIN(64)
#ifdef __int128
DEFINEFUNC_CONVERT_SINT_TO_STRBIN(128)
#endif
