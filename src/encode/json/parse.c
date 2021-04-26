
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/encode/json.h"



typedef struct json_parse
{
	t_char const*	content;
	t_size	length;
	t_size	offset;
	t_size	depth; // How deeply nested (in arrays/objects) is the input at the current offset.
}			s_json_parse;



// get a pointer to the buffer at the position
#define buffer_at_offset(buffer) \
	((buffer)->content + (buffer)->offset)

// check if the given size is left to read in a given parse buffer (starting with 1)
#define can_read(buffer, size) \
	((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))

// check if the buffer can be accessed at the given index (starting with 0)
#define can_access_at_index(buffer, index) \
	((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))



//! Utility to jump whitespace and cr/lf
static s_json_parse *buffer_skip_whitespace(s_json_parse* const buffer)
{
	if ((buffer == NULL) || (buffer->content == NULL))
		return (NULL);
	if (!can_access_at_index(buffer, 0))
		return (buffer);
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



//! skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer
static s_json_parse *skip_utf8_bom(s_json_parse* const buffer)
{
	if ((buffer == NULL) || (buffer->content == NULL) || (buffer->offset != 0))
		return (NULL);
	if (can_access_at_index(buffer, 4) && (String_Compare_N((t_char const*)buffer_at_offset(buffer), "\xEF\xBB\xBF", 3) == 0))
	{
		buffer->offset += 3;
	}
	return (buffer);
}



//! Parse the input text to generate a number, and populate the result into item.
static t_bool parse_number(s_json* const item, s_json_parse* const input_buffer)
{
	t_f64 number = 0;
	t_char number_c_string[64];
	t_size i = 0;

	if ((input_buffer == NULL) || (input_buffer->content == NULL))
		return (FALSE);
	// copy the number into a temporary buffer and replace '.' with the decimal point of the current locale (for strtod)
	// This also takes care of '\0' not necessarily being available for marking the end of the input
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
				number_c_string[i] = '.';
				break;

			default:
				goto loop_end;
		}
	}
loop_end:
	number_c_string[i] = '\0';

	number = F64_FromString((t_char const*)number_c_string);
	if (IS_NAN(number_c_string))
		return (FALSE); // parse_error
	item->value.number = number;
	item->type = DYNAMIC_TYPE_FLOAT;
	input_buffer->offset += i;
	return (TRUE);
}

// parse 4 digit hexadecimal number
static t_uint	parse_hex4(t_char const* const input)
{
	t_uint h = 0;
	t_size i = 0;

	for (i = 0; i < 4; i++)
	{
		// parse digit
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
		else // invalid
			return (0);

		if (i < 3)
		{	// shift left to make place for the next nibble
			h = h << 4;
		}
	}
	return (h);
}



