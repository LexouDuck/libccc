
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTR(BITS) \
t_size	U##BITS##_Parse(t_u##BITS *dest, t_char const* str, t_size n)				\
{																					\
	t_char const* s = NULL;															\
	t_size	i = 0;																	\
																					\
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")	\
		goto failure;																\
	if (n == 0)																		\
		n = SIZE_MAX;																\
	for (i = 0; (i < n - 1 && str[i]); ++i)											\
	{																				\
		if (str[i] == '0')															\
		{																			\
			s = str + i;															\
			break;																	\
		}																			\
	}																				\
	if (s && s[0] && s[0] == '0')													\
	{																				\
		switch (s[1])																\
		{																			\
			case 'x': return (U##BITS##_Parse_Hex(dest, str, n - i));				\
			case 'o': return (U##BITS##_Parse_Oct(dest, str, n - i));				\
			case 'b': return (U##BITS##_Parse_Bin(dest, str, n - i));				\
		}																			\
	}																				\
	return (U##BITS##_Parse_Dec(dest, str, n - i));									\
failure:																			\
	PARSE_RETURN(S##BITS##_ERROR);													\
}																					\
inline t_u##BITS	U##BITS##_FromString(t_char const* str)							\
{																					\
	t_u##BITS	result = U##BITS##_ERROR;											\
	U##BITS##_Parse(&result, str, 0);												\
	return (result);																\
}

DEFINEFUNC_UINT_FROMSTR(8)
DEFINEFUNC_UINT_FROMSTR(16)
DEFINEFUNC_UINT_FROMSTR(32)
DEFINEFUNC_UINT_FROMSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_FROMSTR(128)
#endif



#define DEFINEFUNC_SINT_FROMSTR(BITS) \
t_size	S##BITS##_Parse(t_s##BITS *dest, t_char const* str, t_size n)				\
{																					\
	t_char const* s = NULL;															\
	t_size	i = 0;																	\
																					\
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")	\
		goto failure;																\
	if (n == 0)																		\
		n = SIZE_MAX;																\
	for (i = 0; (i < n - 1 && str[i]); ++i)											\
	{																				\
		if (str[i] == '0')															\
		{																			\
			s = str + i;															\
			break;																	\
		}																			\
	}																				\
	if (s && s[0] && s[0] == '0')													\
	{																				\
		switch (s[1])																\
		{																			\
			case 'x': return (S##BITS##_Parse_Hex(dest, str, n - i));				\
			case 'o': return (S##BITS##_Parse_Oct(dest, str, n - i));				\
			case 'b': return (S##BITS##_Parse_Bin(dest, str, n - i));				\
		}																			\
	}																				\
	return (S##BITS##_Parse_Dec(dest, str, n - i));									\
failure:																			\
	PARSE_RETURN(S##BITS##_ERROR);													\
}																					\
inline t_s##BITS	S##BITS##_FromString(t_char const* str)							\
{																					\
	t_s##BITS	result = S##BITS##_ERROR;											\
	S##BITS##_Parse(&result, str, 0);												\
	return (result);																\
}

DEFINEFUNC_SINT_FROMSTR(8)
DEFINEFUNC_SINT_FROMSTR(16)
DEFINEFUNC_SINT_FROMSTR(32)
DEFINEFUNC_SINT_FROMSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_FROMSTR(128)
#endif
