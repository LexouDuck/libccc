
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/encode/toml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_parse	s_toml_parse;



static t_bool TOML_Parse_Key   (s_toml* item, s_toml_parse* p);
static t_bool TOML_Parse_Value (s_toml* item, s_toml_parse* p);
static t_bool TOML_Parse_Table (s_toml* item, s_toml_parse* p);
static t_bool TOML_Parse_Number(s_toml* item, s_toml_parse* p);
static t_bool TOML_Parse_String(s_toml* item, s_toml_parse* p);
//static t_bool TOML_Parse_Array (s_toml* item, s_toml_parse* p); // TODO
//static t_bool TOML_Parse_Object(s_toml* item, s_toml_parse* p); // TODO



#define PARSINGERROR_TOML_MESSAGE	IO_COLOR_FG_RED"TOML PARSE ERROR"IO_RESET":"

//! used to handle errors during parsing
#define PARSINGERROR_TOML(...) \
	{																						\
		t_char* tmp_error;																	\
		tmp_error = String_Format(__VA_ARGS__);												\
		tmp_error = String_Prepend("\n"PARSINGERROR_TOML_MESSAGE" ", &tmp_error);			\
		p->error = (p->error == NULL ? tmp_error : String_Merge(&p->error, &tmp_error));	\
		goto failure;																		\
	}																						\

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
					break;
			}
			p->offset += i;
		}
		if (!p->strict && p->content[p->offset] == '/') // C-style comments (only if not strict mode)
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
					PARSINGERROR_TOML("input ends unexpectedly, expected end of comment block \"*/\"")
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
			!Char_IsSpace_TOML(p->content[p->offset]) :
			!Char_IsSpace(p->content[p->offset]))
			break;
		p->offset++;
	}
	return (p);

failure:
	return (NULL);
}



