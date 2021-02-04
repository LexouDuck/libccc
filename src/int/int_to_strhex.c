
#include "libccc/int.h"
#include "libccc/memory.h"



#define DEFINEFUNC_CONVERT_UINT_TO_STRHEX(BITS) \
char*	U##BITS##_ToString_Hex(t_u##BITS number)				\
{																		\
	char*	result;														\
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
	if (!(result = (char*)Memory_Alloc(i + 1)))							\
		return (NULL);													\
	n = 0;																\
	while (i--)															\
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);	\
	result[n] = '\0';													\
	return (result);													\
}																		\

DEFINEFUNC_CONVERT_UINT_TO_STRHEX(8)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(16)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(32)
DEFINEFUNC_CONVERT_UINT_TO_STRHEX(64)
