
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/text/format.h"
#include "libccc/encode/xml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_print	s_xml_print;

#define ENSURE(NEEDED) \
{ \
	result = KVT_Print_EnsureBuffer(p, (NEEDED)); \
	if (result == NULL) \
		return (ERROR); \
} \

#define XML_NUMBER_BUFFERSIZE \
		KVT_NUMBER_BUFFERSIZE



static t_bool	XML_Print_Element	(s_xml const* item, s_xml_print* p, t_utf8 const* tag);



/*============================================================================*\
||                              Utility functions                             ||
\*============================================================================*/

//! Checks whether the given char can be the first char of an XML tag/attribute name
static
t_bool	XML_Print_IsNameStartChar(t_utf8 c)
{
	return (Char_IsLetter(c) || c == '_' || c == ':' || ((t_u8)c >= 0x80));
}

//! Checks whether the given char can occur within an XML tag/attribute name
static
t_bool	XML_Print_IsNameChar(t_utf8 c)
{
	return (XML_Print_IsNameStartChar(c) || Char_IsDigit(c) || c == '-' || c == '.');
}

//! Checks whether the given string is a valid XML tag/attribute name
static
t_bool	XML_Print_IsValidName(t_utf8 const* name)
{
	if (name == NULL || name[0] == '\0')
		return (FALSE);
	if (!XML_Print_IsNameStartChar(name[0]))
		return (FALSE);
	for (t_size i = 1; name[i] != '\0'; ++i)
	{
		if (!XML_Print_IsNameChar(name[i]))
			return (FALSE);
	}
	return (TRUE);
}

//! Checks whether the given item's key marks it as an XML attribute (see #XML_KEYPREFIX_ATTRIBUTE)
static
t_bool	XML_Print_IsAttribute(s_xml const* item)
{
	return (item->key != NULL && item->key[0] == XML_KEYPREFIX_ATTRIBUTE);
}

//! Checks whether the given item's key marks it as text content (see #XML_KEY_TEXTCONTENT)
static
t_bool	XML_Print_IsTextContent(s_xml const* item)
{
	return (item->key != NULL && String_Equals(item->key, XML_KEY_TEXTCONTENT));
}

//! Prints the given amount of raw chars to the output buffer
static
t_bool	XML_Print_Chars(s_xml_print* p, t_utf8 const* str, t_size length)
{
	t_utf8*	result = NULL;

	if (length == 0)
		return (OK);
	ENSURE(length + sizeof(""))
	Memory_Copy(result, str, length);
	result[length] = '\0';
	p->offset += length;
	return (OK);
}

//! Prints the indentation (tab chars) for the current nesting depth (only in `format` mode)
static
t_bool	XML_Print_Indent(s_xml_print* p)
{
	t_utf8*	result = NULL;
	t_size	length = p->depth;

	if (!p->format || length == 0)
		return (OK);
	ENSURE(length)
	for (t_size i = 0; i < length; ++i)
	{
		*result++ = '\t';
	}
	p->offset += length;
	return (OK);
}

//! Prints a newline char (only in `format` mode)
static
t_bool	XML_Print_NewLine(s_xml_print* p)
{
	if (!p->format)
		return (OK);
	return (XML_Print_Chars(p, "\n", 1));
}



/*============================================================================*\
||                          Text escaping and scalars                         ||
\*============================================================================*/

//! Prints the given string with XML escaping applied
/*!
**	The chars `&`, `<` and `>` are always escaped, using the XML predefined entities.
**	When printing an attribute value (`in_attribute`), the `"` char is escaped as well,
**	and any whitespace chars other than the space char are escaped as character
**	references (since XML attribute-value parsing normalizes them into space chars).
**	In text content, whitespace control chars at the very beginning/end of the string
**	are escaped as character references, so that they survive text-content trimming.
**	Any other C0 control chars are escaped as character references.
*/
static
t_bool	XML_Print_EscapedString(t_utf8 const* str, s_xml_print* p, t_bool in_attribute)
{
	t_utf8	buffer[8] = {0};
	t_size	length = String_Length(str);
	t_utf8	c;
	t_bool	escape;

	for (t_size i = 0; i < length; ++i)
	{
		c = str[i];
		switch (c)
		{
			case '&':	if (XML_Print_Chars(p, "&amp;", 5))	return (ERROR);	continue;
			case '<':	if (XML_Print_Chars(p, "&lt;", 4))	return (ERROR);	continue;
			case '>':	if (XML_Print_Chars(p, "&gt;", 4))	return (ERROR);	continue;
			case '"':
				if (in_attribute)
				{
					if (XML_Print_Chars(p, "&quot;", 6))
						return (ERROR);
					continue;
				}
				break;
			default:	break;
		}
		escape = FALSE;
		if (c == '\t' || c == '\n' || c == '\r')
		{	// whitespace control chars do not survive attribute-value normalization, nor text trimming at the edges
			escape = (in_attribute || TRUE);
		}
		else if ((t_u8)c < 0x20)
		{	// other C0 control chars are not allowed to appear raw in XML documents
			escape = TRUE;
		}
		else if (c == ' ' && !in_attribute && (i == 0 || i + 1 == length))
		{	// leading/trailing space chars in text content would not survive trimming
			escape = TRUE;
		}
		if (escape)
		{
			t_size n = String_Format_N(buffer, sizeof(buffer), "&#" SF_U8 ";", (t_u8)c);
			if (XML_Print_Chars(p, buffer, n))
				return (ERROR);
			continue;
		}
		if (XML_Print_Chars(p, &c, 1))
			return (ERROR);
	}
	return (OK);
}

