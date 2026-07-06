/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/lzma.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_LZMA_H
#define __LIBCCC_COMPRESS_LZMA_H
/*!@group{libccc_compress_lzma,29,libccc/compress/lzma.h}
**
**	This header defines compression/decompression functions,
**	using the LZMA (Lempel-Ziv-Markov chain) compression algorithm.
**
**	LZMA combines an LZ77-style "sliding window" match model (with a very
**	large window, and a set of 4 "repeated distance" registers) with an
**	adaptive binary range coder (a form of arithmetic coding): every bit of
**	every symbol is encoded according to a context-dependent probability,
**	and each probability adapts as the stream is processed (symmetrically,
**	on both the compression and the decompression side). This gives LZMA
**	some of the best compression ratios of any general-purpose algorithm
**	(it is the algorithm behind the `.7z`, `.xz` and `.lzma` file formats).
**
**	The exact stream layout can be configured at compile-time, via the
**	#LIBCONFIG_COMPRESS_LZMA_FORMAT macro (see below).
**
**	NOTE: unlike the other libccc compression algorithms, no
**	`LZMA_COMPRESS_MAXSIZE()` macro is provided: because the range coder is
**	adaptive, there is no simple, tight worst-case output size bound - the
**	LZMA_Compress() function manages its own output buffer growth internally.
**
**	@see
**	- https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Markov_chain_algorithm
**	- https://github.com/jljusten/LZMA-SDK/blob/master/DOC/lzma-specification.txt
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_LZMA_T
#define __LIBCCC_COMPRESS_LZMA_T

/*============================================================================*\
||                                Configuration                               ||
\*============================================================================*/

//!@doc The possible values for the #LIBCONFIG_COMPRESS_LZMA_FORMAT configuration macro
//!@{

//! The standalone `.lzma` file format (also known as "LZMA-alone")
/*!
**	The compressed stream begins with a 13-byte header:
**	- 1 byte: the model properties (encoding the `lc`/`lp`/`pb` parameters, see below)
**	- 4 bytes: the dictionary size (unsigned 32-bit little-endian)
**	- 8 bytes: the total decompressed size (unsigned 64-bit little-endian),
**		or `0xFFFFFFFFFFFFFFFF` if unknown (in which case the stream is
**		terminated by an explicit "end of stream" marker instead)
**	This is the format produced/consumed by the `lzma` command-line tool,
**	by `xz --format=lzma`, and by most LZMA libraries (eg: python's `lzma`
**	module, with `format=lzma.FORMAT_ALONE`).
*/
#define LZMA_FORMAT_ALONE	(0)

//! Headerless "raw" LZMA stream
/*!
**	The raw LZMA bit-stream, with no header: the model properties are instead
**	fixed at compile-time (via the `LIBCONFIG_COMPRESS_LZMA_*` macros below),
**	and must be known by both sides. Since the decompressed size is not stored
**	anywhere, the stream is always terminated by an "end of stream" marker.
*/
#define LZMA_FORMAT_RAW		(1)

//!@}

//!@doc This macro sets the LZMA compressed stream format used by the LZMA_* functions
/*!
**	This macro configures which binary stream format is used by the
**	LZMA_Compress(), LZMA_Decompress() and LZMA_GetDecompressedSize() functions.
**	The possible values are:
**	- #LZMA_FORMAT_ALONE (this is the default)
**	- #LZMA_FORMAT_RAW
**	NOTE: unlike the other libccc compression algorithms, the default here is
**	the header-based format, since it is the universally-exchanged form of LZMA
**	(a raw LZMA stream is not self-describing: its model parameters must be
**	communicated out-of-band).
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZMA_FORMAT
#define LIBCONFIG_COMPRESS_LZMA_FORMAT	LZMA_FORMAT_ALONE
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT < LZMA_FORMAT_ALONE || LIBCONFIG_COMPRESS_LZMA_FORMAT > LZMA_FORMAT_RAW)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZMA_FORMAT, must be one of: LZMA_FORMAT_ALONE, LZMA_FORMAT_RAW"
#endif

//!@doc These macros set the LZMA probability model parameters (`lc`, `lp` and `pb`)
/*!
**	These three parameters configure how much context is used by the
**	adaptive probability model (they are the `lc`/`lp`/`pb` parameters
**	found in every LZMA implementation):
**	- `LC` is the number of "literal context" bits: how many high bits of the
**		previous byte are used as context when encoding a literal byte (0-8)
**	- `LP` is the number of "literal position" bits: how many low bits of the
**		current position are used as context when encoding a literal byte (0-4)
**	- `PB` is the number of "position" bits: how many low bits of the current
**		position are used as context when encoding match/literal decisions (0-4)
**	The defaults (`lc=3, lp=0, pb=2`) are the standard LZMA defaults, and are
**	suitable for most data. (For the #LZMA_FORMAT_ALONE format, these only
**	affect compression: when decompressing, the values are read from the
**	stream header. For #LZMA_FORMAT_RAW, both sides use these macros.)
**	NOTE: most LZMA implementations (eg: liblzma/xz) require `lc + lp <= 4`.
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZMA_LC
#define LIBCONFIG_COMPRESS_LZMA_LC	(3)
#endif
#ifndef LIBCONFIG_COMPRESS_LZMA_LP
#define LIBCONFIG_COMPRESS_LZMA_LP	(0)
#endif
#ifndef LIBCONFIG_COMPRESS_LZMA_PB
#define LIBCONFIG_COMPRESS_LZMA_PB	(2)
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZMA_LC < 0 || LIBCONFIG_COMPRESS_LZMA_LC > 8)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZMA_LC, must be in range [0, 8]"
#endif
#if (LIBCONFIG_COMPRESS_LZMA_LP < 0 || LIBCONFIG_COMPRESS_LZMA_LP > 4)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZMA_LP, must be in range [0, 4]"
#endif
#if (LIBCONFIG_COMPRESS_LZMA_PB < 0 || LIBCONFIG_COMPRESS_LZMA_PB > 4)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZMA_PB, must be in range [0, 4]"
#endif

//!@doc This macro sets the LZMA dictionary size (in bytes), ie: the sliding window size
/*!
**	This is the maximum distance which the compressor's match-finder will
**	search backwards: larger values usually yield better compression ratios
**	for large data, at the cost of memory usage during compression.
**	NOTE: this only affects compression: the decompressor accepts any distance
**	(within the bounds of the data which has been decompressed so far).
*/
//!@{
#ifndef LIBCONFIG_COMPRESS_LZMA_DICTSIZE
#define LIBCONFIG_COMPRESS_LZMA_DICTSIZE	(0x100000)
#endif
//!@}
#if (LIBCONFIG_COMPRESS_LZMA_DICTSIZE < 0x1000 || LIBCONFIG_COMPRESS_LZMA_DICTSIZE > 0x10000000)
#error "Invalid value selected for LIBCONFIG_COMPRESS_LZMA_DICTSIZE, must be in range [0x1000, 0x10000000]"
#endif

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The size (in bytes) of the header at the start of the compressed stream
//!@{
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_ALONE)
#define LZMA_HEADER_SIZE	(13)
#else
#define LZMA_HEADER_SIZE	(0)
#endif
//!@}

