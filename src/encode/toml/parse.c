
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/toml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_parse	s_toml_parse;



static t_bool	TOML_Parse_Lines		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_KeyValuePair	(s_toml* item, s_toml_parse* p, s_toml* context);
static t_bool	TOML_Parse_Key			(s_toml* item, s_toml_parse* p, s_toml* context, s_toml* *a_result);
static t_bool	TOML_Parse_Value		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_Table		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_Number		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_String		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_Array		(s_toml* item, s_toml_parse* p);
static t_bool	TOML_Parse_Object		(s_toml* item, s_toml_parse* p);



#define PARSINGERROR_TOML_MESSAGE	IO_COLOR_FG_RED"TOML PARSE ERROR"IO_RESET":"

//! used to handle errors during parsing
#define PARSINGERROR_TOML(...) \
	{																							\
		t_char* tmp_error;																		\
		tmp_error = String_Format(__VA_ARGS__);													\
		tmp_error = String_Prepend("\n"PARSINGERROR_TOML_MESSAGE" ", &tmp_error);				\
		if (p) p->error = (p->error == NULL ? tmp_error : String_Merge(&p->error, &tmp_error));	\
		goto failure;																			\
	}																							\

//! Safely checks if the content to parse can be accessed at the given index
#define CAN_PARSE(X) \
	((p->content != NULL) && ((p->offset + X) <= p->length))



static
t_bool	Char_IsSpace_TOML(t_utf32 c)
{
	return ((c == ' ') ||
			(c == '\t') ||
			(c == '\r') ||
			(c == '\n'));
}

//! Utility to parse over whitespace and newlines
static
s_toml_parse*	TOML_Parse_SkipWhiteSpace(s_toml_parse* p)
{
	t_size i;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (p->content == NULL), return (NULL);)
	while (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '\n')
			p->line += 1;
		if (p->content[p->offset] == ';' ||	// INI comments:	;
			p->content[p->offset] == '#')	// TOML comments:	#
		{
			for (i = 0; (p->offset + i < p->length); ++i)
			{
				if (p->content[p->offset + i] == '\n')
				{
					p->line += 1;
					break;
				}
			}
			p->offset += i;
		}
		if (!p->strict && p->content[p->offset] == '/') // C-style comments (only if not strict mode)
		{
			if (p->content[p->offset] == '*') // multiple-line
			{
				for (i = 0; (p->offset + i < p->length); ++i)
				{
					if (p->content[p->offset + i] == '\n')
					{
						p->line += 1;
					}
					else if (p->content[p->offset + i] == '*')
					{
						++i;
						if (p->content[p->offset + i] == '/')
							break;
					}
				}
				if (p->offset + i == p->length)
					PARSINGERROR_TOML("input ends unexpectedly, expected end of comment block \"*/\"")
				p->offset += i;
			}
			else if (p->content[p->offset] == '/') // single-line
			{
				for (i = 0; (p->offset + i < p->length); ++i)
				{
					if (p->content[p->offset + i] == '\n')
					{
						p->line += 1;
						break;
					}
				}
				p->offset += i;
			}
		}
		if (p->strict ?
			!Char_IsSpace_TOML(p->content[p->offset]) :
			!Char_IsSpace(p->content[p->offset]))
			break;
		p->offset++;
	}
	return (p);

failure:
	return (NULL);
}



