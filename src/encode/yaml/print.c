
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/encode/yaml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_print	s_yaml_print;

#define ENSURE(NEEDED) \
{ \
	result = KVT_Print_EnsureBuffer(p, (NEEDED)); \
	if (result == NULL) \
		return (ERROR); \
} \

#define YAML_Print_UpdateOffset \
		KVT_Print_UpdateOffset

#define YAML_NUMBER_BUFFERSIZE \
		KVT_NUMBER_BUFFERSIZE



static t_bool	YAML_Print_Number	(s_yaml const* item, s_yaml_print* p, t_bool bigint);
static t_bool	YAML_Print_String	(s_yaml const* item, s_yaml_print* p);
static t_bool	YAML_Print_Key		(s_yaml const* item, s_yaml_print* p);
static t_bool	YAML_Print_Value	(s_yaml const* item, s_yaml_print* p);
static t_bool	YAML_Print_Block	(s_yaml const* item, s_yaml_print* p, t_bool inline_first);
static t_bool	YAML_Print_Mapping	(s_yaml const* item, s_yaml_print* p, t_bool inline_first);
static t_bool	YAML_Print_Sequence	(s_yaml const* item, s_yaml_print* p, t_bool inline_first);
static t_bool	YAML_Print_FlowValue(s_yaml const* item, s_yaml_print* p);



//! Prints the indentation (space chars) for the current nesting depth
static
t_bool	YAML_Print_Indent(s_yaml_print* p)
{
	t_utf8*	result = NULL;
	t_size	length = p->depth * YAML_PRINTSTYLE_INDENT;

	if (length == 0)
		return (OK);
	ENSURE(length)
	for (t_size i = 0; i < length; ++i)
	{
		*result++ = ' ';
	}
	p->offset += length;
	return (OK);
}

//! Checks whether the given item is a collection (array/object) which holds at least one item
static
t_bool	YAML_Print_IsNonEmptyCollection(s_yaml const* item)
{
	if (item == NULL)
		return (FALSE);
	if ((item->type & DYNAMICTYPE_MASK) != DYNAMICTYPE_ARRAY &&
		(item->type & DYNAMICTYPE_MASK) != DYNAMICTYPE_OBJECT)
		return (FALSE);
	return (item->value.child != NULL);
}



/*============================================================================*\
||                              Scalar printing                               ||
\*============================================================================*/

