
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/encode/toml.h"

#include LIBCONFIG_ERROR_INCLUDE



typedef s_kvt_print	s_toml_print;

#define ENSURE(NEEDED) \
{													\
	result = KVT_Print_EnsureBuffer(p, (NEEDED));	\
	if (result == NULL)								\
		return (ERROR);								\
}													\

#define TOML_Print_UpdateOffset \
		KVT_Print_UpdateOffset

#define TOML_NUMBER_BUFFERSIZE \
		KVT_NUMBER_BUFFERSIZE



//! The set of characters which are valid in a bare (unquoted) key
#define TOML_CHARSET_BAREKEY	"-"CHARSET_ALPHABET"_"CHARSET_DECIMAL

//! The maximum amount of items an inline array/object can have before being spread across multiple lines
#define TOML_INLINE_MULTILINE	8



static
void TOML_Print_KeyPath_Push(s_toml_print* p, t_utf8* key)
{
	t_utf8*	tmp;
	t_utf8*	oldpath = NULL;

	if (p->keypath)
		oldpath = p->keypath;

	if (key == NULL)
		tmp = NULL;
	else if (String_Length(key) > 0 && String_HasOnly(key, TOML_CHARSET_BAREKEY))
		tmp = String_Duplicate(key);
	else
		tmp = String_Format("\"%s\"", key);

	if (oldpath && tmp)
		p->keypath = String_Format("%s.%s", oldpath, tmp);
	else if (tmp)
		p->keypath = String_Duplicate(tmp);
	else return;

	if (tmp)
		String_Delete(&tmp);
	if (oldpath)
		String_Delete(&oldpath);
}

static
void TOML_Print_KeyPath_Pop(s_toml_print* p)
{
	t_size	i;
	t_bool	bare;
	t_utf8*	oldpath = NULL;

	if (p->keypath == NULL)
		return;
	bare = TRUE;

	if (p->keypath)
		oldpath = p->keypath;

	i = String_Length(oldpath);
	if (i)
	{
		if (oldpath[--i] == '.')
			--i;
		while (i--)
		{
			if (bare)
			{
				if (oldpath[i] == '.')
					break;
				if (oldpath[i] == '\"')
					bare = FALSE;
			}
			else
			{
				if (oldpath[i] == '\"')
					bare = TRUE;
			}
		}
		++i;
	}
	p->keypath = (i == 0 ? NULL : String_Sub(oldpath, 0, i));

	if (oldpath)
		String_Delete(&oldpath);
}



static
t_bool	TOML_Print_IsKeyComplex(t_char const* key)
{
	t_size	i = 0;

	if (key == NULL)
		return (FALSE);
	while (key[i])
	{
		if (!(key[i] == '-' || key[i] == '_' || Char_IsAlphaNumeric(key[i])))
			return (TRUE);
		++i;
	}
	return (FALSE);
}

