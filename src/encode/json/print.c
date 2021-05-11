
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/math/math.h"
#include "libccc/encode/json.h"



typedef struct json_print
{
	t_utf8*	buffer;
	t_size	length;
	t_size	offset;
	t_size	depth;	// current nesting depth (for formatted printing)
	t_bool	noalloc;
	t_bool	format;	// is this print a formatted print
}			s_json_print;



// get a pointer to the buffer at the position
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)



static t_bool	JSON_Print_String(s_json const* item, s_json_print* p);
static t_bool	JSON_Print_Number(s_json const* item, s_json_print* p);
static t_bool	JSON_Print_Object(s_json const* item, s_json_print* p);
static t_bool	JSON_Print_Array (s_json const* item, s_json_print* p);
static t_bool	JSON_Print_Value (s_json const* item, s_json_print* p);



// realloc s_json_print if necessary to have at least "needed" bytes more
static
t_utf8*	ensure(s_json_print* p, t_size needed)
{
	t_utf8* newbuffer = NULL;
	t_size newsize = 0;

	if ((p == NULL) || (p->buffer == NULL))
		return (NULL);
	if ((p->length > 0) && (p->offset >= p->length))
	{
		// make sure that offset is valid
		return (NULL);
	}
	if (needed > SIZE_MAX)
	{
		// sizes bigger than SIZE_MAX are currently not supported
		return (NULL);
	}
	needed += p->offset + 1;
	if (needed <= p->length)
		return (p->buffer + p->offset);
	if (p->noalloc)
		return (NULL);
	// calculate new buffer size
	if (needed > (SIZE_MAX / 2))
	{
		// overflow of t_sint, use SIZE_MAX if possible
		if (needed <= SIZE_MAX)
		{
			newsize = SIZE_MAX;
		}
		else
			return (NULL);
	}
	else
	{
		newsize = needed * 2;
	}

#ifdef Memory_Realloc // TODO make this ifdef check more robust ?
	// reallocate with realloc if available
	newbuffer = (t_utf8*)Memory_Realloc(p->buffer, newsize);
	if (newbuffer == NULL)
	{
		Memory_Free(p->buffer);
		p->length = 0;
		p->buffer = NULL;
		return (NULL);
	}
#else
	// otherwise reallocate manually
	newbuffer = (t_utf8*)Memory_Alloc(newsize);
	if (!newbuffer)
	{
		Memory_Free(p->buffer);
		p->length = 0;
		p->buffer = NULL;
		return (NULL);
	}	
	Memory_Copy(newbuffer, p->buffer, p->offset + 1);
	Memory_Free(p->buffer);
#endif
	p->length = newsize;
	p->buffer = newbuffer;
	return (newbuffer + p->offset);
}



// Render the cstring provided to an escaped version that can be printed.
static
t_bool	JSON_Print_StringPtr(t_utf8 const* const input, s_json_print* p)
{
	t_utf8 const* input_pointer = NULL;
	t_utf8* output = NULL;
	t_utf8* result = NULL;
	t_size output_length = 0;
	t_size escape_characters = 0; //!< amount of additional characters needed for escaping

	if (p == NULL)
		return (FALSE);

	// empty string
	if (input == NULL)
	{
		output = ensure(p, sizeof("\"\""));
		if (output == NULL)
			return (FALSE);
		String_Copy(output, "\"\"");
		return (TRUE);
	}

	// set "flag" to 1 if something needs to be escaped
	input_pointer = input;
	while (*input_pointer != '\0')
	{
		switch (*input_pointer)
		{
			case '\"':
			case '\\':
			case '\b':
			case '\f':
			case '\n':
			case '\r':
			case '\t':
				// one character escape sequence
				escape_characters++;
				break;
			default:
				if (!UTF32_IsPrintable(UTF32_FromUTF8((t_utf8*)input_pointer)))
				{
					// UTF-16 escape sequence uXXXX
					escape_characters += 5;
				}
				break;
		}
		input_pointer++;
	}
	output_length = (t_size)(input_pointer - input) + escape_characters;

	output = ensure(p, output_length + sizeof("\"\""));
	if (output == NULL)
		return (FALSE);

	// no characters have to be escaped
	if (escape_characters == 0)
	{
		output[0] = '\"';
		Memory_Copy(output + 1, input, output_length);
		output[output_length + 1] = '\"';
		output[output_length + 2] = '\0';
		return (TRUE);
	}
	output[0] = '\"';
	result = output + 1;
	// copy the string
	input_pointer = input;
	while (*input_pointer != '\0')
	{
		t_utf32 c = UTF32_FromUTF8((t_utf8*)input_pointer);
		t_size len;
			 if (c < UTF8_1BYTE)	len = 1;
		else if (c < UTF8_2BYTE)	len = 2;
		else if (c < UTF8_3BYTE)	len = 3;
		else if (c <= UTF8_4BYTE)	len = 4;
		if (UTF32_IsPrintable(c) &&
			(c != '\"') &&
			(c != '\\'))
		{	// normal character, copy
			*result++ = *input_pointer;
			while (--len && *input_pointer != '\0')
			{
				input_pointer++;
				*result++ = *input_pointer;
			}
		}
		else
		{	// character needs to be escaped
			*result++ = '\\';
			switch (c)
			{
				case '\\':	*result++ = '\\';	break;
				case '\"':	*result++ = '\"';	break;
				case '\b':	*result++ = 'b';	break;
				case '\f':	*result++ = 'f';	break;
				case '\n':	*result++ = 'n';	break;
				case '\r':	*result++ = 'r';	break;
				case '\t':	*result++ = 't';	break;
				default: // escape and print as unicode codepoint
				{
					t_utf16 u[2] = {0};
					len = UTF32_ToUTF16(u, c);
					if (len > 0)
					{
						String_Format_N(result, 6, "u%4.4X", u[0]);
						result += 5;
						if (u[1])
						{
							*result++ = '\\';
							String_Format_N(result, 6, "u%4.4X", u[1]);
							result += 5;
						}
					}
					break;
				}
			}
		}
		input_pointer++;
	}
	*result++ = '\"';
	*result++ = '\0';
	return (TRUE);
}

