
#include "libccc/memory.h"
#include "libccc/compress/lzma.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	See "libccc/compress/lzma.h" for a description of the compressed stream
**	format(s), which can be selected via `LIBCONFIG_COMPRESS_LZMA_FORMAT`.
**
**	This implementation follows the official LZMA specification (the
**	`lzma-specification.txt` + `LzmaSpec.cpp` reference decoder, by Igor Pavlov):
**	all probability contexts, state transitions and range coder operations
**	mirror the reference behavior exactly, so that the streams produced here
**	are interoperable with standard LZMA tools (xz, 7-zip, liblzma, etc).
**
**	A quick overview of how LZMA works:
**	- The data is modeled as a sequence of "packets": literals (a single byte),
**		matches (a `(distance, length)` back-reference, like LZ77), "rep" matches
**		(a match re-using one of the last 4 distances, stored in the `reps[]`
**		registers), and "short rep" matches (a 1-byte match at distance `reps[0]`).
**	- Every decision bit and symbol bit of these packets is encoded by an
**		adaptive binary range coder: each bit has a probability (from a large
**		set of context-dependent probability counters, all initialized to 1/2),
**		which is updated after each encoded/decoded bit. Highly predictable
**		bits therefore cost much less than one bit of output each.
**	- A 12-state state machine (tracking the types of the last few packets)
**		provides further context for the probability model.
*/

#define LZMA_LC	LIBCONFIG_COMPRESS_LZMA_LC
#define LZMA_LP	LIBCONFIG_COMPRESS_LZMA_LP
#define LZMA_PB	LIBCONFIG_COMPRESS_LZMA_PB

#define LZMA_PROB_BITS	(11)	//!< probabilities are 11-bit fixed-point values (0 to 2048)
#define LZMA_PROB_INIT	(1024)	//!< initial probability: 1024/2048, ie: one half
#define LZMA_PROB_MOVE	(5)		//!< adaptation speed of the probabilities
#define LZMA_RC_TOP		((t_u32)1 << 24)

#define LZMA_STATES			(12)
#define LZMA_POSSTATES_MAX	(16)
#define LZMA_LENTOPOSSTATES	(4)
#define LZMA_DIST_SLOTS		(64)
#define LZMA_DIST_MODEL_END	(14)
#define LZMA_ALIGN_BITS		(4)
#define LZMA_MARKER			((t_u32)-1)	//!< the "end of stream" marker is encoded as this distance value

//! The set of adaptive probability counters ("the model"), shared by the encoder and decoder
/*!
**	NOTE: this struct must contain only `t_prob` arrays (no pointers/padding),
**	since it is initialized by looping over it as a flat `t_prob` array.
**	The literal probabilities are kept separate, since their amount depends
**	on the `lc`/`lp` parameters (`0x300 << (lc + lp)` counters).
*/
typedef t_u16	t_prob;
typedef struct lzma_probs
{
	t_prob	is_match	[LZMA_STATES << 4];	// [state][pos_state]
	t_prob	is_rep		[LZMA_STATES];
	t_prob	is_rep_g0	[LZMA_STATES];
	t_prob	is_rep_g1	[LZMA_STATES];
	t_prob	is_rep_g2	[LZMA_STATES];
	t_prob	is_rep0_long[LZMA_STATES << 4];	// [state][pos_state]
	t_prob	dist_slot	[LZMA_LENTOPOSSTATES][LZMA_DIST_SLOTS];
	t_prob	dist_special[115];	// 1 + kNumFullDistances(128) - kEndPosModelIndex(14)
	t_prob	dist_align	[1 << LZMA_ALIGN_BITS];
	t_prob	len_choice, len_choice2;
	t_prob	len_low		[LZMA_POSSTATES_MAX][8];
	t_prob	len_mid		[LZMA_POSSTATES_MAX][8];
	t_prob	len_high	[256];
	t_prob	rep_choice, rep_choice2;
	t_prob	rep_low		[LZMA_POSSTATES_MAX][8];
	t_prob	rep_mid		[LZMA_POSSTATES_MAX][8];
	t_prob	rep_high	[256];
}	s_lzma_probs;

static
void	LZMA_Probs_Init(s_lzma_probs* probs, t_prob* literal, t_u32 literal_count)
{
	t_prob*	p = (t_prob*)probs;
	t_u32	i;
	for (i = 0; i < sizeof(s_lzma_probs) / sizeof(t_prob); ++i)
		p[i] = LZMA_PROB_INIT;
	for (i = 0; i < literal_count; ++i)
		literal[i] = LZMA_PROB_INIT;
}

//! state-machine transitions, after each packet type
#define LZMA_STATE_LITERAL(ST)	((ST) < 4 ? 0 : ((ST) < 10 ? (ST) - 3 : (ST) - 6))
#define LZMA_STATE_MATCH(ST)	((ST) < 7 ? 7 : 10)
#define LZMA_STATE_REP(ST)		((ST) < 7 ? 8 : 11)
#define LZMA_STATE_SHORTREP(ST)	((ST) < 7 ? 9 : 11)



/*============================================================================*\
||                                Range decoder                               ||
\*============================================================================*/

