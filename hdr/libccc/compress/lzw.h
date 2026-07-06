/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/lzw.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_LZW_H
#define __LIBCCC_COMPRESS_LZW_H
/*!@group{libccc_compress_lzw,29,libccc/compress/lzw.h}
**
**	This header defines compression/decompression functions,
**	using the LZW (Lempel-Ziv-Welch) dictionary compression algorithm.
**
**	LZW works by building a dictionary of previously-encountered byte sequences,
**	as the data is being processed (on both the compression side and the
**	decompression side, symmetrically - so the dictionary itself never needs
**	to be stored in the compressed stream). Each dictionary entry is identified
**	by a numeric code: the compressed stream is simply a sequence of such codes.
**	The dictionary starts out with 256 entries (one for each possible byte value,
**	whose code is simply that byte's value), plus (depending on the format used)
**	up to 2 special control codes:
**	- the "clear" code (`256`), which resets the dictionary to its initial state
**	- the "end" code (`257`), which marks the end of the compressed stream
**	Each new code is assigned to the dictionary in ascending order, and codes
**	are stored with a variable bit-width: the width starts at 9 bits, and
**	increases by one bit whenever the dictionary grows past the amount of
**	codes which can be represented with the current width, up to a maximum
**	width of #LZW_MAXBITS bits (at which point, the compressor emits a
**	"clear" code, and the dictionary is reset).
**
**	The exact binary layout of the compressed stream can be configured at
**	compile-time, via the #LIBCONFIG_COMPRESS_LZW_FORMAT macro (see below),
**	so as to be interoperable with some common LZW stream formats.
**
**	@see
**	- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Welch
**	- https://www.w3.org/Graphics/GIF/spec-gif89a.txt (Appendix F)
**	- https://download.osgeo.org/libtiff/doc/TIFF6.pdf (Section 13)
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_LZW_T
#define __LIBCCC_COMPRESS_LZW_T

/*============================================================================*\
||                                Configuration                               ||
\*============================================================================*/

//!@doc The possible values for the #LIBCONFIG_COMPRESS_LZW_FORMAT configuration macro
//!@{

//! Generic "raw" LZW stream: no header, variable-width codes packed LSB-first
/*!
**	Codes are packed least-significant-bit-first (like in GIF files), with
**	both a "clear" code (`256`) and an "end" code (`257`), and the stream
**	always begins with a "clear" code. When #LZW_MAXBITS is `12` (the default),
**	this format is exactly the LZW code stream found inside GIF image data
**	(for a "minimum code size" of 8, ie: 256-color images).
*/
#define LZW_FORMAT_RAW	(0)

//! GIF-style LZW stream: this is simply an alias for #LZW_FORMAT_RAW
/*!
**	NOTE: this refers to the raw LZW code stream inside a GIF file's image data
**	(with a "minimum code size" of 8): the GIF file format further chops this
**	stream up into length-prefixed sub-blocks of at most 255 bytes, but that
**	sub-block layer is part of the GIF container format, not of LZW itself.
**	NOTE: for this to be GIF-compatible, #LZW_MAXBITS must be `12` (the default).
*/
#define LZW_FORMAT_GIF	LZW_FORMAT_RAW

//! TIFF-style LZW stream (the LZW variant used for LZW-compressed TIFF image strips)
/*!
**	Codes are packed most-significant-bit-first, with both a "clear" code (`256`)
**	and an "end" code (`257`), and the stream always begins with a "clear" code.
**	This format uses the (in)famous TIFF "early change" quirk: the code width
**	increases one code earlier than it mathematically needs to (this is a
**	historic off-by-one bug in the original TIFF LZW implementation, which
**	then became enshrined in the TIFF specification).
**	NOTE: this format requires #LZW_MAXBITS to be `12`.
*/
#define LZW_FORMAT_TIFF	(1)

//! UNIX `compress`-compatible LZW stream (the contents of a `.Z` file)
/*!
**	The stream begins with a 3-byte header: two magic bytes (`0x1F`, `0x9D`),
**	then a flags byte which stores the maximum code width (in its lower 5 bits),
**	and the "block mode" flag (`0x80`, always set by the libccc compressor,
**	which means that the "clear" code `256` is in use). There is no "end" code:
**	the stream simply ends when there are no unread bits left in the input.
**	Codes are packed least-significant-bit-first, but with a quirk: codes are
**	written in groups of 8 (so, groups of `width` bytes), and whenever the code
**	width changes (or a "clear" code is emitted), the current group is zero-padded
**	to its full size (this is a historic quirk of the original UNIX `compress`
**	implementation, which must be reproduced for interoperability).
**	NOTE: the maximum code width can be configured with #LZW_MAXBITS (default `16`).
*/
#define LZW_FORMAT_UNIX	(2)

//!@}

