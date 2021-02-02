
/*
**	Functions used from <stdlib.h>: (only when LIBCONFIG_USE_FAST_APPROX_MATH is 0)
**	-	double	atof(char* str);
*/
#include <stdlib.h>

#include "libccc/float.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/math/math.h"



static char*	Convert_String_To_Float_ToUppercase(char const* str)
{
	char*	result;
	t_s32	end;
	t_s32	i;

	i = 0;
	while (Char_IsSpace(str[i]))
		++i;
	end = String_Length(str) - 1;
	while (end >= 0 && !Char_IsAlphaNumeric(str[end]))
		--end;
	if (end == -1 || 1 + end <= i)
		return (NULL);
	result = String_Sub(str, i, 1 + end - i);
	i = 0;
	while (result[i])
	{
		result[i] = Char_ToUppercase(result[i]);
		++i;
	}
	return (result);
}

int			Convert_String_To_Float_CheckInvalid(char const* str, char** result_tmp)
{
	char*	tmp;
	t_size	count_p;
	t_size	count_e;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (ERROR);
#endif
	*result_tmp = NULL;
	if (str[0] == '\0' || !(tmp = Convert_String_To_Float_ToUppercase(str)))
		return (ERROR);
	if (String_Equals(tmp,  "INF") || String_Equals(tmp,  "INFINITY") ||
		String_Equals(tmp, "+INF") || String_Equals(tmp, "+INFINITY") ||
		String_Equals(tmp, "-INF") || String_Equals(tmp, "-INFINITY"))
	{
		*result_tmp = tmp;
		return (OK);
	}
	count_p = String_Count_Char(tmp, 'P');
	count_e = String_Count_Char(tmp, 'E');
	if (!tmp || !tmp[0] || !String_HasOnly(tmp, "0123456789.+-ABCDEFXP") ||
		count_p > 1 || (count_p == 0 && count_e > 1))
	{
		if (tmp)
			Memory_Free(tmp);
		return (ERROR);
	}
	*result_tmp = tmp;
	return (OK);
}



#if LIBCONFIG_USE_FAST_APPROX_MATH

#define DEFINEFUNC_CONVERT_STR_TO_FLOAT(BITS) \
\
static t_f##BITS	Convert_String_To_F##BITS##_Expon(										\
	char const* str_mant,																	\
	char const* str_exp)																	\
{																							\
	t_f##BITS	result;																		\
	t_s16		exponent;																	\
	t_size		frac_digits;																\
	char*		tmp;																		\
																							\
	if (!(tmp = String_Remove(str_mant, ".")))												\
		return (NAN);																		\
	if (String_Length(tmp) > 18)															\
		tmp[18] = '\0';																		\
	result = (t_f##BITS)Convert_String_To_S64(tmp);											\
	Memory_Free(tmp);																		\
	if (!(exponent = 0) && str_exp)															\
	{																						\
		exponent = Convert_String_To_S16(str_exp);											\
		if (exponent > F##BITS##_EXPONENT_BIAS)												\
			return (str_mant[0] == '-' ? -INFINITY : INFINITY);								\
		else if (exponent < 1 - F##BITS##_EXPONENT_BIAS)									\
			return (0.);																	\
	}																						\
	tmp = String_Find_Char(str_mant, '.');													\
	if (tmp && (frac_digits = String_Length(++tmp)) > 0)									\
		exponent -= frac_digits;															\
	if (String_Length(str_mant) > 18)														\
		exponent += String_Length(str_mant) - 18;											\
	return (result * Math_Pow(10., exponent));												\
}																							\
																							\
static t_f##BITS	Convert_String_To_F##BITS##_HexFP(										\
	char const* str_mant,																	\
	char const* str_exp,																	\
	int sign)																				\
{																							\
	t_f##BITS	result;																		\
	t_s16		exponent;																	\
	t_u##BITS	mant;																		\
	char		*tmp;																		\
																							\
	result = sign ? -1. : 1.;																\
	tmp = String_Remove(str_mant, ".");														\
	if (String_Equals(tmp, "0") || String_Equals(tmp, "00"))								\
	{																						\
		Memory_Free(tmp);																	\
		return (0. * result);																\
	}																						\
	mant = Convert_HexString_To_U64(tmp);													\
	result *= mant * F##BITS##_INIT_VALUE * Math_Pow(2., (String_Length(tmp) - 1) * 4);		\
	if ((exponent = Convert_String_To_S16(str_exp)) > F##BITS##_EXPONENT_BIAS)				\
		return ((sign ? -1. : 1.) / 0.);													\
	else if (exponent < 1 - F##BITS##_EXPONENT_BIAS)										\
		return (0.);																		\
	Memory_Copy(&mant, &result, sizeof(result));											\
	mant &= F##BITS##_MANTISSA_SIGNED;														\
	mant |= F##BITS##_EXPONENT &															\
		((t_u##BITS)(exponent + F##BITS##_EXPONENT_BIAS) << F##BITS##_MANTISSA_BITS);		\
	Memory_Copy(&result, &mant, sizeof(result));											\
	Memory_Free(tmp);																		\
	return (result);																		\
}																							\
																							\
t_f##BITS			Convert_String_To_F##BITS(char const *str)								\
{																							\
	t_f##BITS	result;																		\
	char*	tmp;																			\
	char*	hexfp;																			\
	char*	exponent;																		\
	int		mode;																			\
																							\
	result = NAN;																			\
	if (Convert_String_To_Float_CheckInvalid(str, &tmp))									\
		return (result);																	\
	if (tmp[0] == 'I' || (tmp[1] == 'I' && (tmp[0] == '-' || tmp[0] == '+')))				\
	{																						\
		mode = (tmp[0] == '-');																\
		Memory_Free(tmp);																	\
		return (mode ? -INFINITY : INFINITY);												\
	}																						\
	hexfp = String_Find_Char(tmp, 'X');														\
	if ((exponent = String_Find_Char(tmp, (hexfp ? 'P' : 'E'))))							\
		*(exponent++) = '\0';																\
	if (!(mode = (hexfp != NULL) + (exponent != NULL)))										\
		result = Convert_String_To_F##BITS##_Expon(tmp, NULL);								\
	else if (mode == 1)																		\
		result = Convert_String_To_F##BITS##_Expon(tmp, exponent);							\
	else if (mode == 2)																		\
		result = Convert_String_To_F##BITS##_HexFP(hexfp + 1, exponent, tmp[0] == '-');		\
	Memory_Free(tmp);																		\
	return (result);																		\
}																							\

#else

#define DEFINEFUNC_CONVERT_STR_TO_FLOAT(BITS) \
inline t_f##BITS	Convert_String_To_F##BITS(char const* str)	\
{																\
	return (atof(str));											\
}																\

#endif

DEFINEFUNC_CONVERT_STR_TO_FLOAT(32)
DEFINEFUNC_CONVERT_STR_TO_FLOAT(64)
#ifdef __float80
DEFINEFUNC_CONVERT_STR_TO_FLOAT(80)
#endif
#ifdef __float128
DEFINEFUNC_CONVERT_STR_TO_FLOAT(128)
#endif