/* LEGACY CODE

static t_char*	TOML_Parse_ApplySetting(s_parser *p)
{
	t_s32	index;
	t_s32	i;

	if (*(p->label + p->label_length))
		*(p->label + p->label_length) = '\0';
	i = -1;
	index = -1;
	while (++i < ENUMLENGTH_CONFIG)
		if (p->config[i].label && String_Equals(p->label, p->config[i].label))
			index = i;
	if (index == -1)
	{
		Log_Error(p->logger, 0, "Error while reading INI file, at line %zu\n"LOG_TIMESTAMP_INDENT"Unable to resolve label: %s", p->line, p->label);
		return (NULL);
	}
	if (*(p->value + p->value_length))
		*(p->value + p->value_length) = '\0';
	if (!(p->config[index].value = String_Duplicate(p->value)))
		return ("Could not create config value string");
	return (NULL);
}

static t_char*	TOML_Parse_ReadSetting(s_parser *p)
{
	t_char*	file;

	file = p->file;
	p->label = (p->file + p->offset);
	while (file[p->offset] && !(Char_IsSpace(file[p->offset]) ||
		file[p->offset] == '=' ||
		file[p->offset] == '#' ||
		file[p->offset] == ';'))
		++(p->offset);
	p->label_length = (file + p->offset) - p->label;
	if (file[p->offset] != '=')
		TOML_Parse_SkipWhitespace(p);
	if (file[p->offset] != '=')
		return (TOML_Parse_Error('=', " symbol but instead found ", file[p->offset]));
	++(p->offset);
	TOML_Parse_SkipWhitespace(p);
	if (!file[p->offset])
		return ("Unexpected end of file encountered before value.");
	p->value = (file + p->offset);
	while (file[p->offset] && !Char_IsSpace(file[p->offset]))
		++(p->offset);
	p->value_length = (file + p->offset) - p->value;
	++(p->offset);
	return (TOML_Parse_ApplySetting(p));
}

void		TOML_Parse(t_fd fd, s_config* config, s_logger const* logger)
{
	s_parser	parser;
	t_char*		error;

	parser.config = config;
	parser.file = NULL;
	if (IO_Read_File(fd, &parser.file, CONFIG_FILEBUFFER) < 0)
	{
		Log_Error_IO(logger, errno, "Couldn't read config INI file.");
		return;
	}
	parser.index = 0;
	parser.line = 1;
	TOML_Parse_SkipWhitespace(&parser);
	while (parser.file[parser.index])
	{
		if ((error = TOML_Parse_ReadSetting(&parser)))
		{
			Log_Error(logger, 0, "Error while reading INI file, at line %zu\n"LOG_TIMESTAMP_INDENT"%s",
				parser.line, error);
			String_Delete(&error);
		}
		TOML_Parse_SkipWhitespace(&parser);
	}
	String_Delete(&parser.file);
}
*/



//! Parse the input text to generate a number, and populate the result into `item`.
static
t_bool		TOML_Parse_Number(s_toml* item, s_toml_parse* p)
{
	t_utf8*	number;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (p->content == NULL), return (ERROR);)
	for (length = 0; CAN_PARSE(length); ++length)
	{
		if (p->content[p->offset + length] == '.' ||
			p->content[p->offset + length] == '-' ||
			p->content[p->offset + length] == '+')
			continue;
		if (!Char_IsAlphaNumeric(p->content[p->offset + length]))
			break;
	}
	if (CAN_PARSE(length) && !(Char_IsSpace(p->content[p->offset + length]) ||
		p->content[p->offset + length] == ',' ||
		p->content[p->offset + length] == ']' ||
		p->content[p->offset + length] == '}' ||
		p->content[p->offset + length] == '\0'))
		PARSINGERROR_TOML("Unexpected char in number value: \"%.*s\"", (int)(length + 1), p->content + p->offset)
	number = String_Sub(p->content, p->offset, length);
	if (number == NULL)
		PARSINGERROR_TOML("Could not parse number: \"%.*s\"", (int)length, p->content + p->offset)
	if (String_HasOnly(number, "+-"CHARSET_DIGIT"xob_"))
	{
		t_s64	result = S64_FromString(number); // TODO variable-length integer
		item->type = DYNAMICTYPE_INTEGER;
		item->value.integer = result;
	}
	else
	{
		if (length == 1 && (
			number[0] == '.' ||
			number[0] == '-' ||
			number[0] == '+'))
			PARSINGERROR_TOML("Could not parse number: \"%.2s\", invalid char found", p->content + p->offset)
		t_f64	result = F64_FromString(number);
		item->type = DYNAMICTYPE_FLOAT;
		item->value.number = result;
	}
//	if (IS_NAN(result)) // && String_HasOnly(number, CHARSET_ALPHABET".-+"CHARSET_DIGIT))
//		PARSINGERROR_TOML("Error while parsing number: \"%s\"", number)
	String_Delete(&number);
	p->offset += length;
	return (OK);

failure:
	return (ERROR);
}



