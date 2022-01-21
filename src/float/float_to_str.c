
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Returns the appropriate string if the given 'number' is either NaN or +/- infinity, otherwise returns NULL
static
t_char*	Float_ToString_CheckSpecial(t_float number)
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



#if LIBCONFIG_USE_STD_MATH

	#define DEFINEFUNC_FLOAT_TOSTR_ANY_(BITS, FORMAT) \
	t_char*	F##BITS##_ToString(t_f##BITS number, t_u8 precision)			\
	{																		\
		t_char*	result = Float_ToString_CheckSpecial(number);				\
		if (result)															\
			return (result);												\
		if ((number >=  FLOAT_THRESHOLD_HUGE) ||							\
			(number <= -FLOAT_THRESHOLD_HUGE) ||							\
			(number > 0 && number <=  FLOAT_THRESHOLD_TINY) ||				\
			(number < 0 && number >= -FLOAT_THRESHOLD_TINY))				\
			return (String_Format(FORMAT"e", precision, number));			\
		else																\
			return (String_Format(FORMAT"f", precision, number));			\
		return (NULL);														\
	}																		\

	#define DEFINEFUNC_FLOAT_TOSTR(SUFFIX, BITS, FORMAT) \
	t_char*	F##BITS##_ToString##SUFFIX(t_f##BITS number, t_u8 precision)	\
	{																		\
		t_char*	result = Float_ToString_CheckSpecial(number);				\
		if (result)															\
			return (result);												\
		return (String_Format(FORMAT, precision, number));					\
	}																		\



	DEFINEFUNC_FLOAT_TOSTR_ANY_(32,  "%.*")
	DEFINEFUNC_FLOAT_TOSTR(_Exp,32, "%#.*e")
	DEFINEFUNC_FLOAT_TOSTR(_Dec,32, "%#.*f")
	DEFINEFUNC_FLOAT_TOSTR(_Hex,32, "%#.*a")
	DEFINEFUNC_FLOAT_TOSTR(_Bin,32, "%#.*a") // TODO

	DEFINEFUNC_FLOAT_TOSTR_ANY_(64,  "%.*l")
	DEFINEFUNC_FLOAT_TOSTR(_Exp,64, "%#.*le")
	DEFINEFUNC_FLOAT_TOSTR(_Dec,64, "%#.*lf")
	DEFINEFUNC_FLOAT_TOSTR(_Hex,64, "%#.*la")
	DEFINEFUNC_FLOAT_TOSTR(_Bin,64, "%#.*a") // TODO

	#if LIBCONFIG_USE_FLOAT80
	DEFINEFUNC_FLOAT_TOSTR_ANY_(80,  "%.*L")
	DEFINEFUNC_FLOAT_TOSTR(_Exp,80, "%#.*Le")
	DEFINEFUNC_FLOAT_TOSTR(_Dec,80, "%#.*Lf")
	DEFINEFUNC_FLOAT_TOSTR(_Hex,80, "%#.*La")
	DEFINEFUNC_FLOAT_TOSTR(_Bin,80, "%#.*La") // TODO
	#endif

	#if LIBCONFIG_USE_FLOAT128
	DEFINEFUNC_FLOAT_TOSTR_ANY_(128,  "%.*L")
	DEFINEFUNC_FLOAT_TOSTR(_Exp,128, "%#.*Le")
	DEFINEFUNC_FLOAT_TOSTR(_Dec,128, "%#.*Lf")
	DEFINEFUNC_FLOAT_TOSTR(_Hex,128, "%#.*La")
	DEFINEFUNC_FLOAT_TOSTR(_Bin,128, "%#.*La") // TODO
	#endif



#else



