
#include "libccc.h"
#include "libccc/random/random.h"
#include "libccc/math.h"
#include "libccc/math/algebra.h"

#include LIBCONFIG_ERROR_INCLUDE



t_float			c_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain)
{
	u_vector3d	rand_input;
	t_float		result;
	t_u32		i;
	t_rand*		rng;

	result = 0.;
	i = 0;
	rng = Random_New();
	if CCCERROR((rng == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NAN);
	while (i < SAMPLE_NB)
	{
		rand_input.vector.x = Random_GetInRange_Float(rng, domain.start.vector.x, domain.end.vector.x);
		rand_input.vector.y = Random_GetInRange_Float(rng, domain.start.vector.y, domain.end.vector.y);
		rand_input.vector.z = Random_GetInRange_Float(rng, domain.start.vector.z, domain.end.vector.z);
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



/*
** Distance functions.
** All classical distances (1, 2, inf) on the real line are equivalent.
** Multiple type handling.
*/

_INLINE()	t_uint	c_distance_uint	(t_uint x, t_uint y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_u8	c_distance_u8	(t_u8   x, t_u8   y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_u16	c_distance_u16	(t_u16  x, t_u16  y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_u32	c_distance_u32	(t_u32  x, t_u32  y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_u64	c_distance_u64	(t_u64  x, t_u64  y)	{ return (y < x) ? (x - y) : (y - x); }
#if LIBCONFIG_USE_INT128
_INLINE()	t_u128	c_distance_u128	(t_u128 x, t_u128 y)	{ return (y < x) ? (x - y) : (y - x); }
#endif

_INLINE()	t_sint	c_distance_sint	(t_sint x, t_sint y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_s8	c_distance_s8	(t_s8   x, t_s8   y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_s16	c_distance_s16	(t_s16  x, t_s16  y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_s32	c_distance_s32	(t_s32  x, t_s32  y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_s64	c_distance_s64	(t_s64  x, t_s64  y)	{ return (y < x) ? (x - y) : (y - x); }
#if LIBCONFIG_USE_INT128
_INLINE()	t_s128	c_distance_s128	(t_s128 x, t_s128 y)	{ return (y < x) ? (x - y) : (y - x); }
#endif

_INLINE()	t_fixed	c_distance_fixed(t_fixed x, t_fixed y)	{ return (y._ < x._) ? (t_fixed){ (t_sint)(x._ - y._) } : (t_fixed){ (t_sint)(y._ - x._) }; }
_INLINE()	t_q16	c_distance_q16	(t_q16   x, t_q16   y)	{ return (y._ < x._) ? (t_q16  ){ (t_s16 )(x._ - y._) } : (t_q16  ){ (t_s16 )(y._ - x._) }; }
_INLINE()	t_q32	c_distance_q32	(t_q32   x, t_q32   y)	{ return (y._ < x._) ? (t_q32  ){ (t_s32 )(x._ - y._) } : (t_q32  ){ (t_s32 )(y._ - x._) }; }
_INLINE()	t_q64	c_distance_q64	(t_q64   x, t_q64   y)	{ return (y._ < x._) ? (t_q64  ){ (t_s64 )(x._ - y._) } : (t_q64  ){ (t_s64 )(y._ - x._) }; }
#if LIBCONFIG_USE_INT128
_INLINE()	t_q128	c_distance_q128	(t_q128  x, t_q128  y)	{ return (y._ < x._) ? (t_q128 ){ (t_s128)(x._ - y._) } : (t_q128 ){ (t_s128)(y._ - x._) }; }
#endif

_INLINE()	t_float	c_distance_float(t_float x, t_float y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_f32	c_distance_f32	(t_f32   x, t_f32   y)	{ return (y < x) ? (x - y) : (y - x); }
_INLINE()	t_f64	c_distance_f64	(t_f64   x, t_f64   y)	{ return (y < x) ? (x - y) : (y - x); }
#if LIBCONFIG_USE_FLOAT80
_INLINE()	t_f80	c_distance_f80	(t_f80   x, t_f80   y)	{ return (y < x) ? (x - y) : (y - x); }
#endif
#if LIBCONFIG_USE_FLOAT128
_INLINE()	t_f128	c_distance_f128	(t_f128  x, t_f128  y)	{ return (y < x) ? (x - y) : (y - x); }
#endif

//t_float		c_distance_2d()

#if 0 // TODO: use these functions, or define them in the header ?

static inline
t_bool	c_float_in_interval(t_float x, t_float start, t_float end)
{
	return (start <= x && x <= end);
}


/*!
** Returns the value of val after [0,1] is scaled and translated
** (affine transform) to [start, end]. Val is not checked to be
** in the interval [0,1] here. start is not checked to be <= end.
*/
static inline
t_float	c_to_affine(t_float value_01, t_float start, t_float end)
{
	return (value_01 * c_distance_float(start, end)) + start;
}

/*!
** Returns the value of val after [start, end] is scaled and translated
** (affine transform) to [0,1]. Val is not checked to be in the interval
** [start, end] here. start is not checked to be <= end.
*/
static inline
t_float	c_from_affine(t_float value_affine, t_float start, t_float end)
{
	return (value_affine - start) / c_distance_float(start, end);
}

#endif
