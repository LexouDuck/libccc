
#include <stdlib.h>

#ifdef ENABLE_LOCALES
#include <locale.h>
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/json.h"



#define JSON_TYPE_MASK	(0xFF)



typedef struct	s_json_error
{
	const t_char* json;
	t_size				position;
}				s_json_error;

static s_json_error global_error = { NULL, 0 };



const char*	JSON_GetErrorPtr(void)
{
	return ((const char*)(global_error.json + global_error.position));
}

char*	JSON_GetStringValue(s_json const* const item) 
{
	if (!JSON_IsString(item)) 
	{
		return (NULL);
	}

	return (item->value_string);
}

t_f64	JSON_GetNumberValue(s_json const* const item) 
{
	if (!JSON_IsNumber(item)) 
	{
		return ((t_f64)NAN);
	}

	return (item->value_double);
}



/* Internal constructor. */
static s_json* JSON_New_Item(void)
{
	return ((s_json*)Memory_New(sizeof(s_json)));
}

/* Delete a s_json structure. */
void	JSON_Delete(s_json* item)
{
	s_json* next = NULL;
	while (item != NULL)
	{
		next = item->next;
		if (!(item->type & JSON_IsReference) && (item->child != NULL))
		{
			JSON_Delete(item->child);
		}
		if (!(item->type & JSON_IsReference) && (item->value_string != NULL))
		{
			Memory_Free(item->value_string);
		}
		if (!(item->type & JSON_StringIsConst) && (item->string != NULL))
		{
			Memory_Free(item->string);
		}
		Memory_Free(item);
		item = next;
	}
}

/* get the decimal point character of the current locale */
static t_char get_decimal_point(void)
{
#ifdef ENABLE_LOCALES
	struct lconv *lconv = localeconv();
	return (t_char) lconv->decimal_point[0];
#else
	return ('.');
#endif
}

typedef struct	json_parse
{
	const t_char* content;
	t_size length;
	t_size offset;
	t_size depth; /* How deeply nested (in arrays/objects) is the input at the current offset. */
}				s_json_parse;

/* check if the given size is left to read in a given parse buffer (starting with 1) */
#define can_read(buffer, size) ((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))
/* check if the buffer can be accessed at the given index (starting with 0) */
#define can_access_at_index(buffer, index) ((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))
#define cannot_access_at_index(buffer, index) (!can_access_at_index(buffer, index))
/* get a pointer to the buffer at the position */
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)

