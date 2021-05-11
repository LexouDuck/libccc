
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/sys/io.h"
#include "libccc/encode/json.h"



typedef struct json_parse
{
	s_json*			result;		//!< the result JSON
	t_utf8 const*	content;	//!< the string to parse
	t_size			length;		//!< the length of the string to parse
	t_bool			strict;		//!< if TRUE, strict parsing mode is on (rigourously follows the spec)
	t_size			offset;		//!< current parsing offset
	t_uint			depth;		//!< current section nesting level
	t_size			line;		//!< current line number
	t_char*			error;		//!< current error message (or NULL if no error has been thrown yet)
}			s_json_parse;



static t_bool JSON_Parse_Value(s_json* const item, s_json_parse* const p);
static t_bool JSON_Parse_Number(s_json* const item, s_json_parse* const p);
static t_bool JSON_Parse_String(s_json* const item, s_json_parse* const p);
static t_bool JSON_Parse_Array(s_json* const item, s_json_parse* const p);
static t_bool JSON_Parse_Object(s_json* const item, s_json_parse* const p);



#define PARSINGERROR_JSON_MESSAGE	IO_COLOR_FG_RED"JSON PARSE ERROR"IO_RESET":"

//! used to handle errors during parsing
#define PARSINGERROR_JSON(MESSAGE, ...) \
	{																		\
		p->error = String_Format("%s\n"PARSINGERROR_JSON_MESSAGE" "MESSAGE,	\
			(p->error ? p->error : ""), ##__VA_ARGS__);						\
		goto failure;														\
	}																		\

//! Safely checks if the content to parse can be accessed at the given index
#define CAN_PARSE(i) \
	((p->content != NULL) && ((p->offset + i) <= p->length))



static
t_bool	Char_IsSpace_JSON(t_utf32 c)
{
	return ((c == ' ') ||
			(c == '\t') ||
			(c == '\r') ||
			(c == '\n'));
}

//! Utility to jump whitespace and CR/LF
static
s_json_parse*	JSON_Parse_SkipWhiteSpace(s_json_parse* const p, t_bool skip_comments)
{
	t_size i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	while (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '\n')
			p->line += 1;
		if (skip_comments && p->content[p->offset] == '/')
		{
			if (p->content[p->offset] == '*') // multiple-line
			{
				for (i = 0; (p->offset + i < p->length); ++i)
				{
					if (p->content[p->offset + i] == '*')
					{
						++i;
						if (p->content[p->offset + i] == '/')
							break;
					}
				}
				if (p->offset + i == p->length)
					PARSINGERROR_JSON("input ends unexpectedly, expected end of comment block \"*/\"")
				p->offset += i;
			}
			else if (p->content[p->offset] == '/') // single-line
			{
				for (i = 0; (p->offset + i < p->length); ++i)
				{
					if (p->content[p->offset + i] == '\n')
						break;
				}
				p->offset += i;
			}
		}
		if (p->strict ?
			!Char_IsSpace_JSON(p->content[p->offset]) :
			!Char_IsSpace(p->content[p->offset]))
			break;
		p->offset++;
	}
	if (p->offset == p->length)
	{
		p->offset--;
	}
	return (p);

failure:
	return (NULL);
}



//! skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer
static
s_json_parse*	JSON_Parse_SkipUTF8BOM(s_json_parse* const p)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	LIBCONFIG_HANDLE_INDEX2LARGE(NULL, p->offset, p->length)
	if (CAN_PARSE(4) && (String_Compare_N(&p->content[p->offset], UTF8_BOM, 3) == 0))
	{
		p->offset += 3;
	}
	return (p);
}



//! Parse the input text to generate a number, and populate the result into `item`.
static
t_bool		JSON_Parse_Number(s_json* const item, s_json_parse* const p)
{
	t_f64	result;
	t_utf8*	number;
	t_size	length;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	if (p->strict)
	{
		for (length = 0; CAN_PARSE(length); ++length)
		{
			if (Char_IsInCharset(p->content[p->offset + length], "0123456789.+-eE"))
				continue; // decimal floating-point notation
			else break;
		}
	}
	else
	{
		for (length = 0; CAN_PARSE(length); ++length)
		{
			if (p->content[p->offset + length] == '.' ||
				p->content[p->offset + length] == '-' ||
				p->content[p->offset + length] == '+')
				continue;
			if (!Char_IsAlphaNumeric(p->content[p->offset + length]))
				break;
		}
	}
	number = String_Sub(p->content, p->offset, length);
	result = F64_FromString(number);
	if (IS_NAN(result))
		PARSINGERROR_JSON("Could not parse number: \"%s\"", number)
	item->value.number = result;
	item->type = DYNAMIC_TYPE_FLOAT;
	p->offset += length;
	return (TRUE);

failure:
	return (FALSE);
}



