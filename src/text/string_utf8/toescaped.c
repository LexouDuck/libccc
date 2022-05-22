
#include "libccc/text/string_utf8.h"
#include "libccc/text/string_ascii.h"
#include "libccc/memory.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE


// TODO: This should very unconveniently return `FALSE` for `modifier sequence` codepoints ONLY if it appears at the beginning of the string
t_bool ForceEncodingFor_NonPrintable(t_utf8 const* str)
{
	return !CharUTF32_IsPrintable(CharUTF32_FromUTF8(str));
}

t_bool ForceEncodingFor_NonASCII(t_utf8 const* str)
{
	return !CharUTF32_IsASCII(CharUTF32_FromUTF8(str));
}

t_bool ForceEncodingFor_NonASCIIOrNonPrintable(t_utf8 const* str)
{
	return ForceEncodingFor_NonPrintable(str)
		|| ForceEncodingFor_NonASCII(str);
}


_MALLOC()
t_utf8* StringUTF8_ToASCIIEscaped(t_utf8 const* str)
{
	t_size expected_len = StringUTF8_ToASCIIEscapedBuf(NULL, SIZE_ERROR, str);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	t_utf8* result = Memory_Allocate((expected_len + 1) * sizeof(t_utf8));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);

	if (StringUTF8_ToASCIIEscapedBuf(result, expected_len + 1, str) == SIZE_ERROR)
	{
		StringASCII_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size StringUTF8_ToASCIIEscapedBuf(t_utf8 *dest, t_size max_writelen, t_utf8 const* str)
{
	t_utf8 const* charset   =     "\\"     "'"     "\""     "/"    "\a"    "\b"    "\t"    "\n"    "\v"    "\f"    "\r"  "\x1B" ;
	t_utf8 const* aliases[] = { "\\\\" , "\\'" , "\\\"" , "\\/" , "\\a" , "\\b" , "\\t" , "\\n" , "\\v" , "\\f" , "\\r" , "\\e" };

	return StringUTF8_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonASCIIOrNonPrintable, ENCODER_smart);
}


_MALLOC()
t_utf8* StringUTF8_ToJsonEscaped(t_utf8 const* str)
{
	t_size expected_len = StringUTF8_ToJsonEscapedBuf(NULL, SIZE_ERROR, str);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	t_utf8* result = Memory_Allocate((expected_len + 1) * sizeof(t_utf8));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);

	if (StringUTF8_ToJsonEscapedBuf(result, expected_len + 1, str) == SIZE_ERROR)
	{
		StringASCII_Delete(&result);
		return (NULL);
	}
	return result;
}

t_size StringUTF8_ToJsonEscapedBuf(t_utf8 *dest, t_size max_writelen, t_utf8 const* str)
{
	t_utf8 const* charset   =    "\b"    "\f"    "\n"    "\r"    "\t"     "\""     "\\";
	t_utf8 const* aliases[] = { "\\b" , "\\f" , "\\n" , "\\r" , "\\t" , "\\\"" , "\\\\"};

	return StringUTF8_ToEscapedBuf(dest, max_writelen, str, charset, aliases, ForceEncodingFor_NonPrintable, ENCODER_uFFFF);
}





static t_size Write_Alias(t_utf8 *dest, t_size max_writelen, t_utf8 const* alias)
{
	t_size expected_len = StringASCII_Length(alias);

	if (expected_len > max_writelen)
		return 0;

	if (dest)
	{
		StringASCII_Copy(dest, alias);
	}
	return expected_len;
}

static t_size Write_Encoded(t_utf8 *dest, t_utf8 const* str, t_size writeable_len, f_char_encoder encoder)
{
	t_utf32 c = CharUTF32_FromUTF8(str);
	//note: `str` has already been check for validity, call could not fail

	t_size expected_len = encoder(NULL, c);
	if (expected_len == (t_size)ERROR)
		return ((t_size)-1); // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size)-1" to "SIZE_ERROR"
	if (expected_len > writeable_len)
		return 0;
	t_size actual_len = encoder(dest, c);
	
	if CCCERROR((expected_len != actual_len), ERROR_INVALIDARGS, NULL)
		return ((t_size)-1); // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size-1" to "SIZE_ERROR"

	return actual_len;
}


