
#include "libccc/int.h"
#include "libccc/memory.h"



#define DEFINEFUNC_CONVERT_UINT_TO_STR(BITS) \
char*	Convert_U##BITS##_To_String(t_u##BITS number)	\
{														\
	char*	result;										\
	t_u8	digits[MAXDIGIT_##BITS##BIT];				\
	t_u8	i;											\
	t_u##BITS	n;										\
														\
	n = number;											\
	i = 0;												\
	while (n > 0)										\
	{													\
		digits[i++] = n % 10;							\
		n /= 10;										\
	}													\
	if (i == 0)											\
		digits[i++] = 0;								\
	if (!(result = (char*)Memory_Alloc(i + 1)))			\
		return (NULL);									\
	n = 0;												\
	while (i--)											\
		result[n++] = '0' + digits[i];					\
	result[n] = '\0';									\
	return (result);									\
}														\

DEFINEFUNC_CONVERT_UINT_TO_STR(8)
DEFINEFUNC_CONVERT_UINT_TO_STR(16)
DEFINEFUNC_CONVERT_UINT_TO_STR(32)
DEFINEFUNC_CONVERT_UINT_TO_STR(64)



#define DEFINEFUNC_CONVERT_SINT_TO_STR(BITS) \
char*	Convert_S##BITS##_To_String(t_s##BITS number)	\
{														\
	char*	result;										\
	t_u8	digits[MAXDIGIT_##BITS##BIT];				\
	t_u8	i;											\
	t_u##BITS	n;										\
														\
	if (number < 0)										\
		n = -number;									\
	else n = number;									\
	i = 0;												\
	while (n > 0)										\
	{													\
		digits[i++] = n % 10;							\
		n /= 10;										\
	}													\
	if (!(result = (char*)Memory_Alloc(i + 2)))			\
		return (NULL);									\
	result[0] = (number == 0) ? '0' : '-';				\
	n = (number <= 0) ? 1 : 0;							\
	while (i--)											\
		result[n++] = '0' + digits[i];					\
	result[n] = '\0';									\
	return (result);									\
}														\

DEFINEFUNC_CONVERT_SINT_TO_STR(8)
DEFINEFUNC_CONVERT_SINT_TO_STR(16)
DEFINEFUNC_CONVERT_SINT_TO_STR(32)
DEFINEFUNC_CONVERT_SINT_TO_STR(64)
