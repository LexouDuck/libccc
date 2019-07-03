#include "../../libft_math.h"

t_float			ft_mc_integrate3(t_scalar_func3 const sf, t_3d_box const domain)
{
	t_vec3		rand_input;
	t_float		result;
	t_u32		i;

	result = 0.;
	i = 0;
	while (i < SAMPLE_NB)
	{
		rand_input.x = ft_random_float_a_to_b(domain.start.x, domain.end.x);
		rand_input.y = ft_random_float_a_to_b(domain.start.y, domain.end.y);
		rand_input.z = ft_random_float_a_to_b(domain.start.z, domain.end.z);
		result += sf(rand_input);
		++i;
	}
	result /= (t_float)SAMPLE_NB;
	result *=	(domain.end.x - domain.start.x) *
				(domain.end.y - domain.start.y) *
				(domain.end.z - domain.start.z);
	return (result);
}



inline t_bool		ft_float_in_interval(t_float x, t_float start, t_float end)
{
	return (start <= x && x <= end);
}



/*
** Distance functions.
** All classical distances (1, 2, inf) on the real line are equivalent.
** Multiple type handling.
*/

inline t_f32	ft_distance_f32(t_f32 x, t_f32 y)
{
	return (ABS(x - y));
}
inline t_f64	ft_distance_f64(t_f64 x, t_f64 y)
{
	return (ABS(x - y));
}

inline t_u8		ft_distance_u8(t_u8 x, t_u8 y)
{
	return (ABS(x - y));
}
inline t_u16	ft_distance_u16(t_u16 x, t_u16 y)
{
	return (ABS(x - y));
}
inline t_u32	ft_distance_u32(t_u32 x, t_u32 y)
{
	return (ABS(x - y));
}
inline t_u64	ft_distance_u64(t_u64 x, t_u64 y)
{
	return (ABS(x - y));
}

inline t_s8		ft_distance_s8(t_s8 x, t_s8 y)
{
	return (ABS(x - y));
}
inline t_s16	ft_distance_s16(t_s16 x, t_s16 y)
{
	return (ABS(x - y));
}
inline t_s32	ft_distance_s32(t_s32 x, t_s32 y)
{
	return (ABS(x - y));
}
inline t_s64	ft_distance_s64(t_s64 x, t_s64 y)
{
	return (ABS(x - y));
}

inline t_float	ft_distance_float(t_float x, t_float y)
{
	return (ABS(x - y));
}
inline t_uint	ft_distance_uint(t_uint x, t_uint y)
{
	return (ABS(x - y));
}
inline t_int	ft_distance_int(t_int x, t_int y)
{
	return (ABS(x - y));
}

//t_float		ft_distance_2d()


/*
** Returns the value of val after [0,1] is scaled and translated
** (affine transform) to [start, end]. Val is not checked to be
** in the interval [0,1] here. start is not checked to be <= end.
*/
inline t_float	ft_to_affine(t_float value_01, t_float start, t_float end)
{
	return (value_01 * ft_distance_float(start, end)) + start;
}

/*
** Returns the value of val after [start, end] is scaled and translated
** (affine transform) to [0,1]. Val is not checked to be in the interval
** [start, end] here. start is not checked to be <= end.
*/
inline t_float	ft_from_affine(t_float value_affine, t_float start, t_float end)
{
	return (value_affine - start) / ft_distance_float(start, end);
}