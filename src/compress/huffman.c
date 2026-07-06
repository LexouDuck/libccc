
#include "libccc/memory.h"
#include "libccc/compress/huffman.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	See "libccc/compress/huffman.h" for a description of the compressed stream
**	format(s), which can be selected via `LIBCONFIG_COMPRESS_HUFFMAN_FORMAT`.
**
**	Both formats use canonical Huffman codes, packed most-significant-bit-first,
**	but with opposite canonical ordering conventions:
**	- HUFFMAN_FORMAT_RAW assigns codes in increasing order of code length
**		(and of symbol value, within one length), like DEFLATE (RFC 1951)
**	- HUFFMAN_FORMAT_PACK gives the numerically smallest codes of each tree
**		level to the internal nodes, and the largest to the leaves, with the
**		"end of block" symbol always being the all-ones code of the deepest
**		level (this matches the historic UNIX `pack` command, whose output
**		can still be decompressed by `gzip` today)
*/

//! The amount of tree nodes needed to build a Huffman tree over the full alphabet
#define HUFFMAN_TREENODES	(HUFFMAN_SYMBOLS * 2 - 1)

//! The maximum tree depth accepted by the HUFFMAN_FORMAT_PACK *de*compressor
/*!
**	The libccc compressor never produces codes longer than HUFFMAN_MAXLENGTH (15),
**	but the historic `pack` command could produce trees up to 24 levels deep,
**	so the decompressor accepts the full range, for interoperability.
*/
#define HUFFMAN_PACK_MAXLEVEL	(24)



/*============================================================================*\
||                                   Bit i/o                                  ||
\*============================================================================*/

//! Holds the state of a most-significant-bit-first bit-stream writer
typedef struct huffman_bitwriter
{
	t_size	pos;	//!< current byte position
	t_u32	acc;	//!< bit accumulator
	t_uint	bits;	//!< amount of pending bits in `acc`
}	s_huffman_bitwriter;

//! Writes the `length` lowest bits of `code` (most-significant-bit first)
static
void	HUFFMAN_BitWriter_Put(s_huffman_bitwriter* b, t_u8* dest, t_u32 code, t_uint length)
{
	b->acc = ((b->acc << length) | code);
	b->bits += length;
	while (b->bits >= 8)
	{
		b->bits -= 8;
		dest[b->pos++] = (t_u8)(b->acc >> b->bits);
	}
}

//! Flushes any pending bits (zero-padded), and returns the total amount of bytes written
static
t_size	HUFFMAN_BitWriter_Finish(s_huffman_bitwriter* b, t_u8* dest)
{
	if (b->bits > 0)
		dest[b->pos++] = (t_u8)(b->acc << (8 - b->bits));
	return (b->pos);
}

//! Holds the state of a most-significant-bit-first bit-stream reader
typedef struct huffman_bitreader
{
	t_size	pos;	//!< current byte position
	t_uint	bit;	//!< current bit position within the current byte (0 = most significant)
}	s_huffman_bitreader;

//! Reads a single bit, returns `FALSE` if there is no input left
static
t_bool	HUFFMAN_BitReader_Get(s_huffman_bitreader* b, t_u8 const* data, t_size size, t_uint* out_bit)
{
	if (b->pos >= size)
		return (FALSE);
	*out_bit = ((data[b->pos] >> (7 - b->bit)) & 1);
	if (++b->bit == 8)
	{
		b->bit = 0;
		b->pos += 1;
	}
	return (TRUE);
}



/*============================================================================*\
||                        Code length table construction                      ||
\*============================================================================*/

