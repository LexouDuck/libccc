/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/huffman.h                |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_HUFFMAN_H
#define __LIBCCC_COMPRESS_HUFFMAN_H
/*!@group{libccc_compress_huffman,29,libccc/compress/huffman.h}
**
**	This header defines compression/decompression functions,
**	using Huffman coding (an optimal-prefix-code entropy coder).
**
**	Huffman coding works by assigning a variable-length bit code to each
**	possible byte value, such that frequently-occurring bytes get shorter
**	codes, and rare bytes get longer codes. The set of codes forms a
**	"prefix code" (no code is a prefix of another code), so the compressed
**	bit stream can be decoded unambiguously. The code lengths are chosen
**	optimally, based on the byte frequencies of the input data (this is
**	the classic "Huffman algorithm"). Since the code table is built from
**	the input data, a description of it must be stored in the compressed
**	stream, so that the decompressor can rebuild the same table.
**
**	The libccc implementation uses "canonical" Huffman codes: the exact
**	bit codes are derived deterministically from the code *lengths* alone,
**	so only the lengths need to be stored, not the codes themselves.
**	The code lengths are limited to #HUFFMAN_MAXLENGTH (15) bits: in the
**	rare cases where the optimal Huffman tree would be deeper than that,
**	the code lengths are adjusted (with a negligible loss of compression).
**
**	Note that Huffman coding is a pure entropy coder: it only exploits the
**	frequency distribution of individual bytes, not repeated sequences.
**	As such, it compresses poorly compared to dictionary coders (LZ77/LZW/
**	LZMA) on most data - but it is simple, fast, and is the standard
**	final-stage entropy coder in many formats (DEFLATE, JPEG, etc).
**
**	The exact binary layout of the compressed stream can be configured at
**	compile-time, via the #LIBCONFIG_COMPRESS_HUFFMAN_FORMAT macro.
**
**	@see
**	- https://en.wikipedia.org/wiki/Huffman_coding
**	- https://en.wikipedia.org/wiki/Canonical_Huffman_code
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_HUFFMAN_T
#define __LIBCCC_COMPRESS_HUFFMAN_T

/*============================================================================*\
||                                Configuration                               ||
\*============================================================================*/

//!@doc The possible values for the #LIBCONFIG_COMPRESS_HUFFMAN_FORMAT configuration macro
//!@{

//! Generic "raw" canonical Huffman stream: a code length table, then the coded data
/*!
**	The stream begins with a 129-byte code length table: 257 code lengths
**	(one for each of the 256 possible byte values, plus one for the special
**	"end of stream" symbol `256`), each stored as a 4-bit value (`0` meaning
**	"symbol absent", and the upper 4 bits of the final byte are always `0`).
**	The actual bit codes are derived from these lengths, using the standard
**	canonical ordering (as in RFC 1951, section 3.2.2): codes are assigned
**	in increasing order of code length, and by increasing symbol value
**	within the same length. The coded data follows, packed most-significant-
**	bit-first, and is terminated by the "end of stream" symbol's code
**	(any remaining bits in the final byte are zero padding).
**	There is no size field, so the stream is self-terminating: this format
**	has no inherent limit on the amount of data which can be compressed.
*/
#define HUFFMAN_FORMAT_RAW	(0)

//! UNIX `pack`-compatible Huffman stream (the contents of a `.z` file)
/*!
**	This is the (ancient) format produced by the UNIX `pack` command, which
**	can still be decompressed by `gzip`/`gunzip` to this day. The stream
**	begins with a 7-byte header: two magic bytes (`0x1F`, `0x1E`), then the
**	uncompressed size as a big-endian 32-bit integer (so, this format cannot
**	store more than 4 GiB of data), then the depth of the Huffman tree
**	(the maximum code length, at most 24 - libccc only ever produces 15).
**	Then, for each tree level, a byte gives the amount of leaf symbols at
**	that level, followed by a table of all the leaf symbols, level by level.
**	This format uses the opposite canonical ordering from #HUFFMAN_FORMAT_RAW:
**	at each tree level, the internal nodes occupy the numerically smallest
**	codes, and the leaves the largest. The special "end of block" symbol is
**	always the very last leaf of the deepest level (the "all ones" code), and
**	is omitted from the symbol table; the deepest level's leaf count is also
**	stored minus 2, so that it always fits in a single byte. These quirks
**	are historic, and are reproduced faithfully for interoperability.
*/
#define HUFFMAN_FORMAT_PACK	(1)

//!@}

