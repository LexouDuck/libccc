
#include "libccc/memory.h"
#include "libccc/compress/lz77.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	See "libccc/compress/lz77.h" for a description of the compressed stream
**	format(s), which can be selected via `LIBCONFIG_COMPRESS_LZ77_FORMAT`.
**
**	The compressor uses a "hash chain" match-finding strategy (like zlib):
**	- a hash is computed from the `LZ77_MATCHLENGTH_MIN` bytes at each position
**	- `hash_head[hash]` stores the most recent position with that hash
**	- `hash_prev[position % LZ77_WINDOW_SIZE]` chains back to the previous
**		position which had the same hash, forming a linked list of candidates
**	The compressor is greedy: at each position, it takes the longest match
**	found among the (at most `LZ77_COMPRESS_MAXCHAIN`) most recent candidates.
*/

//! The maximum amount of match candidates to check, at each position (speed/ratio tradeoff)
#define LZ77_COMPRESS_MAXCHAIN	(128)

//! The amount of hash buckets used by the compressor's match-finder
#define LZ77_COMPRESS_HASHSIZE	(0x1000)

//! Local convenience macro: sentinel value, and alias for the `t_size` max value
#define LZ77_NONE	((t_size)-1)



/*============================================================================*\
||                       Back-reference token read/write                      ||
\*============================================================================*/

//! Writes a single back-reference token to `dest`, returns the amount of bytes written
static
t_size	LZ77_Token_Write(t_u8* dest, t_size length, t_size distance)
{
	t_size	disp = distance - 1;
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_NDS)
	if (length >= 0x111)
	{	// 4-byte token: `0001LLLL llllllll llllDDDD dddddddd`, stores `length - 0x111`
		t_size	len = length - 0x111;
		dest[0] = (t_u8)(0x10 | (len >> 12));
		dest[1] = (t_u8)(len >> 4);
		dest[2] = (t_u8)((len << 4) | (disp >> 8));
		dest[3] = (t_u8)(disp);
		return (4);
	}
	if (length >= 0x11)
	{	// 3-byte token: `0000LLLL llllDDDD dddddddd`, stores `length - 0x11`
		t_size	len = length - 0x11;
		dest[0] = (t_u8)(len >> 4);
		dest[1] = (t_u8)((len << 4) | (disp >> 8));
		dest[2] = (t_u8)(disp);
		return (3);
	}
	// 2-byte token: `LLLLDDDD dddddddd`, stores `length - 1` (so `LLLL >= 2`)
	dest[0] = (t_u8)(((length - 1) << 4) | (disp >> 8));
	dest[1] = (t_u8)(disp);
	return (2);
#else
	// 2-byte token: `LLLLDDDD dddddddd`, stores `length - 3`
	dest[0] = (t_u8)(((length - 3) << 4) | (disp >> 8));
	dest[1] = (t_u8)(disp);
	return (2);
#endif
}

//! Reads a single back-reference token from `data + src_i`, returns the amount of bytes read (or `0` if the token is truncated)
static
t_size	LZ77_Token_Read(t_size* out_length, t_size* out_distance, t_u8 const* data, t_size size, t_size src_i)
{
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_NDS)
	t_u8	indicator;
	if (src_i + 2 > size)
		return (0);
	indicator = (data[src_i] >> 4);
	if (indicator >= 2)
	{	// 2-byte token
		*out_length   = (t_size)indicator + 1;
		*out_distance = ((((t_size)data[src_i] & 0xF) << 8) | data[src_i + 1]) + 1;
		return (2);
	}
	if (indicator == 0)
	{	// 3-byte token
		if (src_i + 3 > size)
			return (0);
		*out_length   = ((((t_size)data[src_i] & 0xF) << 4) | (data[src_i + 1] >> 4)) + 0x11;
		*out_distance = ((((t_size)data[src_i + 1] & 0xF) << 8) | data[src_i + 2]) + 1;
		return (3);
	}
	// 4-byte token
	if (src_i + 4 > size)
		return (0);
	*out_length   = ((((t_size)data[src_i] & 0xF) << 12) | ((t_size)data[src_i + 1] << 4) | (data[src_i + 2] >> 4)) + 0x111;
	*out_distance = ((((t_size)data[src_i + 2] & 0xF) << 8) | data[src_i + 3]) + 1;
	return (4);
#else
	if (src_i + 2 > size)
		return (0);
	*out_length   = (t_size)(data[src_i] >> 4) + 3;
	*out_distance = ((((t_size)data[src_i] & 0xF) << 8) | data[src_i + 1]) + 1;
	return (2);
#endif
}



/*============================================================================*\
||                          Stream parsing/validation                         ||
\*============================================================================*/

