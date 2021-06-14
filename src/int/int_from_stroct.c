
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTROCT(BITS) \
t_u##BITS	U##BITS##_FromString_Oct(t_char const* str)								\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (U##BITS##_ERROR);)				\
	while (*str && Char_IsSpace(*str))												\
	{																				\
		++str;																		\
	}																				\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || Char_IsDigit_Oct(*str)),				\
		return (U##BITS##_ERROR);,													\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	if (str[i] == '+')																\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'o')											\
		i += 2;																		\
	result = 0;																		\
	while (str[i] && Char_IsDigit_Oct(str[i]))										\
	{																				\
		tmp = result * 8 + (str[i] - '0');											\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result),								\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_U##BITS")", str, U##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	return (result);																\
}																					\

DEFINEFUNC_UINT_FROMSTROCT(8)
DEFINEFUNC_UINT_FROMSTROCT(16)
DEFINEFUNC_UINT_FROMSTROCT(32)
DEFINEFUNC_UINT_FROMSTROCT(64)
#ifdef __int128
DEFINEFUNC_UINT_FROMSTROCT(128)
#endif



#define DEFINEFUNC_SINT_FROMSTROCT(BITS) \
t_s##BITS	S##BITS##_FromString_Oct(t_char const* str)								\
{																					\
	t_u##BITS	result;																\
	t_u##BITS	tmp;																\
	t_bool	negative;																\
	t_size	i = 0;																	\
																					\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (S##BITS##_ERROR);)				\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)								\
		continue;																	\
	HANDLE_ERROR_SF(PARSE,															\
		!(str[i] == '+' || str[i] == '-' || Char_IsDigit_Oct(str[i])),				\
		return (S##BITS##_ERROR);,													\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)		\
	negative = FALSE;																\
	if (str[i] == '-')																\
	{																				\
		negative = TRUE;															\
		++i;																		\
	}																				\
	else if (str[i] == '+')															\
		++i;																		\
	if (str[i] == '0' && str[i + 1] == 'o')											\
		i += 2;																		\
	result = 0;																		\
	while (str[i] && Char_IsDigit_Oct(str[i]))										\
	{																				\
		tmp = result * 8 + (str[i++] - '0');										\
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (t_u##BITS)S##BITS##_MIN),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN),							\
			" (integer underflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MIN)	\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (t_u##BITS)S##BITS##_MAX),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX),							\
			" (integer overflow for \"%s\" at "SF_S##BITS")", str, S##BITS##_MAX)	\
		result = tmp;																\
	}																				\
	return (negative ? -(t_s##BITS)result : (t_s##BITS)result);						\
}																					\

DEFINEFUNC_SINT_FROMSTROCT(8)
DEFINEFUNC_SINT_FROMSTROCT(16)
DEFINEFUNC_SINT_FROMSTROCT(32)
DEFINEFUNC_SINT_FROMSTROCT(64)
#ifdef __int128
DEFINEFUNC_SINT_FROMSTROCT(128)
#endif