typedef struct lzma_rc_dec
{
	t_u8 const*	data;
	t_size	size;
	t_size	pos;
	t_u32	range;
	t_u32	code;
	t_bool	truncated;	//!< set if the decoder ever needed a byte beyond the end of the input
}	s_lzma_rcdec;

static
t_bool	LZMA_RCDec_Init(s_lzma_rcdec* rc, t_u8 const* data, t_size size, t_size pos)
{
	rc->data = data;
	rc->size = size;
	rc->truncated = FALSE;
	rc->range = (t_u32)-1;
	if (pos + 5 > size || data[pos] != 0)
		return (FALSE); // a valid LZMA stream always begins with a zero byte
	rc->code = ((t_u32)data[pos + 1] << 24) | ((t_u32)data[pos + 2] << 16) | ((t_u32)data[pos + 3] << 8) | data[pos + 4];
	rc->pos = pos + 5;
	return (TRUE);
}

static
void	LZMA_RCDec_Normalize(s_lzma_rcdec* rc)
{
	if (rc->range < LZMA_RC_TOP)
	{
		t_u8	byte = 0;
		if (rc->pos < rc->size)
			byte = rc->data[rc->pos];
		else
			rc->truncated = TRUE;
		rc->pos += 1;
		rc->range <<= 8;
		rc->code = (rc->code << 8) | byte;
	}
}

static
t_uint	LZMA_RCDec_Bit(s_lzma_rcdec* rc, t_prob* prob)
{
	t_u32	v = *prob;
	t_u32	bound = (rc->range >> LZMA_PROB_BITS) * v;
	t_uint	bit;
	if (rc->code < bound)
	{
		v += (((t_u32)1 << LZMA_PROB_BITS) - v) >> LZMA_PROB_MOVE;
		rc->range = bound;
		bit = 0;
	}
	else
	{
		v -= v >> LZMA_PROB_MOVE;
		rc->code -= bound;
		rc->range -= bound;
		bit = 1;
	}
	*prob = (t_prob)v;
	LZMA_RCDec_Normalize(rc);
	return (bit);
}

static
t_u32	LZMA_RCDec_Direct(s_lzma_rcdec* rc, t_uint amount)
{
	t_u32	result = 0;
	t_u32	t;
	while (amount--)
	{
		rc->range >>= 1;
		rc->code -= rc->range;
		t = 0 - (rc->code >> 31);
		rc->code += rc->range & t;
		if (rc->code == rc->range)
			rc->truncated = TRUE; // corrupted stream, per the LZMA specification
		LZMA_RCDec_Normalize(rc);
		result = (result << 1) + (t + 1);
	}
	return (result);
}

static
t_u32	LZMA_RCDec_BitTree(s_lzma_rcdec* rc, t_prob* probs, t_uint amount)
{
	t_u32	m = 1;
	while (amount--)
		m = (m << 1) + LZMA_RCDec_Bit(rc, &probs[m]);
	return (m);	// NOTE: the caller subtracts `1 << amount`
}

static
t_u32	LZMA_RCDec_BitTreeReverse(s_lzma_rcdec* rc, t_prob* probs, t_uint amount)
{
	t_u32	m = 1;
	t_u32	result = 0;
	t_uint	bit;
	for (t_uint i = 0; i < amount; ++i)
	{
		bit = LZMA_RCDec_Bit(rc, &probs[m]);
		m = (m << 1) + bit;
		result |= ((t_u32)bit << i);
	}
	return (result);
}

//! Decodes a match length (the caller adds `LZMA_MATCHLENGTH_MIN`)
static
t_u32	LZMA_RCDec_Length(
	s_lzma_rcdec* rc,
	t_prob* choice,
	t_prob* choice2,
	t_prob (*low)[8],
	t_prob (*mid)[8],
	t_prob* high,
	t_uint pos_state)
{
	if (LZMA_RCDec_Bit(rc, choice) == 0)
		return (LZMA_RCDec_BitTree(rc, low[pos_state], 3) - 8);
	if (LZMA_RCDec_Bit(rc, choice2) == 0)
		return (8 + LZMA_RCDec_BitTree(rc, mid[pos_state], 3) - 8);
	return (16 + LZMA_RCDec_BitTree(rc, high, 8) - 256);
}

//! Decodes a match distance value (the real distance is this value, plus one)
static
t_u32	LZMA_RCDec_Distance(s_lzma_rcdec* rc, s_lzma_probs* probs, t_u32 length)
{
	t_u32	len_state = (length < LZMA_LENTOPOSSTATES ? length : LZMA_LENTOPOSSTATES - 1);
	t_u32	slot = LZMA_RCDec_BitTree(rc, probs->dist_slot[len_state], 6) - LZMA_DIST_SLOTS;
	t_u32	dist;
	t_uint	direct;
	if (slot < 4)
		return (slot);
	direct = (slot >> 1) - 1;
	dist = (2 | (slot & 1)) << direct;
	if (slot < LZMA_DIST_MODEL_END)
		dist += LZMA_RCDec_BitTreeReverse(rc, probs->dist_special + dist - slot, direct);
	else
	{
		dist += LZMA_RCDec_Direct(rc, direct - LZMA_ALIGN_BITS) << LZMA_ALIGN_BITS;
		dist += LZMA_RCDec_BitTreeReverse(rc, probs->dist_align, LZMA_ALIGN_BITS);
	}
	return (dist);
}



