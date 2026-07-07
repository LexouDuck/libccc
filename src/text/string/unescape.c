
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/escape.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_ascii	StringASCII_Unescape_GetEscape(t_ascii escapechar)
{
	static const struct { t_ascii esc; t_ascii chr; } lookuptable[] =
	{
		{ .esc =  '0',	.chr = '\0',	}, // Null-terminator
		{ .esc =  'a',	.chr = '\a',	}, // Alert (Beep, Bell) (added in C89)[1]
		{ .esc =  'b',	.chr = '\b',	}, // Backspace
		{ .esc =  't',	.chr = '\t',	}, // Horizontal Tab
		{ .esc =  'n',	.chr = '\n',	}, // Newline (Line Feed); see notes below
		{ .esc =  'v',	.chr = '\v',	}, // Vertical Tab
		{ .esc =  'f',	.chr = '\f',	}, // Form-feed
		{ .esc =  'r',	.chr = '\r',	}, // Carriage Return
		{ .esc =  'e',	.chr = '\x1B',	}, // Escape
		{ .esc = '\'',	.chr = '\'',	}, // Single quotation mark
		{ .esc = '\"',	.chr = '\"',	}, // Double quotation mark
		{ .esc =  '/',	.chr =  '/',	}, // Forward slash
		{ .esc = '\\',	.chr = '\\',	}, // Backslash
		{ .esc = '\0',	.chr = '\0',	}, // Null-terminator
	};
	for (t_uint i = 0; lookuptable[i].esc != '\0'; ++i)
	{
		if (lookuptable[i].esc == escapechar)
			return (lookuptable[i].chr);
	}
	return (ERROR);
}



static
t_size	StringASCII_Unescape_GetLength(t_ascii const* str, t_bool any_escape, t_size n)
{
	t_size	length = 0;
	t_size	i = 0;

	while (i < n && str[i])
	{
		if (str[i] == '\\') // escape sequence
		{
			++i;
			if CCCERROR((i == n || str[i] == '\0'), ERROR_PARSE, 
				"string ends with backslash, potential buffer overrun:\n%s", str)
				return (0);
			if (StringASCII_Unescape_GetEscape(str[i]) != (t_ascii)ERROR)
				length += 1 * sizeof(t_ascii);
			else switch (str[i])
			{
				case 'x':	length += 1 * sizeof(t_ascii);	break; // Hexadecimal t_ascii value
				case 'u':	length += 2 * sizeof(t_ascii);	break; // Unicode 2-byte t_ascii (encodes UTF-32 code point to UTF-8)
				case 'U':	length += 4 * sizeof(t_ascii);	break; // Unicode 4-byte t_ascii (encodes UTF-32 code point to UTF-8)
				default:
					if (CharASCII_IsDigit_Oct(str[i])) // Octal t_ascii value
						length += 1 * sizeof(t_ascii);
					else if (any_escape)
						length += 1 * sizeof(t_ascii);
					else
						length += 2 * sizeof(t_ascii);
					break;
			}
		}
		length += 1 * sizeof(t_ascii);
		++i;
	}
	return (length);
}



//! Parses the hexadecimal digits of a unicode escape sequence into `unicode`
#define	STRING_PARSE_UNICODE_HEX(BITS) \
	for (t_u8 c = 0; c < ((BITS) / 8); ++c) \
	{ \
		tmp[c*2+0] = str[++index]; \
		if (!CharASCII_IsDigit_Hex(str[index]))	{ error = TRUE; break; } \
		tmp[c*2+1] = str[++index]; \
		if (!CharASCII_IsDigit_Hex(str[index]))	{ error = TRUE; break; } \
	} \
	tmp[((BITS) / 4)] = '\0'; \
	unicode = U##BITS##_FromString_Hex(tmp); \

//! Encodes the parsed `unicode` codepoint into the result buffer (setting `error` if it is not encodable)
#define	STRING_WRITE_UNICODE() \
	if (!error) \
	{ \
		t_size encoded_len = CharUTF32_ToUTF8((t_utf8*)result + i, unicode); \
		if (encoded_len == 0 || encoded_len == (t_size)ERROR) \
			error = TRUE; \
		else i += encoded_len; \
	} \



