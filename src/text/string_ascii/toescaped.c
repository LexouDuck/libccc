
#include "libccc/text/char_ascii.h"
#include "libccc/text/string_ascii.h"
#include "libccc/text/string_utf8.h"

#include LIBCONFIG_ERROR_INCLUDE


_MALLOC()
t_ascii* StringASCII_ToASCIIEscaped(t_ascii const* str)
{
	return StringUTF8_ToASCIIEscaped(str);
}

t_size StringASCII_ToASCIIEscapedBuf(t_ascii *dest, size_t max_writelen, t_ascii const* str)
{
	return StringUTF8_ToASCIIEscapedBuf(dest, max_writelen, str);
}

_MALLOC()
t_ascii* StringASCII_ToJsonEscaped(t_ascii const* str)
{
	return StringUTF8_ToJsonEscaped(str);
}

t_size StringASCII_ToJsonEscapedBuf(t_ascii *dest, t_size max_writelen, t_ascii const* str)
{
	return StringUTF8_ToJsonEscapedBuf(dest, max_writelen, str);
}

t_ascii*	StringASCII_ToEscaped(
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscaped(str, charset, aliases, force_encoding_for, char_encoder);
}

t_ascii*	StringASCII_ToEscaped_e(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_resultlen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscaped_e(out_len, out_readlen, max_resultlen, str, charset, aliases, force_encoding_for, char_encoder);
}

t_size	StringASCII_ToEscapedBuf(
		t_ascii *dest,
		t_size max_writelen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscapedBuf(dest, max_writelen, str, charset, aliases, force_encoding_for, char_encoder);
}

t_size StringASCII_ToEscapedBuf_e(
		t_ascii *dest,
		t_size *out_readlen,
		t_size max_writelen,
		t_ascii const* str,
		t_ascii const* charset,
		t_ascii const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscapedBuf_e(dest, out_readlen, max_writelen, str, charset, aliases, force_encoding_for, char_encoder);
}