/*============================================================================*\
||                                Decompression                               ||
\*============================================================================*/

//! Decodes an entire LZMA stream body (everything after the header, if any)
static
t_u8*	LZMA_DecodeBody(
	t_size* out_size,
	t_u8 const* data,
	t_size size,
	t_size start,
	t_uint lc,
	t_uint lp,
	t_uint pb,
	t_bool size_known,
	t_size expected)
{
	s_lzma_probs	probs;
	s_lzma_rcdec	rc;
	t_prob*	literal;
	t_u32	literal_count;
	t_u8*	result;
	t_size	capacity;
	t_size	produced;
	t_u32	reps[4] = {0, 0, 0, 0};
	t_uint	state = 0;
	t_uint	pos_state;
	t_u32	length;
	t_u32	dist;
	t_bool	valid = FALSE;

	*out_size = 0;
	literal_count = ((t_u32)0x300 << (lc + lp));
	literal = (t_prob*)Memory_Allocate(literal_count * sizeof(t_prob));
	if CCCERROR((literal == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	capacity = (size_known ? (expected ? expected : 1) : (size * 4 + 64));
	result = (t_u8*)Memory_Allocate(capacity);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(literal);
		return (NULL);
	}
	LZMA_Probs_Init(&probs, literal, literal_count);
	if CCCERROR((!LZMA_RCDec_Init(&rc, data, size, start)), ERROR_ILLEGALBYTES,
		"invalid LZMA data: stream is too short, or does not begin with a zero byte")
		goto failure;
	produced = 0;
	while (!size_known || produced < expected)
	{
		if (size_known && produced == expected)
			break;
		if CCCERROR((rc.truncated), ERROR_ILLEGALBYTES,
			"invalid LZMA data: stream is truncated or corrupted")
			goto failure;
		pos_state = (produced & (((t_uint)1 << pb) - 1));
		if (LZMA_RCDec_Bit(&rc, &probs.is_match[(state << 4) + pos_state]) == 0)
		{	// literal packet
			t_u8	prev_byte = (produced ? result[produced - 1] : 0);
			t_u32	lit_state = (((produced & (((t_u32)1 << lp) - 1)) << lc) + (prev_byte >> (8 - lc)));
			t_prob*	p = literal + (t_u32)0x300 * lit_state;
			t_u32	symbol = 1;
			if (!size_known && produced >= capacity)
			{	// grow the output buffer
				t_u8*	tmp;
				if CCCERROR((capacity > ((t_size)-1) / 2), ERROR_LENGTH2LARGE, NULL)
					goto failure;
				tmp = (t_u8*)Memory_Reallocate(result, capacity * 2);
				if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
					goto failure;
				result = tmp;
				capacity *= 2;
			}
			if (state >= 7)
			{	// "matched" literal: the byte at distance `reps[0] + 1` provides extra context
				t_u8	match_byte = result[produced - reps[0] - 1];
				t_uint	match_bit;
				t_uint	bit;
				do
				{
					match_bit = ((match_byte >> 7) & 1);
					match_byte <<= 1;
					bit = LZMA_RCDec_Bit(&rc, &p[((1 + match_bit) << 8) + symbol]);
					symbol = (symbol << 1) | bit;
					if (match_bit != bit)
						break;
				}
				while (symbol < 0x100);
			}
			while (symbol < 0x100)
				symbol = (symbol << 1) | LZMA_RCDec_Bit(&rc, &p[symbol]);
			result[produced++] = (t_u8)symbol;
			state = LZMA_STATE_LITERAL(state);
			continue;
		}
		if (LZMA_RCDec_Bit(&rc, &probs.is_rep[state]) != 0)
		{	// "rep" packet: re-use one of the last 4 distances
			if CCCERROR((produced == 0), ERROR_ILLEGALBYTES,
				"invalid LZMA data: rep-match packet at the very start of the stream")
				goto failure;
			if (LZMA_RCDec_Bit(&rc, &probs.is_rep_g0[state]) == 0)
			{
				if (LZMA_RCDec_Bit(&rc, &probs.is_rep0_long[(state << 4) + pos_state]) == 0)
				{	// "short rep" packet: a single byte, at distance `reps[0] + 1`
					state = LZMA_STATE_SHORTREP(state);
					if (!size_known && produced >= capacity)
					{
						t_u8*	tmp;
						if CCCERROR((capacity > ((t_size)-1) / 2), ERROR_LENGTH2LARGE, NULL)
							goto failure;
						tmp = (t_u8*)Memory_Reallocate(result, capacity * 2);
						if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
							goto failure;
						result = tmp;
						capacity *= 2;
					}
					result[produced] = result[produced - reps[0] - 1];
					produced += 1;
					continue;
				}
			}
			else
			{
				if (LZMA_RCDec_Bit(&rc, &probs.is_rep_g1[state]) == 0)
					dist = reps[1];
				else
				{
					if (LZMA_RCDec_Bit(&rc, &probs.is_rep_g2[state]) == 0)
						dist = reps[2];
					else
					{
						dist = reps[3];
						reps[3] = reps[2];
					}
					reps[2] = reps[1];
				}
				reps[1] = reps[0];
				reps[0] = dist;
			}
			length = LZMA_RCDec_Length(&rc,
				&probs.rep_choice, &probs.rep_choice2, probs.rep_low, probs.rep_mid, probs.rep_high,
				pos_state) + LZMA_MATCHLENGTH_MIN;
			state = LZMA_STATE_REP(state);
		}
		else
		{	// match packet: a new distance
			reps[3] = reps[2];
			reps[2] = reps[1];
			reps[1] = reps[0];
			length = LZMA_RCDec_Length(&rc,
				&probs.len_choice, &probs.len_choice2, probs.len_low, probs.len_mid, probs.len_high,
				pos_state) + LZMA_MATCHLENGTH_MIN;
			reps[0] = LZMA_RCDec_Distance(&rc, &probs, length - LZMA_MATCHLENGTH_MIN);
			if (reps[0] == LZMA_MARKER)
			{	// "end of stream" marker
				if CCCERROR((size_known && produced != expected), ERROR_ILLEGALBYTES,
					"invalid LZMA data: stream ends before the announced decompressed size was reached")
					goto failure;
				if CCCERROR((rc.code != 0), ERROR_ILLEGALBYTES,
					"invalid LZMA data: stream is corrupted (range coder check failed at the end marker)")
					goto failure;
				valid = TRUE;
				goto finish;
			}
			state = LZMA_STATE_MATCH(state);
		}
		// copy `length` bytes from distance `reps[0] + 1`
		if CCCERROR(((t_u64)reps[0] + 1 > produced), ERROR_ILLEGALBYTES,
			"invalid LZMA data: match distance points before the start of the data")
			goto failure;
		if CCCERROR((size_known && produced + length > expected), ERROR_ILLEGALBYTES,
			"invalid LZMA data: stream decompresses to more data than its header announces")
			goto failure;
		if (!size_known && produced + length > capacity)
		{
			t_u8*	tmp;
			t_size	needed = produced + length;
			if CCCERROR((capacity > ((t_size)-1) / 2), ERROR_LENGTH2LARGE, NULL)
				goto failure;
			capacity *= 2;
			if (capacity < needed)
				capacity = needed;
			tmp = (t_u8*)Memory_Reallocate(result, capacity);
			if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
				goto failure;
			result = tmp;
		}
		while (length--)
		{
			result[produced] = result[produced - reps[0] - 1];
			produced += 1;
		}
	}
	if CCCERROR((rc.truncated), ERROR_ILLEGALBYTES,
		"invalid LZMA data: stream is truncated or corrupted")
		goto failure;
	valid = TRUE;
finish:
	Memory_Deallocate(literal);
	*out_size = produced;
	if (!size_known && produced > 0)
	{	// shrink the grown buffer to its final size
		t_u8*	tmp = (t_u8*)Memory_Reallocate(result, produced);
		if (tmp != NULL)
			result = tmp;
	}
	return (result);
failure:
	if (!valid)
	{
		Memory_Deallocate(literal);
		Memory_Deallocate(result);
	}
	return (NULL);
}

//! Parses the stream header (if any); returns `FALSE` if it is invalid
static
t_bool	LZMA_ParseHeader(
	t_u8 const* data,
	t_size size,
	t_uint* lc,
	t_uint* lp,
	t_uint* pb,
	t_bool* size_known,
	t_u64* expected)
{
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_ALONE)
	t_uint	props;
	t_u64	usize = 0;
	if CCCERROR((size < LZMA_HEADER_SIZE), ERROR_ILLEGALBYTES,
		"invalid LZMA data: too short to contain the stream header")
		return (FALSE);
	props = data[0];
	if CCCERROR((props >= 225), ERROR_ILLEGALBYTES,
		"invalid LZMA data: invalid model properties byte in the stream header")
		return (FALSE);
	*lc = (props % 9);
	*lp = ((props / 9) % 5);
	*pb = (props / 45);
	for (t_uint i = 0; i < 8; ++i)
		usize |= ((t_u64)data[5 + i] << (i * 8));
	*size_known = (usize != (t_u64)-1);
	if CCCERROR((*size_known && usize > (t_size)-1), ERROR_LENGTH2LARGE,
		"invalid LZMA data: the announced decompressed size does not fit in a `t_size`")
		return (FALSE);
	*expected = usize;
	return (TRUE);
#else
	(void)data;
	(void)size;
	*lc = LZMA_LC;
	*lp = LZMA_LP;
	*pb = LZMA_PB;
	*size_known = FALSE;
	*expected = 0;
	return (TRUE);
#endif
}