// Invoke JSON_Print_StringPtr (which is useful) on an item.
static
t_bool	JSON_Print_String(s_json const* item, s_json_print* p)
{
	return (JSON_Print_StringPtr((t_utf8*)item->value.string, p));
}

// calculate the new length of the string in a s_json_print and update the offset
static
void	JSON_Print_UpdateOffset(s_json_print* const buffer)
{
	t_utf8 const* buffer_pointer = NULL;
	if ((buffer == NULL) || (buffer->buffer == NULL))
		return;
	buffer_pointer = buffer->buffer + buffer->offset;
	buffer->offset += String_Length(buffer_pointer);
}

// Render the number nicely from the given item into a string.
#define JSON_NUMBER_BUFFERSIZE	26
static
t_bool	JSON_Print_Number(s_json const* item, s_json_print* p)
{
	t_utf8*	result = NULL;
	t_sint	length = 0;
	t_f64	d = item->value.number;
	t_size	i = 0;
	t_f64	test = 0.0;
	t_utf8	number_buffer[JSON_NUMBER_BUFFERSIZE] = {0}; // temporary buffer to print the number into

	if (p == NULL)
		return (FALSE);
	// This checks for NaN and Infinity
	if (IS_NAN(d))
	{
		length = String_Format_N(number_buffer, JSON_NUMBER_BUFFERSIZE, "nan");
	}
	else if (IS_INF(d))
	{
		if (d > 0)	length = String_Format_N(number_buffer, JSON_NUMBER_BUFFERSIZE, "+inf");
		if (d < 0)	length = String_Format_N(number_buffer, JSON_NUMBER_BUFFERSIZE, "-inf");
	}
	else
	{
		// Try 15 decimal places of precision to avoid nonsignificant nonzero digits
		length = String_Format_N(number_buffer, JSON_NUMBER_BUFFERSIZE, "%1.15g", d);
		// Check whether the original t_f64 can be recovered
		test = F64_FromString(number_buffer);
		if (!F64_Equals(test, d))
		{
			// If not, print with 17 decimal places of precision
			length = String_Format_N(number_buffer, JSON_NUMBER_BUFFERSIZE, "%1.17g", d);
		}
	}
	// sprintf failed or buffer overrun occurred
	if ((length < 0) || (length > (t_sint)(sizeof(number_buffer) - 1)))
		return (FALSE);
	// reserve appropriate space in the output
	result = ensure(p, (t_size)length + sizeof(""));
	if (result == NULL)
		return (FALSE);
	// copy the printed number to the output and replace locale dependent decimal point with '.'
	for (i = 0; i < ((t_size)length); i++)
	{
		if (number_buffer[i] == '.')
		{
			result[i] = '.';
			continue;
		}
		result[i] = number_buffer[i];
	}
	result[i] = '\0';
	p->offset += (t_size)length;
	return (TRUE);
}



