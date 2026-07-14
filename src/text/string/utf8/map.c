
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Shrinks the given map result buffer to its final length, and null-terminates it
static
t_utf8*	StringUTF8_Map_Finalize(t_utf8* result, t_size written)
{
	t_utf8*	tmp;

	result[written] = '\0';
	tmp = (t_utf8*)Memory_Reallocate(result, written + sizeof(""));
	if (tmp == NULL)
		return (result);
	return (tmp);
}



t_utf8*	StringUTF8_Map(t_utf8 const* str, t_utf32 (*map)(t_utf32 c))
{
	t_utf8*	result;
	t_size	length;
	t_size	written;
	t_size	padlen;
	t_size	i;
	t_sint	charlen;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	result = (t_utf8*)Memory_Allocate(length * 4 + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	written = 0;
	i = 0;
	while (str[i])
	{
		padlen = CharUTF32_ToUTF8(result + written, map(CharUTF32_FromUTF8(str + i)));
		written += padlen;
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (StringUTF8_Map_Finalize(result, written));
}



t_utf8*	StringUTF8_Map_I(t_utf8 const* str, t_utf32 (*map)(t_utf32 c, t_size index))
{
	t_utf8*	result;
	t_size	length;
	t_size	written;
	t_size	padlen;
	t_size	i;
	t_sint	charlen;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	result = (t_utf8*)Memory_Allocate(length * 4 + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	written = 0;
	i = 0;
	while (str[i])
	{
		padlen = CharUTF32_ToUTF8(result + written, map(CharUTF32_FromUTF8(str + i), i));
		written += padlen;
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (StringUTF8_Map_Finalize(result, written));
}



t_utf8*	StringUTF8_Map_InPlace(t_utf8** a_str, t_utf32 (*map)(t_utf32))
{
	t_utf8*	tmp;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((a_str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return (NULL);
	tmp = StringUTF8_Map(*a_str, map);
	StringUTF8_Delete(a_str);
	*a_str = tmp;
	return (tmp);
}
