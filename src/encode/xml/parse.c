
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/text/format.h"
#include "libccc/encode/xml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_parse	s_xml_parse;



static t_bool	XML_Parse_Element	(s_xml* item, s_xml_parse* p);



//! String which is at the beginning of each error log output line
#define PARSINGERROR_XML_PREFIX	"\n -> "

//! used to handle errors during parsing
#define PARSINGERROR_XML(...) \
	{ \
		t_char* tmp_error; \
		tmp_error = String_Format(__VA_ARGS__); \
		tmp_error = String_Prepend(PARSINGERROR_XML_PREFIX, &tmp_error); \
		if (p != NULL) \
		{ p->error = (p->error == NULL ? tmp_error : String_Merge(&p->error, &tmp_error)); } \
		else String_Delete(&tmp_error); \
		goto failure; \
	} \

//! Safely checks if the content to parse can be accessed at the given index
#define CAN_PARSE(X) \
	((p->content != NULL) && ((p->offset + X) <= p->length))

//! Checks whether the given char is an XML whitespace char
#define XML_ISWHITESPACE(C) \
	((C) == ' ' || (C) == '\t' || (C) == '\r' || (C) == '\n')



/*============================================================================*\
||                              Utility functions                             ||
\*============================================================================*/

//! Checks whether the given char can be the first char of an XML tag/attribute name
/*!
**	NOTE: any non-ASCII (multi-byte UTF-8) char is accepted permissively here,
**	rather than checking the exact unicode ranges given by the XML spec.
*/
static
t_bool	XML_Parse_IsNameStartChar(t_utf8 c)
{
	return (Char_IsLetter(c) || c == '_' || c == ':' || ((t_u8)c >= 0x80));
}

//! Checks whether the given char can occur within an XML tag/attribute name
static
t_bool	XML_Parse_IsNameChar(t_utf8 c)
{
	return (XML_Parse_IsNameStartChar(c) || Char_IsDigit(c) || c == '-' || c == '.');
}

//! Checks whether the string at the current parsing offset matches the given (short) string
static
t_bool	XML_Parse_Matches(s_xml_parse* p, t_utf8 const* str)
{
	t_size	length = String_Length((t_char const*)str);

	if (!CAN_PARSE(length))
		return (FALSE);
	return (String_Equals_N(p->content + p->offset, str, length));
}

//! Skips over any whitespace chars at the current parsing offset (keeping track of line count)
static
void	XML_Parse_SkipWhitespace(s_xml_parse* p)
{
	while (CAN_PARSE(0) && XML_ISWHITESPACE(p->content[p->offset]))
	{
		if (p->content[p->offset] == '\n')
			p->line++;
		p->offset++;
	}
}



//! A simple growable text buffer, used to accumulate decoded text content
typedef struct xml_textbuffer
{
	t_utf8*	data;
	t_size	length;
	t_size	capacity;
}	s_xml_textbuffer;

//! Appends `length` chars from the given `str` to the given text buffer `buffer`
static
t_bool	XML_TextBuffer_Append(s_xml_textbuffer* buffer, t_utf8 const* str, t_size length)
{
	t_utf8*	tmp;
	t_size	needed = buffer->length + length + 1;

	if (needed > buffer->capacity)
	{
		buffer->capacity = (buffer->capacity == 0 ? 64 : buffer->capacity);
		while (buffer->capacity < needed)
			buffer->capacity *= 2;
		tmp = (t_utf8*)Memory_Reallocate(buffer->data, buffer->capacity);
		if (tmp == NULL)
			return (ERROR);
		buffer->data = tmp;
	}
	Memory_Copy(buffer->data + buffer->length, str, length);
	buffer->length += length;
	buffer->data[buffer->length] = '\0';
	return (OK);
}



/*============================================================================*\
||                        Names, entities, text content                       ||
\*============================================================================*/

//! Parses an XML tag/attribute name at the current parsing offset
static
t_bool	XML_Parse_Name(t_utf8* *dest, s_xml_parse* p)
{
	t_size	start = p->offset;

	if (!CAN_PARSE(0) || !XML_Parse_IsNameStartChar(p->content[p->offset]))
		PARSINGERROR_XML("Expected a valid XML name start char, instead found: '%c'/0x%2.2X",
			(CAN_PARSE(0) && p->content[p->offset] ? p->content[p->offset] : '\a'),
			(CAN_PARSE(0) ? p->content[p->offset] : 0))
	p->offset++;
	while (CAN_PARSE(0) && XML_Parse_IsNameChar(p->content[p->offset]))
		p->offset++;
	*dest = String_Sub(p->content, start, (p->offset - start));
	if (*dest == NULL)
		PARSINGERROR_XML("Could not parse XML name: Allocation failure")
	return (OK);

failure:
	return (ERROR);
}