// Render an array to text
static
t_bool	JSON_Print_Array(s_json const* item, s_json_print* p)
{
	t_utf8*	result = NULL;
	s_json*	current_item = item->value.child;
	t_size	length = 0;
	t_bool	multiline = p->format;

	if (p == NULL)
		return (FALSE);
	// Compose the output array.
	if (!(current_item && (current_item->next || current_item->prev != current_item)))
		multiline = FALSE;
	if (multiline &&
		p->buffer[p->offset - 1] == ' ' &&
		p->buffer[p->offset - 2] == ':')
	{
		result = ensure(p, p->depth + 1);
		if (result == NULL)
			return (FALSE);
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; i++)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}
	// opening square bracket
	length = 1;//(t_size)(1 + (p->format && !multiline ? 1 : 0));
	result = ensure(p, length);
	if (result == NULL)
		return (FALSE);
	*result++ = '[';
//	if (p->format && !multiline)
//		*result++ = ' ';
	p->offset += length;
	p->depth++;
	while (current_item != NULL)
	{
		if (multiline)
		{
			result = ensure(p, p->depth + 1);
			if (result == NULL)
				return (FALSE);
			*result++ = '\n';
			for (t_size i = 0; i < p->depth; i++)
			{
				*result++ = '\t';
			}
			p->offset += p->depth + 1;
		}
		if (!JSON_Print_Value(current_item, p))
			return (FALSE);
		JSON_Print_UpdateOffset(p);
		length = (t_size)(current_item->next ? 1 : 0);
		result = ensure(p, length + 1);
		if (result == NULL)
			return (FALSE);
		if (current_item->next)
		{
			*result++ = ',';
		}
		*result = '\0';
		p->offset += length;
		current_item = current_item->next;
	}

	p->depth--;
	if (multiline)
	{
		result = ensure(p, p->depth + 1);
		if (result == NULL)
			return (FALSE);
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}
	length = 2;//(t_size)(2 + (p->format && !multiline ? 1 : 0));
	result = ensure(p, length);
	if (result == NULL)
		return (FALSE);
//	if (p->format && !multiline)
//		*result++ = ' ';
	*result++ = ']';
	*result = '\0';
	return (TRUE);
}



// Render an object to text.
static
t_bool	JSON_Print_Object(s_json const* item, s_json_print* p)
{
	t_utf8*	result = NULL;
	s_json*	current_item = item->value.child;
	t_size	length = 0;
	t_bool	multiline = p->format;

	if (p == NULL)
		return (FALSE);

	// Compose the output:
	if (!(current_item && (current_item->next || current_item->prev != current_item)))
		multiline = FALSE;
	if (multiline &&
		p->buffer[p->offset - 1] == ' ' &&
		p->buffer[p->offset - 2] == ':')
	{
		result = ensure(p, p->depth + 1);
		if (result == NULL)
			return (FALSE);
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; i++)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}
	// opening curly brace
	length = 1;//(t_size)(1 + (p->format && !multiline ? 1 : 0));
	result = ensure(p, length);
	if (result == NULL)
		return (FALSE);
	*result++ = '{';
//	if (p->format && !multiline)
//		*result++ = ' ';
	p->offset += length;
	p->depth++;
	while (current_item)
	{
		if (multiline)
		{
			result = ensure(p, p->depth + 1);
			if (result == NULL)
				return (FALSE);
			*result++ = '\n';
			for (t_size i = 0; i < p->depth; i++)
			{
				*result++ = '\t';
			}
			p->offset += p->depth + 1;
		}
		// print key
		if (!JSON_Print_StringPtr(current_item->key, p))
			return (FALSE);
		JSON_Print_UpdateOffset(p);

		length = (t_size)(p->format ? 2 : 1);
		result = ensure(p, length);
		if (result == NULL)
			return (FALSE);
		*result++ = ':';
		if (p->format)
		{
			*result++ = ' ';
		}
		p->offset += length;

		// print value
		if (!JSON_Print_Value(current_item, p))
			return (FALSE);
		JSON_Print_UpdateOffset(p);

		// print comma if not last
		length = (t_size)(current_item->next ? 1 : 0);
		result = ensure(p, length + 1);
		if (result == NULL)
			return (FALSE);
		if (current_item->next)
		{
			*result++ = ',';
		}
		*result = '\0';
		p->offset += length;
		current_item = current_item->next;
	}

	p->depth--;
	if (multiline)
	{
		result = ensure(p, p->depth + 1);
		if (result == NULL)
			return (FALSE);
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}
	length = 2;//(t_size)(2 + (p->format && !multiline ? 1 : 0));
	result = ensure(p, length);
	if (result == NULL)
		return (FALSE);
