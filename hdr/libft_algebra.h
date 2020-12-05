/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_algebra.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_ALGEBRA_H
#define __LIBFT_ALGEBRA_H
/*! @file libft_algebra.h
**	This header defines useful algebra and calculus types, and functions.
**	@addtogroup libft_math
**	@{
*/
// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A simple struct for storing 2-dimensional values
typedef struct	s_vec2_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
}				s_vec2;

//! A struct to store complex/imaginary number values
typedef struct	s_complex_
{
	t_float		re;			//! The "real" part of this complex number
	t_float		im;			//! The "imaginary" part of this complex number
}				s_complex;

//! This union stores a 2-dimensional value which can be accessed in several ways
typedef	union	u_vec2_
{
	t_float		values[2];	//! An array, to access the 2 values from within brackets
	s_vec2		vect;		//! A vector, to access the 2 coordinates as `.x` and `.y`
	s_complex	cplx;		//! A complex number, to access the 2 parts as `.re` and `.im`
}				u_vec2;



//! A simple struct for storing 3-dimensional values
typedef struct	s_vec3_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
	t_float		z;			//! The Z coordinate of this vector
}				s_vec3;

//! This union stores a 3-dimensional value which can be accessed in several ways
typedef	union	u_vec3_
{
	t_float		values[3];	//! An array, to access the 3 values from within brackets
	s_vec3		vect;		//! A vector, to access the 3 coordinates as `.x`, `.y` and `.z`
}				u_vec3;



//! A simple struct for storing 4-dimensional values
typedef struct		s_vec4_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
	t_float		z;			//! The Z coordinate of this vector
	t_float		t;			//! The T coordinate of this vector
}					s_vec4;

//! A struct for storing quaternions
typedef struct		s_quaternion_
{
	t_float		s;			//! The S value of this quaternion
	t_float		i;			//! The I value of this quaternion
	t_float		j;			//! The J value of this quaternion
	t_float		k;			//! The K value of this quaternion
}					s_quaternion;

//! This union stores a 4-dimensional value which can be accessed in several ways
/*!
**	NB: Make sure to be coherent when using 4D vectors:
**	memory layout is in the order `xyz-t` for the 's_vec4' struct,
**	but the other union structs divid it like `s-ijk` and `a-rgb`
*/
typedef	union	u_vec4_
{
	t_float			values[4];	//! An array, to access the 4 values from within brackets
	s_vec4			vect;		//! A vector, to access the 4 coordinates as `.x`, `.y`, `.z`, and `.t`
	s_quaternion	quat;		//! A quaternion, to access the 4 values as `.i`, `.j`, `.k`, and `.s`
}				u_vec4;



typedef		t_float	(*f_scalar_func1)(t_float const v);
typedef		t_float	(*f_scalar_func2)(u_vec2 const v);
typedef		t_float	(*f_scalar_func3)(u_vec3 const v);
typedef		t_float	(*f_scalar_func4)(u_vec4 const v);

typedef		t_float	(*f_real_function)(t_float x);
typedef		t_float	(*f_real_operator)(t_float x, t_float y);



/*
** Note that for a coordinate box in the input space R^3, the volume
** computed by the integral is thus technically a 4-hypervolume (since you
** add a dimension because of the output space of dimension 1).
** The box is assumed to be composed of orthogonal edges (brick shaped),
** which is why only two vectors are necessary to define it.
*/

typedef struct		s_box1d_
{
	t_float		start;
	t_float		end;
}					s_box1d;

typedef struct		s_box2d_
{
	u_vec2	start;
	u_vec2	end;
}					s_box2d;

typedef struct		s_box3d_
{
	u_vec3	start;
	u_vec3	end;
}					s_box3d;

typedef struct		s_box4d_
{
	u_vec4	start;
	u_vec4	end;
}					s_box4d;

typedef s_box1d	s_interval;



/*
** ************************************************************************** *|
**                     Classical Real Number Operations                       *|
** ************************************************************************** *|
*/

//t_float	lin_integrate(sf, domain);
t_float		ft_integrate(f_real_function const f, s_interval const domain, t_float step);
t_float		ft_mc_integrate_1d(f_scalar_func1 const sf, s_box1d const domain);
t_float		ft_mc_integrate_2d(f_scalar_func2 const sf, s_box2d const domain);
t_float		ft_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain);
t_float		ft_mc_integrate_4d(f_scalar_func4 const sf, s_box4d const domain);

t_f32		ft_distance_f32(t_f32 x, t_f32 y);
t_f64		ft_distance_f64(t_f64 x, t_f64 y);
t_u8		ft_distance_u8(t_u8 x, t_u8 y);
t_u16		ft_distance_u16(t_u16 x, t_u16 y);
t_u32		ft_distance_u32(t_u32 x, t_u32 y);
t_u64		ft_distance_u64(t_u64 x, t_u64 y);
t_s8		ft_distance_s8(t_s8 x, t_s8 y);
t_s16		ft_distance_s16(t_s16 x, t_s16 y);
t_s32		ft_distance_s32(t_s32 x, t_s32 y);
t_s64		ft_distance_s64(t_s64 x, t_s64 y);
t_float		ft_distance_float(t_float x, t_float y);
t_uint		ft_distance_uint(t_uint x, t_uint y);
t_int		ft_distance_int(t_int x, t_int y);
// TODO distance manh, eucl, inf for 2d, 3d and 4d



/*! @} */
HEADER_END
#endif