static
t_bool	TOML_Print_IsObjectComplex(s_toml const* item)
{
	s_toml*	tmp;
	t_sint	i = 0;
	if (item == NULL)
		return (FALSE);
	if (TOML_Print_IsKeyComplex(item->key))
		return (TRUE);
	tmp = item->value.child;
	if (tmp && tmp->next)
	while (tmp)
	{
		if ((tmp->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_ARRAY ||
			(tmp->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_OBJECT)
		{
			if (tmp->value.child && tmp->value.child->next)
				return (TRUE);
		}
		tmp = tmp->next;
		++i;
	}
	if (i > TOML_INLINE_MULTILINE)
	{
		return (TRUE);
	}
	return (FALSE);
}



static t_bool	TOML_Print_Number		(s_toml const* item, s_toml_print* p, t_bool bigint);
static t_bool	TOML_Print_String		(s_toml const* item, s_toml_print* p);
static t_bool	TOML_Print_Object		(s_toml const* item, s_toml_print* p);
static t_bool	TOML_Print_Array		(s_toml const* item, s_toml_print* p);
static t_bool	TOML_Print_Table		(s_toml const* item, s_toml_print* p);
static t_bool	TOML_Print_Value		(s_toml const* item, s_toml_print* p);
static t_bool	TOML_Print_Key			(s_toml const* item, s_toml_print* p, t_bool full_path);
static t_bool	TOML_Print_KeyValuePair	(s_toml const* item, s_toml_print* p, t_bool full_path);
static t_bool	TOML_Print_Lines		(s_toml const* item, s_toml_print* p);



// Render the cstring provided to an escaped version that can be printed.
static
t_bool	TOML_Print_StringPtr(t_utf8 const* input, s_toml_print* p)
{
	t_utf8 const* input_ptr = NULL;
	t_utf8*	result = NULL;
	t_utf8*	str;
	t_size	result_length = 0;
	t_size	escape_chars = 0; //!< amount of additional characters needed for escaping

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	// empty string
	if (input == NULL)
	{
		ENSURE(sizeof("\"\""))
		String_Copy(result, "\"\"");
		return (OK);
	}
	// set "flag" to 1 if something needs to be escaped
	input_ptr = input;
	while (*input_ptr != '\0')
	{
		t_utf32 c = UTF32_FromUTF8((t_utf8*)input_ptr);
		t_size length = 1;
			 if (c < UTF8_1BYTE)	length = 1;
		else if (c < UTF8_2BYTE)	length = 2;
		else if (c < UTF8_3BYTE)	length = 3;
		else if (c < UTF8_4BYTE)	length = 4;
		switch (*input_ptr)
		{
			case '\"':
			case '\\':
			case '\b':
			case '\f':
			case '\n':
			case '\r':
			case '\t':
			{	// one character escape sequence
				escape_chars++;
				break;
			}
			default:
			{
				if (!UTF32_IsPrintable(c))
				{
					escape_chars += 5;	// UTF-32 escape sequence \uXXXX
					if (c >= UTF8_3BYTE)
						escape_chars += 4;	// UTF-32 escape sequence \UXXXX
				}
				break;
			}
		}
		input_ptr += length;
	}
	result_length = (t_size)(input_ptr - input) + escape_chars;

	ENSURE(result_length + sizeof("\"\""))

	// no characters have to be escaped
	if (escape_chars == 0)
	{
		result[0] = '\"';
		Memory_Copy(result + 1, input, result_length);
		result[result_length + 1] = '\"';
		result[result_length + 2] = '\0';
		return (OK);
	}
	result[0] = '\"';
	str = result + 1;
	// copy the string
	input_ptr = input;
	while (*input_ptr != '\0')
	{
		t_utf32 c = UTF32_FromUTF8((t_utf8*)input_ptr);
		t_size length = 1;
			 if (c < UTF8_1BYTE)	length = 1;
		else if (c < UTF8_2BYTE)	length = 2;
		else if (c < UTF8_3BYTE)	length = 3;
		else if (c < UTF8_4BYTE)	length = 4;
		if (UTF32_IsPrintable(c) &&
			(c != '\"') &&
			(c != '\\'))
		{	// normal character, copy
			*str++ = *input_ptr;
			while (--length && *input_ptr != '\0')
			{
				input_ptr++;
				*str++ = *input_ptr;
			}
		}
		else // character needs to be escaped
		{
			*str++ = '\\';
			switch (c)
			{
				case '\b':	*str++ = 'b';	break;
				case '\t':	*str++ = 't';	break;
				case '\n':	*str++ = 'n';	break;
				case '\f':	*str++ = 'f';	break;
				case '\r':	*str++ = 'r';	break;
				case '\"':	*str++ = '\"';	break;
				case '\\':	*str++ = '\\';	break;
				default: // escape and print as unicode codepoint
				{
					t_utf16 u[2] = {0};
					length = UTF32_ToUTF16(u, c);
					if (length > 0)
					{
						String_Format_N(str, 6, "u%4.4X", u[0]);
						str += 5;
						if (u[1])
						{
							*str++ = '\\';
							String_Format_N(str, 6, "u%4.4X", u[1]);
							str += 5;
						}
					}
					break;
				}
			}
		}
		input_ptr++;
	}
	*str++ = '\"';
	*str++ = '\0';
	return (OK);
}

// Invoke TOML_Print_StringPtr (which is useful) on an item.
static
t_bool	TOML_Print_String(s_toml const* item, s_toml_print* p)
{
	return (TOML_Print_StringPtr((t_utf8*)item->value.string, p));
}

// Render the number nicely from the given item into a string.
static
t_bool	TOML_Print_Number(s_toml const* item, s_toml_print* p, t_bool bigint)
{
	t_utf8*	result = NULL;
	t_size	length = 0;
	t_size	i = 0;
	t_f64	test = 0.0;
	t_utf8	number_buffer[TOML_NUMBER_BUFFERSIZE] = {0}; // temporary buffer to print the number into

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	if (bigint) // TODO handle variable-length integers
	{
		t_s64	d = item->value.integer;
		length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, SF_S64, d);
	}
	else
	{
		t_f64	d = item->value.number;
		if (IS_NAN(d))
		{
			length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, "nan");
		}
		else if (IS_INF(d))
		{
			if (d > 0)	length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, "+inf");
			if (d < 0)	length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, "-inf");
		}
		else
		{
			// Try 15 decimal places of precision to avoid nonsignificant nonzero digits
			length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, "%#1.1f", d);
			// Check whether the original t_f64 can be recovered
			test = F64_FromString(number_buffer);
			if (test != d)
			{	// If not, print with 17 decimal places of precision
				length = String_Format_N(number_buffer, TOML_NUMBER_BUFFERSIZE, "%1.17g", d);
			}
		}
	}
	HANDLE_ERROR_SF(PRINT, (length == 0), return (ERROR);,
		"could not print number value for item with key \"%s\"", item->key)
	HANDLE_ERROR_SF(PRINT, (length > (sizeof(number_buffer) - 1)), return (ERROR);,
		"could not print number value for item with key \"%s\" -> buffer overrun occurred", item->key)
	// reserve appropriate space in the output
	ENSURE(length + sizeof(""))
	// copy the printed number to the output
	for (i = 0; i < length; ++i)
	{
		result[i] = number_buffer[i];
	}
	// TODO ? replace any locale-dependent decimal point with '.' (inspect whether printf/snprintf may output with other decimal point chars ?)
	p->offset += length;
	result[i] = '\0';
	return (OK);
}



