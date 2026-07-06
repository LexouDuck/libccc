/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/lz77.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_LZ77_H
#define __LIBCCC_COMPRESS_LZ77_H
/*!@group{libccc_compress_lz77,29,libccc/compress/lz77.h}
**
**	This header defines compression/decompression functions,
**	using the LZ77 (Lempel-Ziv 1977) "sliding window" compression algorithm.
**
**	LZ77 works by replacing repeated occurrences of data with short references
**	to a previous occurrence of that same data: a `(distance, length)` pair,
**	which means "go back `distance` bytes in the decompressed output,
**	and copy `length` bytes from there". Any data which cannot be encoded
**	as such a back-reference is stored as-is (a "literal" byte).
**
**	The compressed stream is encoded as a series of groups, where each group
**	begins with a single "flags" byte: each of its 8 bits (read from the
**	most-significant bit to the least-significant bit) says whether the
**	corresponding token in the group is a back-reference (bit set to `1`),
**	or a literal byte (bit set to `0`).
**
**	The exact binary layout of the compressed stream can be configured at
**	compile-time, via the #LIBCONFIG_COMPRESS_LZ77_FORMAT macro (see below),
**	so as to be interoperable with some common LZ77 stream formats.
**
**	@see
**	- https://en.wikipedia.org/wiki/LZ77_and_LZ78
**	- https://problemkaputt.de/gbatek.htm#biosdecompressionfunctions
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_LZ77_T
#define __LIBCCC_COMPRESS_LZ77_T

/*============================================================================*\
||                                Configuration                               ||
\*============================================================================*/

//!@doc The possible values for the #LIBCONFIG_COMPRESS_LZ77_FORMAT configuration macro
//!@{

//! Generic "raw" LZ77 stream: no header, window of 4096 bytes, back-references of 3 to 18 bytes
/*!
**	Each back-reference token is stored as 2 bytes (big-endian), ie: `LLLLDDDD dddddddd`:
**	- the 4 `L` bits store `length - 3` (so, lengths of 3 to 18 bytes)
**	- the 12 `Dd` bits store `distance - 1` (so, distances of 1 to 4096 bytes)
*/
#define LZ77_FORMAT_RAW	(0)

//! GBA BIOS-compatible LZ77 format (the format decoded by the GBA/NDS BIOS "type 0x10" SWI calls)
/*!
**	Identical to #LZ77_FORMAT_RAW, except that the compressed stream begins
**	with a 4-byte header (magic byte `0x10`, followed by the total decompressed
**	size, stored as a 24-bit little-endian unsigned integer), and the total
**	compressed stream is zero-padded to a multiple of 4 bytes in size.
**	NOTE: this means that data larger than 16MB cannot be compressed, with this format.
**	NOTE: if the compressed data is to be decompressed directly to the GBA's VRAM
**	(ie: with the `LZ77UnCompVram` BIOS call), then back-references with a distance
**	of `1` are forbidden: for this, see #LIBCONFIG_COMPRESS_LZ77_MINDISTANCE below.
*/
#define LZ77_FORMAT_GBA	(1)

//! NDS-style extended LZ77 format, commonly known as "LZ11" (the format decoded by the NDS/DSi/3DS "type 0x11" functions)
/*!
**	Same group/flags structure as #LZ77_FORMAT_GBA, with a 4-byte header
**	(magic byte `0x11`, followed by the total decompressed size, stored as
**	a 24-bit little-endian unsigned integer), but each back-reference token
**	can be 2, 3, or 4 bytes long, which allows for much longer back-references
**	(from 3 up to 65808 bytes), while keeping the same 4096-byte window:
**	- `LLLLDDDD dddddddd`                            with `LLLL >= 2`: stores `length - 1`   (lengths 3 to 16)
**	- `0000LLLL llllDDDD dddddddd`                                    : stores `length - 17`  (lengths 17 to 272)
**	- `0001LLLL llllllll llllDDDD dddddddd`                           : stores `length - 273` (lengths 273 to 65808)
**	NOTE: this means that data larger than 16MB cannot be compressed, with this format.
*/
#define LZ77_FORMAT_NDS	(2)

//!@}

