
#include "libccc.h"
#include "libccc/sys/network.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	These functions are implemented in a fully endianness-agnostic manner:
**	rather than detecting the host machine's endianness (and byte-swapping
**	only when needed), they simply write out/read in the value byte-by-byte,
**	in the desired (big-endian) byte order. Any decent optimizing compiler
**	will recognize these patterns, and turn them into a single `bswap`-style
**	instruction (or a no-op) for the target platform, as appropriate.
*/



t_u16	Network_HostToNet_U16(t_u16 value)
{
	t_u16	result;
	t_u8*	bytes = (t_u8*)&result;

	bytes[0] = (t_u8)(value >> 8);
	bytes[1] = (t_u8)(value >> 0);
	return (result);
}

t_u32	Network_HostToNet_U32(t_u32 value)
{
	t_u32	result;
	t_u8*	bytes = (t_u8*)&result;

	bytes[0] = (t_u8)(value >> 24);
	bytes[1] = (t_u8)(value >> 16);
	bytes[2] = (t_u8)(value >> 8);
	bytes[3] = (t_u8)(value >> 0);
	return (result);
}

t_u64	Network_HostToNet_U64(t_u64 value)
{
	t_u64	result;
	t_u8*	bytes = (t_u8*)&result;

	bytes[0] = (t_u8)(value >> 56);
	bytes[1] = (t_u8)(value >> 48);
	bytes[2] = (t_u8)(value >> 40);
	bytes[3] = (t_u8)(value >> 32);
	bytes[4] = (t_u8)(value >> 24);
	bytes[5] = (t_u8)(value >> 16);
	bytes[6] = (t_u8)(value >> 8);
	bytes[7] = (t_u8)(value >> 0);
	return (result);
}



t_u16	Network_NetToHost_U16(t_u16 value)
{
	t_u8 const*	bytes = (t_u8 const*)&value;

	return (t_u16)(
		((t_u16)bytes[0] << 8) |
		((t_u16)bytes[1] << 0));
}

t_u32	Network_NetToHost_U32(t_u32 value)
{
	t_u8 const*	bytes = (t_u8 const*)&value;

	return (
		((t_u32)bytes[0] << 24) |
		((t_u32)bytes[1] << 16) |
		((t_u32)bytes[2] << 8) |
		((t_u32)bytes[3] << 0));
}

t_u64	Network_NetToHost_U64(t_u64 value)
{
	t_u8 const*	bytes = (t_u8 const*)&value;

	return (
		((t_u64)bytes[0] << 56) |
		((t_u64)bytes[1] << 48) |
		((t_u64)bytes[2] << 40) |
		((t_u64)bytes[3] << 32) |
		((t_u64)bytes[4] << 24) |
		((t_u64)bytes[5] << 16) |
		((t_u64)bytes[6] << 8) |
		((t_u64)bytes[7] << 0));
}
