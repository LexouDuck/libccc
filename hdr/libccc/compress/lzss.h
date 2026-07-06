/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/lzss.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_LZSS_H
#define __LIBCCC_COMPRESS_LZSS_H
/*!@group{libccc_compress_lzss,29,libccc/compress/lzss.h}
**
**	This header defines compression/decompression functions,
**	using the LZSS algorithm (Lempel-Ziv-Storer-Szymanski).
**
**	LZSS is a refinement of LZ77 dictionary compression: the compressed
**	stream is a sequence of items, each item being either a "literal"
**	(a byte stored as-is), or a "match" (a position/length pair, which
**	references a sequence of bytes that occurred earlier, in a sliding
**	window over the recently processed data). A group of 8 items is
**	preceded by a flag byte, which tells literals and matches apart
**	(one bit per item, least significant bit first: `1` means literal).
**
**	The libccc implementation produces (and consumes) the exact stream
**	layout of the classic public-domain `LZSS.C` reference program by
**	Haruhiko Okumura (1989), which countless file formats derive from:
**	- the sliding window is a ring buffer of #LZSS_WINDOW (4096) bytes,
**		initially filled with the #LIBCONFIG_COMPRESS_LZSS_FILLBYTE value
**		(a space character, by default), with writing starting at ring
**		position `4096 - 18` - matches store *absolute* ring positions
**		(12 bits), not backwards distances
**	- a match is 2 bytes: first the low 8 bits of the ring position, then
**		the position's high 4 bits, followed by the match length minus 3
**		(4 bits, so matches cover 3 to #LZSS_MATCHLENGTH_MAX (18) bytes)
**	The stream is headerless, and self-terminating only by running out of
**	input bytes (there is no size field, nor any "end of stream" marker).
**
**	@see
**	- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski
**	- https://oku.edu.mie-u.ac.jp/~okumura/compression/history.html
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_LZSS_T
#define __LIBCCC_COMPRESS_LZSS_T

/*============================================================================*\
||                                Configuration                               ||
\*============================================================================*/

//!@doc This macro sets the byte value which initially fills the LZSS sliding window
/*!
**	Because matches may reference any absolute position of the ring buffer
**	window (including regions which have not been written to yet), the
**	initial contents of the window are part of the stream format: both the
**	compressor and decompressor must agree on this value, for streams to
**	decompress identically. The default is `0x20` (the ASCII space), which
**	is what the classic Okumura `LZSS.C` program uses; note that several
**	LZSS-derived formats found in the wild use `0x00` instead.
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZSS_FILLBYTE
#define LIBCONFIG_COMPRESS_LZSS_FILLBYTE	(0x20)
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZSS_FILLBYTE < 0x00 || LIBCONFIG_COMPRESS_LZSS_FILLBYTE > 0xFF)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZSS_FILLBYTE, must be a byte value (from 0x00 to 0xFF)"
#endif

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The size (in bytes) of the LZSS sliding window ring buffer
//!@{
#define LZSS_WINDOW	(0x1000)
//!@}

//!@doc The minimum length (in bytes) of an LZSS match (shorter repetitions are stored as literals)
//!@{
#define LZSS_MATCHLENGTH_MIN	(3)
//!@}

//!@doc The maximum length (in bytes) of an LZSS match
//!@{
#define LZSS_MATCHLENGTH_MAX	(18)
//!@}

//!@doc Macro function which gives the worst-case compressed size, for a given input size `N`
/*!
**	The worst case is an incompressible input, stored as all literals:
**	every group of 8 input bytes then costs 9 bytes (1 flag byte + 8 literals).
*/
//!@{
#define LZSS_COMPRESS_MAXSIZE(N) \
	((N) + ((N) + 7) / 8)
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_LZSS_F
#define __LIBCCC_COMPRESS_LZSS_F

/*============================================================================*\
||                            LZSS: main functions                            ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using the LZSS algorithm
/*!
**	@nonstd
**
**	The compressed stream layout matches the classic Okumura `LZSS.C`
**	program exactly (see the description at the top of this header),
**	provided that the #LIBCONFIG_COMPRESS_LZSS_FILLBYTE configuration
**	macro is left at its default value.
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress.
**
**	@returns
**	A newly allocated buffer, which contains the LZSS-compressed equivalent
**	of the given `data` buffer, or `NULL` if an error occurred.
**	NOTE: if `size` is `0`, a valid (zero-byte, but non-`NULL`) buffer is
**	still returned (an empty input compresses to an empty stream).
*/
//!@{
_MALLOC()
t_u8*					LZSS_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzsscompress	LZSS_Compress
//!@}

//!@doc Decompresses the given LZSS-compressed `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	Since the LZSS stream format is headerless and has no "end of stream"
**	marker, decompression simply proceeds until the input bytes run out
**	(this matches the behavior of the classic Okumura `LZSS.C` program).
**	The only malformed input possible is a stream which ends in the middle
**	of a 2-byte match item (in which case, an error occurs).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The LZSS-compressed data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given LZSS-compressed `data` buffer, or `NULL` if an error
**	occurred. NOTE: if the decompressed size is `0`, a valid (zero-byte,
**	but non-`NULL`) buffer is returned.
*/
//!@{
_MALLOC()
t_u8*						LZSS_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzssdecompress	LZSS_Decompress
//!@}

/*============================================================================*\
||                           LZSS: utility functions                          ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given LZSS-compressed `data` buffer
/*!
**	@nonstd
**
**	Since the LZSS stream format has no header, this parses the entire
**	given stream (checking its validity along the way), summing the sizes
**	of the coded items - this requires no memory allocation, but takes
**	time proportional to the stream size.
**
**	@param	data	The LZSS-compressed data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed/truncated.
*/
//!@{
t_size						LZSS_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_lzssdecompsize	LZSS_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