/* Parse the input text to generate a number, and populate the result into item. */
static t_bool parse_number(s_json* const item, s_json_parse* const input_buffer)
{
	t_f64 number = 0;
	t_char* after_end = NULL;
	t_char number_c_string[64];
	t_char decimal_point = get_decimal_point();
	t_size i = 0;

	if ((input_buffer == NULL) || (input_buffer->content == NULL))
	{
		return (FALSE);
	}

	/* copy the number into a temporary buffer and replace '.' with the decimal point
	 * of the current locale (for strtod)
	 * This also takes care of '\0' not necessarily being available for marking the end of the input */
	for (i = 0; (i < (sizeof(number_c_string) - 1)) && can_access_at_index(input_buffer, i); i++)
	{
		switch (buffer_at_offset(input_buffer)[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '+':
			case '-':
			case 'e':
			case 'E':
				number_c_string[i] = buffer_at_offset(input_buffer)[i];
				break;

			case '.':
				number_c_string[i] = decimal_point;
				break;

			default:
				goto loop_end;
		}
	}
loop_end:
	number_c_string[i] = '\0';

	number = strtod((const char*)number_c_string, (char**)&after_end);
	if (number_c_string == after_end)
	{
		return (FALSE); /* parse_error */
	}

	item->value_double = number;

	/* use saturation in case of overflow */
	if (number >= INT_MAX)
	{
		item->valueint = INT_MAX;
	}
	else if (number <= (t_f64)INT_MIN)
	{
		item->valueint = INT_MIN;
	}
	else
	{
		item->valueint = (t_sint)number;
	}

	item->type = JSON_Number;

	input_buffer->offset += (t_size)(after_end - number_c_string);
	return (TRUE);
}

/* don't ask me, but the original JSON_SetNumberValue returns an integer or t_f64 */
t_f64	JSON_SetNumberHelper(s_json* object, t_f64 number)
{
	if (number >= INT_MAX)
	{
		object->valueint = INT_MAX;
	}
	else if (number <= (t_f64)INT_MIN)
	{
		object->valueint = INT_MIN;
	}
	else
	{
		object->valueint = (t_sint)number;
	}

	return (object->value_double = number);
}

char*	JSON_SetValue_String(s_json* object, const char* value_string)
{
	char* copy = NULL;
	/* if object's type is not JSON_String or is JSON_IsReference, it should not set value_string */
	if (!(object->type & JSON_String) || (object->type & JSON_IsReference))
	{
		return (NULL);
	}
	if (String_Length(value_string) <= String_Length(object->value_string))
	{
		String_Copy(object->value_string, value_string);
		return (object->value_string);
	}
    copy = (char*)String_Duplicate((const t_char*)value_string);
	if (copy == NULL)
	{
		return (NULL);
	}
	if (object->value_string != NULL)
	{
		Memory_Free(object->value_string);
	}
	object->value_string = copy;

	return (copy);
}

typedef struct	json_print
{
	t_char* buffer;
	t_size length;
	t_size offset;
	t_size depth; /* current nesting depth (for formatted printing) */
	t_bool noalloc;
	t_bool format; /* is this print a formatted print */
}				s_json_print;

/* realloc s_json_print if necessary to have at least "needed" bytes more */
static t_char* ensure(s_json_print* const p, t_size needed)
{
	t_char* newbuffer = NULL;
	t_size newsize = 0;

	if ((p == NULL) || (p->buffer == NULL))
	{
		return (NULL);
	}

	if ((p->length > 0) && (p->offset >= p->length))
	{
		/* make sure that offset is valid */
		return (NULL);
	}

	if (needed > INT_MAX)
	{
		/* sizes bigger than INT_MAX are currently not supported */
		return (NULL);
	}

	needed += p->offset + 1;
	if (needed <= p->length)
	{
		return (p->buffer + p->offset);
	}

	if (p->noalloc) {
		return (NULL);
	}

	/* calculate new buffer size */
	if (needed > (INT_MAX / 2))
	{
		/* overflow of t_sint, use INT_MAX if possible */
		if (needed <= INT_MAX)
		{
			newsize = INT_MAX;
		}
		else
		{
			return (NULL);
		}
	}
	else
	{
		newsize = needed * 2;
	}

	if (p->Memory_Realloc != NULL)
	{
		/* reallocate with realloc if available */
		newbuffer = (t_char*)p->Memory_Realloc(p->buffer, newsize);
		if (newbuffer == NULL)
		{
			p->Memory_Free(p->buffer);
			p->length = 0;
			p->buffer = NULL;

			return (NULL);
		}
	}
	else
	{
		/* otherwise reallocate manually */
		newbuffer = (t_char*)p->Memory_Alloc(newsize);
		if (!newbuffer)
		{
			p->Memory_Free(p->buffer);
			p->length = 0;
			p->buffer = NULL;

			return (NULL);
		}
		
		Memory_Copy(newbuffer, p->buffer, p->offset + 1);
		p->Memory_Free(p->buffer);
	}
	p->length = newsize;
	p->buffer = newbuffer;

	return (newbuffer + p->offset);
}

/* calculate the new length of the string in a s_json_print and update the offset */
static void update_offset(s_json_print* const buffer)
{
	const t_char* buffer_pointer = NULL;
	if ((buffer == NULL) || (buffer->buffer == NULL))
	{
		return;
	}
	buffer_pointer = buffer->buffer + buffer->offset;

	buffer->offset += String_Length((const char*)buffer_pointer);
}

/* Render the number nicely from the given item into a string. */
static t_bool print_number(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output_pointer = NULL;
	t_f64 d = item->value_double;
	t_sint length = 0;
	t_size i = 0;
	t_char number_buffer[26] = {0}; /* temporary buffer to print the number into */
	t_char decimal_point = get_decimal_point();
	t_f64 test = 0.0;

	if (output_buffer == NULL)
	{
		return (FALSE);
	}

	/* This checks for NaN and Infinity */
	if (isnan(d) || isinf(d))
	{
		length = sprintf((char*)number_buffer, "null");
	}
	else
	{
		/* Try 15 decimal places of precision to avoid nonsignificant nonzero digits */
		length = sprintf((char*)number_buffer, "%1.15g", d);

		/* Check whether the original t_f64 can be recovered */
		if ((sscanf((char*)number_buffer, "%lg", &test) != 1) || !F64_Equals((t_f64)test, d))
		{
			/* If not, print with 17 decimal places of precision */
			length = sprintf((char*)number_buffer, "%1.17g", d);
		}
	}

	/* sprintf failed or buffer overrun occurred */
	if ((length < 0) || (length > (t_sint)(sizeof(number_buffer) - 1)))
	{
		return (FALSE);
	}

	/* reserve appropriate space in the output */
	output_pointer = ensure(output_buffer, (t_size)length + sizeof(""));
	if (output_pointer == NULL)
	{
		return (FALSE);
	}

	/* copy the printed number to the output and replace locale
	 * dependent decimal point with '.' */
	for (i = 0; i < ((t_size)length); i++)
	{
		if (number_buffer[i] == decimal_point)
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

/* parse 4 digit hexadecimal number */
static t_uint	parse_hex4(const t_char* const input)
{
	t_uint h = 0;
	t_size i = 0;

	for (i = 0; i < 4; i++)
	{
		/* parse digit */
		if ((input[i] >= '0') && (input[i] <= '9'))
		{
			h += (t_uint) input[i] - '0';
		}
		else if ((input[i] >= 'A') && (input[i] <= 'F'))
		{
			h += (t_uint) 10 + input[i] - 'A';
		}
		else if ((input[i] >= 'a') && (input[i] <= 'f'))
		{
			h += (t_uint) 10 + input[i] - 'a';
		}
		else /* invalid */
		{
			return (0);
		}

		if (i < 3)
		{
			/* shift left to make place for the next nibble */
			h = h << 4;
		}
	}

	return (h);
}

/* converts a UTF-16 literal to UTF-8
 * A literal can be one or two sequences of the form \uXXXX */
static t_char utf16_literal_to_utf8(const t_char* const input_pointer, const t_char* const input_end, t_char* *output_pointer)
{
	long t_uint codepoint = 0;
	t_uint first_code = 0;
	const t_char* first_sequence = input_pointer;
	t_char utf8_length = 0;
	t_char utf8_position = 0;
	t_char sequence_length = 0;
	t_char first_byte_mark = 0;

	if ((input_end - first_sequence) < 6)
	{
		/* input ends unexpectedly */
		goto fail;
	}

	/* get the first utf16 sequence */
	first_code = parse_hex4(first_sequence + 2);

	/* check that the code is valid */
	if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
	{
		goto fail;
	}

	/* UTF16 surrogate pair */
	if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
	{
		const t_char* second_sequence = first_sequence + 6;
		t_uint second_code = 0;
		sequence_length = 12; /* \uXXXX\uXXXX */

		if ((input_end - second_sequence) < 6)
		{
			/* input ends unexpectedly */
			goto fail;
		}

		if ((second_sequence[0] != '\\') || (second_sequence[1] != 'u'))
		{
			/* missing second half of the surrogate pair */
			goto fail;
		}

		/* get the second utf16 sequence */
		second_code = parse_hex4(second_sequence + 2);
		/* check that the code is valid */
		if ((second_code < 0xDC00) || (second_code > 0xDFFF))
		{
			/* invalid second half of the surrogate pair */
			goto fail;
		}


		/* calculate the unicode codepoint from the surrogate pair */
		codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
	}
	else
	{
		sequence_length = 6; /* \uXXXX */
		codepoint = first_code;
	}

	/* encode as UTF-8
	 * takes at maximum 4 bytes to encode:
	 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
	if (codepoint < 0x80)
	{
		/* normal ascii, encoding 0xxxxxxx */
		utf8_length = 1;
	}
	else if (codepoint < 0x800)
	{
		/* two bytes, encoding 110xxxxx 10xxxxxx */
		utf8_length = 2;
		first_byte_mark = 0xC0; /* 11000000 */
	}
	else if (codepoint < 0x10000)
	{
		/* three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx */
		utf8_length = 3;
		first_byte_mark = 0xE0; /* 11100000 */
	}
	else if (codepoint <= 0x10FFFF)
	{
		/* four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx */
		utf8_length = 4;
		first_byte_mark = 0xF0; /* 11110000 */
	}
	else
	{
		/* invalid unicode codepoint */
		goto fail;
	}

	/* encode as utf8 */
	for (utf8_position = (t_char)(utf8_length - 1); utf8_position > 0; utf8_position--)
	{
		/* 10xxxxxx */
		(*output_pointer)[utf8_position] = (t_char)((codepoint | 0x80) & 0xBF);
		codepoint >>= 6;
	}
	/* encode first byte */
	if (utf8_length > 1)
	{
		(*output_pointer)[0] = (t_char)((codepoint | first_byte_mark) & JSON_TYPE_MASK);
	}
	else
	{
		(*output_pointer)[0] = (t_char)(codepoint & 0x7F);
	}

	*output_pointer += utf8_length;

	return (sequence_length);

fail:
	return (0);
}

/* Parse the input text into an unescaped cinput, and populate item. */
static t_bool parse_string(s_json* const item, s_json_parse* const input_buffer)
{
	const t_char* input_pointer = buffer_at_offset(input_buffer) + 1;
	const t_char* input_end = buffer_at_offset(input_buffer) + 1;
	t_char* output_pointer = NULL;
	t_char* output = NULL;

	/* not a string */
	if (buffer_at_offset(input_buffer)[0] != '\"')
	{
		goto fail;
	}

	{
		/* calculate approximate size of the output (overestimate) */
		t_size allocation_length = 0;
		t_size skipped_bytes = 0;
		while (((t_size)(input_end - input_buffer->content) < input_buffer->length) && (*input_end != '\"'))
		{
			/* is escape sequence */
			if (input_end[0] == '\\')
			{
				if ((t_size)(input_end + 1 - input_buffer->content) >= input_buffer->length)
				{
					/* prevent buffer overflow when last input character is a backslash */
					goto fail;
				}
				skipped_bytes++;
				input_end++;
			}
			input_end++;
		}
		if (((t_size)(input_end - input_buffer->content) >= input_buffer->length) || (*input_end != '\"'))
		{
			goto fail; /* string ended unexpectedly */
		}

		/* This is at most how much we need for the output */
		allocation_length = (t_size) (input_end - buffer_at_offset(input_buffer)) - skipped_bytes;
		output = (t_char*)input_buffer->Memory_Alloc(allocation_length + sizeof(""));
		if (output == NULL)
		{
			goto fail; /* allocation failure */
		}
	}

	output_pointer = output;
	/* loop through the string literal */
	while (input_pointer < input_end)
	{
		if (*input_pointer != '\\')
		{
			*output_pointer++ = *input_pointer++;
		}
		/* escape sequence */
		else
		{
			t_char sequence_length = 2;
			if ((input_end - input_pointer) < 1)
			{
				goto fail;
			}

			switch (input_pointer[1])
			{
				case 'b':
					*output_pointer++ = '\b';
					break;
				case 'f':
					*output_pointer++ = '\f';
					break;
				case 'n':
					*output_pointer++ = '\n';
					break;
				case 'r':
					*output_pointer++ = '\r';
					break;
				case 't':
					*output_pointer++ = '\t';
					break;
				case '\"':
				case '\\':
				case '/':
					*output_pointer++ = input_pointer[1];
					break;

				/* UTF-16 literal */
				case 'u':
					sequence_length = utf16_literal_to_utf8(input_pointer, input_end, &output_pointer);
					if (sequence_length == 0)
					{
						/* failed to convert UTF16-literal to UTF-8 */
						goto fail;
					}
					break;

				default:
					goto fail;
			}
			input_pointer += sequence_length;
		}
	}

	/* zero terminate the output */
	*output_pointer = '\0';

	item->type = JSON_String;
	item->value_string = (char*)output;

	input_buffer->offset = (t_size) (input_end - input_buffer->content);
	input_buffer->offset++;

	return (TRUE);

fail:
	if (output != NULL)
	{
		input_buffer->Memory_Free(output);
	}

	if (input_pointer != NULL)
	{
		input_buffer->offset = (t_size)(input_pointer - input_buffer->content);
	}

	return (FALSE);
}

/* Render the cstring provided to an escaped version that can be printed. */
static t_bool print_string_ptr(const t_char* const input, s_json_print* const output_buffer)
{
	const t_char* input_pointer = NULL;
	t_char* output = NULL;
	t_char* output_pointer = NULL;
	t_size output_length = 0;
	/* numbers of additional characters needed for escaping */
	t_size escape_characters = 0;

	if (output_buffer == NULL)
	{
		return (FALSE);
	}

	/* empty string */
	if (input == NULL)
	{
		output = ensure(output_buffer, sizeof("\"\""));
		if (output == NULL)
		{
			return (FALSE);
		}
		String_Copy((char*)output, "\"\"");

		return (TRUE);
	}

	/* set "flag" to 1 if something needs to be escaped */
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
				/* one character escape sequence */
				escape_characters++;
				break;
			default:
				if (*input_pointer < 32)
				{
					/* UTF-16 escape sequence uXXXX */
					escape_characters += 5;
				}
				break;
		}
	}
	output_length = (t_size)(input_pointer - input) + escape_characters;

	output = ensure(output_buffer, output_length + sizeof("\"\""));
	if (output == NULL)
	{
		return (FALSE);
	}

	/* no characters have to be escaped */
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
	/* copy the string */
	for (input_pointer = input; *input_pointer != '\0'; (void)input_pointer++, output_pointer++)
	{
		if ((*input_pointer > 31) && (*input_pointer != '\"') && (*input_pointer != '\\'))
		{
			/* normal character, copy */
			*output_pointer = *input_pointer;
		}
		else
		{
			/* character needs to be escaped */
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
				default:
					/* escape and print as unicode codepoint */
					sprintf((char*)output_pointer, "u%04x", *input_pointer);
					output_pointer += 4;
					break;
			}
		}
	}
	output[output_length + 1] = '\"';
	output[output_length + 2] = '\0';

	return (TRUE);
}

