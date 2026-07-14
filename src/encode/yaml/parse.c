
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/text/escape.h"
#include "libccc/text/format.h"
#include "libccc/encode/yaml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_parse	s_yaml_parse;



static t_bool	YAML_Parse_Block		(s_yaml* item, s_yaml_parse* p, t_size indent);
static t_bool	YAML_Parse_Mapping		(s_yaml* item, s_yaml_parse* p, t_size indent);
static t_bool	YAML_Parse_Sequence		(s_yaml* item, s_yaml_parse* p, t_size indent);
static t_bool	YAML_Parse_FlowValue	(s_yaml* item, s_yaml_parse* p, t_bool in_flow);
static t_bool	YAML_Parse_FlowArray	(s_yaml* item, s_yaml_parse* p);
static t_bool	YAML_Parse_FlowObject	(s_yaml* item, s_yaml_parse* p);
static t_bool	YAML_Parse_String		(s_yaml* item, s_yaml_parse* p);
static t_bool	YAML_Parse_Scalar		(s_yaml* item, s_yaml_parse* p, t_bool in_flow);
static t_bool	YAML_Parse_BlockScalar	(s_yaml* item, s_yaml_parse* p, t_size indent);



//! String which is at the beginning of each error log output line
#define PARSINGERROR_YAML_PREFIX	"\n -> "

//! used to handle errors during parsing
#define PARSINGERROR_YAML(...) \
	{ \
		t_char* tmp_error; \
		tmp_error = String_Format(__VA_ARGS__); \
		tmp_error = String_Prepend(PARSINGERROR_YAML_PREFIX, &tmp_error); \
		if (p != NULL) \
		{ p->error = (p->error == NULL ? tmp_error : String_Merge(&p->error, &tmp_error)); } \
		else String_Delete(&tmp_error); \
		goto failure; \
	} \

//! Safely checks if the content to parse can be accessed at the given index
#define CAN_PARSE(X) \
	((p->content != NULL) && ((p->offset + X) <= p->length))

//! Checks whether the given char marks the end of a line of text
#define YAML_ISLINEBREAK(C) \
	((C) == '\n' || (C) == '\0')



//! Checks whether the char at the current parsing offset marks the end of the line's content
/*!
**	This can be a linebreak/nul char, or a `#` comment (which extends to the end of the line).
*/
static
t_bool	YAML_Parse_IsLineEnd(s_yaml_parse* p)
{
	if (!CAN_PARSE(0))
		return (TRUE);
	if (YAML_ISLINEBREAK(p->content[p->offset]))
		return (TRUE);
	if (p->content[p->offset] == '\r' && CAN_PARSE(1) && YAML_ISLINEBREAK(p->content[p->offset + 1]))
		return (TRUE);
	if (p->content[p->offset] == '#')
		return (TRUE);
	return (FALSE);
}

//! Utility to skip over any space chars (but not linebreaks) at the current parsing offset
static
void	YAML_Parse_SkipSpaces(s_yaml_parse* p)
{
	while (CAN_PARSE(0) && (
		p->content[p->offset] == ' ' ||
		p->content[p->offset] == '\t'))
	{
		p->offset++;
	}
}

//! Computes the column index (i.e. indentation) of the char at the current parsing offset
/*!
**	This is done by scanning backwards, from the current offset to the start of the line.
**	NOTE: any tab characters found are counted as a single column of indentation.
*/
static
t_size	YAML_Parse_GetIndent(s_yaml_parse* p)
{
	t_size	i = p->offset;
	t_size	column = 0;

	while (i > 0 && !YAML_ISLINEBREAK(p->content[i - 1]))
	{
		--i;
		++column;
	}
	return (column);
}

//! Checks whether the current line (at line-start `offset`) is a document marker: `---` or `...`
static
t_bool	YAML_Parse_IsDocumentMarker(s_yaml_parse* p, t_utf8 marker)
{
	if (!CAN_PARSE(3))
		return (FALSE);
	if (p->content[p->offset + 0] != marker ||
		p->content[p->offset + 1] != marker ||
		p->content[p->offset + 2] != marker)
		return (FALSE);
	if ((p->offset + 3) < p->length &&
		!YAML_ISLINEBREAK(p->content[p->offset + 3]) &&
		p->content[p->offset + 3] != ' ' &&
		p->content[p->offset + 3] != '\t' &&
		p->content[p->offset + 3] != '\r')
		return (FALSE);
	return (TRUE);
}

//! Skips to the start of the next line (assumes the rest of the current line holds no content)
/*!
**	Throws a parsing error if any non-space, non-comment content is found before the linebreak.
*/
static
t_bool	YAML_Parse_SkipToNextLine(s_yaml_parse* p)
{
	YAML_Parse_SkipSpaces(p);
	if (CAN_PARSE(0) && p->content[p->offset] == '#')
	{	// skip comment, until end of line
		while (CAN_PARSE(0) && !YAML_ISLINEBREAK(p->content[p->offset]))
			p->offset++;
	}
	if (CAN_PARSE(0) && p->content[p->offset] == '\r')
		p->offset++;
	if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
		return (OK);
	if (p->content[p->offset] != '\n')
		PARSINGERROR_YAML("Expected end of line, instead found trailing content: \"%.8s\"", p->content + p->offset)
	p->offset++;
	p->line++;
	return (OK);

failure:
	return (ERROR);
}

//! Advances the parsing offset to the first content char of the next non-blank line
/*!
**	This function assumes that the current parsing offset is at the start of a line.
**	Any blank lines, comment-only lines, and `%` directive lines are skipped over.
**	If a document end marker (`...`), or a subsequent document start marker (`---`),
**	is encountered, then parsing of the current document stops (treated like end of input).
**	@param	end	Output: is set to `TRUE` if the end of the document/input was reached
*/
static
t_bool	YAML_Parse_GotoNextContent(s_yaml_parse* p, t_bool* end)
{
	*end = FALSE;
	while (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '\0')
			break;
		// check for document markers and directives, which can only occur at column 0
		if (YAML_Parse_IsDocumentMarker(p, '.') ||
			YAML_Parse_IsDocumentMarker(p, '-'))
		{	// stop parsing at the end of the current document (the marker itself is not consumed)
			*end = TRUE;
			return (OK);
		}
		if (p->content[p->offset] == '%')
		{	// skip directive lines (`%YAML`, `%TAG`, etc)
			while (CAN_PARSE(0) && !YAML_ISLINEBREAK(p->content[p->offset]))
				p->offset++;
			if (CAN_PARSE(0) && p->content[p->offset] == '\n')
			{
				p->offset++;
				p->line++;
			}
			continue;
		}
		// skip over any leading indentation
		while (CAN_PARSE(0) && (p->content[p->offset] == ' ' ||
			(!p->strict && p->content[p->offset] == '\t')))
		{
			p->offset++;
		}
		if (CAN_PARSE(0) && p->content[p->offset] == '\t')
			PARSINGERROR_YAML("Tab characters are not allowed for indentation in YAML (only space characters)")
		if (YAML_Parse_IsLineEnd(p))
		{	// blank line, or comment-only line: skip to the next one
			if (YAML_Parse_SkipToNextLine(p))
				goto failure;
			if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
				break;
			continue;
		}
		return (OK); // found a content char
	}
	*end = TRUE;
	return (OK);