//!@doc This macro sets the LZW compressed stream format used by the LZW_* functions
/*!
**	This macro configures which binary stream format is used by the
**	LZW_Compress(), LZW_Decompress() and LZW_GetDecompressedSize() functions.
**	The possible values are:
**	- #LZW_FORMAT_RAW (this is the default)
**	- #LZW_FORMAT_GIF (an alias for #LZW_FORMAT_RAW)
**	- #LZW_FORMAT_TIFF
**	- #LZW_FORMAT_UNIX
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZW_FORMAT
#define LIBCONFIG_COMPRESS_LZW_FORMAT	LZW_FORMAT_RAW
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZW_FORMAT < LZW_FORMAT_RAW || LIBCONFIG_COMPRESS_LZW_FORMAT > LZW_FORMAT_UNIX)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZW_FORMAT, must be one of: LZW_FORMAT_RAW, LZW_FORMAT_GIF, LZW_FORMAT_TIFF, LZW_FORMAT_UNIX"
#endif

//!@doc This macro sets the maximum LZW code width (in bits), ie: the maximum dictionary size
/*!
**	A larger maximum code width means a larger dictionary, which usually
**	yields better compression ratios for large data (at the cost of memory).
**	The default value is `12` (a 4096-entry dictionary), except for the
**	#LZW_FORMAT_UNIX format, whose default is `16` (like the UNIX `compress`
**	command) - note that, when decompressing #LZW_FORMAT_UNIX streams, the
**	actual maximum code width is read from the stream's header (and it must
**	not exceed this compiled-in maximum, otherwise an error is raised).
**	NOTE: the #LZW_FORMAT_RAW format is only GIF-compatible when this is `12`.
**	NOTE: the #LZW_FORMAT_TIFF format requires this to be exactly `12`.
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZW_MAXBITS
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
#define LIBCONFIG_COMPRESS_LZW_MAXBITS	(16)
#else
#define LIBCONFIG_COMPRESS_LZW_MAXBITS	(12)
#endif
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZW_MAXBITS < 9 || LIBCONFIG_COMPRESS_LZW_MAXBITS > 16)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZW_MAXBITS, must be in range [9, 16]"
#endif
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_TIFF && LIBCONFIG_COMPRESS_LZW_MAXBITS != 12)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZW_MAXBITS: the LZW_FORMAT_TIFF format requires it to be 12"
#endif

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The initial (and minimum) LZW code width, in bits
//!@{
#define LZW_WIDTH_INIT	(9)
//!@}

//!@doc The maximum LZW code width (in bits), as configured by #LIBCONFIG_COMPRESS_LZW_MAXBITS
//!@{
#define LZW_MAXBITS		LIBCONFIG_COMPRESS_LZW_MAXBITS
//!@}

//!@doc The maximum amount of LZW dictionary codes (derived from #LZW_MAXBITS)
//!@{
#define LZW_CODES_MAX	((t_u32)1 << LZW_MAXBITS)
//!@}

//!@doc The special LZW control codes (whether each one is present depends on the format)
//!@{
#define LZW_CODE_CLEAR	(256)	//!< Resets the dictionary to its initial state
#define LZW_CODE_END	(257)	//!< Marks the end of the compressed stream (not present in #LZW_FORMAT_UNIX)
//!@}

//!@doc The size (in bytes) of the header at the start of the compressed stream
//!@{
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
#define LZW_HEADER_SIZE	(3)
#else
#define LZW_HEADER_SIZE	(0)
#endif
//!@}

//!@doc The magic bytes at the very start of the compressed stream (if the format has a header)
//!@{
#if (LIBCONFIG_COMPRESS_LZW_FORMAT == LZW_FORMAT_UNIX)
#define LZW_HEADER_MAGIC_0	(0x1F)
#define LZW_HEADER_MAGIC_1	(0x9D)
#endif
//!@}

//!@doc Macro function which gives the worst-case compressed size, for a given input size `N`
/*!
**	The worst-case scenario for LZW compression is input data in which very few
**	repeated sequences can be found: in this case, most input bytes cost one
**	whole output code each (of up to #LZW_MAXBITS bits). The extra terms account
**	for the control codes, the stream header, and any group padding, if any.
*/
//!@{
#define LZW_COMPRESS_MAXSIZE(N) \
	(LZW_HEADER_SIZE + (((N) + 4) * LZW_MAXBITS) / 8 + ((N) / 16) + 32)
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_LZW_F
#define __LIBCCC_COMPRESS_LZW_F

/*============================================================================*\
||                             LZW: main functions                            ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using LZW compression
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZW_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress.
**
**	@returns
**	A newly allocated buffer, which contains the LZW-compressed equivalent
**	of the given `data` buffer, or `NULL` if an error occurred.
**	NOTE: if `size` is `0`, a valid (non-`NULL`) buffer is still returned
**	(which contains only the stream header and/or control codes).
*/
//!@{
_MALLOC()
t_u8*					LZW_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzwcompress	LZW_Compress
//!@}

//!@doc Decompresses the given LZW-compressed `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZW_FORMAT configuration macro (at compile-time).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The LZW-compressed data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given LZW-compressed `data` buffer, or `NULL` if an error occurred
**	(for instance, if the given `data` is malformed/truncated LZW data).
**	NOTE: if the decompressed size is `0`, a valid (zero-byte, but non-`NULL`)
**	buffer is returned.
*/
//!@{
_MALLOC()
t_u8*						LZW_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzwdecompress		LZW_Decompress
//!@}

/*============================================================================*\
||                            LZW: utility functions                          ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given LZW-compressed `data` buffer
/*!
**	@nonstd
**
**	Parses the given LZW-compressed `data` buffer, checking its validity,
**	and computes the total size which this data would occupy, once decompressed.
**	This function is called by LZW_Decompress() to check the validity of its
**	input, and know how much memory to allocate for the decompressed output.
**	NOTE: unlike its RLE/LZ77 counterparts, this function needs to simulate
**	the LZW dictionary construction, so it performs one (small) temporary
**	memory allocation internally, for dictionary bookkeeping.
**
**	@param	data	The LZW-compressed data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed/truncated LZW data.
*/
//!@{
t_size						LZW_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_lzwdecompsize		LZW_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