/* Invoke print_string_ptr (which is useful) on an item. */
static t_bool print_string(s_json const* const item, s_json_print* const p)
{
	return (print_string_ptr((t_char*)item->value_string, p));
}

/* Predeclare these prototypes. */
static t_bool parse_value(s_json* const item, s_json_parse* const input_buffer);
static t_bool print_value(s_json const* const item, s_json_print* const output_buffer);
static t_bool parse_array(s_json* const item, s_json_parse* const input_buffer);
static t_bool print_array(s_json const* const item, s_json_print* const output_buffer);
static t_bool parse_object(s_json* const item, s_json_parse* const input_buffer);
static t_bool print_object(s_json const* const item, s_json_print* const output_buffer);

/* Utility to jump whitespace and cr/lf */
static s_json_parse *buffer_skip_whitespace(s_json_parse* const buffer)
{
	if ((buffer == NULL) || (buffer->content == NULL))
	{
		return (NULL);
	}

	if (cannot_access_at_index(buffer, 0))
	{
		return (buffer);
	}

	while (can_access_at_index(buffer, 0) && (buffer_at_offset(buffer)[0] <= 32))
	{
	   buffer->offset++;
	}

	if (buffer->offset == buffer->length)
	{
		buffer->offset--;
	}

	return (buffer);
}

/* skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer */
static s_json_parse *skip_utf8_bom(s_json_parse* const buffer)
{
	if ((buffer == NULL) || (buffer->content == NULL) || (buffer->offset != 0))
	{
		return (NULL);
	}

	if (can_access_at_index(buffer, 4) && (strncmp((const char*)buffer_at_offset(buffer), "\xEF\xBB\xBF", 3) == 0))
	{
		buffer->offset += 3;
	}

	return (buffer);
}

s_json*	JSON_ParseWithOpts(const char* value, const char* *return_parse_end, t_bool require_null_terminated)
{
	t_size buffer_length;

	if (NULL == value)
	{
		return (NULL);
	}

	/* Adding null character size due to require_null_terminated. */
	buffer_length = String_Length(value) + sizeof("");

	return (JSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated));
}

/* Parse an object - create a new root, and populate. */
s_json*	JSON_ParseWithLengthOpts(const char* value, t_size buffer_length, const char* *return_parse_end, t_bool require_null_terminated)
{
	s_json_parse buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
	s_json* item = NULL;

	/* reset s_json_error position */
	global_error.json = NULL;
	global_error.position = 0;

	if (value == NULL || 0 == buffer_length)
	{
		goto fail;
	}

	buffer.content = (const t_char*)value;
	buffer.length = buffer_length; 
	buffer.offset = 0;
	buffer.hooks = global_hooks;

	item = JSON_New_Item(&global_hooks);
	if (item == NULL) /* memory fail */
	{
		goto fail;
	}

	if (!parse_value(item, buffer_skip_whitespace(skip_utf8_bom(&buffer))))
	{
		/* parse failure. ep is set. */
		goto fail;
	}

	/* if we require null-terminated JSON without appended garbage, skip and then check for a null terminator */
	if (require_null_terminated)
	{
		buffer_skip_whitespace(&buffer);
		if ((buffer.offset >= buffer.length) || buffer_at_offset(&buffer)[0] != '\0')
		{
			goto fail;
		}
	}
	if (return_parse_end)
	{
		*return_parse_end = (const char*)buffer_at_offset(&buffer);
	}

	return (item);

fail:
	if (item != NULL)
	{
		JSON_Delete(item);
	}

	if (value != NULL)
	{
		s_json_error local_error;
		local_error.json = (const t_char*)value;
		local_error.position = 0;

		if (buffer.offset < buffer.length)
		{
			local_error.position = buffer.offset;
		}
		else if (buffer.length > 0)
		{
			local_error.position = buffer.length - 1;
		}

		if (return_parse_end != NULL)
		{
			*return_parse_end = (const char*)local_error.json + local_error.position;
		}

		global_error = local_error;
	}

	return (NULL);
}

/* Default options for JSON_Parse */
s_json*	JSON_Parse(const char* value)
{
	return (JSON_ParseWithOpts(value, 0, 0));
}