static
t_bool	TOML_Parse_String(s_toml* item, s_toml_parse* p)
{
	t_utf8 const* input_ptr = NULL;
	t_utf8 const* input_end = NULL;
	t_utf8* output_ptr = NULL;
	t_utf8* output = NULL;
	t_size skipped_bytes;
	t_char stringtype = 0;
	t_bool is_multiline = FALSE;
	t_utf32 c;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (p->content == NULL), return (ERROR);)
	// not a string
	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse string: Unexpected end of end of input before string")
	if (p->content[p->offset] == '\"')
		stringtype = '\"';
	if (p->content[p->offset] == '\'')
		stringtype = '\'';
	if (!stringtype)
		PARSINGERROR_TOML("Could not parse string: Expected string quote char '\"' or '\'', instead found '%c'/0x%4.4X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	input_ptr = &p->content[p->offset] + 1;
	input_end = &p->content[p->offset] + 1;
	if (CAN_PARSE(1) && p->content[p->offset + 1] == stringtype &&
		CAN_PARSE(2) && p->content[p->offset + 2] == stringtype)
	{
		is_multiline = TRUE;
		input_ptr += 2;
		input_end += 2;
	}
	// calculate approximate size of the output (overestimate)
	skipped_bytes = 0;
	while ((t_size)(input_end - p->content) < p->length)
	{
		// is escape sequence
		if (input_end[0] == '\\')
		{
			// TODO implement newer fixes from JSON_Parse_String() here
			if ((t_size)(input_end + 1 - p->content) >= p->length)
				PARSINGERROR_TOML("Could not parse string: Potential buffer-overflow, string ends with backslash")
			skipped_bytes++;
			input_end++;
		}
		else if (input_end[0] == stringtype)
		{
			if (is_multiline)
			{
				if (CAN_PARSE(1) && input_end[1] == stringtype &&
					CAN_PARSE(2) && input_end[2] == stringtype)
					break;
			}
			else break;
		}
		input_end++;
	}
	if ((t_size)(input_end - p->content) >= p->length)
		PARSINGERROR_TOML("Could not parse string: Unexpected end of input")

	if (!p->strict)
	{
		if ((input_end - input_ptr) == 0)
			output = String_Duplicate("");
		else String_Parse(&output, input_ptr, (input_end - input_ptr), FALSE);
	}
	else
	{
		// This is how many bytes we need for the output, at most
		t_size	alloc_length = (t_size)(input_end - &p->content[p->offset]) - skipped_bytes;
		output = (t_utf8*)Memory_Allocate(alloc_length + sizeof(""));
		if (output == NULL)
			PARSINGERROR_TOML("Could not parse string: Allocation failure")
		output_ptr = output;
		// loop through the string literal
		while (input_ptr < input_end)
		{
			if (*input_ptr == '\\') // escape sequence
			{
				t_utf8 sequence_length = 2;
				if ((input_end - input_ptr) < 1)
					PARSINGERROR_TOML("Could not parse string: Unexpected end of input within string escape sequence")
				switch (input_ptr[1])
				{
					case 'b':	*output_ptr++ = '\b';	break;
					case 't':	*output_ptr++ = '\t';	break;
					case 'n':	*output_ptr++ = '\n';	break;
					case 'f':	*output_ptr++ = '\f';	break;
					case 'r':	*output_ptr++ = '\r';	break;
					case '\"':
					case '\\':
						*output_ptr++ = input_ptr[1];
						break;
					case 'u': // UTF-32 literal TODO ensure 4 hex chars
					case 'U': // UTF-32 literal TODO ensure 8 hex chars
						sequence_length = UTF32_Parse(&c, input_ptr, (input_end - input_ptr));
						if (sequence_length == 0)
							PARSINGERROR_TOML("Could not parse string: Failed to convert UTF16-literal to UTF-8")
						output_ptr += UTF32_ToUTF8(output_ptr, c);
						break;
					default: // TODO non-strict escape sequence handling
						PARSINGERROR_TOML("Could not parse string: Invalid string escape sequence encountered: \"\\%c\"", input_ptr[1])
				}
				input_ptr += sequence_length;
			}
			else *output_ptr++ = *input_ptr++;
		}
		// zero terminate the output
		*output_ptr = '\0';
	}
	item->type = DYNAMICTYPE_STRING;
	item->value.string = output;
	p->offset = (t_size)(input_end - p->content);
	p->offset++;
	return (OK);

failure:
	if (output != NULL)
	{
		Memory_Free(output);
	}
	if (input_ptr != NULL)
	{
		p->offset = (t_size)(input_ptr - p->content);
	}
	return (ERROR);
}