//! Swaps two entries of a binary min-heap of tree node indices, ordered by node frequency
static
void	HUFFMAN_Heap_Sift(t_u16* heap, t_uint heap_size, t_u64 const* freq, t_uint i)
{
	t_uint	child;
	t_u16	tmp;

	while (TRUE)
	{
		child = (i * 2 + 1);
		if (child >= heap_size)
			break;
		if (child + 1 < heap_size && (freq[heap[child + 1]] < freq[heap[child]] ||
			(freq[heap[child + 1]] == freq[heap[child]] && heap[child + 1] < heap[child])))
			child += 1;
		if (freq[heap[i]] < freq[heap[child]] ||
			(freq[heap[i]] == freq[heap[child]] && heap[i] < heap[child]))
			break;
		tmp = heap[i];	heap[i] = heap[child];	heap[child] = tmp;
		i = child;
	}
}

//! Computes optimal, length-limited Huffman code lengths for the given symbol frequencies
/*!
**	This builds a classic Huffman tree (using a binary min-heap), measures the
**	depth of each leaf, and then, if any leaf is deeper than #HUFFMAN_MAXLENGTH,
**	adjusts the length counts to fit (using the same technique as zlib: moving
**	overflowed leaves up, at the cost of moving one shallower leaf down), and
**	finally distributes the lengths among the symbols (rarest symbols getting
**	the longest codes), which preserves optimality.
*/
static
void	HUFFMAN_BuildLengths(t_u8* lengths, t_u64 const* symbol_freq)
{
	t_u64	freq[HUFFMAN_TREENODES];
	t_u16	parent[HUFFMAN_TREENODES];
	t_u16	heap[HUFFMAN_SYMBOLS + 1];
	t_u16	sorted[HUFFMAN_SYMBOLS];
	t_uint	bl_count[HUFFMAN_MAXLENGTH + 1];
	t_uint	heap_size;
	t_uint	nodes;
	t_uint	used;
	t_uint	symbol;
	t_uint	depth;
	t_uint	node;
	t_uint	i;
	t_sint	overflow;
	t_u16	a;
	t_u16	b;

	Memory_Set(lengths, 0, HUFFMAN_SYMBOLS);
	// build a min-heap containing every used symbol (leaf node index = symbol value)
	heap_size = 0;
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		freq[symbol] = symbol_freq[symbol];
		if (symbol_freq[symbol] > 0)
			heap[heap_size++] = (t_u16)symbol;
	}
	used = heap_size;
	if (used == 1)
	{	// degenerate case: a single used symbol still needs a 1-bit code
		lengths[heap[0]] = 1;
		return;
	}
	for (i = heap_size / 2; i-- > 0;)
		HUFFMAN_Heap_Sift(heap, heap_size, freq, i);
	// classic Huffman: repeatedly merge the two least frequent nodes
	nodes = HUFFMAN_SYMBOLS;
	while (heap_size > 1)
	{
		a = heap[0];
		heap[0] = heap[--heap_size];
		HUFFMAN_Heap_Sift(heap, heap_size, freq, 0);
		b = heap[0];
		freq[nodes] = freq[a] + freq[b];
		parent[a] = (t_u16)nodes;
		parent[b] = (t_u16)nodes;
		heap[0] = (t_u16)nodes;
		HUFFMAN_Heap_Sift(heap, heap_size, freq, 0);
		nodes += 1;
	}
	// measure the depth of each leaf, counting how many codes exist of each length
	// (leaves deeper than HUFFMAN_MAXLENGTH are counted as overflow, to fix below)
	Memory_Set(bl_count, 0, sizeof(bl_count));
	overflow = 0;
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		if (symbol_freq[symbol] == 0)
			continue;
		depth = 0;
		node = symbol;
		while (node != nodes - 1)
		{
			node = parent[node];
			depth += 1;
		}
		if (depth > HUFFMAN_MAXLENGTH)
		{
			depth = HUFFMAN_MAXLENGTH;
			overflow += 1;
		}
		bl_count[depth] += 1;
	}
	while (overflow > 0)
	{	// move one leaf from the deepest non-full length down by one, freeing
		// a slot at that length's sibling subtree for two overflowed leaves
		i = HUFFMAN_MAXLENGTH - 1;
		while (bl_count[i] == 0)
			i -= 1;
		bl_count[i] -= 1;
		bl_count[i + 1] += 2;
		bl_count[HUFFMAN_MAXLENGTH] -= 1;
		overflow -= 2;
	}
	// sort the used symbols by ascending frequency (ties broken by symbol value)
	heap_size = 0;
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		if (symbol_freq[symbol] == 0)
			continue;
		i = heap_size++;
		while (i > 0 && symbol_freq[sorted[i - 1]] > symbol_freq[symbol])
		{
			sorted[i] = sorted[i - 1];
			i -= 1;
		}
		sorted[i] = (t_u16)symbol;
	}
	// hand out the lengths: the rarest symbols get the longest codes
	i = 0;
	for (depth = HUFFMAN_MAXLENGTH; depth >= 1; --depth)
	{
		for (node = 0; node < bl_count[depth]; ++node)
			lengths[sorted[i++]] = (t_u8)depth;
	}
}