failure:
	return (ERROR);
}



/*============================================================================*\
||                            Scalar value parsing                            ||
\*============================================================================*/

static
t_bool	YAML_Scalar_IsInteger(t_utf8 const* str)
{
	t_size	i = 0;

	if (str[i] == '-' || str[i] == '+')
		++i;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
	{
		i += 2;
		if (str[i] == '\0')	return (FALSE);
		while (Char_IsDigit_Hex(str[i]))	++i;
		return (str[i] == '\0');
	}
	if (str[i] == '0' && (str[i + 1] == 'o' || str[i + 1] == 'O'))
	{
		i += 2;
		if (str[i] == '\0')	return (FALSE);
		while (str[i] >= '0' && str[i] <= '7')	++i;
		return (str[i] == '\0');
	}
	if (str[i] == '0' && (str[i + 1] == 'b' || str[i + 1] == 'B'))
	{
		i += 2;
		if (str[i] == '\0')	return (FALSE);
		while (str[i] == '0' || str[i] == '1')	++i;
		return (str[i] == '\0');
	}
	if (str[i] == '\0')
		return (FALSE);
	while (Char_IsDigit(str[i]))	++i;
	return (str[i] == '\0');
}

static
t_bool	YAML_Scalar_IsFloat(t_utf8 const* str)
{
	t_size	i = 0;
	t_bool	has_digits = FALSE;
	t_bool	has_point = FALSE;

	if (str[i] == '-' || str[i] == '+')
		++i;
	while (Char_IsDigit(str[i]))
	{
		has_digits = TRUE;
		++i;
	}
	if (str[i] == '.')
	{
		has_point = TRUE;
		++i;
		while (Char_IsDigit(str[i]))
		{
			has_digits = TRUE;
			++i;
		}
	}
	if (!has_digits)
		return (FALSE);
	if (str[i] == 'e' || str[i] == 'E')
	{
		++i;
		if (str[i] == '-' || str[i] == '+')
			++i;
		if (!Char_IsDigit(str[i]))
			return (FALSE);
		while (Char_IsDigit(str[i]))	++i;
	}
	else if (!has_point)
		return (FALSE); // integers are handled by YAML_Scalar_IsInteger()
	return (str[i] == '\0');
}

//! Resolves the type of a plain (unquoted) scalar string, as per the YAML "core schema"
/*!
**	@see https://yaml.org/spec/1.2.2/#103-core-schema
*/
static
t_bool	YAML_Parse_ResolveScalar(s_yaml* item, s_yaml_parse* p, t_utf8* str)
{
	t_size	start = 0;

	// null values
	if (str[0] == '\0' ||
		String_Equals(str, "~") ||
		String_Equals(str, "null") ||
		String_Equals(str, "Null") ||
		String_Equals(str, "NULL"))
	{
		item->type = DYNAMICTYPE_NULL;
		String_Delete(&str);
		return (OK);
	}
	// boolean values
	if (String_Equals(str, "true") ||
		String_Equals(str, "True") ||
		String_Equals(str, "TRUE") ||
		(!p->strict && (
		String_Equals_IgnoreCase(str, "yes") ||
		String_Equals_IgnoreCase(str, "on"))))
	{
		item->type = DYNAMICTYPE_BOOLEAN;
		item->value.boolean = TRUE;
		String_Delete(&str);
		return (OK);
	}
	if (String_Equals(str, "false") ||
		String_Equals(str, "False") ||
		String_Equals(str, "FALSE") ||
		(!p->strict && (
		String_Equals_IgnoreCase(str, "no") ||
		String_Equals_IgnoreCase(str, "off"))))
	{
		item->type = DYNAMICTYPE_BOOLEAN;
		item->value.boolean = FALSE;
		String_Delete(&str);
		return (OK);
	}
	// special float values (`.inf`, `-.inf`, `.nan`)
	start = 0;
	if (str[start] == '-' || str[start] == '+')
		++start;
	if (str[start] == '.' && (
		String_Equals_N_IgnoreCase(str + start, ".inf", 4) ||
		String_Equals_N_IgnoreCase(str + start, ".nan", 4)) &&
		str[start + 4] == '\0')
	{
		item->type = DYNAMICTYPE_FLOAT;
		if (str[start + 1] == 'n' || str[start + 1] == 'N')
			item->value.number = F64_FromString("nan");
		else item->value.number = (str[0] == '-' ? F64_FromString("-inf") : F64_FromString("+inf"));
		String_Delete(&str);
		return (OK);
	}
	if (!p->strict && (
		String_Equals_N_IgnoreCase(str + start, "inf", 3) ||
		String_Equals_N_IgnoreCase(str + start, "nan", 3)) &&
		str[start + 3] == '\0')
	{
		item->type = DYNAMICTYPE_FLOAT;
		if (str[start] == 'n' || str[start] == 'N')
			item->value.number = F64_FromString("nan");
		else item->value.number = (str[0] == '-' ? F64_FromString("-inf") : F64_FromString("+inf"));
		String_Delete(&str);
		return (OK);
	}
	// integer values
	if (YAML_Scalar_IsInteger(str))
	{
		t_size	prefix = ((str[0] == '-' || str[0] == '+') ? 1 : 0);
		if (p->strict && str[prefix] == '0' && (str[prefix + 1] == 'b' || str[prefix + 1] == 'B'))
			PARSINGERROR_YAML("Binary integer literals (\"%s\") are not allowed in strict YAML (only \"0x\" and \"0o\" prefixes)", str)
		item->type = DYNAMICTYPE_INTEGER;
		item->value.integer = S64_FromString(str); // TODO variable-length integer
		String_Delete(&str);
		return (OK);
	}
	// floating-point values
	if (YAML_Scalar_IsFloat(str))
	{
		item->type = DYNAMICTYPE_FLOAT;
		item->value.number = F64_FromString(str);
		String_Delete(&str);
		return (OK);
	}
	// any other plain scalar is a string
	item->type = DYNAMICTYPE_STRING;
	item->value.string = str;
	return (OK);

failure:
	String_Delete(&str);
	return (ERROR);
}

