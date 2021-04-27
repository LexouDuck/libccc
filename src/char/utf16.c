
#include "libccc/char.h"
#include "libccc/pointer.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"



#define SURROGATE_MASK	0x3FF
#define SURROGATE_HI	0xD800
#define SURROGATE_LO	0xDC00
#define SURROGATE_END	0xE000
#define UTF16_BIAS		0x10000



t_size		Char_ToUTF16(t_utf16* dest, t_utf32 c)
{
	LIBCONFIG_HANDLE_NULLPOINTER(dest, 0)
	if (c >= SURROGATE_HI)
	{
		if (c < SURROGATE_END) // INVALID UTF-16
			return (ERROR);
		c -= UTF16_BIAS;
		dest[0] = (c >> 10) + SURROGATE_HI;
		dest[1] = (c & ((1 << 10) - 1)) + SURROGATE_LO;
		return (4);
	}
	else
	{
		dest[0] = (t_utf16)c;
		return (2);
	}
}



t_utf32		Char_FromUTF16(t_utf16 const* str)
{
	t_u16 c;

	LIBCONFIG_HANDLE_NULLPOINTER(str, ERROR)
	c = str[0];
	if (c >= SURROGATE_HI)
	{
		t_utf32 result = (c - SURROGATE_HI) << 10;
		c = str[1];
		if (c < SURROGATE_LO) // INVALID UTF-16
			return (ERROR);
		result |= (c - SURROGATE_LO);
		result += UTF16_BIAS;
		return (result);
	}
	else return ((t_utf32)c);
}



//! parse a 4-digit hexadecimal number from the given `str`
static
t_u16	Char_Parse_UTF16_Hex4(t_char const* str)
{
	t_uint result = 0;
	t_size i = 0;

	for (i = 0; i < 4; i++)
	{
		// p digit
		if ((str[i] >= '0') && (str[i] <= '9'))			result += (t_uint)(str[i] - '0');
		else if ((str[i] >= 'A') && (str[i] <= 'F'))	result += (t_uint)(str[i] - 'A' + 10);
		else if ((str[i] >= 'a') && (str[i] <= 'f'))	result += (t_uint)(str[i] - 'a' + 10);
		else // invalid
			return (0);

		if (i < 3)
		{	// shift left to make place for the next nibble
			result <<= 4;
		}
	}
	return (result);
}



#define ERROR_Char_Parse_UTF16	"Could not parse UTF-16 escape sequence: "

t_utf32		Char_Parse_UTF16(t_char const* str)
{
	t_utf32	result = 0;
	t_size	length = 0;
	t_size	sequence_length;
	t_u16	code1;
	t_u16	code2;

	LIBCONFIG_HANDLE_NULLPOINTER(str, ERROR)
	sequence_length = 6;
	length = String_Length(str);
	if (sequence_length >= length)
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "input ends unexpectedly during the first '\\u' sequence")
	if (str[0] != '\\')
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "not a valid escape sequence, expected '\\' char")
	if (str[1] != 'u')
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "not a valid UTF-16 escape sequence, expected 'u' char")
	// get the first UTF-16 sequence
	code1 = Char_Parse_UTF16_Hex4(str + 2);
	// check that the code is valid
	if (((code1 >= SURROGATE_LO) && (code1 < SURROGATE_END)))
		LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "invalid UTF-16 char code ("FORMAT_HEX_U16")", code1)
	// UTF16 surrogate pair
	if ((code1 >= SURROGATE_HI) && (code1 < SURROGATE_LO))
	{
		t_char const* str2 = str + 6;
		code2 = 0;
		sequence_length = 12; // \uXXXX\uXXXX
		if (sequence_length >= length)
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "input ends unexpectedly during the second '\\u' sequence")
		if ((str2[0] != '\\') || (str2[1] != 'u'))
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "missing second half of the surrogate pair, expected second '\\u' sequence")
		// get the second utf16 sequence
		code2 = Char_Parse_UTF16_Hex4(str2 + 2);
		// check that the code is valid
		if ((code2 < 0xDC00) || (code2 > 0xDFFF))
			LIBCONFIG_HANDLE_PARSINGERROR(ERROR, "invalid second half of the surrogate pair ("FORMAT_HEX_U16")", code2)
		// calculate the unicode codepoint from the surrogate pair
		result = UTF16_BIAS + (((code1 & SURROGATE_MASK) << 10) | (code2 & SURROGATE_MASK));
	}
	else
	{
		sequence_length = 6; // \uXXXX
		result = code1;
	}
	return (result);
}
