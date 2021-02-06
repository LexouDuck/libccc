
#include "libccc/fixed.h"
#include "libccc/memory.h"



#define DEFINEFUNC_CONVERT_FIXED_TO_STR(BITS) \
char*	Q##BITS##_ToString(t_q##BITS number, t_u8 precision)\
{															\
	char*	result;											\
	t_u8	digits[MAXDIGITS_##BITS##BIT];					\
	t_u8	i;												\
	t_u##BITS	n;											\
															\
	if (number < 0)											\
		n = -Fixed_IntegerPart(number);						\
	else n = Fixed_IntegerPart(number);						\
	i = 0;													\
	while (n > 0)											\
	{														\
		digits[i++] = n % 10;								\
		n /= 10;											\
	}														\
	if (!(result = (char*)Memory_Alloc(i + precision + 3)))	\
		return (NULL);										\
	result[0] = (number == 0) ? '0' : '-';					\
	n = (number <= 0) ? 1 : 0;								\
	while (i--)												\
	{														\
		result[n++] = '0' + digits[i];						\
	}														\
	i = n;													\
	result[i++] = '.';										\
	n = Fixed_FractionPart(number);							\
	while (precision--)										\
	{														\
		result[i++] = (n % 10) + '0';						\
		n /= 10;											\
	}														\
	result[i] = '\0';										\
	return (result);										\
}															\

DEFINEFUNC_CONVERT_FIXED_TO_STR(16)
DEFINEFUNC_CONVERT_FIXED_TO_STR(32)
DEFINEFUNC_CONVERT_FIXED_TO_STR(64)
#ifdef __int128
DEFINEFUNC_CONVERT_FIXED_TO_STR(128)
#endif
