
#include "libccc/text/unicode.h"
#include "libccc/pointer.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



#define MASK	((1 << 6) - 1)

t_sint		CharUTF8_Length(t_utf8 const* str)
{
	t_u8	c;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR);
	c = str[0];
	if (c & (1 << 7)) // multi-byte character
	{
		if (c & (1 << 6)) // 2-byte character
		{
			if (c & (1 << 5)) // 3-byte character
			{
				if (c & (1 << 4)) // 4-byte character
				{
					if CCCERROR((c & (1 << 3)), ERROR_ILLEGALBYTES,
						"illegal UTF-8 char start byte: '%c'/0x%4.4X", (c ? c : '\a'), c)
						return (ERROR);
					return (4);
				}
				else
				{
					return (3);
				}
			}
			else
			{
				return (2);
			}
		}
		else
		{
			CCCERROR(TRUE, ERROR_ILLEGALBYTES,
				"illegal UTF-8 char start byte: '%c'/0x%4.4X", (c ? c : '\a'), c);
			return (ERROR);
		}
	}
	else if (c == '\0')
	{
		return (0);
	}
	else return (1);
}

t_bool CharUTF8_IsSeqValid(const t_utf8* str, t_size* out_length)
{
	if (out_length) *out_length = SIZE_ERROR;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (FALSE);
	t_sint length = CharUTF8_Length(str);
	if (length == ERROR)
	{
		return (FALSE);
	}

	for (t_sint i = 1; i < length; ++i)
		if CCCERROR((((t_u8)str[i] >> 6) != 2), ERROR_ILLEGALBYTES,
			"illegal UTF-8 at idx %d: '%c'/0x%4.4X",
			i, (str[i] ? str[i] : '\a'), str[i])
			return (FALSE);

	if (out_length) *out_length = length;
	return TRUE;
}

t_bool CharUTF8_IsStringValid(const t_utf8* str, t_size* out_symcount, t_size* out_bytecount)
{
	return CharUTF8_IsStringValid_N(str, SIZE_MAX, out_symcount, out_bytecount);
}

t_bool CharUTF8_IsStringValid_N(const t_utf8* str, t_size n, t_size* out_symcount, t_size* out_bytecount)
{
	t_size symcount = 0;
	t_size bytecount = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
	{
		if (out_symcount)  *out_symcount  = SIZE_ERROR;
		if (out_bytecount) *out_bytecount = SIZE_ERROR;
		return (FALSE);
	}
	while (str[bytecount])
	{
		t_size seq_len = CharUTF8_Length(str + bytecount);

		if (bytecount + seq_len > n)
			break;
		if (!CharUTF8_IsSeqValid(str + bytecount, NULL))
		{
			if (out_symcount)  *out_symcount  = symcount;
			if (out_bytecount) *out_bytecount = bytecount;
			return FALSE;
		}
		++symcount;
		bytecount += seq_len;
	}

	if (out_symcount)  *out_symcount  = symcount;
	if (out_bytecount) *out_bytecount = bytecount;
	return TRUE;
}


t_size		CharUTF32_ToUTF8(t_utf8* dest, t_utf32 c)
{
	t_u8	mask;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if CCCERROR(!CharUTF32_IsValid(c), ERROR_ILLEGALBYTES,
		"invalid unicode character, code point: "SF_U32, c)
		return (0);
	if (c < UTF8_1BYTE)
	{
		dest[0] = (t_u8)c;
		return (1);
	}
	else if (c < UTF8_2BYTE)
	{
		mask = ((1 << 5) - 1);
		dest[0] = (mask & (c >> (6 * 1))) | 0xC0;
		dest[1] = (MASK & (c >> (6 * 0))) | 0x80;
		return (2);
	}
	else if (c < UTF8_3BYTE)
	{
		mask = ((1 << 4) - 1);
		dest[0] = (mask & (c >> (6 * 2))) | 0xE0;
		dest[1] = (MASK & (c >> (6 * 1))) | 0x80;
		dest[2] = (MASK & (c >> (6 * 0))) | 0x80;
		return (3);
	}
	else if (c <= UTF8_4BYTE)
	{
		mask = ((1 << 3) - 1);
		dest[0] = (mask & (c >> (6 * 3))) | 0xF0;
		dest[1] = (MASK & (c >> (6 * 2))) | 0x80;
		dest[2] = (MASK & (c >> (6 * 1))) | 0x80;
		dest[3] = (MASK & (c >> (6 * 0))) | 0x80;
		return (4);
	}
	else return (0);
}