t_u8*	LZMA_Decompress(t_size* dest_size, t_u8 const* data, t_size size)
{
	t_u8*	result;
	t_size	result_size;
	t_uint	lc, lp, pb;
	t_bool	size_known;
	t_u64	expected;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if (!LZMA_ParseHeader(data, size, &lc, &lp, &pb, &size_known, &expected))
		return (NULL);
	result = LZMA_DecodeBody(&result_size, data, size, LZMA_HEADER_SIZE,
		lc, lp, pb, size_known, (t_size)expected);
	if (result == NULL)
		return (NULL);
	if (dest_size)
		*dest_size = result_size;
	return (result);
}

t_size	LZMA_GetDecompressedSize(t_u8 const* data, t_size size)
{
	t_uint	lc, lp, pb;
	t_bool	size_known;
	t_u64	expected;
	t_u8*	decoded;
	t_size	result;

	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (SIZE_ERROR);
	if (!LZMA_ParseHeader(data, size, &lc, &lp, &pb, &size_known, &expected))
		return (SIZE_ERROR);
	if (size_known)
		return ((t_size)expected);
	// unknown-size stream: the only way to know the size is to fully decode it
	decoded = LZMA_DecodeBody(&result, data, size, LZMA_HEADER_SIZE,
		lc, lp, pb, FALSE, 0);
	if (decoded == NULL)
		return (SIZE_ERROR);
	Memory_Deallocate(decoded);
	return (result);
}