t_size	StringASCII_Unescape(t_utf8* *dest, t_ascii const* str, t_size n, t_bool any_escape)
{
	t_ascii*	result = NULL;
	t_ascii	tmp[9] = { 0 };
	t_utf32	unicode = 0;
	t_bool	error = FALSE;
	t_size	index = 0;
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		goto failure;
	if (n == 0)
		n = SIZE_MAX;
	result = (t_ascii*)Memory_New(StringASCII_Unescape_GetLength(str, any_escape, n) + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	while (index < n && str[index])
	{
		if (str[index] == '\\') // escape sequence
		{
			++index;
			if CCCERROR((index == n || str[index] == '\0'), ERROR_PARSE, 
				"string ends with backslash, potential buffer overrun:\n%s", str)
				goto failure;
			t_ascii	escapechar = StringASCII_Unescape_GetEscape(str[index]);
			if (escapechar != (t_ascii)ERROR)
				result[i++] = escapechar;
			else switch (str[index])
			{
				case 'u': // Unicode UTF-16 code unit: "\uXXXX" (or surrogate pair: "\uXXXX\uXXXX"), encoded to UTF-8
				{
					STRING_PARSE_UNICODE_HEX(16)
					if (error)
						break;
					if ((unicode >= UTF16_SURROGATE_HI) && (unicode < UTF16_SURROGATE_LO))
					{	// high surrogate: a second "\uXXXX" sequence (the low surrogate) must follow
						t_utf32	code1 = unicode;
						if (str[index + 1] != '\\' || str[index + 2] != 'u')
						{
							error = TRUE;
							break;
						}
						index += 2;
						STRING_PARSE_UNICODE_HEX(16)
						if (error)
							break;
						if ((unicode < UTF16_SURROGATE_LO) || (unicode >= UTF16_SURROGATE_END))
						{	// the second code unit is not a valid low surrogate
							error = TRUE;
							break;
						}
						// calculate the unicode codepoint from the surrogate pair
						unicode = (t_utf32)(UTF16_BIAS + (((code1 & UTF16_SURROGATE_MASK) << 10) | (unicode & UTF16_SURROGATE_MASK)));
					}
					else if ((unicode >= UTF16_SURROGATE_LO) && (unicode < UTF16_SURROGATE_END))
					{	// lone low surrogate: not a valid unicode character
						error = TRUE;
						break;
					}
					STRING_WRITE_UNICODE()
					break;
				}
				case 'U': // Unicode UTF-32 code point: "\UXXXXXXXX", encoded to UTF-8
				{
					STRING_PARSE_UNICODE_HEX(32)
					if (!error && (unicode >= UTF16_SURROGATE_HI) && (unicode < UTF16_SURROGATE_END))
					{	// surrogate code points are not valid unicode characters
						error = TRUE;
						break;
					}
					STRING_WRITE_UNICODE()
					break;
				}
				case 'x': // Hexadecimal byte value
					tmp[0] = str[++index];	if (!CharASCII_IsDigit_Hex(tmp[0]))	error = TRUE;
					tmp[1] = str[++index];	if (!CharASCII_IsDigit_Hex(tmp[1]))	error = TRUE;
					tmp[2] = '\0';
					result[i++] = U8_FromString_Hex(tmp);
					break;

				default:
					if (any_escape)
					{
						result[i++] = str[index];
					}
					else
					{
						result[i++] = str[index - 1];
						result[i++] = str[index];
					}
					break;
			}
			if CCCERROR((error), ERROR_PARSE, NULL)
				goto failure;
		}
		else result[i++] = str[index];
		++index;
	}
	result[i] = '\0';
	if (dest)
		*dest = result;
	return (index);
failure:
	if (result != NULL)
	{
		StringASCII_Delete(&result);
	}
	if (dest)
		*dest = NULL;
	return (i);
}



_INLINE()
t_utf8*	StringASCII_FromEscaped(t_ascii const* str, t_bool any_escape)
{
	t_ascii*	result = NULL;
	StringASCII_Unescape(&result, str, 0, any_escape);
	return (result);
}