t_utf8*	StringUTF8_ToEscaped(
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscaped_e(NULL, NULL, SIZE_ERROR, str, charset, aliases, force_encoding_for, char_encoder);
}

t_utf8*	StringUTF8_ToEscaped_e(
		t_size *out_len,
		t_size *out_readlen,
		t_size max_resultlen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_utf8 *result;

	if (out_len) *out_len = SIZE_ERROR;

	// The `max_resultlen` of `*ToEscapedBuf` does include the final '\0', unlike the `max_resultlen` of `*ToEscape`
	t_size new_max_resultlen = (max_resultlen != SIZE_ERROR && max_resultlen != SIZE_MAX ? max_resultlen + 1 : SIZE_ERROR);
	t_size expected_len = StringUTF8_ToEscapedBuf_e(NULL, out_readlen, new_max_resultlen, str, charset, aliases, force_encoding_for, char_encoder);
	if (expected_len == SIZE_ERROR)
		return (NULL);

	result = (t_utf8*)Memory_Allocate(expected_len + sizeof(t_utf8));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);

	
	t_size actual_len = StringUTF8_ToEscapedBuf_e(result, out_readlen, expected_len + 1, str, charset, aliases, force_encoding_for, char_encoder);
	if (actual_len == SIZE_ERROR)
	{
		StringASCII_Delete(&result);
		return (NULL);
	}

	if (out_len)
		*out_len = actual_len;
	return result;
}

t_size	StringUTF8_ToEscapedBuf(
		t_utf8 *dest,
		t_size max_writelen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	return StringUTF8_ToEscapedBuf_e(dest, NULL, max_writelen, str, charset, aliases, force_encoding_for, char_encoder);
}

t_size StringUTF8_ToEscapedBuf_e(
		t_utf8 *dest,
		t_size *out_readlen,
		t_size max_writelen,
		t_utf8 const* str,
		t_utf8 const* charset,
		t_utf8 const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_size	wr_idx = 0;
	t_size	rd_idx = SIZE_ERROR; // value to return in *out_readlen function fails before parsing begins

	{
		if CCCERROR((char_encoder == NULL), ERROR_NULLPOINTER, "char_encoder() function given is NULL")
			goto failure;
		if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
			goto failure;
		if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
			goto failure;
		if CCCERROR((aliases == NULL), ERROR_NULLPOINTER, "array of escape aliases given is NULL")
			goto failure;
		t_size charset_symcount;
		t_size charset_bytecount;
		if (!CharUTF8_IsStringValid(charset, &charset_symcount, &charset_bytecount))
			if CCCERROR(TRUE, ERROR_INVALIDARGS,
				"Charset contains invalid sequence at symbol "SF_SIZE" (byte "SF_SIZE"): \"%.4s\"",
				charset_symcount,
				charset_bytecount + 1,
				charset + charset_bytecount + 1)
				goto failure;
	}

	rd_idx = 0;

	if (max_writelen == SIZE_ERROR)
		max_writelen = SIZE_MAX;
	while (wr_idx < (max_writelen - 1) && str[rd_idx] != '\0')
	{
		t_utf8* write_head = (dest ? dest + wr_idx : NULL);
		t_utf8 const* read_head = str + rd_idx;
		t_size writeable_len = max_writelen - wr_idx - 1;
		t_size len_written = 0;
		t_size len_read;
		if (!CharUTF8_IsSeqValid(read_head, &len_read))
			if CCCERROR(TRUE, ERROR_ILLEGALBYTES, NULL) goto failure;

		t_utf8 const *alias = NULL;
		t_utf8 const *find_res = StringASCII_Find_Char(charset, CharUTF32_FromUTF8(read_head));

		if (find_res != NULL)
		{
			t_sint index = CharUTF8_SymbolCount_N(charset, find_res - charset);
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
				len_written = Write_Encoded(write_head, read_head, writeable_len, char_encoder);
				if (len_written == ((t_size)-1)) // DZ_ON_REFACTOR_OF_SIZE_ERROR: change "(t_size)-1" to "SIZE_ERROR"
					goto failure;
			}
		}
		else
		{
			len_written = len_read;
			if (dest)
				StringASCII_Copy_N(write_head, read_head, len_read);
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