// Parse the input text into an unescaped cinput, and populate item.
static t_bool JSON_Parse_String(s_json* const item, s_json_parse* const p)
{
	t_utf8 const* input_pointer = &p->content[p->offset] + 1;
	t_utf8 const* input_end = &p->content[p->offset] + 1;
	t_utf8* output_pointer = NULL;
	t_utf8* output = NULL;
	t_size allocation_length;
	t_size skipped_bytes;
	t_utf32 c;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	// not a string
	if (p->content[p->offset] != '\"')
		PARSINGERROR_JSON("Could not parse string: Expected double-quote char '\"', instead found '%c'", p->content[p->offset])
	// calculate approximate size of the output (overestimate)
	allocation_length = 0;
	skipped_bytes = 0;
	while (((t_size)(input_end - p->content) < p->length) && (*input_end != '\"'))
	{
		// is escape sequence
		if (input_end[0] == '\\')
		{
			if ((t_size)(input_end + 1 - p->content) >= p->length)
				PARSINGERROR_JSON("Could not parse string: Potential buffer-overflow, string ends with backslash")
			skipped_bytes++;
			input_end++;
		}
		input_end++;
	}
	if (((t_size)(input_end - p->content) >= p->length) || (*input_end != '\"'))
		PARSINGERROR_JSON("Could not parse string: Unexpected end of input before closing quote")
	// This is at most how much we need for the output
	allocation_length = (t_size)(input_end - &p->content[p->offset]) - skipped_bytes;
	output = (t_utf8*)Memory_Alloc(allocation_length + sizeof(""));
	if (output == NULL)
		PARSINGERROR_JSON("Could not parse string: Allocation failure")
	output_pointer = output;
	// loop through the string literal
	while (input_pointer < input_end)
	{
		if (*input_pointer == '\\') // escape sequence
		{
			t_utf8 sequence_length = 2;
			if ((input_end - input_pointer) < 1)
				PARSINGERROR_JSON("Could not parse string: Unexpected end of input within string escape sequence")
			switch (input_pointer[1])
			{
				case 'b':	*output_pointer++ = '\b';	break;
				case 'f':	*output_pointer++ = '\f';	break;
				case 'n':	*output_pointer++ = '\n';	break;
				case 'r':	*output_pointer++ = '\r';	break;
				case 't':	*output_pointer++ = '\t';	break;
				case '\"':
				case '\\':
				case '/':
					*output_pointer++ = input_pointer[1];
					break;
				case 'u': // UTF-16 literal
					sequence_length = UTF32_Parse_N(&c, input_pointer, (input_end - input_pointer));
					if (sequence_length == 0)
						PARSINGERROR_JSON("Could not parse string: Failed to convert UTF16-literal to UTF-8")
					output_pointer += UTF32_ToUTF8(output_pointer, c);
					break;
				default:
					PARSINGERROR_JSON("Could not parse string: Invalid string escape sequence encountered: \"\\%c\"", input_pointer[1])
			}
			input_pointer += sequence_length;
		}
		else *output_pointer++ = *input_pointer++;
	}
	// zero terminate the output
	*output_pointer = '\0';
	item->type = DYNAMIC_TYPE_STRING;
	item->value.string = output;
	p->offset = (t_size)(input_end - p->content);
	p->offset++;
	return (TRUE);

failure:
	if (output != NULL)
	{
		Memory_Free(output);
	}
	if (input_pointer != NULL)
	{
		p->offset = (t_size)(input_pointer - p->content);
	}
	return (FALSE);
}



static
t_bool	JSON_Parse_Array(s_json* const item, s_json_parse* const p)
{
	s_json* head = NULL; // head of the linked list
	s_json* current_item = NULL;
	t_uint index;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	if (p->depth >= KVT_NESTING_LIMIT)
		return (FALSE); // too deeply nested
	p->depth++;

	if (p->content[p->offset] != '[')
		PARSINGERROR_JSON("Could not parse array: Expected '[' char to begin array, instead found '%c'", p->content[p->offset])
	p->offset++;
	JSON_Parse_SkipWhiteSpace(p, p->strict);
	if (CAN_PARSE(0) && (p->content[p->offset] == ']'))
		goto success; // empty array
	// check if we skipped to the end of the buffer
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_JSON("Could not parse array: Unexpected end of input after '[' array start char")
	}
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated array elements
	index = 0;
	do
	{
		p->offset++;
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		if (!p->strict && CAN_PARSE(0) && (p->content[p->offset] == ']'))
			goto success; // allow trailing commas when not in strict mode
		// allocate next item
		s_json* new_item = JSON_Item();
		if (new_item == NULL)
			PARSINGERROR_JSON("Could not parse array: Allocation failure")
		// attach next item to list
		if (head == NULL)
		{	// start the linked list
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
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		if (!JSON_Parse_Value(current_item, p))
			PARSINGERROR_JSON("Inside array: failed to parse value within array, at index %u", index)
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		index++;
	}
	while (CAN_PARSE(0) && p->content[p->offset] == ',');

	if (!CAN_PARSE(0))
		PARSINGERROR_JSON("Could not parse array: Unexpected end of end of input within array")
	if (p->content[p->offset] != ']')
		PARSINGERROR_JSON("Could not parse array: Expected end of array ']' char, instead found '%c'", p->content[p->offset])

success:
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMIC_TYPE_ARRAY;
	item->value.child = head;
	p->offset++;
	return (TRUE);

failure:
	if (head != NULL)
	{
		JSON_Delete(head);
	}
	return (FALSE);
}



