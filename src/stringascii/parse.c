
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"
#include "libccc/text/unicode.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_ascii	String_Parse_GetEscape(t_ascii escapechar)
{
	static const struct { t_ascii esc; t_ascii chr; } lookuptable[] =
	{
		{ .esc =  '0',	.chr = '\x00',	}, // Null-terminator
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
		{ .esc = '\0' }
	};
	for (t_uint i = 0; lookuptable[i].esc != '\0'; ++i)
	{
		if (lookuptable[i].esc == escapechar)
			return (lookuptable[i].chr);
	}
	return (ERROR);
}



static
t_size	String_Parse_GetLength(t_ascii const* str, t_bool any_escape, t_size n)
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
			if (String_Parse_GetEscape(str[i]) != ERROR)
				length += 1 * sizeof(t_ascii);
			else switch (str[i])
			{
				case 'x':	length += 1 * sizeof(t_ascii);	break; // Hexadecimal t_ascii value
				case 'u':	length += 2 * sizeof(t_ascii);	break; // Unicode 2-byte t_ascii (encodes UTF-32 code point to UTF-8)
				case 'U':	length += 4 * sizeof(t_ascii);	break; // Unicode 4-byte t_ascii (encodes UTF-32 code point to UTF-8)
				default:
					if (Char_IsDigit_Oct(str[i])) // Octal t_ascii value
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



//! Parses a unicode escape sequence, and encodes the result into a UTF-8 multibyte character
#define	String_Parse_Unicode(_BITS_) \
	for (t_u8 c = 0; c < ((_BITS_) / 8); ++c)									\
	{																			\
		tmp[c*2+0] = str[++index];												\
		if (!Char_IsDigit_Hex(str[index]))	{ error = TRUE; break; }			\
		tmp[c*2+1] = str[++index];												\
		if (!Char_IsDigit_Hex(str[index]))	{ error = TRUE; break; }			\
	}																			\
	tmp[((_BITS_) / 4)] = '\0';													\
	unicode = U##_BITS_##_FromString_Hex(tmp);									\
	i += CharUTF32_ToUTF8((t_utf8*)result + i, unicode);						\



t_size	String_Parse(t_utf8* *dest, t_ascii const* str, t_size n, t_bool any_escape)
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
	result = (t_ascii*)Memory_New(String_Parse_GetLength(str, any_escape, n) + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	while (index < n && str[index])
	{
		if (str[index] == '\\') // escape sequence
		{
			++index;
			if CCCERROR((index == n || str[index] == '\0'), ERROR_PARSE, 
				"string ends with backslash, potential buffer overrun:\n%s", str)
				return (0);
			t_ascii	escapechar = String_Parse_GetEscape(str[index]);
			if (escapechar != ERROR)
				result[i++] = escapechar;
			else switch (str[index])
			{
				case 'u':	String_Parse_Unicode(16)	break; // Unicode 2-byte t_ascii (encodes UTF-32 code point to UTF-8)
				case 'U':	String_Parse_Unicode(32)	break; // Unicode 4-byte t_ascii (encodes UTF-32 code point to UTF-8)
				case 'x': // Hexadecimal byte value
					tmp[0] = str[++index];	if (!Char_IsDigit_Hex(tmp[0]))	error = TRUE;
					tmp[1] = str[++index];	if (!Char_IsDigit_Hex(tmp[1]))	error = TRUE;
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
		String_Delete(&result);
	}
	*dest = NULL;
	return (i);
}



inline
t_utf8*	String_FromEscape(t_ascii const* str, t_bool any_escape)
{
	t_ascii*	result = NULL;
	String_Parse(&result, str, 0, any_escape);
	return (result);
}