static
t_bool	TOML_Parse_Array(s_toml* item, s_toml_parse* p)
{
	s_toml* head = NULL; // head of the linked list
	s_toml* current_item = NULL;
	t_uint index;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (p->content == NULL), return (ERROR);)
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_TOML("Could not parse TOML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse array: Unexpected end of end of input before array")
	if (p->content[p->offset] != '[')
		PARSINGERROR_TOML("Could not parse array: Expected '[' char to begin array, instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	TOML_Parse_SkipWhiteSpace(p);
	if (CAN_PARSE(0) && (p->content[p->offset] == ']'))
		goto success; // empty array
	// check if we skipped to the end of the buffer
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_TOML("Could not parse array: Unexpected end of input after '[' array start char")
	}
	item->type = DYNAMICTYPE_ARRAY;
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated array elements
	index = 0;
	do
	{
		p->offset++;
		TOML_Parse_SkipWhiteSpace(p);
		if (CAN_PARSE(0) && (p->content[p->offset] == ']'))
			goto success; // allow trailing commas
		// allocate next item
		s_toml* new_item = TOML_Item();
		if (new_item == NULL)
			PARSINGERROR_TOML("Could not parse array: Allocation failure")
		// attach next item to list
		if (head == NULL)
		{	// start the linked list
			head = new_item;
			current_item = new_item;
		}
		else
		{
			// add to the end and advance
			current_item->next = new_item;
			new_item->prev = current_item;
			current_item = new_item;
		}
		// parse next value
		TOML_Parse_SkipWhiteSpace(p);
		if (TOML_Parse_Value(current_item, p))
			PARSINGERROR_TOML("Inside array: failed to parse value within array, at index "SF_UINT, index)
		TOML_Parse_SkipWhiteSpace(p);
		index++;
	}
	while (CAN_PARSE(0) && p->content[p->offset] == ',');

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse array: Unexpected end of end of input within array")
	if (p->content[p->offset] != ']')
		PARSINGERROR_TOML("Could not parse array: Expected end of array ']' char, instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])

success:
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMICTYPE_ARRAY;
	item->value.child = head;
	p->offset++;
	return (OK);

failure:
	if (head != NULL)
	{
		TOML_Delete(head);
		head = NULL;
	}
	return (ERROR);
}