//!@doc This macro sets the LZ77 compressed stream format used by the LZ77_* functions
/*!
**	This macro configures which binary stream format is used by the
**	LZ77_Compress(), LZ77_Decompress() and LZ77_GetDecompressedSize() functions.
**	The possible values are:
**	- #LZ77_FORMAT_RAW (this is the default)
**	- #LZ77_FORMAT_GBA
**	- #LZ77_FORMAT_NDS
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZ77_FORMAT
#define LIBCONFIG_COMPRESS_LZ77_FORMAT	LZ77_FORMAT_RAW
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT < LZ77_FORMAT_RAW || LIBCONFIG_COMPRESS_LZ77_FORMAT > LZ77_FORMAT_NDS)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZ77_FORMAT, must be one of: LZ77_FORMAT_RAW, LZ77_FORMAT_GBA, LZ77_FORMAT_NDS"
#endif

//!@doc This macro sets the minimum allowed back-reference distance for the LZ77 compressor
/*!
**	By default, this is `1`, meaning the compressor is allowed to output
**	back-references which overlap with the data they produce (this is valid
**	LZ77, and is in fact a very efficient way to encode repeating patterns).
**	Some decompressors, however, cannot handle a back-reference distance of `1`
**	(most notably, the GBA BIOS `LZ77UnCompVram` call, which writes to VRAM
**	in 16-bit units) - in which case, this macro should be set to `2`.
**	NOTE: this only affects compression: decompression always accepts any distance.
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZ77_MINDISTANCE
#define LIBCONFIG_COMPRESS_LZ77_MINDISTANCE	(1)
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZ77_MINDISTANCE < 1 || LIBCONFIG_COMPRESS_LZ77_MINDISTANCE > 0x1000)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZ77_MINDISTANCE, must be in range [1, 4096]"
#endif

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The size (in bytes) of the LZ77 "sliding window" (ie: the maximum back-reference distance)
//!@{
#define LZ77_WINDOW_SIZE	(0x1000)
//!@}

//!@doc The minimum/maximum length (in bytes) which a single LZ77 back-reference token can encode
//!@{
#define LZ77_MATCHLENGTH_MIN	(3)
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_NDS)
#define LZ77_MATCHLENGTH_MAX	(0x10110)
#else
#define LZ77_MATCHLENGTH_MAX	(18)
#endif
//!@}

//!@doc The size (in bytes) of the header at the start of the compressed stream
//!@{
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_RAW)
#define LZ77_HEADER_SIZE	(0)
#else
#define LZ77_HEADER_SIZE	(4)
#endif
//!@}

//!@doc The magic byte value at the very start of the compressed stream (if the format has a header)
//!@{
#if (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_GBA)
#define LZ77_HEADER_MAGIC	(0x10)
#elif (LIBCONFIG_COMPRESS_LZ77_FORMAT == LZ77_FORMAT_NDS)
#define LZ77_HEADER_MAGIC	(0x11)
#endif
//!@}

//!@doc The maximum size (in bytes) of data which can be compressed, for the current format
/*!
**	The header-based formats (#LZ77_FORMAT_GBA and #LZ77_FORMAT_NDS) store the
**	total decompressed size as a 24-bit integer, so they cannot handle data
**	which is larger than 16MB.
*/
//!@{
#if (LZ77_HEADER_SIZE > 0)
#define LZ77_SIZE_MAX	((t_size)0xFFFFFF)
#else
#define LZ77_SIZE_MAX	((t_size)-1)
#endif
//!@}

//!@doc Macro function which gives the worst-case compressed size, for a given input size `N`
/*!
**	The worst-case scenario for LZ77 compression is input data in which
**	no repeating sequences can be found whatsoever: in this case, the data
**	will be encoded as literal bytes only, which costs 1 extra "flags" byte
**	for every 8 bytes of input data (plus the header and padding, if any).
*/
//!@{
#if (LZ77_HEADER_SIZE > 0)
#define LZ77_COMPRESS_MAXSIZE(N) \
	(LZ77_HEADER_SIZE + (N) + (((N) + 7) / 8) + 3) // `+ 3` for the zero-padding to a multiple of 4 bytes
#else
#define LZ77_COMPRESS_MAXSIZE(N) \
	((N) + (((N) + 7) / 8))
#endif
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_LZ77_F
#define __LIBCCC_COMPRESS_LZ77_F

/*============================================================================*\
||                            LZ77: main functions                            ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using LZ77 compression
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZ77_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress
**						(cannot exceed #LZ77_SIZE_MAX, for the current format).
**
**	@returns
**	A newly allocated buffer, which contains the LZ77-compressed equivalent
**	of the given `data` buffer, or `NULL` if an error occurred.
**	NOTE: if `size` is `0`, a valid (possibly zero-byte, but non-`NULL`) buffer
**	is returned (for header-based formats, this buffer contains only the header).
*/
//!@{
_MALLOC()
t_u8*					LZ77_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lz77compress	LZ77_Compress
//!@}

//!@doc Decompresses the given LZ77-compressed `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZ77_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The LZ77-compressed data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given LZ77-compressed `data` buffer, or `NULL` if an error occurred
**	(for instance, if the given `data` is malformed/truncated LZ77 data,
**	or contains an invalid back-reference).
**	NOTE: if the decompressed size is `0`, a valid (zero-byte, but non-`NULL`)
**	buffer is returned.
*/
//!@{
_MALLOC()
t_u8*						LZ77_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lz77decompress	LZ77_Decompress
//!@}

/*============================================================================*\
||                           LZ77: utility functions                          ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given LZ77-compressed `data` buffer
/*!
**	@nonstd
**
**	Parses the given LZ77-compressed `data` buffer, checking its validity,
**	and computes the total size which this data would occupy, once decompressed.
**	For the header-based formats (#LZ77_FORMAT_GBA and #LZ77_FORMAT_NDS),
**	this function also checks that the parsed stream total matches the
**	decompressed size which is announced in the stream's header.
**	This function does not allocate anything, and is called by LZ77_Decompress()
**	to check the validity of its input, and know how much memory to allocate.
**
**	@param	data	The LZ77-compressed data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed/truncated LZ77 data.
*/
//!@{
t_size						LZ77_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_lz77decompsize	LZ77_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