// Render an array to text
static
t_bool	TOML_Print_Array(s_toml const* item, s_toml_print* p)
{
	t_utf8*	result = NULL;
	s_toml*	current_item = item->value.child;
	t_bool	multiline = p->format && TOML_Print_IsObjectComplex(item);

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	// Compose the output array.
	if (!(current_item && (current_item->next || current_item->prev != current_item)))
		multiline = FALSE;
	if (multiline && p->offset >= 2 &&
		p->result[p->offset - 1] == ' ' &&
		p->result[p->offset - 2] == '=')
	{
		ENSURE(p->depth + 1)
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}

	// opening square bracket
	ENSURE(1)
	*result++ = '[';
	p->offset++;
	if (p->format && item->value.child)
	{
		ENSURE(1)
		*result++ = multiline ? '\n' : ' ';
		p->offset++;
	}

	TOML_Print_KeyPath_Push(p, item->key);
	p->depth++;
	while (current_item)
	{
		if (multiline)
		{
			ENSURE(p->depth)
			for (t_size i = 0; i < p->depth; ++i)
			{
				*result++ = '\t';
			}
			p->offset += p->depth;
		}
		if (TOML_Print_Value(current_item, p))
			return (ERROR);
		TOML_Print_UpdateOffset(p);

		// print comma if not last
		if (current_item->next)
		{
			ENSURE(p->format ? 3 : 2)
			*result++ = ',';
			p->offset++;
			if (p->format)
			{
				*result++ = multiline ? '\n' : ' ';
				p->offset++;
			}
		}
		else ENSURE(1)
		*result = '\0';
		current_item = current_item->next;
	}
	TOML_Print_KeyPath_Pop(p);
	p->depth--;

	// closing square bracket
	if (p->format && item->value.child)
	{
		ENSURE(1)
		*result++ = multiline ? '\n' : ' ';
		p->offset++;
	}
	if (multiline)
	{
		ENSURE(p->depth)
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth;
	}
	ENSURE(2)
	*result++ = ']';
	p->offset++;
	*result = '\0';
	return (OK);
}