//!@doc The value of the "properties" byte (the first byte of the #LZMA_FORMAT_ALONE header)
//!@{
#define LZMA_PROPSBYTE	\
	((LIBCONFIG_COMPRESS_LZMA_PB * 5 + LIBCONFIG_COMPRESS_LZMA_LP) * 9 + LIBCONFIG_COMPRESS_LZMA_LC)
//!@}

//!@doc The minimum/maximum length (in bytes) which a single LZMA match can encode
//!@{
#define LZMA_MATCHLENGTH_MIN	(2)
#define LZMA_MATCHLENGTH_MAX	(273)
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_LZMA_F
#define __LIBCCC_COMPRESS_LZMA_F

/*============================================================================*\
||                            LZMA: main functions                            ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using LZMA compression
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZMA_FORMAT configuration macro (at compile-time).
**	For the #LZMA_FORMAT_ALONE format, the header always stores the actual
**	decompressed size (never the "unknown size" value).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress.
**
**	@returns
**	A newly allocated buffer, which contains the LZMA-compressed equivalent
**	of the given `data` buffer, or `NULL` if an error occurred.
**	NOTE: if `size` is `0`, a valid (non-`NULL`) buffer is still returned
**	(which contains only the stream header and/or range coder flush bytes).
*/
//!@{
_MALLOC()
t_u8*					LZMA_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzmacompress	LZMA_Compress
//!@}

//!@doc Decompresses the given LZMA-compressed `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	The binary format of the compressed stream depends on the value of the
**	#LIBCONFIG_COMPRESS_LZMA_FORMAT configuration macro (at compile-time).
**	Both "known size" and "unknown size" (end-marker-terminated) streams
**	are supported, as are any valid `lc`/`lp`/`pb` model properties (for
**	the #LZMA_FORMAT_ALONE format, these are read from the stream header).
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The LZMA-compressed data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given LZMA-compressed `data` buffer, or `NULL` if an error occurred
**	(for instance, if the given `data` is malformed/truncated LZMA data).
**	NOTE: if the decompressed size is `0`, a valid (zero-byte, but non-`NULL`)
**	buffer is returned.
*/
//!@{
_MALLOC()
t_u8*						LZMA_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_lzmadecompress	LZMA_Decompress
//!@}

/*============================================================================*\
||                           LZMA: utility functions                          ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given LZMA-compressed `data` buffer
/*!
**	@nonstd
**
**	For #LZMA_FORMAT_ALONE streams which store their decompressed size in the
**	stream header, this simply validates the header and returns that size
**	(without checking the validity of the whole stream - that full validation
**	happens during LZMA_Decompress(), which checks every decoded symbol).
**	For "unknown size" streams (and for the #LZMA_FORMAT_RAW format), the
**	decompressed size is not stored anywhere - and, because the LZMA
**	probability model depends on the actual decompressed bytes, the only way
**	to compute the size is to fully decompress the stream: in this case, this
**	function does exactly that internally (and frees the result immediately),
**	so it can be as expensive as a full LZMA_Decompress() call.
**
**	@param	data	The LZMA-compressed data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed LZMA data.
*/
//!@{
t_size						LZMA_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_lzmadecompsize	LZMA_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
