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
# define LIBFT_MATH_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
** Various relevant constants to speed up our homemade versions of some
** fundamental algorithms and functions.
*/

# define DIV1_BY10			0x1.999999999999Ap-4
# define LN2_DIV_LN10		0x1.34413509F79FFp-2
# define LN_3DIV2			0x1.9F323ECBF984Cp-2
# define DIV_2_BY_3			0x1.5555555555556p-1
# define LN2				0x1.62E42FEFA39EFp-1
# define LN10				0x1.26BB1BBB55516p+1
# define SQRT2				0x1.6A09E667F3BCDp+0

# define HALF_PI			0x1.921fb54442d18p+0
# define PI					0x1.921fb54442d18p+1
# define TAU 				0x1.921fb54442d18p+2
# define INV_PI				0x1.45f306dc9c883p-2
# define INV_TAU			0x1.45f306dc9c883p-3

# define POS_INF			(1. / 0.)
# define NEG_INF			(-1. / 0.)
# ifndef NAN
#  define NAN				(0. / 0.)
# endif
# define IS_NAN(x)			((x) != (x))

# define F32_MSB			0x80000000
# define F32_EXPONENT		0x7F800000
# define F32_EXP_ZERO		0x3F800000
# define F32_MANTISSA		0x007FFFFF
# define F32_EXP_BIAS		127
# define F32_EXP_BIT_NB		8
# define F32_MANT_BIT_NB	23

# define F64_MSB			0x8000000000000000
# define F64_EXPONENT		0x7FF0000000000000
# define F64_EXP_ZERO		0x3FF0000000000000
# define F64_MANTISSA		0x000FFFFFFFFFFFFF
# define F64_EXP_BIAS		1023
# define F64_EXP_BIT_NB		11
# define F64_MANT_BIT_NB	52

# define SAMPLE_NB			1024



# ifndef ABS
#  define ABS(x)				((x) < 0 ? -(x) : (x))
# endif

/*
** ************************************************************************** *|
**                         Classical Real Functions                           *|
** ************************************************************************** *|
*/

//t_f32						ft_cos32(t_f32 x);
//t_f64						ft_cos64(t_f64 x);
t_float					ft_cos(t_float t);
//t_f32						ft_sin32(t_f32 x);
//t_f64						ft_sin64(t_f64 x);
t_float					ft_sin(t_float t);
//t_f32						ft_tan32(t_f32 x);
//t_f64						ft_tan64(t_f64 x);
//t_float					ft_tan(t_float t);



t_float					ft_exp(t_float x);
t_f32					ft_ln32(t_f32 x);
t_f64					ft_ln64(t_f64 lf);
t_float					ft_ln(t_float x);
t_float					ft_lg(t_float x);
t_float					ft_log(t_float x);
t_float					ft_logn(t_float x, t_float n);

t_float					ft_sqr(t_float x);
//t_float					ft_sqrt(t_float x);
t_float					ft_fmod(t_float x, t_float y);


/*
** ************************************************************************** *|
**                             Algebra & Calculus                             *|
** ************************************************************************** *|
*/

typedef	union	u_vec2
{
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

	t_float		values[2];
}				t_vec2;

typedef	union	u_vec3
{
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

	t_float		values[3];
}				t_vec3;

/*
** Be coherent when using 4D vectors: memory is in the order xyz-t
** but the others are s-ijk and a-rgb
*/
typedef	union	u_vec4
{
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

	t_float		values[4];
}				t_vec4;


typedef		t_float	(*t_scalar_func1)(t_float const v);
typedef		t_scalar_func1	t_real_func;
typedef		t_float	(*t_scalar_func2)(t_vec2 const v);
typedef		t_float	(*t_scalar_func3)(t_vec3 const v);
typedef		t_float	(*t_scalar_func4)(t_vec4 const v);


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
t_float		ft_integrate(t_real_func const f, t_interval const domain,
												t_float step);
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
//TODO distance manh, eucl, inf for 2d, 3d and 4d


/*
** ************************************************************************** *|
**                      Statistics & Probabilities                            *|
** ************************************************************************** *|
*/

# define PROB_APPROX			0.000001


typedef struct	s_int_list
{
	t_int		*data;
	t_u32		len;
}				t_int_list;

typedef struct	s_float_list
{
	t_float		*data;
	t_u32		len;
}				t_float_list;

/*
** Use only to signify a list with no repeating values.
*/
typedef t_int_list		t_int_set;
typedef t_float_list	t_float_set;
/*
** Use only to signify a list that has been ordered.
*/
typedef t_int_list		t_int_list_sorted;
typedef t_float_list	t_float_list_sorted;