//! Computes the frequency of each symbol in the given data (plus one "end" symbol)
static
void	HUFFMAN_CountFrequencies(t_u64* freq, t_u8 const* data, t_size size)
{
	t_size	i;

	Memory_Set(freq, 0, HUFFMAN_SYMBOLS * sizeof(t_u64));
	for (i = 0; i < size; ++i)
		freq[data[i]] += 1;
	freq[HUFFMAN_SYMBOL_END] = 1;
}



#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT == HUFFMAN_FORMAT_PACK)

/*============================================================================*\
||                        UNIX `pack` (.z file) format                        ||
\*============================================================================*/

t_u8*	HUFFMAN_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_huffman_bitwriter	b = {0};
	t_u64	freq[HUFFMAN_SYMBOLS];
	t_u8	lengths[HUFFMAN_SYMBOLS];
	t_u16	codes[HUFFMAN_SYMBOLS];
	t_uint	leaves[HUFFMAN_MAXLENGTH + 1];
	t_uint	codebase[HUFFMAN_MAXLENGTH + 1];
	t_u8*	result;
	t_size	dest_i;
	t_size	i;
	t_uint	maxlen;
	t_uint	nodes;
	t_uint	level;
	t_uint	symbol;
	t_uint	next;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if CCCERROR((size > (t_size)0xFFFFFFFFu), ERROR_LENGTH2LARGE,
		"data to compress is too large: the pack format stores the size as a 32-bit integer")
		return (NULL);
	result = (t_u8*)Memory_Allocate(HUFFMAN_COMPRESS_MAXSIZE(size));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	HUFFMAN_CountFrequencies(freq, data, size);
	if (size == 0)
		freq[0] = 1; // the pack tree format cannot describe a single-leaf tree: add a dummy leaf
	HUFFMAN_BuildLengths(lengths, freq);
	// the "end of block" symbol must be the very last leaf of the deepest level:
	// if it is not at the deepest level, swap it with a symbol which is (this
	// never worsens the compressed size, since that symbol is at least as
	// frequent as the end symbol, which only ever occurs once)
	maxlen = 0;
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		if (lengths[symbol] > maxlen)
			maxlen = lengths[symbol];
	}
	if (lengths[HUFFMAN_SYMBOL_END] < maxlen)
	{
		for (symbol = 0; symbol < HUFFMAN_SYMBOL_END; ++symbol)
		{
			if (lengths[symbol] == maxlen)
				break;
		}
		lengths[symbol] = lengths[HUFFMAN_SYMBOL_END];
		lengths[HUFFMAN_SYMBOL_END] = (t_u8)maxlen;
	}
	// count the leaves at each tree level, and derive each level's first leaf code
	// (in this format, the internal nodes take the smallest codes of each level)
	Memory_Set(leaves, 0, sizeof(leaves));
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		if (lengths[symbol] > 0)
			leaves[lengths[symbol]] += 1;
	}
	nodes = 2;
	for (level = 1; level <= maxlen; ++level)
	{
		codebase[level] = (nodes - leaves[level]);
		nodes = (codebase[level] * 2);
	}
	// assign the canonical codes: each level's leaves in ascending symbol order,
	// with the "end of block" symbol always last at the deepest level
	for (level = 1; level <= maxlen; ++level)
	{
		next = codebase[level];
		for (symbol = 0; symbol < HUFFMAN_SYMBOL_END; ++symbol)
		{
			if (lengths[symbol] == level)
				codes[symbol] = (t_u16)(next++);
		}
	}
	codes[HUFFMAN_SYMBOL_END] = (t_u16)(codebase[maxlen] + leaves[maxlen] - 1);
	// write the header: magic bytes, big-endian 32-bit size, tree depth
	result[0] = HUFFMAN_HEADER_MAGIC_0;
	result[1] = HUFFMAN_HEADER_MAGIC_1;
	result[2] = (t_u8)(size >> 24);
	result[3] = (t_u8)(size >> 16);
	result[4] = (t_u8)(size >> 8);
	result[5] = (t_u8)(size >> 0);
	result[6] = (t_u8)maxlen;
	dest_i = HUFFMAN_HEADER_SIZE;
	// write the per-level leaf counts (the deepest level's count is stored minus 2)
	for (level = 1; level <= maxlen; ++level)
		result[dest_i++] = (t_u8)(level == maxlen ? leaves[level] - 2 : leaves[level]);
	// write the symbol table (the "end of block" symbol is implicit, and not stored)
	for (level = 1; level <= maxlen; ++level)
	{
		for (symbol = 0; symbol < HUFFMAN_SYMBOL_END; ++symbol)
		{
			if (lengths[symbol] == level)
				result[dest_i++] = (t_u8)symbol;
		}
	}
	// write the coded data, terminated by the "end of block" code
	b.pos = dest_i;
	for (i = 0; i < size; ++i)
		HUFFMAN_BitWriter_Put(&b, result, codes[data[i]], lengths[data[i]]);
	HUFFMAN_BitWriter_Put(&b, result, codes[HUFFMAN_SYMBOL_END], lengths[HUFFMAN_SYMBOL_END]);
	dest_i = HUFFMAN_BitWriter_Finish(&b, result);
	// shrink the buffer to fit the actual compressed size
	if (dest_i < (t_size)HUFFMAN_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}