static
t_bool	TOML_Parse_Object(s_toml* item, s_toml_parse* p)
{
	s_toml* head = NULL; // linked list head
	s_toml* current_item = NULL;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (p->content == NULL), return (ERROR);)
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_TOML("Could not parse TOML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;
	if (!CAN_PARSE(0) || (p->content[p->offset] != '{'))
		PARSINGERROR_TOML("Could not parse object: Expected '{' to begin object, instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	TOML_Parse_SkipWhiteSpace(p);
	if (CAN_PARSE(0) && (p->content[p->offset] == '}'))
		goto success; // empty object
	// check if we skipped to the end of the buffer
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_TOML("Could not parse object: Unexpected end of input after '{' object start char")
	}
	item->type = DYNAMICTYPE_OBJECT;
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated array elements
	do
	{
		p->offset++;
		TOML_Parse_SkipWhiteSpace(p);
		if (CAN_PARSE(0) && (p->content[p->offset] == '}'))
			goto success; // allow trailing commas
		// allocate next item
		s_toml* new_item = TOML_Item();
		if (new_item == NULL)
			PARSINGERROR_TOML("Could not parse object: Allocation failure")
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

		if (TOML_Parse_KeyValuePair(current_item, p, item))
			PARSINGERROR_TOML("Could not parse object: Failed to parse inline table member (in item wth key \"%s\")", current_item->key)
		TOML_Parse_SkipWhiteSpace(p);
/*
		// parse the name of the child
		if (TOML_Parse_String(current_item, p))
			PARSINGERROR_TOML("Could not parse object: Failed to parse object member key")
		// swap value.string and string, because we parsed the name
		current_item->key = current_item->value.string;
		current_item->value.string = NULL;
		TOML_Parse_SkipWhiteSpace(p);
		if (!CAN_PARSE(0))
			PARSINGERROR_TOML("Could not parse object: Unexpected end of input after object member key")
		if (p->content[p->offset] != ':')
			PARSINGERROR_TOML("Could not parse object: Invalid object key/value pair, expected ':' char")
		// parse the value
		p->offset++;
		TOML_Parse_SkipWhiteSpace(p);
		if (TOML_Parse_Value(current_item, p))
			PARSINGERROR_TOML("Inside object: Failed to parse object member value (key is \"%s\")", current_item->key)
		TOML_Parse_SkipWhiteSpace(p);
*/
	}
	while (CAN_PARSE(0) && (p->content[p->offset] == ','));

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse object: Unexpected end of input within object")
	if (p->content[p->offset] != '}')
		PARSINGERROR_TOML("Could not parse object: Expected end of object char '}', instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])

success:
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMICTYPE_OBJECT;
	item->value.child = head;
	p->offset++;
	return (OK);

failure:
	if (head != NULL)
	{
		TOML_Delete(head);
		head = NULL;
	}
	return (ERROR);
}



static
t_bool	TOML_Parse_Value(s_toml* item, s_toml_parse* p)
{
	if ((p == NULL) || (p->content == NULL) || !CAN_PARSE(0))
	{
		PARSINGERROR_TOML("Unexpected end of input, unable to parse TOML value")
	}
	else if (CAN_PARSE(4) && ((String_Equals_N(p->content + p->offset, "null", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "Null", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "NULL", 4))))
	{	// null
		item->type = DYNAMICTYPE_NULL;
//		Memory_Clear(&item->value, sizeof(item->value));
		p->offset += 4;
		return (OK);
	}
	else if (CAN_PARSE(5) && ((String_Equals_N(p->content + p->offset, "false", 5)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "False", 5)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "FALSE", 5))))
	{	// FALSE
		item->type = DYNAMICTYPE_BOOLEAN;
		item->value.boolean = FALSE;
		p->offset += 5;
		return (OK);
	}
	else if (CAN_PARSE(4) && ((String_Equals_N(p->content + p->offset, "true", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "True", 4)) ||
				(!p->strict && String_Equals_N(p->content + p->offset, "TRUE", 4))))
	{	// TRUE
		item->type = DYNAMICTYPE_BOOLEAN;
		item->value.boolean = TRUE;
		p->offset += 4;
		return (OK);
	}
	else
	{
		if (p->content[p->offset] == '[')
			return (TOML_Parse_Array( item, p));	// array
		if (p->content[p->offset] == '{')
			return (TOML_Parse_Object(item, p));	// object
		if (p->content[p->offset] == '\"')
			return (TOML_Parse_String(item, p));	// string
		if (p->content[p->offset] == '\'')
			return (TOML_Parse_String(item, p));	// string
		if (Char_IsDigit(p->content[p->offset]))
			return (TOML_Parse_Number(item, p));	// number
		t_bool	sign = FALSE;
		if (p->content[p->offset] == '-' ||
			p->content[p->offset] == '+')
			sign = TRUE;
		if (sign)	p->offset++;

		if (Char_IsDigit(p->content[p->offset]))
		{
			if (sign)	p->offset--;
			return (TOML_Parse_Number(item, p));	// number
		}
		if (CAN_PARSE(3))
		{
			if (Char_IsDigit(p->content[p->offset]))
			{
				if (sign)	p->offset--;
				return (TOML_Parse_Number(item, p));	// number
			}
			else if (p->strict && CAN_PARSE(4) && Char_IsAlphaNumeric(p->content[p->offset + 4]))
			{
				PARSINGERROR_TOML("Any non-numeric value (here: \"%.4s\") must be 3-letter lowercase, in strict TOML", p->content + p->offset)
			}
			
			if (String_Equals_N(p->content + p->offset, "inf", 3) ||
				String_Equals_N(p->content + p->offset, "nan", 3))
			{
				if (sign)	p->offset--;
				return (TOML_Parse_Number(item, p));
			}
			else if (
				String_Equals_N(p->content + p->offset, "Inf", 3) ||
				String_Equals_N(p->content + p->offset, "INF", 3))
			{	// number
				if (p->strict)
					PARSINGERROR_TOML("Any non-numeric value (here, infinity: \"%.3s\") must be 3-letter lowercase, in strict TOML", p->content + p->offset)
				if (sign)	p->offset--;
				return (TOML_Parse_Number(item, p));
			}
			else if (
				String_Equals_N(p->content + p->offset, "NaN", 3) ||
				String_Equals_N(p->content + p->offset, "NAN", 3))
			{	// number
				if (p->strict)
					PARSINGERROR_TOML("Any non-numeric value (here, 'not a number': \"%.3s\") must be 3-letter lowercase, in strict TOML", p->content + p->offset)
				if (sign)	p->offset--;
				return (TOML_Parse_Number(item, p));
			}
		}
		if (sign)	p->offset--;
	}

	if (p->strict && Char_IsSpace(p->content[p->offset]))
	{
		PARSINGERROR_TOML("Non-standard whitespace character used ('%c'/0x%4.4X) which is not allowed in strict TOML",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	}

	PARSINGERROR_TOML("Unable to determine the kind of parsing to attempt: \"%.6s\"", p->content + p->offset)

failure:
	return (ERROR);
}



