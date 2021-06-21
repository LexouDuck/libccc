
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_size	String_Print_GetLength(t_char const* str, t_char const* charset_extra)
{
	t_size	length = 0;
	t_size	i = 0;

	while (str[i])
	{
		switch (str[i])
		{
			case '\x07': length += 2; break; // Alert (Beep, Bell) (added in C89)[1]
			case '\x08': length += 2; break; // Backspace
			case '\x09': length += 2; break; // Horizontal Tab
			case '\x0A': length += 2; break; // Newline (Line Feed); see notes below
			case '\x0B': length += 2; break; // Vertical Tab
			case '\x0C': length += 2; break; // Formfeed
			case '\x0D': length += 2; break; // Carriage Return
			case '\x1B': length += 2; break; // Escape
			case '\x27': length += 2; break; // Single quotation mark
			case '\x22': length += 2; break; // Double quotation mark
			case '\x3F': length += 2; break; // Question mark (used to avoid trigraphs)
			case '\x5C': length += 2; break; // Backslash
			default:
				if (!Char_IsPrintable(str[i]) ||
					(String_IndexOf_Char(charset_extra, str[i]) >= 0))
				{	// TODO unicode \u???? UTF-16 and \U???????? UTF-32 ?
					length += 4;
				}
				else length += 1;
				break;
		}
		++i;
	}
	return (length);
}



t_size	String_Print(t_char* *dest, t_char const* str, t_size n, t_char const* charset_extra)
{
	t_u8	HI_nibble;
	t_u8	LO_nibble;
	t_char*	result;
	t_size	index = 0;
	t_size	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), PRINT_RETURN(NULL))
	if (n == 0)
		n = SIZE_MAX;
	result = (t_char*)Memory_Allocate(String_Print_GetLength(str, charset_extra) + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), PRINT_RETURN(NULL))
	while (index < n && str[index])
	{
		switch (str[index])
		{
			case '\x07': result[i++] = '\\';	result[i++] =  'a'; break; // Alert (Beep, Bell) (added in C89)[1]
			case '\x08': result[i++] = '\\';	result[i++] =  'b'; break; // Backspace
			case '\x09': result[i++] = '\\';	result[i++] =  't'; break; // Horizontal Tab
			case '\x0A': result[i++] = '\\';	result[i++] =  'n'; break; // Newline (Line Feed); see notes below
			case '\x0B': result[i++] = '\\';	result[i++] =  'v'; break; // Vertical Tab
			case '\x0C': result[i++] = '\\';	result[i++] =  'f'; break; // Formfeed
			case '\x0D': result[i++] = '\\';	result[i++] =  'r'; break; // Carriage Return
			case '\x1B': result[i++] = '\\';	result[i++] =  'e'; break; // Escape
			case '\x27': result[i++] = '\\';	result[i++] = '\''; break; // Single quotation mark
			case '\x22': result[i++] = '\\';	result[i++] = '\"'; break; // Double quotation mark
			case '\x3F': result[i++] = '\\';	result[i++] =  '?'; break; // Question mark (used to avoid trigraphs)
			case '\x5C': result[i++] = '\\';	result[i++] = '\\'; break; // Backslash
			default:
				if (!Char_IsPrintable(str[index]) ||
					(String_IndexOf_Char(charset_extra, str[index]) >= 0))
				{	// TODO unicode \u???? UTF-16 and \U???????? UTF-32 ?
					result[i++] = '\\';
					result[i++] = 'x'; // Hexadecimal t_char notation: \xFF
					HI_nibble = (str[index] & 0xF0) >> 4;
					LO_nibble = (str[index] & 0x0F);
					result[i++] = (HI_nibble < 10) ? (HI_nibble + '0') : (HI_nibble - 10 + 'A');
					result[i++] = (LO_nibble < 10) ? (LO_nibble + '0') : (LO_nibble - 10 + 'A');
				}
				else result[i++] = str[index];
				break;
		}
		++index;
	}
	result[i] = '\0';
	if (dest)	*dest = result;
	return (index);
}



inline
t_char*	String_ToEscape(t_char const* str, t_char const* charset_extra)
{
	t_char*	result = NULL;
	String_Print(&result, str, 0, charset_extra);
	return (result);
}