//! Parses LZ77-compressed data, validating it, and computing its decompressed size
static
t_bool	LZ77_Parse(t_size* out_size, t_u8 const* data, t_size size)
{
	t_size	produced;
	t_size	src_i;
	t_size	length;
	t_size	distance;
	t_size	token_size;
	t_u8	flags;
	t_uint	block;

	*out_size = 0;
	produced = 0;
	src_i = 0;
#if (LZ77_HEADER_SIZE > 0)
	t_size	expected;
	if CCCERROR((size < LZ77_HEADER_SIZE), ERROR_ILLEGALBYTES,
		"invalid LZ77 data: too short to contain the stream header")
		return (FALSE);
	if CCCERROR((data[0] != LZ77_HEADER_MAGIC), ERROR_ILLEGALBYTES,
		"invalid LZ77 data: stream does not begin with the expected magic byte")
		return (FALSE);
	expected = ((t_size)data[1] | ((t_size)data[2] << 8) | ((t_size)data[3] << 16));
	src_i = LZ77_HEADER_SIZE;
#define LZ77_PARSE_DONE	(produced >= expected)
#else
#define LZ77_PARSE_DONE	(src_i >= size)
#endif
	while (!LZ77_PARSE_DONE)
	{
		if CCCERROR((src_i >= size), ERROR_ILLEGALBYTES,
			"invalid LZ77 data: stream is truncated")
			return (FALSE);
		flags = data[src_i++];
		for (block = 0; block < 8 && !LZ77_PARSE_DONE; ++block)
		{
			if (flags & (0x80 >> block)) // back-reference token
			{
				token_size = LZ77_Token_Read(&length, &distance, data, size, src_i);
				if CCCERROR((token_size == 0), ERROR_ILLEGALBYTES,
					"invalid LZ77 data: back-reference token is truncated")
					return (FALSE);
				if CCCERROR((distance > produced), ERROR_ILLEGALBYTES,
					"invalid LZ77 data: back-reference distance points before the start of the data")
					return (FALSE);
				src_i += token_size;
				produced += length;
			}
			else // literal byte
			{
				if CCCERROR((src_i >= size), ERROR_ILLEGALBYTES,
					"invalid LZ77 data: literal byte is missing (stream is truncated)")
					return (FALSE);
				src_i += 1;
				produced += 1;
			}
		}
	}
#if (LZ77_HEADER_SIZE > 0)
	if CCCERROR((produced != expected), ERROR_ILLEGALBYTES,
		"invalid LZ77 data: stream decompresses to more data than its header announces")
		return (FALSE);
	// NOTE: any bytes remaining after this point are considered padding, and are ignored
#endif
#undef LZ77_PARSE_DONE
	*out_size = produced;
	return (TRUE);
}



t_size	LZ77_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!LZ77_Parse(&result, data, size))
		return (SIZE_ERROR);
	return (result);
}



/*============================================================================*\
||                                Decompression                               ||
\*============================================================================*/

t_u8*	LZ77_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	result_size;
	t_size	dest_i;
	t_size	src_i;
	t_size	length;
	t_size	distance;
	t_u8	flags;
	t_uint	block;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!LZ77_Parse(&result_size, data, size))
		return (NULL);
	result = (t_u8*)Memory_Allocate(result_size ? result_size : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	// NOTE: the stream was fully validated by LZ77_Parse() above, so it can be trusted here
	length = 0;
	distance = 0;
	dest_i = 0;
	src_i = LZ77_HEADER_SIZE;
	while (dest_i < result_size)
	{
		flags = data[src_i++];
		for (block = 0; block < 8 && dest_i < result_size; ++block)
		{
			if (flags & (0x80 >> block)) // back-reference token
			{
				src_i += LZ77_Token_Read(&length, &distance, data, size, src_i);
				// copy byte-per-byte: back-references can overlap with the data they produce
				while (length--)
				{
					result[dest_i] = result[dest_i - distance];
					dest_i += 1;
				}
			}
			else // literal byte
			{
				result[dest_i++] = data[src_i++];
			}
		}
	}
	if (dest_size)
		*dest_size = result_size;
	return (result);
}



/*============================================================================*\
||                                 Compression                                ||
\*============================================================================*/

//! Computes the match-finder hash for the `LZ77_MATCHLENGTH_MIN` bytes at `data`
static
t_u32	LZ77_Compress_Hash(t_u8 const* data)
{
	t_u32	value = (((t_u32)data[0] << 16) | ((t_u32)data[1] << 8) | (t_u32)data[2]);
	return ((value * 2654435761u) >> 20) & (LZ77_COMPRESS_HASHSIZE - 1);
}

