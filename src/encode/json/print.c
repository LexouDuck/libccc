
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/math/math.h"
#include "libccc/encode/json.h"



typedef struct	json_print
{
	t_char*	buffer;
	t_size	length;
	t_size	offset;
	t_size	depth;	// current nesting depth (for formatted printing)
	t_bool	noalloc;
	t_bool	format;	// is this print a formatted print
}				s_json_print;



// get a pointer to the buffer at the position
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)



// realloc s_json_print if necessary to have at least "needed" bytes more
static t_char* ensure(s_json_print* const p, t_size needed)
{
	t_char* newbuffer = NULL;
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
	newbuffer = (t_char*)Memory_Realloc(p->buffer, newsize);
	if (newbuffer == NULL)
	{
		Memory_Free(p->buffer);
		p->length = 0;
		p->buffer = NULL;
		return (NULL);
	}
#else
	// otherwise reallocate manually
	newbuffer = (t_char*)Memory_Alloc(newsize);
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
static t_bool print_string_ptr(t_char const* const input, s_json_print* const output_buffer)
{
	t_char const* input_pointer = NULL;
	t_char* output = NULL;
	t_char* output_pointer = NULL;
	t_size output_length = 0;
	// numbers of additional characters needed for escaping
	t_size escape_characters = 0;

	if (output_buffer == NULL)
		return (FALSE);

	// empty string
	if (input == NULL)
	{
		output = ensure(output_buffer, sizeof("\"\""));
		if (output == NULL)
			return (FALSE);
		String_Copy((t_char*)output, "\"\"");
		return (TRUE);
	}

	// set "flag" to 1 if something needs to be escaped
	for (input_pointer = input; *input_pointer; input_pointer++)
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
				if (*input_pointer < 32)
				{
					// UTF-16 escape sequence uXXXX
					escape_characters += 5;
				}
				break;
		}
	}
	output_length = (t_size)(input_pointer - input) + escape_characters;

	output = ensure(output_buffer, output_length + sizeof("\"\""));
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
	output_pointer = output + 1;
	// copy the string
	for (input_pointer = input; *input_pointer != '\0'; (void)input_pointer++, output_pointer++)
	{
		if ((*input_pointer > 31) && (*input_pointer != '\"') && (*input_pointer != '\\'))
		{
			// normal character, copy
			*output_pointer = *input_pointer;
		}
		else
		{
			// character needs to be escaped
			*output_pointer++ = '\\';
			switch (*input_pointer)
			{
				case '\\':
					*output_pointer = '\\';
					break;
				case '\"':
					*output_pointer = '\"';
					break;
				case '\b':
					*output_pointer = 'b';
					break;
				case '\f':
					*output_pointer = 'f';
					break;
				case '\n':
					*output_pointer = 'n';
					break;
				case '\r':
					*output_pointer = 'r';
					break;
				case '\t':
					*output_pointer = 't';
					break;
				default: // escape and print as unicode codepoint
					String_Format_N((t_char*)output_pointer, 6, "u%04x", *input_pointer);
					output_pointer += 4;
					break;
			}
		}
	}
	output[output_length + 1] = '\"';
	output[output_length + 2] = '\0';
	return (TRUE);
}

// Invoke print_string_ptr (which is useful) on an item.
static t_bool print_string(s_json const* const item, s_json_print* const p)
{
	return (print_string_ptr((t_char*)item->value_string, p));
}

// calculate the new length of the string in a s_json_print and update the offset
static void update_offset(s_json_print* const buffer)
{
	t_char const* buffer_pointer = NULL;
	if ((buffer == NULL) || (buffer->buffer == NULL))
		return;
	buffer_pointer = buffer->buffer + buffer->offset;

	buffer->offset += String_Length((t_char const*)buffer_pointer);
}

