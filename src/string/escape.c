
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/memory.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE

t_size String_EncodeEscape_xFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFF)
		return ERROR;

	if (dest)
	{
		t_u8 hexa0 = (c & 0x0F) >> 0;
		t_u8 hexa1 = (c & 0xF0) >> 4;

		dest[0] = '\\';
		dest[1] = 'x';
		dest[2] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[3] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 4;
}


t_size String_EncodeEscape_uFFFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFFFF)
		return ERROR;

	if (dest)
	{
		t_u8 hexa0 = (c & 0x000F) >> 0;
		t_u8 hexa1 = (c & 0x00F0) >> 4;
		t_u8 hexa2 = (c & 0x0F00) >> 8;
		t_u8 hexa3 = (c & 0xF000) >> 12;

		dest[0] = '\\';
		dest[1] = 'u';
		dest[2] = (hexa3 < 10) ? (hexa3 + '0') : (hexa3 - 10 + 'A');
		dest[3] = (hexa2 < 10) ? (hexa2 + '0') : (hexa2 - 10 + 'A');
		dest[4] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[5] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 6;
}

t_size String_EncodeEscape_UFFFFFFFF(t_char *dest, t_utf32 c)
{
	if (dest)
	{
		t_u8 hexa0 = (c & 0x0000000F) >> 0;
		t_u8 hexa1 = (c & 0x000000F0) >> 4;
		t_u8 hexa2 = (c & 0x00000F00) >> 8;
		t_u8 hexa3 = (c & 0x0000F000) >> 12;
		t_u8 hexa4 = (c & 0x000F0000) >> 16;
		t_u8 hexa5 = (c & 0x00F00000) >> 20;
		t_u8 hexa6 = (c & 0x0F000000) >> 24;
		t_u8 hexa7 = (c & 0xF0000000) >> 28;

		dest[0] = '\\';
		dest[1] = 'U';
		dest[2] = (hexa7 < 10) ? (hexa7 + '0') : (hexa7 - 10 + 'A');
		dest[3] = (hexa6 < 10) ? (hexa6 + '0') : (hexa6 - 10 + 'A');
		dest[4] = (hexa5 < 10) ? (hexa5 + '0') : (hexa5 - 10 + 'A');
		dest[5] = (hexa4 < 10) ? (hexa4 + '0') : (hexa4 - 10 + 'A');
		dest[6] = (hexa3 < 10) ? (hexa3 + '0') : (hexa3 - 10 + 'A');
		dest[7] = (hexa2 < 10) ? (hexa2 + '0') : (hexa2 - 10 + 'A');
		dest[8] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[9] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 10;
}

t_size String_EncodeEscape_smart(t_char *dest, t_utf32 c)
{
	if (UTF32_IsValid(c))
	{
		if (c < 0x10000)
			return String_EncodeEscape_uFFFF(dest, c);
		else
			return String_EncodeEscape_UFFFFFFFF(dest, c);
	}
	else
			return String_EncodeEscape_xFF(dest, c);
}

// TODO: I feel like this could be a niche standard function
//! writes `alias` into `dest` and return number of byte written. If `n` is not big enough to write the entire alias, nothing is written
static size_t Write_Alias(t_char *dest, size_t n, t_char const* alias)
{
	size_t alias_length = String_Length(alias);

	if (alias_length >= n)
		return 0;

	if (dest)
		String_Copy(dest, alias);
	return alias_length;
}

static size_t Write_Encoded(t_char *dest, t_char const* str, t_size writeable, f_char_encoder encoder)
{
	t_utf32 c = UTF32_FromUTF8(str);

	if (encoder(NULL, c) > writeable)
		return 0;
	return encoder(dest, c);
}

t_char*	String_ToEscapeStr(
		t_char const* str,
		t_char const* charset,
		t_char const* const* charset_alias,
		f_should_encode_char should_encode_char,
		f_char_encoder char_encoder)
{
	t_char *result = NULL;
	String_ToEscapeNew(&result, 0, str, charset, charset_alias, should_encode_char, char_encoder);
	return result;
}

t_sint String_ToEscapeNew(
		t_char* *dest,
		size_t n,
		t_char const* str,
		t_char const* charset,
		t_char const* const* charset_alias,
		f_should_encode_char should_encode_char,
		f_char_encoder char_encoder)
{
	t_char *result;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (-1););
	if (n == 0)
		n = SIZE_MAX;

	t_sint getlength_result = String_ToEscapeBuf(NULL, SIZE_MAX, str, charset, charset_alias, should_encode_char, char_encoder);
	if (getlength_result == -1)
		return -1;

	t_size length = (t_size)getlength_result;
	if (length > n)
		length = n;
	result = (t_char*)Memory_Allocate(length + sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), *dest = NULL; return (-1);)

	if (String_ToEscapeBuf(result, length, str, charset, charset_alias, should_encode_char, char_encoder) == -1)
	{
		String_Delete(&result);
		*dest = NULL;
		return -1;
	}

	*dest = result;
	return length;
}

t_sint String_ToEscapeBuf(
		t_char *dest,
		size_t n,
		t_char const* str,
		t_char const* charset,
		t_char const* const* charset_alias,
		f_should_encode_char should_encode_char,
		f_char_encoder char_encoder)
{
	t_size	wr_idx = 0;
	t_size	rd_idx = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return -1;)
	HANDLE_ERROR(NULLPOINTER, (charset_alias == NULL), return -1;)
	HANDLE_ERROR_SF(INVALIDARGS, (String_Length(charset) != StringArray_Length(charset_alias)), return (-1);, "`charset` and `charset_alias` are of different length");
	if (n == 0)
		n = SIZE_MAX;
	for (; wr_idx < (n - 1) && str[rd_idx]; rd_idx += UTF8_Length(str + rd_idx))
	{
		size_t writeable = n - wr_idx - 1;
		size_t written = 0;

		if (should_encode_char(str + rd_idx))
		{
			written = Write_Encoded(dest, str, writeable, char_encoder);
		}
		else
		{
			t_char const *find_res = String_Find_Char(charset, str[rd_idx]);

			if (find_res != NULL)
			{
				int charset_idx = find_res - charset;

				if (charset_alias[charset_idx])
					written = Write_Alias(dest, writeable, charset_alias[charset_idx]);
				else
					written = Write_Encoded(dest, str, writeable, char_encoder);
			}
		}
		if (written == 0)
			break;
		wr_idx += written;
	}
	if (dest)
		dest[wr_idx] = '\0';
	return (wr_idx);
}

