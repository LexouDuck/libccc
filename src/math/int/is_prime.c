
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/math/int.h"



// Modular exponentiation: compute (base^exp) % mod efficiently
// This prevents overflow by taking modulo at each multiplication step
static
inline
t_u64	modpow_u64(t_u64 base, t_u64 exp, t_u64 mod)
{
	t_u64	result;

	result = 1;
	base %= mod;
	while (exp > 0)
	{
		if (exp & 1)
			result = ((__uint128_t)result * base) % mod;
		base = ((__uint128_t)base * base) % mod;
		exp >>= 1;
	}
	return (result);
}

// For 128-bit integers, we need special handling
static
inline
t_u128	modpow_u128(t_u128 base, t_u128 exp, t_u128 mod)
{
	t_u128	result;
	t_u128	temp;

	result = 1;
	base %= mod;
	while (exp > 0)
	{
		if (exp & 1)
		{
			// Multiply with overflow protection
			temp = result;
			result = 0;
			while (temp > 0)
			{
				if (temp & 1)
					result = (result + base) % mod;
				base = (base + base) % mod;
				temp >>= 1;
			}
			base = result;
		}
		// Square base
		temp = base;
		base = 0;
		while (temp > 0)
		{
			if (temp & 1)
				base = (base + temp) % mod;
			temp = (temp + temp) % mod;
			temp >>= 1;
		}
		exp >>= 1;
	}
	return (result);
}

// Miller-Rabin primality test with a single witness
static
inline
t_bool	miller_rabin_u64(t_u64 n, t_u64 witness)
{
	t_u64	d;
	t_u64	x;
	t_u64	r;

	if (n <= 1 || (n > 2 && (n & 1) == 0))
		return (FALSE);
	if (n == 2 || n == 3)
		return (TRUE);
	
	// Write n-1 as 2^r * d
	d = n - 1;
	r = 0;
	while ((d & 1) == 0)
	{
		d >>= 1;
		r++;
	}
	
	// Compute witness^d % n
	x = modpow_u64(witness, d, n);
	
	if (x == 1 || x == n - 1)
		return (TRUE);
	
	while (r > 1)
	{
		x = ((__uint128_t)x * x) % n;
		if (x == n - 1)
			return (TRUE);
		r--;
	}
	return (FALSE);
}

static
inline
t_bool	miller_rabin_u128(t_u128 n, t_u128 witness)
{
	t_u128	d;
	t_u128	x;
	t_u128	r;

	if (n <= 1 || (n > 2 && (n & 1) == 0))
		return (FALSE);
	if (n == 2 || n == 3)
		return (TRUE);
	
	// Write n-1 as 2^r * d
	d = n - 1;
	r = 0;
	while ((d & 1) == 0)
	{
		d >>= 1;
		r++;
	}
	
	// Compute witness^d % n
	x = modpow_u128(witness, d, n);
	
	if (x == 1 || x == n - 1)
		return (TRUE);
	
	while (r > 1)
	{
		x = modpow_u128(x, 2, n);
		if (x == n - 1)
			return (TRUE);
		r--;
	}
	return (FALSE);
}



/*
** Deterministic Miller-Rabin for various ranges
** Using known witness sets that guarantee correctness up to certain bounds
*/

// For n < 2,047: witness = 2
// For n < 1,373,653: witnesses = 2, 3
// For n < 9,080,191: witnesses = 31, 73
// For n < 25,326,001: witnesses = 2, 3, 5
// For n < 3,215,031,751: witnesses = 2, 3, 5, 7
// For n < 4,759,123,141: witnesses = 2, 7, 61
// For n < 2^32: witnesses = 2, 7, 61
// For n < 3,317,044,064,679,887,385,961,981: witnesses = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37

#define DEFINEFUNC_PRIMALITY_UINT(BITS) \
t_bool	U##BITS##_IsPrime(t_u##BITS x) \
{ \
	t_u64	n; \
\
	if (x <= 1) \
		return (FALSE); \
	if (x == 2) \
		return (TRUE); \
	if ((x & 1) == 0) \
		return (FALSE); \
	if (x < 9) \
		return (TRUE); \
	if (x % 3 == 0 || x % 5 == 0 || x % 7 == 0) \
		return (FALSE); \
\
	n = (t_u64)x; \
	if (BITS <= 8 || n < 2047) \
		return (miller_rabin_u64(n, 2)); \
	if (BITS <= 16 || n < 1373653) \
		return ( \
			miller_rabin_u64(n, 2) && \
			miller_rabin_u64(n, 3)); \
	if (n < 25326001) \
		return ( \
			miller_rabin_u64(n, 2) && \
			miller_rabin_u64(n, 3) && \
			miller_rabin_u64(n, 5)); \
	if (BITS <= 32) \
		return ( \
			miller_rabin_u64(n,  2) && \
			miller_rabin_u64(n,  7) && \
			miller_rabin_u64(n, 61)); \
	return ( \
		miller_rabin_u64(n,  2) && \
		miller_rabin_u64(n,  3) && \
		miller_rabin_u64(n,  5) && \
		miller_rabin_u64(n,  7) && \
		miller_rabin_u64(n, 11) && \
		miller_rabin_u64(n, 13) && \
		miller_rabin_u64(n, 17)); \
}

#define DEFINEFUNC_PRIMALITY_SINT(BITS) \
t_bool	S##BITS##_IsPrime(t_s##BITS x) \
{ \
	if (x <= 1) \
		return (FALSE); \
	return (U##BITS##_IsPrime((t_u##BITS)x)); \
}



// Generate all unsigned integer type implementations
DEFINEFUNC_PRIMALITY_UINT(8)
DEFINEFUNC_PRIMALITY_UINT(16)
DEFINEFUNC_PRIMALITY_UINT(32)
DEFINEFUNC_PRIMALITY_UINT(64)

// Generate all signed integer type implementations
DEFINEFUNC_PRIMALITY_SINT(8)
DEFINEFUNC_PRIMALITY_SINT(16)
DEFINEFUNC_PRIMALITY_SINT(32)
DEFINEFUNC_PRIMALITY_SINT(64)

// Special handling for 128-bit integers
t_bool	U128_IsPrime(t_u128 x)
{
	if (x <= 1)
		return (FALSE);
	if (x == 2)
		return (TRUE);
	if ((x & 1) == 0)
		return (FALSE);
	if (x < 9)
		return (TRUE);
	if (x % 3 == 0 || x % 5 == 0 || x % 7 == 0)
		return (FALSE);

	// For 128-bit: use first 12 primes as witnesses
	// This is deterministic for n < ~3.3e24
	return (
		miller_rabin_u128(x,  2) &&
		miller_rabin_u128(x,  3) &&
		miller_rabin_u128(x,  5) &&
		miller_rabin_u128(x,  7) &&
		miller_rabin_u128(x, 11) &&
		miller_rabin_u128(x, 13) &&
		miller_rabin_u128(x, 17) &&
		miller_rabin_u128(x, 19) &&
		miller_rabin_u128(x, 23) &&
		miller_rabin_u128(x, 29) &&
		miller_rabin_u128(x, 31) &&
		miller_rabin_u128(x, 37));
}

t_bool	S128_IsPrime(t_s128 x)
{
	if (x <= 1)
		return (FALSE);
	return (U128_IsPrime((t_u128)x));
}
