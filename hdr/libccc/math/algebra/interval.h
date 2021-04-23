/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/algebra/interval.h           |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_ALGEBRA_INTERVAL_H
#define __LIBCCC_MATH_ALGEBRA_INTERVAL_H
/*!@group{libccc_math_algebra_interval}
** @{
**	This header defines useful algebra and calculus types, and functions.
**
**	@file
*/
// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/math/float.h"
#include "libccc/math/algebra/vector.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                     Axis-aligned Bounding-box Operations                   *|
** ************************************************************************** *|
*/

/*
**	Definitions of axis-aligned bounding-box are assumed to be entirely composed of
**	orthogonal edges (brick shaped), which is why only two vectors are necessary to define it.
*/

//! A 1-dimensional interval of coordinates, defined by two corner-point vectors
typedef struct box1d
{
	t_float		start;
	t_float		end;
}					s_box1d;
TYPEDEF_ALIAS(		s_box1d, BOX_1D, STRUCT)

//! A 2-dimensional area of coordinates, defined by two corner-point vectors
typedef struct box2d
{
	u_vector2d	start;
	u_vector2d	end;
}					s_box2d;
TYPEDEF_ALIAS(		s_box2d, BOX_2D, STRUCT)

//! A 3-dimensional volume of coordinates, defined by two corner-point vectors
typedef struct box3d
{
	u_vector3d	start;
	u_vector3d	end;
}					s_box3d;
TYPEDEF_ALIAS(		s_box3d, BOX_3D, STRUCT)

//! A 4-dimensional hypervolume of coordinates, defined by two corner-point vectors
typedef struct box4d
{
	u_vector4d	start;
	u_vector4d	end;
}					s_box4d;
TYPEDEF_ALIAS(		s_box4d, BOX_4D, STRUCT)



//! An interval/range, defined by a 'start' number and 'end' number
typedef s_box1d	s_interval;
TYPEDEF_ALIAS(	s_interval, INTERVAL, STRUCT)



//! The type of function which takes a 1-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func1)(t_float const v);
//! The type of function which takes a 2-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func2)(u_vector2d const v);
//! The type of function which takes a 3-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func3)(u_vector3d const v);
//! The type of function which takes a 4-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func4)(u_vector4d const v);



/*
**	NB: For a coordinate box in the input space R^3, the volume computed
**	by the integral is thus technically a 4-hypervolume (since you
**	add a dimension because of the output space of dimension 1).
*/
// TODO document these functions
//t_float	lin_integrate(sf, domain);
t_float		c_integrate(f_float_function const f, s_interval const domain, t_float step);
t_float		c_mc_integrate_1d(f_scalar_func1 const sf, s_box1d const domain);
t_float		c_mc_integrate_2d(f_scalar_func2 const sf, s_box2d const domain);
t_float		c_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain);
t_float		c_mc_integrate_4d(f_scalar_func4 const sf, s_box4d const domain);



t_float		c_distance_float(t_float x, t_float y);
t_f32		c_distance_f32  (t_f32   x, t_f32   y);
t_f64		c_distance_f64  (t_f64   x, t_f64   y);

t_uint		c_distance_uint(t_uint x, t_uint y);
t_u8		c_distance_u8  (t_u8   x, t_u8   y);
t_u16		c_distance_u16 (t_u16  x, t_u16  y);
t_u32		c_distance_u32 (t_u32  x, t_u32  y);
t_u64		c_distance_u64 (t_u64  x, t_u64  y);

t_sint		c_distance_int (t_sint x, t_sint y);
t_s8		c_distance_s8  (t_s8  x, t_s8  y);
t_s16		c_distance_s16 (t_s16 x, t_s16 y);
t_s32		c_distance_s32 (t_s32 x, t_s32 y);
t_s64		c_distance_s64 (t_s64 x, t_s64 y);
// TODO distance manh, eucl, inf for 2d, 3d and 4d



/*! @} */
HEADER_END
#endif
