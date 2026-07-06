/*============================================================================*\
||                                            ______________________________  ||
||  libccc/compress/rle.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_COMPRESS_RLE_H
#define __LIBCCC_COMPRESS_RLE_H
/*!@group{libccc_compress_rle,29,libccc/compress/rle.h}
**
**	This header defines compression/decompression functions,
**	using the RLE (Run-Length Encoding) compression algorithm.
**
**	The particular flavor of RLE implemented here is the well-known
**	"PackBits" byte-oriented scheme (originally from Apple MacPaint,
**	also used in TIFF/ILBM files), which encodes data as a series of
**	"runs", where each run begins with a single control byte `c`:
**	- if `c` is in `[0x00, 0x7F]`: "literal run":
**		the next `c + 1` bytes (ie: from 1 to 128 bytes) are copied verbatim.
**	- if `c` is in `[0x81, 0xFF]`: "repeat run":
**		the next byte is repeated `0x101 - c` times (ie: from 2 to 128 times).
**	- if `c` is `0x80`: no-op (this control byte is simply skipped).
**
**	This scheme guarantees a worst-case compressed size of
**	`n + ceil(n / 128)` bytes, for an input of `n` bytes
**	(worst case being input data with no repeated byte sequences).
**
**	@see
**	- https://en.wikipedia.org/wiki/Run-length_encoding
**	- https://en.wikipedia.org/wiki/PackBits
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_COMPRESS_RLE_T
#define __LIBCCC_COMPRESS_RLE_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc The maximum amount of bytes which a single RLE run can encode
//!@{
#define RLE_RUNLENGTH_MAX	(128)
//!@}

//!@doc Macro function which gives the worst-case compressed size, for a given input size `N`
/*!
**	The worst-case scenario for PackBits RLE compression is input data which
**	contains no repeating byte sequences whatsoever: in this case, the data
**	will be encoded as a series of maximum-length "literal runs", each of which
**	costs 1 extra control byte per #RLE_RUNLENGTH_MAX bytes of input data.
*/
//!@{
#define RLE_COMPRESS_MAXSIZE(N) \
	((N) + (((N) + (RLE_RUNLENGTH_MAX - 1)) / RLE_RUNLENGTH_MAX))
//!@}

#endif
#ifndef __LIBCCC_COMPRESS_RLE_F
#define __LIBCCC_COMPRESS_RLE_F

/*============================================================================*\
||                             RLE: main functions                            ||
\*============================================================================*/

//!@doc Compresses the given `data` buffer (of `size` bytes), using RLE compression
/*!
**	@nonstd
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned compressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The data buffer to compress.
**	@param	size		The amount of bytes of `data` to compress.
**
**	@returns
**	A newly allocated buffer, which contains the RLE-compressed equivalent
**	of the given `data` buffer, or `NULL` if an error occurred.
**	NOTE: if `size` is `0`, a valid (zero-byte, but non-`NULL`) buffer is returned.
*/
//!@{
_MALLOC()
t_u8*					RLE_Compress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_rlecompress	RLE_Compress
//!@}

//!@doc Decompresses the given RLE-compressed `data` buffer (of `size` bytes)
/*!
**	@nonstd
**
**	@param	dest_size	The address in which to store the size (in bytes) of
**						the returned decompressed buffer (optional, can be `NULL`).
**						Will be set to `0` if any error occurs.
**	@param	data		The RLE-compressed data buffer to decompress.
**	@param	size		The amount of bytes of `data` to decompress.
**
**	@returns
**	A newly allocated buffer, which contains the decompressed equivalent
**	of the given RLE-compressed `data` buffer, or `NULL` if an error occurred
**	(for instance, if the given `data` is malformed/truncated RLE data).
**	NOTE: if `size` is `0`, a valid (zero-byte, but non-`NULL`) buffer is returned.
*/
//!@{
_MALLOC()
t_u8*					RLE_Decompress(t_size* dest_size, t_u8 const* data, t_size size);
#define c_rledecompress	RLE_Decompress
//!@}

/*============================================================================*\
||                            RLE: utility functions                          ||
\*============================================================================*/

//!@doc Returns the decompressed size for the given RLE-compressed `data` buffer
/*!
**	@nonstd
**
**	Parses the given RLE-compressed `data` buffer, checking its validity,
**	and computes the total size which this data would occupy, once decompressed.
**	This function does not allocate anything, and is called by RLE_Decompress()
**	to check the validity of its input, and know how much memory to allocate.
**
**	@param	data	The RLE-compressed data buffer to parse.
**	@param	size	The amount of bytes of `data` to parse.
**
**	@returns
**	The size (in bytes) which the given `data` will occupy once decompressed,
**	or `SIZE_ERROR` if the given `data` buffer is malformed/truncated RLE data.
*/
//!@{
t_size						RLE_GetDecompressedSize(t_u8 const* data, t_size size);
#define c_rledecompsize		RLE_GetDecompressedSize
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