s_json*	JSON_ParseWithLength(const char* value, t_size buffer_length)
{
	return (JSON_ParseWithLengthOpts(value, buffer_length, 0, 0));
}

#define cjson_min(a, b) (((a) < (b)) ? (a) : (b))

static t_char* print(s_json const* const item, t_bool format, s_json_hooks const* const hooks)
{
	static const t_size default_buffer_size = 256;
	s_json_print buffer[1];
	t_char* printed = NULL;

	memset(buffer, 0, sizeof(buffer));

	/* create buffer */
	buffer->buffer = (t_char*) Memory_Alloc(default_buffer_size);
	buffer->length = default_buffer_size;
	buffer->format = format;
	buffer->hooks = *hooks;
	if (buffer->buffer == NULL)
	{
		goto fail;
	}

	/* print the value */
	if (!print_value(item, buffer))
	{
		goto fail;
	}
	update_offset(buffer);

	/* check if reallocate is available */
	if (hooks->reallocate != NULL)
	{
		printed = (t_char*) hooks->reallocate(buffer->buffer, buffer->offset + 1);
		if (printed == NULL) {
			goto fail;
		}
		buffer->buffer = NULL;
	}
	else /* otherwise copy the JSON over to a new buffer */
	{
		printed = (t_char*) Memory_Alloc(buffer->offset + 1);
		if (printed == NULL)
		{
			goto fail;
		}
		Memory_Copy(printed, buffer->buffer, cjson_min(buffer->length, buffer->offset + 1));
		printed[buffer->offset] = '\0'; /* just to be sure */

		/* free the buffer */
		hooks->deallocate(buffer->buffer);
	}

	return (printed);

fail:
	if (buffer->buffer != NULL)
	{
		hooks->deallocate(buffer->buffer);
	}

	if (printed != NULL)
	{
		hooks->deallocate(printed);
	}

	return (NULL);
}

/* Render a s_json item/entity/structure to text. */
char*	JSON_Print(s_json const* item)
{
	return (char*)print(item, TRUE, &global_hooks);
}

char*	JSON_PrintUnformatted(s_json const* item)
{
	return (char*)print(item, FALSE, &global_hooks);
}

char*	JSON_PrintBuffered(s_json const* item, t_sint prebuffer, t_bool fmt)
{
	s_json_print p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

	if (prebuffer < 0)
	{
		return (NULL);
	}

	p.buffer = (t_char*)Memory_Alloc((t_size)prebuffer);
	if (!p.buffer)
	{
		return (NULL);
	}

	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = fmt;
	p.hooks = global_hooks;

	if (!print_value(item, &p))
	{
		Memory_Free(p.buffer);
		return (NULL);
	}

	return (char*)p.buffer;
}

t_bool	JSON_PrintPreallocated(s_json* item, char* buffer, const t_sint length, const t_bool format)
{
	s_json_print p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

	if ((length < 0) || (buffer == NULL))
	{
		return (FALSE);
	}

	p.buffer = (t_char*)buffer;
	p.length = (t_size)length;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = format;
	p.hooks = global_hooks;

	return (print_value(item, &p));
}

/* Parser core - when encountering text, process appropriately. */
static t_bool parse_value(s_json* const item, s_json_parse* const input_buffer)
{
	if ((input_buffer == NULL) || (input_buffer->content == NULL))
	{
		return (FALSE; /* no input *)/
	}

	/* parse the different types of values */
	/* null */
	if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "null", 4) == 0))
	{
		item->type = JSON_NULL;
		input_buffer->offset += 4;
		return (TRUE);
	}
	/* FALSE */
	if (can_read(input_buffer, 5) && (strncmp((const char*)buffer_at_offset(input_buffer), "FALSE", 5) == 0))
	{
		item->type = JSON_False;
		input_buffer->offset += 5;
		return (TRUE);
	}
	/* TRUE */
	if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "TRUE", 4) == 0))
	{
		item->type = JSON_True;
		item->valueint = 1;
		input_buffer->offset += 4;
		return (TRUE);
	}
	/* string */
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
	{
		return (parse_string(item, input_buffer));
	}
	/* number */
	if (can_access_at_index(input_buffer, 0) && ((buffer_at_offset(input_buffer)[0] == '-') || ((buffer_at_offset(input_buffer)[0] >= '0') && (buffer_at_offset(input_buffer)[0] <= '9'))))
	{
		return (parse_number(item, input_buffer));
	}
	/* array */
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
	{
		return (parse_array(item, input_buffer));
	}
	/* object */
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
	{
		return (parse_object(item, input_buffer));
	}

	return (FALSE);
}

/* Render a value to text. */
static t_bool print_value(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output = NULL;

	if ((item == NULL) || (output_buffer == NULL))
	{
		return (FALSE);
	}

	switch ((item->type) & JSON_TYPE_MASK)
	{
		case JSON_NULL:
			output = ensure(output_buffer, 5);
			if (output == NULL)
			{
				return (FALSE);
			}
			String_Copy((char*)output, "null");
			return (TRUE);

		case JSON_False:
			output = ensure(output_buffer, 6);
			if (output == NULL)
			{
				return (FALSE);
			}
			String_Copy((char*)output, "FALSE");
			return (TRUE);

		case JSON_True:
			output = ensure(output_buffer, 5);
			if (output == NULL)
			{
				return (FALSE);
			}
			String_Copy((char*)output, "TRUE");
			return (TRUE);

		case JSON_Number:
			return (print_number(item, output_buffer));

		case JSON_Raw:
		{
			t_size raw_length = 0;
			if (item->value_string == NULL)
			{
				return (FALSE);
			}

			raw_length = String_Length(item->value_string) + sizeof("");
			output = ensure(output_buffer, raw_length);
			if (output == NULL)
			{
				return (FALSE);
			}
			Memory_Copy(output, item->value_string, raw_length);
			return (TRUE);
		}

		case JSON_String:
			return (print_string(item, output_buffer));

		case JSON_Array:
			return (print_array(item, output_buffer));

		case JSON_Object:
			return (print_object(item, output_buffer));

		default:
			return (FALSE);
	}
}

/* Build an array from input text. */
static t_bool parse_array(s_json* const item, s_json_parse* const input_buffer)
{
	s_json* head = NULL; /* head of the linked list */
	s_json* current_item = NULL;

	if (input_buffer->depth >= JSON_NESTING_LIMIT)
	{
		return (FALSE; /* to deeply nested *)/
	}
	input_buffer->depth++;

	if (buffer_at_offset(input_buffer)[0] != '[')
	{
		/* not an array */
		goto fail;
	}

	input_buffer->offset++;
	buffer_skip_whitespace(input_buffer);
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ']'))
	{
		/* empty array */
		goto success;
	}

	/* check if we skipped to the end of the buffer */
	if (cannot_access_at_index(input_buffer, 0))
	{
		input_buffer->offset--;
		goto fail;
	}

	/* step back to character in front of the first element */
	input_buffer->offset--;
	/* loop through the comma separated array elements */
	do
	{
		/* allocate next item */
		s_json* new_item = JSON_New_Item(&(input_buffer->hooks));
		if (new_item == NULL)
		{
			goto fail; /* allocation failure */
		}

		/* attach next item to list */
		if (head == NULL)
		{
			/* start the linked list */
			current_item = head = new_item;
		}
		else
		{
			/* add to the end and advance */
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}

		/* parse next value */
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_value(current_item, input_buffer))
		{
			goto fail; /* failed to parse value */
		}
		buffer_skip_whitespace(input_buffer);
	}
	while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

	if (cannot_access_at_index(input_buffer, 0) || buffer_at_offset(input_buffer)[0] != ']')
	{
		goto fail; /* expected end of array */
	}

