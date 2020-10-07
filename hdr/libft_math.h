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

#define Math_GetExponent	ft_getexp
#define Math_GetExp			ft_getexp
#define Math_AbsoluteValue	ft_fabs
#define Math_Abs			ft_fabs
#define Math_Modulo			ft_fmod
#define Math_Mod			ft_fmod

#define Math_Round			ft_round
#define Math_Truncate		ft_trunc
#define Math_Floor			ft_floor
#define Math_Ceiling		ft_ceil
#define Math_Ceil			ft_ceil

#define Math_Power			ft_pow
#define Math_Pow			ft_pow
#define Math_SquareRoot		ft_sqrt
#define Math_SqRt			ft_sqrt
#define Math_CubicRoot		ft_cbrt
#define Math_CbRt			ft_cbrt
#define Math_NRoot			ft_nrt
#define Math_NRt			ft_nrt

#define Math_Exponential		ft_exp
#define Math_Exp				ft_exp
#define Math_NaturalLogarithm	ft_ln
#define Math_Ln					ft_ln
#define Math_Logarithm_Base2	ft_lg
#define Math_Log_2				ft_lg
#define Math_Logarithm_Base10	ft_log
#define Math_Log_10				ft_log
#define Math_Logarithm_BaseN	ft_logn
#define Math_Log_N				ft_logn



#define Math_Cosine				ft_cos
#define Math_Cos				ft_cos
#define Math_Sine				ft_sin
#define Math_Sin				ft_sin
#define Math_Tangent			ft_tan
#define Math_Tan				ft_tan
#define Math_InvCosine			ft_acos
#define Math_ArcCos				ft_acos
#define Math_InvSine			ft_asin
#define Math_ArcSin				ft_asin
#define Math_InvTangent			ft_atan
#define Math_ArcTan				ft_atan

#define Math_ArcTangent_YoverX	ft_atan2
#define Math_ArcTan2			ft_atan2

#define Math_Cosine_Hyperbolic		ft_cosh
#define Math_CosH					ft_cosh
#define Math_Sine_Hyperbolic		ft_sinh
#define Math_SinH					ft_sinh
#define Math_Tangent_Hyperbolic		ft_tanh
#define Math_TanH					ft_tanh
#define Math_InvCosine_Hyperbolic	ft_acosh
#define Math_InvCosH				ft_acosh
#define Math_InvSine_Hyperbolic		ft_asinh
#define Math_InvSinH				ft_asinh
#define Math_InvTangent_Hyperbolic	ft_atanh
#define Math_InvTanH				ft_atanh



// TODO add other function macros for integral, distance, etc



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Expands to the absolute value of 'x'
*/
#ifndef ABS
#define ABS(x)		((x) < 0 ? -(x) : (x))
#endif

/*
**	Expands to the minimum value of 'x' and 'y'
*/
#ifndef MIN
#define MIN(x, y)		((x) < (y) ? (x) : (y))
#endif

/*
**	Expands to the maximum value of 'x' and 'y'
*/
#ifndef MAX
#define MAX(x, y)		((x) < (y) ? (y) : (x))
#endif


/*
**	Expands to +1 or -1 according to the sign of 'x'
*/
#ifndef SIGN
#define SIGN(x)		((x) < 0 ? -1 : +1)
#endif

/*
**	Floating-point "inf" value: can be positive or negative.
*/
#ifndef INFINITY
#define INFINITY		(1. / 0.)
#endif
#ifndef IS_INFINITY
#define IS_INFINITY(x)	((x) == INFINITY || (x) == -INFINITY)
#endif

/*
**	Floating-point "not a number" value.
*/
#ifndef NAN
#define NAN				(0. / 0.)
#endif
#ifndef IS_NAN
#define IS_NAN(x)		((x) != (x))
#endif

/*
**	This very small value is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable operation.
*/
#define FLOAT_BIAS		(1.0e-10)

/*
**	TODO document
*/
#define SAMPLE_NB		1024



