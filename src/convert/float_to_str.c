
#include "libccc_memory.h"
#include "libccc_string.h"
#include "libccc_math.h"
#include "libccc_convert.h"



// TODO actually implement this

#define DEFINEFUNC_CONVERT_FLOAT_TO_STR(BITS,PRINTF) \
inline char*	Convert_F##BITS##_To_String(t_f##BITS number)	\
{																\
	return (String_Build(PRINTF, number));						\
}																\

DEFINEFUNC_CONVERT_FLOAT_TO_STR( 32, "%g")
DEFINEFUNC_CONVERT_FLOAT_TO_STR( 64, "%lg")
#ifdef	__float80
DEFINEFUNC_CONVERT_FLOAT_TO_STR( 80, "%llg")
#endif
#ifdef	__float128
DEFINEFUNC_CONVERT_FLOAT_TO_STR(128, "%llg")
#endif



// TODO actually implement this

#define DEFINEFUNC_CONVERT_FLOAT_TO_STRHEX(BITS,PRINTF) \
inline char*	Convert_F##BITS##_To_HexString(t_f##BITS number)\
{																\
	return (String_Build(PRINTF, number));						\
}																\

DEFINEFUNC_CONVERT_FLOAT_TO_STRHEX( 32, "%#a")
DEFINEFUNC_CONVERT_FLOAT_TO_STRHEX( 64, "%#la")
#ifdef	__float80
DEFINEFUNC_CONVERT_FLOAT_TO_STRHEX( 80, "%#lla")
#endif
#ifdef	__float128
DEFINEFUNC_CONVERT_FLOAT_TO_STRHEX(128, "%#lla")
#endif



t_bool		Convert_Float_To_String_CheckSpecial(t_f32 number, char **result)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (result == NULL)
		return (FALSE);
#endif
	if (IS_NAN(number))
	{
		*result = String_Duplicate("NaN");
		return (TRUE);
	}
	else if (IS_INFINITY(number))
	{
		*result = (number < 0 ?
			String_Duplicate("-INFINITY") :
			String_Duplicate("+INFINITY"));
		return (TRUE);
	}
	return (FALSE);
}



#define DEFINEFUNC_CONVERT_FLOAT_TO_STR_P(BITS, POWER) \
																												\
static char*	Convert_F##BITS##_To_String_Decim(t_f##BITS number, t_u8 precision)								\
{																												\
	char*	result;																								\
	char	digits[BITS];																						\
	t_u8	i;																									\
	t_u64	n;																									\
																												\
	i = precision + 1;																							\
	while (--i)																									\
		number *= 10;																							\
	n = (t_u64)(number < 0 ? -number : number);																	\
	while (n > 0 || i < precision)																				\
	{																											\
		digits[i++] = (n % 10) + '0';																			\
		n /= 10;																								\
		if (i == precision && (digits[i++] = '.'))																\
			if (n == 0 && number != 0)																			\
				digits[i++] = '0';																				\
	}																											\
	if (!(result = (char*)Memory_Alloc(i + 2)))																	\
		return (NULL);																							\
	result[0] = (number == 0) ? '0' : '-';																		\
	n = (number <= 0) ? 1 : 0;																					\
	while (i--)																									\
		result[n++] = digits[i];																				\
	result[n] = '\0';																							\
	return (result);																							\
}																												\
																												\
static t_s16	Convert_F##BITS##_To_String_GetExponent(t_f##BITS* number)										\
{																												\
	t_f##BITS	nearest;																						\
	t_s16	power;																								\
	t_s16	exponent;																							\
																												\
	exponent = 0;																								\
	power = POWER;																								\
	if (*number >= FLOAT_THRESHOLD_HUGE ||																		\
		*number <= -FLOAT_THRESHOLD_HUGE)																		\
		while ((power /= 2) > 0)																				\
			if (*number >= (nearest = Math_Pow(10, power)))														\
			{																									\
				*number /= nearest;																				\
				exponent += power;																				\
			}																									\
	if ((*number > 0 && *number <= FLOAT_THRESHOLD_TINY) ||														\
		(*number < 0 && *number >= -FLOAT_THRESHOLD_TINY))														\
		while ((power /= 2) > 0)																				\
			if (*number < Math_Pow(10, 1 - power))																\
			{																									\
				*number *= Math_Pow(10, power);																	\
				exponent -= power;																				\
			}																									\
	return (exponent);																							\
}																												\
																												\
static char*	Convert_F##BITS##_To_String_Expon(t_f##BITS number, t_u8 precision,								\
	char** result_exp,																							\
	char** result_mant)																							\
{																												\
	char*	result;																								\
	t_size	i;																									\
	t_bool	sign;																								\
																												\
	sign = (number < 0);																						\
	number = (sign ? -number : number);																			\
	if (!(*result_exp = Convert_S16_To_String(Convert_F##BITS##_To_String_GetExponent(&number))) ||				\
		!(*result_mant = Convert_F##BITS##_To_String_Decim(number, precision)) ||								\
		!(result = (char*)Memory_Alloc(String_Length(*result_mant) + String_Length(*result_exp) + 2 + (t_u8)sign)))	\
	{																											\
		return (NULL);																							\
	}																											\
	i = 0;																										\
	if (sign)																									\
		result[i++] = '-';																						\
	String_Copy(result + i, *result_mant);																		\
	i += String_Length(*result_mant);																			\
	result[i++] = 'e';																							\
	String_Copy(result + i, *result_exp);																		\
	i += String_Length(*result_exp);																			\
	result[i] = '\0';																							\
	return (result);																							\
}																												\
																												\
char*		Convert_F##BITS##_To_String_P(t_f##BITS number, t_u8 precision)										\
{																												\
	char*	result;																								\
	char*	result_exp;																							\
	char*	result_mant;																						\
																												\
	result = NULL;																								\
	result_exp = NULL;																							\
	result_mant = NULL;																							\
	if (Convert_Float_To_String_CheckSpecial(number, &result))													\
		return (result);																						\
	if (number >= FLOAT_THRESHOLD_HUGE || number <= -FLOAT_THRESHOLD_HUGE ||									\
		(number > 0 && number <= FLOAT_THRESHOLD_TINY) ||														\
		(number < 0 && number >= -FLOAT_THRESHOLD_TINY))														\
		result = Convert_F##BITS##_To_String_Expon(number, precision,											\
			&result_exp, &result_mant);																			\
	else																										\
		result = Convert_F##BITS##_To_String_Decim(number, precision);											\
	if (result_exp)																								\
		Memory_Free(result_exp);																				\
	if (result_mant)																							\
		Memory_Free(result_mant);																				\
	return (result);																							\
}																												\

DEFINEFUNC_CONVERT_FLOAT_TO_STR_P(32, 512)
DEFINEFUNC_CONVERT_FLOAT_TO_STR_P(64, 4096)