/*
** Remember:
**
** A random variable X is a function from an input set O to an output set V,
** where:
**		- The universe O of possible events is the input set of X.
**		- The universe O is endowed with a sigma-algebra A (think "power set or
**			appropriate continuous extension of the power set"). Events are the
**			members of A, or equivalently, events are the subsets of O.
**		- P is a measure over A with values in [0, 1] such that the event for
**			the whole of O is given measure 1 (=all possibilites). Generally P
**			is found/constructed by taking some obvious	measure M on O (like
**			Lebesgue or counting) and normalizing by defining for every event
**			'a' the following: P(a) = M(a) / M(O).
**		- The triplet (O, A, P) is called a probability space. It's in a sense
**			our "full" input space with all necessary structure.
**		- probability for a given output Y is the measure of the preimage of
**			Y by f. Ie, the measure of the set X in O, or element a in A,
**			such that f(X) = Y.
**			Eg, the probability of getting an even number on a uniform 6-sided
**			dice (event "e") is 1/2 because M(e) = #({2,4,6}) = 3 and
**			M(O) = #({1,2,3,4,5,6}) = 6 and P(e)= M(e) / M(O) = 3/6 = 1/2.
**		- "values" of X are the values in the output space V.
**		- the output set V is generally R, sometimes R^n, rarely N without
**			extending it to R naturally (ie, medians, average, etc. of integers
**			end up in the real numbers anyways).
**		- a probability distribution f is a function from V to [0,1] that
**			assigns its probability to each event, represented not as an element
**			of A, but as the (set of) value(s) of that event in V.
**		- if the input set is discrete, f is a "probability mass function".
**		- if the input set is continuous, f is a "probability density function".
**
** To summarize, there are 3 major spaces: (O, A, P), V and [0,1], and they are
** linked thus:
**		- X: (O, A, P) -> V
**		- P: (O, A, P) -> [0, 1]
**		- f: V -> [0, 1]
**
** In the following implementation, discrete universes are kept finite and
** indexed, each atomic event is given by an index of the list.
** "value[i]" corresponds to X(i); "prob[i]" corresponds to f(X(i)).
*/

/*
** A struct for the probability mass function describing a discrete random var.
*/
typedef struct	s_prob_mass
{
	t_float				*value;
	t_float				*prob;
	t_u32				len;
}				t_prob_mass;

/*
typedef struct	s_prob_dens
{
	t_float		(*distrib)(); //? cumul distib ?
}				t_prob_dens;
*/

t_int_list			ft_stat_merge_ilst(t_int_list *start,
							t_int_list *append);
t_float_list		ft_stat_merge_flst(t_float_list *start,
							t_float_list *append);


t_int_list 			ft_stat_quicksort_i(t_int_list const i_lst);
t_float_list 		ft_stat_quicksort_f(t_float_list const f_lst);

/*
** List is supposed to be already in order for this to return the right result.
*/
t_float				ft_stat_median_i(t_int_list_sorted const i_lst);
t_float				ft_stat_median_f(t_float_list_sorted const f_lst);

t_float				ft_stat_average_i(t_int_list const i_lst);
t_float				ft_stat_average_f(t_float_list const f_lst);

t_float				ft_stat_variance_i(t_int_list const i_lst);
t_float				ft_stat_variance_f(t_float_list const f_lst);

t_float				ft_stat_stddev_i(t_int_list const i_lst);
t_float				ft_stat_stddev_f(t_float_list const f_lst);

t_int_list			ft_stat_new_ilst(t_u32 len);
t_float_list		ft_stat_new_flst(t_u32 len);
void				ft_stat_free_ilst(t_int_list *ilst);
void				ft_stat_free_flst(t_float_list *flst);

/*
void				ft_stat_decile_i(t_int_list const i_lst);
void				ft_stat_decile_f(t_float_list const f_lst);


t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst);
t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
*/

t_prob_mass			ft_stat_new_pmf(t_u32 len);
void				ft_stat_free_pmf(t_prob_mass *drv);
t_int_list			ft_stat_ilst_to_iset(t_int_list const ilst);
t_u32				ft_stat_ilst_count(t_int_list ilst, t_int elem);
t_prob_mass			ft_stat_ilst_to_pmf(t_int_list const ilst);



/*
** ************************************************************************** *|
**                         Random Number Generator                            *|
** ************************************************************************** *|
*/

/*
** Random number generator. Modulus is 2^31
**
** - OFFSET and MODULUS are mutually prime.
** - CEIL_SQRT_MOD % 4 should be = 1 because MODULUS is a multiple of 4
** - For all P prime divisors of MODULUS, a % p = 1
** - OFFSET should be small compared to the two other parameters
** - The bitwise & is applied, which explains the choice of modulus to be
**		2^31 - 1 in implementation (could also be called RAND_MAX)
**
** Basic RNG formula is:
**		new_nb = (CEIL_SQRT_MOD  * old_nb + OFFSET) % MODULUS
*/

# define DEFAULT_SEED	0x93E21FD5

# define MODULUS		0x7FFFFFFF		
# define CEIL_SQRT_MOD	46341
# define OFFSET			2835



void		ft_random_set_seed(t_u32 seed);
void		ft_random_renew_seed(void);
t_u32		ft_random(void);
t_u32		ft_random_0_to_pow2n(t_u32 n);
t_u32		ft_random_0_to_n(t_u32 n);
t_int		ft_random_int_a_to_b(t_int a, t_int b);
t_float		ft_random_float_0_to_1(void);
t_float		ft_random_float_a_to_b(t_float a, t_float b);

#endif
