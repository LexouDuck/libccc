
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Copy(t_utf8* dest, t_utf8 const* src)
{
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (dest);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}



t_utf8*	StringUTF8_Copy_N(t_utf8* dest, t_utf8 const* src, t_size n)
{
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		++i;
	}
	return (dest);
}



t_size	StringUTF8_Copy_L(t_utf8* dest, t_utf8 const* src, t_size size)
{
	t_size	length;
	t_sint	charlen;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (0);
	if (size > 0)
	{	// only copy whole multi-byte sequences: stop before any glyph which would be cut by the buffer size
		length = 0;
		while (src[length] && length < size - 1)
		{
			charlen = CharUTF8_Length(src + length);
			if (charlen <= 0)
				charlen = 1;
			if (length + (t_size)charlen > size - 1)
				break;
			length += (t_size)charlen;
		}
		i = 0;
		while (i < length)
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	return (StringUTF8_Length(src));
}
