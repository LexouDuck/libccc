/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
#define LIBFT_MATH_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define FT_Modulo(x, y)			ft_fmod(x, y)

#define FT_Power(x, y)			ft_pow(x, y)

#define FT_SquareRoot(x)		ft_sqrt(x)
#define FT_CubicRoot(x)			ft_cbrt(x)
#define FT_NRoot(x, n)			ft_nrt(x, n)



#define FT_Exp(x)				ft_exp(x)

#define FT_Ln(x)				ft_ln(x)

#define FT_Log_2(x)				ft_lg(x)
#define FT_Log_10(x)			ft_log(x)
#define FT_Log_N(x, n)			ft_logn(x, n)



#define FT_Cos(x)				ft_cos(x)
#define FT_Sin(x)				ft_sin(x)
#define FT_Tan(x)				ft_tan(x)

#define FT_ArcCos(x)			ft_acos(x)
#define FT_ArcSin(x)			ft_asin(x)
#define FT_ArcTan(x)			ft_atan(x)

#define FT_ArcTan2(x, y)		ft_atan2(x, y)

#define FT_CosH(x)				ft_cosh(x)
#define FT_SinH(x)				ft_sinh(x)
#define FT_TanH(x)				ft_tanh(x)

#define FT_ArcCosH(x)			ft_acosh(x)
#define FT_ArcSinH(x)			ft_asinh(x)
#define FT_ArcTanH(x)			ft_atanh(x)



// TODO add other function macros for integral, distance, etc



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
** Various relevant constants to speed up our homemade versions of some
** fundamental algorithms and functions.
*/

#define QUARTER_PI		DIV_PI_4
#define HALF_PI			DIV_PI_2
#define DIV_PI_4		(t_float)0x1.921FB54442D18p-1
#define DIV_PI_2		(t_float)0x1.921FB54442D18p+0
#define PI				(t_float)0x1.921FB54442D18p+1
#define TAU 			(t_float)0x1.921FB54442D18p+2
#define INV_PI			(t_float)0x1.45F306DC9C883p-2
#define INV_TAU			(t_float)0x1.45F306DC9C883p-3

#define E				(t_float)0x1.5BF0A8B145769p+1
#define LN_2			(t_float)0x1.62E42FEFA39EFp-1
#define LN_10			(t_float)0x1.26BB1BBB55516p+1

#define SQRT_2			(t_float)0x1.6A09E667F3BCDp+0
#define INV_SQRT_2		(t_float)0x1.6A09E667F3BCDp-1
#define SQRT_3			(t_float)0x1.BB67AE8584CAAp+0
#define INV_SQRT_3		(t_float)0x1.279A74590331Cp-1
#define SQRT_5			(t_float)0x1.1E3779B97F4A7p+1
#define INV_SQRT_5		(t_float)0x1.C9F25C5BFEDD9p-2



#define SAMPLE_NB		1024



#ifndef ABS
#define ABS(x)		((x) < 0 ? -(x) : (x))
#endif

#ifndef SIGN
#define SIGN(x)		((x) < 0 ? -1 : +1)
#endif



/*
** ************************************************************************** *|
**                         Classical Real Functions                           *|
** ************************************************************************** *|
*/

t_float		ft_fmod(t_float x, t_float y);

t_float		ft_pow(t_float x, t_float y);

t_float		ft_sqrt(t_float x);
t_float		ft_cbrt(t_float x);
t_float		ft_nrt(t_float x, t_u8 n);



t_float		ft_exp(t_float x);

t_float		ft_ln(t_float x);

t_float		ft_lg(t_float x);
t_float		ft_log(t_float x);
t_float		ft_logn(t_float x, t_float n);



t_float		ft_cos(t_float x);
t_float		ft_sin(t_float x);
t_float		ft_tan(t_float x);

t_float		ft_acos(t_float x);
t_float		ft_asin(t_float x);
t_float		ft_atan(t_float x);

t_float		ft_atan2(t_float x, t_float y);

t_float		ft_cosh(t_float x);
t_float		ft_sinh(t_float x);
t_float		ft_tanh(t_float x);

t_float		ft_acosh(t_float x);
t_float		ft_asinh(t_float x);
t_float		ft_atanh(t_float x);



/*
** ************************************************************************** *|
**                             Algebra & Calculus                             *|
** ************************************************************************** *|
*/

typedef	union	u_vec2
{
	t_float		values[2];
	struct
	{
		t_float		x;
		t_float		y;
	};
	struct
	{
		t_float		re;
		t_float		im;
	};
}				t_vec2;

typedef	union	u_vec3
{
	t_float		values[3];
	struct
	{
		t_float		x;
		t_float		y;
		t_float		z;
	};
	struct
	{
		t_float		r;
		t_float		g;
		t_float		b;
	};
	struct
	{
		t_float		h;
		t_float		s;
		t_float		l;
	};
}				t_vec3;

/*
** Be coherent when using 4D vectors: memory is in the order xyz-t
** but the others are s-ijk and a-rgb
*/
typedef	union	u_vec4
{
	t_float		values[4];
	struct
	{
		t_float		x;
		t_float		y;
		t_float		z;
		t_float		t;
	};
	struct
	{
		t_float		s;
		t_float		i;
		t_float		j;
		t_float		k;
	};
	struct
	{
		t_float		a;
		t_float		r;
		t_float		g;
		t_float		b;
	};
}				t_vec4;



typedef		t_float	(*t_scalar_func1)(t_float const v);
typedef		t_float	(*t_scalar_func2)(t_vec2 const v);
typedef		t_float	(*t_scalar_func3)(t_vec3 const v);
typedef		t_float	(*t_scalar_func4)(t_vec4 const v);
typedef		t_scalar_func1	t_real_func;



/*
** Note that for a coordinate box in the input space R^3, the volume
** computed by the integral is thus technically a 4-hypervolume (since you
** add a dimension because of the output space of dimension 1).
** The box is assumed to be composed of orthogonal edges (brick shaped),
** which is why only two vectors are necessary to define it.
*/

typedef struct		s_1d_box
{
	t_float		start;
	t_float		end;
}					t_1d_box;
typedef t_1d_box	t_interval;

typedef struct		s_2d_box
{
	t_vec2	start;
	t_vec2	end;
}					t_2d_box;

typedef struct		s_3d_box
{
	t_vec3	start;
	t_vec3	end;
}					t_3d_box;

typedef struct		s_4d_box
{
	t_vec4	start;
	t_vec4	end;
}					t_4d_box;

//t_float	lin_integrate(sf, domain);
t_float		ft_integrate(t_real_func const f, t_interval const domain, t_float step);
t_float		ft_mc_integrate_1d(t_scalar_func1 const sf, t_1d_box const domain);
t_float		ft_mc_integrate_2d(t_scalar_func2 const sf, t_2d_box const domain);
t_float		ft_mc_integrate_3d(t_scalar_func3 const sf, t_3d_box const domain);
t_float		ft_mc_integrate_4d(t_scalar_func4 const sf, t_4d_box const domain);

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

#endif