/*
**	Various relevant constants to speed up our homemade versions of some
**	fundamental algorithms and functions.
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



/*
** ************************************************************************** *|
**                     Classical Real Number Operations                       *|
** ************************************************************************** *|
*/

t_s32		ft_getexp(t_float x);

t_float		ft_fabs(t_float x);

t_float		ft_fmod(t_float x, t_float y);

t_float		ft_round(t_float x); // TODO
t_float		ft_trunc(t_float x);
t_float		ft_floor(t_float x);
t_float		ft_ceil(t_float x);

t_float		ft_pow(t_float x, t_float y);
t_float		ft_pow_n(t_float x, t_int n);

t_float		ft_sqrt(t_float x);
t_float		ft_cbrt(t_float x);
t_float		ft_nrt(t_float x, t_u8 n);



t_float		ft_exp(t_float x);

t_float		ft_ln(t_float x);
t_float		ft_lg(t_float x);
t_float		ft_log(t_float x);
t_float		ft_log_n(t_float x, t_float n);



t_float		ft_cos(t_float x);
t_float		ft_sin(t_float x);
t_float		ft_tan(t_float x);

t_float		ft_acos(t_float x);
t_float		ft_asin(t_float x);
t_float		ft_atan(t_float x);

t_float		ft_atan2(t_float y, t_float x);

t_float		ft_cosh(t_float x);
t_float		ft_sinh(t_float x);
t_float		ft_tanh(t_float x);

t_float		ft_acosh(t_float x);
t_float		ft_asinh(t_float x);
t_float		ft_atanh(t_float x);

// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?


#if (LIBFTCONFIG_FAST_APPROX_MATH == 0)

	#ifdef _FLOAT_32_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##f(x, y)); }
	#endif

	#ifdef _FLOAT_64_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME(x, y)); }
	#endif

	#ifdef _FLOAT_80_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##l(x, y)); }
	#endif

	#ifdef _FLOAT_128_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##q(x, y)); }
	#endif

#endif

/*
**	This union type is used in several math functions to handle float bits directly
*/
typedef union	u_float_cast_
{
	t_float		value_float;
#ifdef _FLOAT_32_
	t_s32		value_int;
#endif
#ifdef _FLOAT_64_
	t_s64		value_int;
#endif
#ifdef _FLOAT_80_
	t_s64[2]	value_int;
#endif
#ifdef _FLOAT_128_
	t_s64[2]	value_int;
#endif
}				u_float_cast;

/*
** ************************************************************************** *|
**                             Algebra & Calculus                             *|
** ************************************************************************** *|
*/

typedef struct	s_vec2_
{
	t_float		x;
	t_float		y;
}				s_vec2;

typedef struct	s_complex_
{
	t_float		re;
	t_float		im;
}				s_complex;

typedef	union	u_vec2_
{
	t_float		values[2];
	s_vec2		vect;
	s_complex	cplx;
}				u_vec2;



typedef struct	s_vec3_
{
	t_float		x;
	t_float		y;
	t_float		z;
}				s_vec3;

typedef struct	s_rgb_
{
	t_float		r;
	t_float		g;
	t_float		b;
}				s_rgb;

typedef struct	s_hsl_
{
	t_float		h;
	t_float		s;
	t_float		l;
}				s_hsl;

typedef	union	u_vec3_
{
	t_float		values[3];
	s_vec3		vect;
	s_rgb		rgb;
	s_hsl		hsl;
}				u_vec3;



/*
** Be coherent when using 4D vectors: memory is in the order xyz-t
** but the others are s-ijk and a-rgb
*/

typedef struct		s_vec4_
{
	t_float		x;
	t_float		y;
	t_float		z;
	t_float		t;
}					s_vec4;

typedef struct		s_quaternion_
{
	t_float		s;
	t_float		i;
	t_float		j;
	t_float		k;
}					s_quaternion;

typedef struct		s_argb_
{
	t_float		a;
	t_float		r;
	t_float		g;
	t_float		b;
}					s_argb;

typedef struct		s_ahsl_
{
	t_float		a;
	t_float		h;
	t_float		s;
	t_float		l;
}					s_ahsl;