t_utf32		CharUTF32_FromUTF8(t_utf8 const* str)
{
	t_utf32	result = 0;
	t_u8	mask;
	t_u8	c;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR);
	c = str[0];
	if (c & (1 << 7)) // multi-byte character
	{
		if (c & (1 << 6)) // 2-byte character
		{
			if (c & (1 << 5)) // 3-byte character
			{
				if (c & (1 << 4)) // 4-byte character
				{
					if CCCERROR((c & (1 << 3)), ERROR_ILLEGALBYTES,
						"illegal UTF-8 byte: '%c'/0x%4.4X", (c ? c : '\a'), c)
						return (ERROR);
					mask = ((1 << 3) - 1);
					result |= (c & mask) << (6 * 3);	c = str[1];
					result |= (c & MASK) << (6 * 2);	c = str[2];
					result |= (c & MASK) << (6 * 1);	c = str[3];
					result |= (c & MASK);
					return (result);
				}
				else
				{
					mask = ((1 << 4) - 1);
					result |= (c & mask) << (6 * 2);	c = str[1];
					result |= (c & MASK) << (6 * 1);	c = str[2];
					result |= (c & MASK);
					return (result);
				}
			}
			else
			{
				mask = ((1 << 5) - 1);
				result |= (c & mask) << (6 * 1);	c = str[1];
				result |= (c & MASK);
				return (result);
			}
		}
		else
		{
			CCCERROR(TRUE, ERROR_ILLEGALBYTES,
				"illegal UTF-8 byte: '%c'/0x%4.4X", (c ? c : '\a'), c);
			return (ERROR);
		}
	}
	else return ((t_utf32)c);
}

t_size CharUTF8_Copy(t_utf8* dest, t_utf8 const* str)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (SIZE_ERROR);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (SIZE_ERROR);

	t_size length;
	if (!CharUTF8_IsSeqValid(str, &length))
		return SIZE_ERROR;

	for (t_size i = 0; i < length; ++i)
		dest[i] = str[i];
	return length;
}



// TODO: Handle multi-utf8sequence characters, such as skin tone modifier etc
t_sint	CharUTF8_SymbolCount(t_utf8 const* str)
{
	t_size i;
	t_sint result = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR);
	i = 0;
	while (str[i])
	{
		t_size charlen;
		if (!CharUTF8_IsSeqValid(str + i, &charlen))
			return ERROR;
		i += charlen;
		++result;
	}
	return (result);
}

// TODO: Handle multi-utf8sequence characters, such as skin tone modifier etc
t_sint	CharUTF8_SymbolCount_N(t_utf8 const* str, t_size n)
{
	t_size i;
	t_sint result = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR);
	i = 0;
	while (i < n && str[i])
	{
		t_sint charlen = CharUTF8_Length(str + i);
		if (charlen > 0 && (t_size)charlen > n)
			break;
		if (charlen == ERROR || !CharUTF8_IsSeqValid(str + i, NULL))
			return ERROR;
		i += charlen;
		++result;
	}
	return (result);
}

/*
void	CharUTF32_Print_UTF8(t_utf8* dest, t_utf32 c)
{
	t_uint	utf8_length = 0;
	t_uint	utf8_position = 0;
	t_uint	sequence_length = 0;
	t_uint	first_byte_mark = 0;

	// encode as UTF-8 -> takes at maximum 4 bytes to encode:
	// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	if (codepoint < 0x80)
	{
		// normal ASCII, encoding 0xxxxxxx
		utf8_length = 1;
	}
	else if (codepoint < 0x800)
	{
		// two bytes, encoding 110xxxxx 10xxxxxx
		utf8_length = 2;
		first_byte_mark = (t_uint)0xC0; // 11000000
	}
	else if (codepoint < 0x10000)
	{
		// three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx
		utf8_length = 3;
		first_byte_mark = (t_uint)0xE0; // 11100000
	}
	else if (codepoint <= 0x10FFFF)
	{
		// four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx
		utf8_length = 4;
		first_byte_mark = (t_uint)0xF0; // 11110000
	}
	else
		goto failure; // invalid unicode codepoint

	// encode as utf8
	for (utf8_position = (t_uint)(utf8_length - 1); utf8_position > 0; utf8_position--)
	{
		// 10xxxxxx
		(*output_pointer)[(t_sint)utf8_position] = (t_uint)((codepoint | 0x80) & 0xBF);
		codepoint >>= 6;
	}
	// encode first byte
	if (utf8_length > 1)
	{
		(*output_pointer)[0] = (t_uint)((codepoint | first_byte_mark) & DYNAMICTYPE_MASK);
	}
	else
	{
		(*output_pointer)[0] = (t_uint)(codepoint & 0x7F);
	}
}
*/