//! Parses a plain (unquoted) scalar value, which ends at the end of the line
/*!
**	When `in_flow` is `TRUE`, the scalar also ends at any of the flow chars: `,`, `]`, `}`
*/
static
t_bool	YAML_Parse_Scalar(s_yaml* item, s_yaml_parse* p, t_bool in_flow)
{
	t_utf8*	str = NULL;
	t_size	length = 0;
	t_size	content_length = 0;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	while (CAN_PARSE(length) && !YAML_ISLINEBREAK(p->content[p->offset + length]))
	{
		t_utf8 c = p->content[p->offset + length];
		if (c == '\r' && CAN_PARSE(length + 1) && YAML_ISLINEBREAK(p->content[p->offset + length + 1]))
			break;
		if (c == '#' && length > 0 && (
			p->content[p->offset + length - 1] == ' ' ||
			p->content[p->offset + length - 1] == '\t'))
			break; // comment (a '#' char must be preceded by whitespace to start a comment)
		if (in_flow && (c == ',' || c == ']' || c == '}'))
			break;
		if (in_flow && c == ':' && (
			!CAN_PARSE(length + 1) ||
			p->content[p->offset + length + 1] == ' ' ||
			p->content[p->offset + length + 1] == '\t' ||
			YAML_ISLINEBREAK(p->content[p->offset + length + 1])))
			break; // flow mapping `key: value` separator
		++length;
		if (c != ' ' && c != '\t')
			content_length = length; // used to trim trailing whitespace
	}
	if (content_length == 0)
		PARSINGERROR_YAML("Could not parse plain scalar: empty value")
	str = String_Sub(p->content, p->offset, content_length);
	if (str == NULL)
		PARSINGERROR_YAML("Could not parse plain scalar: allocation failure")
	p->offset += length;
	return (YAML_Parse_ResolveScalar(item, p, str));

failure:
	return (ERROR);
}



