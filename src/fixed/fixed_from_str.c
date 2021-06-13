
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/string.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_FROMSTR(BASE, BITS) \
t_q##BITS	Q##BITS##_FromString##BASE(t_char const* str)								\
{																						\
	t_s##BITS	result = 0;																\
	t_s##BITS	numerator = 0;															\
	t_s##BITS	denominator = 1;														\
	t_q##BITS	fraction = 0;															\
																						\
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)								\
	while (*str && Char_IsSpace(*str))	{ ++str; }										\
	if (*str == '(')																	\
	{																					\
		++str;																			\
		goto fraction;																	\
	}																					\
/*integer:*/	\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || *str == '-' || Char_IsDigit(*str)),			\
		return (0);,																	\
		": expected a number (with spaces/sign), but instead got \"%s\"", str)			\
	result = S##BITS##_FromString##BASE(str);											\
	if (*str == '+' || *str == '-')	++str;												\
	while (*str && Char_IsDigit(*str))	{ ++str; }										\
/*separator:*/	\
	if (*str == '.')	++str;															\
	while (*str && Char_IsSpace(*str))	{ ++str; }										\
	if (*str == '\0')	goto success;													\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || *str == '('), return (0);,					\
		": expected a fractional part separator char, but instead got \"%s\"", str)		\
fraction:	\
	while (*str && Char_IsSpace(*str))	{ ++str; }										\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || *str == '-' || Char_IsDigit(*str)),			\
		return (0);,																	\
		": expected a fraction numerator, but instead got \"%s\"", str)					\
	numerator = S##BITS##_FromString##BASE(str);										\
	if (*str == '+' || *str == '-')	++str;												\
	while (*str && Char_IsDigit(*str))	{ ++str; }										\
	while (*str && Char_IsSpace(*str))	{ ++str; }										\
	HANDLE_ERROR_SF(PARSE, !(*str == '/'), return (0);,									\
		": expected a fraction '/' separator char, but instead got \"%s\"", str)		\
	++str;																				\
	while (*str && Char_IsSpace(*str))	{ ++str; }										\
	HANDLE_ERROR_SF(PARSE, !(*str == '+' || *str == '-' || Char_IsDigit(*str)),			\
		return (0);,																	\
		": expected a fraction denominator, but instead got \"%s\"", str)				\
	denominator = S##BITS##_FromString##BASE(str);										\
	HANDLE_ERROR_SF(MATHDOMAIN, !(denominator == 0), return (0);,						\
		": fraction denominator cannot be zero \"%s\"", str)							\
	fraction = Q##BITS##_From(numerator, denominator);									\
success:	\
	HANDLE_ERROR_SF(RESULTRANGE, (result < Q##BITS##_MININT),							\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MIN),									\
		" (fixed-point underflow for integer part at "SF_S##BITS")", Q##BITS##_MININT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result > Q##BITS##_MAXINT),							\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MAX),									\
		" (fixed-point overflow for integer part at "SF_S##BITS")", Q##BITS##_MAXINT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result + Q##BITS##_Round(fraction) < Q##BITS##_MININT),\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MIN),									\
		" (fixed-point underflow for fraction part at "SF_S##BITS")", Q##BITS##_MININT)	\
	HANDLE_ERROR_SF(RESULTRANGE, (result + Q##BITS##_Round(fraction) > Q##BITS##_MAXINT),\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MAX),									\
		" (fixed-point overflow for fraction part at "SF_S##BITS")", Q##BITS##_MAXINT)	\
	return (result * FIXED_DENOMINATOR + fraction);										\
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
