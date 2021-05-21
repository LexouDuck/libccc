
#include "libccc/sys/time.h"
#include "libccc/math/random.h"



t_u32		random_U32 = DEFAULT_SEED;



inline t_u32	c_random_32bit_shuffle(t_u32 n)
{
	n = (n << 12) ^ (n >> 20);
	return (36969 * (n & 0xFFFF) + (n >> 16));
}

inline void		c_random_set_seed(t_u32 seed)
{
	random_U32 = seed;
}

void			c_random_renew_seed(void)
{
	random_U32 = c_random_32bit_shuffle(Time_Now());
}



inline t_u32	c_random_u32(void)
{
	random_U32 = (CEIL_SQRT_MOD * c_random_32bit_shuffle(random_U32) + OFFSET) & MODULUS;
	return (random_U32);
}

inline t_u32	c_random_u32_0_to_pow2n(t_u32 n)
{
	return (c_random_u32() & ((0x1 << n) - 1));
}

inline t_u32	c_random_u32_0_to_n(t_u32 n)
{
	return (n == 0 ? n : (c_random_u32() % n));
}

inline t_sint	c_random_int_a_to_b(t_sint a, t_sint b)
{
	if (a < b)
		return (c_random_u32_0_to_n(b - a) + a);
	else
		return (c_random_u32_0_to_n(a - b) + b);
}

inline t_float	c_random_float_0_to_1(void)
{
	return (((t_float)c_random_u32()) / (t_float)MODULUS);
}

inline t_float	c_random_float_a_to_b(t_float a, t_float b)
{
	if (a < b)
		return (c_random_float_0_to_1() * (b - a) + a);
	else
		return (c_random_float_0_to_1() * (a - b) + b);
}
