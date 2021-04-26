
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"



static
t_size	String_Parse_GetLength(t_char const* str, t_bool any_escape)
{
	t_size	length = 0;
	t_size	i = 0;

	while (str[i])
	{
		if (str[i] == '\\') // escape sequence
		{
			++i;
			switch (str[i])
			{
				case 'a':	length += 1;	break; // Alert (Beep, Bell) (added in C89)[1]
				case 'b':	length += 1;	break; // Backspace
				case 't':	length += 1;	break; // Horizontal Tab
				case 'n':	length += 1;	break; // Newline (Line Feed); see notes below
				case 'v':	length += 1;	break; // Vertical Tab
				case 'f':	length += 1;	break; // Form-feed
				case 'r':	length += 1;	break; // Carriage Return
				case 'e':	length += 1;	break; // Escape
				case '\'':	length += 1;	break; // Single quotation mark
				case '\"':	length += 1;	break; // Double quotation mark
				case  '?':	length += 1;	break; // Question mark (used to avoid trigraphs)
				case '\\':	length += 1;	break; // Backslash
				case 'x':	length += 1;	break; // Hexadecimal byte value
				case 'u':	length += 2;	break; // Unicode 2-byte t_char (UTF-16)
				case 'U':	length += 4;	break; // Unicode 4-byte t_char (UTF-32)
				default:
					if (any_escape)
					{
						length += 1;
					}
					else
					{
						length += 2;
					}
					break;
			}
		}
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
	i += Char_ToUTF8((t_utf8*)result, unicode);									\



t_char*	String_Parse(t_char const* str, t_bool any_escape)
{
	t_char*	result;
	t_char	tmp[9] = { 0 };
	t_utf32	unicode;
	t_size	index = 0;
	t_size	i = 0;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	if (!(result = (t_char*)Memory_Alloc(String_Parse_GetLength(str, any_escape) + 1)))
		return (NULL);
	while (str[index])
	{
		if (str[index] == '\\') // escape sequence
		{
			++index;
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
				case '\'':	result[i++] = '\x27';	break; // Single quotation mark
				case '\"':	result[i++] = '\x22';	break; // Double quotation mark
				case  '?':	result[i++] = '\x3F';	break; // Question mark (used to avoid trigraphs)
				case '\\':	result[i++] = '\x5C';	break; // Backslash
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
		++index;
	}
	result[i] = '\0';
	return (result);
}
