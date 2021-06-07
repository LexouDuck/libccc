
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/pointer.h"
#include "libccc/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(BITS) \
t_q##BITS	Q##BITS##_FromString_Dec(t_char const* str)					\
{																		\
	t_u##BITS	result;													\
	t_bool	negative;													\
	t_size	i;															\
																		\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)				\
	for (i = 0; str[i] && Char_IsSpace(str[i]); ++i)					\
		continue;														\
	if (!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])))		\
		return (0);														\
	negative = FALSE;													\
	if (str[i] == '-')													\
	{																	\
		negative = TRUE;												\
		++i;															\
	}																	\
	else if (str[i] == '+')												\
		++i;															\
	result = 0;															\
	while (str[i] && Char_IsDigit(str[i]))								\
	{																	\
		result = result * 10 + (str[i++] - '0');						\
	}																	\
	return (negative ? -(t_q##BITS)result : (t_q##BITS)result);			\
}																		\

DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(16)
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(32)
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(64)
#ifdef __int128
DEFINEFUNC_CONVERT_STRDEC_TO_FIXED(128)
#endif