// converts a UTF-16 literal to UTF-8: a literal can be one or two sequences of the form \uXXXX
static t_char utf16_literal_to_utf8(t_char const* const input_pointer, t_char const* const input_end, t_char* *output_pointer)
{
	t_u32	codepoint = 0;
	t_uint	first_code = 0;
	t_char const* first_sequence = input_pointer;
	t_char	utf8_length = 0;
	t_char	utf8_position = 0;
	t_char	sequence_length = 0;
	t_char	first_byte_mark = 0;

	if ((input_end - first_sequence) < 6)
	{
		// input ends unexpectedly
		goto failure;
	}

	// get the first utf16 sequence
	first_code = parse_hex4(first_sequence + 2);

	// check that the code is valid
	if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
	{
		goto failure;
	}

	// UTF16 surrogate pair
	if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
	{
		t_char const* second_sequence = first_sequence + 6;
		t_uint second_code = 0;
		sequence_length = 12; // \uXXXX\uXXXX

		if ((input_end - second_sequence) < 6)
			goto failure; // input ends unexpectedly

		if ((second_sequence[0] != '\\') || (second_sequence[1] != 'u'))
			goto failure; // missing second half of the surrogate pair

		// get the second utf16 sequence
		second_code = parse_hex4(second_sequence + 2);
		// check that the code is valid
		if ((second_code < 0xDC00) || (second_code > 0xDFFF))
			goto failure; // invalid second half of the surrogate pair
		// calculate the unicode codepoint from the surrogate pair
		codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
	}
	else
	{
		sequence_length = 6; // \uXXXX
		codepoint = first_code;
	}
	// encode as UTF-8 -> takes at maximum 4 bytes to encode:
	// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	if (codepoint < 0x80)
	{
		// normal ascii, encoding 0xxxxxxx
		utf8_length = 1;
	}
	else if (codepoint < 0x800)
	{
		// two bytes, encoding 110xxxxx 10xxxxxx
		utf8_length = 2;
		first_byte_mark = (t_char)0xC0; // 11000000
	}
	else if (codepoint < 0x10000)
	{
		// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
		utf8_length = 3;
		first_byte_mark = (t_char)0xE0; // 11100000
	}
	else if (codepoint <= 0x10FFFF)
	{
		// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx
		utf8_length = 4;
		first_byte_mark = (t_char)0xF0; // 11110000
	}
	else
		goto failure; // invalid unicode codepoint

	// encode as utf8
	for (utf8_position = (t_char)(utf8_length - 1); utf8_position > 0; utf8_position--)
	{
		// 10xxxxxx
		(*output_pointer)[(t_sint)utf8_position] = (t_char)((codepoint | 0x80) & 0xBF);
		codepoint >>= 6;
	}
	// encode first byte
	if (utf8_length > 1)
	{
		(*output_pointer)[0] = (t_char)((codepoint | first_byte_mark) & DYNAMIC_TYPE_MASK);
	}
	else
	{
		(*output_pointer)[0] = (t_char)(codepoint & 0x7F);
	}

	*output_pointer += utf8_length;
	return (sequence_length);

failure:
	return (0);
}



// Parse the input text into an unescaped cinput, and populate item.
static t_bool parse_string(s_json* const item, s_json_parse* const input_buffer)
{
	t_char const* input_pointer = buffer_at_offset(input_buffer) + 1;
	t_char const* input_end = buffer_at_offset(input_buffer) + 1;
	t_char* output_pointer = NULL;
	t_char* output = NULL;

	// not a string
	if (buffer_at_offset(input_buffer)[0] != '\"')
	{
		goto failure;
	}

	{
		// calculate approximate size of the output (overestimate)
		t_size allocation_length = 0;
		t_size skipped_bytes = 0;
		while (((t_size)(input_end - input_buffer->content) < input_buffer->length) && (*input_end != '\"'))
		{
			// is escape sequence
			if (input_end[0] == '\\')
			{
				if ((t_size)(input_end + 1 - input_buffer->content) >= input_buffer->length)
				{
					// prevent buffer overflow when last input character is a backslash
					goto failure;
				}
				skipped_bytes++;
				input_end++;
			}
			input_end++;
		}
		if (((t_size)(input_end - input_buffer->content) >= input_buffer->length) || (*input_end != '\"'))
		{
			goto failure; // string ended unexpectedly
		}

		// This is at most how much we need for the output
		allocation_length = (t_size) (input_end - buffer_at_offset(input_buffer)) - skipped_bytes;
		output = (t_char*)Memory_Alloc(allocation_length + sizeof(""));
		if (output == NULL)
		{
			goto failure; // allocation failure
		}
	}

	output_pointer = output;
	// loop through the string literal
	while (input_pointer < input_end)
	{
		if (*input_pointer != '\\')
		{
			*output_pointer++ = *input_pointer++;
		}
		// escape sequence
		else
		{
			t_char sequence_length = 2;
			if ((input_end - input_pointer) < 1)
			{
				goto failure;
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

				// UTF-16 literal
				case 'u':
					sequence_length = utf16_literal_to_utf8(input_pointer, input_end, &output_pointer);
					if (sequence_length == 0)
					{
						// failed to convert UTF16-literal to UTF-8
						goto failure;
					}
					break;

				default:
					goto failure;
			}
			input_pointer += sequence_length;
		}
	}

	// zero terminate the output
	*output_pointer = '\0';

	item->type = DYNAMIC_TYPE_STRING;
	item->value.string = (t_char*)output;

	input_buffer->offset = (t_size) (input_end - input_buffer->content);
	input_buffer->offset++;
	return (TRUE);

failure:
	if (output != NULL)
	{
		Memory_Free(output);
	}
	if (input_pointer != NULL)
	{
		input_buffer->offset = (t_size)(input_pointer - input_buffer->content);
	}
	return (FALSE);
}