//! Inserts the given position `pos` into the match-finder hash chains
static
void	LZ77_Compress_Insert(t_size* hash_head, t_size* hash_prev, t_u8 const* data, t_size size, t_size pos)
{
	t_u32	hash;

	if (pos + LZ77_MATCHLENGTH_MIN > size)
		return;
	hash = LZ77_Compress_Hash(data + pos);
	hash_prev[pos & (LZ77_WINDOW_SIZE - 1)] = hash_head[hash];
	hash_head[hash] = pos;
}

//! Finds the longest match for the data at `pos`, returns its length (`0` if no acceptable match was found)
static
t_size	LZ77_Compress_FindMatch(t_size* out_distance,
	t_size const* hash_head, t_size const* hash_prev,
	t_u8 const* data, t_size size, t_size pos)
{
	t_size	best_length = 0;
	t_size	length_max;
	t_size	length;
	t_size	candidate;
	t_size	limit;
	t_uint	chain;

	if (pos + LZ77_MATCHLENGTH_MIN > size)
		return (0);
	length_max = size - pos;
	if (length_max > LZ77_MATCHLENGTH_MAX)
		length_max = LZ77_MATCHLENGTH_MAX;
	limit = (pos > LZ77_WINDOW_SIZE) ? (pos - LZ77_WINDOW_SIZE) : 0;
	candidate = hash_head[LZ77_Compress_Hash(data + pos)];
	for (chain = 0; chain < LZ77_COMPRESS_MAXCHAIN; ++chain)
	{
		t_size	next;
		if (candidate == LZ77_NONE || candidate < limit)
			break;
		if (pos - candidate >= LIBCONFIG_COMPRESS_LZ77_MINDISTANCE &&
			data[candidate + best_length] == data[pos + best_length])
		{
			length = 0;
			while (length < length_max && data[candidate + length] == data[pos + length])
				length += 1;
			if (length > best_length)
			{
				best_length = length;
				*out_distance = pos - candidate;
				if (best_length == length_max)
					break;
			}
		}
		next = hash_prev[candidate & (LZ77_WINDOW_SIZE - 1)];
		if (next >= candidate)
			break; // guards against stale ring-buffer entries (ensures chain positions strictly decrease)
		candidate = next;
	}
	return (best_length >= LZ77_MATCHLENGTH_MIN ? best_length : 0);
}

t_u8*	LZ77_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size*	hash_head;
	t_size*	hash_prev;
	t_size	dest_i;
	t_size	src_i;
	t_size	flags_i;
	t_size	length;
	t_size	distance;
	t_u8	flags;
	t_uint	block;
	t_uint	i;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if CCCERROR((size > LZ77_SIZE_MAX), ERROR_LENGTH2LARGE,
		"data given is too large to be compressed with the current LZ77 format")
		return (NULL);
	result = (t_u8*)Memory_Allocate(size ? LZ77_COMPRESS_MAXSIZE(size) : LZ77_COMPRESS_MAXSIZE(0) + 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	hash_head = (t_size*)Memory_Allocate((LZ77_COMPRESS_HASHSIZE + LZ77_WINDOW_SIZE) * sizeof(t_size));
	if CCCERROR((hash_head == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(result);
		return (NULL);
	}
	hash_prev = hash_head + LZ77_COMPRESS_HASHSIZE;
	for (t_size h = 0; h < LZ77_COMPRESS_HASHSIZE; ++h)
		hash_head[h] = LZ77_NONE;
	dest_i = 0;
#if (LZ77_HEADER_SIZE > 0)
	result[dest_i++] = LZ77_HEADER_MAGIC;
	result[dest_i++] = (t_u8)(size);
	result[dest_i++] = (t_u8)(size >> 8);
	result[dest_i++] = (t_u8)(size >> 16);
#endif
	src_i = 0;
	while (src_i < size)
	{
		flags = 0;
		flags_i = dest_i++; // reserve the "flags" byte for this group (written below, once known)
		for (block = 0; block < 8 && src_i < size; ++block)
		{
			length = LZ77_Compress_FindMatch(&distance, hash_head, hash_prev, data, size, src_i);
			if (length > 0)
			{
				flags |= (0x80 >> block);
				dest_i += LZ77_Token_Write(result + dest_i, length, distance);
				for (i = 0; i < length; ++i)
					LZ77_Compress_Insert(hash_head, hash_prev, data, size, src_i + i);
				src_i += length;
			}
			else
			{
				result[dest_i++] = data[src_i];
				LZ77_Compress_Insert(hash_head, hash_prev, data, size, src_i);
				src_i += 1;
			}
		}
		result[flags_i] = flags;
	}
	Memory_Deallocate(hash_head);
#if (LZ77_HEADER_SIZE > 0)
	while (dest_i % 4 != 0) // zero-pad the compressed stream to a multiple of 4 bytes in size
		result[dest_i++] = 0x00;
#endif
	// shrink the buffer to fit the actual compressed size
	if (dest_i > 0 && dest_i < LZ77_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}