success:
	input_buffer->depth--;

	if (head != NULL) {
		head->prev = current_item;
	}

	item->type = JSON_Array;
	item->child = head;

	input_buffer->offset++;

	return (TRUE);

fail:
	if (head != NULL)
	{
		JSON_Delete(head);
	}

	return (FALSE);
}

/* Render an array to text */
static t_bool print_array(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output_pointer = NULL;
	t_size length = 0;
	s_json* current_element = item->child;

	if (output_buffer == NULL)
	{
		return (FALSE);
	}

	/* Compose the output array. */
	/* opening square bracket */
	output_pointer = ensure(output_buffer, 1);
	if (output_pointer == NULL)
	{
		return (FALSE);
	}

	*output_pointer = '[';
	output_buffer->offset++;
	output_buffer->depth++;

	while (current_element != NULL)
	{
		if (!print_value(current_element, output_buffer))
		{
			return (FALSE);
		}
		update_offset(output_buffer);
		if (current_element->next)
		{
			length = (t_size) (output_buffer->format ? 2 : 1);
			output_pointer = ensure(output_buffer, length + 1);
			if (output_pointer == NULL)
			{
				return (FALSE);
			}
			*output_pointer++ = ',';
			if(output_buffer->format)
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
	{
		return (FALSE);
	}
	*output_pointer++ = ']';
	*output_pointer = '\0';
	output_buffer->depth--;

	return (TRUE);
}

/* Build an object from the text. */
static t_bool parse_object(s_json* const item, s_json_parse* const input_buffer)
{
	s_json* head = NULL; /* linked list head */
	s_json* current_item = NULL;

	if (input_buffer->depth >= JSON_NESTING_LIMIT)
	{
		return (FALSE; /* to deeply nested *)/
	}
	input_buffer->depth++;

	if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '{'))
	{
		goto fail; /* not an object */
	}

	input_buffer->offset++;
	buffer_skip_whitespace(input_buffer);
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '}'))
	{
		goto success; /* empty object */
	}

	/* check if we skipped to the end of the buffer */
	if (cannot_access_at_index(input_buffer, 0))
	{
		input_buffer->offset--;
		goto fail;
	}

	/* step back to character in front of the first element */
	input_buffer->offset--;
	/* loop through the comma separated array elements */
	do
	{
		/* allocate next item */
		s_json* new_item = JSON_New_Item(&(input_buffer->hooks));
		if (new_item == NULL)
		{
			goto fail; /* allocation failure */
		}

		/* attach next item to list */
		if (head == NULL)
		{
			/* start the linked list */
			current_item = head = new_item;
		}
		else
		{
			/* add to the end and advance */
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}

		/* parse the name of the child */
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_string(current_item, input_buffer))
		{
			goto fail; /* failed to parse name */
		}
		buffer_skip_whitespace(input_buffer);

		/* swap value_string and string, because we parsed the name */
		current_item->string = current_item->value_string;
		current_item->value_string = NULL;

		if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != ':'))
		{
			goto fail; /* invalid object */
		}

		/* parse the value */
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_value(current_item, input_buffer))
		{
			goto fail; /* failed to parse value */
		}
		buffer_skip_whitespace(input_buffer);
	}
	while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

	if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '}'))
	{
		goto fail; /* expected end of object */
	}

success:
	input_buffer->depth--;

	if (head != NULL) {
		head->prev = current_item;
	}

	item->type = JSON_Object;
	item->child = head;

	input_buffer->offset++;
	return (TRUE);

fail:
	if (head != NULL)
	{
		JSON_Delete(head);
	}

	return (FALSE);
}

/* Render an object to text. */
static t_bool print_object(s_json const* const item, s_json_print* const output_buffer)
{
	t_char* output_pointer = NULL;
	t_size length = 0;
	s_json* current_item = item->child;

	if (output_buffer == NULL)
	{
		return (FALSE);
	}

	/* Compose the output: */
	length = (t_size) (output_buffer->format ? 2 : 1); /* fmt: {\n */
	output_pointer = ensure(output_buffer, length + 1);
	if (output_pointer == NULL)
	{
		return (FALSE);
	}

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
			{
				return (FALSE);
			}
			for (i = 0; i < output_buffer->depth; i++)
			{
				*output_pointer++ = '\t';
			}
			output_buffer->offset += output_buffer->depth;
		}

		/* print key */
		if (!print_string_ptr((t_char*)current_item->string, output_buffer))
		{
			return (FALSE);
		}
		update_offset(output_buffer);

		length = (t_size) (output_buffer->format ? 2 : 1);
		output_pointer = ensure(output_buffer, length);
		if (output_pointer == NULL)
		{
			return (FALSE);
		}
		*output_pointer++ = ':';
		if (output_buffer->format)
		{
			*output_pointer++ = '\t';
		}
		output_buffer->offset += length;

		/* print value */
		if (!print_value(current_item, output_buffer))
		{
			return (FALSE);
		}
		update_offset(output_buffer);

		/* print comma if not last */
		length = ((t_size)(output_buffer->format ? 1 : 0) + (t_size)(current_item->next ? 1 : 0));
		output_pointer = ensure(output_buffer, length + 1);
		if (output_pointer == NULL)
		{
			return (FALSE);
		}
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
	{
		return (FALSE);
	}
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

/* Get Array size/item / object item. */
t_sint	JSON_GetArraySize(s_json const* array)
{
	s_json* child = NULL;
	t_size size = 0;

	if (array == NULL)
	{
		return (0);
	}

	child = array->child;

	while(child != NULL)
	{
		size++;
		child = child->next;
	}

	/* FIXME: Can overflow here. Cannot be fixed without breaking the API */

	return (t_sint)size;
}

static s_json* get_array_item(s_json const* array, t_size index)
{
	s_json* current_child = NULL;

	if (array == NULL)
	{
		return (NULL);
	}

	current_child = array->child;
	while ((current_child != NULL) && (index > 0))
	{
		index--;
		current_child = current_child->next;
	}

	return (current_child);
}

s_json*	JSON_GetArrayItem(s_json const* array, t_sint index)
{
	if (index < 0)
	{
		return (NULL);
	}

	return (get_array_item(array, (t_size)index));
}

static s_json* get_object_item(s_json const* const object, const char* const name, const t_bool case_sensitive)
{
	s_json* current_element = NULL;

	if ((object == NULL) || (name == NULL))
	{
		return (NULL);
	}

	current_element = object->child;
	if (case_sensitive)
	{
		while ((current_element != NULL) && (current_element->string != NULL) && (strcmp(name, current_element->string) != 0))
		{
			current_element = current_element->next;
		}
	}
	else
	{
		while ((current_element != NULL) && (String_Compare_IgnoreCase((const t_char*)name, (const t_char*)(current_element->string)) != 0))
		{
			current_element = current_element->next;
		}
	}

	if ((current_element == NULL) || (current_element->string == NULL)) {
		return (NULL);
	}

	return (current_element);
}

s_json*	JSON_GetObjectItem(s_json const* const object, const char* const string)
{
	return (get_object_item(object, string, FALSE));
}

s_json*	JSON_GetObjectItemCaseSensitive(s_json const* const object, const char* const string)
{
	return (get_object_item(object, string, TRUE));
}

t_bool	JSON_HasObjectItem(s_json const* object, const char* string)
{
	return (JSON_GetObjectItem(object, string) ? 1 : 0);
}

/* Utility for array list handling. */
static void suffix_object(s_json* prev, s_json* item)
{
	prev->next = item;
	item->prev = prev;
}