static
t_bool	TOML_Parse_Key_IsBareKeyChar(t_utf32 c)
{
	return (c == '-' || c == '_' || Char_IsAlphaNumeric(c));
}

static
t_bool	TOML_Parse_Key(s_toml* item, s_toml_parse* p, s_toml* context, s_toml* *a_result)
{
	s_toml*	result = item;
	s_toml*	exists = NULL;
	s_toml* child = NULL;
	s_toml*	tmp = NULL;
	t_char*	key = NULL;

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse key string: Unexpected end of input before key")
	if (item->key)
		PARSINGERROR_TOML("Could not parse key string: Key is already assigned: \"%s\"", item->key)

	if (TOML_Parse_Key_IsBareKeyChar(p->content[p->offset]))
	{	// bare key
		t_size	length = 0;
		while (TOML_Parse_Key_IsBareKeyChar(p->content[p->offset + length]))
		{
			if (!CAN_PARSE(length))
				PARSINGERROR_TOML("Could not parse key string: Unexpected end of input")
			++length;
		}
		key = String_Sub(p->content, p->offset, length);
		p->offset += length;
	}
	else if (p->content[p->offset] == '\"' || p->content[p->offset] == '\'')
	{	// quoted key
		s_toml*	tmp = TOML_Item();
		if (tmp == NULL)
			PARSINGERROR_TOML("Could not parse key string: allocation failure");
		if (TOML_Parse_String(tmp, p))
			PARSINGERROR_TOML("Could not parse key string: Failed to parse object member key")
		// swap value.string and .key, because we parsed the key
		key = tmp->value.string;
		tmp->value.string = NULL;
		TOML_Delete(tmp);
		tmp = NULL;
	}
	else
		PARSINGERROR_TOML("Could not parse key string: Unexpected character '%c'/0x%4.4X, expected bare key or quoted key",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])

	if (key == NULL)
		PARSINGERROR_TOML("Could not parse key string: allocation failure when copying key")

	// check if parent-level object already contains this key
	if ((context->type & DYNAMICTYPE_OBJECT) == 0)
		PARSINGERROR_TOML("Could not parse key string: parent item does not have type 'OBJECT'")
	tmp = context->value.child;
	exists = NULL;
	if (tmp)
	{
		while (tmp->next)
		{
			if (item != tmp && tmp->key && String_Equals(key, tmp->key))
			{
				exists = tmp;
				break;
			}
			tmp = tmp->next;
		}
	}
	tmp = NULL;
	if (exists)
	{
		TOML_Delete(item);
		item = exists;
	}
	else
	{
		if (item->key)
			PARSINGERROR_TOML("Could not parse key string: item does not exist but has a key: \"%s\"", item->key)
		item->key = key;
	}

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse key string: Unexpected end of input after key")

	TOML_Parse_SkipWhiteSpace(p);
	if (p->content[p->offset] == '.')
	{
		p->offset++;

		item->type |= DYNAMICTYPE_OBJECT;
		item->value.child = child;

		child = TOML_Item();
		if (child == NULL)
			PARSINGERROR_TOML("Could not allocate child object for parent with key \"%s\"", item->key)
		TOML_Parse_SkipWhiteSpace(p);
		if (TOML_Parse_Key(child, p, item, &result))
			PARSINGERROR_TOML("Could not parse sub-field key after parent key \"%s\"", item->key)
	}
	else // throw error when key is already assigned for leaf-level keys
	{
		if (exists)
			PARSINGERROR_TOML("Name conflict, item key already exists: \"%s\"", item->key)
	}

	if (a_result)
		*a_result = result;
	return (OK);