static
t_bool	JSON_Parse_Object(s_json* const item, s_json_parse* const p)
{
	s_json* head = NULL; // linked list head
	s_json* current_item = NULL;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, p->content)
	if (p->depth >= KVT_NESTING_LIMIT)
		return (FALSE); // reached nesting depth limit
	p->depth++;
	if (!CAN_PARSE(0) || (p->content[p->offset] != '{'))
		PARSINGERROR_JSON("Could not parse object: Expected '{' to begin object, instead found '%c'", p->content[p->offset])
	p->offset++;
	JSON_Parse_SkipWhiteSpace(p, p->strict);
	if (CAN_PARSE(0) && (p->content[p->offset] == '}'))
		goto success; // empty object
	// check if we skipped to the end of the buffer
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_JSON("Could not parse object: Unexpected end of input after '{' object start char")
	}
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated array elements
	do
	{
		p->offset++;
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		if (!p->strict && CAN_PARSE(0) && (p->content[p->offset] == '}'))
			goto success; // allow trailing commas when not in strict mode
		// allocate next item
		s_json* new_item = JSON_Item();
		if (new_item == NULL)
			PARSINGERROR_JSON("Could not parse object: Allocation failure")
		// attach next item to list
		if (head == NULL)
		{	// start the linked list
			head = new_item;
			current_item = new_item;
		}
		else
		{	// add to the end and advance
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}
		// parse the name of the child
		if (!JSON_Parse_String(current_item, p))
			PARSINGERROR_JSON("Could not parse object: Failed to parse object member key")
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		// swap value.string and string, because we parsed the name
		current_item->key = current_item->value.string;
		current_item->value.string = NULL;
		if (!CAN_PARSE(0))
			PARSINGERROR_JSON("Could not parse object: Unexpected end of input after object member key")
		if (p->content[p->offset] != ':')
			PARSINGERROR_JSON("Could not parse object: Invalid object key/value pair, expected ':' char")
		// parse the value
		p->offset++;
		JSON_Parse_SkipWhiteSpace(p, p->strict);
		if (!JSON_Parse_Value(current_item, p))
			PARSINGERROR_JSON("Inside object: Failed to parse object member value (key is \"%s\")", current_item->key)
		JSON_Parse_SkipWhiteSpace(p, p->strict);
	}
	while (CAN_PARSE(0) && (p->content[p->offset] == ','));

	if (!CAN_PARSE(0))
		PARSINGERROR_JSON("Could not parse object: Unexpected end of input within object")
	if (p->content[p->offset] != '}')
		PARSINGERROR_JSON("Could not parse object: Expected end of object char '}', instead found '%c'", p->content[p->offset])

success:
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMIC_TYPE_OBJECT;
	item->value.child = head;
	p->offset++;
	return (TRUE);

failure:
	if (head != NULL)
	{
		JSON_Delete(head);
	}
	return (FALSE);
}