//! Parses an entity/character reference (`&...;`) and appends the decoded char(s) to `buffer`
/*!
**	Expects the parsing offset to be at the leading `&` char.
**	Handles the five XML predefined entities, as well as
**	decimal (`&#NNN;`) and hexadecimal (`&#xHH;`) character references.
**	In lenient mode, unknown entity references are kept verbatim in the text.
*/
static
t_bool	XML_Parse_Reference(s_xml_textbuffer* buffer, s_xml_parse* p)
{
	t_utf8	utf8[8] = {0};
	t_utf32	c = 0;
	t_size	start = p->offset;
	t_size	length;

	p->offset++; // skip '&'
	if (CAN_PARSE(0) && p->content[p->offset] == '#')
	{	// numeric character reference
		p->offset++;
		if (CAN_PARSE(0) && (p->content[p->offset] == 'x' || p->content[p->offset] == 'X'))
		{
			p->offset++;
			if (!CAN_PARSE(0) || !Char_IsDigit_Hex(p->content[p->offset]))
				PARSINGERROR_XML("Expected hexadecimal digits in XML character reference")
			while (CAN_PARSE(0) && Char_IsDigit_Hex(p->content[p->offset]))
			{
				c = (c * 16) + (t_utf32)(
					Char_IsDigit(p->content[p->offset]) ? (p->content[p->offset] - '0') :
					(p->content[p->offset] | 0x20) - 'a' + 10);
				p->offset++;
			}
		}
		else
		{
			if (!CAN_PARSE(0) || !Char_IsDigit(p->content[p->offset]))
				PARSINGERROR_XML("Expected decimal digits in XML character reference")
			while (CAN_PARSE(0) && Char_IsDigit(p->content[p->offset]))
			{
				c = (c * 10) + (t_utf32)(p->content[p->offset] - '0');
				p->offset++;
			}
		}
		if (!CAN_PARSE(0) || p->content[p->offset] != ';')
			PARSINGERROR_XML("Expected ';' char to end XML character reference")
		p->offset++;
		length = CharUTF32_ToUTF8(utf8, c);
		if (length == 0 || length == SIZE_ERROR)
			PARSINGERROR_XML("Invalid unicode codepoint in XML character reference: U+%4.4X", c)
		return (XML_TextBuffer_Append(buffer, utf8, length));
	}
	// named entity reference
	if      (XML_Parse_Matches(p, "lt;"))  	{ p->offset += 3;	return (XML_TextBuffer_Append(buffer, "<", 1)); }
	else if (XML_Parse_Matches(p, "gt;"))  	{ p->offset += 3;	return (XML_TextBuffer_Append(buffer, ">", 1)); }
	else if (XML_Parse_Matches(p, "amp;")) 	{ p->offset += 4;	return (XML_TextBuffer_Append(buffer, "&", 1)); }
	else if (XML_Parse_Matches(p, "apos;"))	{ p->offset += 5;	return (XML_TextBuffer_Append(buffer, "'", 1)); }
	else if (XML_Parse_Matches(p, "quot;"))	{ p->offset += 5;	return (XML_TextBuffer_Append(buffer, "\"", 1)); }
	if (p->strict)
		PARSINGERROR_XML("Unknown XML entity reference: \"%.8s\" (custom `<!ENTITY>` definitions are not supported)",
			p->content + start)
	// lenient mode: keep the unknown entity reference verbatim
	return (XML_TextBuffer_Append(buffer, p->content + start, (p->offset - start)));

failure:
	return (ERROR);
}