/* Utility for handling references. */
static s_json* create_reference(s_json const* item, s_json_hooks const* const hooks)
{
	s_json* reference = NULL;
	if (item == NULL)
	{
		return (NULL);
	}

	reference = JSON_New_Item(hooks);
	if (reference == NULL)
	{
		return (NULL);
	}

	Memory_Copy(reference, item, sizeof(s_json));
	reference->string = NULL;
	reference->type |= JSON_IsReference;
	reference->next = reference->prev = NULL;
	return (reference);
}

static t_bool add_item_to_array(s_json* array, s_json* item)
{
	s_json* child = NULL;

	if ((item == NULL) || (array == NULL) || (array == item))
	{
		return (FALSE);
	}

	child = array->child;
	/*
	 * To find the last item in array quickly, we use prev in array
	 */
	if (child == NULL)
	{
		/* list is empty, start new one */
		array->child = item;
		item->prev = item;
		item->next = NULL;
	}
	else
	{
		/* append to the end */
		if (child->prev)
		{
			suffix_object(child->prev, item);
			array->child->prev = item;
		}
	}

	return (TRUE);
}

/* Add item to array/object. */
t_bool	JSON_AddItemToArray(s_json* array, s_json* item)
{
	return (add_item_to_array(array, item));
}

#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
	#pragma GCC diagnostic push
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
/* helper function to cast away const */
static void* cast_away_const(const void* string)
{
	return (void*)string;
}
#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
	#pragma GCC diagnostic pop
#endif


static t_bool add_item_to_object(s_json* const object, const char* const string, s_json* const item, s_json_hooks const* const hooks, const t_bool constant_key)
{
	char* new_key = NULL;
	t_sint new_type = JSON_Invalid;

	if ((object == NULL) || (string == NULL) || (item == NULL) || (object == item))
	{
		return (FALSE);
	}

	if (constant_key)
	{
		new_key = (char*)cast_away_const(string);
		new_type = item->type | JSON_StringIsConst;
	}
	else
	{
		new_key = (char*)JSON_strdup((const t_char*)string, hooks);
		if (new_key == NULL)
		{
			return (FALSE);
		}

		new_type = item->type & ~JSON_StringIsConst;
	}

	if (!(item->type & JSON_StringIsConst) && (item->string != NULL))
	{
		hooks->deallocate(item->string);
	}

	item->string = new_key;
	item->type = new_type;

	return (add_item_to_array(object, item));
}

t_bool	JSON_AddItemToObject(s_json* object, const char* string, s_json* item)
{
	return (add_item_to_object(object, string, item, &global_hooks, FALSE));
}

/* Add an item to an object with constant string as key */
t_bool	JSON_AddItemToObjectCS(s_json* object, const char* string, s_json* item)
{
	return (add_item_to_object(object, string, item, &global_hooks, TRUE));
}

t_bool	JSON_AddItemReferenceToArray(s_json* array, s_json* item)
{
	if (array == NULL)
	{
		return (FALSE);
	}

	return (add_item_to_array(array, create_reference(item, &global_hooks)));
}

t_bool	JSON_AddItemReferenceToObject(s_json* object, const char* string, s_json* item)
{
	if ((object == NULL) || (string == NULL))
	{
		return (FALSE);
	}

	return (add_item_to_object(object, string, create_reference(item, &global_hooks), &global_hooks, FALSE));
}

s_json*	JSON_AddNullToObject(s_json* const object, const char* const name)
{
	s_json* null = JSON_CreateNull();
	if (add_item_to_object(object, name, null, &global_hooks, FALSE))
	{
		return (null);
	}

	JSON_Delete(null);
	return (NULL);
}

s_json*	JSON_AddTrueToObject(s_json* const object, const char* const name)
{
	s_json* TRUE_item = JSON_CreateTrue();
	if (add_item_to_object(object, name, TRUE_item, &global_hooks, FALSE))
	{
		return (TRUE_item);
	}

	JSON_Delete(TRUE_item);
	return (NULL);
}

s_json*	JSON_AddFalseToObject(s_json* const object, const char* const name)
{
	s_json* FALSE_item = JSON_CreateFalse();
	if (add_item_to_object(object, name, FALSE_item, &global_hooks, FALSE))
	{
		return (FALSE_item);
	}

	JSON_Delete(FALSE_item);
	return (NULL);
}

s_json*	JSON_AddBoolToObject(s_json* const object, const char* const name, const t_bool boolean)
{
	s_json* bool_item = JSON_CreateBool(boolean);
	if (add_item_to_object(object, name, bool_item, &global_hooks, FALSE))
	{
		return (bool_item);
	}

	JSON_Delete(bool_item);
	return (NULL);
}

s_json*	JSON_AddNumberToObject(s_json* const object, const char* const name, const t_f64 number)
{
	s_json* number_item = JSON_CreateNumber(number);
	if (add_item_to_object(object, name, number_item, &global_hooks, FALSE))
	{
		return (number_item);
	}

	JSON_Delete(number_item);
	return (NULL);
}

s_json*	JSON_AddStringToObject(s_json* const object, const char* const name, const char* const string)
{
	s_json* string_item = JSON_CreateString(string);
	if (add_item_to_object(object, name, string_item, &global_hooks, FALSE))
	{
		return (string_item);
	}

	JSON_Delete(string_item);
	return (NULL);
}

s_json*	JSON_AddRawToObject(s_json* const object, const char* const name, const char* const raw)
{
	s_json* raw_item = JSON_CreateRaw(raw);
	if (add_item_to_object(object, name, raw_item, &global_hooks, FALSE))
	{
		return (raw_item);
	}

	JSON_Delete(raw_item);
	return (NULL);
}

s_json*	JSON_AddObjectToObject(s_json* const object, const char* const name)
{
	s_json* object_item = JSON_CreateObject();
	if (add_item_to_object(object, name, object_item, &global_hooks, FALSE))
	{
		return (object_item);
	}

	JSON_Delete(object_item);
	return (NULL);
}

s_json*	JSON_AddArrayToObject(s_json* const object, const char* const name)
{
	s_json* array = JSON_CreateArray();
	if (add_item_to_object(object, name, array, &global_hooks, FALSE))
	{
		return (array);
	}

	JSON_Delete(array);
	return (NULL);
}

s_json*	JSON_DetachItemViaPointer(s_json* parent, s_json* const item)
{
	if ((parent == NULL) || (item == NULL))
	{
		return (NULL);
	}

	if (item != parent->child)
	{
		/* not the first element */
		item->prev->next = item->next;
	}
	if (item->next != NULL)
	{
		/* not the last element */
		item->next->prev = item->prev;
	}

	if (item == parent->child)
	{
		/* first element */
		parent->child = item->next;
	}
	else if (item->next == NULL)
	{
		/* last element */
		parent->child->prev = item->prev;
	}

	/* make sure the detached item doesn't point anywhere anymore */
	item->prev = NULL;
	item->next = NULL;

	return (item);
}

s_json*	JSON_DetachItemFromArray(s_json* array, t_sint which)
{
	if (which < 0)
	{
		return (NULL);
	}

	return (JSON_DetachItemViaPointer(array, get_array_item(array, (t_size)which)));
}

void	JSON_DeleteItemFromArray(s_json* array, t_sint which)
{
	JSON_Delete(JSON_DetachItemFromArray(array, which));
}

s_json*	JSON_DetachItemFromObject(s_json* object, const char* string)
{
	s_json* to_detach = JSON_GetObjectItem(object, string);

	return (JSON_DetachItemViaPointer(object, to_detach));
}

s_json*	JSON_DetachItemFromObjectCaseSensitive(s_json* object, const char* string)
{
	s_json* to_detach = JSON_GetObjectItemCaseSensitive(object, string);

	return (JSON_DetachItemViaPointer(object, to_detach));
}

