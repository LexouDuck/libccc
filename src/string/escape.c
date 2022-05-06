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

t_bool ForceEncodingFor_NonAscii(t_char const* str)
{
	return !UTF32_IsASCII(UTF32_FromUTF8(str));
}

t_bool ForceEncodingFor_NonAsciiOrNonPrintable(t_char const* str)
{
	return ForceEncodingFor_NonPrintable(str)
		|| ForceEncodingFor_NonAscii(str);
}


_MALLOC()
t_char* String_ToAsciiEscaped(t_char const* str)
{
	t_size expected_len = String_ToAsciiEscapedBuf(NULL, SIZE_ERROR, str);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	t_char* result = Memory_Allocate((expected_len + 1) * sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)

	if (String_ToAsciiEscapedBuf(result, expected_len + 1, str) == SIZE_ERROR)
	{
		String_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size String_ToAsciiEscapedBuf(t_char *dest, t_size max_writelen, t_char const* str)
{
	t_char const* charset   =     "\\"     "'"     "\""     "/"    "\a"    "\b"    "\t"    "\n"    "\v"    "\f"    "\r"  "\x1B" ;
	t_char const* aliases[] = { "\\\\" , "\\'" , "\\\"" , "\\/" , "\\a" , "\\b" , "\\t" , "\\n" , "\\v" , "\\f" , "\\r" , "\\e" };

	return String_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonAsciiOrNonPrintable, ENCODER_smart);
}


_MALLOC()
t_char* String_ToJsonEscaped(t_char const* str)
{
	t_size expected_len = String_ToJsonEscapedBuf(NULL, SIZE_ERROR, str);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	t_char* result = Memory_Allocate((expected_len + 1) * sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)

	if (String_ToJsonEscapedBuf(result, expected_len + 1, str) == SIZE_ERROR)
	{
		String_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size String_ToJsonEscapedBuf(t_char *dest, t_size max_writelen, t_char const* str)
{
	t_char const* charset   =    "\b"    "\f"    "\n"    "\r"    "\t"     "\""     "\\";
	t_char const* aliases[] = { "\\b" , "\\f" , "\\n" , "\\r" , "\\t" , "\\\"" , "\\\\"};

	return String_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonPrintable, ENCODER_uFFFF);
}





static t_size Write_Alias(t_char *dest, t_size max_writelen, t_char const* alias)
{
	t_size expected_len = String_Length(alias);

	if (expected_len > max_writelen)
		return 0;

	if (dest)
	{
		String_Copy(dest, alias);
	}
	return expected_len;
}

static t_size Write_Encoded(t_char *dest, t_char const* str, t_size writeable_len, f_char_encoder encoder)
{
	t_utf32 c = UTF32_FromUTF8(str);
	//note: `str` has already been check for validity, call could not fail

	t_size expected_len = encoder(NULL, c);
	if (expected_len == (t_size)ERROR)
		return ((t_size)-1); // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size)-1" to "SIZE_ERROR"
	if (expected_len > writeable_len)
		return 0;
	t_size actual_len = encoder(dest, c);
	
	HANDLE_ERROR(INVALIDARGS, (expected_len != actual_len), return ((t_size)-1);) // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size)-1" to "SIZE_ERROR"

	return actual_len;
}


t_char*	String_ToEscaped(
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return String_ToEscaped_e(NULL, NULL, SIZE_ERROR, str, charset, aliases, force_encoding_for, char_encoder);
}

t_char*	String_ToEscaped_e(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_resultlen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_char *result;

	if (out_len) *out_len = SIZE_ERROR;

	// The `max_resultlen` of `*ToEscapedBuf` does include the final '\0', unlike the `max_resultlen` of `*ToEscape`
	t_size new_max_resultlen = (max_resultlen != SIZE_ERROR && max_resultlen != SIZE_MAX ? max_resultlen + 1 : SIZE_ERROR);
	t_size expected_len = String_ToEscapedBuf_e(NULL, out_readlen, new_max_resultlen, str, charset, aliases, force_encoding_for, char_encoder);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	result = (t_char*)Memory_Allocate(expected_len + sizeof(t_char));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)

	
	t_size actual_len = String_ToEscapedBuf_e(result, out_readlen, expected_len + 1, str, charset, aliases, force_encoding_for, char_encoder);
	if (actual_len == SIZE_ERROR)
	{
		String_Delete(&result);
		return (NULL);
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
	return String_ToEscapedBuf_e(dest, NULL, max_writelen, str, charset, aliases, force_encoding_for, char_encoder);
}

t_size String_ToEscapedBuf_e(
		t_char *dest,
		t_size *out_readlen,
		t_size max_writelen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_size	wr_idx = 0;
	t_size	rd_idx = SIZE_ERROR; // value to return in *out_readlen function fails before parsing begins

	{
		HANDLE_ERROR(NULLPOINTER, (str == NULL)    , goto failure;)
		HANDLE_ERROR(NULLPOINTER, (charset == NULL), goto failure;)
		HANDLE_ERROR(NULLPOINTER, (aliases == NULL), goto failure;)
		t_size charset_symcount;
		t_size charset_bytecount;
		if (!UTF8_IsStringValid(charset, &charset_symcount, &charset_bytecount))
			HANDLE_ERROR_SF(INVALIDARGS, TRUE, goto failure;,
					"Charset contains invalid sequence at symbol %zu (byte %zu): \"%.4s\"", charset_symcount, charset_bytecount + 1, charset + charset_bytecount + 1
				);
	}

	rd_idx = 0;

	if (max_writelen == SIZE_ERROR)
		max_writelen = SIZE_MAX;
	while (wr_idx < (max_writelen - 1) && str[rd_idx] != '\0')
	{
		t_char* write_head = (dest ? dest + wr_idx : NULL);
		t_char const* read_head = str + rd_idx;
		t_size writeable_len = max_writelen - wr_idx - 1;
		t_size len_written = 0;
		t_size len_read;
		if (!UTF8_IsSeqValid(read_head, &len_read))
			HANDLE_ERROR(ILLEGALBYTES, TRUE, goto failure;)

		t_char const *alias = NULL;
		t_char const *find_res = String_Find_Char(charset, UTF32_FromUTF8(read_head));

		if (find_res != NULL)
		{
			int index = UTF8_SymbolCount_N(charset, find_res - charset);
			alias = aliases[index];
		}

		if (find_res != NULL || (force_encoding_for && force_encoding_for(read_head)))
		{
			if (alias)
			{
				len_written = Write_Alias(write_head, writeable_len, alias);
			}
			else
			{
				HANDLE_ERROR(NULLPOINTER, (char_encoder == NULL), goto failure;)
				len_written = Write_Encoded(write_head, read_head, writeable_len, char_encoder);
				if (len_written == ((t_size)-1)) // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size)-1" to "SIZE_ERROR"
					goto failure;
			}
		}
		else
		{
			len_written = len_read;
			if (dest)
				String_Copy_N(write_head, read_head, len_read);
		}

		if (len_written == 0)
			break;
		wr_idx += len_written;
		rd_idx += len_read;
	}
	if (dest)
		dest[wr_idx] = '\0';
	if (out_readlen)
		*out_readlen = rd_idx;
	return (wr_idx);

failure:
	if (dest)
		dest[wr_idx] = '\0';
	if (out_readlen)
		*out_readlen = rd_idx;
	return SIZE_ERROR;
}