//! Parses and validates a pack-format stream header and tree, filling the decode tables
static
t_bool	HUFFMAN_PACK_ParseTree(
	t_u8 const* data, t_size size,
	t_size* out_usize, t_uint* out_levels, t_size* out_datapos,
	t_uint* leaves, t_uint* codebase, t_u8* symbols)
{
	t_bool	seen[256] = {FALSE};
	t_uint	levels;
	t_uint	level;
	t_uint	nodes;
	t_uint	total;
	t_uint	i;
	t_size	pos;

	if CCCERROR((size < HUFFMAN_HEADER_SIZE), ERROR_ILLEGALBYTES,
		"invalid pack data: too short to contain the stream header")
		return (FALSE);
	if CCCERROR((data[0] != HUFFMAN_HEADER_MAGIC_0 || data[1] != HUFFMAN_HEADER_MAGIC_1), ERROR_ILLEGALBYTES,
		"invalid pack data: stream does not begin with the expected magic bytes")
		return (FALSE);
	*out_usize =
		((t_size)data[2] << 24) |
		((t_size)data[3] << 16) |
		((t_size)data[4] << 8) |
		((t_size)data[5] << 0);
	levels = data[6];
	if CCCERROR((levels < 1 || levels > HUFFMAN_PACK_MAXLEVEL), ERROR_ILLEGALBYTES,
		"invalid pack data: the huffman tree depth is out of range")
		return (FALSE);
	if CCCERROR((size < (t_size)HUFFMAN_HEADER_SIZE + levels), ERROR_ILLEGALBYTES,
		"invalid pack data: stream is truncated within the tree level counts")
		return (FALSE);
	pos = HUFFMAN_HEADER_SIZE;
	total = 0;
	for (level = 1; level <= levels; ++level)
	{
		leaves[level] = data[pos++];
		total += leaves[level];
	}
	leaves[levels] += 2; // the deepest level's count is stored minus 2 (and includes the implicit end symbol)
	total += 1; // the symbol table holds every leaf except the implicit end symbol
	if CCCERROR((total > 256), ERROR_ILLEGALBYTES,
		"invalid pack data: the huffman tree has too many symbols")
		return (FALSE);
	// validate that the leaf counts describe a full binary tree, and derive
	// each level's first leaf code (internal nodes take the smallest codes)
	nodes = 2;
	for (level = 1; level <= levels; ++level)
	{
		if CCCERROR((leaves[level] > nodes), ERROR_ILLEGALBYTES,
			"invalid pack data: the huffman tree has more leaves than nodes at some level")
			return (FALSE);
		codebase[level] = (nodes - leaves[level]);
		if CCCERROR((level == levels && codebase[level] != 0), ERROR_ILLEGALBYTES,
			"invalid pack data: the huffman tree is incomplete")
			return (FALSE);
		if CCCERROR((level < levels && codebase[level] == 0), ERROR_ILLEGALBYTES,
			"invalid pack data: the huffman tree has unreachable levels")
			return (FALSE);
		nodes = (codebase[level] * 2);
	}
	if CCCERROR((size - pos < (t_size)total), ERROR_ILLEGALBYTES,
		"invalid pack data: stream is truncated within the symbol table")
		return (FALSE);
	for (i = 0; i < total; ++i)
	{
		symbols[i] = data[pos];
		if CCCERROR((seen[data[pos]]), ERROR_ILLEGALBYTES,
			"invalid pack data: the symbol table contains a duplicate symbol")
			return (FALSE);
		seen[data[pos]] = TRUE;
		pos += 1;
	}
	*out_levels = levels;
	*out_datapos = pos;
	return (TRUE);
}