// Render the number nicely from the given item into a string.
#define JSON_NUMBER_BUFFERSIZE	26
static t_bool print_number(s_json const* const item, s_json_print* const output_buffer)
{
	t_char*	output_pointer = NULL;
	t_sint	length = 0;
	t_f64	d = item->value_number;
	t_size	i = 0;
	t_f64	test = 0.0;
	t_char	number_buffer[JSON_NUMBER_BUFFERSIZE] = {0}; // temporary buffer to print the number into

	if (output_buffer == NULL)
		return (FALSE);
	// This checks for NaN and Infinity
	if (isnan(d) || isinf(d))
	{
		length = String_Format_N((t_char*)number_buffer, JSON_NUMBER_BUFFERSIZE, "null");
	}
	else
	{
		// Try 15 decimal places of precision to avoid nonsignificant nonzero digits
		length = String_Format_N((t_char*)number_buffer, JSON_NUMBER_BUFFERSIZE, "%1.15g", d);
		// Check whether the original t_f64 can be recovered
		test = F64_FromString((t_char*)number_buffer);
		if (!F64_Equals((t_f64)test, d))
		{
			// If not, print with 17 decimal places of precision
			length = String_Format_N((t_char*)number_buffer, JSON_NUMBER_BUFFERSIZE, "%1.17g", d);
		}
	}
	// sprintf failed or buffer overrun occurred
	if ((length < 0) || (length > (t_sint)(sizeof(number_buffer) - 1)))
		return (FALSE);
	// reserve appropriate space in the output
	output_pointer = ensure(output_buffer, (t_size)length + sizeof(""));
	if (output_pointer == NULL)
		return (FALSE);
	// copy the printed number to the output and replace locale dependent decimal point with '.'
	for (i = 0; i < ((t_size)length); i++)
	{
		if (number_buffer[i] == '.')
		{
			output_pointer[i] = '.';
			continue;
		}
		output_pointer[i] = number_buffer[i];
	}
	output_pointer[i] = '\0';
	output_buffer->offset += (t_size)length;
	return (TRUE);
}



static t_bool print_array(s_json const* const item, s_json_print* const output_buffer);
static t_bool print_object(s_json const* const item, s_json_print* const output_buffer);



static t_bool print_value(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output = NULL;

	if ((item == NULL) || (output_buffer == NULL))
		return (FALSE);

	switch ((item->type) & JSON_TYPE_MASK)
	{
		case JSON_TYPE_NULL:
			output = ensure(output_buffer, 5);
			if (output == NULL)
				return (FALSE);
			String_Copy((t_char*)output, "null");
			return (TRUE);

		case JSON_TYPE_FALSE:
			output = ensure(output_buffer, 6);
			if (output == NULL)
				return (FALSE);
			String_Copy((t_char*)output, "FALSE");
			return (TRUE);

		case JSON_TYPE_TRUE:
			output = ensure(output_buffer, 5);
			if (output == NULL)
				return (FALSE);
			String_Copy((t_char*)output, "TRUE");
			return (TRUE);

		case JSON_TYPE_NUMBER:
			return (print_number(item, output_buffer));

		case JSON_TYPE_RAW:
		{
			t_size raw_length = 0;
			if (item->value_string == NULL)
				return (FALSE);

			raw_length = String_Length(item->value_string) + sizeof("");
			output = ensure(output_buffer, raw_length);
			if (output == NULL)
				return (FALSE);
			Memory_Copy(output, item->value_string, raw_length);
			return (TRUE);
		}

		case JSON_TYPE_STRING:
			return (print_string(item, output_buffer));

		case JSON_TYPE_ARRAY:
			return (print_array(item, output_buffer));

		case JSON_TYPE_OBJECT:
			return (print_object(item, output_buffer));

		default:
			return (FALSE);
	}
}

// Render an array to text
static t_bool print_array(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output_pointer = NULL;
	t_size length = 0;
	s_json* current_element = item->child;

	if (output_buffer == NULL)
		return (FALSE);

	// Compose the output array.
	// opening square bracket
	output_pointer = ensure(output_buffer, 1);
	if (output_pointer == NULL)
		return (FALSE);

	*output_pointer = '[';
	output_buffer->offset++;
	output_buffer->depth++;

	while (current_element != NULL)
	{
		if (!print_value(current_element, output_buffer))
			return (FALSE);
		update_offset(output_buffer);
		if (current_element->next)
		{
			length = (t_size) (output_buffer->format ? 2 : 1);
			output_pointer = ensure(output_buffer, length + 1);
			if (output_pointer == NULL)
				return (FALSE);
			*output_pointer++ = ',';
			if (output_buffer->format)
			{
				*output_pointer++ = ' ';
			}
			*output_pointer = '\0';
			output_buffer->offset += length;
		}
		current_element = current_element->next;
	}

	output_pointer = ensure(output_buffer, 2);
	if (output_pointer == NULL)
		return (FALSE);
	*output_pointer++ = ']';
	*output_pointer = '\0';
	output_buffer->depth--;
	return (TRUE);
}

