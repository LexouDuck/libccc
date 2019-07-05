#include "../../libft_math.h"
#include "../../libft_memory.h"



static t_float	inv_factorial(t_u32 n)
{
	static t_float	res[16] =
	{
		1, 1, 0.5, 1. / 6,
		1. / 24, 1. / 120, 1. / 720, 1. / 5040,
		1. / 40320, 1. / 362880, 1. / 3628800, 1. / 39916800,
		1. / 479001600, 1. / 6227020800, 1. / 87178291200, 1. / 1307674368000
	};

	return (res[n]); //static so it shouldn't be called with any weird values
//	return (n >= 16) ? 0. : res[n];
}



/*
** ===============================
**           Trigonometry
** ===============================
*/

//TODO Check if rounding algorithm for C99 compiler float->int conversion is floor()
t_float			ft_fmod_tau(t_float x)
{
	t_float		a;
	t_s32		floor_a;

	a = x * INV_TAU;
	floor_a = a;
	return (a - floor_a) * TAU;
}

t_float			ft_cos(t_float t)
{
	t_float		res;
	t_bool		sign; //True for negative
	t_float		t_p2;
	t_float		t_p4;
	t_float		t_p6;
	t_float		t_p8;

	sign = 0;
	if (t < 0.)
		t = -t;
	if (t > TAU)
		t = ft_fmod_tau(t);
	if (t > PI)
		t = PI - (t - PI);
	if (t > HALF_PI)
	{
		t = HALF_PI - (t - HALF_PI);
		sign = -1;
	}

	t_p2 = t * t;
	t_p4 = t_p2 * t_p2;
	t_p6 = t_p2 * t_p4;
	t_p8 = t_p4 * t_p4;

	res = 1.;
	res -= t_p2 * 0.5;
	res += t_p4 * inv_factorial(4);
	res -= t_p6 * inv_factorial(6);
	res += t_p8 * inv_factorial(8);
	res -= t_p8 * t_p2 * inv_factorial(10);
	res += t_p8 * t_p4 * inv_factorial(12);
	res -= t_p8 * t_p6 * inv_factorial(14);

	return sign ? -res : res;
}

t_float			ft_sin(t_float t)
{
	t_float		res;
	t_bool		sign; //True for negative
	t_float		t_p2;
	t_float		t_p3;
	t_float		t_p5;
	t_float		t_p7;
	t_float		t_p9;
	t_float		t_p11;
	t_float		t_p13;

	sign = 0;
	if (t < 0.)
	{
		t = -t;
		sign = !sign;
	}
	if (t > TAU)
		t = ft_fmod_tau(t);
	if (t > PI)
	{
		t = PI - (t - PI);
		sign = !sign;
	}
	if (t > HALF_PI)
		t = HALF_PI - (t - HALF_PI);

	t_p2 = t * t;
	t_p3 = t * t_p2;
	t_p5 = t_p2 * t_p3;
	t_p7 = t_p2 * t_p5;
	t_p9 = t_p2 * t_p7;
	t_p11 = t_p2 * t_p9;
	t_p13 = t_p2 * t_p11;

	res = t;
	res -= t_p3 * inv_factorial(3);
	res += t_p5 * inv_factorial(5);
	res -= t_p7 * inv_factorial(7);
	res += t_p9 * inv_factorial(9);
	res -= t_p11 * inv_factorial(11);
	res += t_p13 * inv_factorial(13);
	res -= t_p13 * t_p2 * inv_factorial(15);

	return sign ? -res : res;
}

/*
** ===============================
**    Logarithms & Exponentials
** ===============================
*/