t_size	HUFFMAN_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_uint	leaves[HUFFMAN_PACK_MAXLEVEL + 1];
	t_uint	codebase[HUFFMAN_PACK_MAXLEVEL + 1];
	t_u8	symbols[256];
	t_size	usize;
	t_uint	levels;
	t_size	datapos;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!HUFFMAN_PACK_ParseTree(data, size, &usize, &levels, &datapos, leaves, codebase, symbols))
		return (SIZE_ERROR);
	return (usize); // NOTE: this simply trusts the header (see the doc in "libccc/compress/huffman.h")
}

t_u8*	HUFFMAN_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_huffman_bitreader	b = {0};
	t_uint	leaves[HUFFMAN_PACK_MAXLEVEL + 1];
	t_uint	codebase[HUFFMAN_PACK_MAXLEVEL + 1];
	t_uint	offset[HUFFMAN_PACK_MAXLEVEL + 1];
	t_u8	symbols[256];
	t_u8*	result;
	t_size	usize;
	t_uint	levels;
	t_size	datapos;
	t_size	produced;
	t_uint	level;
	t_uint	code;
	t_uint	bit;
	t_uint	index;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!HUFFMAN_PACK_ParseTree(data, size, &usize, &levels, &datapos, leaves, codebase, symbols))
		return (NULL);
	// compute each level's offset into the symbol table
	index = 0;
	for (level = 1; level <= levels; ++level)
	{
		offset[level] = index;
		index += leaves[level];
	}
	result = (t_u8*)Memory_Allocate(usize ? usize : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	b.pos = datapos;
	produced = 0;
	while (TRUE)
	{
		code = 0;
		level = 1;
		while (TRUE)
		{
			if CCCERROR((!HUFFMAN_BitReader_Get(&b, data, size, &bit)), ERROR_ILLEGALBYTES,
				"invalid pack data: stream ends before its \"end of block\" code")
			{
				Memory_Deallocate(result);
				return (NULL);
			}
			code = ((code << 1) | bit);
			if (code >= codebase[level])
				break; // reached a leaf node
			level += 1; // reached an internal node: descend one level
		}
		index = (code - codebase[level]);
		if (level == levels && index == leaves[levels] - 1)
		{	// the all-ones code of the deepest level is the "end of block" symbol
			if CCCERROR((produced != usize), ERROR_ILLEGALBYTES,
				"invalid pack data: the coded data ends before the header's stored size")
			{
				Memory_Deallocate(result);
				return (NULL);
			}
			break;
		}
		if CCCERROR((produced >= usize), ERROR_ILLEGALBYTES,
			"invalid pack data: the coded data exceeds the header's stored size")
		{
			Memory_Deallocate(result);
			return (NULL);
		}
		result[produced++] = symbols[offset[level] + index];
	}
	if (dest_size)
		*dest_size = usize;
	return (result);
}