#define DEFINEFUNC_FLOAT_TOSTR(BITS) \
t_char*		F##BITS##_ToString(t_f##BITS number, t_u8 precision)	\
{																	\
	if ((number >=  FLOAT_THRESHOLD_HUGE) ||						\
		(number <= -FLOAT_THRESHOLD_HUGE) ||						\
		(number > 0 && number <=  FLOAT_THRESHOLD_TINY) ||			\
		(number < 0 && number >= -FLOAT_THRESHOLD_TINY))			\
		return (F##BITS##_ToString_Exp(number, precision));			\
	else															\
		return (F##BITS##_ToString_Dec(number, precision));			\
	return (NULL);													\
}



#define DEFINEFUNC_FLOAT_TOSTREXP(BITS) \
t_char*	F##BITS##_ToString_Exp(t_f##BITS number, t_u8 precision)			\
{																			\
	t_char*	result = NULL;													\
	t_char*	result_exponent = NULL;											\
	t_char*	result_mantissa = NULL;											\
	t_size	i;																\
	t_bool	sign;															\
	result = Float_ToString_CheckSpecial(number);							\
	if (result)																\
		return (result);													\
	sign = (number < 0);													\
	number = (sign ? -number : number);										\
	result_exponent = S16_ToString(F##BITS##_GetExp10(number));				\
	HANDLE_ERROR(ALLOCFAILURE, (result_exponent == NULL), goto failure;)	\
	result_mantissa = F##BITS##_ToString_Dec(number, precision);			\
	HANDLE_ERROR(ALLOCFAILURE, (result_mantissa == NULL), goto failure;)	\
	result = (t_char*)Memory_Allocate(2 + (t_u8)sign						\
			+ String_Length(result_mantissa)								\
			+ String_Length(result_exponent));								\
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), goto failure;)				\
	i = 0;																	\
	if (sign)																\
		result[i++] = '-';													\
	String_Copy(result + i, result_mantissa);								\
	i += String_Length(result_mantissa);									\
	result[i++] = 'e';														\
	String_Copy(result + i, result_exponent);								\
	i += String_Length(result_exponent);									\
	result[i] = '\0';														\
failure:																	\
	if (result_exponent)	Memory_Free(result_exponent);					\
	if (result_mantissa)	Memory_Free(result_mantissa);					\
	return (result);														\
}



#define DEFINEFUNC_FLOAT_TOSTRDEC(BITS) \
t_char*	F##BITS##_ToString_Dec(t_f##BITS number, t_u8 precision)	\
{																	\
	t_char*	result = NULL;											\
	char	digits[BITS];											\
	t_u8	i;														\
	t_u64	n;														\
	result = Float_ToString_CheckSpecial(number);					\
	if (result)														\
		return (result);											\
	i = precision + 1;												\
	while (--i)														\
		number *= 10;												\
	n = (t_u64)(number < 0 ? -number : number);						\
	while (n > 0 || i < precision)									\
	{																\
		digits[i++] = (n % 10) + '0';								\
		n /= 10;													\
		if (i == precision && (digits[i++] = '.'))					\
			if (n == 0 && number != 0)								\
				digits[i++] = '0';									\
	}																\
	result = (t_char*)Memory_Allocate(i + 2);						\
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)	\
	result[0] = (number == 0) ? '0' : '-';							\
	n = (number <= 0) ? 1 : 0;										\
	while (i--)														\
		result[n++] = digits[i];									\
	result[n] = '\0';												\
	return (result);												\
}



// TODO Float_ToString_Hex()
#define DEFINEFUNC_FLOAT_TOSTRHEX(BITS) \
t_char*	F##BITS##_ToString_Hex(t_f##BITS number, t_u8 precision)	\
{ return (IS_NAN(number) ? "NaN" : (precision == 0 ? "" : NULL)); }



// TODO Float_ToString_Bin()
#define DEFINEFUNC_FLOAT_TOSTRBIN(BITS) \
t_char*	F##BITS##_ToString_Bin(t_f##BITS number, t_u8 precision)	\
{ return (IS_NAN(number) ? "NaN" : (precision == 0 ? "" : NULL)); }



DEFINEFUNC_FLOAT_TOSTR(   32)
DEFINEFUNC_FLOAT_TOSTREXP(32)
DEFINEFUNC_FLOAT_TOSTRDEC(32)
DEFINEFUNC_FLOAT_TOSTRHEX(32)
DEFINEFUNC_FLOAT_TOSTRBIN(32)

DEFINEFUNC_FLOAT_TOSTR(   64)
DEFINEFUNC_FLOAT_TOSTREXP(64)
DEFINEFUNC_FLOAT_TOSTRDEC(64)
DEFINEFUNC_FLOAT_TOSTRHEX(64)
DEFINEFUNC_FLOAT_TOSTRBIN(64)

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TOSTR(   80)
DEFINEFUNC_FLOAT_TOSTREXP(80)
DEFINEFUNC_FLOAT_TOSTRDEC(80)
DEFINEFUNC_FLOAT_TOSTRHEX(80)
DEFINEFUNC_FLOAT_TOSTRBIN(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TOSTR(   128)
DEFINEFUNC_FLOAT_TOSTREXP(128)
DEFINEFUNC_FLOAT_TOSTRDEC(128)
DEFINEFUNC_FLOAT_TOSTRHEX(128)
DEFINEFUNC_FLOAT_TOSTRBIN(128)
#endif



#endif
