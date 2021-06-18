
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/string.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FROMSTR(BASE, BITS) \
t_size	Q##BITS##_Parse##BASE(t_q##BITS *dest, t_char const* str)						\
{																						\
	t_s##BITS	result = 0;																\
	t_s##BITS	numerator = 0;															\
	t_s##BITS	denominator = 1;														\
	t_q##BITS	fraction = 0;															\
	t_size	i = 0;																		\
																						\
	HANDLE_ERROR(NULLPOINTER, (str == NULL),											\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);)								\
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }									\
	if (str[i] == '(')																	\
	{																					\
		++i;																			\
		goto fraction;																	\
	}																					\
/*integer:*/	\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),	\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)			\
	result = S##BITS##_FromString##BASE(str);											\
	if (str[i] == '+' || str[i] == '-')	++i;											\
	while (str[i] && Char_IsDigit(str[i]))	{ ++i; }									\
/*separator:*/	\
	if (str[i] == '.')	++i;															\
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }									\
	if (str[i] == '\0')	goto success;													\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || str[i] == '('),							\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": expected a fractional part separator char, but instead got \"%s\"", str)		\
fraction:	\
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }									\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),	\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": expected a fraction numerator, but instead got \"%s\"", str)					\
	numerator = S##BITS##_FromString##BASE(str);										\
	if (str[i] == '+' || str[i] == '-')	++i;											\
	while (str[i] && Char_IsDigit(str[i]))	{ ++i; }									\
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }									\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '/'),											\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": expected a fraction '/' separator char, but instead got \"%s\"", str)		\
	++i;																				\
	while (str[i] && Char_IsSpace(str[i]))	{ ++i; }									\
	HANDLE_ERROR_SF(PARSE, !(str[i] == '+' || str[i] == '-' || Char_IsDigit(str[i])),	\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": expected a fraction denominator, but instead got \"%s\"", str)				\
	denominator = S##BITS##_FromString##BASE(str);										\
	HANDLE_ERROR_SF(MATHDOMAIN, !(denominator == 0),									\
		if (dest) *dest = Q##BITS##_ERROR;	return (i);,								\
		": fraction denominator cannot be zero \"%s\"", str)							\
	fraction = Q##BITS##_From(numerator, denominator);									\
success:	\
	HANDLE_ERROR_SF(RESULTRANGE, (result < Q##BITS##_MININT),							\
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MIN),									\
		" (fixed-point underflow for integer part at "SF_S##BITS")", Q##BITS##_MININT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result > Q##BITS##_MAXINT),							\
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MAX),									\
		" (fixed-point overflow for integer part at "SF_S##BITS")", Q##BITS##_MAXINT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result + Q##BITS##_Round(fraction) < Q##BITS##_MININT),\
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MIN),									\
		" (fixed-point underflow for fraction part at "SF_S##BITS")", Q##BITS##_MININT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result + Q##BITS##_Round(fraction) > Q##BITS##_MAXINT),\
		LIBCONFIG_ERROR_PARSEROVERFLOW(Q##BITS##_MAX),									\
		" (fixed-point overflow for fraction part at "SF_S##BITS")", Q##BITS##_MAXINT)	\
	return (result * FIXED_DENOMINATOR + fraction);										\
}																						\
inline t_q##BITS	Q##BITS##_FromString##BASE(t_char const* str)						\
{																						\
	t_q##BITS	result = Q##BITS##_ERROR;												\
	Q##BITS##_Parse(&result, str);														\
	return (result);																	\
}																						\

DEFINEFUNC_FIXED_FROMSTR(,		16)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	16)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	16)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	16)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	16)

DEFINEFUNC_FIXED_FROMSTR(,		32)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	32)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	32)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	32)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	32)

DEFINEFUNC_FIXED_FROMSTR(,		64)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	64)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	64)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	64)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	64)

#ifdef __int128
DEFINEFUNC_FIXED_FROMSTR(,		128)
DEFINEFUNC_FIXED_FROMSTR(_Dec,	128)
DEFINEFUNC_FIXED_FROMSTR(_Hex,	128)
DEFINEFUNC_FIXED_FROMSTR(_Oct,	128)
DEFINEFUNC_FIXED_FROMSTR(_Bin,	128)
#endif