typedef	union	u_vec4_
{
	t_float			values[4];
	s_vec4			vect;
	s_quaternion	quat;
	s_argb			argb;
	s_ahsl			ahsl;
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



/*
** ************************************************************************** *|
**                            Float Type Definitions                          *|
** ************************************************************************** *|
*/

/*
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
#define F32_SIGNED			0x80000000
#define F32_EXPONENT_BIAS	127
#define F32_EXPONENT		0x7F800000
#define F32_EXPONENT_ZERO	0x3F800000
#define F32_EXPONENT_BITS	8
#define F32_MANTISSA		0x007FFFFF
#define F32_MANTISSA_SIGNED	0x807FFFFF
#define F32_MANTISSA_BITS	23
#define F32_INIT_VALUE		0x1.p-23

/*
**	IEEE 754 64-bit floating point double-precision bitwise macros
*/
#define F64_SIGNED			0x8000000000000000
#define F64_EXPONENT_BIAS	1023
#define F64_EXPONENT		0x7FF0000000000000
#define F64_EXPONENT_ZERO	0x3FF0000000000000
#define F64_EXPONENT_BITS	11
#define F64_MANTISSA		0x000FFFFFFFFFFFFF
#define F64_MANTISSA_SIGNED	0x800FFFFFFFFFFFFF
#define F64_MANTISSA_BITS	52
#define F64_INIT_VALUE		0x1.p-52

/*
**	x86 80-bit floating point extended precision bitwise macros
*/
#define F80_SIGNED			0x80000000000000000000L
#define F80_EXPONENT_BIAS	16383
#define F80_EXPONENT		0x7FFF0000000000000000L
#define F80_EXPONENT_ZERO	0x3FFF0000000000000000L
#define F80_EXPONENT_BITS	15
#define F80_MANTISSA		0x0000FFFFFFFFFFFFFFFFL
#define F80_MANTISSA_SIGNED	0x8000FFFFFFFFFFFFFFFFL
#define F80_MANTISSA_BITS	64
#define F80_INIT_VALUE		0x1.p-64

/*
**	IEEE 754 128-bit floating point quadruple-precision bitwise macros
*/
#define F128_SIGNED				0x80000000000000000000000000000000L
#define F128_EXPONENT_BIAS		16383
#define F128_EXPONENT			0x7FFF0000000000000000000000000000L
#define F128_EXPONENT_ZERO		0x3FFF0000000000000000000000000000L
#define F128_EXPONENT_BITS		15
#define F128_MANTISSA			0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL
#define F128_MANTISSA_SIGNED	0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL
#define F128_MANTISSA_BITS		112
#define F128_INIT_VALUE			0x1.p-112



/*
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_, etc) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/

#ifdef _FLOAT_32_
	#define FLOAT_SIGNED			F32_SIGNED
	#define FLOAT_EXPONENT_BIAS		F32_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F32_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F32_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F32_EXPONENT_BITS
	#define FLOAT_MANTISSA			F32_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F32_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F32_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F32_INIT_VALUE
#endif

#ifdef _FLOAT_64_
	#define FLOAT_SIGNED			F64_SIGNED
	#define FLOAT_EXPONENT_BIAS		F64_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F64_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F64_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F64_EXPONENT_BITS
	#define FLOAT_MANTISSA			F64_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F64_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F64_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F64_INIT_VALUE
#endif

#ifdef _FLOAT_80_
	#define FLOAT_SIGNED			F80_SIGNED
	#define FLOAT_EXPONENT_BIAS		F80_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F80_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F80_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F80_EXPONENT_BITS
	#define FLOAT_MANTISSA			F80_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F80_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F80_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F80_INIT_VALUE
#endif

#ifdef _FLOAT_128_
	#define FLOAT_SIGNED			F128_SIGNED
	#define FLOAT_EXPONENT_BIAS		F128_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F128_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F128_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F128_EXPONENT_BITS
	#define FLOAT_MANTISSA			F128_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F128_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F128_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F128_INIT_VALUE
#endif

#endif