//	if (p->format && !multiline)
//		*result++ = ' ';
	*result++ = '}';
	*result = '\0';
	return (TRUE);
}



static
t_bool	JSON_Print_Value(s_json const* item, s_json_print* p)
{
	t_utf8* output = NULL;
	t_utf8 const* str;

	if ((item == NULL) || (p == NULL))
		return (FALSE);

	switch ((item->type) & DYNAMIC_TYPE_MASK)
	{
		case DYNAMIC_TYPE_NULL:
			str = "null";
			output = ensure(p, String_Length(str) + 1);
			if (output == NULL)
				return (FALSE);
			String_Copy(output, str);
			return (TRUE);

		case DYNAMIC_TYPE_BOOLEAN:
			str = (item->value.boolean ? "true" : "false");
			output = ensure(p, String_Length(str) + 1);
			if (output == NULL)
				return (FALSE);
			String_Copy(output, str);
			return (TRUE);

		case DYNAMIC_TYPE_INTEGER:
			return (JSON_Print_Number(item, p)); // TODO handle intege/float separately ?

		case DYNAMIC_TYPE_FLOAT:
			return (JSON_Print_Number(item, p)); // TODO handle intege/float separately ?

		case DYNAMIC_TYPE_RAW:
		{
			t_size raw_length = 0;
			if (item->value.string == NULL)
				return (FALSE);

			raw_length = String_Length(item->value.string) + sizeof("");
			output = ensure(p, raw_length);
			if (output == NULL)
				return (FALSE);
			Memory_Copy(output, item->value.string, raw_length);
			return (TRUE);
		}

		case DYNAMIC_TYPE_STRING:
			return (JSON_Print_String(item, p));

		case DYNAMIC_TYPE_ARRAY:
			return (JSON_Print_Array(item, p));

		case DYNAMIC_TYPE_OBJECT:
			return (JSON_Print_Object(item, p));

		default:
			return (FALSE);
	}
}



static
t_utf8*	JSON_Print_(s_json const* item, t_bool format)
{
	static const t_size default_buffer_size = 256;
	s_json_print buffer[1];
	t_utf8* printed = NULL;

	Memory_Set(buffer, 0, sizeof(buffer));
	// create buffer
	buffer->buffer = (t_utf8*)Memory_Alloc(default_buffer_size);
	buffer->length = default_buffer_size;
	buffer->format = format;
	if (buffer->buffer == NULL)
	{
		goto failure;
	}
	// print the value
	if (!JSON_Print_Value(item, buffer))
	{
		goto failure;
	}
	JSON_Print_UpdateOffset(buffer);

#ifdef Memory_Realloc // check if reallocate is available
		printed = (t_utf8*)Memory_Realloc(buffer->buffer, buffer->offset + 1);
		if (printed == NULL)
		{
			goto failure;
		}
		buffer->buffer = NULL;
#else // otherwise copy the JSON over to a new buffer
		printed = (t_utf8*) Memory_Alloc(buffer->offset + 1);
		if (printed == NULL)
		{
			goto failure;
		}
		Memory_Copy(printed, buffer->buffer, MIN(buffer->length, buffer->offset + 1));
		printed[buffer->offset] = '\0'; // just to be sure

		// free the buffer
		Memory_Free(buffer->buffer);
#endif
	return (printed);

failure:
	if (buffer->buffer != NULL)
	{
		Memory_Free(buffer->buffer);
	}

	if (printed != NULL)
	{
		Memory_Free(printed);
	}
	return (NULL);
}



t_utf8*	JSON_Print_Pretty(s_json const* item)
{
	return (JSON_Print_(item, TRUE));
}

t_utf8*	JSON_Print_Minify(s_json const* item)
{
	return (JSON_Print_(item, FALSE));
}

t_utf8*	JSON_Print_Buffered(s_json const* item, t_sint prebuffer, t_bool fmt)
{
	s_json_print p = { 0 };

	if (prebuffer < 0)
		return (NULL);
	p.buffer = (t_utf8*)Memory_Alloc((t_size)prebuffer);
	if (!p.buffer)
		return (NULL);
	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = fmt;
	if (!JSON_Print_Value(item, &p))
	{
		Memory_Free(p.buffer);
		return (NULL);
	}
	return ((t_utf8*)p.buffer);
}

t_bool	JSON_Print_Preallocated(s_json* item, t_utf8* buffer, const t_sint length, const t_bool format)
{
	s_json_print p = { 0 };

	if ((length < 0) || (buffer == NULL))
		return (FALSE);

	p.buffer = (t_utf8*)buffer;
	p.length = (t_size)length;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = format;
	return (JSON_Print_Value(item, &p));
}
