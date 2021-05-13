
#include "libccc/int.h"
#include "libccc/memory.h"



#define DEFINEFUNC_CONVERT_UINT_TO_STRHEX(BITS) \
t_char*	U##BITS##_ToString_Hex(t_u##BITS number, t_bool prefix)			\
{																		\
	t_char*	result;														\
	t_u8	digits[BITS / 4];											\
	t_u8	i;															\
	t_u##BITS	n;														\
																		\
	n = number;															\
	i = 0;																\
	while (n > 0)														\
	{																	\
		digits[i++] = n % 16;											\
		n /= 16;														\
	}																	\
	if (i == 0)															\
		digits[i++] = 0;												\
	if (!(result = (t_char*)Memory_Alloc((prefix ? 2 : 0) + i + 1)))		\
		return (NULL);													\
	n = 0;																\
	if (prefix)															\
	{																	\
		result[n++] = '0';												\
		result[n++] = 'x';												\
	}																	\
	while (i--)															\
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);	\
	result[n] = '\0';													\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_UINT_TO_STRHEX(8)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(16)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(32)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(64)
#ifdef __int128
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(128)
#endif



#define DEFINEFUNC_CONVERT_SINT_TO_STRHEX(BITS) \
t_char*	S##BITS##_ToString_Hex(t_s##BITS number, t_bool prefix)			\
{																		\
	t_char*	result;														\
	t_u8	digits[BITS / 4];											\
	t_u8	i;															\
	t_u##BITS	n;														\
																		\
	if (number < 0)														\
		n = -number;													\
	else n = number;													\
	i = 0;																\
	while (n > 0)														\
	{																	\
		digits[i++] = n % 16;											\
		n /= 16;														\
	}																	\
	if (!(result = (t_char*)Memory_Alloc((prefix ? 2 : 0) + i + 1)))		\
		return (NULL);													\
	n = 0;																\
	if (number < 0) 	result[n++] = '-';								\
	if (number == 0)	result[n++] = '0';								\
	if (prefix)															\
	{																	\
		result[n++] = '0';												\
		result[n++] = 'x';												\
	}																	\
	while (i--)															\
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);	\
	result[n] = '\0';													\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_SINT_TO_STRHEX(8)
DEFINEFUNC_CONVERT_SINT_TO_STRHEX(16)
DEFINEFUNC_CONVERT_SINT_TO_STRHEX(32)
DEFINEFUNC_CONVERT_SINT_TO_STRHEX(64)
#ifdef __int128
DEFINEFUNC_CONVERT_SINT_TO_STRHEX(128)
#endif