//! Prints a number (integer or floating-point) item value
static
t_bool	XML_Print_Number(s_xml const* item, s_xml_print* p, t_bool bigint)
{
	t_utf8*	result = NULL;
	t_size	length = 0;
	t_size	i = 0;
	t_f64	test = 0.0;
	t_utf8	number_buffer[XML_NUMBER_BUFFERSIZE] = {0}; // temporary buffer to print the number into

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (bigint) // TODO handle variable-length integers
	{
		t_s64	d = item->value.integer;
		length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, SF_S64, d);
	}
	else
	{
		t_f64	d = item->value.number;
		if (F64_IsNaN(d))
		{
			length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, "NaN");
		}
		else if (F64_IsInf(d))
		{
			if (d > 0)	length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, "INF");
			if (d < 0)	length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, "-INF");
		}
		else
		{
			// Try 15 decimal places of precision to avoid nonsignificant nonzero digits
			length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, "%#1.1f", d);
			// Check whether the original t_f64 can be recovered
			test = F64_FromString(number_buffer);
			if (test != d)
			{	// If not, print with 17 decimal places of precision
				length = String_Format_N(number_buffer, XML_NUMBER_BUFFERSIZE, "%1.17g", d);
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

//! Prints any scalar item value as XML text (used for text content and attribute values)
static
t_bool	XML_Print_TextValue(s_xml const* item, s_xml_print* p, t_bool in_attribute)
{
	switch (item->type & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_NULL:    return (OK); // null values map to empty text
		case DYNAMICTYPE_BOOLEAN: return (XML_Print_Chars(p,
			(item->value.boolean ? "true" : "false"),
			(item->value.boolean ? 4 : 5)));
		case DYNAMICTYPE_INTEGER: return (XML_Print_Number(item, p, TRUE));
		case DYNAMICTYPE_FLOAT:   return (XML_Print_Number(item, p, FALSE));
		case DYNAMICTYPE_STRING:  return (XML_Print_EscapedString(
			(item->value.string ? item->value.string : ""), p, in_attribute));
		case DYNAMICTYPE_RAW:     return (XML_Print_Chars(p,
			(item->value.string ? item->value.string : ""),
			(item->value.string ? String_Length(item->value.string) : 0)));
		default: break;
	}
	if CCCERROR(TRUE, ERROR_PRINT,
		"cannot print a collection (array/object) value as XML text (item with key \"%s\")", item->key)
		return (ERROR);
	return (ERROR);
}



/*============================================================================*\
||                            Elements and documents                          ||
\*============================================================================*/

//! Prints all XML attributes of the given element (i.e. its children with '@'-prefixed keys)
static
t_bool	XML_Print_Attributes(s_xml const* item, s_xml_print* p)
{
	s_xml const*	child;

	for (child = item->value.child; child != NULL; child = child->next)
	{
		if (!XML_Print_IsAttribute(child))
			continue;
		if CCCERROR((!XML_Print_IsValidName(child->key + 1)), ERROR_PRINT,
			"invalid XML attribute name: \"%s\"", child->key + 1)
			return (ERROR);
		if (XML_Print_Chars(p, " ", 1))
			return (ERROR);
		if (XML_Print_Chars(p, child->key + 1, String_Length(child->key + 1)))
			return (ERROR);
		if (XML_Print_Chars(p, "=\"", 2))
			return (ERROR);
		if (XML_Print_TextValue(child, p, TRUE))
			return (ERROR);
		if (XML_Print_Chars(p, "\"", 1))
			return (ERROR);
	}
	return (OK);
}

//! Prints an OBJECT node as an XML element with the given `tag` name
static
t_bool	XML_Print_Object(s_xml const* item, s_xml_print* p, t_utf8 const* tag)
{
	s_xml const*	child;
	s_xml const*	text = NULL;
	t_size	elements = 0;

	// take stock of the object's contents: attributes, text content, child elements
	for (child = item->value.child; child != NULL; child = child->next)
	{
		if (XML_Print_IsAttribute(child))
			continue;
		if (XML_Print_IsTextContent(child))
		{
			text = child;
			continue;
		}
		elements++;
	}
	// print the open tag, with any attributes
	if (XML_Print_Indent(p))	return (ERROR);
	if (XML_Print_Chars(p, "<", 1))	return (ERROR);
	if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
	if (XML_Print_Attributes(item, p))	return (ERROR);
	if (elements == 0 && text == NULL)
	{	// no content at all: print a self-closing tag
		if (XML_Print_Chars(p, "/>", 2))	return (ERROR);
		return (XML_Print_NewLine(p));
	}
	if (XML_Print_Chars(p, ">", 1))	return (ERROR);
	if (elements == 0)
	{	// text content only: print the whole element on a single line
		if (XML_Print_TextValue(text, p, FALSE))	return (ERROR);
		if (XML_Print_Chars(p, "</", 2))	return (ERROR);
		if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
		if (XML_Print_Chars(p, ">", 1))	return (ERROR);
		return (XML_Print_NewLine(p));
	}
	// print the child elements, one per line, indented
	if (XML_Print_NewLine(p))	return (ERROR);
	p->depth++;
	if (text != NULL)
	{	// the text content (if any) is printed first
		if (XML_Print_Indent(p))	return (ERROR);
		if (XML_Print_TextValue(text, p, FALSE))	return (ERROR);
		if (XML_Print_NewLine(p))	return (ERROR);
	}
	for (child = item->value.child; child != NULL; child = child->next)
	{
		if (XML_Print_IsAttribute(child) || XML_Print_IsTextContent(child))
			continue;
		if CCCERROR((child->key == NULL), ERROR_PRINT,
			"cannot print XML element: object child node has no key (inside <%s>)", tag)
			return (ERROR);
		if (XML_Print_Element(child, p, child->key))
			return (ERROR);
	}
	p->depth--;
	// print the close tag
	if (XML_Print_Indent(p))	return (ERROR);
	if (XML_Print_Chars(p, "</", 2))	return (ERROR);
	if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
	if (XML_Print_Chars(p, ">", 1))	return (ERROR);
	return (XML_Print_NewLine(p));
}

//! Prints any KVT node as one (or several) XML element(s) with the given `tag` name
/*!
**	- A scalar node is printed as `<tag>value</tag>` (or `<tag/>`, if null)
**	- An OBJECT node is printed as an element with attributes/text/children (see above)
**	- An ARRAY node is printed as one element per array item, all sharing the same `tag`
**		(nested arrays are printed wrapped in a `<tag>` element, with #XML_TAG_DEFAULT items)
*/
static
t_bool	XML_Print_Element(s_xml const* item, s_xml_print* p, t_utf8 const* tag)
{
	s_xml const*	child;

	if CCCERROR((p == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if CCCERROR((p->depth >= KVT_NESTING_LIMIT), ERROR_PRINT,
		"could not print XML: nested too deep, max depth of nesting is %u", KVT_NESTING_LIMIT)
		return (ERROR);
	if CCCERROR((!XML_Print_IsValidName(tag)), ERROR_PRINT,
		"invalid XML element tag name: \"%s\"", tag)
		return (ERROR);
	switch (item->type & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_ARRAY:
		{
			for (child = item->value.child; child != NULL; child = child->next)
			{
				if ((child->type & DYNAMICTYPE_MASK) != DYNAMICTYPE_ARRAY)
				{
					if (XML_Print_Element(child, p, tag))
						return (ERROR);
					continue;
				}
				// nested array: print it wrapped inside a `<tag>` element
				if (XML_Print_Indent(p))	return (ERROR);
				if (XML_Print_Chars(p, "<", 1))	return (ERROR);
				if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
				if (XML_Print_Chars(p, ">", 1))	return (ERROR);
				if (XML_Print_NewLine(p))	return (ERROR);
				p->depth++;
				if (XML_Print_Element(child, p, XML_TAG_DEFAULT))
					return (ERROR);
				p->depth--;
				if (XML_Print_Indent(p))	return (ERROR);
				if (XML_Print_Chars(p, "</", 2))	return (ERROR);
				if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
				if (XML_Print_Chars(p, ">", 1))	return (ERROR);
				if (XML_Print_NewLine(p))	return (ERROR);
			}
			return (OK);
		}
		case DYNAMICTYPE_OBJECT:
		{
			return (XML_Print_Object(item, p, tag));
		}
		case DYNAMICTYPE_NULL:
		{	// a null value is printed as an empty, self-closing element
			if (XML_Print_Indent(p))	return (ERROR);
			if (XML_Print_Chars(p, "<", 1))	return (ERROR);
			if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
			if (XML_Print_Chars(p, "/>", 2))	return (ERROR);
			return (XML_Print_NewLine(p));
		}
		default:
		{	// any other scalar value is printed as a single-line element
			if (XML_Print_Indent(p))	return (ERROR);
			if (XML_Print_Chars(p, "<", 1))	return (ERROR);
			if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
			if (XML_Print_Chars(p, ">", 1))	return (ERROR);
			if (XML_Print_TextValue(item, p, FALSE))	return (ERROR);
			if (XML_Print_Chars(p, "</", 2))	return (ERROR);
			if (XML_Print_Chars(p, tag, String_Length(tag)))	return (ERROR);
			if (XML_Print_Chars(p, ">", 1))	return (ERROR);
			return (XML_Print_NewLine(p));
		}
	}
}

//! Prints an entire XML document from the given KVT tree
/*!
**	If the given `item` is an OBJECT holding exactly one child with a valid tag
**	name, then that child is printed as the document's root element (this is the
**	same structure that the XML parsing functions produce). Otherwise, the whole
**	`item` is printed wrapped inside a default `<root>` element (#XML_TAG_ROOT).
*/
static
t_bool	XML_Print_Lines(s_xml const* item, s_xml_print* p)
{
	s_xml const*	child;

	if CCCERROR((item == NULL), ERROR_NULLPOINTER, NULL)
		return (ERROR);
	if (p->format)
	{	// print the XML declaration
		if (XML_Print_Chars(p, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>", 38))
			return (ERROR);
		if (XML_Print_NewLine(p))
			return (ERROR);
	}
	if ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_OBJECT)
	{
		child = item->value.child;
		if (child != NULL && child->next == NULL &&
			child->key != NULL &&
			child->key[0] != XML_KEYPREFIX_ATTRIBUTE &&
			!XML_Print_IsTextContent(child) &&
			XML_Print_IsValidName(child->key))
		{	// the object holds a single, valid root element: print it directly
			return (XML_Print_Element(child, p, child->key));
		}
	}
	return (XML_Print_Element(item, p, XML_TAG_ROOT));
}



/*============================================================================*\
||                          Main printing entry points                        ||
\*============================================================================*/

static
t_utf8*	XML_Print_(s_xml const* item, t_bool format)
{
	static const t_size default_buffer_size = 256;
	s_xml_print p[1];
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
	if (XML_Print_Lines(item, p))
		goto failure;

#ifdef Memory_Realloc // check if reallocate is available
	{
		printed = (t_utf8*)Memory_Reallocate(p->result, p->offset + 1);
		if CCCERROR((printed == NULL), ERROR_ALLOCFAILURE, NULL)
			goto failure;
		p->result = NULL;
	}
#else // otherwise copy the XML over to a new buffer
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



t_size	XML_Print_Pretty(t_utf8* dest, s_xml const* item, t_size n)
{
	s_xml_print p;

	Memory_Clear(&p, sizeof(s_xml_print));
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
	XML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}

t_size	XML_Print_Minify(t_utf8* dest, s_xml const* item, t_size n)
{
	s_xml_print p;

	Memory_Clear(&p, sizeof(s_xml_print));
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
	XML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}



t_utf8*	XML_ToString_Pretty(s_xml const* item)
{
	return (XML_Print_(item, TRUE));
}

t_utf8*	XML_ToString_Minify(s_xml const* item)
{
	return (XML_Print_(item, FALSE));
}



#if 0 // TODO
t_utf8*	XML_Print_Buffered(s_xml const* item, t_sint prebuffer, t_bool format)
{
	s_xml_print p = { 0 };

	if CCCERROR((prebuffer < 0), ERROR_LENGTH2SMALL, NULL)
		return (NULL);
	p.result = (t_utf8*)Memory_Allocate((t_size)prebuffer);
	if CCCERROR((p.result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = format;
	if (XML_Print_Lines(item, &p))
	{
		Memory_Free(p.result);
		return (NULL);
	}
	return ((t_utf8*)p.result);
}
#endif