#else

/*============================================================================*\
||                       "raw" canonical Huffman format                       ||
\*============================================================================*/

t_u8*	HUFFMAN_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_huffman_bitwriter	b = {0};
	t_u64	freq[HUFFMAN_SYMBOLS];
	t_u8	lengths[HUFFMAN_SYMBOLS];
	t_u16	codes[HUFFMAN_SYMBOLS];
	t_u16	next_code[HUFFMAN_MAXLENGTH + 1];
	t_uint	bl_count[HUFFMAN_MAXLENGTH + 1];
	t_u8*	result;
	t_size	dest_i;
	t_size	i;
	t_uint	symbol;
	t_uint	length;
	t_u16	code;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_Allocate(HUFFMAN_COMPRESS_MAXSIZE(size));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	HUFFMAN_CountFrequencies(freq, data, size);
	HUFFMAN_BuildLengths(lengths, freq);
	// write the code length table: 257 lengths, packed as 4-bit values
	Memory_Set(result, 0, HUFFMAN_HEADER_SIZE);
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
		result[symbol >> 1] |= (t_u8)(lengths[symbol] << ((symbol & 1) * 4));
	dest_i = HUFFMAN_HEADER_SIZE;
	// assign the canonical codes (RFC 1951 convention: by ascending length, then symbol)
	Memory_Set(bl_count, 0, sizeof(bl_count));
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
		bl_count[lengths[symbol]] += 1;
	code = 0;
	bl_count[0] = 0;
	for (length = 1; length <= HUFFMAN_MAXLENGTH; ++length)
	{
		code = (t_u16)((code + bl_count[length - 1]) << 1);
		next_code[length] = code;
	}
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		if (lengths[symbol] > 0)
			codes[symbol] = next_code[lengths[symbol]]++;
	}
	// write the coded data, terminated by the "end of stream" code
	b.pos = dest_i;
	for (i = 0; i < size; ++i)
		HUFFMAN_BitWriter_Put(&b, result, codes[data[i]], lengths[data[i]]);
	HUFFMAN_BitWriter_Put(&b, result, codes[HUFFMAN_SYMBOL_END], lengths[HUFFMAN_SYMBOL_END]);
	dest_i = HUFFMAN_BitWriter_Finish(&b, result);
	// shrink the buffer to fit the actual compressed size
	if (dest_i < (t_size)HUFFMAN_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}