static
t_bool	TOML_Print_Object(s_toml const* item, s_toml_print* p)
{
	t_utf8*	result = NULL;
	s_toml*	current_item = item->value.child;
	t_bool	multiline = p->format && TOML_Print_IsObjectComplex(item);

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	if (!(current_item && (current_item->next || current_item->prev != current_item)))
		multiline = FALSE;
	if (multiline && p->offset >= 2 &&
		p->result[p->offset - 1] == ' ' &&
		p->result[p->offset - 2] == '=')
	{
		ENSURE(p->depth + 1)
		*result++ = '\n';
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth + 1;
	}

	// opening curly brace
	ENSURE(1)
	*result++ = '{';
	p->offset++;
	if (p->format && item->value.child)
	{
		ENSURE(1)
		*result++ = multiline ? '\n' : ' ';
		p->offset++;
	}

	TOML_Print_KeyPath_Push(p, item->key);
	p->depth++;
	while (current_item)
	{
		if (multiline)
		{
			ENSURE(p->depth)
			for (t_size i = 0; i < p->depth; ++i)
			{
				*result++ = '\t';
			}
			p->offset += p->depth;
		}

		// print value
		if (TOML_Print_KeyValuePair(current_item, p, FALSE))
			return (ERROR);

		// print comma if not last
		if (current_item->next)
		{
			ENSURE(p->format ? 3 : 2)
			*result++ = ',';
			p->offset++;
			if (p->format)
			{
				*result++ = multiline ? '\n' : ' ';
				p->offset++;
			}
		}
		else ENSURE(1)
		*result = '\0';
		current_item = current_item->next;
	}

	TOML_Print_KeyPath_Pop(p);
	p->depth--;

	// closing curly brace
	if (p->format && item->value.child)
	{
		ENSURE(1)
		*result++ = multiline ? '\n' : ' ';
		p->offset++;
	}
	if (multiline)
	{
		ENSURE(p->depth)
		for (t_size i = 0; i < p->depth; ++i)
		{
			*result++ = '\t';
		}
		p->offset += p->depth;
	}
	ENSURE(2)
	*result++ = '}';
	p->offset++;
	*result = '\0';
	return (OK);
}



static
t_bool	TOML_Print_Value(s_toml const* item, s_toml_print* p)
{
	t_utf8* result = NULL;
	t_utf8 const* str;
	t_size	length;

	switch ((item->type) & DYNAMICTYPE_MASK)
	{
		case DYNAMICTYPE_INTEGER: return (TOML_Print_Number(item, p, TRUE));
		case DYNAMICTYPE_FLOAT:   return (TOML_Print_Number(item, p, FALSE));
		case DYNAMICTYPE_STRING:  return (TOML_Print_String(item, p));
		case DYNAMICTYPE_ARRAY:   return (TOML_Print_Array(item, p));
		case DYNAMICTYPE_OBJECT:  return (TOML_Print_Object(item, p));
		case DYNAMICTYPE_NULL:
		{
			str = "null";
			length = (String_Length(str) + sizeof(""));
			ENSURE(length)
			String_Copy(result, str);
			return (OK);
		}
		case DYNAMICTYPE_BOOLEAN:
		{
			str = (item->value.boolean ? "true" : "false");
			length = (String_Length(str) + sizeof(""));
			ENSURE(length)
			String_Copy(result, str);
			return (OK);
		}
		case DYNAMICTYPE_RAW:
		{
			HANDLE_ERROR_SF(PRINT, (item->value.string == NULL), return (ERROR);,
				"item with key \"%s\" is of 'raw string' type, but its value is null", item->key)
			length = String_Length(item->value.string) + sizeof("");
			ENSURE(length)
			Memory_Copy(result, item->value.string, length);
			return (OK);
		}
		default:
			HANDLE_ERROR_SF(PRINT, (TRUE), return (ERROR);,
				"cannot print item with key %s, has invalid type (%i)", p->keypath, item->type)
	}
}