t_float		ft_exp(t_float x)
{
	t_float		i;
	t_float		acc_i;
	t_float		acc_x;
	t_float		result;
	t_float		prev_res;

	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	prev_res = 0.;
	while (result != prev_res)
	{
		prev_res = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
}

/*
** The following pair of functions return the natural logarithm of f.
** ln(f) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** F32_EXP_ZERO = 0x3F800... is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_f32	ft_ln32_taylor_series(t_f32 x)
{
	t_f32	result;
	t_f32	prev_res;
	t_f32	powx;
	t_f32	i;

	i = 2.f;
	powx = x;
	result = x;
	while (powx != 0.f)
	{
		powx *= x;
		result += (((((int)i % 2)) * 2) - 1.f) * (powx / i);
		if (result == prev_res)
			break ;
		prev_res = result;
		++i;
	}
	return (result);
}

t_f32			ft_ln32(t_f32 x)
{
	t_f32	result;
	t_u32	tmp;
	t_u32	norm;
	t_s32	exp_b2;

	if (x < 0.f)
		return NAN;
	if (x == 0.f)
		return NEG_INF;
	if (x == 1.f)
		return (0.f);
	if (x == POS_INF)
		return (POS_INF);
	if (x < 1.f || 2.f <= x)
	{
		ft_memcpy(&tmp, &x, sizeof(t_u32));
		norm = (tmp & (F32_MSB | F32_MANTISSA)) | F32_EXP_ZERO;
		ft_memcpy(&x, &norm, sizeof(t_u32));
		result = ft_ln32(x);
		exp_b2 = ((tmp << 1) >> (F32_MANT_BIT_NB + 1)) - F32_EXP_BIAS;
		return (LN2 * exp_b2 + result);
	}
	if (1.9f <= x && x < 2.f)
		return (ft_ln32(x * DIV_2_BY_3) + LN_3DIV2);
	result = ft_ln32_taylor_series(x - 1.f);
	return (result);
}

/*
** The following pair of functions return the natural logarithm of lf.
** ln(lf) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** F64_EXP_ZERO = 0x3FF00... is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_f64	ft_ln64_taylor_series(t_f64 x)
{
	t_f64	result;
	t_f64	prev_res;
	t_f64	powx;
	t_f64	i;

	i = 2.;
	powx = x;
	result = x;
	while (powx != 0.)
	{
		powx *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (powx / i);
		if (result == prev_res)
			break ;
		prev_res = result;
		++i;
	}
	return (result);
}

#include <stdio.h>

t_f64			ft_ln64(t_f64 lf)
{
	t_f64	result;
	t_u64	tmp; //a raw memory copy
	t_u64	norm; //the float x in x*2^n in raw memory
	t_s32	exp_b2;

	if (lf < 0.)
		return NAN;
	if (lf == 0.)
		return NEG_INF;
	if (lf == 1.)
		return (0.);
	if (lf == POS_INF)
		return (POS_INF);
	if (lf < 1. || 2. <= lf)
	{
		ft_memcpy(&tmp, &lf, sizeof(t_u64));
		norm = (tmp & (F64_MSB | F64_MANTISSA)) | F64_EXP_ZERO;
		ft_memcpy(&lf, &norm, sizeof(t_u64));
		result = ft_ln64(lf);
		exp_b2 = ((tmp << 1) >> (F64_MANT_BIT_NB + 1)) - F64_EXP_BIAS;
		return (LN2 * exp_b2 + result);
	}
	if (1.9 <= lf && lf < 2.)
		return (ft_ln64(lf * DIV_2_BY_3) + LN_3DIV2);
	result = ft_ln64_taylor_series(lf - 1.);
	return (result);
}

#ifdef _FLOAT_32_
	inline t_float			ft_ln(t_float x)
	{
		return (ft_ln32(x));
	}
#endif
#ifdef _FLOAT_64_
	inline t_float			ft_ln(t_float x)
	{
		return (ft_ln64(x));
	}
#endif

inline t_float				ft_lg(t_float x)
{
	return ft_ln(x) / ((t_float)(LN2));
}

inline t_float				ft_log(t_float x)
{
	return ft_ln(x) / ((t_float)(LN10));
}

inline t_float				ft_logn(t_float x, t_float n)
{
	if (n == 2)
		return ft_lg(x);
	else if (n == 10)
		return ft_log(x);
	else
		return ft_ln(x) / ft_ln(n);
}



/*
** ===============================
**        Miscellaneous
** ===============================
*/

/*
** Useful when you want to square an expression optimally
*/
inline t_float		ft_sqr(t_float x)
{
	return (x * x);
}

/*
** Core idea is that sqrt(x) == x^(1/2) and that x is a float so
** x^(1/2) == (m * 2^n)^(1/2) == m^(1/2) * 2^(n * 1/2)
** with m between 1 and 2, and thus a taylor series can be used.
** NB: Watch the parity of n.
**
** Based on Heron's algorithm
*/

t_f32		ft_sqrt32(t_f32 x)
{
	t_f32		res = 1.f;
	t_f32		limit;
	t_s8		exp_b2;
	t_u32		norm = 0;	
	t_u32		a;
//	t_u32		b;

	if (x < 0)
		return (NAN);

	if (x < 1.f || 2.f <= x)
	{
		ft_memcpy(&norm, &x, sizeof(t_u32));
		exp_b2 = (t_s16)((norm << 1) >> (F32_MANT_BIT_NB + 1)) - F32_EXP_BIAS;
		norm = (norm & F32_MANTISSA) | F32_EXP_ZERO;
		ft_memcpy(&x, &norm, sizeof(t_u32));
		if (exp_b2 > 0)
		{
			if (exp_b2 % 2)
				res *= SQRT2;
			exp_b2 = exp_b2 / 2;
		}
		else
		{
			if (exp_b2 % 2)
				res *= INV_SQRT2;
			exp_b2 = exp_b2 / 2;
		}
		a = exp_b2 + F32_EXP_BIAS;
		a = a << F32_MANT_BIT_NB;
		res *= *(t_f32*)(&a);
	}
/*
	norm = (norm & F32_MANTISSA) | 0x00800000;//corresponds to the hidden bit
	b = norm;
	norm = 3.f;
	a = 3.f;
	norm = b / norm;
	norm = (norm + a) >> 1;
	a = norm;
	norm = b / norm;
	norm = (norm + a) >> 1;
	a = norm;
	norm = b / norm;
	norm = (norm + a) >> 1;

//	a = (F32_MANT_BIT_NB + F32_EXP_BIAS) << F32_MANT_BIT_NB;
	res *= norm * *(t_f32*)(&a);
*/
	limit = 1.5f;
	limit = 0.5 * (limit + x / limit);
	limit = 0.5 * (limit + x / limit);
	limit = 0.5 * (limit + x / limit);

	return (res * limit);
}


t_float				ft_fmod(t_float x, t_float y)
{
	t_float		a;
	t_s32		floor_a;

	a = x / y;
	floor_a = a;
	return (a - floor_a) * y;
}