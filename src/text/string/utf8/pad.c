
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Returns the byte offset of the glyph at index `n` within the given string
static
t_size	StringUTF8_Pad_OffsetOfChar(t_utf8 const* str, t_size n)
{
	t_size	offset;
	t_sint	charlen;

	offset = 0;
	while (n-- && str[offset])
	{
		charlen = CharUTF8_Length(str + offset);
		offset += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (offset);
}

//! Constructs a padded string: `pads_l` pad chars, then `chars` glyphs of `str` (from glyph `from`), then `pads_r` pad chars
static
t_utf8*	StringUTF8_Pad_Construct(t_utf8 const* str, t_size from, t_size chars, t_utf32 c, t_size pads_l, t_size pads_r)
{
	t_utf8	padded[4];
	t_size	padlen;
	t_utf8*	result;
	t_size	offset;
	t_size	length;
	t_size	i;
	t_size	j;

	padlen = CharUTF32_ToUTF8(padded, c);
	if CCCERROR((padlen == 0), ERROR_INVALIDARGS,
		"padding character given is not a valid unicode code point")
		return (NULL);
	offset = StringUTF8_Pad_OffsetOfChar(str, from);
	length = StringUTF8_Pad_OffsetOfChar(str + offset, chars);
	result = (t_utf8*)Memory_Allocate((pads_l + pads_r) * padlen + length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (pads_l--)
	{
		for (j = 0; j < padlen; ++j)
			result[i++] = padded[j];
	}
	for (j = 0; j < length; ++j)
		result[i++] = str[offset + j];
	while (pads_r--)
	{
		for (j = 0; j < padlen; ++j)
			result[i++] = padded[j];
	}
	result[i] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Pad(t_utf8 const* str, t_utf32 c, t_size length)
{
	t_size	chars;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	chars = StringUTF8_Chars(str);
	if (length == chars)
		return (StringUTF8_Duplicate(str));
	if (length < chars)
		return (StringUTF8_Pad_Construct(str, (chars - length) / 2, length, c, 0, 0));
	return (StringUTF8_Pad_Construct(str, 0, chars, c,
		(length - chars) / 2,
		(length - chars) - (length - chars) / 2));
}



t_utf8*	StringUTF8_Pad_L(t_utf8 const* str, t_utf32 c, t_size length)
{
	t_size	chars;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	chars = StringUTF8_Chars(str);
	if (length == chars)
		return (StringUTF8_Duplicate(str));
	if (length < chars)
		return (StringUTF8_Pad_Construct(str, chars - length, length, c, 0, 0));
	return (StringUTF8_Pad_Construct(str, 0, chars, c, length - chars, 0));
}



t_utf8*	StringUTF8_Pad_R(t_utf8 const* str, t_utf32 c, t_size length)
{
	t_size	chars;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	chars = StringUTF8_Chars(str);
	if (length == chars)
		return (StringUTF8_Duplicate(str));
	if (length < chars)
		return (StringUTF8_Pad_Construct(str, 0, length, c, 0, 0));
	return (StringUTF8_Pad_Construct(str, 0, chars, c, 0, length - chars));
}