static
t_bool	JSON_Parse_Value(s_json* const item, s_json_parse* const p)
{
	if ((p == NULL) || (p->content == NULL))
	{
		PARSINGERROR_JSON("Unexpected end of input, unable to parse JSON value")
	}
	else if (CAN_PARSE(4) && ((String_Equals_N(p->content + p->offset, "null", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "Null", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "NULL", 4))))
	{	// null
		item->type = DYNAMIC_TYPE_NULL;
//		Memory_Clear(&item->value, sizeof(item->value));
		p->offset += 4;
		return (TRUE);
	}
	else if (CAN_PARSE(5) && ((String_Equals_N(p->content + p->offset, "false", 5)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "False", 5)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "FALSE", 5))))
	{	// FALSE
		item->type = DYNAMIC_TYPE_BOOLEAN;
		item->value.boolean = FALSE;
		p->offset += 5;
		return (TRUE);
	}
	else if (CAN_PARSE(4) && ((String_Equals_N(p->content + p->offset, "true", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "True", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "TRUE", 4))))
	{	// TRUE
		item->type = DYNAMIC_TYPE_BOOLEAN;
		item->value.boolean = TRUE;
		p->offset += 4;
		return (TRUE);
	}
	else if (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '[')
			return (JSON_Parse_Array( item, p));	// array
		if (p->content[p->offset] == '{')
			return (JSON_Parse_Object(item, p));	// object
		if (p->content[p->offset] == '\"')
			return (JSON_Parse_String(item, p));	// string
		if (p->content[p->offset] == '-' || Char_IsDigit(p->content[p->offset]))
			return (JSON_Parse_Number(item, p));	// number
	}

	if (!p->strict)
	{
		if (CAN_PARSE(0))
		{
//			if (p->content[p->offset] == '\'')
//				return (JSON_Parse_String(item, p));	// string
			if (p->content[p->offset] == '+')
				return (JSON_Parse_Number(item, p));	// number
		}
		if (CAN_PARSE(3) && (
			String_Equals_N(p->content + p->offset, "inf", 3) ||
			String_Equals_N(p->content + p->offset, "Inf", 3) ||
			String_Equals_N(p->content + p->offset, "INF", 3)))
		{	// number
			return (JSON_Parse_Number(item, p));
		}
		if (CAN_PARSE(3) && (
			String_Equals_N(p->content + p->offset, "nan", 3) ||
			String_Equals_N(p->content + p->offset, "NaN", 3) ||
			String_Equals_N(p->content + p->offset, "NAN", 3)))
		{	// number
			return (JSON_Parse_Number(item, p));
		}
	}
	PARSINGERROR_JSON("No match, unable to determine the kind of parsing to attempt: \"%.6s\"", p->content + p->offset)

failure:
	return (FALSE);
}



static
s_json*	JSON_Parse_(t_utf8 const* json, t_size buffer_length, t_bool strict, t_utf8 const** return_parse_end)
{
	s_json_parse p = { 0 };
	s_json* result = NULL;

	LIBCONFIG_HANDLE_LENGTH2SMALL(NULL, buffer_length, 1)
	p.content = json;
	p.length = buffer_length; 
	p.offset = 0;
	p.strict = strict;
	result = JSON_Item();
	if (result == NULL)
		goto failure; // memory failure
	if (!JSON_Parse_Value(result, JSON_Parse_SkipWhiteSpace(JSON_Parse_SkipUTF8BOM(&p), !p.strict)))
		goto failure; // parse failure. ep is set.
	if (p.strict)
	{	// if we require null-terminated JSON without appended garbage, skip and then check for a null terminator
		JSON_Parse_SkipWhiteSpace(&p, FALSE);
		if ((p.offset >= p.length) || (&p.content[p.offset])[0] != '\0')
			goto failure;
	}
	if (return_parse_end)
	{
		*return_parse_end = &p.content[p.offset];
	}
	return (result);

failure:
	if (result != NULL)
	{
		JSON_Delete(result);
	}
	if (json != NULL)
	{
		t_size	position = 0;

		if (p.offset < p.length)
			position = p.offset;
		else if (p.length > 0)
			position = p.length - 1;

		if (return_parse_end != NULL)
		{
			*return_parse_end = (json + position);
		}
	}
	t_size column = 0;
	while (p.offset - column != 0)
	{
		if (p.content[p.offset - column] == '\n')
			break;
		column++;
	}
	LIBCONFIG_HANDLE_PARSINGERROR(NULL, "\n"PARSINGERROR_JSON_MESSAGE" at nesting depth %u -> line %zu, column %zu (char index %zu: '%c')%s",
		p.depth, p.line, column, p.offset, p.content[p.offset], p.error)
}



s_json*	JSON_Parse(t_utf8 const* json)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, json)
	return (JSON_Parse_(json, String_Length(json), FALSE, NULL));
}

s_json*	JSON_Parse_N(t_utf8 const* json, t_size maxlength)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, json)
	return (JSON_Parse_(json, maxlength, FALSE, NULL));
}

s_json*	JSON_Parse_Strict(t_utf8 const* json, t_utf8 const** return_parse_end)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, json)
	return (JSON_Parse_(json, String_Length(json), TRUE, return_parse_end));
}

s_json*	JSON_Parse_Strict_N(t_utf8 const* json, t_size maxlength, t_utf8 const** return_parse_end)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, json)
	return (JSON_Parse_(json, maxlength, TRUE, return_parse_end));
}