/*============================================================================*\
||                                Range encoder                               ||
\*============================================================================*/

typedef struct lzma_rc_enc
{
	t_u8*	dest;
	t_size	capacity;
	t_size	pos;
	t_u64	low;
	t_u32	range;
	t_u8	cache;
	t_size	cache_size;
	t_bool	failed;	//!< set if an output buffer growth reallocation failed
}	s_lzma_rcenc;

static
void	LZMA_RCEnc_WriteByte(s_lzma_rcenc* rc, t_u8 byte)
{
	if (rc->pos >= rc->capacity)
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(rc->dest, rc->capacity * 2);
		if (tmp == NULL)
		{
			rc->failed = TRUE;
			rc->pos = 0; // stop writing (the error is reported by the caller)
			return;
		}
		rc->dest = tmp;
		rc->capacity *= 2;
	}
	rc->dest[rc->pos++] = byte;
}

static
void	LZMA_RCEnc_ShiftLow(s_lzma_rcenc* rc)
{
	if ((t_u32)rc->low < (t_u32)0xFF000000 || (t_uint)(rc->low >> 32) != 0)
	{
		t_u8	temp = rc->cache;
		do
		{
			LZMA_RCEnc_WriteByte(rc, (t_u8)(temp + (t_u8)(rc->low >> 32)));
			temp = 0xFF;
		}
		while (--rc->cache_size != 0);
		rc->cache = (t_u8)(rc->low >> 24);
	}
	rc->cache_size += 1;
	rc->low = ((t_u32)rc->low) << 8;
}

static
void	LZMA_RCEnc_Bit(s_lzma_rcenc* rc, t_prob* prob, t_uint bit)
{
	t_u32	v = *prob;
	t_u32	bound = (rc->range >> LZMA_PROB_BITS) * v;
	if (bit == 0)
	{
		v += (((t_u32)1 << LZMA_PROB_BITS) - v) >> LZMA_PROB_MOVE;
		rc->range = bound;
	}
	else
	{
		v -= v >> LZMA_PROB_MOVE;
		rc->low += bound;
		rc->range -= bound;
	}
	*prob = (t_prob)v;
	while (rc->range < LZMA_RC_TOP)
	{
		rc->range <<= 8;
		LZMA_RCEnc_ShiftLow(rc);
	}
}

static
void	LZMA_RCEnc_Direct(s_lzma_rcenc* rc, t_u32 value, t_uint amount)
{
	while (amount--)
	{
		rc->range >>= 1;
		if ((value >> amount) & 1)
			rc->low += rc->range;
		while (rc->range < LZMA_RC_TOP)
		{
			rc->range <<= 8;
			LZMA_RCEnc_ShiftLow(rc);
		}
	}
}

static
void	LZMA_RCEnc_Flush(s_lzma_rcenc* rc)
{
	for (t_uint i = 0; i < 5; ++i)
		LZMA_RCEnc_ShiftLow(rc);
}

static
void	LZMA_RCEnc_BitTree(s_lzma_rcenc* rc, t_prob* probs, t_uint amount, t_u32 symbol)
{
	t_u32	m = 1;
	t_uint	bit;
	while (amount--)
	{
		bit = ((symbol >> amount) & 1);
		LZMA_RCEnc_Bit(rc, &probs[m], bit);
		m = (m << 1) | bit;
	}
}

static
void	LZMA_RCEnc_BitTreeReverse(s_lzma_rcenc* rc, t_prob* probs, t_uint amount, t_u32 symbol)
{
	t_u32	m = 1;
	t_uint	bit;
	while (amount--)
	{
		bit = (symbol & 1);
		symbol >>= 1;
		LZMA_RCEnc_Bit(rc, &probs[m], bit);
		m = (m << 1) | bit;
	}
}

