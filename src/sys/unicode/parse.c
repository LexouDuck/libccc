
#include "libccc/sys/unicode.h"
#include "libccc/pointer.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"



//! parse a 4-digit hexadecimal number from the given `str`
#define DEFINEFUNC_PARSE_HEX(BITS) \
static t_bool	UTF32_Parse_Hex_##BITS(t_u##BITS* dest, t_ascii const* str)	\
{																					\
	t_u##BITS result;																\
	t_size i;																		\
																					\
	result = 0;																		\
	for (i = 0; i < (BITS / 4); i++)												\
	{																				\
		if ((str[i] >= '0') && (str[i] <= '9'))										\
			result += (t_u##BITS)(str[i] - '0');									\
		else if ((str[i] >= 'A') && (str[i] <= 'F'))								\
			result += (t_u##BITS)(str[i] - 'A' + 10);								\
		else if ((str[i] >= 'a') && (str[i] <= 'f'))								\
			result += (t_u##BITS)(str[i] - 'a' + 10);								\
		else /* invalid */															\
			return (ERROR);															\
		if (i < ((BITS / 4) - 1))													\
		{	/* shift left to make room for the next nibble */						\
			result <<= 4;															\
		}																			\
	}																				\
	*dest = result;																	\
	return (OK);																	\
}																					\

DEFINEFUNC_PARSE_HEX(16)
DEFINEFUNC_PARSE_HEX(32)



#define PARSINGERROR_UTF16	"Could not parse UTF-16 escape sequence: "
#define PARSINGERROR_UTF16_SURROGATE	PARSINGERROR_UTF16"2nd half of surrogate pair -> "

t_size		UTF32_Parse_N(t_utf32* dest, t_ascii const* str, t_size n)
{
	t_utf32	result = 0;
	t_size	length;
	t_size	i = 0;
	t_u16	code1;
	t_u16	code2;

	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, str)
	if (n == 0)
		n = String_Length(str);
	length = 6; // "\uXXXX"
	if (length >= n)
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"input ends unexpectedly")
	if (str[i] != '\\')
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"not a valid escape sequence, expected '\\' char")
	i += 1;
	if (str[i] == 'U')
	{
		i += 1;
		if (UTF32_Parse_Hex_32(&result, str + i)) // get the whole UTF-32 sequence
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"not a valid UTF-16 escape sequence, expected 4 hexadecimal digits")
		i += 8;
	}
	else if (str[i] == 'u')
	{
		i += 1;
		if (UTF32_Parse_Hex_16(&code1, str + i)) // get the first UTF-16 sequence
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"not a valid UTF-16 escape sequence, expected 4 hexadecimal digits")
		i += 4;
		if (((code1 >= UTF16_SURROGATE_LO) && (code1 < UTF16_SURROGATE_END)))
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"invalid UTF-16 char code ("FORMAT_HEX_U16")", code1)
		if ((code1 >= UTF16_SURROGATE_HI) && (code1 < UTF16_SURROGATE_LO))
		{	// UTF16 surrogate pair
			code2 = 0;
			length = 12; // "\uXXXX\uXXXX"
			if (length >= n)
				LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16_SURROGATE"input ends unexpectedly")
			if (str[i] != '\\')
				LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16_SURROGATE"not a valid escape sequence, expected '\\' char")
			i += 1;
			if (str[i] != 'u')
				LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16_SURROGATE"not a valid UTF-16 escape sequence, expected 'u' char")
			i += 1;
			if (UTF32_Parse_Hex_16(&code2, str + 2)) // get the second UTF-16 sequence
				LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16_SURROGATE"not a valid UTF-16 escape sequence, expected 4 hexadecimal digits")
			i += 4;
			if ((code2 < UTF16_SURROGATE_LO) || (code2 >= UTF16_SURROGATE_END))
				LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16_SURROGATE"invalid UTF-16 char code for second half of the surrogate pair ("FORMAT_HEX_U16")", code2)
			// calculate the unicode codepoint from the surrogate pair
			result = (t_utf32)(UTF16_BIAS + (((code1 & UTF16_SURROGATE_MASK) << 10) | (code2 & UTF16_SURROGATE_MASK)));
		}
		else
		{
			result = (t_utf32)code1;
		}
	}
	else
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, PARSINGERROR_UTF16"not a valid UTF-16 escape sequence, expected 'u' char")
	*dest = result;
	return (i);
}

t_utf32		UTF32_Parse(t_ascii const* str)
{
	t_utf32	result = ERROR;
	if (UTF32_Parse_N(&result, str, 0))
		return (result);
	return (ERROR);
}