static
t_bool	TOML_Print_Table(s_toml const* item, s_toml_print* p)
{
	t_utf8*	result = NULL;

	if (p->format && p->offset > 1)
	{
		ENSURE(2)
		*result++ = '\n';
		p->offset++;
	}
	else ENSURE(1)
	*result++ = '[';
	p->offset++;

	if (TOML_Print_Key(item, p, TRUE))
		return (ERROR);

	ENSURE(2)
	*result++ = ']';
	p->offset++;
	*result++ = '\n';
	p->offset++;

	TOML_Print_KeyPath_Push(p, item->key);
	p->depth++;

	if (TOML_Print_Lines(item, p))
		return (ERROR);

	TOML_Print_KeyPath_Pop(p);
	p->depth--;

	return (OK);
}



static
t_bool	TOML_Print_Key(s_toml const* item, s_toml_print* p, t_bool full_path)
{
	t_utf8* result = NULL;
	t_size	length;

	if (full_path && p->keypath)
	{
		length = String_Length(p->keypath) + 1;
		ENSURE(length)
		String_Copy(result, p->keypath);
		result[length - 1] = '.';
		p->offset += length;
		result[length] = '\0';
	}
	length = String_Length(item->key);
	if (length > 0 && String_HasOnly(item->key, TOML_CHARSET_BAREKEY))
	{
		ENSURE(length)
		String_Copy(result, item->key);
		p->offset += length;
	}
	else
	{
		if (TOML_Print_StringPtr(item->key, p))
			return (ERROR);
		TOML_Print_UpdateOffset(p);
	}
	return (OK);
}



static
t_bool	TOML_Print_KeyValuePair(s_toml const* item, s_toml_print* p, t_bool full_path)
{
	t_utf8* result = NULL;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (ERROR);)

	if (TOML_Print_Key(item, p, full_path))
		return (ERROR);

	length = (t_size)(p->format ? 3 : 1);
	ENSURE(length)
	if (p->format)	*result++ = ' ';
	*result++ = '=';
	if (p->format)	*result++ = ' ';
	p->offset += length;

	if (TOML_Print_Value(item, p))
		return (ERROR);
	TOML_Print_UpdateOffset(p);

	return (OK);
}



static
t_bool	TOML_Print_Lines(s_toml const* item, s_toml_print* p)
{
	t_utf8*	result = NULL;
	s_toml*	current_item = NULL;

	HANDLE_ERROR(NULLPOINTER, (p == NULL), return (ERROR);)
	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (ERROR);)

	if (p->format)
	{
		ENSURE(2)
		*result++ = '\n';
		p->offset++;
		*result = '\0';
	}

	current_item = item->value.child;
	while (current_item)
	{
		if (p->format && p->depth)
		{
			ENSURE(p->depth)
			for (t_size i = 0; i < p->depth; ++i)
			{
				*result++ = '\t';
			}
			p->offset += p->depth;
		}
		// print value
		HANDLE_ERROR(NULLPOINTER, (current_item == NULL), return (ERROR);)
/* TODO array tables
		else if ((current_item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_ARRAY &&
			TOML_Print_IsObjectComplex(current_item))
		{
			if (TOML_Print_Table(current_item, p))
				return (ERROR);
		}
*/
		else if ((current_item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_OBJECT &&
			TOML_Print_IsObjectComplex(current_item))
		{
			if (item != p->item) // return to top level for next table
				return (OK);
			if (TOML_Print_Table(current_item, p))
				return (ERROR);
		}
		else if (TOML_Print_KeyValuePair(current_item, p, FALSE))
			return (ERROR);

		if ((p->format || current_item->next) &&
			p->result[p->offset - 1] != '\n')
		{
			ENSURE(2)
			*result++ = '\n';
			p->offset++;
		}
		else ENSURE(1)
		*result = '\0';
		current_item = current_item->next;
	}

	return (OK);
}