//! Encodes a match length (`symbol` is the length, minus `LZMA_MATCHLENGTH_MIN`)
static
void	LZMA_RCEnc_Length(
	s_lzma_rcenc* rc,
	t_prob* choice,
	t_prob* choice2,
	t_prob (*low)[8],
	t_prob (*mid)[8],
	t_prob* high,
	t_uint pos_state,
	t_u32 symbol)
{
	if (symbol < 8)
	{
		LZMA_RCEnc_Bit(rc, choice, 0);
		LZMA_RCEnc_BitTree(rc, low[pos_state], 3, symbol);
		return;
	}
	LZMA_RCEnc_Bit(rc, choice, 1);
	if (symbol < 16)
	{
		LZMA_RCEnc_Bit(rc, choice2, 0);
		LZMA_RCEnc_BitTree(rc, mid[pos_state], 3, symbol - 8);
		return;
	}
	LZMA_RCEnc_Bit(rc, choice2, 1);
	LZMA_RCEnc_BitTree(rc, high, 8, symbol - 16);
}

//! Encodes a match distance value (`dist` is the real distance, minus one)
static
void	LZMA_RCEnc_Distance(s_lzma_rcenc* rc, s_lzma_probs* probs, t_u32 length, t_u32 dist)
{
	t_u32	len_state = (length < LZMA_LENTOPOSSTATES ? length : LZMA_LENTOPOSSTATES - 1);
	t_u32	slot;
	t_u32	base;
	t_uint	direct;
	if (dist < 4)
		slot = dist;
	else
	{
		t_uint	top = 31;
		while (((dist >> top) & 1) == 0)
			top -= 1; // index of the highest set bit
		slot = ((t_u32)top << 1) | ((dist >> (top - 1)) & 1);
	}
	LZMA_RCEnc_BitTree(rc, probs->dist_slot[len_state], 6, slot);
	if (slot < 4)
		return;
	direct = (slot >> 1) - 1;
	base = (2 | (slot & 1)) << direct;
	if (slot < LZMA_DIST_MODEL_END)
		LZMA_RCEnc_BitTreeReverse(rc, probs->dist_special + base - slot, direct, dist - base);
	else
	{
		LZMA_RCEnc_Direct(rc, (dist - base) >> LZMA_ALIGN_BITS, direct - LZMA_ALIGN_BITS);
		LZMA_RCEnc_BitTreeReverse(rc, probs->dist_align, LZMA_ALIGN_BITS, (dist - base) & ((1 << LZMA_ALIGN_BITS) - 1));
	}
}

//! Encodes a single literal byte
static
void	LZMA_RCEnc_Literal(
	s_lzma_rcenc* rc,
	t_prob* literal,
	t_u8 const* data,
	t_size pos,
	t_uint state,
	t_u32 rep0)
{
	t_u8	prev_byte = (pos ? data[pos - 1] : 0);
	t_u32	lit_state = (((pos & (((t_u32)1 << LZMA_LP) - 1)) << LZMA_LC) + (prev_byte >> (8 - LZMA_LC)));
	t_prob*	p = literal + (t_u32)0x300 * lit_state;
	t_u32	m = 1;
	t_u8	byte = data[pos];
	t_bool	matched = (state >= 7);
	t_u8	match_byte = (matched ? data[pos - rep0 - 1] : 0);
	t_uint	bit;
	t_uint	match_bit;
	for (t_sint i = 7; i >= 0; --i)
	{
		bit = ((byte >> i) & 1);
		if (matched)
		{
			match_bit = ((match_byte >> i) & 1);
			LZMA_RCEnc_Bit(rc, &p[((1 + match_bit) << 8) + m], bit);
			if (match_bit != bit)
				matched = FALSE;
		}
		else
			LZMA_RCEnc_Bit(rc, &p[m], bit);
		m = (m << 1) | bit;
	}
}



/*============================================================================*\
||                                 Compression                                ||
\*============================================================================*/

//! The maximum amount of match candidates to check, at each position (speed/ratio tradeoff)
#define LZMA_COMPRESS_MAXCHAIN	(96)

//! The amount of hash buckets used by the compressor's match-finder
#define LZMA_COMPRESS_HASHBITS	(17)
#define LZMA_COMPRESS_HASHSIZE	((t_u32)1 << LZMA_COMPRESS_HASHBITS)

#define LZMA_NONE	((t_u32)-1)

static
t_u32	LZMA_Compress_Hash(t_u8 const* data)
{
	t_u32	value = ((t_u32)data[0] | ((t_u32)data[1] << 8) | ((t_u32)data[2] << 16) | ((t_u32)data[3] << 24));
	return ((value * 2654435761u) >> (32 - LZMA_COMPRESS_HASHBITS));
}

static
void	LZMA_Compress_Insert(
	t_u32* hash_head,
	t_u32* hash_prev,
	t_u32 ring_mask,
	t_u8 const* data,
	t_size size,
	t_size pos)
{
	t_u32	hash;
	if (pos + 4 > size)
		return;
	hash = LZMA_Compress_Hash(data + pos);
	hash_prev[pos & ring_mask] = hash_head[hash];
	hash_head[hash] = (t_u32)pos;
}

