
#include "libccc/memory.h"
#include "libccc/compress/lzw.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	See "libccc/compress/lzw.h" for a description of the compressed stream
**	format(s), which can be selected via `LIBCONFIG_COMPRESS_LZW_FORMAT`.
**
**	Some format-specific quirks handled here:
**	- code bit-packing order: LSB-first (RAW/GIF, UNIX) or MSB-first (TIFF)
**	- the TIFF "early change": the code width increases one code early
**	- the UNIX `compress` code grouping: codes are written in groups of 8
**		(so, groups of `width` bytes), and whenever the code width changes
**		(or a "clear" code is emitted), the rest of the current group is
**		zero-padded, and the reader must skip those padding bits
**
**	NOTE on encoder/decoder synchronization: the decoder's dictionary always
**	lags one entry behind the encoder's (the decoder can only complete an entry
**	once it has received the *next* code). This is compensated by the timing of
**	the width-increase checks: the encoder checks after writing a code (but
**	before adding that step's new entry), whereas the decoder checks before
**	reading each code - this way, both sides change width between the same
**	two codes of the stream. This mirrors the reference implementations
**	(UNIX compress, GIF codecs, libtiff).
*/

#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_TIFF)
	#define LZW_MSBFIRST	1	//!< Codes are packed most-significant-bit first
	#define LZW_EARLYCHANGE	1	//!< Code width increases one code early (TIFF quirk)
	#define LZW_GROUPED		0	//!< No code grouping
	#define LZW_HAS_END		1	//!< Stream is terminated by an "end" code
	#define LZW_CODE_FIRST	258	//!< First dynamically-assigned dictionary code
	//! The TIFF spec mandates that the encoder emit a "clear" code when the table reaches 4094 entries
	#define LZW_CLEAR_THRESHOLD	(LZW_CODES_MAX - 2)
#elif (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
	#define LZW_MSBFIRST	0
	#define LZW_EARLYCHANGE	0
	#define LZW_GROUPED		1
	#define LZW_HAS_END		0	//!< No "end" code: the stream ends with the input
	#define LZW_CODE_FIRST	257	//!< (block mode: code 256 is the "clear" code, and there is no "end" code)
	#define LZW_CLEAR_THRESHOLD	(LZW_CODES_MAX)
#else // LZW_FORMAT_RAW / LZW_FORMAT_GIF
	#define LZW_MSBFIRST	0
	#define LZW_EARLYCHANGE	0
	#define LZW_GROUPED		0
	#define LZW_HAS_END		1
	#define LZW_CODE_FIRST	258
	#define LZW_CLEAR_THRESHOLD	(LZW_CODES_MAX)
#endif

//! The amount of hash buckets used by the compressor's dictionary (2x the max code amount)
#define LZW_HASHBITS	(LZW_MAXBITS + 1)
#define LZW_HASHSIZE	((t_u32)1 << LZW_HASHBITS)



/*============================================================================*\
||                          Variable-width bit i/o                            ||
\*============================================================================*/

//! Holds the state of a variable-width bit-stream reader/writer
typedef struct lzw_bits
{
	t_size	pos;	//!< current byte position (if `LZW_GROUPED`: the current group's base position)
	t_u32	acc;	//!< bit accumulator (not used if `LZW_GROUPED`)
	t_uint	bits;	//!< amount of pending bits in `acc` (not used if `LZW_GROUPED`)
	t_uint	codes;	//!< amount of codes read/written in the current group (only used if `LZW_GROUPED`)
	t_uint	width;	//!< current code width, in bits
}	s_lzw_bits;

//! Writes a single code of `b->width` bits to `dest`
static
void	LZW_Bits_Put(s_lzw_bits* b, t_u8* dest, t_u32 code)
{
#if LZW_GROUPED
	t_uint	bito;
	t_size	idx;
	if (b->codes == 8)
	{
		b->pos += b->width;
		b->codes = 0;
	}
	if (b->codes == 0)
		Memory_Set(dest + b->pos, 0, b->width); // groups are zeroed in advance, so codes can be OR-ed in
	bito = b->codes * b->width;
	idx = b->pos + (bito >> 3);
	code <<= (bito & 7);
	dest[idx] |= (t_u8)code;
	if ((code >>= 8))	dest[idx + 1] |= (t_u8)code;
	if ((code >>= 8))	dest[idx + 2] |= (t_u8)code;
	b->codes += 1;
#elif LZW_MSBFIRST
	b->acc = (b->acc << b->width) | code;
	b->bits += b->width;
	while (b->bits >= 8)
	{
		b->bits -= 8;
		dest[b->pos++] = (t_u8)(b->acc >> b->bits);
	}
#else
	b->acc |= (code << b->bits);
	b->bits += b->width;
	while (b->bits >= 8)
	{
		dest[b->pos++] = (t_u8)b->acc;
		b->acc >>= 8;
		b->bits -= 8;
	}
#endif
}

//! Reads a single code of `b->width` bits from `data`, returns `FALSE` if there are not enough bits left
static
t_bool	LZW_Bits_Get(s_lzw_bits* b, t_u8 const* data, t_size size, t_u32* out_code)
{
#if LZW_GROUPED
	t_uint	bito;
	t_uint	have;
	t_size	idx;
	t_u32	value;
	if (b->codes == 8)
	{
		b->pos += b->width;
		b->codes = 0;
	}
	bito = b->codes * b->width;
	if (b->pos + ((bito + b->width + 7) >> 3) > size)
		return (FALSE); // any bits left over are (at most `width - 1` bits of) padding
	idx = b->pos + (bito >> 3);
	value = (data[idx] >> (bito & 7));
	have = 8 - (bito & 7);
	while (have < b->width)
	{
		idx += 1;
		value |= ((t_u32)data[idx] << have);
		have += 8;
	}
	*out_code = value & (((t_u32)1 << b->width) - 1);
	b->codes += 1;
	return (TRUE);
#elif LZW_MSBFIRST
	while (b->bits < b->width)
	{
		if (b->pos >= size)
			return (FALSE);
		b->acc = (b->acc << 8) | data[b->pos++];
		b->bits += 8;
	}
	b->bits -= b->width;
	*out_code = (b->acc >> b->bits) & (((t_u32)1 << b->width) - 1);
	return (TRUE);
#else
	while (b->bits < b->width)
	{
		if (b->pos >= size)
			return (FALSE);
		b->acc |= ((t_u32)data[b->pos++] << b->bits);
		b->bits += 8;
	}
	*out_code = b->acc & (((t_u32)1 << b->width) - 1);
	b->acc >>= b->width;
	b->bits -= b->width;
	return (TRUE);
#endif
}

//! Handles a code width change (or dictionary clear) transition, for the bit reader/writer
/*!
**	For the `LZW_GROUPED` (UNIX) format, this skips/pads the rest of the current
**	group of 8 codes. For the other formats, this is a no-op: codes are packed
**	back-to-back, so nothing special happens on a width change.
**	NOTE: this must be called *before* changing `b->width`.
*/
static
void	LZW_Bits_Transition(s_lzw_bits* b)
{
#if LZW_GROUPED
	if (b->codes > 0)
	{
		b->pos += b->width;
		b->codes = 0;
	}
#else
	(void)b;
#endif
}

//! (writer only) Flushes any pending bits, and returns the total amount of bytes written
static
t_size	LZW_Bits_Finish(s_lzw_bits* b, t_u8* dest)
{
#if LZW_GROUPED
	(void)dest;
	return (b->pos + ((b->codes * b->width + 7) >> 3)); // only the used bytes of the final group
#elif LZW_MSBFIRST
	if (b->bits > 0)
		dest[b->pos++] = (t_u8)(b->acc << (8 - b->bits)); // final bits are padded with zeros (to the right)
	return (b->pos);
#else
	if (b->bits > 0)
		dest[b->pos++] = (t_u8)b->acc; // final bits are padded with zeros (in the upper bits)
	return (b->pos);
#endif
}



/*============================================================================*\
||                          Stream parsing/validation                         ||
\*============================================================================*/

//! Parses LZW-compressed data, validating it, and computing its decompressed size
/*!
**	This simulates the LZW dictionary construction (only keeping track of the
**	*length* of each dictionary entry, since the actual bytes are not needed
**	to compute the total decompressed size).
*/
static
t_bool	LZW_Parse(t_size* out_size, t_u8 const* data, t_size size)
{
	s_lzw_bits	b = {0};
	t_u32*	lengths;
	t_size	produced;
	t_u32	next_code;
	t_u32	code;
	t_u32	entry_len;
	t_u32	prev_len;
	t_bool	have_prev;
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
	t_uint	width_max;
	t_u32	codes_max;
	t_u32	code_first;
	t_bool	has_clear;

	*out_size = 0;
	if CCCERROR((size < LZW_HEADER_SIZE), ERROR_ILLEGALBYTES,
		"invalid LZW data: too short to contain the stream header")
		return (FALSE);
	if CCCERROR((data[0] != LZW_HEADER_MAGIC_0 || data[1] != LZW_HEADER_MAGIC_1), ERROR_ILLEGALBYTES,
		"invalid LZW data: stream does not begin with the expected magic bytes")
		return (FALSE);
	width_max = (data[2] & 0x1F);
	has_clear = ((data[2] & 0x80) != 0);
	if CCCERROR((width_max < LZW_WIDTH_INIT || width_max > LZW_MAXBITS), ERROR_ILLEGALBYTES,
		"invalid LZW data: the stream's maximum code width exceeds the compiled-in LZW_MAXBITS maximum")
		return (FALSE);
	codes_max = ((t_u32)1 << width_max);
	code_first = (has_clear ? 257 : 256);
	b.pos = LZW_HEADER_SIZE;
#else
	t_uint const	width_max = LZW_MAXBITS;
	t_u32 const		codes_max = LZW_CODES_MAX;
	t_u32 const		code_first = LZW_CODE_FIRST;

	*out_size = 0;
#endif
	lengths = (t_u32*)Memory_Allocate(codes_max * sizeof(t_u32));
	if CCCERROR((lengths == NULL), ERROR_ALLOCFAILURE, NULL)
		return (FALSE);
	b.width = LZW_WIDTH_INIT;
	next_code = code_first;
	produced = 0;
	prev_len = 0;
	have_prev = FALSE;
	while (TRUE)
	{
		// width increase check (must happen before each code is read)
		if (next_code >= ((((t_u32)1 << b.width)) - LZW_EARLYCHANGE) && b.width < width_max)
		{
			LZW_Bits_Transition(&b);
			b.width += 1;
		}
		if (!LZW_Bits_Get(&b, data, size, &code))
		{
#if LZW_HAS_END
			if CCCERROR((TRUE), ERROR_ILLEGALBYTES,
				"invalid LZW data: stream is truncated (its \"end\" code is missing)")
			{
				Memory_Deallocate(lengths);
				return (FALSE);
			}
#else
			break; // normal end of stream, for formats without an "end" code
#endif
		}
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
		if (has_clear && code == LZW_CODE_CLEAR)
#else
		if (code == LZW_CODE_CLEAR)
#endif
		{
			LZW_Bits_Transition(&b);
			b.width = LZW_WIDTH_INIT;
			next_code = code_first;
			have_prev = FALSE;
			continue;
		}
#if LZW_HAS_END
		if (code == LZW_CODE_END)
			break; // NOTE: any bytes remaining after this point are ignored
#endif
		if (!have_prev)
		{	// the first code (after the stream start, or after any "clear" code) must be a literal
			if CCCERROR((code >= 256), ERROR_ILLEGALBYTES,
				"invalid LZW data: the first code after a dictionary reset must be a literal")
			{
				Memory_Deallocate(lengths);
				return (FALSE);
			}
			entry_len = 1;
		}
		else if (code < 256)
			entry_len = 1;
		else if (code >= code_first && code < next_code)
			entry_len = lengths[code];
		else if (code == next_code && next_code < codes_max)
			entry_len = prev_len + 1; // the special "KwKwK" case: a reference to the entry being defined
		else
		{
			if CCCERROR((TRUE), ERROR_ILLEGALBYTES,
				"invalid LZW data: encountered a code which is not yet present in the dictionary")
			{
				Memory_Deallocate(lengths);
				return (FALSE);
			}
		}
		if (have_prev && next_code < codes_max)
		{	// add a dictionary entry: the previous entry, extended by one byte
			lengths[next_code] = prev_len + 1;
			next_code += 1;
		}
		if CCCERROR((produced > (t_size)-1 - entry_len), ERROR_LENGTH2LARGE,
			"invalid LZW data: total decompressed size is too large to be represented")
		{
			Memory_Deallocate(lengths);
			return (FALSE);
		}
		produced += entry_len;
		prev_len = entry_len;
		have_prev = TRUE;
	}
	Memory_Deallocate(lengths);
	*out_size = produced;
	return (TRUE);
}



t_size	LZW_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!LZW_Parse(&result, data, size))
		return (SIZE_ERROR);
	return (result);
}



