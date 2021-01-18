
#include "libccc_memory.h"
#include "libccc_convert.h"



static t_size	Convert_Int_To_BaseString_GetLength(char const *base, t_bool sign)
{
	t_size	i;
	t_size	j;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (base == NULL)
		return (0);
#endif
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
char*	Convert_U##BITS##_To_BaseString(t_u##BITS number, char const* base)	\
{																			\
	char*	result;															\
	char	digits[BITS];													\
	t_size	length;															\
	t_size	i;																\
	t_u##BITS	n;															\
																			\
	length = Convert_Int_To_BaseString_GetLength(base, FALSE);				\
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
	if (!(result = (char*)Memory_Alloc(i + 1)))								\
		return (NULL);														\
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



#define DEFINEFUNC_CONVERT_SINT_TO_STRBASE(BITS) \
char*	Convert_S##BITS##_To_BaseString(t_s##BITS number, char const* base)	\
{																			\
	char*	result;															\
	char	digits[BITS];													\
	t_size	length;															\
	t_size	i;																\
	t_u##BITS	n;															\
																			\
	length = Convert_Int_To_BaseString_GetLength(base, TRUE);				\
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
	if (!(result = (char*)Memory_Alloc(i + 2)))								\
		return (NULL);														\
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
