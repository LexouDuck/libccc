
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/memory.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE


t_bool ForceEncodingFor_NonPrintable(t_char const* str)
{
	return !UTF32_IsPrintable(UTF32_FromUTF8(str));
}

_MALLOC()
t_char* String_ToAnsiEscaped(t_char const* str)
{
	t_size expected_len = String_ToAnsiEscapedBuf(NULL, SIZE_ERROR, str);
	t_char* result = Memory_Allocate((expected_len + 1) * sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)

	if (String_ToAnsiEscapedBuf(result, expected_len, str) == SIZE_ERROR)
	{
		String_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size					String_ToAnsiEscapedBuf(t_char *dest, size_t max_writelen, t_char const* str)
{
	t_char charset[]        = {   '\\' ,  '\'' ,    '"' ,   '/' ,   '?' ,  '\a' ,  '\b' ,  '\t' ,  '\n' ,  '\v' ,  '\f' ,  '\r' , '\x1B' };
	t_char const* aliases[] = { "\\\\" , "\\'" , "\\\"" , "\\/" , "\\?" , "\\a" , "\\b" , "\\t" , "\\n" , "\\v" , "\\f" , "\\r" ,  "\\e" };

	return String_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonPrintable, ENCODER_smart);
}


_MALLOC()
t_char* String_ToJsonEscaped(t_char const* str)
{
	t_size expected_len = String_ToJsonEscapedBuf(NULL, SIZE_ERROR, str);
	t_char* result = Memory_Allocate((expected_len + 1) * sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)

	if (String_ToJsonEscapedBuf(result, expected_len, str) == SIZE_ERROR)
	{
		String_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size String_ToJsonEscapedBuf(t_char *dest, size_t max_writelen, t_char const* str)
{
	t_char charset[]        = {  '\b' ,  '\f' ,  '\n' ,  '\r' ,  '\t' ,  '"' ,   '\\'};
	t_char const* aliases[] = { "\\b" , "\\f" , "\\n" , "\\r" , "\\t" , "\"" , "\\\\"};

	return String_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonPrintable, ENCODER_uFFFF);
}





static size_t Write_Alias(t_char *dest, size_t max_writelen, t_char const* alias)
{
	size_t alias_length = String_Length(alias);

	if (alias_length >= max_writelen)
		return 0;

	if (dest)
		String_Copy(dest, alias);
	return alias_length;
}

static size_t Write_Encoded(t_char *dest, t_char const* str, t_size writeable_len, f_char_encoder encoder)
{
	t_utf32 c = UTF32_FromUTF8(str);

	if (encoder(NULL, c) > writeable_len)
		return 0;
	return encoder(dest, c);
}


t_char*	String_ToEscaped(
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return String_ToEscaped_(NULL, NULL, SIZE_ERROR, str, charset, aliases, force_encoding_for, char_encoder);
}

t_char*	String_ToEscaped_(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_writelen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_char *result;

	if (max_writelen == SIZE_ERROR)
		max_writelen = SIZE_MAX;

	t_size expected_len = String_ToEscapedBuf(NULL, SIZE_MAX, str, charset, aliases, force_encoding_for, char_encoder);
	if (expected_len == SIZE_ERROR)
		return (SIZE_ERROR);

	if (expected_len > max_writelen)
		expected_len = max_writelen;
	result = (t_char*)Memory_Allocate(expected_len + sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (SIZE_ERROR);)

	
	t_size actual_len = String_ToEscapedBuf_(result, out_readlen, expected_len, str, charset, aliases, force_encoding_for, char_encoder);
	if (actual_len == SIZE_ERROR)
	{
		String_Delete(&result);
		return (SIZE_ERROR);
	}

	if (out_len)
		*out_len = actual_len;
	return result;
}

t_size	String_ToEscapedBuf(
		t_char *dest,
		t_size max_writelen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return String_ToEscapedBuf_(dest, NULL, max_writelen, str, charset, aliases, force_encoding_for, char_encoder);
}

t_size String_ToEscapedBuf_(
		t_char *dest,
		t_size *out_readlen,
		size_t max_writelen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_size	wr_idx = 0;
	t_size	rd_idx = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (SIZE_ERROR);)
	HANDLE_ERROR(NULLPOINTER, (aliases == NULL), return (SIZE_ERROR);)
	HANDLE_ERROR_SF(INVALIDARGS, (String_Length(charset) != StringArray_Length(aliases)), return ((SIZE_ERROR));, "`charset` and `aliases` are of different length");
	if (max_writelen == SIZE_ERROR)
		max_writelen = SIZE_MAX;
	for (; wr_idx < (max_writelen - 1) && str[rd_idx]; rd_idx += UTF8_Length(str + rd_idx))
	{
		size_t writeable_len = max_writelen - wr_idx - 1;
		size_t written = 0;

		if (force_encoding_for != NULL && force_encoding_for(str + rd_idx))
		{
			HANDLE_ERROR(NULLPOINTER, (char_encoder == NULL), return (SIZE_ERROR);)
			written = Write_Encoded(dest, str, writeable_len, char_encoder);
		}
		else
		{
			t_char const *find_res = String_Find_Char(charset, str[rd_idx]);

			if (find_res != NULL)
			{
				int charset_idx = find_res - charset;

				if (aliases[charset_idx])
					written = Write_Alias(dest, writeable_len, aliases[charset_idx]);
				else
				{
					HANDLE_ERROR(NULLPOINTER, (char_encoder == NULL), return (SIZE_ERROR);)
					written = Write_Encoded(dest, str, writeable_len, char_encoder);
				}
			}
		}
		if (written == 0)
			break;
		wr_idx += written;
	}
	if (dest)
		dest[wr_idx] = '\0';
	if (out_readlen)
		*out_readlen = rd_idx;
	return (wr_idx);
}

