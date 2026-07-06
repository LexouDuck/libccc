
#include "libccc/memory.h"
#include "libccc/compress/lzss.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	See "libccc/compress/lzss.h" for a description of the compressed stream
**	format, which matches the classic Okumura `LZSS.C` reference program:
**	groups of 8 items, preceded by a flag byte (least-significant-bit first,
**	`1` = literal byte, `0` = 2-byte match item), where match items store an
**	*absolute* 12-bit position within the 4096-byte ring buffer window
**	(which is initially filled with LIBCONFIG_COMPRESS_LZSS_FILLBYTE, and
**	written starting from ring position 4096 - 18), and a 4-bit length
**	(the actual match length, minus 3).
*/

//! The ring buffer position at which the first input byte is written (like Okumura's `r = N - F`)
#define LZSS_STARTPOS	(LZSS_WINDOW - LZSS_MATCHLENGTH_MAX)

//! The maximum backwards distance for a match
/*!
**	Matches never reference the `LZSS_MATCHLENGTH_MAX - 1` most distant ring
**	buffer positions, since those may be (partially) overwritten while the
**	match is being copied by the decompressor - the classic Okumura encoder
**	has this same effective limit (its binary trees hold `N - F` strings).
*/
#define LZSS_MAXDISTANCE	(LZSS_WINDOW - LZSS_MATCHLENGTH_MAX)

//! The amount of hash chain heads used by the compressor's match-finder
#define LZSS_HASHSIZE	(1 << 13)

//! The maximum amount of hash chain entries examined for one match search
#define LZSS_MAXCHAIN	(128)

//! Computes the match-finder hash of the 3 bytes at `ptr`
static
t_uint	LZSS_Hash(t_u8 const* ptr)
{
	return (((t_uint)ptr[0] << 10) ^ ((t_uint)ptr[1] << 5) ^ (t_uint)ptr[2]) & (LZSS_HASHSIZE - 1);
}