//! Checks whether the given string can be printed as a plain (unquoted) YAML scalar
/*!
**	A string needs to be quoted if printing it as a plain scalar would be
**	ambiguous (i.e. it could be parsed back as some other scalar type),
**	or if it contains any chars which are not allowed in plain scalars.
*/
static
t_bool	YAML_Print_IsStringComplex(t_utf8 const* str)
{
	t_size	i;

	if (str == NULL || str[0] == '\0')
		return (TRUE); // the empty string must be quoted (as it would otherwise be parsed as `null`)
	// plain scalars cannot begin with (or sometimes contain) YAML indicator chars
	if (Char_IsInCharset(str[0], "-?:,[]{}#&*!|>'\"%@` \t"))
		return (TRUE);
	for (i = 0; str[i]; ++i)
	{
		if (str[i] == '\n' || str[i] == '\r')
			return (TRUE); // multi-line strings must be quoted (or use block scalar notation)
		if (str[i] == ':' && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
			return (TRUE); // would be parsed as a `key: value` mapping
		if (str[i] == '#' && i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
			return (TRUE); // would be parsed as a comment
		if (str[i] == ',' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}')
			return (TRUE); // would break flow-style collections (always quote these, to be safe)
		if (!Char_IsPrintable(str[i]) && !(str[i] & 0x80))
			return (TRUE); // control chars must be escaped, within a double-quoted string
	}
	if (str[i - 1] == ' ' || str[i - 1] == '\t')
		return (TRUE); // trailing whitespace would be trimmed by the parser
	// check whether the string would be parsed back as some other scalar type
	if (String_Equals(str, "~") ||
		String_Equals_IgnoreCase(str, "null") ||
		String_Equals_IgnoreCase(str, "true") ||
		String_Equals_IgnoreCase(str, "false") ||
		String_Equals_IgnoreCase(str, "yes") ||
		String_Equals_IgnoreCase(str, "no") ||
		String_Equals_IgnoreCase(str, "on") ||
		String_Equals_IgnoreCase(str, "off") ||
		String_Equals_IgnoreCase(str, ".inf") ||
		String_Equals_IgnoreCase(str, "-.inf") ||
		String_Equals_IgnoreCase(str, "+.inf") ||
		String_Equals_IgnoreCase(str, ".nan"))
		return (TRUE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	if (Char_IsDigit(str[i]) || (str[i] == '.' && Char_IsDigit(str[i + 1])))
		return (TRUE); // could be parsed as a number (always quote these, to be safe)
	return (FALSE);
}

// Render the cstring provided to an escaped, double-quoted version that can be printed.
static
t_bool	YAML_Print_StringPtr(t_utf8 const* input, s_yaml_print* p)
{
	t_utf8 const* input_ptr = NULL;
	t_utf8*	result = NULL;
	t_utf8*	str;
	t_size	result_length = 0;
	t_size	escape_chars = 0; //!< amount of additional characters needed for escaping

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	// empty string
	if (input == NULL || input[0] == '\0')
	{
		ENSURE(sizeof("\"\""))
		String_Copy(result, "\"\"");
		p->offset += STRING_LENGTH("\"\"");
		return (OK);
	}
	// count how many additional chars are needed for escaping
	input_ptr = input;
	while (*input_ptr != '\0')
	{
		t_utf32 c = CharUTF32_FromUTF8((t_utf8*)input_ptr);
		t_size length = 1;
			 if (c < UTF8_1BYTE)	length = 1;
		else if (c < UTF8_2BYTE)	length = 2;
		else if (c < UTF8_3BYTE)	length = 3;
		else if (c < UTF8_4BYTE)	length = 4;
		switch (*input_ptr)
		{
			case '\"':
			case '\\':
			case '\b':
			case '\f':
			case '\n':
			case '\r':
			case '\t':
			{	// one character escape sequence
				escape_chars++;
				break;
			}
			default:
			{
				if (!CharUTF32_IsPrintable(c))
				{
					escape_chars += 5;	// UTF-32 escape sequence \uXXXX
					if (c >= UTF8_3BYTE)
						escape_chars += 4;	// UTF-32 escape sequence \UXXXX
				}
				break;
			}
		}
		input_ptr += length;
	}
	result_length = (t_size)(input_ptr - input) + escape_chars;

	ENSURE(result_length + sizeof("\"\""))

	// no characters have to be escaped
	if (escape_chars == 0)
	{
		result[0] = '\"';
		Memory_Copy(result + 1, input, result_length);
		result[result_length + 1] = '\"';
		result[result_length + 2] = '\0';
		p->offset += result_length + STRING_LENGTH("\"\"");
		return (OK);
	}
	result[0] = '\"';
	str = result + 1;
	// copy the string
	input_ptr = input;
	while (*input_ptr != '\0')
	{
		t_utf32 c = CharUTF32_FromUTF8((t_utf8*)input_ptr);
		t_size length = 1;
			 if (c < UTF8_1BYTE)	length = 1;
		else if (c < UTF8_2BYTE)	length = 2;
		else if (c < UTF8_3BYTE)	length = 3;
		else if (c < UTF8_4BYTE)	length = 4;
		if (CharUTF32_IsPrintable(c) &&
			(c != '\"') &&
			(c != '\\'))
		{	// normal character, copy
			*str++ = *input_ptr;
			while (--length && *input_ptr != '\0')
			{
				input_ptr++;
				*str++ = *input_ptr;
			}
		}
		else // character needs to be escaped
		{
			*str++ = '\\';
			switch (c)
			{
				case '\b':	*str++ = 'b';	break;
				case '\t':	*str++ = 't';	break;
				case '\n':	*str++ = 'n';	break;
				case '\f':	*str++ = 'f';	break;
				case '\r':	*str++ = 'r';	break;
				case '\"':	*str++ = '\"';	break;
				case '\\':	*str++ = '\\';	break;
				default: // escape and print as unicode codepoint
				{
					t_utf16 u[2] = {0};
					length = CharUTF32_ToUTF16(u, c);
					if (length > 0)
					{
						String_Format_N(str, 6, "u%4.4X", u[0]);
						str += 5;
						if (u[1])
						{
							*str++ = '\\';
							String_Format_N(str, 6, "u%4.4X", u[1]);
							str += 5;
						}
					}
					break;
				}
			}
		}
		input_ptr++;
	}
	*str++ = '\"';
	*str = '\0';
	p->offset += (t_size)(str - result);
	return (OK);
}

// Invoke YAML_Print_StringPtr (which is useful) on an item.
static
t_bool	YAML_Print_String(s_yaml const* item, s_yaml_print* p)
{
	t_utf8*	result = NULL;
	t_size	length;

	if (item->value.string != NULL &&
		!YAML_Print_IsStringComplex(item->value.string))
	{	// print as plain (unquoted) scalar
		length = String_Length(item->value.string);
		ENSURE(length + sizeof(""))
		Memory_Copy(result, item->value.string, length);
		result[length] = '\0';
		p->offset += length;
		return (OK);
	}
	return (YAML_Print_StringPtr((t_utf8*)item->value.string, p));
}

// Render the number nicely from the given item into a string.
static
t_bool	YAML_Print_Number(s_yaml const* item, s_yaml_print* p, t_bool bigint)
{
	t_utf8*	result = NULL;
	t_size	length = 0;
	t_size	i = 0;
	t_f64	test = 0.0;
	t_utf8	number_buffer[YAML_NUMBER_BUFFERSIZE] = {0}; // temporary buffer to print the number into

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (bigint) // TODO handle variable-length integers
	{
		t_s64	d = item->value.integer;
		length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, SF_S64, d);
	}
	else
	{
		t_f64	d = item->value.number;
		if (F64_IsNaN(d))
		{
			length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, ".nan");
		}
		else if (F64_IsInf(d))
		{
			if (d > 0)	length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, ".inf");
			if (d < 0)	length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, "-.inf");
		}
		else
		{
			// Try 15 decimal places of precision to avoid nonsignificant nonzero digits
			length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, "%#1.1f", d);
			// Check whether the original t_f64 can be recovered
			test = F64_FromString(number_buffer);
			if (test != d)
			{	// If not, print with 17 decimal places of precision
				length = String_Format_N(number_buffer, YAML_NUMBER_BUFFERSIZE, "%1.17g", d);
			}
		}
	}
	if CCCERROR((length == 0), ERROR_PRINT, 
		"could not print number value for item with key \"%s\"", item->key)
		return (ERROR);
	if CCCERROR((length > (sizeof(number_buffer) - 1)), ERROR_PRINT,
		"could not print number value for item with key \"%s\": buffer overrun occurred", item->key)
		return (ERROR);
	// reserve appropriate space in the output
	ENSURE(length + sizeof(""))
	// copy the printed number to the output
	for (i = 0; i < length; ++i)
	{
		result[i] = number_buffer[i];
	}
	p->offset += length;
	result[i] = '\0';
	return (OK);
}