/*
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
	if (!p->strict && String_Has(number, CHARSET_DIGIT) && number[length - 1] == 'n')
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
t_bool TOML_Parse_String(s_toml* item, s_toml_parse* p)
{
	t_utf8 const* input_ptr = &p->content[p->offset] + 1;
	t_utf8 const* input_end = &p->content[p->offset] + 1;
	t_utf8* output_ptr = NULL;
	t_utf8* output = NULL;
	t_size alloc_length;
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
		PARSINGERROR_TOML("Could not parse string: Expected string quote char '\"' or '\'', instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	if (CAN_PARSE(1) && p->content[p->offset + 1] == stringtype &&
		CAN_PARSE(2) && p->content[p->offset + 2] == stringtype)
		is_multiline = TRUE;
	// calculate approximate size of the output (overestimate)
	alloc_length = 0;
	skipped_bytes = 0;
	while ((t_size)(input_end - p->content) < p->length)
	{
		// is escape sequence
		if (input_end[0] == '\\')
		{
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
	// This is how many bytes we need for the output, at most
	alloc_length = (t_size)(input_end - &p->content[p->offset]) - skipped_bytes;
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
					sequence_length = UTF32_Parse_N(&c, input_ptr, (input_end - input_ptr));
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
t_bool	TOML_Parse_Key(s_toml* item, s_toml_parse* p)
{

	if (!CAN_PARSE(0))
		PARSINGERROR_TOML("Could not parse object member key: Unexpected end of input")
	if (p->content[p->offset] == '-' ||
		p->content[p->offset] == '_' ||
		Char_IsAlphaNumeric(p->content[p->offset]))
	{	// bare key
		t_size	length = 0;
		while (Char_IsAlphaNumeric(p->content[p->offset + length]) ||
			p->content[p->offset + length] == '-' ||
			p->content[p->offset + length] == '_')
		{
			if (!CAN_PARSE(length))
				PARSINGERROR_TOML("Could not parse object member key: Unexpected end of input")
			++length;
		}
		item->key = String_Sub(p->content, p->offset, length);
		p->offset += length;
	}
	else if (p->content[p->offset] == '\"' || p->content[p->offset] == '\'')
	{	// quoted key
		if (TOML_Parse_String(item, p))
			PARSINGERROR_TOML("Could not parse object: Failed to parse object member key")
		// swap value.string and string, because we parsed the name
		item->key = item->value.string;
		item->value.string = NULL;
	}

	if (p->content[p->offset] == '.')
	{
		p->offset++;
		s_toml* child = TOML_Item();
		if (child == NULL)
			PARSINGERROR_TOML("Could not allocate child object for parent with key \"%s\"", item->key)
		item->type |= DYNAMICTYPE_OBJECT;
		item->value.child = child;
		if (TOML_Parse_Key(child, p))
			goto failure;
	}

	return (OK);

failure:
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
//		if (p->content[p->offset] == '[')
//			return (TOML_Parse_Array( item, p));	// array
//		if (p->content[p->offset] == '{')
//			return (TOML_Parse_Object(item, p));	// object
		if (p->content[p->offset] == '\"')
			return (TOML_Parse_String(item, p));	// string
		if (Char_IsDigit(p->content[p->offset]) ||
			p->content[p->offset] == '-' ||
			p->content[p->offset] == '+' ||
			(CAN_PARSE(3) && (
				String_Equals_N(p->content + p->offset, "inf", 3) ||
				String_Equals_N(p->content + p->offset, "nan", 3))))
			return (TOML_Parse_Number(item, p));	// number
	}

//	if (p->content[p->offset] == '\'')
//		return (TOML_Parse_String(item, p));	// string
	if (p->strict && Char_IsSpace(p->content[p->offset]))
	{
		PARSINGERROR_TOML("Non-standard whitespace character used ('%c'/0x%2X) is not allowed in strict TOML", p->content[p->offset], p->content[p->offset])
	}
	else if (CAN_PARSE(3) && (
		String_Equals_N(p->content + p->offset, "Inf", 3) ||
		String_Equals_N(p->content + p->offset, "INF", 3)))
	{	// number
		if (p->strict)
			PARSINGERROR_TOML("Any non-numeric value (here, infinity: \"%.3s\") must be 3-letter lowercase, in strict TOML", p->content + p->offset)
		return (TOML_Parse_Number(item, p));
	}
	else if (CAN_PARSE(3) && (
		String_Equals_N(p->content + p->offset, "NaN", 3) ||
		String_Equals_N(p->content + p->offset, "NAN", 3)))
	{	// number
		if (p->strict)
			PARSINGERROR_TOML("Any non-numeric value (here, 'not a number': \"%.3s\") must be 3-letter lowercase, in strict TOML", p->content + p->offset)
		return (TOML_Parse_Number(item, p));
	}

	PARSINGERROR_TOML("Unable to determine the kind of parsing to attempt: \"%.6s\"", p->content + p->offset)

failure:
	return (ERROR);
}



static
t_bool	TOML_Parse_KeyValuePair(s_toml* item, s_toml_parse* p)
{
	s_toml* head = NULL; // linked list head
	s_toml* current_item = NULL;
	s_toml* new_item;
	t_size	line_no = 0;
//	p.result = ;
	TOML_Parse_SkipWhiteSpace(p);
	while (p->content[p->offset])
	{
		line_no = p->line;
		TOML_Parse_SkipWhiteSpace(p);
		if (CAN_PARSE(0))
			goto success; // empty object

		new_item = TOML_Item();
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

		if (p->content[p->offset] == '[')
		{
			if (TOML_Parse_Table(current_item, p))
				goto failure;
			if (p->strict && line_no != p->line)
				PARSINGERROR_TOML("A table/section name cannot span over multiple lines in strict TOML (only certain value types can)")
		}
		else
		{
			if (TOML_Parse_Key(current_item, p))
				goto failure;
			TOML_Parse_SkipWhiteSpace(p);
			if (p->content[p->offset] == '=' || (!p->strict && p->content[p->offset] == ':'))
				p->offset += 1;
			else
				PARSINGERROR_TOML("Could not parse key/value pair: Expected '='%s char, instead found '%c'/0x%2X",
					(p->strict ? "" : " or ':'"), p->content[p->offset], p->content[p->offset])
			TOML_Parse_SkipWhiteSpace(p);
			if (p->strict && line_no != p->line)
				PARSINGERROR_TOML("A key/value pair cannot span over multiple lines in strict TOML (only certain value types can)")
			if (TOML_Parse_Value(current_item, p))
				goto failure;
		}
		TOML_Parse_SkipWhiteSpace(p);
		++p->offset;
	}
	return (p->result);

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
	}
	return (ERROR);
}



static
t_bool	TOML_Parse_Table(s_toml* item, s_toml_parse* p)
{
	// TODO
	if ((p->content[p->offset] != '['))
		PARSINGERROR_TOML("Expected '[' char, to begin table key, instead found '%c'/0x%2X",
			p->content[p->offset], p->content[p->offset])
	TOML_Parse_SkipWhiteSpace(p);
	if (TOML_Parse_Key(item, p))
		goto failure;
	TOML_Parse_SkipWhiteSpace(p);
	if (p->content[p->offset] != ']')
		PARSINGERROR_TOML("Expected ']' char, to end table key, instead found '%c'/0x%2X",
			p->content[p->offset], p->content[p->offset])
	return (OK);

failure:
	return (ERROR);
}



static
t_size	TOML_Parse_(s_toml* *dest, t_char const* str, t_size n, t_bool strict)
{
	s_toml_parse parser = { 0 };
	s_toml_parse* p = &parser;
	s_toml* result = NULL;

	HANDLE_ERROR(LENGTH2SMALL, (n < 1),
		if (dest) *dest = NULL;
		return (p->offset);)
	p->content = str;
	p->length = n; 
	p->offset = 0;
	p->strict = strict;
	result = TOML_Item();
	if (result == NULL)
		PARSINGERROR_TOML("Got null result: memory failure")
	p->offset += UTF8_ByteOrderMark(str);
	if (!TOML_Parse_KeyValuePair(result, TOML_Parse_SkipWhiteSpace(p)))
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
	if (dest) *dest = result;
	return (p->offset);

failure:
	if (result != NULL)
	{
		TOML_Delete(result);
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
}



t_size	TOML_Parse_Lenient(s_toml* *dest, t_utf8 const* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	return (TOML_Parse_(dest, str, String_Length(str), FALSE));
}

t_size	TOML_Parse_Strict(s_toml* *dest, t_utf8 const* str)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	return (TOML_Parse_(dest, str, String_Length(str), TRUE));
}



t_size	TOML_Parse_N_Lenient(s_toml* *dest, t_utf8 const* str, t_size n)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	return (TOML_Parse_(dest, str, n, FALSE));
}

t_size	TOML_Parse_N_Strict(s_toml* *dest, t_utf8 const* str, t_size n)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
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