//! Parses (and validates) a raw-format stream: computes its decompressed size, and optionally decodes it
/*!
**	If `dest` is `NULL`, this only computes the size; otherwise, it also
**	writes the decoded bytes to `dest` (which must be large enough).
*/
static
t_bool	HUFFMAN_RAW_Parse(t_size* out_size, t_u8* dest, t_u8 const* data, t_size size)
{
	s_huffman_bitreader	b = {0};
	t_u8	lengths[HUFFMAN_SYMBOLS];
	t_u16	symbols[HUFFMAN_SYMBOLS];
	t_uint	bl_count[HUFFMAN_MAXLENGTH + 1];
	t_size	produced;
	t_uint	symbol;
	t_uint	length;
	t_uint	used;
	t_uint	index;
	t_uint	first;
	t_uint	code;
	t_uint	bit;
	t_sint	left;

	*out_size = 0;
	if CCCERROR((size < HUFFMAN_HEADER_SIZE), ERROR_ILLEGALBYTES,
		"invalid huffman data: too short to contain the code length table")
		return (FALSE);
	if CCCERROR((data[HUFFMAN_HEADER_SIZE - 1] & 0xF0), ERROR_ILLEGALBYTES,
		"invalid huffman data: the code length table has nonzero padding bits")
		return (FALSE);
	Memory_Set(bl_count, 0, sizeof(bl_count));
	used = 0;
	for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
	{
		lengths[symbol] = ((data[symbol >> 1] >> ((symbol & 1) * 4)) & 0xF);
		if (lengths[symbol] > 0)
		{
			bl_count[lengths[symbol]] += 1;
			used += 1;
		}
	}
	if CCCERROR((lengths[HUFFMAN_SYMBOL_END] == 0), ERROR_ILLEGALBYTES,
		"invalid huffman data: the code length table has no \"end of stream\" code")
		return (FALSE);
	// the code length table must describe a complete prefix code (or the
	// degenerate single-symbol code, which can only ever be the "end" symbol)
	if (used == 1)
	{
		if CCCERROR((lengths[HUFFMAN_SYMBOL_END] != 1), ERROR_ILLEGALBYTES,
			"invalid huffman data: a single-symbol code length table must use a 1-bit code")
			return (FALSE);
	}
	else
	{
		left = 1;
		for (length = 1; length <= HUFFMAN_MAXLENGTH; ++length)
		{
			left <<= 1;
			left -= bl_count[length];
			if CCCERROR((left < 0), ERROR_ILLEGALBYTES,
				"invalid huffman data: the code length table is oversubscribed")
				return (FALSE);
		}
		if CCCERROR((left != 0), ERROR_ILLEGALBYTES,
			"invalid huffman data: the code length table is incomplete")
			return (FALSE);
	}
	// build the canonical symbol table (symbols ordered by ascending length, then value)
	index = 0;
	for (length = 1; length <= HUFFMAN_MAXLENGTH; ++length)
	{
		for (symbol = 0; symbol < HUFFMAN_SYMBOLS; ++symbol)
		{
			if (lengths[symbol] == length)
				symbols[index++] = (t_u16)symbol;
		}
	}
	// decode the bit stream, symbol by symbol, until the "end of stream" code
	b.pos = HUFFMAN_HEADER_SIZE;
	produced = 0;
	while (TRUE)
	{
		code = 0;
		first = 0;
		index = 0;
		length = 1;
		while (TRUE)
		{
			if CCCERROR((length > HUFFMAN_MAXLENGTH), ERROR_ILLEGALBYTES,
				"invalid huffman data: the stream contains an invalid code")
				return (FALSE);
			if CCCERROR((!HUFFMAN_BitReader_Get(&b, data, size, &bit)), ERROR_ILLEGALBYTES,
				"invalid huffman data: stream ends before its \"end of stream\" code")
				return (FALSE);
			code |= bit;
			if (code - first < bl_count[length])
			{
				symbol = symbols[index + (code - first)];
				break;
			}
			index += bl_count[length];
			first = ((first + bl_count[length]) << 1);
			code <<= 1;
			length += 1;
		}
		if (symbol == HUFFMAN_SYMBOL_END)
			break; // NOTE: any bytes remaining after this point are ignored
		if (dest != NULL)
			dest[produced] = (t_u8)symbol;
		produced += 1;
	}
	*out_size = produced;
	return (TRUE);
}

t_size	HUFFMAN_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!HUFFMAN_RAW_Parse(&result, NULL, data, size))
		return (SIZE_ERROR);
	return (result);
}

t_u8*	HUFFMAN_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	result_size;
	t_size	check;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!HUFFMAN_RAW_Parse(&result_size, NULL, data, size))
		return (NULL);
	result = (t_u8*)Memory_Allocate(result_size ? result_size : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	HUFFMAN_RAW_Parse(&check, result, data, size); // already validated above, cannot fail
	if (dest_size)
		*dest_size = result_size;
	return (result);
}

#endif
