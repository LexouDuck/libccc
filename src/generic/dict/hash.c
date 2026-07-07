
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	This is an implementation of the SipHash-1-3 hashing algorithm
**	(SipHash with 1 compression round and 3 finalization rounds), see:
**	- https://en.wikipedia.org/wiki/SipHash
**	- https://github.com/veorq/SipHash (the reference implementation)
**	The 128-bit seed key is set with the `LIBCONFIG_DICT_HASHSEED_*` macros,
**	and defaults to the reference implementation's canonical test key
**	(ie: the byte sequence `000102030405060708090A0B0C0D0E0F`), so that the
**	output of this function can be verified against the reference implementation.
*/

#define DICT_SIPHASH_ROTL(X, BITS) \
	(((X) << (BITS)) | ((X) >> (64 - (BITS))))

#define DICT_SIPHASH_ROUND() \
	do \
	{ \
		v0 += v1;	v1 = DICT_SIPHASH_ROTL(v1, 13);	v1 ^= v0;	v0 = DICT_SIPHASH_ROTL(v0, 32); \
		v2 += v3;	v3 = DICT_SIPHASH_ROTL(v3, 16);	v3 ^= v2; \
		v0 += v3;	v3 = DICT_SIPHASH_ROTL(v3, 21);	v3 ^= v0; \
		v2 += v1;	v1 = DICT_SIPHASH_ROTL(v1, 17);	v1 ^= v2;	v2 = DICT_SIPHASH_ROTL(v2, 32); \
	} \
	while (0) \

_GENERIC()
t_u64	Dict_HashKey(T)(t_char const* key)
{
	t_u64 const	k0 = (t_u64)LIBCONFIG_DICT_HASHSEED_0;
	t_u64 const	k1 = (t_u64)LIBCONFIG_DICT_HASHSEED_1;
	t_u64	v0 = (0x736F6D6570736575ULL ^ k0);
	t_u64	v1 = (0x646F72616E646F6DULL ^ k1);
	t_u64	v2 = (0x6C7967656E657261ULL ^ k0);
	t_u64	v3 = (0x7465646279746573ULL ^ k1);
	t_u64	block;
	t_u64	length;
	t_u64	i;

	if (key == NULL)
		key = ""; // a NULL key string is hashed like an empty string
	length = 0;
	while (key[length])
	{
		length += 1;
	}
	// process the input string as successive 8-byte little-endian blocks
	for (i = 0; i + 8 <= length; i += 8)
	{
		block = 0;
		for (t_u64 byte = 0; byte < 8; ++byte)
		{
			block |= ((t_u64)(t_u8)key[i + byte] << (byte * 8));
		}
		v3 ^= block;
		DICT_SIPHASH_ROUND(); // (1 compression round)
		v0 ^= block;
	}
	// the final block contains the remaining bytes, and the input length in the top byte
	block = ((t_u64)(length & 0xFF) << 56);
	for (t_u64 byte = 0; i + byte < length; ++byte)
	{
		block |= ((t_u64)(t_u8)key[i + byte] << (byte * 8));
	}
	v3 ^= block;
	DICT_SIPHASH_ROUND(); // (1 compression round)
	v0 ^= block;
	// finalization
	v2 ^= 0xFF;
	DICT_SIPHASH_ROUND(); // (3 finalization rounds)
	DICT_SIPHASH_ROUND();
	DICT_SIPHASH_ROUND();
	return (v0 ^ v1 ^ v2 ^ v3);
}

#undef DICT_SIPHASH_ROTL
#undef DICT_SIPHASH_ROUND