//! Parses a quoted string: double-quoted (with escape sequences) or single-quoted (verbatim)
static
t_bool	YAML_Parse_String(s_yaml* item, s_yaml_parse* p)
{
	t_utf8 const* input_ptr = NULL;
	t_utf8 const* input_end = NULL;
	t_utf8*	output = NULL;
	t_size	offset;
	t_size	skipped_bytes;
	t_utf8	stringtype = 0;
	t_utf32	c;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (!CAN_PARSE(0))
		PARSINGERROR_YAML("Could not parse string: Unexpected end of input before string")
	if (p->content[p->offset] == '\"')
		stringtype = '\"';
	if (p->content[p->offset] == '\'')
		stringtype = '\'';
	if (!stringtype)
		PARSINGERROR_YAML("Could not parse string: Expected string quote char '\"' or '\'', instead found '%c'/0x%4.4X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	input_ptr = &p->content[p->offset] + 1;
	input_end = &p->content[p->offset] + 1;
	// calculate approximate size of the output (overestimate)
	skipped_bytes = 0;
	while ((t_size)(input_end - p->content) < p->length)
	{
		if (stringtype == '\"' && input_end[0] == '\\')
		{	// is escape sequence
			if ((t_size)(input_end + 1 - p->content) >= p->length)
				PARSINGERROR_YAML("Could not parse string: Potential buffer-overflow, string ends with backslash")
			c = input_end[1];
			t_sint sequence_chars = 0;
			switch (c)
			{
				case 'u': 					sequence_chars = 4;	skipped_bytes += (2 + sequence_chars - 2);	break;
				case 'U': 					sequence_chars = 8;	skipped_bytes += (2 + sequence_chars - 4);	break;
				case 'x': 					sequence_chars = 2;	skipped_bytes += (2 + sequence_chars - 1);	break;
				default:					sequence_chars = 0;	skipped_bytes += (2 + sequence_chars - 1);	break;
			}
			input_end++;
			for (t_sint i = 1; i <= sequence_chars; ++i)
			{
				if ((t_size)(input_end + i - p->content) >= p->length ||
					!Char_IsDigit_Hex(input_end[i]))
					PARSINGERROR_YAML("Could not parse string: Unicode escape sequence char '%c' "
						"must be followed by " SF_SINT " hexadecimal digit chars, instead found \"%.*s\"",
						(t_utf8)c, sequence_chars, (int)(sequence_chars + 2), input_end - 1)
			}
			input_end += sequence_chars;
		}
		else if (input_end[0] == stringtype)
		{
			if (stringtype == '\'' &&
				(t_size)(input_end + 1 - p->content) < p->length &&
				input_end[1] == '\'')
			{	// escaped single-quote, within a single-quoted string: ''
				skipped_bytes++;
				input_end++;
			}
			else break;
		}
		input_end++;
	}
	if (((t_size)(input_end - p->content) >= p->length) || (*input_end != stringtype))
		PARSINGERROR_YAML("Could not parse string: Unexpected end of input before closing quote")

	{
		// This is at most how much we need for the output
		t_size	alloc_length = (t_size)(input_end - &p->content[p->offset]) - skipped_bytes;
		output = (t_utf8*)Memory_Allocate(alloc_length + sizeof(""));
		if (output == NULL)
			PARSINGERROR_YAML("Could not parse string: Allocation failure")
		offset = 0;
		// loop through the string literal
		while (input_ptr < input_end)
		{
			if (stringtype == '\'' && *input_ptr == '\'')
			{	// escaped single-quote: '' becomes '
				output[offset++] = '\'';
				input_ptr += 2;
			}
			else if (stringtype == '\"' && *input_ptr == '\\')
			{	// escape sequence
				t_utf8 sequence_length = 2;
				if ((input_end - input_ptr) < 1)
					PARSINGERROR_YAML("Could not parse string: Unexpected end of input within string escape sequence")
				switch (input_ptr[1])
				{
					case '0':	output[offset++] = '\0';	break;
					case 'a':	output[offset++] = '\a';	break;
					case 'b':	output[offset++] = '\b';	break;
					case 't':	output[offset++] = '\t';	break;
					case 'n':	output[offset++] = '\n';	break;
					case 'v':	output[offset++] = '\v';	break;
					case 'f':	output[offset++] = '\f';	break;
					case 'r':	output[offset++] = '\r';	break;
					case 'e':	output[offset++] = '\x1B';	break;
					case ' ':	output[offset++] = ' ';		break;
					case '\"':
					case '\'':
					case '\\':
					case '/':
						output[offset++] = input_ptr[1];
						break;
					case 'x': // 8-bit char literal
					case 'u': // UTF-16 literal
					case 'U': // UTF-32 literal
						c = '\0';
						sequence_length = CharUTF32_Unescape(&c, input_ptr, (input_end - input_ptr));
						if (sequence_length == 0)
							PARSINGERROR_YAML("Could not parse string: Failed to convert unicode escape sequence to UTF-8")
						offset += CharUTF32_ToUTF8(output + offset, c);
						break;
					default:
						PARSINGERROR_YAML("Could not parse string: Invalid string escape sequence encountered: \"\\%c\"", input_ptr[1])
				}
				input_ptr += sequence_length;
			}
			else output[offset++] = *input_ptr++;
		}
		// zero terminate the output
		output[offset] = '\0';
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



/*============================================================================*\
||                          Block scalars: `|` and `>`                        ||
\*============================================================================*/

static
t_bool	YAML_Parse_BlockScalar(s_yaml* item, s_yaml_parse* p, t_size indent)
{
	t_utf8*	output = NULL;
	t_size	offset = 0;
	t_bool	folded;
	t_utf8	chomp = '\0'; // '\0' is "clip" mode, '-' is "strip" mode, '+' is "keep" mode
	t_size	content_indent = 0;
	t_size	region_start;
	t_size	region_end;
	t_size	pending_breaks = 0;
	t_bool	has_content = FALSE;
	t_bool	end = FALSE;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->content[p->offset] != '|' &&
		p->content[p->offset] != '>')
		PARSINGERROR_YAML("Could not parse block scalar: Expected '|' or '>' char, instead found '%c'/0x%4.4X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	folded = (p->content[p->offset] == '>');
	p->offset++;
	// parse header indicators (chomping: '-'/'+', and/or explicit indentation: digit from 1 to 9)
	for (t_uint i = 0; i < 2 && CAN_PARSE(0); ++i)
	{
		if (p->content[p->offset] == '-' || p->content[p->offset] == '+')
		{
			if (chomp != '\0')
				PARSINGERROR_YAML("Could not parse block scalar: multiple chomping indicator chars given")
			chomp = p->content[p->offset];
			p->offset++;
		}
		else if (p->content[p->offset] >= '1' && p->content[p->offset] <= '9')
		{
			if (content_indent != 0)
				PARSINGERROR_YAML("Could not parse block scalar: multiple indentation indicator chars given")
			content_indent = indent + (p->content[p->offset] - '0');
			p->offset++;
		}
		else break;
	}
	if (YAML_Parse_SkipToNextLine(p))
		PARSINGERROR_YAML("Could not parse block scalar: unexpected content after '%c' block scalar header", (folded ? '>' : '|'))

	// first pass: find the extent of the block scalar's content region, and detect its indentation
	region_start = p->offset;
	region_end = p->offset;
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		t_size	line_indent = 0;
		t_size	line_start = p->offset;
		while (CAN_PARSE(0) && p->content[p->offset] == ' ')
		{
			p->offset++;
			line_indent++;
		}
		if (YAML_ISLINEBREAK(p->content[p->offset]) ||
			(p->content[p->offset] == '\r' && CAN_PARSE(1) && YAML_ISLINEBREAK(p->content[p->offset + 1])))
		{	// blank line: belongs to the block scalar
			if (p->content[p->offset] == '\r')
				p->offset++;
			if (CAN_PARSE(0) && p->content[p->offset] == '\n')
			{
				p->offset++;
				p->line++;
			}
			else break; // end of input
			region_end = p->offset;
			continue;
		}
		if (line_indent <= indent)
		{	// this line belongs to a parent node: end of the block scalar
			p->offset = line_start;
			break;
		}
		if (content_indent == 0)
			content_indent = line_indent; // auto-detect content indentation from the first non-blank line
		if (line_indent < content_indent)
			PARSINGERROR_YAML("Could not parse block scalar: line is less indented (" SF_SIZE " chars) than the first line of the block (" SF_SIZE " chars)",
				line_indent, content_indent)
		// skip to the end of this content line
		while (CAN_PARSE(0) && !YAML_ISLINEBREAK(p->content[p->offset]))
			p->offset++;
		if (CAN_PARSE(0) && p->content[p->offset] == '\n')
		{
			p->offset++;
			p->line++;
		}
		region_end = p->offset;
	}

	// second pass: build the output string (the region length is a strict upper bound for the output length)
	output = (t_utf8*)Memory_Allocate((region_end - region_start) + sizeof("\n"));
	if (output == NULL)
		PARSINGERROR_YAML("Could not parse block scalar: Allocation failure")
	{
		t_size	i = region_start;
		while (i < region_end)
		{
			t_size	line_indent = 0;
			t_size	line_length = 0;
			while (i + line_indent < region_end && p->content[i + line_indent] == ' ' && line_indent < content_indent)
				line_indent++;
			i += line_indent;
			while (i + line_length < region_end && !YAML_ISLINEBREAK(p->content[i + line_length]))
				line_length++;
			// trim any trailing '\r' char
			if (line_length > 0 && p->content[i + line_length - 1] == '\r')
				line_length--;
			if (line_length == 0)
			{	// blank line
				pending_breaks += 1;
			}
			else
			{
				if (has_content)
				{	// separate from the previous line
					if (!folded)
						output[offset++] = '\n';
					else if (pending_breaks > 0)
					{
						for (t_size b = 0; b < pending_breaks; ++b)
							output[offset++] = '\n';
					}
					else output[offset++] = ' ';
					if (folded)
						pending_breaks = 0;
				}
				else if (folded && pending_breaks > 0)
				{	// leading blank lines are preserved
					for (t_size b = 0; b < pending_breaks; ++b)
						output[offset++] = '\n';
					pending_breaks = 0;
				}
				if (!folded && pending_breaks > 0)
				{
					for (t_size b = 0; b < pending_breaks; ++b)
						output[offset++] = '\n';
					pending_breaks = 0;
				}
				Memory_Copy(output + offset, p->content + i, line_length);
				offset += line_length;
				has_content = TRUE;
			}
			// skip past the linebreak
			while (i < region_end && !YAML_ISLINEBREAK(p->content[i]))
				i++;
			if (i < region_end && p->content[i] == '\n')
				i++;
		}
	}
	// apply the chomping mode, for trailing linebreaks
	if (chomp == '+')
	{	// "keep" mode: preserve all trailing linebreaks
		if (has_content)
			output[offset++] = '\n';
		for (t_size b = 0; b < pending_breaks; ++b)
			output[offset++] = '\n';
	}
	else if (chomp == '\0' && has_content)
	{	// "clip" mode: keep a single trailing linebreak
		output[offset++] = '\n';
	}
	// otherwise, "strip" mode: no trailing linebreak
	output[offset] = '\0';

	item->type = DYNAMICTYPE_STRING;
	item->value.string = output;
	// leave the parsing offset at the first content char of the next content line
	if (YAML_Parse_GotoNextContent(p, &end))
		goto failure;
	return (OK);

failure:
	if (output != NULL)
	{
		Memory_Free(output);
	}
	return (ERROR);
}



/*============================================================================*\
||                    Flow-style collections (JSON-like)                      ||
\*============================================================================*/

//! Utility to skip over whitespace/linebreaks/comments, within a flow-style collection
static
t_bool	YAML_Parse_Flow_SkipWhiteSpace(s_yaml_parse* p)
{
	while (CAN_PARSE(0))
	{
		if (p->content[p->offset] == '\n')
			p->line++;
		else if (p->content[p->offset] == '#')
		{
			while (CAN_PARSE(0) && !YAML_ISLINEBREAK(p->content[p->offset]))
				p->offset++;
			continue;
		}
		else if (p->content[p->offset] != ' ' &&
				p->content[p->offset] != '\t' &&
				p->content[p->offset] != '\r')
			break;
		p->offset++;
	}
	return (OK);
}

static
t_bool	YAML_Parse_FlowArray(s_yaml* item, s_yaml_parse* p)
{
	s_yaml* head = NULL; // head of the linked list
	s_yaml* current_item = NULL;
	t_uint index;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_YAML("Could not parse YAML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;

	if (!CAN_PARSE(0))
		PARSINGERROR_YAML("Could not parse flow sequence: Unexpected end of input before sequence")
	if (p->content[p->offset] != '[')
		PARSINGERROR_YAML("Could not parse flow sequence: Expected '[' char to begin sequence, instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	YAML_Parse_Flow_SkipWhiteSpace(p);
	if (CAN_PARSE(0) && (p->content[p->offset] == ']'))
		goto success; // empty array
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_YAML("Could not parse flow sequence: Unexpected end of input after '[' sequence start char")
	}
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated array elements
	index = 0;
	do
	{
		p->offset++;
		YAML_Parse_Flow_SkipWhiteSpace(p);
		if (CAN_PARSE(0) && (p->content[p->offset] == ']'))
		{
			if (p->strict)
				PARSINGERROR_YAML("Inside flow sequence: trailing commas are not accepted in strict YAML")
			goto success; // allow trailing commas when not in strict mode
		}
		// allocate next item
		s_yaml* new_item = YAML_Item();
		if (new_item == NULL)
			PARSINGERROR_YAML("Could not parse flow sequence: Allocation failure")
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
		// parse next value
		if (YAML_Parse_FlowValue(current_item, p, TRUE))
			PARSINGERROR_YAML("Inside flow sequence: failed to parse value within sequence, at index " SF_UINT, index)
		YAML_Parse_Flow_SkipWhiteSpace(p);
		index++;
	}
	while (CAN_PARSE(0) && p->content[p->offset] == ',');

	if (!CAN_PARSE(0))
		PARSINGERROR_YAML("Could not parse flow sequence: Unexpected end of input within sequence")
	if (p->content[p->offset] != ']')
		PARSINGERROR_YAML("Could not parse flow sequence: Expected end of sequence ']' char, instead found '%c'/0x%2X",
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
		YAML_Delete(head);
	}
	return (ERROR);
}

static
t_bool	YAML_Parse_FlowObject(s_yaml* item, s_yaml_parse* p)
{
	s_yaml* head = NULL; // linked list head
	s_yaml* new_item = NULL;
	s_yaml* current_item = NULL;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_YAML("Could not parse YAML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;
	if (!CAN_PARSE(0) || (p->content[p->offset] != '{'))
		PARSINGERROR_YAML("Could not parse flow mapping: Expected '{' to begin mapping, instead found '%c'/0x%2X",
			(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	YAML_Parse_Flow_SkipWhiteSpace(p);
	if (CAN_PARSE(0) && (p->content[p->offset] == '}'))
		goto success; // empty object
	if (!CAN_PARSE(0))
	{
		p->offset--;
		PARSINGERROR_YAML("Could not parse flow mapping: Unexpected end of input after '{' mapping start char")
	}
	// step back to character in front of the first element
	p->offset--;
	// loop through the comma separated key/value pairs
	do
	{
		p->offset++;
		YAML_Parse_Flow_SkipWhiteSpace(p);
		if (CAN_PARSE(0) && (p->content[p->offset] == '}'))
		{
			if (p->strict)
				PARSINGERROR_YAML("Inside flow mapping: trailing commas are not accepted in strict YAML")
			goto success; // allow trailing commas when not in strict mode
		}
		// allocate next item
		new_item = YAML_Item();
		if (new_item == NULL)
			PARSINGERROR_YAML("Could not parse flow mapping: Allocation failure")
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
		// parse the key of the child
		if (p->content[p->offset] == '\"' ||
			p->content[p->offset] == '\'')
		{
			if (YAML_Parse_String(current_item, p))
				PARSINGERROR_YAML("Could not parse flow mapping: Failed to parse mapping member key")
			// swap value.string and key, because we parsed the key
			current_item->key = current_item->value.string;
			current_item->value.string = NULL;
			current_item->type = DYNAMICTYPE_INVALID;
		}
		else
		{	// plain key: scan raw text until the ':' key/value separator char
			t_size	length = 0;
			t_size	content_length = 0;
			while (CAN_PARSE(length) && !YAML_ISLINEBREAK(p->content[p->offset + length]))
			{
				t_utf8 c = p->content[p->offset + length];
				if (c == ':' || c == ',' || c == '}' || c == ']')
					break;
				++length;
				if (c != ' ' && c != '\t')
					content_length = length; // used to trim trailing whitespace
			}
			if (content_length == 0)
				PARSINGERROR_YAML("Could not parse flow mapping: empty mapping member key")
			current_item->key = String_Sub(p->content, p->offset, content_length);
			if (current_item->key == NULL)
				PARSINGERROR_YAML("Could not parse flow mapping: allocation failure when copying key")
			p->offset += length;
		}
		YAML_Parse_Flow_SkipWhiteSpace(p);
		if (!CAN_PARSE(0))
			PARSINGERROR_YAML("Could not parse flow mapping: Unexpected end of input after mapping member key")
		if (p->content[p->offset] != ':')
			PARSINGERROR_YAML("Could not parse flow mapping: Invalid mapping key/value pair, expected ':' char, instead found '%c'/0x%2X",
				(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
		// parse the value
		p->offset++;
		YAML_Parse_Flow_SkipWhiteSpace(p);
		if (YAML_Parse_FlowValue(current_item, p, TRUE))
			PARSINGERROR_YAML("Inside flow mapping: Failed to parse mapping member value (key is \"%s\")", current_item->key)
		YAML_Parse_Flow_SkipWhiteSpace(p);
	}
	while (CAN_PARSE(0) && (p->content[p->offset] == ','));

	if (!CAN_PARSE(0))
		PARSINGERROR_YAML("Could not parse flow mapping: Unexpected end of input within mapping")
	if (p->content[p->offset] != '}')
		PARSINGERROR_YAML("Could not parse flow mapping: Expected end of mapping char '}', instead found '%c'/0x%2X",
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
		YAML_Delete(head);
	}
	return (ERROR);
}

//! Parses any value which can occur within a flow context (or after a `key:` on the same line)
static
t_bool	YAML_Parse_FlowValue(s_yaml* item, s_yaml_parse* p, t_bool in_flow)
{
	if ((p == NULL) || (p->content == NULL) || !CAN_PARSE(0))
		PARSINGERROR_YAML("Unexpected end of input, unable to parse YAML value")
	if (p->content[p->offset] == '[')
		return (YAML_Parse_FlowArray(item, p));		// flow sequence
	if (p->content[p->offset] == '{')
		return (YAML_Parse_FlowObject(item, p));	// flow mapping
	if (p->content[p->offset] == '\"' ||
		p->content[p->offset] == '\'')
		return (YAML_Parse_String(item, p));		// quoted string
	if (in_flow && (
		p->content[p->offset] == ',' ||
		p->content[p->offset] == ']' ||
		p->content[p->offset] == '}'))
	{	// empty value within a flow collection
		item->type = DYNAMICTYPE_NULL;
		return (OK);
	}
	if (p->content[p->offset] == '&' ||
		p->content[p->offset] == '*')
		PARSINGERROR_YAML("YAML anchors ('&') and aliases ('*') are not supported by this parser")
	if (p->content[p->offset] == '!')
		PARSINGERROR_YAML("YAML tags ('!') are not supported by this parser")
	if (p->content[p->offset] == '@' ||
		p->content[p->offset] == '`')
		PARSINGERROR_YAML("The chars '@' and '`' are reserved chars in YAML, and cannot begin a plain scalar")
	return (YAML_Parse_Scalar(item, p, in_flow));	// plain scalar

failure:
	return (ERROR);
}



/*============================================================================*\
||                          Block-style collections                           ||
\*============================================================================*/

//! Checks whether the current line holds a block mapping `key: value` pair
/*!
**	This is done by scanning ahead for a ':' char (outside of any quotes/flow collections)
**	which is immediately followed by a whitespace char, or by the end of the line.
*/
static
t_bool	YAML_Parse_IsMappingLine(s_yaml_parse* p)
{
	t_size	i = 0;
	t_utf8	quote = '\0';
	t_sint	flow_depth = 0;

	while (CAN_PARSE(i) && !YAML_ISLINEBREAK(p->content[p->offset + i]))
	{
		t_utf8 c = p->content[p->offset + i];
		if (quote != '\0')
		{
			if (c == '\\' && quote == '\"')
				++i;
			else if (c == quote)
				quote = '\0';
		}
		else if (c == '\"' || c == '\'')
			quote = c;
		else if (c == '[' || c == '{')
			flow_depth++;
		else if (c == ']' || c == '}')
			flow_depth--;
		else if (c == '#' && i > 0 && (
			p->content[p->offset + i - 1] == ' ' ||
			p->content[p->offset + i - 1] == '\t'))
			return (FALSE); // comment: end of line content
		else if (c == ':' && flow_depth == 0 && (
			!CAN_PARSE(i + 1) ||
			p->content[p->offset + i + 1] == ' ' ||
			p->content[p->offset + i + 1] == '\t' ||
			YAML_ISLINEBREAK(p->content[p->offset + i + 1]) ||
			(p->content[p->offset + i + 1] == '\r' && CAN_PARSE(i + 2) && YAML_ISLINEBREAK(p->content[p->offset + i + 2]))))
			return (TRUE);
		++i;
	}
	return (FALSE);
}

//! Parses a block mapping key (plain or quoted), consuming the ':' char which follows it
static
t_bool	YAML_Parse_Key(s_yaml* item, s_yaml_parse* p)
{
	t_utf8*	key = NULL;

	if (!CAN_PARSE(0))
		PARSINGERROR_YAML("Could not parse mapping key: Unexpected end of input before key")
	if (item->key)
		PARSINGERROR_YAML("Could not parse mapping key: Key is already assigned: \"%s\"", item->key)
	if (p->content[p->offset] == '?')
		PARSINGERROR_YAML("Explicit key notation ('?') is not supported by this parser")
	if (p->content[p->offset] == '\"' ||
		p->content[p->offset] == '\'')
	{	// quoted key
		s_yaml*	tmp = YAML_Item();
		if (tmp == NULL)
			PARSINGERROR_YAML("Could not parse mapping key: allocation failure")
		if (YAML_Parse_String(tmp, p))
		{
			YAML_Delete(tmp);
			PARSINGERROR_YAML("Could not parse mapping key: Failed to parse quoted key string")
		}
		// swap value.string and .key, because we parsed the key
		key = tmp->value.string;
		tmp->value.string = NULL;
		YAML_Delete(tmp);
	}
	else
	{	// plain key: scan until the ':' key/value separator char
		t_size	length = 0;
		t_size	content_length = 0;
		while (CAN_PARSE(length) && !YAML_ISLINEBREAK(p->content[p->offset + length]))
		{
			t_utf8 c = p->content[p->offset + length];
			if (c == ':' && (
				!CAN_PARSE(length + 1) ||
				p->content[p->offset + length + 1] == ' ' ||
				p->content[p->offset + length + 1] == '\t' ||
				YAML_ISLINEBREAK(p->content[p->offset + length + 1]) ||
				(p->content[p->offset + length + 1] == '\r' && CAN_PARSE(length + 2) && YAML_ISLINEBREAK(p->content[p->offset + length + 2]))))
				break;
			++length;
			if (c != ' ' && c != '\t')
				content_length = length; // used to trim trailing whitespace
		}
		if (content_length == 0)
			PARSINGERROR_YAML("Could not parse mapping key: empty key string")
		key = String_Sub(p->content, p->offset, content_length);
		if (key == NULL)
			PARSINGERROR_YAML("Could not parse mapping key: allocation failure when copying key")
		p->offset += length;
	}
	// consume the ':' key/value separator char
	YAML_Parse_SkipSpaces(p);
	if (!CAN_PARSE(0) || p->content[p->offset] != ':')
		PARSINGERROR_YAML("Could not parse mapping key: Expected ':' char after key \"%s\", instead found '%c'/0x%4.4X",
			key, (p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
	p->offset++;
	item->key = key;
	return (OK);

failure:
	if (key != NULL)
		String_Delete(&key);
	return (ERROR);
}

//! Parses the value assigned to a mapping key (i.e. everything after the ':' char)
static
t_bool	YAML_Parse_MappingValue(s_yaml* item, s_yaml_parse* p, t_size indent)
{
	t_bool	end = FALSE;
	t_size	child_indent;

	YAML_Parse_SkipSpaces(p);
	if (YAML_Parse_IsLineEnd(p))
	{	// no value on this line: the value is a nested block (or null)
		if (YAML_Parse_SkipToNextLine(p))
			goto failure;
		if (YAML_Parse_GotoNextContent(p, &end))
			goto failure;
		if (end)
		{	// end of input: the value is null
			item->type = DYNAMICTYPE_NULL;
			return (OK);
		}
		child_indent = YAML_Parse_GetIndent(p);
		if (child_indent > indent)
			return (YAML_Parse_Block(item, p, child_indent));
		if (child_indent == indent &&
			p->content[p->offset] == '-' && (
			!CAN_PARSE(1) ||
			p->content[p->offset + 1] == ' ' ||
			p->content[p->offset + 1] == '\t' ||
			YAML_ISLINEBREAK(p->content[p->offset + 1])))
		{	// a block sequence is allowed to be at the same indentation level as its parent mapping key
			return (YAML_Parse_Sequence(item, p, indent));
		}
		// the pending line belongs to a parent node: the value is null
		item->type = DYNAMICTYPE_NULL;
		return (OK);
	}
	if (p->content[p->offset] == '|' ||
		p->content[p->offset] == '>')
	{	// block scalar value
		return (YAML_Parse_BlockScalar(item, p, indent));
	}
	// in-line value (plain scalar, quoted string, or flow collection)
	if (YAML_Parse_FlowValue(item, p, FALSE))
		goto failure;
	if (YAML_Parse_SkipToNextLine(p))
		goto failure;
	if (YAML_Parse_GotoNextContent(p, &end))
		goto failure;
	return (OK);

failure:
	return (ERROR);
}

static
t_bool	YAML_Parse_Mapping(s_yaml* item, s_yaml_parse* p, t_size indent)
{
	s_yaml* head = NULL; // linked list head
	s_yaml* current_item = NULL;
	s_yaml*	new_item = NULL;
	s_yaml*	tmp = NULL;
	t_size	next_indent;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_YAML("Could not parse YAML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		// allocate next item
		new_item = YAML_Item();
		if (new_item == NULL)
			PARSINGERROR_YAML("Could not parse block mapping: Allocation failure")
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
		// parse the key, and the ':' separator char
		if (YAML_Parse_Key(current_item, p))
			PARSINGERROR_YAML("Could not parse block mapping: error while parsing key")
		// check for name conflicts with any previous keys within this mapping
		for (tmp = head; tmp != current_item; tmp = tmp->next)
		{
			if (tmp->key && String_Equals(tmp->key, current_item->key))
				PARSINGERROR_YAML("Could not parse block mapping: name conflict, mapping key already exists: \"%s\"", current_item->key)
		}
		// parse the value
		if (YAML_Parse_MappingValue(current_item, p, indent))
			PARSINGERROR_YAML("Could not parse block mapping: error while parsing value assigned to key \"%s\"", current_item->key)
		// after each key/value pair, the offset is at the first content char of the next content line (or at the end)
		if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
			break;
		if (YAML_Parse_GetIndent(p) == 0 && (
			YAML_Parse_IsDocumentMarker(p, '.') ||
			YAML_Parse_IsDocumentMarker(p, '-')))
			break; // end of the current document
		next_indent = YAML_Parse_GetIndent(p);
		if (next_indent < indent)
			break; // the pending line belongs to a parent node
		if (next_indent > indent)
			PARSINGERROR_YAML("Could not parse block mapping: invalid indentation (" SF_SIZE " chars, expected " SF_SIZE " chars) for line: \"%.16s\"",
				next_indent, indent, p->content + p->offset)
	}
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMICTYPE_OBJECT;
	item->value.child = head;
	return (OK);

failure:
	if (head != NULL)
	{
		YAML_Delete(head);
	}
	return (ERROR);
}

static
t_bool	YAML_Parse_Sequence(s_yaml* item, s_yaml_parse* p, t_size indent)
{
	s_yaml* head = NULL; // linked list head
	s_yaml* current_item = NULL;
	s_yaml*	new_item = NULL;
	t_size	next_indent;
	t_uint	index = 0;
	t_bool	end = FALSE;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_YAML("Could not parse YAML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (p->content[p->offset] != '-')
			PARSINGERROR_YAML("Could not parse block sequence: Expected '-' item indicator char, instead found '%c'/0x%4.4X",
				(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
		p->offset++;
		if (CAN_PARSE(0) &&
			p->content[p->offset] != ' ' &&
			p->content[p->offset] != '\t' &&
			!YAML_Parse_IsLineEnd(p))
			PARSINGERROR_YAML("Could not parse block sequence: Expected whitespace after '-' item indicator char, instead found '%c'/0x%4.4X",
				(p->content[p->offset] ? p->content[p->offset] : '\a'), p->content[p->offset])
		// allocate next item
		new_item = YAML_Item();
		if (new_item == NULL)
			PARSINGERROR_YAML("Could not parse block sequence: Allocation failure")
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
		// parse the item's value
		YAML_Parse_SkipSpaces(p);
		if (YAML_Parse_IsLineEnd(p))
		{	// no value on this line: the item is a nested block (or null)
			if (YAML_Parse_SkipToNextLine(p))
				goto failure;
			if (YAML_Parse_GotoNextContent(p, &end))
				goto failure;
			if (end)
			{	// end of input: the item is null
				current_item->type = DYNAMICTYPE_NULL;
				break;
			}
			next_indent = YAML_Parse_GetIndent(p);
			if (next_indent > indent)
			{
				if (YAML_Parse_Block(current_item, p, next_indent))
					PARSINGERROR_YAML("Inside block sequence: failed to parse item at index " SF_UINT, index)
			}
			else current_item->type = DYNAMICTYPE_NULL;
		}
		else
		{	// in-line item value: everything after the "- " is a nested block, indented at its column
			if (YAML_Parse_Block(current_item, p, YAML_Parse_GetIndent(p)))
				PARSINGERROR_YAML("Inside block sequence: failed to parse item at index " SF_UINT, index)
		}
		index++;
		// after each item, the offset is at the first content char of the next content line (or at the end)
		if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
			break;
		if (YAML_Parse_GetIndent(p) == 0 && (
			YAML_Parse_IsDocumentMarker(p, '.') ||
			YAML_Parse_IsDocumentMarker(p, '-')))
			break; // end of the current document
		next_indent = YAML_Parse_GetIndent(p);
		if (next_indent < indent)
			break; // the pending line belongs to a parent node
		if (next_indent > indent)
			PARSINGERROR_YAML("Could not parse block sequence: invalid indentation (" SF_SIZE " chars, expected " SF_SIZE " chars) for line: \"%.16s\"",
				next_indent, indent, p->content + p->offset)
		if (p->content[p->offset] != '-')
			break; // the pending line is not a sequence item: it belongs to a parent node (e.g. a mapping at the same indent)
	}
	p->depth--;
	if (head != NULL)
	{
		head->prev = current_item;
	}
	item->type = DYNAMICTYPE_ARRAY;
	item->value.child = head;
	return (OK);

failure:
	if (head != NULL)
	{
		YAML_Delete(head);
	}
	return (ERROR);
}

//! Parses any block-context node: dispatches to sequence/mapping/scalar parsing accordingly
/*!
**	Expects the parsing offset to be at the first content char of the node, with the given `indent`.
**	Upon success, the parsing offset will be at the first content char of the next content line
**	whose indentation is lesser than the given `indent` (or at the end of the input/document).
*/
static
t_bool	YAML_Parse_Block(s_yaml* item, s_yaml_parse* p, t_size indent)
{
	t_bool	end = FALSE;

	if ((p == NULL) || (p->content == NULL) || !CAN_PARSE(0))
		PARSINGERROR_YAML("Unexpected end of input, unable to parse YAML value")
	if (p->content[p->offset] == '-' && (
		!CAN_PARSE(1) ||
		p->content[p->offset + 1] == ' ' ||
		p->content[p->offset + 1] == '\t' ||
		YAML_ISLINEBREAK(p->content[p->offset + 1])))
	{	// block sequence
		return (YAML_Parse_Sequence(item, p, indent));
	}
	if (p->content[p->offset] == '&' ||
		p->content[p->offset] == '*')
		PARSINGERROR_YAML("YAML anchors ('&') and aliases ('*') are not supported by this parser")
	if (p->content[p->offset] == '!')
		PARSINGERROR_YAML("YAML tags ('!') are not supported by this parser")
	if (p->content[p->offset] == '?')
		PARSINGERROR_YAML("Explicit key notation ('?') is not supported by this parser")
	if (p->content[p->offset] != '[' &&
		p->content[p->offset] != '{' &&
		YAML_Parse_IsMappingLine(p))
	{	// block mapping
		return (YAML_Parse_Mapping(item, p, indent));
	}
	if (p->content[p->offset] == '|' ||
		p->content[p->offset] == '>')
	{	// block scalar
		return (YAML_Parse_BlockScalar(item, p, indent));
	}
	// in-line value (plain scalar, quoted string, or flow collection)
	if (YAML_Parse_FlowValue(item, p, FALSE))
		goto failure;
	if (YAML_Parse_SkipToNextLine(p))
		goto failure;
	if (YAML_Parse_GotoNextContent(p, &end))
		goto failure;
	return (OK);

failure:
	return (ERROR);
}



/*============================================================================*\
||                          Main parsing entry points                         ||
\*============================================================================*/

static
t_size	YAML_Parse_(s_yaml* *dest, t_utf8 const* str, t_size n, t_bool strict)
{
	s_yaml_parse	parser;
	s_yaml_parse*	p = &parser;
	s_yaml*	result = NULL;
	t_size	column = 0;
	t_bool	end = FALSE;

	Memory_Clear(p, sizeof(s_yaml_parse));
	if CCCERROR((n < 1), ERROR_LENGTH2SMALL, NULL)
	{
		if (dest) *dest = NULL;
		return (p->offset);
	}
	p->content = str;
	p->length = n; 
	p->offset = CharUTF8_ByteOrderMark(str);
	p->strict = strict;
	p->line = 1;
	result = YAML_Item();
	if (result == NULL)
		PARSINGERROR_YAML("Got null result: memory failure")
	if (YAML_Parse_GotoNextContent(p, &end))
		goto failure;
	if (end && YAML_Parse_IsDocumentMarker(p, '-'))
	{	// consume the (optional) document start marker line: `---`
		p->offset += 3;
		if (YAML_Parse_SkipToNextLine(p))
			goto failure;
		if (YAML_Parse_GotoNextContent(p, &end))
			goto failure;
	}
	if (end)
	{	// an empty document is a single null value
		result->type = DYNAMICTYPE_NULL;
	}
	else if (YAML_Parse_Block(result, p, YAML_Parse_GetIndent(p)))
		goto failure;
	// check for any trailing garbage chars after the root-level node
	if (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (YAML_Parse_GotoNextContent(p, &end))
			goto failure;
		if (!end && CAN_PARSE(0) && p->content[p->offset] != '\0')
			PARSINGERROR_YAML("Invalid YAML: unexpected garbage chars after root-level node: \"%.16s\"", p->content + p->offset)
	}
	if (dest)	*dest = result;
	return (p->offset);

failure:
	if (result != NULL)
	{
		YAML_Delete(result);
		result = NULL;
	}
	while (p->offset - column != 0)
	{
		if (p->content[p->offset - column] == '\n')
			break;
		column++;
	}
	if CCCERROR(TRUE, ERROR_PARSE,
		"at nesting depth " SF_UINT ": line " SF_SIZE ", column " SF_SIZE " (char index " SF_SIZE ": '%c'/0x%2X)%s\n",
		p->depth,
		p->line,
		column,
		p->offset,
		p->content[p->offset] ? p->content[p->offset] : '\a',
		p->content[p->offset],
		p->error)
	{
		if (dest) *dest = NULL;
		String_Delete(&p->error);
		return (p->offset);
	}
	String_Delete(&p->error);
	return (p->offset);
}



t_size	YAML_Parse_Lenient(s_yaml* *dest, t_utf8 const* str, t_size n)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")
		return (SIZE_ERROR);
	if (n == 0)
		n = String_Length(str);
	return (YAML_Parse_(dest, str, n, FALSE));
}

t_size	YAML_Parse_Strict(s_yaml* *dest, t_utf8 const* str, t_size n)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")
		return (SIZE_ERROR);
	if (n == 0)
		n = String_Length(str);
	return (YAML_Parse_(dest, str, n, TRUE));
}



s_yaml*	YAML_FromString_Lenient(t_utf8 const* str)
{
	s_yaml*	result;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")
		return (NULL);
	YAML_Parse_(&result, str, String_Length(str), FALSE);
	return (result);
}

s_yaml*	YAML_FromString_Strict(t_utf8 const* str)
{
	s_yaml*	result;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to parse given is NULL")
		return (NULL);
	YAML_Parse_(&result, str, String_Length(str), TRUE);
	return (result);
}
