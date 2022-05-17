
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/text/unicode.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_size	String_Parse_GetLength(t_char const* str, t_bool any_escape, t_size n)
{
	t_size	length = 0;
	t_size	i = 0;

	while (i < n && str[i])
	{
		if (str[i] == '\\') // escape sequence
		{
			++i;
			HANDLE_ERROR_SF(PARSE, (i == n || str[i] == '\0'), return (0);,
				"string ends with backslash, potential buffer overrun:\n%s", str)
			switch (str[i])
			{
				case 'a':	length += 1 * sizeof(t_char);	break; // Alert (Beep, Bell) (added in C89)[1]
				case 'b':	length += 1 * sizeof(t_char);	break; // Backspace
				case 't':	length += 1 * sizeof(t_char);	break; // Horizontal Tab
				case 'n':	length += 1 * sizeof(t_char);	break; // Newline (Line Feed); see notes below
				case 'v':	length += 1 * sizeof(t_char);	break; // Vertical Tab
				case 'f':	length += 1 * sizeof(t_char);	break; // Form-feed
				case 'r':	length += 1 * sizeof(t_char);	break; // Carriage Return
				case 'e':	length += 1 * sizeof(t_char);	break; // Escape
				case '\'':	length += 1 * sizeof(t_char);	break; // Single quotation mark
				case '\"':	length += 1 * sizeof(t_char);	break; // Double quotation mark
				case  '?':	length += 1 * sizeof(t_char);	break; // Question mark (used to avoid trigraphs)
				case  '/':	length += 1 * sizeof(t_char);	break; // Forward slash
				case '\\':	length += 1 * sizeof(t_char);	break; // Backslash
				case 'x':	length += 1 * sizeof(t_char);	break; // Hexadecimal t_char value
				case 'u':	length += 2 * sizeof(t_char);	break; // Unicode 2-byte t_char (encodes UTF-32 code point to UTF-8)
				case 'U':	length += 4 * sizeof(t_char);	break; // Unicode 4-byte t_char (encodes UTF-32 code point to UTF-8)
				default:
					if (Char_IsDigit_Oct(str[i])) // Octal t_char value
						length += 1 * sizeof(t_char);
					else if (any_escape)
						length += 1 * sizeof(t_char);
					else
						length += 2 * sizeof(t_char);
					break;
			}
		}
		length += 1 * sizeof(t_char);
		++i;
	}
	return (length);
}



//! Parses a unicode escape sequence, and encodes the result into a UTF-8 multibyte character
#define	String_Parse_Unicode(_BITS_) \
	for (t_u8 c = 0; c < ((_BITS_) / 8); ++c)									\
	{																			\
		tmp[c*2+0] = str[++index]; if (!Char_IsDigit_Hex(str[index]))	break;	\
		tmp[c*2+1] = str[++index]; if (!Char_IsDigit_Hex(str[index]))	break;	\
	}																			\
	tmp[((_BITS_) / 4)] = '\0';													\
	unicode = U##_BITS_##_FromString_Hex(tmp);									\
	i += CharUTF32_ToUTF8((t_utf8*)result + i, unicode);							\



t_size	String_Parse(t_utf8* *dest, t_char const* str, t_size n, t_bool any_escape)
{
	t_char*	result;
	t_char	tmp[9] = { 0 };
	t_utf32	unicode;
	t_size	index = 0;
	t_size	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), PARSE_RETURN(NULL);)
	if (n == 0)
		n = SIZE_MAX;
	result = (t_char*)Memory_New(String_Parse_GetLength(str, any_escape, n) + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), PARSE_RETURN(NULL);)
	while (index < n && str[index])
	{
		if (str[index] == '\\') // escape sequence
		{
			++index;
			HANDLE_ERROR_SF(PARSE, (index == n || str[index] == '\0'), return (0);,
				"string ends with backslash, potential buffer overrun:\n%s", str)
			switch (str[index])
			{
				case 'a':	result[i++] = '\x07';	break; // Alert (Beep, Bell) (added in C89)[1]
				case 'b':	result[i++] = '\x08';	break; // Backspace
				case 't':	result[i++] = '\x09';	break; // Horizontal Tab
				case 'n':	result[i++] = '\x0A';	break; // Newline (Line Feed); see notes below
				case 'v':	result[i++] = '\x0B';	break; // Vertical Tab
				case 'f':	result[i++] = '\x0C';	break; // Formfeed
				case 'r':	result[i++] = '\x0D';	break; // Carriage Return
				case 'e':	result[i++] = '\x1B';	break; // Escape
				case '\'':	result[i++] = '\'';		break; // Single quotation mark
				case '\"':	result[i++] = '\"';		break; // Double quotation mark
				case  '/':	result[i++] = '/';		break; // Forward Slash
				case '\\':	result[i++] = '\\';		break; // Backslash
				case 'u':	String_Parse_Unicode(16)	break; // Unicode 2-byte t_char (encodes UTF-32 code point to UTF-8)
				case 'U':	String_Parse_Unicode(32)	break; // Unicode 4-byte t_char (encodes UTF-32 code point to UTF-8)
				case 'x': // Hexadecimal byte value
					tmp[0] = str[++index];
					tmp[1] = str[++index];
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
		}
		else result[i++] = str[index];
		++index;
	}
	result[i] = '\0';
	if (dest)	*dest = result;
	return (index);
}



inline
t_utf8*	String_FromEscape(t_char const* str, t_bool any_escape)
{
	t_char*	result = NULL;
	String_Parse(&result, str, 0, any_escape);
	return (result);
}