//! Parses a run of text content, until the next `<` char, decoding any entity references
/*!
**	The decoded text is appended to the given `buffer`, with leading/trailing
**	whitespace trimmed (a single space char is inserted between separate segments).
*/
static
t_bool	XML_Parse_Text(s_xml_textbuffer* buffer, s_xml_parse* p)
{
	t_size	start;
	t_size	end;
	t_size	trimmed_end;
	t_bool	segment_started = FALSE;

	// skip leading whitespace of this text segment
	XML_Parse_SkipWhitespace(p);
	while (CAN_PARSE(0) &&
		p->content[p->offset] != '<' &&
		p->content[p->offset] != '\0')
	{
		if (p->content[p->offset] == '&')
		{
			if (!segment_started && buffer->length > 0)
			{	// separate this segment from any previous text with a single space
				if (XML_TextBuffer_Append(buffer, " ", 1))
					PARSINGERROR_XML("Could not parse XML text content: Allocation failure")
			}
			segment_started = TRUE;
			if (XML_Parse_Reference(buffer, p))
				PARSINGERROR_XML("Could not parse XML entity/character reference")
			continue;
		}
		// scan a run of plain chars (until any entity ref, tag, or end of line)
		start = p->offset;
		while (CAN_PARSE(0) &&
			p->content[p->offset] != '<' &&
			p->content[p->offset] != '&' &&
			p->content[p->offset] != '\0')
		{
			if (p->strict && p->content[p->offset] == '>' &&
				p->offset >= 2 && String_Equals_N(p->content + p->offset - 2, "]]", 2))
				PARSINGERROR_XML("The literal sequence \"]]>\" is not allowed in XML text content")
			if (p->content[p->offset] == '\n')
				p->line++;
			p->offset++;
		}
		end = p->offset;
		// trim trailing whitespace (only if this marks the end of the text run)
		trimmed_end = end;
		if (!CAN_PARSE(0) || p->content[p->offset] != '&')
		{
			while (trimmed_end > start && XML_ISWHITESPACE(p->content[trimmed_end - 1]))
				trimmed_end--;
		}
		if (trimmed_end > start)
		{
			if (!segment_started && buffer->length > 0)
			{	// separate this segment from any previous text with a single space
				if (XML_TextBuffer_Append(buffer, " ", 1))
					PARSINGERROR_XML("Could not parse XML text content: Allocation failure")
			}
			segment_started = TRUE;
			if (XML_TextBuffer_Append(buffer, p->content + start, (trimmed_end - start)))
				PARSINGERROR_XML("Could not parse XML text content: Allocation failure")
		}
	}
	return (OK);

failure:
	return (ERROR);
}

//! Parses a `<![CDATA[ ... ]]>` section, appending its contents verbatim to the given `buffer`
static
t_bool	XML_Parse_CDATA(s_xml_textbuffer* buffer, s_xml_parse* p)
{
	t_size	start;

	p->offset += 9; // skip "<![CDATA["
	start = p->offset;
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (XML_Parse_Matches(p, "]]>"))
		{
			if (XML_TextBuffer_Append(buffer, p->content + start, (p->offset - start)))
				PARSINGERROR_XML("Could not parse XML CDATA section: Allocation failure")
			p->offset += 3;
			return (OK);
		}
		if (p->content[p->offset] == '\n')
			p->line++;
		p->offset++;
	}
	PARSINGERROR_XML("Unexpected end of input within XML CDATA section (expected \"]]>\")")

failure:
	return (ERROR);
}



/*============================================================================*\
||                     Comments, PIs, DOCTYPE, misc content                   ||
\*============================================================================*/

//! Parses (skips) an XML comment: `<!-- ... -->`
static
t_bool	XML_Parse_Comment(s_xml_parse* p)
{
	p->offset += 4; // skip "<!--"
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (XML_Parse_Matches(p, "--"))
		{
			if (CAN_PARSE(2) && p->content[p->offset + 2] == '>')
			{
				p->offset += 3;
				return (OK);
			}
			if (p->strict)
				PARSINGERROR_XML("The literal sequence \"--\" is not allowed within an XML comment")
			p->offset += 2;
			continue;
		}
		if (p->content[p->offset] == '\n')
			p->line++;
		p->offset++;
	}
	PARSINGERROR_XML("Unexpected end of input within XML comment (expected \"-->\")")

failure:
	return (ERROR);
}

//! Parses (skips) an XML processing instruction (or XML declaration): `<? ... ?>`
static
t_bool	XML_Parse_ProcessingInstruction(s_xml_parse* p)
{
	p->offset += 2; // skip "<?"
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (XML_Parse_Matches(p, "?>"))
		{
			p->offset += 2;
			return (OK);
		}
		if (p->content[p->offset] == '\n')
			p->line++;
		p->offset++;
	}
	PARSINGERROR_XML("Unexpected end of input within XML processing instruction (expected \"?>\")")