failure:

	if (child && !exists)
	{
		TOML_Delete(child);
		child = NULL;
	}
	if (tmp)
	{
		TOML_Delete(tmp);
		tmp = NULL;
	}
	if (key && key != item->key)
		String_Delete(&key);
	return (ERROR);
}



static
t_bool	TOML_Parse_Table(s_toml* item, s_toml_parse* p)
{
	t_size	line_no = p->line;
	s_toml*	result = NULL;

	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (ERROR);)
	// TODO double-bracket table array notation

	if (p->content[p->offset] != '[')
		PARSINGERROR_TOML("Expected '[' char, to begin table key, instead found '%c'/0x%4.4X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	TOML_Parse_SkipWhiteSpace(p);

	if (TOML_Parse_Key(item, p, p->result, &result))
		PARSINGERROR_TOML("Inside table: Could not parse table/section name key");
	result->type |= DYNAMICTYPE_OBJECT;

	TOML_Parse_SkipWhiteSpace(p);
	if (p->content[p->offset] != ']')
		PARSINGERROR_TOML("Expected ']' char, to end table key, instead found '%c'/0x%4.4X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	if (p->strict && line_no != p->line)
		PARSINGERROR_TOML("A table/section name cannot span over multiple lines in strict TOML (only certain value types can)")
	TOML_Parse_SkipWhiteSpace(p);

	if (TOML_Parse_Lines(result, p))
		PARSINGERROR_TOML("Inside table/section [\"%s\"]: error while parsing TOML string", item->key)

	return (OK);

failure:
	return (ERROR);
}



static
t_bool	TOML_Parse_KeyValuePair(s_toml* item, s_toml_parse* p, s_toml* context)
{
	t_size	line_no = p->line;
	s_toml*	result = NULL;

	if (TOML_Parse_Key(item, p, context, &result))
		PARSINGERROR_TOML("Could not parse key/value pair: error while parsing key")

	TOML_Parse_SkipWhiteSpace(p);
	if (p->content[p->offset] == '=' || (!p->strict && p->content[p->offset] == ':'))
		p->offset += 1;
	else
		PARSINGERROR_TOML("Could not parse key/value pair: Expected '='%s char, instead found '%c'/0x%4.4X",
			(p->strict ? "" : " or ':'"),
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	TOML_Parse_SkipWhiteSpace(p);
	if (p->strict && line_no != p->line)
		PARSINGERROR_TOML("A key/value pair cannot span over multiple lines in strict TOML (only certain value types can)")
	if (TOML_Parse_Value(result, p))
		PARSINGERROR_TOML("Could not parse key/value pair: error while parsing value assigned to key \"%s\"", result->key)

	return (OK);

failure:
	return (ERROR);
}



static
t_bool	TOML_Parse_Lines(s_toml* item, s_toml_parse* p)
{
	s_toml* head = NULL; // linked list head
	s_toml* current_item = NULL;
	s_toml* new_item;

	TOML_Parse_SkipWhiteSpace(p);
	if (p->content[p->offset] == '=')
	{
		// TODO custom logic: when no key is given ('=' at the beginning of the line), apply value to parent element
	}

	p->depth++;
	while (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '\0')
			goto success;

		new_item = TOML_Item();
		if (new_item == NULL)
			PARSINGERROR_TOML("Could not parse object: Allocation failure")

		if (p->content[p->offset] == '[')
		{
			if (item != p->result)
				goto success;
			item->type = DYNAMICTYPE_OBJECT; // TODO handle TOML with root-level arrays
			if (item->value.child == NULL)
			{
				item->value.child = new_item;
				current_item = new_item;
			}
			else if (current_item)
			{	// add to the end and advance
				current_item->next = new_item;
				new_item->prev = current_item;
				current_item = new_item;
			}
			if (TOML_Parse_Table(new_item, p))
				goto failure;
		}
		else
		{
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
			item->type = DYNAMICTYPE_OBJECT;
			item->value.child = head;
			if (TOML_Parse_KeyValuePair(current_item, p, item))
				goto failure;
		}
		TOML_Parse_SkipWhiteSpace(p);
	}

success:
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMICTYPE_OBJECT;
	if (item != p->result)
		item->value.child = head;
	return (OK);

failure:
	if (head != NULL)
	{
		TOML_Delete(head);
		head = NULL;
	}
	return (ERROR);
}



static
t_size	TOML_Parse_(s_toml* *dest, t_char const* str, t_size n, t_bool strict)
{
	s_toml_parse parser = { 0 };
	s_toml_parse* p = &parser;

	HANDLE_ERROR(LENGTH2SMALL, (n < 1),
		if (dest) *dest = NULL;
		return (p->offset);
	)
	p->content = str;
	p->length = n; 
	p->offset = UTF8_ByteOrderMark(str);
	p->strict = strict;
	p->line = 1;
	p->result = TOML_Item();
	if (p->result == NULL)
		PARSINGERROR_TOML("Got null result: memory failure")
	if (TOML_Parse_Lines(p->result, TOML_Parse_SkipWhiteSpace(p)))
		goto failure;
	if (p->strict)
	{	// if we require null-terminated TOML without appended garbage, skip and then check for a null terminator
		TOML_Parse_SkipWhiteSpace(p);
		if (p->content[p->offset] != '\0')
			PARSINGERROR_TOML("Invalid TOML: unexpected garbage chars after root-level value: \"%s\"", p->content + p->offset)
	}
/*
	if (return_parse_end)
	{
		*return_parse_end = &p.content[p.offset];
	}
*/
	if (dest) *dest = p->result;
	return (p->offset);

failure:
	if (p->result != NULL)
	{
//		TOML_Delete(p->result);
		p->result = NULL;
	}
	if (str != NULL)
	{
/*
		t_size	position = 0;
		if (p.offset < p.length)
			position = p.offset;
		else if (p.length > 0)
			position = p.length - 1;
		if (return_parse_end != NULL)
		{
			*return_parse_end = (str + position);
		}
*/
	}
	t_size column = 0;
	while (p->offset - column != 0)
	{
		if (p->content[p->offset - column] == '\n')
			break;
		column++;
	}
	HANDLE_ERROR_SF(PARSE, (TRUE),
		if (dest) *dest = NULL;
		return (p->offset);,
		": at nesting depth %u: line %zu, column %zu (char index %zu: '%c'/0x%X)%s\n",
		p->depth,
		p->line,
		column,
		p->offset,
		p->content[p->offset] ? p->content[p->offset] : '\a',
		p->content[p->offset],
		p->error)
	return (p->offset);
}



t_size	TOML_Parse_Lenient(s_toml* *dest, t_utf8 const* str, t_size n)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	if (n == 0)
		n = String_Length(str);
	return (TOML_Parse_(dest, str, n, FALSE));
}

t_size	TOML_Parse_Strict(s_toml* *dest, t_utf8 const* str, t_size n)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	if (n == 0)
		n = String_Length(str);
	return (TOML_Parse_(dest, str, n, TRUE));
}



s_toml*	TOML_FromString_Lenient(t_utf8 const* str)
{
	s_toml*	result;
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	TOML_Parse_(&result, str, String_Length(str), FALSE);
	return (result);
}

s_toml*	TOML_FromString_Strict(t_utf8 const* str)
{
	s_toml*	result;
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	TOML_Parse_(&result, str, String_Length(str), TRUE);
	return (result);
}