void	JSON_DeleteItemFromObject(s_json* object, const char* string)
{
	JSON_Delete(JSON_DetachItemFromObject(object, string));
}

void	JSON_DeleteItemFromObjectCaseSensitive(s_json* object, const char* string)
{
	JSON_Delete(JSON_DetachItemFromObjectCaseSensitive(object, string));
}

/* Replace array/object items with new ones. */
t_bool	JSON_InsertItemInArray(s_json* array, t_sint which, s_json* newitem)
{
	s_json* after_inserted = NULL;

	if (which < 0)
	{
		return (FALSE);
	}

	after_inserted = get_array_item(array, (t_size)which);
	if (after_inserted == NULL)
	{
		return (add_item_to_array(array, newitem));
	}

	newitem->next = after_inserted;
	newitem->prev = after_inserted->prev;
	after_inserted->prev = newitem;
	if (after_inserted == array->child)
	{
		array->child = newitem;
	}
	else
	{
		newitem->prev->next = newitem;
	}
	return (TRUE);
}

t_bool	JSON_ReplaceItemViaPointer(s_json* const parent, s_json* const item, s_json * replacement)
{
	if ((parent == NULL) || (replacement == NULL) || (item == NULL))
	{
		return (FALSE);
	}

	if (replacement == item)
	{
		return (TRUE);
	}

	replacement->next = item->next;
	replacement->prev = item->prev;

	if (replacement->next != NULL)
	{
		replacement->next->prev = replacement;
	}
	if (parent->child == item)
	{
		if (parent->child->prev == parent->child)
		{
			replacement->prev = replacement;
		}
		parent->child = replacement;
	}
	else
	{   /*
		 * To find the last item in array quickly, we use prev in array.
		 * We can't modify the last item's next pointer where this item was the parent's child
		 */
		if (replacement->prev != NULL)
		{
			replacement->prev->next = replacement;
		}
		if (replacement->next == NULL)
		{
			parent->child->prev = replacement;
		}
	}

	item->next = NULL;
	item->prev = NULL;
	JSON_Delete(item);

	return (TRUE);
}

t_bool	JSON_ReplaceItemInArray(s_json* array, t_sint which, s_json* newitem)
{
	if (which < 0)
	{
		return (FALSE);
	}

	return (JSON_ReplaceItemViaPointer(array, get_array_item(array, (t_size)which), newitem));
}

static t_bool replace_item_in_object(s_json* object, const char* string, s_json* replacement, t_bool case_sensitive)
{
	if ((replacement == NULL) || (string == NULL))
	{
		return (FALSE);
	}

	/* replace the name in the replacement */
	if (!(replacement->type & JSON_StringIsConst) && (replacement->string != NULL))
	{
		Memory_Free(replacement->string);
	}
	replacement->string = (char*)JSON_strdup((const t_char*)string, &global_hooks);
	replacement->type &= ~JSON_StringIsConst;

	return (JSON_ReplaceItemViaPointer(object, get_object_item(object, string, case_sensitive), replacement));
}

t_bool	JSON_ReplaceItemInObject(s_json* object, const char* string, s_json* newitem)
{
	return (replace_item_in_object(object, string, newitem, FALSE));
}

t_bool	JSON_ReplaceItemInObjectCaseSensitive(s_json* object, const char* string, s_json* newitem)
{
	return (replace_item_in_object(object, string, newitem, TRUE));
}

/* Create basic types: */
s_json*	JSON_CreateNull(void)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_NULL;
	}

	return (item);
}

s_json*	JSON_CreateTrue(void)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_True;
	}

	return (item);
}

s_json*	JSON_CreateFalse(void)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_False;
	}

	return (item);
}

s_json*	JSON_CreateBool(t_bool boolean)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = boolean ? JSON_True : JSON_False;
	}

	return (item);
}

s_json*	JSON_CreateNumber(t_f64 num)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_Number;
		item->value_double = num;

		/* use saturation in case of overflow */
		if (num >= INT_MAX)
		{
			item->valueint = INT_MAX;
		}
		else if (num <= (t_f64)INT_MIN)
		{
			item->valueint = INT_MIN;
		}
		else
		{
			item->valueint = (t_sint)num;
		}
	}

	return (item);
}

s_json*	JSON_CreateString(const char* string)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_String;
		item->value_string = (char*)JSON_strdup((const t_char*)string, &global_hooks);
		if(!item->value_string)
		{
			JSON_Delete(item);
			return (NULL);
		}
	}

	return (item);
}

s_json*	JSON_CreateStringReference(const char* string)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if (item != NULL)
	{
		item->type = JSON_String | JSON_IsReference;
		item->value_string = (char*)cast_away_const(string);
	}

	return (item);
}

s_json*	JSON_CreateObjectReference(s_json const* child)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if (item != NULL) {
		item->type = JSON_Object | JSON_IsReference;
		item->child = (s_json*)cast_away_const(child);
	}

	return (item);
}

s_json*	JSON_CreateArrayReference(s_json const* child) {
	s_json* item = JSON_New_Item(&global_hooks);
	if (item != NULL) {
		item->type = JSON_Array | JSON_IsReference;
		item->child = (s_json*)cast_away_const(child);
	}

	return (item);
}

s_json*	JSON_CreateRaw(const char* raw)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type = JSON_Raw;
		item->value_string = (char*)JSON_strdup((const t_char*)raw, &global_hooks);
		if(!item->value_string)
		{
			JSON_Delete(item);
			return (NULL);
		}
	}

	return (item);
}

s_json*	JSON_CreateArray(void)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if(item)
	{
		item->type=JSON_Array;
	}

	return (item);
}

s_json*	JSON_CreateObject(void)
{
	s_json* item = JSON_New_Item(&global_hooks);
	if (item)
	{
		item->type = JSON_Object;
	}

	return (item);
}

/* Create Arrays: */
s_json*	JSON_CreateIntArray(const t_sint *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
	{
		return (NULL);
	}

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber(numbers[i]);
		if (!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if(!i)
		{
			a->child = n;
		}
		else
		{
			suffix_object(p, n);
		}
		p = n;
	}

	if (a && a->child) {
		a->child->prev = n;
	}

	return (a);
}

s_json*	JSON_CreateFloatArray(const t_f32 *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
	{
		return (NULL);
	}

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber((t_f64)numbers[i]);
		if(!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if(!i)
		{
			a->child = n;
		}
		else
		{
			suffix_object(p, n);
		}
		p = n;
	}

	if (a && a->child) {
		a->child->prev = n;
	}

	return (a);
}

s_json*	JSON_CreateDoubleArray(const t_f64 *numbers, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (numbers == NULL))
	{
		return (NULL);
	}

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateNumber(numbers[i]);
		if(!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if(!i)
		{
			a->child = n;
		}
		else
		{
			suffix_object(p, n);
		}
		p = n;
	}

	if (a && a->child) {
		a->child->prev = n;
	}

	return (a);
}

s_json*	JSON_CreateStringArray(const char* const *strings, t_sint count)
{
	t_size i = 0;
	s_json* n = NULL;
	s_json* p = NULL;
	s_json* a = NULL;

	if ((count < 0) || (strings == NULL))
	{
		return (NULL);
	}

	a = JSON_CreateArray();

	for (i = 0; a && (i < (t_size)count); i++)
	{
		n = JSON_CreateString(strings[i]);
		if(!n)
		{
			JSON_Delete(a);
			return (NULL);
		}
		if(!i)
		{
			a->child = n;
		}
		else
		{
			suffix_object(p,n);
		}
		p = n;
	}

	if (a && a->child) {
		a->child->prev = n;
	}
	
	return (a);
}