failure:
	return (ERROR);
}

//! Parses (skips) a `<!DOCTYPE ... >` declaration (DTD content is not processed)
static
t_bool	XML_Parse_Doctype(s_xml_parse* p)
{
	t_utf8	quote;

	p->offset += 9; // skip "<!DOCTYPE"
	while (CAN_PARSE(0) && p->content[p->offset] != '\0')
	{
		if (p->content[p->offset] == '>')
		{
			p->offset += 1;
			return (OK);
		}
		if (p->content[p->offset] == '"' ||
			p->content[p->offset] == '\'')
		{	// skip quoted literals (which may contain '>' or '[' chars)
			quote = p->content[p->offset];
			p->offset++;
			while (CAN_PARSE(0) && p->content[p->offset] != quote && p->content[p->offset] != '\0')
			{
				if (p->content[p->offset] == '\n')
					p->line++;
				p->offset++;
			}
			if (!CAN_PARSE(0) || p->content[p->offset] != quote)
				PARSINGERROR_XML("Unexpected end of input within XML DOCTYPE declaration (unclosed quote)")
			p->offset++;
			continue;
		}
		if (p->content[p->offset] == '[')
		{	// internal DTD subset: skip until the matching ']' char
			if (p->strict)
				PARSINGERROR_XML("Internal DTD subsets (`<!DOCTYPE root [ ... ]>`) are not supported by this parser")
			while (CAN_PARSE(0) && p->content[p->offset] != ']' && p->content[p->offset] != '\0')
			{
				if (p->content[p->offset] == '\n')
					p->line++;
				p->offset++;
			}
			if (!CAN_PARSE(0) || p->content[p->offset] != ']')
				PARSINGERROR_XML("Unexpected end of input within XML DOCTYPE internal subset (expected ']')")
			p->offset++;
			continue;
		}
		if (p->content[p->offset] == '\n')
			p->line++;
		p->offset++;
	}
	PARSINGERROR_XML("Unexpected end of input within XML DOCTYPE declaration (expected '>')")

failure:
	return (ERROR);
}

//! Parses (skips) any "misc" content: whitespace, comments, and processing instructions
static
t_bool	XML_Parse_Misc(s_xml_parse* p)
{
	while (CAN_PARSE(0))
	{
		XML_Parse_SkipWhitespace(p);
		if (XML_Parse_Matches(p, "<!--"))
		{
			if (XML_Parse_Comment(p))
				goto failure;
			continue;
		}
		if (XML_Parse_Matches(p, "<?"))
		{
			if (XML_Parse_ProcessingInstruction(p))
				goto failure;
			continue;
		}
		break;
	}
	return (OK);

failure:
	return (ERROR);
}



/*============================================================================*\
||                                  Attributes                                ||
\*============================================================================*/

//! Parses an attribute value (quoted, or unquoted when in lenient mode)
/*!
**	As per the XML spec, whitespace chars within attribute values are
**	normalized: any tab/newline chars are replaced with space chars.
*/
static
t_bool	XML_Parse_AttributeValue(t_utf8* *dest, s_xml_parse* p)
{
	s_xml_textbuffer	buffer = {0};
	t_utf8	quote;
	t_utf8	c;

	*dest = NULL;
	if (CAN_PARSE(0) && (p->content[p->offset] == '"' || p->content[p->offset] == '\''))
	{
		quote = p->content[p->offset];
		p->offset++;
		while (CAN_PARSE(0) && p->content[p->offset] != quote)
		{
			if (p->content[p->offset] == '\0')
				PARSINGERROR_XML("Unexpected end of input within XML attribute value (unclosed quote)")
			if (p->content[p->offset] == '&')
			{
				if (XML_Parse_Reference(&buffer, p))
					PARSINGERROR_XML("Could not parse entity/character reference in XML attribute value")
				continue;
			}
			if (p->strict && p->content[p->offset] == '<')
				PARSINGERROR_XML("Raw '<' chars are not allowed within XML attribute values (use \"&lt;\")")
			c = p->content[p->offset];
			if (c == '\n')
				p->line++;
			if (c == '\n' || c == '\t' || c == '\r')
				c = ' '; // attribute-value whitespace normalization
			if (XML_TextBuffer_Append(&buffer, &c, 1))
				PARSINGERROR_XML("Could not parse XML attribute value: Allocation failure")
			p->offset++;
		}
		if (!CAN_PARSE(0))
			PARSINGERROR_XML("Unexpected end of input within XML attribute value (unclosed quote)")
		p->offset++; // skip closing quote
	}
	else
	{	// unquoted attribute value
		if (p->strict)
			PARSINGERROR_XML("XML attribute values must be quoted (single or double quotes)")
		while (CAN_PARSE(0) &&
			!XML_ISWHITESPACE(p->content[p->offset]) &&
			p->content[p->offset] != '>' &&
			p->content[p->offset] != '/' &&
			p->content[p->offset] != '\0')
		{
			if (p->content[p->offset] == '&')
			{
				if (XML_Parse_Reference(&buffer, p))
					PARSINGERROR_XML("Could not parse entity/character reference in XML attribute value")
				continue;
			}
			if (XML_TextBuffer_Append(&buffer, p->content + p->offset, 1))
				PARSINGERROR_XML("Could not parse XML attribute value: Allocation failure")
			p->offset++;
		}
	}
	if (buffer.data == NULL)
	{	// empty attribute value
		buffer.data = String_Duplicate("");
		if (buffer.data == NULL)
			PARSINGERROR_XML("Could not parse XML attribute value: Allocation failure")
	}
	*dest = buffer.data;
	return (OK);

failure:
	if (buffer.data != NULL)
		String_Delete(&buffer.data);
	return (ERROR);
}