static t_bool parse_array(s_json* const item, s_json_parse* const input_buffer);
static t_bool parse_object(s_json* const item, s_json_parse* const input_buffer);



static t_bool parse_value(s_json* const item, s_json_parse* const input_buffer)
{
	if ((input_buffer == NULL) || (input_buffer->content == NULL))
		return (FALSE); // no input

	// parse the different types of values
	if (can_read(input_buffer, 4) && (
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "null", 4) ||
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "NULL", 4)))
	{	// null
		item->type = DYNAMIC_TYPE_NULL;
		input_buffer->offset += 4;
		return (TRUE);
	}
	if (can_read(input_buffer, 5) && (
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "false", 5) &&
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "FALSE", 5)))
	{	// FALSE
		item->type = DYNAMIC_TYPE_BOOLEAN;
		item->value.boolean = FALSE;
		input_buffer->offset += 5;
		return (TRUE);
	}
	if (can_read(input_buffer, 4) && (
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "true", 4) &&
		String_Equals_N((t_char const*)buffer_at_offset(input_buffer), "TRUE", 4)))
	{	// TRUE
		item->type = DYNAMIC_TYPE_BOOLEAN;
		item->value.boolean = TRUE;
		input_buffer->offset += 4;
		return (TRUE);
	}
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
	{	// string
		return (parse_string(item, input_buffer));
	}
	if (can_access_at_index(input_buffer, 0) && ((buffer_at_offset(input_buffer)[0] == '-') ||
		((buffer_at_offset(input_buffer)[0] >= '0') && (buffer_at_offset(input_buffer)[0] <= '9'))))
	{	// number
		return (parse_number(item, input_buffer));
	}
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
	{	// array
		return (parse_array(item, input_buffer));
	}
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
	{	// object
		return (parse_object(item, input_buffer));
	}
	return (FALSE);
}



static t_bool parse_array(s_json* const item, s_json_parse* const input_buffer)
{
	s_json* head = NULL; // head of the linked list
	s_json* current_item = NULL;

	if (input_buffer->depth >= KVT_NESTING_LIMIT)
		return (FALSE); // too deeply nested
	input_buffer->depth++;

	if (buffer_at_offset(input_buffer)[0] != '[')
	{	// not an array
		goto failure;
	}
	input_buffer->offset++;
	buffer_skip_whitespace(input_buffer);
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ']'))
	{	// empty array
		goto success;
	}
	// check if we skipped to the end of the buffer
	if (!can_access_at_index(input_buffer, 0))
	{
		input_buffer->offset--;
		goto failure;
	}

	// step back to character in front of the first element
	input_buffer->offset--;
	// loop through the comma separated array elements
	do
	{
		// allocate next item
		s_json* new_item = JSON_Item();
		if (new_item == NULL)
		{
			goto failure; // allocation failure
		}

		// attach next item to list
		if (head == NULL)
		{
			// start the linked list
			current_item = head = new_item;
		}
		else
		{
			// add to the end and advance
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}

		// parse next value
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_value(current_item, input_buffer))
		{
			goto failure; // failed to parse value
		}
		buffer_skip_whitespace(input_buffer);
	}
	while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

	if (!can_access_at_index(input_buffer, 0) || buffer_at_offset(input_buffer)[0] != ']')
	{
		goto failure; // expected end of array
	}

success:
	input_buffer->depth--;

	if (head != NULL)
	{
		head->prev = current_item;
	}

	item->type = DYNAMIC_TYPE_ARRAY;
	item->value.child = head;

	input_buffer->offset++;
	return (TRUE);

failure:
	if (head != NULL)
	{
		JSON_Delete(head);
	}
	return (FALSE);
}



