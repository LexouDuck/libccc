
#include "libccc/random/random.h"
#include "libccc/math/math.h"
#include "libccc/math/algebra.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_float			c_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain)
{
	u_vector3d	rand_input;
	t_float		result;
	t_u32		i;
	t_rand*		rng;

	result = 0.;
	i = 0;
	rng = Random_New();
	while (i < SAMPLE_NB)
	{
		rand_input.vector.x = Random_Float_Range(rng, domain.start.vector.x, domain.end.vector.x);
		rand_input.vector.y = Random_Float_Range(rng, domain.start.vector.y, domain.end.vector.y);
		rand_input.vector.z = Random_Float_Range(rng, domain.start.vector.z, domain.end.vector.z);
		result += sf(rand_input);
		++i;
	}
	Random_Delete(&rng);
	result /= (t_float)SAMPLE_NB;
	result =
		(domain.end.vector.x - domain.start.vector.x) *
		(domain.end.vector.y - domain.start.vector.y) *
		(domain.end.vector.z - domain.start.vector.z) *
		result;
	return (result);
}



inline
t_bool		c_float_in_interval(t_float x, t_float start, t_float end)
{
	return (start <= x && x <= end);
}



/*
** Distance functions.
** All classical distances (1, 2, inf) on the real line are equivalent.
** Multiple type handling.
*/

inline t_f32	c_distance_f32(t_f32 x, t_f32 y)	{ return (ABS(x - y)); }
inline t_f64	c_distance_f64(t_f64 x, t_f64 y)	{ return (ABS(x - y)); }

inline t_u8		c_distance_u8(t_u8 x, t_u8 y)		{ return (x - y); }
inline t_u16	c_distance_u16(t_u16 x, t_u16 y)	{ return (x - y); }
inline t_u32	c_distance_u32(t_u32 x, t_u32 y)	{ return (x - y); }
inline t_u64	c_distance_u64(t_u64 x, t_u64 y)	{ return (x - y); }

inline t_s8		c_distance_s8(t_s8 x, t_s8 y)		{ return (ABS(x - y)); }
inline t_s16	c_distance_s16(t_s16 x, t_s16 y)	{ return (ABS(x - y)); }
inline t_s32	c_distance_s32(t_s32 x, t_s32 y)	{ return (ABS(x - y)); }
inline t_s64	c_distance_s64(t_s64 x, t_s64 y)	{ return (ABS(x - y)); }

inline t_float	c_distance_float(t_float x, t_float y)	{ return (ABS(x - y)); }
inline t_uint	c_distance_uint(t_uint x, t_uint y)		{ return (x - y); }
inline t_sint	c_distance_int(t_sint x, t_sint y)		{ return (ABS(x - y)); }

//t_float		c_distance_2d()


/*
** Returns the value of val after [0,1] is scaled and translated
** (affine transform) to [start, end]. Val is not checked to be
** in the interval [0,1] here. start is not checked to be <= end.
*/
inline
t_float	c_to_affine(t_float value_01, t_float start, t_float end)
{
	return (value_01 * c_distance_float(start, end)) + start;
}

/*
** Returns the value of val after [start, end] is scaled and translated
** (affine transform) to [0,1]. Val is not checked to be in the interval
** [start, end] here. start is not checked to be <= end.
*/
inline
t_float	c_from_affine(t_float value_affine, t_float start, t_float end)
{
	return (value_affine - start) / c_distance_float(start, end);
}
