
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Returns a pointer to the glyph at index `n` within the given string (or its terminator, if `n` is too large)
static
t_utf8 const*	StringUTF8_Replace_CharAt(t_utf8 const* str, t_size n)
{
	t_size	offset;
	t_sint	charlen;

	offset = 0;
	while (n-- && str[offset])
	{
		charlen = CharUTF8_Length(str + offset);
		offset += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (str + offset);
}

//! Returns the glyph index of the first occurrence of codepoint `c` in `str` (or `ERROR` if absent), without logging
static
t_sintmax	StringUTF8_Replace_IndexOfChar(t_utf8 const* str, t_utf32 c)
{
	t_size	i;
	t_size	index;
	t_sint	charlen;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (CharUTF32_FromUTF8(str + i) == c)
			return ((t_sintmax)index);
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
		++index;
	}
	return (ERROR);
}



t_utf8*	StringUTF8_Replace_Char(t_utf8 const* str, t_utf8 const* char_old, t_utf8* const char_new)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((char_old == NULL), ERROR_NULLPOINTER, "old char given is NULL")
		return (NULL);
	if CCCERROR((char_new == NULL), ERROR_NULLPOINTER, "new char given is NULL")
		return (NULL);
	if CCCERROR((char_old[0] == '\0'), ERROR_INVALIDARGS, "old char given is an empty string")
		return (NULL);
	return (StringUTF8_Replace_String(str, char_old, char_new));
}



t_utf8*	StringUTF8_Replace_Charset(t_utf8 const* str, t_utf8 const* cset_old, t_utf8 const* cset_new)
{
	t_utf8*		result;
	t_utf8 const*	glyph;
	t_sintmax	c_index;
	t_size	written;
	t_size	i;
	t_size	j;
	t_size	charlen;
	t_sint	length;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((cset_old == NULL), ERROR_NULLPOINTER, "old charset string given is NULL")
		return (NULL);
	if CCCERROR((cset_new == NULL), ERROR_NULLPOINTER, "new charset string given is NULL")
		return (NULL);
	if (cset_old == cset_new)
		return (StringUTF8_Duplicate(str));
	if (StringUTF8_Chars(cset_old) != StringUTF8_Chars(cset_new))
		return (NULL);
	// check for duplicate glyphs in the old charset
	i = 0;
	while (cset_old[i])
	{
		length = CharUTF8_Length(cset_old + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		if CCCERROR((StringUTF8_Replace_IndexOfChar(cset_old + i + charlen,
				CharUTF32_FromUTF8(cset_old + i)) >= 0), ERROR_INVALIDARGS,
			"duplicate character in source charset")
			return (NULL);
		i += charlen;
	}
	// each replacement glyph can be up to 4 bytes, so allocate the worst-case size
	result = (t_utf8*)Memory_Allocate(StringUTF8_Chars(str) * 4 + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	written = 0;
	i = 0;
	while (str[i])
	{
		length = CharUTF8_Length(str + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		c_index = StringUTF8_Replace_IndexOfChar(cset_old, CharUTF32_FromUTF8(str + i));
		glyph = (c_index >= 0 ? StringUTF8_Replace_CharAt(cset_new, (t_size)c_index) : str + i);
		if (c_index >= 0)
		{
			length = CharUTF8_Length(glyph);
			for (j = 0; j < (length <= 0 ? 1 : (t_size)length); ++j)
				result[written++] = glyph[j];
		}
		else
		{
			for (j = 0; j < charlen; ++j)
				result[written++] = str[i + j];
		}
		i += charlen;
	}
	result[written] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Replace_String(t_utf8 const* str, t_utf8 const* str_old, t_utf8 const* str_new)
{
	t_utf8*		result;
	t_utf8**	strarr;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((str_old == NULL), ERROR_NULLPOINTER, "old replace string given is NULL")
		return (NULL);
	if CCCERROR((str_new == NULL), ERROR_NULLPOINTER, "new replace string given is NULL")
		return (NULL);
	if ((str_old == str_new) || (StringUTF8_Length(str_old) == 0))
		return (StringUTF8_Duplicate(str));
	strarr = StringUTF8_Split_String(str, str_old);
	result = StringUTF8_Join((t_utf8 const**)strarr, str_new);
	StringArrayUTF8_Delete(&strarr);
	return (result);
}



void	StringUTF8_Replace_Char_InPlace(t_utf8* str, t_utf32 char_old, t_utf32 char_new)
{
	t_utf8	encoded_old[4];
	t_utf8	encoded_new[4];
	t_size	len_old;
	t_size	len_new;
	t_size	i;
	t_size	j;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	if (char_old == char_new || char_old == 0)
		return;
	len_old = CharUTF32_ToUTF8(encoded_old, char_old);
	len_new = CharUTF32_ToUTF8(encoded_new, char_new);
	if CCCERROR((len_old != len_new), ERROR_INVALIDARGS,
		"cannot replace in-place: the two given chars have different UTF-8 encoded lengths")
		return;
	i = 0;
	while (str[i])
	{
		if (CharUTF32_FromUTF8(str + i) == char_old)
		{
			for (j = 0; j < len_new; ++j)
				str[i + j] = encoded_new[j];
			i += len_new;
			continue;
		}
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
}



void	StringUTF8_Replace_Charset_InPlace(t_utf8* str, t_utf8 const* charset_old, t_utf8 const* charset_new)
{
	t_utf8 const*	glyph;
	t_sintmax	c_index;
	t_size	i;
	t_size	j;
	t_size	charlen;
	t_sint	length;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	if CCCERROR((charset_old == NULL), ERROR_NULLPOINTER, "old charset string given is NULL")
		return;
	if CCCERROR((charset_new == NULL), ERROR_NULLPOINTER, "new charset string given is NULL")
		return;
	if (charset_old[0] == '\0' || charset_new[0] == '\0')
		return;
	if (StringUTF8_Chars(charset_old) != StringUTF8_Chars(charset_new))
		return;
	// in-place replacement requires each old/new glyph pair to have the same UTF-8 encoded length,
	// and the old charset to have no duplicate glyphs: otherwise, this function fails silently
	i = 0;
	while (charset_old[i])
	{
		length = CharUTF8_Length(charset_old + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		if (StringUTF8_Replace_IndexOfChar(charset_old + i + charlen,
				CharUTF32_FromUTF8(charset_old + i)) >= 0)
			return;
		c_index = StringUTF8_Replace_IndexOfChar(charset_old, CharUTF32_FromUTF8(charset_old + i));
		glyph = StringUTF8_Replace_CharAt(charset_new, (t_size)c_index);
		length = CharUTF8_Length(glyph);
		if (charlen != (length <= 0 ? 1 : (t_size)length))
			return;
		i += charlen;
	}
	i = 0;
	while (str[i])
	{
		length = CharUTF8_Length(str + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		c_index = StringUTF8_Replace_IndexOfChar(charset_old, CharUTF32_FromUTF8(str + i));
		if (c_index >= 0)
		{
			glyph = StringUTF8_Replace_CharAt(charset_new, (t_size)c_index);
			for (j = 0; j < charlen; ++j)
				str[i + j] = glyph[j];
		}
		i += charlen;
	}
}



void	StringUTF8_Replace_String_InPlace(t_utf8** a_str, t_utf8 const* str_old, t_utf8 const* str_new)
{
	t_utf8*	tmp;

	if CCCERROR((a_str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return;
	tmp = StringUTF8_Replace_String(*a_str, str_old, str_new);
	StringUTF8_Delete(a_str);
	*a_str = tmp;
}