//! Prints any scalar (non-collection) item value
static
t_bool	YAML_Print_Value(s_yaml const* item, s_yaml_print* p)
{
	t_utf8*	result = NULL;
	t_utf8 const* str;
	t_size	length;

	switch ((item->type) & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_INTEGER: return (YAML_Print_Number(item, p, TRUE));
		case DYNAMICTYPE_FLOAT:   return (YAML_Print_Number(item, p, FALSE));
		case DYNAMICTYPE_STRING:  return (YAML_Print_String(item, p));
		case DYNAMICTYPE_NULL:
		{
			str = "null";
			length = String_Length(str);
			ENSURE(length + sizeof(""))
			String_Copy(result, str);
			p->offset += length;
			return (OK);
		}
		case DYNAMICTYPE_BOOLEAN:
		{
			str = (item->value.boolean ? "true" : "false");
			length = String_Length(str);
			ENSURE(length + sizeof(""))
			String_Copy(result, str);
			p->offset += length;
			return (OK);
		}
		case DYNAMICTYPE_RAW:
		{
			if CCCERROR((item->value.string == NULL), ERROR_PRINT, 
				"item with key \"%s\" is of 'raw string' type, but its value is null", item->key)
				return (ERROR);
			length = String_Length(item->value.string);
			ENSURE(length + sizeof(""))
			Memory_Copy(result, item->value.string, length + sizeof(""));
			p->offset += length;
			return (OK);
		}
		case DYNAMICTYPE_ARRAY: // empty collections are printed in flow-style
		case DYNAMICTYPE_OBJECT:
		{
			return (YAML_Print_FlowValue(item, p));
		}
	}
	CCCERROR(TRUE, ERROR_PRINT, 
		"cannot print item with key \"%s\", has invalid type (%i)", item->key, item->type);
	return (ERROR);
}

//! Prints a mapping key (as a plain scalar if possible, or double-quoted otherwise)
static
t_bool	YAML_Print_Key(s_yaml const* item, s_yaml_print* p)
{
	t_utf8*	result = NULL;
	t_size	length;

	if (item->key != NULL &&
		!YAML_Print_IsStringComplex(item->key) &&
		!String_Has(item->key, ":"))
	{	// print as plain (unquoted) key
		length = String_Length(item->key);
		ENSURE(length + sizeof(""))
		Memory_Copy(result, item->key, length);
		result[length] = '\0';
		p->offset += length;
		return (OK);
	}
	return (YAML_Print_StringPtr((t_utf8*)item->key, p));
}



