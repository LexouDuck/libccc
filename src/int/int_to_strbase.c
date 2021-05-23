
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



static t_size	Int_ToString_Base_GetLength(t_char const* base, t_bool sign)
{
	t_size	i;
	t_size	j;

	HANDLE_ERROR(NULLPOINTER, (base == NULL), return (0);)
	i = 0;
	while (base[i])
	{
		if (sign && (base[i] == '+' || base[i] == '-'))
			return (0);
		j = i - 1;
		while (j != (t_size)-1)
		{
			if (base[i] == base[j])
				return (0);
			--j;
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}



#define DEFINEFUNC_CONVERT_UINT_TO_STRBASE(BITS) \
t_char*	U##BITS##_ToString_Base(t_u##BITS number, t_char const* base)			\
{																			\
	t_char*	result;															\
	char	digits[BITS];													\
	t_size	length;															\
	t_size	i;																\
	t_u##BITS	n;															\
																			\
	length = Int_ToString_Base_GetLength(base, FALSE);						\
	if (length == 0)														\
		return (NULL);														\
	n = number;																\
	i = 0;																	\
	while (n > 0)															\
	{																		\
		digits[i++] = base[n % length];										\
		n /= length;														\
	}																		\
	if (i == 0)																\
		digits[i++] = base[0];												\
	result = (t_char*)Memory_Alloc(i + 1);									\
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)			\
	n = 0;																	\
	while (i--)																\
	{																		\
		result[n++] = digits[i];											\
	}																		\
	result[n] = '\0';														\
	return (result);														\
}																			\

DEFINEFUNC_CONVERT_UINT_TO_STRBASE(8)
DEFINEFUNC_CONVERT_UINT_TO_STRBASE(16)
DEFINEFUNC_CONVERT_UINT_TO_STRBASE(32)
DEFINEFUNC_CONVERT_UINT_TO_STRBASE(64)
#ifdef __int128
DEFINEFUNC_CONVERT_UINT_TO_STRBASE(128)
#endif



#define DEFINEFUNC_CONVERT_SINT_TO_STRBASE(BITS) \
t_char*	S##BITS##_ToString_Base(t_s##BITS number, t_char const* base)			\
{																			\
	t_char*	result;															\
	char	digits[BITS];													\
	t_size	length;															\
	t_size	i;																\
	t_u##BITS	n;															\
																			\
	length = Int_ToString_Base_GetLength(base, TRUE);						\
	if (length == 0)														\
		return (NULL);														\
	if (number < 0)															\
		n = -number;														\
	else n = number;														\
	i = 0;																	\
	while (n > 0)															\
	{																		\
		digits[i++] = base[n % length];										\
		n /= length;														\
	}																		\
	result = (t_char*)Memory_Alloc(i + 2);									\
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)			\
	result[0] = (number == 0) ? base[0] : '-';								\
	n = (number <= 0) ? 1 : 0;												\
	while (i--)																\
		result[n++] = digits[i];											\
	result[n] = '\0';														\
	return (result);														\
}																			\

DEFINEFUNC_CONVERT_SINT_TO_STRBASE(8)
DEFINEFUNC_CONVERT_SINT_TO_STRBASE(16)
DEFINEFUNC_CONVERT_SINT_TO_STRBASE(32)
DEFINEFUNC_CONVERT_SINT_TO_STRBASE(64)
#ifdef __int128
DEFINEFUNC_CONVERT_SINT_TO_STRBASE(128)
#endif