static
t_utf8*	TOML_Print_(s_toml const* item, t_bool format)
{
	static const t_size default_buffer_size = 256;
	s_toml_print p[1];
	t_utf8* printed = NULL;

	Memory_Clear(p, sizeof(p));
	// create buffer
	p->item = item;
	p->format = format;
	p->length = default_buffer_size;
	p->result = (t_utf8*)Memory_Allocate(default_buffer_size);
	HANDLE_ERROR(ALLOCFAILURE, (p->result == NULL), goto failure;)
	// print the value
	if (TOML_Print_Lines(item, p))
		goto failure;

#ifdef Memory_Realloc // check if reallocate is available
	{
		printed = (t_utf8*)Memory_Reallocate(p->result, p->offset + 1);
		HANDLE_ERROR(ALLOCFAILURE, (printed == NULL), goto failure;)
		p->result = NULL;
	}
#else // otherwise copy the TOML over to a new buffer
	{
		printed = (t_utf8*)Memory_Allocate(p->offset + 1);
		HANDLE_ERROR(ALLOCFAILURE, (printed == NULL), goto failure;)
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



t_size	TOML_Print_Pretty(t_utf8* dest, s_toml const* item, t_size n)
{
	s_toml_print p;

	Memory_Clear(&p, sizeof(s_toml_print));
	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (0);)
	if (n == 0)
		n = SIZE_MAX;
	p.item = item;
	p.result = dest;
	p.length = n;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = TRUE;
	TOML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}

t_size	TOML_Print_Minify(t_utf8* dest, s_toml const* item, t_size n)
{
	s_toml_print p;

	Memory_Clear(&p, sizeof(s_toml_print));
	HANDLE_ERROR(NULLPOINTER, (item == NULL), return (0);)
	if (n == 0)
		n = SIZE_MAX;
	p.item = item;
	p.result = dest;
	p.length = n;
	p.offset = 0;
	p.noalloc = TRUE;
	p.format = FALSE;
	TOML_Print_Lines(item, &p); // TODO error handling ?
	return (p.offset);
}



t_utf8*	TOML_ToString_Pretty(s_toml const* item)
{
	return (TOML_Print_(item, TRUE));
}

t_utf8*	TOML_ToString_Minify(s_toml const* item)
{
	return (TOML_Print_(item, FALSE));
}



#if 0 // TODO
t_utf8*	TOML_Print_Buffered(s_toml const* item, t_sint prebuffer, t_bool format)
{
	s_toml_print p = { 0 };

	HANDLE_ERROR(LENGTH2SMALL, (prebuffer < 0), return (ERROR);)
	p.result = (t_utf8*)Memory_Allocate((t_size)prebuffer);
	HANDLE_ERROR(ALLOCFAILURE, (p.result == NULL), return (NULL);)
	p.length = (t_size)prebuffer;
	p.offset = 0;
	p.noalloc = FALSE;
	p.format = format;
	if (TOML_Print_Lines(item, &p))
	{
		Memory_Free(p.result);
		return (NULL);
	}
	return ((t_utf8*)p.result);
}
#endif
