
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_FROMSTRDEC(UINT_TYPE, UINT_NAME, UINT_MACRO) \
t_size	UINT_NAME##_Parse(UINT_TYPE* dest, t_char const* str)							\
{																						\
	UINT_TYPE	result;																	\
	UINT_TYPE	tmp;																	\
	t_size	i = 0;																		\
																						\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),											\
		PARSE_RETURN(UINT_MACRO##_ERROR))												\
	while (str[i] && Char_IsSpace(str[i]))												\
	{																					\
		++i;																			\
	}																					\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || Char_IsDigit(str[i])),					\
		PARSE_RETURN(UINT_MACRO##_ERROR),												\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)			\
	if (str[i] == '+')																	\
		++i;																			\
	result = 0;																			\
	while (str[i] && Char_IsDigit(str[i]))												\
	{																					\
		tmp = result * 10 + (str[i++] - '0');											\
		HANDLE_ERROR_SF(RESULTRANGE, (tmp < result),									\
			LIBCONFIG_ERROR_PARSEROVERFLOW(UINT_MACRO##_MAX),							\
			" (integer overflow for \"%s\" at "SF_##UINT_MACRO")", str, UINT_MACRO##_MAX)\
		result = tmp;																	\
	}																					\
	if (dest)	*dest = result;															\
	return (i);																			\
}																						\
inline UINT_TYPE	UINT_NAME##_FromString(t_char const* str)							\
{																						\
	UINT_TYPE	result = UINT_MACRO##_ERROR;											\
	UINT_NAME##_Parse(&result, str);													\
	return (result);																	\
}																						\



#define DEFINEFUNC_SINT_FROMSTRDEC(SINT_TYPE, SINT_NAME, SINT_MACRO, UINT_TYPE) \
t_size	SINT_NAME##_Parse(SINT_TYPE* dest, t_char const* str)							\
{																						\
	UINT_TYPE	result;																	\
	UINT_TYPE	tmp;																	\
	t_bool	negative;																	\
	t_size	i = 0;																		\
																						\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),											\
		PARSE_RETURN(SINT_MACRO##_ERROR))												\
	while (str[i] && Char_IsSpace(str[i]))												\
	{																					\
		++i;																			\
	}																					\
	HANDLE_ERROR_SF(PARSE,																\
		!(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),						\
		PARSE_RETURN(SINT_MACRO##_ERROR),												\
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
		HANDLE_ERROR_SF(RESULTRANGE, (negative && tmp > (UINT_TYPE)SINT_MACRO##_MIN),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(SINT_MACRO##_MIN),							\
			" (integer underflow for \"%s\" at "SF_##SINT_MACRO")", str, SINT_MACRO##_MIN)\
		HANDLE_ERROR_SF(RESULTRANGE, (!negative && tmp > (UINT_TYPE)SINT_MACRO##_MAX),	\
			LIBCONFIG_ERROR_PARSEROVERFLOW(SINT_MACRO##_MAX),							\
			" (integer overflow for \"%s\" at "SF_##SINT_MACRO")", str, SINT_MACRO##_MAX)\
		result = tmp;																	\
	}																					\
	if (dest)	*dest = (negative ? -(SINT_TYPE)result : (SINT_TYPE)result);			\
	return (i);																			\
}																						\
inline SINT_TYPE	SINT_NAME##_FromString(t_char const* str)							\
{																						\
	SINT_TYPE	result = SINT_MACRO##_ERROR;											\
	SINT_NAME##_Parse(&result, str);													\
	return (result);																	\
}																						\



DEFINEFUNC_UINT_FROMSTRDEC(t_size,		Size,		SIZE)
DEFINEFUNC_SINT_FROMSTRDEC(t_ptrdiff,	PtrDiff,	PTRDIFF, t_size)
DEFINEFUNC_UINT_FROMSTRDEC(t_uintmax,	UIntMax,	UINTMAX)
DEFINEFUNC_SINT_FROMSTRDEC(t_sintmax,	SIntMax,	SINTMAX, t_uintmax)
DEFINEFUNC_UINT_FROMSTRDEC(t_uintptr,	UIntPtr,	UINTPTR)
DEFINEFUNC_SINT_FROMSTRDEC(t_sintptr,	SIntPtr,	SINTPTR, t_uintptr)