//! Parses all attributes of a tag, until the closing `>` or `/>` chars
/*!
**	Each attribute is stored as a STRING child node, whose key is the
**	attribute's name prefixed with the '@' char (#XML_KEYPREFIX_ATTRIBUTE).
**	The resulting linked list of attribute nodes is stored into `attributes`.
**	Expects the parsing offset to be just after the tag name.
**	Upon success, the parsing offset will be just after the `>` char.
*/
static
t_bool	XML_Parse_Attributes(s_xml* *attributes, s_xml_parse* p, t_bool* self_closing)
{
	s_xml*	head = NULL;
	s_xml*	current_item = NULL;
	s_xml*	new_item = NULL;
	s_xml*	tmp = NULL;
	t_utf8*	name = NULL;
	t_bool	had_whitespace;

	*attributes = NULL;
	*self_closing = FALSE;
	while (CAN_PARSE(0))
	{
		had_whitespace = XML_ISWHITESPACE(p->content[p->offset]);
		XML_Parse_SkipWhitespace(p);
		if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
			PARSINGERROR_XML("Unexpected end of input within XML tag (expected '>')")
		if (p->content[p->offset] == '>')
		{
			p->offset++;
			*attributes = head;
			return (OK);
		}
		if (p->content[p->offset] == '/')
		{
			p->offset++;
			if (!CAN_PARSE(0) || p->content[p->offset] != '>')
				PARSINGERROR_XML("Expected '>' char after '/' in self-closing XML tag")
			p->offset++;
			*self_closing = TRUE;
			*attributes = head;
			return (OK);
		}
		if (!had_whitespace)
			PARSINGERROR_XML("Expected whitespace between XML attributes")
		// parse the attribute name
		if (XML_Parse_Name(&name, p))
			PARSINGERROR_XML("Could not parse XML attribute name")
		// parse the (optional, in lenient mode) attribute value
		new_item = XML_Item();
		if (new_item == NULL)
			PARSINGERROR_XML("Could not parse XML attributes: Allocation failure")
		new_item->type = DYNAMICTYPE_STRING;
		new_item->key = String_Prepend("@", &name);
		name = NULL; // NOTE: `String_Prepend()` updates the given pointer, so `name` would alias `new_item->key`
		if (new_item->key == NULL)
			PARSINGERROR_XML("Could not parse XML attributes: Allocation failure")
		XML_Parse_SkipWhitespace(p);
		if (CAN_PARSE(0) && p->content[p->offset] == '=')
		{
			p->offset++;
			XML_Parse_SkipWhitespace(p);
			if (XML_Parse_AttributeValue(&new_item->value.string, p))
				PARSINGERROR_XML("Could not parse value of XML attribute \"%s\"", new_item->key + 1)
		}
		else
		{	// minimized (valueless) attribute, e.g. `<input disabled>`
			if (p->strict)
				PARSINGERROR_XML("Expected '=' char after XML attribute name \"%s\"", new_item->key + 1)
			new_item->value.string = String_Duplicate("");
			if (new_item->value.string == NULL)
				PARSINGERROR_XML("Could not parse XML attributes: Allocation failure")
		}
		// check for name conflicts with any previous attributes of this tag
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->key && String_Equals(tmp->key, new_item->key))
			{
				if (p->strict)
					PARSINGERROR_XML("Name conflict, XML attribute already exists: \"%s\"", new_item->key + 1)
				// lenient mode: the last occurrence of the attribute wins
				String_Delete(&tmp->value.string);
				tmp->value.string = new_item->value.string;
				new_item->value.string = NULL;
				XML_Delete(new_item);
				new_item = NULL;
				break;
			}
		}
		if (new_item == NULL)
			continue;
		// attach the new attribute node to the list
		if (head == NULL)
		{
			head = new_item;
			new_item->prev = new_item; // NOTE: the head's `prev` pointer refers to the last item of the list
		}
		else
		{
			current_item = head->prev;
			current_item->next = new_item;
			new_item->prev = current_item;
			head->prev = new_item;
		}
		new_item = NULL;
	}
	PARSINGERROR_XML("Unexpected end of input within XML tag (expected '>')")

