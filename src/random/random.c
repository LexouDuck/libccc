
#include <time.h>

#include "libft_random.h"



t_u32		random_U32 = DEFAULT_SEED;



inline t_u32	ft_random_32bit_shuffle(t_u32 n)
{
	n = (n << 12) ^ (n >> 20);
	return (36969 * (n & 0xFFFF) + (n >> 16));
}

inline void		ft_random_set_seed(t_u32 seed)
{
	random_U32 = seed;
}

void			ft_random_renew_seed(void)
{
	random_U32 = ft_random_32bit_shuffle(time(NULL));
}



inline t_u32	ft_random_u32(void)
{
	random_U32 = (CEIL_SQRT_MOD * ft_random_32bit_shuffle(random_U32) + OFFSET) & MODULUS;
	return (random_U32);
}

inline t_u32	ft_random_u32_0_to_pow2n(t_u32 n)
{
	return (ft_random_u32() & ((0x1 << n) - 1));
}

inline t_u32	ft_random_u32_0_to_n(t_u32 n)
{
	return (n == 0 ? n : (ft_random_u32() % n));
}

inline t_int	ft_random_int_a_to_b(t_int a, t_int b)
{
	if (a < b)
		return (ft_random_u32_0_to_n(b - a) + a);
	else
		return (ft_random_u32_0_to_n(a - b) + b);
}

inline t_float	ft_random_float_0_to_1(void)
{
	return (((t_float)ft_random_u32()) / (t_float)MODULUS);
}

inline t_float	ft_random_float_a_to_b(t_float a, t_float b)
{
	if (a < b)
		return (ft_random_float_0_to_1() * (b - a) + a);
	else
		return (ft_random_float_0_to_1() * (a - b) + b);
}