//!@doc This macro sets the Huffman compressed stream format used by the HUFFMAN_* functions
/*!
**	This macro configures which binary stream format is used by the
**	HUFFMAN_Compress(), HUFFMAN_Decompress() and HUFFMAN_GetDecompressedSize()
**	functions. The possible values are:
**	- #HUFFMAN_FORMAT_RAW (this is the default)
**	- #HUFFMAN_FORMAT_PACK
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_HUFFMAN_FORMAT
#define LIBCONFIG_COMPRESS_HUFFMAN_FORMAT	HUFFMAN_FORMAT_RAW
#endif
//!@}
#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT < HUFFMAN_FORMAT_RAW || LIBCONFIG_COMPRESS_HUFFMAN_FORMAT > HUFFMAN_FORMAT_PACK)
#error "Invalid value selected for LIBCONFIG_COMPRESS_HUFFMAN_FORMAT, must be one of: HUFFMAN_FORMAT_RAW, HUFFMAN_FORMAT_PACK"
#endif

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The maximum length (in bits) of a Huffman code produced by the libccc compressor
//!@{
#define HUFFMAN_MAXLENGTH	(15)
//!@}

//!@doc The amount of symbols in the Huffman alphabet (256 byte values, plus the end symbol)
//!@{
#define HUFFMAN_SYMBOLS		(257)
//!@}

//!@doc The special "end of stream"/"end of block" symbol, which terminates the coded data
//!@{
#define HUFFMAN_SYMBOL_END	(256)
//!@}

//!@doc The size (in bytes) of the fixed-size portion at the start of the compressed stream
/*!
**	For #HUFFMAN_FORMAT_RAW, this is the code length table (129 bytes).
**	For #HUFFMAN_FORMAT_PACK, this is the 7-byte header (the variable-size
**	tree level counts and symbol table follow it).
*/
//!@{
#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT == HUFFMAN_FORMAT_PACK)
#define HUFFMAN_HEADER_SIZE	(7)
#else
#define HUFFMAN_HEADER_SIZE	(129)
#endif
//!@}

//!@doc The magic bytes at the very start of the compressed stream (if the format has magic bytes)
//!@{
#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT == HUFFMAN_FORMAT_PACK)
#define HUFFMAN_HEADER_MAGIC_0	(0x1F)
#define HUFFMAN_HEADER_MAGIC_1	(0x1E)
#endif
//!@}

//!@doc Macro function which gives the worst-case compressed size, for a given input size `N`
/*!
**	Every coded symbol (each input byte, and the final "end" symbol) costs
**	at most #HUFFMAN_MAXLENGTH bits, and the tree description costs at most
**	a few hundred bytes (a constant, per format): this bound is thus fully
**	provable, if quite pessimistic (in practice, even incompressible data
**	only costs slightly more than 8 bits per byte).
*/
//!@{
#if (LIBCONFIG_COMPRESS_HUFFMAN_FORMAT == HUFFMAN_FORMAT_PACK)
#define HUFFMAN_COMPRESS_MAXSIZE(N) \
	(HUFFMAN_HEADER_SIZE + 24 + 256 + (((N) + 1) * HUFFMAN_MAXLENGTH + 7) / 8 + 1)
#else
#define HUFFMAN_COMPRESS_MAXSIZE(N) \
	(HUFFMAN_HEADER_SIZE + (((N) + 1) * HUFFMAN_MAXLENGTH + 7) / 8 + 1)
#endif
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_HUFFMAN_F
#define __LIBCCC_COMPRESS_HUFFMAN_F

/*============================================================================*\
||                           Huffman: main functions                          ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using Huffman coding
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_HUFFMAN_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress.
**
**	@returns
**	A newly allocated buffer, which contains the Huffman-coded equivalent
**	of the given `data` buffer, or `NULL` if an error occurred (for instance,
**	if `size` is larger than 4 GiB, for the #HUFFMAN_FORMAT_PACK format).
**	NOTE: if `size` is `0`, a valid (non-`NULL`) buffer is still returned
**	(which contains only the code table and the "end of stream" code).
*/
//!@{
_MALLOC()
t_u8*						HUFFMAN_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_huffmancompress	HUFFMAN_Compress
//!@}

//!@doc Decompresses the given Huffman-coded `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_HUFFMAN_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The Huffman-coded data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given Huffman-coded `data` buffer, or `NULL` if an error occurred
**	(for instance, if the given `data` is malformed/truncated).
**	NOTE: if the decompressed size is `0`, a valid (zero-byte, but non-`NULL`)
**	buffer is returned.
*/
//!@{
_MALLOC()
t_u8*						HUFFMAN_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_huffmandecompress	HUFFMAN_Decompress
//!@}

/*============================================================================*\
||                          Huffman: utility functions                        ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given Huffman-coded `data` buffer
/*!
**	@nonstd
**
**	For the #HUFFMAN_FORMAT_RAW format, this parses the entire given stream
**	(checking its validity along the way), counting the coded symbols - this
**	requires no memory allocation, but takes time proportional to the stream
**	size. For the #HUFFMAN_FORMAT_PACK format, this simply returns the size
**	field stored in the stream's header - NOTE: this means that, for this
**	format, the returned value is only as trustworthy as the given stream
**	(HUFFMAN_Decompress() does fully validate that the coded data matches
**	the header's size field, and errors out if it does not).
**
**	@param	data	The Huffman-coded data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed/truncated.
*/
//!@{
t_size						HUFFMAN_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_huffmandecompsize	HUFFMAN_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