/*============================================================================*\
||                                Decompression                               ||
\*============================================================================*/

t_u8*	LZW_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_lzw_bits	b = {0};
	t_u8*	result;
	t_size	result_size;
	t_size*	entry_pos;	//!< for each dictionary code: the position (in `result`) of that entry's first occurrence
	t_u32*	entry_len;	//!< for each dictionary code: the length of that entry
	t_size	dest_i;
	t_size	cur_pos;
	t_u32	cur_len;
	t_size	prev_pos;
	t_u32	prev_len;
	t_u32	next_code;
	t_u32	code;
	t_bool	have_prev;
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
	t_uint	width_max;
	t_u32	codes_max;
	t_u32	code_first;
	t_bool	has_clear;
#else
	t_uint const	width_max = LZW_MAXBITS;
	t_u32 const		codes_max = LZW_CODES_MAX;
	t_u32 const		code_first = LZW_CODE_FIRST;
#endif

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!LZW_Parse(&result_size, data, size))
		return (NULL);
	result = (t_u8*)Memory_Allocate(result_size ? result_size : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
	width_max = (data[2] & 0x1F);
	has_clear = ((data[2] & 0x80) != 0);
	codes_max = ((t_u32)1 << width_max);
	code_first = (has_clear ? 257 : 256);
	b.pos = LZW_HEADER_SIZE;
#endif
	entry_pos = (t_size*)Memory_Allocate(codes_max * (sizeof(t_size) + sizeof(t_u32)));
	if CCCERROR((entry_pos == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(result);
		return (NULL);
	}
	entry_len = (t_u32*)(entry_pos + codes_max);
	// NOTE: the stream was fully validated by LZW_Parse() above, so it can be trusted here
	b.width = LZW_WIDTH_INIT;
	next_code = code_first;
	dest_i = 0;
	prev_pos = 0;
	prev_len = 0;
	have_prev = FALSE;
	while (TRUE)
	{
		if (next_code >= ((((t_u32)1 << b.width)) - LZW_EARLYCHANGE) && b.width < width_max)
		{
			LZW_Bits_Transition(&b);
			b.width += 1;
		}
		if (!LZW_Bits_Get(&b, data, size, &code))
			break;
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
		if (has_clear && code == LZW_CODE_CLEAR)
#else
		if (code == LZW_CODE_CLEAR)
#endif
		{
			LZW_Bits_Transition(&b);
			b.width = LZW_WIDTH_INIT;
			next_code = code_first;
			have_prev = FALSE;
			continue;
		}
#if LZW_HAS_END
		if (code == LZW_CODE_END)
			break;
#endif
		if (!have_prev)
		{	// first code after a dictionary reset: always a single literal byte
			result[dest_i] = (t_u8)code;
			prev_pos = dest_i;
			prev_len = 1;
			dest_i += 1;
			have_prev = TRUE;
			continue;
		}
		if (code < 256)
		{	// literal byte
			result[dest_i] = (t_u8)code;
			cur_pos = dest_i;
			cur_len = 1;
			dest_i += 1;
		}
		else if (code == next_code)
		{	// the special "KwKwK" case: previous entry, followed by its own first byte
			Memory_Copy(result + dest_i, result + prev_pos, prev_len);
			result[dest_i + prev_len] = result[prev_pos];
			cur_pos = dest_i;
			cur_len = prev_len + 1;
			dest_i += cur_len;
		}
		else
		{	// existing dictionary entry: its bytes are already present in the output, simply copy them
			cur_len = entry_len[code];
			Memory_Copy(result + dest_i, result + entry_pos[code], cur_len);
			cur_pos = dest_i;
			dest_i += cur_len;
		}
		if (next_code < codes_max)
		{	// add a dictionary entry: the previous entry, extended by one byte
			// (that byte sequence starts exactly where the previous entry was written)
			entry_pos[next_code] = prev_pos;
			entry_len[next_code] = prev_len + 1;
			next_code += 1;
		}
		prev_pos = cur_pos;
		prev_len = cur_len;
	}
	Memory_Deallocate(entry_pos);
	if (dest_size)
		*dest_size = result_size;
	return (result);
}



/*============================================================================*\
||                                 Compression                                ||
\*============================================================================*/

//! Writes a single code, and performs the width increase check (which must happen after each written code)
static
void	LZW_Compress_Emit(s_lzw_bits* b, t_u8* dest, t_u32 code, t_u32 next_code)
{
	LZW_Bits_Put(b, dest, code);
	if (next_code >= ((((t_u32)1 << b->width)) - LZW_EARLYCHANGE) && b->width < LZW_MAXBITS)
	{
		LZW_Bits_Transition(b);
		b->width += 1;
	}
}

t_u8*	LZW_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_lzw_bits	b = {0};
	t_u8*	result;
	t_u32*	hash_keys;	//!< hash bucket keys: `((prefix_code << 8) | byte) + 1`, or `0` if the bucket is empty
	t_u32*	hash_vals;	//!< hash bucket values: the dictionary code for that (prefix, byte) pair
	t_size	dest_i;
	t_size	src_i;
	t_u32	next_code;
	t_u32	ent;
	t_u32	key;
	t_u32	hash;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_Allocate(LZW_COMPRESS_MAXSIZE(size));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	hash_keys = (t_u32*)Memory_Allocate(LZW_HASHSIZE * 2 * sizeof(t_u32));
	if CCCERROR((hash_keys == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(result);
		return (NULL);
	}
	hash_vals = hash_keys + LZW_HASHSIZE;
	Memory_Set(hash_keys, 0, LZW_HASHSIZE * sizeof(t_u32));
	b.width = LZW_WIDTH_INIT;
	next_code = LZW_CODE_FIRST;
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
	result[0] = LZW_HEADER_MAGIC_0;
	result[1] = LZW_HEADER_MAGIC_1;
	result[2] = (LZW_MAXBITS | 0x80); // `0x80` is the "block mode" flag (ie: the "clear" code is in use)
	b.pos = LZW_HEADER_SIZE;
#else
	LZW_Compress_Emit(&b, result, LZW_CODE_CLEAR, next_code); // these formats always begin with a "clear" code
#endif
	if (size > 0)
	{
		ent = data[0];
		for (src_i = 1; src_i < size; ++src_i)
		{
			key = (((ent << 8) | data[src_i]) + 1);
			hash = ((key * 2654435761u) >> (32 - LZW_HASHBITS));
			while (hash_keys[hash] != 0 && hash_keys[hash] != key)
				hash = ((hash + 1) & (LZW_HASHSIZE - 1));
			if (hash_keys[hash] == key)
			{	// the current sequence, extended by this byte, is in the dictionary: keep extending
				ent = hash_vals[hash];
				continue;
			}
			// otherwise: emit the code for the current sequence, and add the extended one to the dictionary
			LZW_Compress_Emit(&b, result, ent, next_code);
			if (next_code < LZW_CLEAR_THRESHOLD)
			{
				hash_keys[hash] = key;
				hash_vals[hash] = next_code;
				next_code += 1;
			}
			else
			{	// the dictionary is full: emit a "clear" code, and reset the dictionary
				LZW_Compress_Emit(&b, result, LZW_CODE_CLEAR, next_code);
				LZW_Bits_Transition(&b);
				b.width = LZW_WIDTH_INIT;
				Memory_Set(hash_keys, 0, LZW_HASHSIZE * sizeof(t_u32));
				next_code = LZW_CODE_FIRST;
			}
			ent = data[src_i];
		}
		LZW_Compress_Emit(&b, result, ent, next_code);
	}
#if LZW_HAS_END
	LZW_Compress_Emit(&b, result, LZW_CODE_END, next_code);
#endif
	dest_i = LZW_Bits_Finish(&b, result);
	Memory_Deallocate(hash_keys);
	// shrink the buffer to fit the actual compressed size
	if (dest_i > 0 && dest_i < LZW_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}