static
t_u32	LZMA_Compress_FindMatch(
	t_u32* out_distance,
	t_u32 const* hash_head,
	t_u32 const* hash_prev,
	t_u32 ring_mask,
	t_u8 const* data,
	t_size size,
	t_size pos,
	t_u32 length_max)
{
	t_u32	best_length = 0;
	t_u32	length;
	t_u32	candidate;
	t_size	limit;
	t_uint	chain;

	if (pos + 4 > size || length_max < 4)
		return (0);
	limit = (pos > LIBCONFIG_COMPRESS_LZMA_DICTSIZE ? pos - LIBCONFIG_COMPRESS_LZMA_DICTSIZE : 0);
	candidate = hash_head[LZMA_Compress_Hash(data + pos)];
	for (chain = 0; chain < LZMA_COMPRESS_MAXCHAIN; ++chain)
	{
		t_u32	next;
		if (candidate == LZMA_NONE || candidate < limit)
			break;
		if (data[candidate + best_length] == data[pos + best_length])
		{
			length = 0;
			while (length < length_max && data[candidate + length] == data[pos + length])
				length += 1;
			if (length > best_length)
			{
				best_length = length;
				*out_distance = (t_u32)(pos - candidate);
				if (best_length == length_max)
					break;
			}
		}
		next = hash_prev[candidate & ring_mask];
		if (next >= candidate)
			break; // guards against stale ring-buffer entries
		candidate = next;
	}
	return (best_length >= 4 ? best_length : 0);
}