t_u8*	LZSS_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8	group[1 + 8 * 2];
	t_u8*	result;
	t_size*	head;
	t_size*	prev;
	t_size	dest_i;
	t_size	i;
	t_size	j;
	t_size	limit;
	t_size	best_pos;
	t_uint	best_len;
	t_uint	group_len;
	t_uint	group_items;
	t_uint	maxlen;
	t_uint	len;
	t_uint	chain;
	t_uint	hash;
	t_uint	rpos;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_Allocate(size ? LZSS_COMPRESS_MAXSIZE(size) : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	head = (t_size*)Memory_Allocate((LZSS_HASHSIZE + LZSS_WINDOW) * sizeof(t_size));
	if CCCERROR((head == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(result);
		return (NULL);
	}
	prev = (head + LZSS_HASHSIZE);
	for (i = 0; i < LZSS_HASHSIZE; ++i)
		head[i] = SIZE_MAX;
	dest_i = 0;
	group[0] = 0;
	group_len = 1;
	group_items = 0;
	i = 0;
	while (i < size)
	{
		// find the longest match for the bytes at `i`, in the sliding window behind it
		best_len = 0;
		best_pos = 0;
		maxlen = (size - i < LZSS_MATCHLENGTH_MAX) ? (t_uint)(size - i) : LZSS_MATCHLENGTH_MAX;
		if (maxlen >= LZSS_MATCHLENGTH_MIN)
		{
			limit = (i > LZSS_MAXDISTANCE) ? (i - LZSS_MAXDISTANCE) : 0;
			j = head[LZSS_Hash(data + i)];
			chain = LZSS_MAXCHAIN;
			while (j != SIZE_MAX && j >= limit && j < i && chain-- > 0)
			{
				len = 0;
				while (len < maxlen && data[j + len] == data[i + len])
					len += 1;
				if (len > best_len)
				{
					best_len = len;
					best_pos = j;
					if (len == maxlen)
						break;
				}
				j = prev[j % LZSS_WINDOW];
			}
		}
		if (best_len >= LZSS_MATCHLENGTH_MIN)
		{	// emit a match item: the *ring buffer* position where the match starts, and its length
			rpos = (t_uint)((LZSS_STARTPOS + best_pos) % LZSS_WINDOW);
			group[group_len++] = (t_u8)(rpos & 0xFF);
			group[group_len++] = (t_u8)(((rpos >> 4) & 0xF0) | (best_len - LZSS_MATCHLENGTH_MIN));
		}
		else
		{	// emit a literal item
			group[0] |= (t_u8)(1 << group_items);
			group[group_len++] = data[i];
			best_len = 1;
		}
		// insert every covered position into the match-finder hash chains
		for (len = 0; len < best_len; ++len, ++i)
		{
			if (size - i >= LZSS_MATCHLENGTH_MIN)
			{
				hash = LZSS_Hash(data + i);
				prev[i % LZSS_WINDOW] = head[hash];
				head[hash] = i;
			}
		}
		if (++group_items == 8)
		{	// the group is full: flush its flag byte and items to the output
			Memory_Copy(result + dest_i, group, group_len);
			dest_i += group_len;
			group[0] = 0;
			group_len = 1;
			group_items = 0;
		}
	}
	if (group_items > 0)
	{
		Memory_Copy(result + dest_i, group, group_len);
		dest_i += group_len;
	}
	Memory_Deallocate(head);
	// shrink the buffer to fit the actual compressed size
	if (size && dest_i < (t_size)LZSS_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i ? dest_i : 1);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}



//! Parses (and validates) an LZSS stream: computes its decompressed size, and optionally decodes it
/*!
**	If `dest` is `NULL`, this only computes the size; otherwise, it also
**	writes the decoded bytes to `dest` (which must be large enough).
*/
static
t_bool	LZSS_Parse(t_size* out_size, t_u8* dest, t_u8 const* data, t_size size)
{
	t_u8	window[LZSS_WINDOW];
	t_size	produced;
	t_size	i;
	t_uint	rpos;
	t_uint	flags;
	t_uint	item;
	t_uint	pos;
	t_uint	len;
	t_uint	k;
	t_u8	c;

	*out_size = 0;
	Memory_Set(window, LIBCONFIG_COMPRESS_LZSS_FILLBYTE, LZSS_WINDOW);
	rpos = LZSS_STARTPOS;
	produced = 0;
	i = 0;
	while (i < size)
	{
		flags = data[i++];
		for (item = 0; item < 8 && i < size; ++item)
		{
			// NOTE: `produced` cannot overflow `t_size` here: it grows by at
			// most 18 bytes per 2 input bytes, and the result buffer of that
			// size must be allocatable, so `SIZE_MAX` can never be approached
			if (flags & (1u << item))
			{	// literal item: a single byte, stored as-is
				c = data[i++];
				if (dest != NULL)
					dest[produced] = c;
				produced += 1;
				window[rpos] = c;
				rpos = ((rpos + 1) % LZSS_WINDOW);
			}
			else
			{	// match item: a 12-bit ring buffer position, and a 4-bit length
				if CCCERROR((size - i < 2), ERROR_ILLEGALBYTES,
					"invalid lzss data: stream ends in the middle of a match item")
					return (FALSE);
				pos = (data[i] | (((t_uint)data[i + 1] & 0xF0) << 4));
				len = ((data[i + 1] & 0x0F) + LZSS_MATCHLENGTH_MIN);
				i += 2;
				for (k = 0; k < len; ++k)
				{
					c = window[(pos + k) % LZSS_WINDOW];
					if (dest != NULL)
						dest[produced] = c;
					produced += 1;
					window[rpos] = c;
					rpos = ((rpos + 1) % LZSS_WINDOW);
				}
			}
		}
	}
	*out_size = produced;
	return (TRUE);
}

t_size	LZSS_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!LZSS_Parse(&result, NULL, data, size))
		return (SIZE_ERROR);
	return (result);
}

t_u8*	LZSS_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	result_size;
	t_size	check;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!LZSS_Parse(&result_size, NULL, data, size))
		return (NULL);
	result = (t_u8*)Memory_Allocate(result_size ? result_size : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	LZSS_Parse(&check, result, data, size); // already validated above, cannot fail
	if (dest_size)
		*dest_size = result_size;
	return (result);
}