/* Duplication */
s_json*	JSON_Duplicate(s_json const* item, t_bool recurse)
{
	s_json* newitem = NULL;
	s_json* child = NULL;
	s_json* next = NULL;
	s_json* newchild = NULL;

	/* Bail on bad ptr */
	if (!item)
	{
		goto fail;
	}
	/* Create new item */
	newitem = JSON_New_Item(&global_hooks);
	if (!newitem)
	{
		goto fail;
	}
	/* Copy over all vars */
	newitem->type = item->type & (~JSON_IsReference);
	newitem->value_double = item->value_double;
	if (item->value_string)
	{
		newitem->value_string = (char*)JSON_strdup((t_char*)item->value_string, &global_hooks);
		if (!newitem->value_string)
		{
			goto fail;
		}
	}
	if (item->string)
	{
		newitem->string = (item->type&JSON_StringIsConst) ? item->string : (char*)JSON_strdup((t_char*)item->string, &global_hooks);
		if (!newitem->string)
		{
			goto fail;
		}
	}
	/* If non-recursive, then we're done! */
	if (!recurse)
	{
		return (newitem);
	}
	/* Walk the ->next chain for the child. */
	child = item->child;
	while (child != NULL)
	{
		newchild = JSON_Duplicate(child, TRUE); /* Duplicate (with recurse) each item in the ->next chain */
		if (!newchild)
		{
			goto fail;
		}
		if (next != NULL)
		{
			/* If newitem->child already set, then crosswire ->prev and ->next and move on */
			next->next = newchild;
			newchild->prev = next;
			next = newchild;
		}
		else
		{
			/* Set newitem->child and move to it */
			newitem->child = newchild;
			next = newchild;
		}
		child = child->next;
	}
	if (newitem && newitem->child)
	{
		newitem->child->prev = newchild;
	}

	return (newitem);

fail:
	if (newitem != NULL)
	{
		JSON_Delete(newitem);
	}

	return (NULL);
}

static void skip_oneline_comment(char* *input)
{
	*input += STRING_LENGTH("//");

	for (; (*input)[0] != '\0'; ++(*input))
	{
		if ((*input)[0] == '\n') {
			*input += STRING_LENGTH("\n");
			return;
		}
	}
}

static void skip_multiline_comment(char* *input)
{
	*input += STRING_LENGTH("/*");

	for (; (*input)[0] != '\0'; ++(*input))
	{
		if (((*input)[0] == '*') && ((*input)[1] == '/'))
		{
			*input += STRING_LENGTH("*/");
			return;
		}
	}
}

static void minify_string(char* *input, char* *output) {
	(*output)[0] = (*input)[0];
	*input += STRING_LENGTH("\"");
	*output += STRING_LENGTH("\"");


	for (; (*input)[0] != '\0'; (void)++(*input), ++(*output)) {
		(*output)[0] = (*input)[0];

		if ((*input)[0] == '\"') {
			(*output)[0] = '\"';
			*input += STRING_LENGTH("\"");
			*output += STRING_LENGTH("\"");
			return;
		} else if (((*input)[0] == '\\') && ((*input)[1] == '\"')) {
			(*output)[1] = (*input)[1];
			*input += STRING_LENGTH("\"");
			*output += STRING_LENGTH("\"");
		}
	}
}

void	JSON_Minify(char* json)
{
	char* into = json;

	if (json == NULL)
	{
		return;
	}

	while (json[0] != '\0')
	{
		switch (json[0])
		{
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				json++;
				break;

			case '/':
				if (json[1] == '/')
				{
					skip_oneline_comment(&json);
				}
				else if (json[1] == '*')
				{
					skip_multiline_comment(&json);
				} else {
					json++;
				}
				break;

			case '\"':
				minify_string(&json, (char**)&into);
				break;

			default:
				into[0] = json[0];
				json++;
				into++;
		}
	}

	/* and null-terminate. */
	*into = '\0';
}

t_bool	JSON_IsInvalid(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_Invalid;
}

t_bool	JSON_IsFalse(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_False;
}

t_bool	JSON_IsTrue(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & 0xff) == JSON_True;
}


t_bool	JSON_IsBool(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & (JSON_True | JSON_False)) != 0;
}
t_bool	JSON_IsNull(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_NULL;
}

t_bool	JSON_IsNumber(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_Number;
}

t_bool	JSON_IsString(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_String;
}

t_bool	JSON_IsArray(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_Array;
}

t_bool	JSON_IsObject(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_Object;
}

t_bool	JSON_IsRaw(s_json const* const item)
{
	if (item == NULL)
	{
		return (FALSE);
	}

	return (item->type & JSON_TYPE_MASK) == JSON_Raw;
}

t_bool	JSON_Compare(s_json const* const a, s_json const* const b, const t_bool case_sensitive)
{
	if ((a == NULL) || (b == NULL) || ((a->type & JSON_TYPE_MASK) != (b->type & JSON_TYPE_MASK)) || JSON_IsInvalid(a))
	{
		return (FALSE);
	}

	/* check if type is valid */
	switch (a->type & JSON_TYPE_MASK)
	{
		case JSON_False:
		case JSON_True:
		case JSON_NULL:
		case JSON_Number:
		case JSON_String:
		case JSON_Raw:
		case JSON_Array:
		case JSON_Object:
			break;

		default:
			return (FALSE);
	}

	/* identical objects are equal */
	if (a == b)
	{
		return (TRUE);
	}

	switch (a->type & JSON_TYPE_MASK)
	{
		/* in these cases and equal type is enough */
		case JSON_False:
		case JSON_True:
		case JSON_NULL:
			return (TRUE);

		case JSON_Number:
			if (F64_Equals(a->value_double, b->value_double))
			{
				return (TRUE);
			}
			return (FALSE);

		case JSON_String:
		case JSON_Raw:
			if ((a->value_string == NULL) || (b->value_string == NULL))
			{
				return (FALSE);
			}
			if (strcmp(a->value_string, b->value_string) == 0)
			{
				return (TRUE);
			}

			return (FALSE);

		case JSON_Array:
		{
			s_json* a_element = a->child;
			s_json* b_element = b->child;

			for (; (a_element != NULL) && (b_element != NULL);)
			{
				if (!JSON_Compare(a_element, b_element, case_sensitive))
				{
					return (FALSE);
				}

				a_element = a_element->next;
				b_element = b_element->next;
			}

			/* one of the arrays is longer than the other */
			if (a_element != b_element) {
				return (FALSE);
			}

			return (TRUE);
		}

		case JSON_Object:
		{
			s_json* a_element = NULL;
			s_json* b_element = NULL;
			JSON_ArrayForEach(a_element, a)
			{
				/* TODO This has O(n^2) runtime, which is horrible! */
				b_element = get_object_item(b, a_element->string, case_sensitive);
				if (b_element == NULL)
				{
					return (FALSE);
				}

				if (!JSON_Compare(a_element, b_element, case_sensitive))
				{
					return (FALSE);
				}
			}

			/* doing this twice, once on a and b to prevent TRUE comparison if a subset of b
			 * TODO: Do this the proper way, this is just a fix for now */
			JSON_ArrayForEach(b_element, b)
			{
				a_element = get_object_item(a, b_element->string, case_sensitive);
				if (a_element == NULL)
				{
					return (FALSE);
				}

				if (!JSON_Compare(b_element, a_element, case_sensitive))
				{
					return (FALSE);
				}
			}

			return (TRUE);
		}

		default:
			return (FALSE);
	}
}
