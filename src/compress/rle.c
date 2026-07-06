
#include "libccc/memory.h"
#include "libccc/compress/rle.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	PackBits-style RLE, see "libccc/compress/rle.h" for a description of the format.
**
**	The compressor is greedy: it scans forward, measuring the length of the
**	run of identical bytes at the current position:
**	- any run of 3 or more identical bytes is always encoded as a "repeat run"
**	- a run of exactly 2 identical bytes is only encoded as a "repeat run" if
**		there is no "literal run" currently being accumulated (since breaking
**		a literal run to encode a 2-byte repeat run would gain nothing, and
**		can even produce a larger output, if the literal run must be resumed
**		right after with a new control byte)
*/



t_u8*	RLE_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	dest_i;
	t_size	src_i;
	t_size	literal;
	t_size	run;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_Allocate(size ? RLE_COMPRESS_MAXSIZE(size) : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	dest_i = 0;
	src_i = 0;
	literal = 0; // index at which the currently-accumulating literal run started (only valid if `literal < src_i`)
	while (src_i < size)
	{
		// measure the length of the run of identical bytes at the current position
		run = 1;
		while (src_i + run < size &&
			data[src_i + run] == data[src_i] &&
			run < RLE_RUNLENGTH_MAX)
		{
			run += 1;
		}
		if (run >= 3 || (run == 2 && literal == src_i))
		{	// flush any pending literal run
			while (literal < src_i)
			{
				t_size	amount = src_i - literal;
				if (amount > RLE_RUNLENGTH_MAX)
					amount = RLE_RUNLENGTH_MAX;
				result[dest_i++] = (t_u8)(amount - 1);
				Memory_Copy(result + dest_i, data + literal, amount);
				dest_i += amount;
				literal += amount;
			}
			// write the repeat run: control byte, then the byte to repeat
			result[dest_i++] = (t_u8)(0x101 - run);
			result[dest_i++] = data[src_i];
			src_i += run;
			literal = src_i;
		}
		else
		{	// accumulate into the current literal run
			src_i += run;
		}
	}
	// flush any final pending literal run
	while (literal < src_i)
	{
		t_size	amount = src_i - literal;
		if (amount > RLE_RUNLENGTH_MAX)
			amount = RLE_RUNLENGTH_MAX;
		result[dest_i++] = (t_u8)(amount - 1);
		Memory_Copy(result + dest_i, data + literal, amount);
		dest_i += amount;
		literal += amount;
	}
	// shrink the buffer to fit the actual compressed size
	if (dest_i > 0 && dest_i < RLE_COMPRESS_MAXSIZE(size))
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, dest_i);
		if (tmp != NULL)
			result = tmp;
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}



//! Parses RLE-compressed data, validating it, and computing its decompressed size
static
t_bool	RLE_Parse(t_size* out_size, t_u8 const* data, t_size size)
{
	t_size	result;
	t_size	src_i;
	t_u8	control;

	*out_size = 0;
	result = 0;
	src_i = 0;
	while (src_i < size)
	{
		control = data[src_i++];
		if (control < 0x80) // literal run: `control + 1` bytes follow
		{
			if CCCERROR((src_i + control + 1 > size), ERROR_ILLEGALBYTES,
				"invalid RLE data: literal run is truncated")
				return (FALSE);
			result += (t_size)control + 1;
			src_i += (t_size)control + 1;
		}
		else if (control > 0x80) // repeat run: 1 byte follows, repeated `0x101 - control` times
		{
			if CCCERROR((src_i >= size), ERROR_ILLEGALBYTES,
				"invalid RLE data: repeat run is truncated")
				return (FALSE);
			result += (t_size)(0x101 - control);
			src_i += 1;
		}
		// (control == 0x80 is a no-op control byte: skip it)
	}
	*out_size = result;
	return (TRUE);
}



t_size	RLE_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!RLE_Parse(&result, data, size))
		return (SIZE_ERROR);
	return (result);
}



t_u8*	RLE_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	result_size;
	t_size	dest_i;
	t_size	src_i;
	t_u8	control;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!RLE_Parse(&result_size, data, size))
		return (NULL);
	result = (t_u8*)Memory_Allocate(result_size ? result_size : 1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	dest_i = 0;
	src_i = 0;
	while (src_i < size)
	{
		control = data[src_i++];
		if (control < 0x80) // literal run
		{
			Memory_Copy(result + dest_i, data + src_i, (t_size)control + 1);
			dest_i += (t_size)control + 1;
			src_i += (t_size)control + 1;
		}
		else if (control > 0x80) // repeat run
		{
			Memory_Set(result + dest_i, data[src_i], (t_size)(0x101 - control));
			dest_i += (t_size)(0x101 - control);
			src_i += 1;
		}
	}
	if (dest_size)
		*dest_size = dest_i;
	return (result);
}
