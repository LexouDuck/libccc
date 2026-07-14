
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Add(t_utf8* dest, t_utf8 const* src)
{
	t_size	length;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (dest);
	length = StringUTF8_Length(dest);
	i = 0;
	while (src[i])
	{
		dest[length + i] = src[i];
		++i;
	}
	dest[length + i] = '\0';
	return (dest);
}



t_utf8*	StringUTF8_Add_N(t_utf8* dest, t_utf8 const* src, t_size n)
{
	t_size	length;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (dest);
	length = StringUTF8_Length(dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[length + i] = src[i];
		++i;
	}
	dest[length + i] = '\0';
	return (dest);
}



t_size	StringUTF8_Add_L(t_utf8* dest, t_utf8 const* src, t_size size)
{
	t_size	dst_len;
	t_size	src_len;
	t_size	length;
	t_sint	charlen;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (0);
	src_len = StringUTF8_Length(src);
	dst_len = 0;
	while (dest[dst_len] && dst_len < size)
		++dst_len;
	if (dst_len != size)
	{	// only copy whole multi-byte sequences: stop before any glyph which would be cut by the buffer size
		length = 0;
		while (src[length] && dst_len + length < size - 1)
		{
			charlen = CharUTF8_Length(src + length);
			if (charlen <= 0)
				charlen = 1;
			if (dst_len + length + (t_size)charlen > size - 1)
				break;
			length += (t_size)charlen;
		}
		i = 0;
		while (i < length)
		{
			dest[dst_len + i] = src[i];
			++i;
		}
		dest[dst_len + i] = '\0';
	}
	return (dst_len + src_len);
}