t_u8*	LZMA_Compress(t_size* dest_size, t_u8 const* data, t_size size)
{
	s_lzma_probs	probs;
	s_lzma_rcenc	rc = {0};
	t_prob*	literal;
	t_u32*	hash_head;
	t_u32*	hash_prev;
	t_u32	ring_size;
	t_u32	reps[4] = {0, 0, 0, 0};
	t_uint	state = 0;
	t_uint	pos_state;
	t_size	pos;
	t_u32	length_max;
	t_u32	rep_len, rep_idx;
	t_bool	rep0_one;
	t_u32	main_len, main_dist;
	t_u32	i;

	if (dest_size)
		*dest_size = 0;
	if CCCERROR((data == NULL), ERROR_NULLPOINTER, "data buffer given is NULL")
		return (NULL);
	if CCCERROR((size >= (t_u32)-1), ERROR_LENGTH2LARGE,
		"data given is too large to be compressed (must be less than 4GB)")
		return (NULL);
	rc.capacity = LZMA_HEADER_SIZE + size + size / 2 + 256;
	rc.dest = (t_u8*)Memory_Allocate(rc.capacity);
	if CCCERROR((rc.dest == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	literal = (t_prob*)Memory_Allocate(((t_u32)0x300 << (LZMA_LC + LZMA_LP)) * sizeof(t_prob));
	if CCCERROR((literal == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(rc.dest);
		return (NULL);
	}
	ring_size = 16;
	while (ring_size < size && ring_size < LIBCONFIG_COMPRESS_LZMA_DICTSIZE)
		ring_size <<= 1;
	hash_head = (t_u32*)Memory_Allocate((LZMA_COMPRESS_HASHSIZE + ring_size) * sizeof(t_u32));
	if CCCERROR((hash_head == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(rc.dest);
		Memory_Deallocate(literal);
		return (NULL);
	}
	hash_prev = hash_head + LZMA_COMPRESS_HASHSIZE;
	for (i = 0; i < LZMA_COMPRESS_HASHSIZE; ++i)
		hash_head[i] = LZMA_NONE;
	LZMA_Probs_Init(&probs, literal, ((t_u32)0x300 << (LZMA_LC + LZMA_LP)));
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_ALONE)
	rc.dest[0] = LZMA_PROPSBYTE;
	for (i = 0; i < 4; ++i)
		rc.dest[1 + i] = (t_u8)((t_u32)LIBCONFIG_COMPRESS_LZMA_DICTSIZE >> (i * 8));
	for (i = 0; i < 8; ++i)
		rc.dest[5 + i] = (t_u8)((t_u64)size >> (i * 8));
	rc.pos = LZMA_HEADER_SIZE;
#endif
	rc.range = (t_u32)-1;
	rc.cache = 0;
	rc.cache_size = 1;
	rc.low = 0;
	pos = 0;
	while (pos < size)
	{
		pos_state = (pos & (((t_uint)1 << LZMA_PB) - 1));
		length_max = (t_u32)(size - pos < LZMA_MATCHLENGTH_MAX ? size - pos : LZMA_MATCHLENGTH_MAX);
		// check the 4 "repeated distance" registers for matches at the current position
		rep_len = 0;
		rep_idx = 0;
		rep0_one = FALSE;
		for (i = 0; i < 4; ++i)
		{
			t_size	dist = (t_size)reps[i] + 1;
			t_u32	len = 0;
			if (dist > pos)
				continue;
			while (len < length_max && data[pos - dist + len] == data[pos + len])
				len += 1;
			if (i == 0 && len >= 1)
				rep0_one = TRUE;
			if (len > rep_len)
			{
				rep_len = len;
				rep_idx = i;
			}
		}
		// search the hash chains for a regular match
		main_len = LZMA_Compress_FindMatch(&main_dist,
			hash_head, hash_prev, ring_size - 1, data, size, pos, length_max);
		// decide which packet to emit (greedy, with a preference for cheap "rep" matches)
		if (rep_len >= 2 && (rep_len + 1 >= main_len || main_len < 4))
		{	// "rep" match packet
			LZMA_RCEnc_Bit(&rc, &probs.is_match[(state << 4) + pos_state], 1);
			LZMA_RCEnc_Bit(&rc, &probs.is_rep[state], 1);
			if (rep_idx == 0)
			{
				LZMA_RCEnc_Bit(&rc, &probs.is_rep_g0[state], 0);
				LZMA_RCEnc_Bit(&rc, &probs.is_rep0_long[(state << 4) + pos_state], 1);
			}
			else
			{
				t_u32	dist = reps[rep_idx];
				LZMA_RCEnc_Bit(&rc, &probs.is_rep_g0[state], 1);
				if (rep_idx == 1)
					LZMA_RCEnc_Bit(&rc, &probs.is_rep_g1[state], 0);
				else
				{
					LZMA_RCEnc_Bit(&rc, &probs.is_rep_g1[state], 1);
					LZMA_RCEnc_Bit(&rc, &probs.is_rep_g2[state], (rep_idx == 2 ? 0 : 1));
					if (rep_idx == 3)
						reps[3] = reps[2];
					reps[2] = reps[1];
				}
				reps[1] = reps[0];
				reps[0] = dist;
			}
			LZMA_RCEnc_Length(&rc,
				&probs.rep_choice, &probs.rep_choice2, probs.rep_low, probs.rep_mid, probs.rep_high,
				pos_state, rep_len - LZMA_MATCHLENGTH_MIN);
			state = LZMA_STATE_REP(state);
			for (i = 0; i < rep_len; ++i)
				LZMA_Compress_Insert(hash_head, hash_prev, ring_size - 1, data, size, pos + i);
			pos += rep_len;
		}
		else if (main_len >= 4)
		{	// match packet (a new distance)
			LZMA_RCEnc_Bit(&rc, &probs.is_match[(state << 4) + pos_state], 1);
			LZMA_RCEnc_Bit(&rc, &probs.is_rep[state], 0);
			LZMA_RCEnc_Length(&rc,
				&probs.len_choice, &probs.len_choice2, probs.len_low, probs.len_mid, probs.len_high,
				pos_state, main_len - LZMA_MATCHLENGTH_MIN);
			LZMA_RCEnc_Distance(&rc, &probs, main_len - LZMA_MATCHLENGTH_MIN, main_dist - 1);
			reps[3] = reps[2];
			reps[2] = reps[1];
			reps[1] = reps[0];
			reps[0] = main_dist - 1;
			state = LZMA_STATE_MATCH(state);
			for (i = 0; i < main_len; ++i)
				LZMA_Compress_Insert(hash_head, hash_prev, ring_size - 1, data, size, pos + i);
			pos += main_len;
		}
		else if (rep0_one)
		{	// "short rep" packet: a single byte, at distance `reps[0] + 1`
			LZMA_RCEnc_Bit(&rc, &probs.is_match[(state << 4) + pos_state], 1);
			LZMA_RCEnc_Bit(&rc, &probs.is_rep[state], 1);
			LZMA_RCEnc_Bit(&rc, &probs.is_rep_g0[state], 0);
			LZMA_RCEnc_Bit(&rc, &probs.is_rep0_long[(state << 4) + pos_state], 0);
			state = LZMA_STATE_SHORTREP(state);
			LZMA_Compress_Insert(hash_head, hash_prev, ring_size - 1, data, size, pos);
			pos += 1;
		}
		else
		{	// literal packet
			LZMA_RCEnc_Bit(&rc, &probs.is_match[(state << 4) + pos_state], 0);
			LZMA_RCEnc_Literal(&rc, literal, data, pos, state, reps[0]);
			state = LZMA_STATE_LITERAL(state);
			LZMA_Compress_Insert(hash_head, hash_prev, ring_size - 1, data, size, pos);
			pos += 1;
		}
	}
#if (LIBCONFIG_COMPRESS_LZMA_FORMAT == LZMA_FORMAT_RAW)
	// emit the "end of stream" marker (a match with the maximum distance value)
	pos_state = (pos & (((t_uint)1 << LZMA_PB) - 1));
	LZMA_RCEnc_Bit(&rc, &probs.is_match[(state << 4) + pos_state], 1);
	LZMA_RCEnc_Bit(&rc, &probs.is_rep[state], 0);
	LZMA_RCEnc_Length(&rc,
		&probs.len_choice, &probs.len_choice2, probs.len_low, probs.len_mid, probs.len_high,
		pos_state, 0);
	LZMA_RCEnc_Distance(&rc, &probs, 0, LZMA_MARKER);
#endif
	LZMA_RCEnc_Flush(&rc);
	Memory_Deallocate(hash_head);
	Memory_Deallocate(literal);
	if CCCERROR((rc.failed), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Deallocate(rc.dest);
		return (NULL);
	}
	// shrink the buffer to fit the actual compressed size
	if (rc.pos > 0 && rc.pos < rc.capacity)
	{
		t_u8*	tmp = (t_u8*)Memory_Reallocate(rc.dest, rc.pos);
		if (tmp != NULL)
			rc.dest = tmp;
	}
	if (dest_size)
		*dest_size = rc.pos;
	return (rc.dest);
}