failure:
	if (name != NULL)
		String_Delete(&name);
	if (new_item != NULL)
		XML_Delete(new_item);
	if (head != NULL)
		XML_Delete(head);
	return (ERROR);
}



/*============================================================================*\
||                                   Elements                                 ||
\*============================================================================*/

//! Adds a parsed child element to its parent's list of children, coalescing repeated tags
/*!
**	If a sibling with the same tag name already exists, both siblings are
**	coalesced into a single ARRAY node (keyed by the tag name) which holds
**	every same-named sibling, in document order.
*/
static
t_bool	XML_Parse_AddChild(s_xml* *head, s_xml* child)
{
	s_xml*	existing;
	s_xml*	array;
	s_xml*	last;

	for (existing = *head; existing != NULL; existing = existing->next)
	{
		if (existing->key && child->key && String_Equals(existing->key, child->key))
			break;
	}
	if (existing == NULL)
	{	// no name conflict: simply append the child to the end of the list
		if (*head == NULL)
		{
			*head = child;
			child->prev = child; // NOTE: the head's `prev` pointer refers to the last item of the list
		}
		else
		{
			last = (*head)->prev;
			last->next = child;
			child->prev = last;
			(*head)->prev = child;
		}
		return (OK);
	}
	if ((existing->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_ARRAY)
	{	// already coalesced: append the child as a new (unkeyed) array element
		String_Delete(&child->key);
		if (existing->value.child == NULL)
		{
			existing->value.child = child;
			child->prev = child;
			return (OK);
		}
		last = existing->value.child->prev;
		last->next = child;
		child->prev = last;
		existing->value.child->prev = child;
		return (OK);
	}
	// first repetition: replace the existing node with an ARRAY node holding both siblings
	array = XML_Item();
	if (array == NULL)
		return (ERROR);
	array->type = DYNAMICTYPE_ARRAY;
	array->key = existing->key;
	existing->key = NULL;
	// swap the array node into the existing node's place within the parent's list
	array->next = existing->next;
	if (existing == *head)
	{
		array->prev = (existing->prev == existing ? array : existing->prev);
		*head = array;
	}
	else
	{
		array->prev = existing->prev;
		array->prev->next = array;
	}
	if (array->next != NULL)
		array->next->prev = array;
	else if (*head != array)
		(*head)->prev = array; // the array node is now the last item of the list
	// the two same-named siblings become the array's (unkeyed) elements
	String_Delete(&child->key);
	existing->next = child;
	child->prev = existing;
	child->next = NULL;
	existing->prev = child; // NOTE: the head's `prev` pointer refers to the last item of the list
	array->value.child = existing;
	return (OK);
}

//! Parses a full XML element (open tag, attributes, content, close tag)
/*!
**	Expects the parsing offset to be at the opening `<` char.
**	The element's tag name is stored as the resulting node's key.
*/
static
t_bool	XML_Parse_Element(s_xml* item, s_xml_parse* p)
{
	s_xml_textbuffer	text = {0};
	s_xml*	attributes = NULL;
	s_xml*	head = NULL;
	s_xml*	new_item = NULL;
	s_xml*	tmp = NULL;
	t_utf8*	close_name = NULL;
	t_bool	self_closing = FALSE;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->content == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->depth >= KVT_NESTING_LIMIT)
		PARSINGERROR_XML("Could not parse XML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
	p->depth++;
	p->offset++; // skip '<'
	if (XML_Parse_Name(&item->key, p))
		PARSINGERROR_XML("Could not parse XML element tag name")
	if (XML_Parse_Attributes(&attributes, p, &self_closing))
		PARSINGERROR_XML("Could not parse attributes of XML element <%s>", item->key)
	if (!self_closing)
	{	// parse the element's content, until the matching close tag
		while (TRUE)
		{
			if (!CAN_PARSE(0) || p->content[p->offset] == '\0')
				PARSINGERROR_XML("Unexpected end of input: XML element <%s> is never closed", item->key)
			if (p->content[p->offset] != '<')
			{	// text content
				if (XML_Parse_Text(&text, p))
					PARSINGERROR_XML("Could not parse text content of XML element <%s>", item->key)
				continue;
			}
			if (XML_Parse_Matches(p, "</"))
			{	// close tag
				p->offset += 2;
				if (XML_Parse_Name(&close_name, p))
					PARSINGERROR_XML("Could not parse XML close tag name")
				if (!String_Equals(close_name, item->key))
					PARSINGERROR_XML("Mismatched XML close tag: expected </%s>, instead found </%s>", item->key, close_name)
				String_Delete(&close_name);
				XML_Parse_SkipWhitespace(p);
				if (!CAN_PARSE(0) || p->content[p->offset] != '>')
					PARSINGERROR_XML("Expected '>' char to end XML close tag </%s>", item->key)
				p->offset++;
				break;
			}
			if (XML_Parse_Matches(p, "<!--"))
			{
				if (XML_Parse_Comment(p))
					goto failure;
				continue;
			}
			if (XML_Parse_Matches(p, "<![CDATA["))
			{
				if (XML_Parse_CDATA(&text, p))
					goto failure;
				continue;
			}
			if (XML_Parse_Matches(p, "<?"))
			{
				if (XML_Parse_ProcessingInstruction(p))
					goto failure;
				continue;
			}
			if (XML_Parse_Matches(p, "<!"))
				PARSINGERROR_XML("Unexpected \"<!\" markup within XML element <%s>", item->key)
			// child element
			new_item = XML_Item();
			if (new_item == NULL)
				PARSINGERROR_XML("Could not parse XML element: Allocation failure")
			if (XML_Parse_Element(new_item, p))
				PARSINGERROR_XML("Could not parse child element of XML element <%s>", item->key)
			if (XML_Parse_AddChild(&head, new_item))
			{
				new_item = NULL;
				PARSINGERROR_XML("Could not parse XML element: Allocation failure")
			}
			new_item = NULL;
		}
	}
	p->depth--;
	// construct the resulting node from the attributes, text content, and child elements
	if (attributes == NULL && head == NULL)
	{	// an element with no attributes/children is a plain STRING (or NULL, if empty)
		if (text.data == NULL || text.length == 0)
		{
			item->type = DYNAMICTYPE_NULL;
			if (text.data != NULL)
				String_Delete(&text.data);
		}
		else
		{
			item->type = DYNAMICTYPE_STRING;
			item->value.string = text.data;
			text.data = NULL;
		}
		return (OK);
	}
	// otherwise, the element is an OBJECT: attributes first, then "#text", then child elements
	item->type = DYNAMICTYPE_OBJECT;
	if (text.data != NULL && text.length > 0)
	{	// add the text content as a child node, with the special "#text" key
		new_item = XML_Item();
		if (new_item == NULL)
			PARSINGERROR_XML("Could not parse XML element: Allocation failure")
		new_item->type = DYNAMICTYPE_STRING;
		new_item->key = String_Duplicate(XML_KEY_TEXTCONTENT);
		new_item->value.string = text.data;
		text.data = NULL;
		if (new_item->key == NULL)
			PARSINGERROR_XML("Could not parse XML element: Allocation failure")
		if (head == NULL)
		{
			new_item->prev = new_item;
		}
		else
		{	// prepend: the new node becomes the head, inheriting the last-item pointer
			new_item->next = head;
			new_item->prev = head->prev;
			head->prev = new_item;
		}
		head = new_item;
		new_item = NULL;
	}
	else if (text.data != NULL)
		String_Delete(&text.data);
	if (attributes != NULL)
	{	// prepend the attribute nodes to the list of children
		tmp = attributes->prev; // last attribute
		if (head != NULL)
		{
			attributes->prev = head->prev; // last child becomes the last item overall
			tmp->next = head;
			head->prev = tmp;
		}
		head = attributes;
		attributes = NULL;
	}
	item->value.child = head;
	return (OK);

failure:
	if (text.data != NULL)
		String_Delete(&text.data);
	if (close_name != NULL)
		String_Delete(&close_name);
	if (attributes != NULL)
		XML_Delete(attributes);
	if (head != NULL)
		XML_Delete(head);
	if (new_item != NULL)
		XML_Delete(new_item);
	return (ERROR);
}



/*============================================================================*\
||                          Main parsing entry points                         ||
\*============================================================================*/

static
t_size	XML_Parse_(s_xml* *dest, t_utf8 const* str, t_size n, t_bool strict)
{
	s_xml_parse	parser;
	s_xml_parse*	p = &parser;
	s_xml*	result = NULL;
	s_xml*	root = NULL;
	s_xml*	head = NULL;
	t_size	column = 0;
	t_size	roots = 0;

	Memory_Clear(p, sizeof(s_xml_parse));
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
	result = XML_Item();
	if (result == NULL)
		PARSINGERROR_XML("Got null result: memory failure")
	// parse the document prolog: XML declaration, comments, PIs, and DOCTYPE
	if (XML_Parse_Misc(p))
		goto failure;
	if (XML_Parse_Matches(p, "<!DOCTYPE"))
	{
		if (XML_Parse_Doctype(p))
			goto failure;
		if (XML_Parse_Misc(p))
			goto failure;
	}
	// parse the root element(s): well-formed XML has exactly one root element,
	// but lenient mode accepts several (useful for XML/HTML fragments)
	while (CAN_PARSE(0) && p->content[p->offset] == '<')
	{
		if (roots >= 1 && p->strict)
			PARSINGERROR_XML("Well-formed XML must have a single root element (found more than one)")
		root = XML_Item();
		if (root == NULL)
			PARSINGERROR_XML("Got null result: memory failure")
		if (XML_Parse_Element(root, p))
		{
			XML_Delete(root);
			root = NULL;
			PARSINGERROR_XML("Could not parse XML root element")
		}
		if (XML_Parse_AddChild(&head, root))
		{
			root = NULL;
			PARSINGERROR_XML("Could not parse XML: Allocation failure")
		}
		root = NULL;
		roots++;
		// parse the document epilog: comments, PIs, whitespace
		if (XML_Parse_Misc(p))
			goto failure;
	}
	if (roots == 0)
		PARSINGERROR_XML("Could not parse XML: no root element found")
	// check for any trailing garbage chars after the root element
	if (CAN_PARSE(0) && p->content[p->offset] != '\0')
		PARSINGERROR_XML("Invalid XML: unexpected garbage chars after root element: \"%.16s\"", p->content + p->offset)
	result->type = DYNAMICTYPE_OBJECT;
	result->value.child = head;
	if (dest)	*dest = result;
	return (p->offset);

failure:
	if (result != NULL)
	{
		XML_Delete(result);
		result = NULL;
	}
	if (head != NULL)
	{
		XML_Delete(head);
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
	{}
	if (p->error != NULL)
	{
		String_Delete(&p->error);
	}
	if (dest)	*dest = NULL;
	return (p->offset);
}



t_size	XML_Parse_Lenient(s_xml* *dest, t_utf8 const* str, t_size n)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "xml string given is NULL")
	{
		if (dest)	*dest = NULL;
		return (SIZE_ERROR);
	}
	if (n == 0)
		n = String_Length(str);
	return (XML_Parse_(dest, str, n, FALSE));
}

t_size	XML_Parse_Strict(s_xml* *dest, t_utf8 const* str, t_size n)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "xml string given is NULL")
	{
		if (dest)	*dest = NULL;
		return (SIZE_ERROR);
	}
	if (n == 0)
		n = String_Length(str);
	return (XML_Parse_(dest, str, n, TRUE));
}

s_xml*	XML_FromString_Lenient(t_utf8 const* str)
{
	s_xml*	result = NULL;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "xml string given is NULL")
		return (NULL);
	XML_Parse_(&result, str, String_Length(str), FALSE);
	return (result);
}

s_xml*	XML_FromString_Strict(t_utf8 const* str)
{
	s_xml*	result = NULL;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "xml string given is NULL")
		return (NULL);
	XML_Parse_(&result, str, String_Length(str), TRUE);
	return (result);
}