static t_bool parse_object(s_json* const item, s_json_parse* const input_buffer)
{
	s_json* head = NULL; // linked list head
	s_json* current_item = NULL;

	if (input_buffer->depth >= KVT_NESTING_LIMIT)
		return (FALSE); // to deeply nested
	input_buffer->depth++;

	if (!can_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '{'))
	{
		goto failure; // not an object
	}

	input_buffer->offset++;
	buffer_skip_whitespace(input_buffer);
	if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '}'))
	{
		goto success; // empty object
	}
	// check if we skipped to the end of the buffer
	if (!can_access_at_index(input_buffer, 0))
	{
		input_buffer->offset--;
		goto failure;
	}

	// step back to character in front of the first element
	input_buffer->offset--;
	// loop through the comma separated array elements
	do
	{
		// allocate next item
		s_json* new_item = JSON_Item();
		if (new_item == NULL)
		{
			goto failure; // allocation failure
		}
		// attach next item to list
		if (head == NULL)
		{	// start the linked list
			current_item = head = new_item;
		}
		else
		{	// add to the end and advance
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}

		// parse the name of the child
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_string(current_item, input_buffer))
		{
			goto failure; // failed to parse name
		}
		buffer_skip_whitespace(input_buffer);

		// swap value.string and string, because we parsed the name
		current_item->key = current_item->value.string;
		current_item->value.string = NULL;

		if (!can_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != ':'))
		{
			goto failure; // invalid object
		}

		// parse the value
		input_buffer->offset++;
		buffer_skip_whitespace(input_buffer);
		if (!parse_value(current_item, input_buffer))
		{
			goto failure; // failed to parse value
		}
		buffer_skip_whitespace(input_buffer);
	}
	while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

	if (!can_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '}'))
	{
		goto failure; // expected end of object
	}

failure:
	if (head != NULL)
	{
		JSON_Delete(head);
	}
	return (FALSE);

success:
	input_buffer->depth--;

	if (head != NULL)
	{
		head->prev = current_item;
	}

	item->type = DYNAMIC_TYPE_OBJECT;
	item->value.child = head;

	input_buffer->offset++;
	return (TRUE);
}




s_json*	JSON_ParseStrict_N(t_char const* value, t_size buffer_length, t_char const* *return_parse_end, t_bool require_null_terminated)
{
	s_json_parse buffer = { 0 };
	s_json* item = NULL;

	if (value == NULL || 0 == buffer_length)
	{
		goto failure;
	}

	buffer.content = (t_char const*)value;
	buffer.length = buffer_length; 
	buffer.offset = 0;

	item = JSON_Item();
	if (item == NULL)
		goto failure; // memory failure
	if (!parse_value(item, buffer_skip_whitespace(skip_utf8_bom(&buffer))))
		goto failure; // parse failure. ep is set.
	// if we require null-terminated JSON without appended garbage, skip and then check for a null terminator
	if (require_null_terminated)
	{
		buffer_skip_whitespace(&buffer);
		if ((buffer.offset >= buffer.length) || buffer_at_offset(&buffer)[0] != '\0')
		{
			goto failure;
		}
	}
	if (return_parse_end)
	{
		*return_parse_end = (t_char const*)buffer_at_offset(&buffer);
	}
	return (item);

failure:
	if (item != NULL)
	{
		JSON_Delete(item);
	}
	if (value != NULL)
	{
		t_size	position = 0;

		if (buffer.offset < buffer.length)
		{
			position = buffer.offset;
		}
		else if (buffer.length > 0)
		{
			position = buffer.length - 1;
		}
		if (return_parse_end != NULL)
		{
			*return_parse_end = (t_char const*)value + position;
		}
	}
	return (NULL);
}

s_json*	JSON_ParseStrict(t_char const* value, t_char const* *return_parse_end, t_bool require_null_terminated)
{
	t_size buffer_length;

	if (NULL == value)
		return (NULL);

	// Adding null character size due to require_null_terminated.
	buffer_length = String_Length(value) + sizeof("");
	return (JSON_ParseStrict_N(value, buffer_length, return_parse_end, require_null_terminated));
}

// Default options for JSON_Parse
s_json*	JSON_Parse(t_char const* value)
{
	return (JSON_ParseStrict(value, 0, 0));
}

s_json*	JSON_Parse_N(t_char const* value, t_size buffer_length)
{
	return (JSON_ParseStrict_N(value, buffer_length, 0, 0));
}
