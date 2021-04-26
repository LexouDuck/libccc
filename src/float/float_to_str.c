
#include "libccc/bool.h"
#include "libccc/float.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/math/math.h"



//! Returns the appropriate string if the given 'number' is either NaN or +/- infinity, otherwise returns NULL
char*	Float_ToString_CheckSpecial(t_f32 number)
{
	if (IS_NAN(number))
	{
		return (String_Duplicate("NAN"));
	}
	else if (IS_INFINITY(number))
	{
		return (number < 0 ?
			String_Duplicate("-INFINITY") :
			String_Duplicate("+INFINITY"));
	}
	return (NULL);
}



#if LIBCONFIG_USE_FAST_APPROX_MATH

#define DEFINEFUNC_FLOAT_TO_STR(BITS) \
char*		F##BITS##_ToString(t_f##BITS number, t_u8 precision)	\
{																	\
	if ((number >=  FLOAT_THRESHOLD_HUGE) ||						\
		(number <= -FLOAT_THRESHOLD_HUGE) ||						\
		(number > 0 && number <=  FLOAT_THRESHOLD_TINY) ||			\
		(number < 0 && number >= -FLOAT_THRESHOLD_TINY))			\
		return (F##BITS##_ToString_Exp(number, precision));			\
	else															\
		return (F##BITS##_ToString_Dec(number, precision));			\
	return (NULL);													\
}																	\



#define DEFINEFUNC_FLOAT_TO_STREXP(BITS, POWER) \
static t_s16	F##BITS##_ToString_GetExp(t_f##BITS* number)				\
{																			\
	t_f##BITS	nearest;													\
	t_s16	power;															\
	t_s16	exponent;														\
	exponent = 0;															\
	power = POWER;															\
	if (*number >= FLOAT_THRESHOLD_HUGE ||									\
		*number <= -FLOAT_THRESHOLD_HUGE)									\
		while ((power /= 2) > 0)											\
			if (*number >= (nearest = Float_Pow(10, power)))				\
			{																\
				*number /= nearest;											\
				exponent += power;											\
			}																\
	if ((*number > 0 && *number <= FLOAT_THRESHOLD_TINY) ||					\
		(*number < 0 && *number >= -FLOAT_THRESHOLD_TINY))					\
		while ((power /= 2) > 0)											\
			if (*number < Float_Pow(10, 1 - power))							\
			{																\
				*number *= Float_Pow(10, power);							\
				exponent -= power;											\
			}																\
	return (exponent);														\
}																			\
																			\
char*	F##BITS##_ToString_Exp(t_f##BITS number, t_u8 precision)			\
{																			\
	char*	result = NULL;													\
	char*	result_exp = NULL;												\
	char*	result_mant = NULL;												\
	t_size	i;																\
	t_bool	sign;															\
	result = Float_ToString_CheckSpecial(number);							\
	if (result)																\
		return (result);													\
	sign = (number < 0);													\
	number = (sign ? -number : number);										\
	if (!(*result_exp = S16_ToString(F##BITS##_ToString_GetExp(&number))) ||\
		!(*result_mant = F##BITS##_ToString_Dec(number, precision)) ||		\
		!(result = (char*)Memory_Alloc(										\
			String_Length(*result_mant) +									\
			String_Length(*result_exp) + 2 + (t_u8)sign)))					\
	{																		\
		return (NULL);														\
	}																		\
	i = 0;																	\
	if (sign)																\
		result[i++] = '-';													\
	String_Copy(result + i, *result_mant);									\
	i += String_Length(*result_mant);										\
	result[i++] = 'e';														\
	String_Copy(result + i, *result_exp);									\
	i += String_Length(*result_exp);										\
	result[i] = '\0';														\
	if (result_exp)		Memory_Free(result_exp);							\
	if (result_mant)	Memory_Free(result_mant);							\
	return (result);														\
}																			\



#define DEFINEFUNC_FLOAT_TO_STRDEC(BITS) \
static char*	F##BITS##_ToString_Dec(t_f##BITS number, t_u8 precision)	\
{																			\
	char*	result = NULL;													\
	char	digits[BITS];													\
	t_u8	i;																\
	t_u64	n;																\
	result = Float_ToString_CheckSpecial(number);							\
	if (result)																\
		return (result);													\
	i = precision + 1;														\
	while (--i)																\
		number *= 10;														\
	n = (t_u64)(number < 0 ? -number : number);								\
	while (n > 0 || i < precision)											\
	{																		\
		digits[i++] = (n % 10) + '0';										\
		n /= 10;															\
		if (i == precision && (digits[i++] = '.'))							\
			if (n == 0 && number != 0)										\
				digits[i++] = '0';											\
	}																		\
	if (!(result = (char*)Memory_Alloc(i + 2)))								\
		return (NULL);														\
	result[0] = (number == 0) ? '0' : '-';									\
	n = (number <= 0) ? 1 : 0;												\
	while (i--)																\
		result[n++] = digits[i];											\
	result[n] = '\0';														\
	return (result);														\
}																			\



// TODO Float_ToString_Hex()
#define DEFINEFUNC_FLOAT_TO_STRHEX(BITS) \
static char*	F##BITS##_ToString_Hex(t_f##BITS number, t_u8 precision)	\
{ return (IS_NAN(number) ? NAN : precision); }



// TODO Float_ToString_Bin()
#define DEFINEFUNC_FLOAT_TO_STRBIN(BITS) \
static char*	F##BITS##_ToString_Bin(t_f##BITS number, t_u8 precision)	\
{ return (IS_NAN(number) ? NAN : precision); }



DEFINEFUNC_FLOAT_TO_STR(   32)
DEFINEFUNC_FLOAT_TO_STREXP(32, 512) // 2**9
DEFINEFUNC_FLOAT_TO_STRDEC(32)
DEFINEFUNC_FLOAT_TO_STRHEX(32)
DEFINEFUNC_FLOAT_TO_STRBIN(32)

DEFINEFUNC_FLOAT_TO_STR(   64)
DEFINEFUNC_FLOAT_TO_STREXP(64, 4096) // 2**12
DEFINEFUNC_FLOAT_TO_STRDEC(64)
DEFINEFUNC_FLOAT_TO_STRHEX(64)
DEFINEFUNC_FLOAT_TO_STRBIN(64)

#ifdef	__float80
DEFINEFUNC_FLOAT_TO_STR(   80)
DEFINEFUNC_FLOAT_TO_STREXP(80, 4096) // 2**?
DEFINEFUNC_FLOAT_TO_STRDEC(80)
DEFINEFUNC_FLOAT_TO_STRHEX(80)
DEFINEFUNC_FLOAT_TO_STRBIN(80)
#endif

#ifdef	__float128
DEFINEFUNC_FLOAT_TO_STR(   128)
DEFINEFUNC_FLOAT_TO_STREXP(128, 4096) // 2**?
DEFINEFUNC_FLOAT_TO_STRDEC(128)
DEFINEFUNC_FLOAT_TO_STRHEX(128)
DEFINEFUNC_FLOAT_TO_STRBIN(128)
#endif



#else

	#define DEFINEFUNC_FLOAT_TO_STR_ANY_(BITS, FORMAT) \
	inline char*	F##BITS##_ToString(t_f##BITS number, t_u8 precision)			\
	{																				\
		char*	result = Float_ToString_CheckSpecial(number);						\
		if (result)																	\
			return (result);														\
		if ((number >=  FLOAT_THRESHOLD_HUGE) ||									\
			(number <= -FLOAT_THRESHOLD_HUGE) ||									\
			(number > 0 && number <=  FLOAT_THRESHOLD_TINY) ||						\
			(number < 0 && number >= -FLOAT_THRESHOLD_TINY))						\
			return (String_Format(FORMAT"e", precision, number));					\
		else																		\
			return (String_Format(FORMAT"f", precision, number));					\
		return (NULL);																\
	}																				\

	#define DEFINEFUNC_FLOAT_TO_STR(SUFFIX, BITS, FORMAT) \
	inline char*	F##BITS##_ToString##SUFFIX(t_f##BITS number, t_u8 precision)	\
	{																				\
		char*	result = Float_ToString_CheckSpecial(number);						\
		if (result)																	\
			return (result);														\
		return (String_Format(FORMAT, precision, number));							\
	}																				\



	DEFINEFUNC_FLOAT_TO_STR_ANY_(32,  "%.*")
	DEFINEFUNC_FLOAT_TO_STR(_Exp,32, "%#.*e")
	DEFINEFUNC_FLOAT_TO_STR(_Dec,32, "%#.*f")
	DEFINEFUNC_FLOAT_TO_STR(_Hex,32, "%#.*a")
	DEFINEFUNC_FLOAT_TO_STR(_Bin,32, "%#.*a") // TODO

	DEFINEFUNC_FLOAT_TO_STR_ANY_(64,  "%.*l")
	DEFINEFUNC_FLOAT_TO_STR(_Exp,64, "%#.*le")
	DEFINEFUNC_FLOAT_TO_STR(_Dec,64, "%#.*lf")
	DEFINEFUNC_FLOAT_TO_STR(_Hex,64, "%#.*la")
	DEFINEFUNC_FLOAT_TO_STR(_Bin,64, "%#.*a") // TODO

	#ifdef	__float80
	DEFINEFUNC_FLOAT_TO_STR_ANY_(80,  "%.*ll")
	DEFINEFUNC_FLOAT_TO_STR(_Exp,80, "%#.*lle")
	DEFINEFUNC_FLOAT_TO_STR(_Dec,80, "%#.*llf")
	DEFINEFUNC_FLOAT_TO_STR(_Hex,80, "%#.*lla")
	DEFINEFUNC_FLOAT_TO_STR(_Bin,80, "%#.*a") // TODO
	#endif

	#ifdef	__float128
	DEFINEFUNC_FLOAT_TO_STR_ANY_(128,  "%.*ll")
	DEFINEFUNC_FLOAT_TO_STR(_Exp,128, "%#.*lle")
	DEFINEFUNC_FLOAT_TO_STR(_Dec,128, "%#.*llf")
	DEFINEFUNC_FLOAT_TO_STR(_Hex,128, "%#.*lla")
	DEFINEFUNC_FLOAT_TO_STR(_Bin,128, "%#.*a") // TODO
	#endif



#endif