// Render an object to text.
static t_bool print_object(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output_pointer = NULL;
	t_size length = 0;
	s_json* current_item = item->child;

	if (output_buffer == NULL)
		return (FALSE);

	// Compose the output:
	length = (t_size) (output_buffer->format ? 2 : 1); /* fmt:
	{\n */
	output_pointer = ensure(output_buffer, length + 1);
	if (output_pointer == NULL)
		return (FALSE);

	*output_pointer++ = '{';
	output_buffer->depth++;
	if (output_buffer->format)
	{
		*output_pointer++ = '\n';
	}
	output_buffer->offset += length;

	while (current_item)
	{
		if (output_buffer->format)
		{
			t_size i;
			output_pointer = ensure(output_buffer, output_buffer->depth);
			if (output_pointer == NULL)
				return (FALSE);
			for (i = 0; i < output_buffer->depth; i++)
			{
				*output_pointer++ = '\t';
			}
			output_buffer->offset += output_buffer->depth;
		}

		// print key
		if (!print_string_ptr((t_char*)current_item->key, output_buffer))
			return (FALSE);
		update_offset(output_buffer);

		length = (t_size) (output_buffer->format ? 2 : 1);
		output_pointer = ensure(output_buffer, length);
		if (output_pointer == NULL)
			return (FALSE);
		*output_pointer++ = ':';
		if (output_buffer->format)
		{
			*output_pointer++ = '\t';
		}
		output_buffer->offset += length;

		// print value
		if (!print_value(current_item, output_buffer))
			return (FALSE);
		update_offset(output_buffer);

		// print comma if not last
		length = ((t_size)(output_buffer->format ? 1 : 0) + (t_size)(current_item->next ? 1 : 0));
		output_pointer = ensure(output_buffer, length + 1);
		if (output_pointer == NULL)
			return (FALSE);
		if (current_item->next)
		{
			*output_pointer++ = ',';
		}

		if (output_buffer->format)
		{
			*output_pointer++ = '\n';
		}
		*output_pointer = '\0';
		output_buffer->offset += length;

		current_item = current_item->next;
	}

	output_pointer = ensure(output_buffer, output_buffer->format ? (output_buffer->depth + 1) : 2);
	if (output_pointer == NULL)
		return (FALSE);
	if (output_buffer->format)
	{
		t_size i;
		for (i = 0; i < (output_buffer->depth - 1); i++)
		{
			*output_pointer++ = '\t';
		}
	}
	*output_pointer++ = '}';
	*output_pointer = '\0';
	output_buffer->depth--;
	return (TRUE);
}




static t_char* print(s_json const* const item, t_bool format)
{
	static const t_size default_buffer_size = 256;
	s_json_print buffer[1];
	t_char* printed = NULL;

	Memory_Set(buffer, 0, sizeof(buffer));
	// create buffer
	buffer->buffer = (t_char*) Memory_Alloc(default_buffer_size);
	buffer->length = default_buffer_size;
	buffer->format = format;
	if (buffer->buffer == NULL)
	{
		goto fail;
	}
	// print the value
	if (!print_value(item, buffer))
	{
		goto fail;
	}
	update_offset(buffer);

#ifdef Memory_Realloc // check if reallocate is available
		printed = (t_char*)Memory_Realloc(buffer->buffer, buffer->offset + 1);
		if (printed == NULL)
		{
			goto fail;
		}
		buffer->buffer = NULL;
#else // otherwise copy the JSON over to a new buffer
		printed = (t_char*) Memory_Alloc(buffer->offset + 1);
		if (printed == NULL)
		{
			goto fail;
		}
		Memory_Copy(printed, buffer->buffer, MIN(buffer->length, buffer->offset + 1));
		printed[buffer->offset] = '\0'; // just to be sure

		// free the buffer
		Memory_Free(buffer->buffer);
#endif
	return (printed);

fail:
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

// Render a s_json item/entity/structure to text.
t_char*	JSON_Print(s_json const* item)
{
	return (t_char*)print(item, TRUE);
}

t_char*	JSON_PrintUnformatted(s_json const* item)
{
	return (t_char*)print(item, FALSE);
}

t_char*	JSON_PrintBuffered(s_json const* item, t_sint prebuffer, t_bool fmt)
{
	s_json_print p = { 0 };

	if (prebuffer < 0)
		return (NULL);
	p.buffer = (t_char*)Memory_Alloc((t_size)prebuffer);
	if (!p.buffer)
		return (NULL);
	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = fmt;
	if (!print_value(item, &p))
	{
		Memory_Free(p.buffer);
		return (NULL);
	}
	return (t_char*)p.buffer;
}

t_bool	JSON_PrintPreallocated(s_json* item, t_char* buffer, const t_sint length, const t_bool format)
{
	s_json_print p = { 0 };

	if ((length < 0) || (buffer == NULL))
		return (FALSE);

	p.buffer = (t_char*)buffer;
	p.length = (t_size)length;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = format;
	return (print_value(item, &p));
}