/*============================================================================*\
||                       Flow-style printing (minified)                       ||
\*============================================================================*/

static
t_bool	YAML_Print_FlowValue(s_yaml const* item, s_yaml_print* p)
{
	t_utf8*	result = NULL;
	s_yaml*	current_item;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	switch ((item->type) & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_ARRAY:
		{
			ENSURE(1)
			*result = '[';
			p->offset++;
			current_item = item->value.child;
			while (current_item)
			{
				if (YAML_Print_FlowValue(current_item, p))
					return (ERROR);
				if (current_item->next)
				{
					ENSURE(p->format ? 2 : 1)
					result[0] = ',';
					p->offset++;
					if (p->format)
					{
						result[1] = ' ';
						p->offset++;
					}
				}
				current_item = current_item->next;
			}
			ENSURE(2)
			*result++ = ']';
			p->offset++;
			*result = '\0';
			return (OK);
		}
		case DYNAMICTYPE_OBJECT:
		{
			ENSURE(1)
			*result = '{';
			p->offset++;
			current_item = item->value.child;
			while (current_item)
			{
				if (YAML_Print_Key(current_item, p))
					return (ERROR);
				// NOTE: in YAML, a space char is required after the ':' key/value separator
				ENSURE(2)
				result[0] = ':';
				result[1] = ' ';
				p->offset += 2;
				if (YAML_Print_FlowValue(current_item, p))
					return (ERROR);
				if (current_item->next)
				{
					ENSURE(p->format ? 2 : 1)
					result[0] = ',';
					p->offset++;
					if (p->format)
					{
						result[1] = ' ';
						p->offset++;
					}
				}
				current_item = current_item->next;
			}
			ENSURE(2)
			*result++ = '}';
			p->offset++;
			*result = '\0';
			return (OK);
		}
		default:
		{
			return (YAML_Print_Value(item, p));
		}
	}
}



/*============================================================================*\
||                      Block-style printing (formatted)                      ||
\*============================================================================*/

static
t_bool	YAML_Print_Mapping(s_yaml const* item, s_yaml_print* p, t_bool inline_first)
{
	t_utf8*	result = NULL;
	s_yaml*	current_item = item->value.child;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	while (current_item)
	{
		if (inline_first)
			inline_first = FALSE; // the first key/value pair is printed in-line (after a `- ` sequence item indicator)
		else if (YAML_Print_Indent(p))
			return (ERROR);
		// print the key, and the ':' separator char
		if (YAML_Print_Key(current_item, p))
			return (ERROR);
		ENSURE(1)
		*result = ':';
		p->offset++;
		// print the value
		if (YAML_Print_IsNonEmptyCollection(current_item))
		{	// the value is a nested block, on the following lines
			ENSURE(1)
			*result = '\n';
			p->offset++;
			p->depth++;
			if (YAML_Print_Block(current_item, p, FALSE))
				return (ERROR);
			p->depth--;
		}
		else
		{	// the value is printed in-line, on the same line as the key
			ENSURE(1)
			*result = ' ';
			p->offset++;
			if (YAML_Print_Value(current_item, p))
				return (ERROR);
			ENSURE(2)
			*result++ = '\n';
			p->offset++;
			*result = '\0';
		}
		current_item = current_item->next;
	}
	return (OK);
}

static
t_bool	YAML_Print_Sequence(s_yaml const* item, s_yaml_print* p, t_bool inline_first)
{
	t_utf8*	result = NULL;
	s_yaml*	current_item = item->value.child;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	while (current_item)
	{
		if (inline_first)
			inline_first = FALSE; // the first item is printed in-line (after a parent `- ` sequence item indicator)
		else if (YAML_Print_Indent(p))
			return (ERROR);
		// print the '-' item indicator char
		ENSURE(2)
		*result++ = '-';
		*result = ' ';
		p->offset += 2;
		if (YAML_Print_IsNonEmptyCollection(current_item))
		{	// nested collection: printed compactly, starting on the same line as the '-' indicator
			p->depth++;
			if (YAML_Print_Block(current_item, p, TRUE))
				return (ERROR);
			p->depth--;
		}
		else
		{
			if (YAML_Print_Value(current_item, p))
				return (ERROR);
			ENSURE(2)
			*result++ = '\n';
			p->offset++;
			*result = '\0';
		}
		current_item = current_item->next;
	}
	return (OK);
}

