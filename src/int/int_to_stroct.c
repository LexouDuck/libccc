
#include "libccc/int.h"
#include "libccc/memory.h"



#define MAXDIGITS_8BIT	 ( 3)	//!< The amount of digits needed to represent an 8-bit integer in octal (max: 377)
#define MAXDIGITS_16BIT	 ( 6)	//!< The amount of digits needed to represent a 16-bit integer in octal (max: 177777)
#define MAXDIGITS_32BIT	 (11)	//!< The amount of digits needed to represent a 32-bit integer in octal (max: 37777777777)
#define MAXDIGITS_64BIT	 (22)	//!< The amount of digits needed to represent a 64-bit integer in octal (max: 1777777777777777777777)
#define MAXDIGITS_128BIT (43)	//!< The amount of digits needed to represent a 128-bit integer in octal (max: 3777777777777777777777777777777777777777777)



#define DEFINEFUNC_CONVERT_UINT_TO_STROCT(BITS) \
char*	U##BITS##_ToString_Oct(t_u##BITS number)	\
{													\
	char*	result;									\
	t_u8	digits[MAXDIGITS_##BITS##BIT];			\
	t_u8	i;										\
	t_u##BITS	n;									\
													\
	n = number;										\
	i = 0;											\
	while (n > 0)									\
	{												\
		digits[i++] = n % 8;						\
		n /= 8;										\
	}												\
	if (i == 0)										\
		digits[i++] = 0;							\
	if (!(result = (char*)Memory_Alloc(i + 1)))		\
		return (NULL);								\
	n = 0;											\
	while (i--)										\
		result[n++] = digits[i] + '0';				\
	result[n] = '\0';								\
	return (result);								\
}													\

DEFINEFUNC_CONVERT_UINT_TO_STROCT(8)
DEFINEFUNC_CONVERT_UINT_TO_STROCT(16)
DEFINEFUNC_CONVERT_UINT_TO_STROCT(32)
DEFINEFUNC_CONVERT_UINT_TO_STROCT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_UINT_TO_STROCT(128)
#endif



#define DEFINEFUNC_CONVERT_SINT_TO_STROCT(BITS) \
char*	S##BITS##_ToString_Oct(t_s##BITS number)	\
{													\
	char*	result;									\
	t_u8	digits[MAXDIGITS_##BITS##BIT];			\
	t_u8	i;										\
	t_u##BITS	n;									\
													\
	if (number < 0)									\
		n = -number;								\
	else n = number;								\
	i = 0;											\
	while (n > 0)									\
	{												\
		digits[i++] = n % 8;						\
		n /= 8;										\
	}												\
	if (!(result = (char*)Memory_Alloc(i + 1)))		\
		return (NULL);								\
	result[0] = (number == 0) ? '0' : '-';			\
	n = (number <= 0) ? 1 : 0;						\
	while (i--)										\
		result[n++] = digits[i] + '0';				\
	result[n] = '\0';								\
	return (result);								\
}													\

DEFINEFUNC_CONVERT_SINT_TO_STROCT(8)
DEFINEFUNC_CONVERT_SINT_TO_STROCT(16)
DEFINEFUNC_CONVERT_SINT_TO_STROCT(32)
DEFINEFUNC_CONVERT_SINT_TO_STROCT(64)
#ifdef __int128
DEFINEFUNC_CONVERT_SINT_TO_STROCT(128)
#endif
