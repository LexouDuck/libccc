
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/pointer.h"
#include "libccc/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(BITS) \
t_q##BITS	Q##BITS##_FromString_Dec(t_char const* str)									\
{																						\
	static const t_s##BITS	q##BITS##_min = (Q##BITS##_MIN / FIXED_DENOMINATOR);		\
	static const t_s##BITS	q##BITS##_max = (Q##BITS##_MAX / FIXED_DENOMINATOR);		\
	t_u##BITS	result;																	\
	t_u##BITS	tmp;																	\
	t_bool	negative;																	\
	t_size	i;																			\
																						\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)								\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)									\
	{																					\
		continue;																		\
	}																					\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),	\
		return (0);,																	\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)			\
	negative = FALSE;																	\
	if (str[i] == '-')																	\
	{																					\
		negative = TRUE;																\
		++i;																			\
	}																					\
	else if (str[i] == '+')																\
		++i;																			\
	result = 0;																			\
	while (str[i] && Char_IsDigit(str[i]))												\
	{																					\
		tmp = result * 10 + (str[i++] - '0');											\
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (t_u##BITS)-q##BITS##_min),		\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN),								\
			" (fixed-point underflow for \"%s\" at "SF_S##BITS")", str, q##BITS##_min)	\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (t_u##BITS)q##BITS##_max),		\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX),								\
			" (fixed-point overflow for \"%s\" at "SF_S##BITS")", str, q##BITS##_max)	\
		result = tmp;																	\
	}																					\
	return (negative ? -(t_q##BITS)result : (t_q##BITS)result);							\
}																						\

DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(16)
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(32)
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(128)
#endif