//! Prints any block-context node (dispatches to mapping/sequence/scalar printing accordingly)
/*!
**	If `inline_first` is `TRUE`, the first line of this block is printed at the current
**	offset (used for compact sequence item notation), rather than after fresh indentation.
*/
static
t_bool	YAML_Print_Block(s_yaml const* item, s_yaml_print* p, t_bool inline_first)
{
	t_utf8*	result = NULL;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	switch ((item->type) & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_OBJECT:
		{
			if (item->value.child == NULL)
				break;
			return (YAML_Print_Mapping(item, p, inline_first));
		}
		case DYNAMICTYPE_ARRAY:
		{
			if (item->value.child == NULL)
				break;
			return (YAML_Print_Sequence(item, p, inline_first));
		}
		default: break;
	}
	// scalar value (or empty collection): printed on a single line
	if (!inline_first && YAML_Print_Indent(p))
		return (ERROR);
	if (YAML_Print_Value(item, p))
		return (ERROR);
	ENSURE(2)
	*result++ = '\n';
	p->offset++;
	*result = '\0';
	return (OK);
}



/*============================================================================*\
||                          Main printing entry points                        ||
\*============================================================================*/

static
t_bool	YAML_Print_Lines(s_yaml const* item, s_yaml_print* p)
{
	t_utf8*	result = NULL;

	if (p->format)
		return (YAML_Print_Block(item, p, FALSE));
	// minified: flow-style (JSON-like), single-line output
	if (YAML_Print_FlowValue(item, p))
		return (ERROR);
	ENSURE(1)
	*result = '\0';
	return (OK);
}



static
t_utf8*	YAML_Print_(s_yaml const* item, t_bool format)
{
	static const t_size default_buffer_size = 256;
	s_yaml_print p[1];
	t_utf8* printed = NULL;

	Memory_Clear(p, sizeof(p));
	// create buffer
	p->item = item;
	p->format = format;
	p->length = default_buffer_size;
	p->result = (t_utf8*)Memory_Allocate(default_buffer_size);
	if CCCERROR((p->result == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	// print the value
	if (YAML_Print_Lines(item, p))
		goto failure;

#ifdef Memory_Realloc // check if reallocate is available
	{
		printed = (t_utf8*)Memory_Reallocate(p->result, p->offset + 1);
		if CCCERROR((printed == NULL), ERROR_ALLOCFAILURE, NULL)
			goto failure;
		p->result = NULL;
	}
#else // otherwise copy the YAML over to a new buffer
	{
		printed = (t_utf8*)Memory_Allocate(p->offset + 1);
		if CCCERROR((printed == NULL), ERROR_ALLOCFAILURE, NULL)
			goto failure;
		Memory_Copy(printed, p->result, MIN(p->length, p->offset + 1));
		printed[p->offset] = '\0'; // just to be sure
		Memory_Free(p->result); // free the buffer
	}
#endif
	return (printed);

failure:
	if (p->result != NULL)
	{
		Memory_Free(p->result);
	}
	if (printed != NULL)
	{
		Memory_Free(printed);
	}
	return (NULL);
}



t_size	YAML_Print_Pretty(t_utf8* dest, s_yaml const* item, t_size n)
{
	s_yaml_print p;

	Memory_Clear(&p, sizeof(s_yaml_print));
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, "KVT given is NULL")
		return (SIZE_ERROR);
	if (n == 0)
		n = SIZE_MAX;
	p.item = item;
	p.result = dest;
	p.length = n;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = TRUE;
	YAML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}

t_size	YAML_Print_Minify(t_utf8* dest, s_yaml const* item, t_size n)
{
	s_yaml_print p;

	Memory_Clear(&p, sizeof(s_yaml_print));
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, "KVT given is NULL")
		return (SIZE_ERROR);
	if (n == 0)
		n = SIZE_MAX;
	p.item = item;
	p.result = dest;
	p.length = n;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = FALSE;
	YAML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}



t_utf8*	YAML_ToString_Pretty(s_yaml const* item)
{
	return (YAML_Print_(item, TRUE));
}

t_utf8*	YAML_ToString_Minify(s_yaml const* item)
{
	return (YAML_Print_(item, FALSE));
}



#if 0 // TODO
t_utf8*	YAML_Print_Buffered(s_yaml const* item, t_sint prebuffer, t_bool format)
{
	s_yaml_print p = { 0 };

	if CCCERROR((prebuffer < 0), ERROR_LENGTH2SMALL, NULL)
		return (NULL);
	p.result = (t_utf8*)Memory_Allocate((t_size)prebuffer);
	if CCCERROR((p.result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = format;
	if (YAML_Print_Lines(item, &p))
	{
		Memory_Free(p.result);
		return (NULL);
	}
	return ((t_utf8*)p.result);
}
#endif
