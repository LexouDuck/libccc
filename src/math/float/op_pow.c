
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Pow, pow)
#elif LIBCONFIG_USE_CCC_MATH

#if 1
// crazy approximate method
#define DEFINEFUNC_MATH_FLOAT_POW(BITS, HALF, MAGIC) \
t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	union { t_f##BITS f; t_s##HALF i[2]; } u = { x }; \
	u.i[1] = (t_s##HALF)(y * (t_f##BITS)(u.i[1] - MAGIC) + MAGIC); \
	u.i[0] = 0; \
	return u.f; \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_MATH_FLOAT_POW(16, 8, ?)
#endif
DEFINEFUNC_MATH_FLOAT_POW(32, 16, 1064866816)

DEFINEFUNC_MATH_FLOAT_POW(64, 32, 1072632447)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_MATH_FLOAT_POW(80, 64, ?)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_MATH_FLOAT_POW(128, 64, ?)
#endif

#endif

#if 0
	u_float_cast result;
	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.value_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
#endif

// lame exp*ln method
#if 0 
	return (F##BITS##_Exp(y * F##BITS##_Log(x)));
#endif



#else


#define TABLEBITS_LOG2_POW_F32	4
#if TOINT_INTRINSICS
#define SCALEBITS_POW_F32	TABLEBITS_EXP_F32
#else
#define SCALEBITS_POW_F32	0
#endif
#define SCALE_POW_F32	((t_f64)(1 << SCALEBITS_POW_F32))

/*
TABLEBITS_EXP_F32 = 5

ULP error: 0.82 (~ 0.5 + relerr*2^24)
relerr: 1.27 * 2^-26 (Relative error ~= 128*Ln2*relerr_log2 + relerr_exp2)
relerr_log2: 1.83 * 2^-33 (Relative error of logx.)
relerr_exp2: 1.69 * 2^-34 (Relative error of exp2(ylogx).)
*/

#define N	(1 << TABLEBITS_LOG2_POW_F32)
#define OFF	0x3F330000

static const
struct data_pow_f32
{
	struct { t_f64 invc, logc; } table[N];
	t_f64 poly[5];
}
__data_pow_f32 =
{
	.table =
	{
		{ +0x1.661EC79F8F3BEp+0, -0x1.EFEC65B963019p-2 * SCALE_POW_F32 },
		{ +0x1.571ED4AAF883Dp+0, -0x1.B0B6832D4FCA4p-2 * SCALE_POW_F32 },
		{ +0x1.49539F0F010B0p+0, -0x1.7418B0A1FB77Bp-2 * SCALE_POW_F32 },
		{ +0x1.3C995B0B80385p+0, -0x1.39DE91A6DCF7Bp-2 * SCALE_POW_F32 },
		{ +0x1.30D190C8864A5p+0, -0x1.01D9BF3F2B631p-2 * SCALE_POW_F32 },
		{ +0x1.25E227B0B8EA0p+0, -0x1.97C1D1B3B7AF0p-3 * SCALE_POW_F32 },
		{ +0x1.1BB4A4A1A343Fp+0, -0x1.2F9E393AF3C9Fp-3 * SCALE_POW_F32 },
		{ +0x1.12358F08AE5BAp+0, -0x1.960CBBF788D5Cp-4 * SCALE_POW_F32 },
		{ +0x1.0953F419900A7p+0, -0x1.A6F9DB6475FCEp-5 * SCALE_POW_F32 },
		{ +0x1.0000000000000p+0, +0x0.0000000000000p+0 * SCALE_POW_F32 },
		{ +0x1.E608CFD9A47ACp-1, +0x1.338CA9F24F53Dp-4 * SCALE_POW_F32 },
		{ +0x1.CA4B31F026AA0p-1, +0x1.476A9543891BAp-3 * SCALE_POW_F32 },
		{ +0x1.B2036576AFCE6p-1, +0x1.E840B4AC4E4D2p-3 * SCALE_POW_F32 },
		{ +0x1.9C2D163A1AA2Dp-1, +0x1.40645F0C6651Cp-2 * SCALE_POW_F32 },
		{ +0x1.886E6037841EDp-1, +0x1.88E9C2C1B9FF8p-2 * SCALE_POW_F32 },
		{ +0x1.767DCF5534862p-1, +0x1.CE0A44EB17BCCp-2 * SCALE_POW_F32 },
	},
	.poly =
	{
		+0x1.27616C9496E0Bp-2 * SCALE_POW_F32,
		-0x1.71969A075C67Ap-2 * SCALE_POW_F32,
		+0x1.EC70A6CA7BADDp-2 * SCALE_POW_F32,
		-0x1.7154748BEF6C8p-1 * SCALE_POW_F32,
		+0x1.71547652AB82Bp+0 * SCALE_POW_F32,
	}
};

/*
**	Subnormal input is normalized so ix has negative biased exponent.
**	Output is multiplied by N (SCALE_POW_F32) if TOINT_INTRINICS is set.
*/
static inline
t_f64 F32_log2_inline(t_u32 ix)
{
	t_f64 z, r, r2, r4, p, q, y, y0, invc, logc;
	t_u32 iz, top, tmp;
	int k, i;

	/* x = 2^k z; where z is in range [OFF,2*OFF] and exact. The range is split into N subintervals. The ith subinterval contains z and c is near its center. */
	tmp = ix - OFF;
	i = (tmp >> (23 - TABLEBITS_LOG2_POW_F32)) % N;
	top = tmp & 0xff800000;
	iz = ix - top;
	k = (t_s32)top >> (23 - SCALEBITS_POW_F32); /* arithmetic shift */
	invc = __data_pow_f32.table[i].invc;
	logc = __data_pow_f32.table[i].logc;
	z = (t_f64)AS_F32(iz);

	/* log2(x) = log1p(z/c-1)/ln2 + log2(c) + k */
	r = z * invc - 1;
	y0 = logc + (t_f64)k;

	/* Pipelined polynomial evaluation to approximate log1p(r)/ln2. */
	r2 = r * r;
	y = __data_pow_f32.poly[0] * r + __data_pow_f32.poly[1];
	p = __data_pow_f32.poly[2] * r + __data_pow_f32.poly[3];
	r4 = r2 * r2;
	q = __data_pow_f32.poly[4] * r + y0;
	q = p * r2 + q;
	y = y * r4 + q;
	return y;
}

#define N_POW_F32	(1 << TABLEBITS_EXP_F32)
#undef SIGN_BIAS
#define SIGN_BIAS	(1 << (TABLEBITS_EXP_F32 + 11))

/*
**	The output of log2 and thus the input of exp2 is either scaled by N (in case of fast toint intrinsics) or not.
**	The unscaled xd must be in [-1021,1023], sign_bias sets the sign of the result.
*/
static inline
t_f32 F32_exp2_inline(t_f64 xd, t_u32 sign_bias)
{
	t_u64 ki, ski, t;
	t_f64 kd, z, r, r2, y, s;

	/* x = k/N + r with r in [-1/(2N), 1/(2N)] */
	kd = (t_f64)(xd + __data_exp_f32.shift_scaled);
	ki = AS_U64(kd);
	kd -= __data_exp_f32.shift_scaled; /* k/N */
	r = xd - kd;
	/* exp2(x) = 2^(k/N) * 2^r ~= s * (C0*r^3 + C1*r^2 + C2*r + 1) */
	t = __data_exp_f32.table[ki % N_POW_F32];
	ski = ki + sign_bias;
	t += ski << (52 - TABLEBITS_EXP_F32);
	s = AS_F64(t);
	z = __data_exp_f32.poly[0] * r + __data_exp_f32.poly[1];
	r2 = r * r;
	y = __data_exp_f32.poly[2] * r + 1;
	y = z * r2 + y;
	y = y * s;
	return (t_f32)(y);
}

/*
**	Returns 0 if not int, 1 if odd int, 2 if even int.
**	The argument is the bit representation of a non-zero finite floating-point value.
*/
static inline
int F32_checkint(t_u32 iy)
{
	int e = iy >> 23 & 0xff;
	if (e < 0x7F)
		return 0;
	if (e > 0x7F + 23)
		return 2;
	if (iy & ((1 << (0x7F + 23 - e)) - 1))
		return 0;
	if (iy & (1 << (0x7F + 23 - e)))
		return 1;
	return 2;
}

static inline
int F32_zeroinfnan(t_u32 ix)
{
	return 2 * ix - 1 >= 2u * F32_EXPONENT_MASK - 1;
}

t_f32	F32_Pow(t_f32 x, t_f32 y)
{
	t_u32 sign_bias = 0;
	t_u32 ix, iy;

	ix = AS_U32(x);
	iy = AS_U32(y);
	if (predict_false(ix - 0x00800000 >= F32_EXPONENT_MASK - 0x00800000 || F32_zeroinfnan(iy)))
	{
		/* Either (x < 0x1p-126 or inf or nan) or (y is 0 or inf or nan). */
		if (predict_false(F32_zeroinfnan(iy)))
		{
			if (2 * iy == 0)
				return issignalingf_inline(x) ? x + y : 1.0f;
			if (ix == F32_EXPONENT_ZERO)
				return issignalingf_inline(y) ? x + y : 1.0f;
			if (2 * ix > 2u * F32_EXPONENT_MASK || 2 * iy > 2u * F32_EXPONENT_MASK)
				return x + y;
			if (2 * ix == 2 * F32_EXPONENT_ZERO)
				return 1.0f;
			if ((2 * ix < 2 * F32_EXPONENT_ZERO) == !(iy & F32_SIGN_BIT_MASK))
				return 0.0f; /* |x|<1 && y==inf or |x|>1 && y==-inf. */
			return y * y;
		}
		if (predict_false(F32_zeroinfnan(ix)))
		{
			t_f32 x2 = x * x;
			if (ix & F32_SIGN_BIT_MASK && F32_checkint(iy) == 1)
				x2 = -x2;
			/* Without the barrier some versions of clang hoist the 1/x2 and thus division by zero exception can be signaled spuriously. */
			return iy & F32_SIGN_BIT_MASK ? /*fp_barrierf*/(1 / x2) : x2;
		}
		/* x and y are non-zero finite. */
		if (ix & F32_SIGN_BIT_MASK)
		{
			/* Finite x < 0. */
			int yint = F32_checkint(iy);
			if (yint == 0)
				return __math_invalidf(x);
			if (yint == 1)
				sign_bias = SIGN_BIAS;
			ix &= ~F32_SIGN_BIT_MASK;
		}
		if (ix < 0x00800000)
		{
			/* Normalize subnormal x so exponent becomes negative. */
			ix = AS_U32(x * 0x1p23f);
			ix &= ~F32_SIGN_BIT_MASK;
			ix -= 23 << 23;
		}
	}
	t_f64 logx = F32_log2_inline(ix);
	t_f64 ylogx = y * logx; /* cannot overflow, y is single prec. */
	if (predict_false((AS_U64(ylogx) >> 47 & 0xFFFF) >= AS_U64(126.0 * SCALE_POW_F32) >> 47))
	{
		/* |y*log(x)| >= 126. */
		if (ylogx > 0x1.FFFFFFFD1D571p+6 * SCALE_POW_F32)
			return __math_oflowf(sign_bias ? -1.f : +1.f);
		if (ylogx <= -150.0 * SCALE_POW_F32)
			return __math_uflowf(sign_bias ? -1.f : +1.f);
	}
	return F32_exp2_inline(ylogx, sign_bias);
}



#define TABLEBITS_POW_LOG	7
#define POW_LOG_POLY_ORDER	8
#undef N
#define N	(1 << TABLEBITS_POW_LOG)

static const
struct data_pow_f64
{
	t_f64 ln2hi;
	t_f64 ln2lo;
	t_f64 poly[POW_LOG_POLY_ORDER - 1]; /* First coefficient is 1. */
	/* Note: the pad field is unused, but allows slightly faster indexing. */
	struct { t_f64 invc, pad, logc, logctail; } table[N];
}
__data_pow_f64 =
{
	.ln2hi = 0x1.62E42FEFA3800p-1,
	.ln2lo = 0x1.EF35793C76730p-45,
	.poly =
	{
		/* relative error: 0x1.11922ap-70 in [-0x1.6bp-8 ; +0x1.6bp-8] */
		/* Coefficients are scaled to match the scaling during evaluation. */
		-0x1.0000000000000p-1,
		+0x1.5555555555556p-2 * -2,
		-0x1.0000000000006p-2 * -2,
		+0x1.999999959554Ep-3 * +4,
		-0x1.555555529A47Ap-3 * +4,
		+0x1.2495B9B4845E9p-3 * -8,
		-0x1.0002B8B263FC3p-3 * -8,
	},
/*
Algorithm:

	x = 2^k z
	log(x) = k ln2 + log(c) + log(z/c)
	log(z/c) = poly(z/c - 1)

where z is in [0x1.69555p-1 ; 0x1.69555p0] which is split into N subintervals
and z falls into the ith one, then table entries are computed as

	table[i].invc = 1/c
	table[i].logc = round(0x1p43*log(c))/0x1p43
	table[i].logctail = (t_f64)(log(c) - logc)

where c is chosen near the center of the subinterval such that 1/c has only a
few precision bits so z/c - 1 is exactly representible as t_f64:

	1/c = center < 1 ? round(N/center)/N : round(2*N/center)/N/2

Note: |z/c - 1| < 1/N for the chosen c, |log(c) - logc - logctail| < 0x1p-97,
the last few bits of logc are rounded away so k*ln2hi + logc has no rounding
error and the interval for z is selected such that near x == 1,
where log(x) is tiny, large cancellation error is avoided in logc + poly(z/c - 1).
*/
	.table =
	{
		{ +0x1.6A00000000000p+0, 0, -0x1.62C82F2B9C800p-2, +0x1.AB42428375680p-48 },
		{ +0x1.6800000000000p+0, 0, -0x1.5D1BDBF580800p-2, -0x1.CA508D8E0F720p-46 },
		{ +0x1.6600000000000p+0, 0, -0x1.5767717455800p-2, -0x1.362A4D5B6506Dp-45 },
		{ +0x1.6400000000000p+0, 0, -0x1.51AAD872DF800p-2, -0x1.684E49EB067D5p-49 },
		{ +0x1.6200000000000p+0, 0, -0x1.4BE5F95777800p-2, -0x1.41B6993293EE0p-47 },
		{ +0x1.6000000000000p+0, 0, -0x1.4618BC21C6000p-2, +0x1.3D82F484C84CCp-46 },
		{ +0x1.5E00000000000p+0, 0, -0x1.404308686A800p-2, +0x1.C42F3ED820B3Ap-50 },
		{ +0x1.5C00000000000p+0, 0, -0x1.3A64C55694800p-2, +0x1.0B1C686519460p-45 },
		{ +0x1.5A00000000000p+0, 0, -0x1.347DD9A988000p-2, +0x1.5594DD4C58092p-45 },
		{ +0x1.5800000000000p+0, 0, -0x1.2E8E2BAE12000p-2, +0x1.67B1E99B72BD8p-45 },
		{ +0x1.5600000000000p+0, 0, -0x1.2895A13DE8800p-2, +0x1.5CA14B6CFB03Fp-46 },
		{ +0x1.5600000000000p+0, 0, -0x1.2895A13DE8800p-2, +0x1.5CA14B6CFB03Fp-46 },
		{ +0x1.5400000000000p+0, 0, -0x1.22941FBCF7800p-2, -0x1.65A242853DA76p-46 },
		{ +0x1.5200000000000p+0, 0, -0x1.1C898C1699800p-2, -0x1.FAFBC68E75404p-46 },
		{ +0x1.5000000000000p+0, 0, -0x1.1675CABABA800p-2, +0x1.F1FC63382A8F0p-46 },
		{ +0x1.4E00000000000p+0, 0, -0x1.1058BF9AE4800p-2, -0x1.6A8C4FD055A66p-45 },
		{ +0x1.4C00000000000p+0, 0, -0x1.0A324E2739000p-2, -0x1.C6BEE7EF4030Ep-47 },
		{ +0x1.4A00000000000p+0, 0, -0x1.0402594B4D000p-2, -0x1.036B89EF42D7Fp-48 },
		{ +0x1.4A00000000000p+0, 0, -0x1.0402594B4D000p-2, -0x1.036B89EF42D7Fp-48 },
		{ +0x1.4800000000000p+0, 0, -0x1.FB9186D5E4000p-3, +0x1.D572AAB993C87p-47 },
		{ +0x1.4600000000000p+0, 0, -0x1.EF0ADCBDC6000p-3, +0x1.B26B79C86AF24p-45 },
		{ +0x1.4400000000000p+0, 0, -0x1.E27076E2AF000p-3, -0x1.72F4F543FFF10p-46 },
		{ +0x1.4200000000000p+0, 0, -0x1.D5C216B4FC000p-3, +0x1.1BA91BBCA681Bp-45 },
		{ +0x1.4000000000000p+0, 0, -0x1.C8FF7C79AA000p-3, +0x1.7794F689F8434p-45 },
		{ +0x1.4000000000000p+0, 0, -0x1.C8FF7C79AA000p-3, +0x1.7794F689F8434p-45 },
		{ +0x1.3E00000000000p+0, 0, -0x1.BC286742D9000p-3, +0x1.94EB0318BB78Fp-46 },
		{ +0x1.3C00000000000p+0, 0, -0x1.AF3C94E80C000p-3, +0x1.A4E633FCD9066p-52 },
		{ +0x1.3A00000000000p+0, 0, -0x1.A23BC1FE2B000p-3, -0x1.58C64DC46C1EAp-45 },
		{ +0x1.3A00000000000p+0, 0, -0x1.A23BC1FE2B000p-3, -0x1.58C64DC46C1EAp-45 },
		{ +0x1.3800000000000p+0, 0, -0x1.9525A9CF45000p-3, -0x1.AD1D904C1D4E3p-45 },
		{ +0x1.3600000000000p+0, 0, -0x1.87FA06520D000p-3, +0x1.BBDBF7FDBFA09p-45 },
		{ +0x1.3400000000000p+0, 0, -0x1.7AB890210E000p-3, +0x1.BDB9072534A58p-45 },
		{ +0x1.3400000000000p+0, 0, -0x1.7AB890210E000p-3, +0x1.BDB9072534A58p-45 },
		{ +0x1.3200000000000p+0, 0, -0x1.6D60FE719D000p-3, -0x1.0E46AA3B2E266p-46 },
		{ +0x1.3000000000000p+0, 0, -0x1.5FF3070A79000p-3, -0x1.E9E439F105039p-46 },
		{ +0x1.3000000000000p+0, 0, -0x1.5FF3070A79000p-3, -0x1.E9E439F105039p-46 },
		{ +0x1.2E00000000000p+0, 0, -0x1.526E5E3A1B000p-3, -0x1.0DE8B90075B8Fp-45 },
		{ +0x1.2C00000000000p+0, 0, -0x1.44D2B6CCB8000p-3, +0x1.70CC16135783Cp-46 },
		{ +0x1.2C00000000000p+0, 0, -0x1.44D2B6CCB8000p-3, +0x1.70CC16135783Cp-46 },
		{ +0x1.2A00000000000p+0, 0, -0x1.371FC201E9000p-3, +0x1.178864D27543Ap-48 },
		{ +0x1.2800000000000p+0, 0, -0x1.29552F81FF000p-3, -0x1.48D301771C408p-45 },
		{ +0x1.2600000000000p+0, 0, -0x1.1B72AD52F6000p-3, -0x1.E80A41811A396p-45 },
		{ +0x1.2600000000000p+0, 0, -0x1.1B72AD52F6000p-3, -0x1.E80A41811A396p-45 },
		{ +0x1.2400000000000p+0, 0, -0x1.0D77E7CD09000p-3, +0x1.A699688E85BF4p-47 },
		{ +0x1.2400000000000p+0, 0, -0x1.0D77E7CD09000p-3, +0x1.A699688E85BF4p-47 },
		{ +0x1.2200000000000p+0, 0, -0x1.FEC9131DBE000p-4, -0x1.575545CA333F2p-45 },
		{ +0x1.2000000000000p+0, 0, -0x1.E27076E2B0000p-4, +0x1.A342C2AF0003Cp-45 },
		{ +0x1.2000000000000p+0, 0, -0x1.E27076E2B0000p-4, +0x1.A342C2AF0003Cp-45 },
		{ +0x1.1E00000000000p+0, 0, -0x1.C5E548F5BC000p-4, -0x1.D0C57585FBE06p-46 },
		{ +0x1.1C00000000000p+0, 0, -0x1.A926D3A4AE000p-4, +0x1.53935E85BAAC8p-45 },
		{ +0x1.1C00000000000p+0, 0, -0x1.A926D3A4AE000p-4, +0x1.53935E85BAAC8p-45 },
		{ +0x1.1A00000000000p+0, 0, -0x1.8C345D631A000p-4, +0x1.37C294D2F5668p-46 },
		{ +0x1.1A00000000000p+0, 0, -0x1.8C345D631A000p-4, +0x1.37C294D2F5668p-46 },
		{ +0x1.1800000000000p+0, 0, -0x1.6F0D28AE56000p-4, -0x1.69737C93373DAp-45 },
		{ +0x1.1600000000000p+0, 0, -0x1.51B073F062000p-4, +0x1.F025B61C65E57p-46 },
		{ +0x1.1600000000000p+0, 0, -0x1.51B073F062000p-4, +0x1.F025B61C65E57p-46 },
		{ +0x1.1400000000000p+0, 0, -0x1.341D7961BE000p-4, +0x1.C5EDACCF913DFp-45 },
		{ +0x1.1400000000000p+0, 0, -0x1.341D7961BE000p-4, +0x1.C5EDACCF913DFp-45 },
		{ +0x1.1200000000000p+0, 0, -0x1.16536EEA38000p-4, +0x1.47C5E768FA309p-46 },
		{ +0x1.1000000000000p+0, 0, -0x1.F0A30C0118000p-5, +0x1.D599E83368E91p-45 },
		{ +0x1.1000000000000p+0, 0, -0x1.F0A30C0118000p-5, +0x1.D599E83368E91p-45 },
		{ +0x1.0E00000000000p+0, 0, -0x1.B42DD71198000p-5, +0x1.C827AE5D6704Cp-46 },
		{ +0x1.0E00000000000p+0, 0, -0x1.B42DD71198000p-5, +0x1.C827AE5D6704Cp-46 },
		{ +0x1.0C00000000000p+0, 0, -0x1.77458F632C000p-5, -0x1.CFC4634F2A1EEp-45 },
		{ +0x1.0C00000000000p+0, 0, -0x1.77458F632C000p-5, -0x1.CFC4634F2A1EEp-45 },
		{ +0x1.0A00000000000p+0, 0, -0x1.39E87B9FEC000p-5, +0x1.502B7F526FEAAp-48 },
		{ +0x1.0A00000000000p+0, 0, -0x1.39E87B9FEC000p-5, +0x1.502B7F526FEAAp-48 },
		{ +0x1.0800000000000p+0, 0, -0x1.F829B0E780000p-6, -0x1.980267C7E09E4p-45 },
		{ +0x1.0800000000000p+0, 0, -0x1.F829B0E780000p-6, -0x1.980267C7E09E4p-45 },
		{ +0x1.0600000000000p+0, 0, -0x1.7B91B07D58000p-6, -0x1.88D5493FAA639p-45 },
		{ +0x1.0400000000000p+0, 0, -0x1.FC0A8B0FC0000p-7, -0x1.F1E7CF6D3A69Cp-50 },
		{ +0x1.0400000000000p+0, 0, -0x1.FC0A8B0FC0000p-7, -0x1.F1E7CF6D3A69Cp-50 },
		{ +0x1.0200000000000p+0, 0, -0x1.FE02A6B100000p-8, -0x1.9E23F0DDA40E4p-46 },
		{ +0x1.0200000000000p+0, 0, -0x1.FE02A6B100000p-8, -0x1.9E23F0DDA40E4p-46 },
		{ +0x1.0000000000000p+0, 0, +0x0.0000000000000p+0, +0x0.0000000000000p+0  },
		{ +0x1.0000000000000p+0, 0, +0x0.0000000000000p+0, +0x0.0000000000000p+0  },
		{ +0x1.FC00000000000p-1, 0, +0x1.0101575890000p-7, -0x1.0C76B999D2BE8p-46 },
		{ +0x1.F800000000000p-1, 0, +0x1.0205658938000p-6, -0x1.3DC5B06E2F7D2p-45 },
		{ +0x1.F400000000000p-1, 0, +0x1.8492528C90000p-6, -0x1.AA0BA325A0C34p-45 },
		{ +0x1.F000000000000p-1, 0, +0x1.0415D89E74000p-5, +0x1.111C05CF1D753p-47 },
		{ +0x1.EC00000000000p-1, 0, +0x1.466AED42E0000p-5, -0x1.C167375BDFD28p-45 },
		{ +0x1.E800000000000p-1, 0, +0x1.894AA149FC000p-5, -0x1.97995D05A267Dp-46 },
		{ +0x1.E400000000000p-1, 0, +0x1.CCB73CDDDC000p-5, -0x1.A68F247D82807p-46 },
		{ +0x1.E200000000000p-1, 0, +0x1.EEA31C006C000p-5, -0x1.E113E4FC93B7Bp-47 },
		{ +0x1.DE00000000000p-1, 0, +0x1.1973BD1466000p-4, -0x1.5325D560D9E9Bp-45 },
		{ +0x1.DA00000000000p-1, 0, +0x1.3BDF5A7D1E000p-4, +0x1.CC85EA5DB4ED7p-45 },
		{ +0x1.D600000000000p-1, 0, +0x1.5E95A4D97A000p-4, -0x1.C69063C5D1D1Ep-45 },
		{ +0x1.D400000000000p-1, 0, +0x1.700D30AEAC000p-4, +0x1.C1E8DA99DED32p-49 },
		{ +0x1.D000000000000p-1, 0, +0x1.9335E5D594000p-4, +0x1.3115C3ABD47DAp-45 },
		{ +0x1.CC00000000000p-1, 0, +0x1.B6AC88DAD6000p-4, -0x1.390802BF768E5p-46 },
		{ +0x1.CA00000000000p-1, 0, +0x1.C885801BC4000p-4, +0x1.646D1C65AACD3p-45 },
		{ +0x1.C600000000000p-1, 0, +0x1.EC739830A2000p-4, -0x1.DC068AFE645E0p-45 },
		{ +0x1.C400000000000p-1, 0, +0x1.FE89139DBE000p-4, -0x1.534D64FA10AFDp-45 },
		{ +0x1.C000000000000p-1, 0, +0x1.1178E8227E000p-3, +0x1.1EF78CE2D07F2p-45 },
		{ +0x1.BE00000000000p-1, 0, +0x1.1AA2B7E23F000p-3, +0x1.CA78E44389934p-45 },
		{ +0x1.BA00000000000p-1, 0, +0x1.2D1610C868000p-3, +0x1.39D6CCB81B4A1p-47 },
		{ +0x1.B800000000000p-1, 0, +0x1.365FCB0159000p-3, +0x1.62FA8234B7289p-51 },
		{ +0x1.B400000000000p-1, 0, +0x1.4913D8333B000p-3, +0x1.5837954FDB678p-45 },
		{ +0x1.B200000000000p-1, 0, +0x1.527E5E4A1B000p-3, +0x1.633E8E5697DC7p-45 },
		{ +0x1.AE00000000000p-1, 0, +0x1.6574EBE8C1000p-3, +0x1.9CF8B2C3C2E78p-46 },
		{ +0x1.AC00000000000p-1, 0, +0x1.6F0128B757000p-3, -0x1.5118DE59C21E1p-45 },
		{ +0x1.AA00000000000p-1, 0, +0x1.7898D85445000p-3, -0x1.C661070914305p-46 },
		{ +0x1.A600000000000p-1, 0, +0x1.8BEAFEB390000p-3, -0x1.73D54AAE92CD1p-47 },
		{ +0x1.A400000000000p-1, 0, +0x1.95A5ADCF70000p-3, +0x1.7F22858A0FF6Fp-47 },
		{ +0x1.A000000000000p-1, 0, +0x1.A93ED3C8AE000p-3, -0x1.8724350562169p-45 },
		{ +0x1.9E00000000000p-1, 0, +0x1.B31D8575BD000p-3, -0x1.C358D4EACE1AAp-47 },
		{ +0x1.9C00000000000p-1, 0, +0x1.BD087383BE000p-3, -0x1.D4BC4595412B6p-45 },
		{ +0x1.9A00000000000p-1, 0, +0x1.C6FFBC6F01000p-3, -0x1.1EC72C5962BD2p-48 },
		{ +0x1.9600000000000p-1, 0, +0x1.DB13DB0D49000p-3, -0x1.AFF2AF715B035p-45 },
		{ +0x1.9400000000000p-1, 0, +0x1.E530EFFE71000p-3, +0x1.212276041F430p-51 },
		{ +0x1.9200000000000p-1, 0, +0x1.EF5ADE4DD0000p-3, -0x1.A211565BB8E11p-51 },
		{ +0x1.9000000000000p-1, 0, +0x1.F991C6CB3B000p-3, +0x1.BCBECCA0CDF30p-46 },
		{ +0x1.8C00000000000p-1, 0, +0x1.07138604D5800p-2, +0x1.89CDB16ED4E91p-48 },
		{ +0x1.8A00000000000p-1, 0, +0x1.0C42D67616000p-2, +0x1.7188B163CEAE9p-45 },
		{ +0x1.8800000000000p-1, 0, +0x1.1178E8227E800p-2, -0x1.C210E63A5F01Cp-45 },
		{ +0x1.8600000000000p-1, 0, +0x1.16B5CCBACF800p-2, +0x1.B9ACDF7A51681p-45 },
		{ +0x1.8400000000000p-1, 0, +0x1.1BF99635A6800p-2, +0x1.CA6ED5147BDB7p-45 },
		{ +0x1.8200000000000p-1, 0, +0x1.214456D0EB800p-2, +0x1.A87DEBA46BAEAp-47 },
		{ +0x1.7E00000000000p-1, 0, +0x1.2BEF07CDC9000p-2, +0x1.A9CFA4A5004F4p-45 },
		{ +0x1.7C00000000000p-1, 0, +0x1.314F1E1D36000p-2, -0x1.8E27AD3213CB8p-45 },
		{ +0x1.7A00000000000p-1, 0, +0x1.36B6776BE1000p-2, +0x1.16ECDB0F177C8p-46 },
		{ +0x1.7800000000000p-1, 0, +0x1.3C25277333000p-2, +0x1.83B54B606BD5Cp-46 },
		{ +0x1.7600000000000p-1, 0, +0x1.419B423D5E800p-2, +0x1.8E436EC90E09Dp-47 },
		{ +0x1.7400000000000p-1, 0, +0x1.4718DC271C800p-2, -0x1.F27CE0967D675p-45 },
		{ +0x1.7200000000000p-1, 0, +0x1.4C9E09E173000p-2, -0x1.E20891B0AD8A4p-45 },
		{ +0x1.7000000000000p-1, 0, +0x1.522AE0738A000p-2, +0x1.EBE708164C759p-45 },
		{ +0x1.6E00000000000p-1, 0, +0x1.57BF753C8D000p-2, +0x1.FADEDEE5D40EFp-46 },
		{ +0x1.6C00000000000p-1, 0, +0x1.5D5BDDF596000p-2, -0x1.A0B2A08A465DCp-47 },
	},
};

/*
**	Worst-case error: 0.54 ULP (~= ulperr_exp + 1024*Ln2*relerr_log*2^53)
**	relerr_log: 1.3 * 2^-68 (Relative error of log, 1.5 * 2^-68 without fma)
**	ulperr_exp: 0.509 ULP (ULP error of exp, 0.511 ULP without fma)
*/

#define Ln2hi __data_pow_f64.ln2hi
#define Ln2lo __data_pow_f64.ln2lo
#undef N
#define N (1 << TABLEBITS_POW_LOG)
#undef OFF
#define OFF 0x3FE6955500000000

/* Top 12 bits of a t_f64 (sign and exponent bits). */
static inline
t_u32 F64_Pow_top12(t_f64 x)
{
	return AS_U64(x) >> 52;
}

/*
**	Compute y+TAIL = log(x) where the rounded result is y and TAIL has about additional 15 bits precision.
**	IX is the bit representation of x, but normalized in the subnormal range using the sign bit for the exponent.
*/
static inline
t_f64 log_inline(t_u64 ix, t_f64 *tail)
{
	/* t_f64 for better performance on targets with FLT_EVAL_METHOD==2. */
	t_f64 z, r, y, invc, logc, logctail, kd, hi, t1, t2, lo, lo1, lo2, p;
	t_u64 iz, tmp;
	int k, i;
	/*
	x = 2^k z; where z is in range [OFF,2*OFF) and exact.
	The range is split into N subintervals.
	The ith subinterval contains z and c is near its center.
	*/
	tmp = ix - OFF;
	i = (tmp >> (52 - TABLEBITS_POW_LOG)) % N;
	k = (t_s64)tmp >> 52; /* arithmetic shift */
	iz = ix - (tmp & 0xfffULL << 52);
	z = AS_F64(iz);
	kd = (t_f64)k;
	/* log(x) = k*Ln2 + log(c) + log1p(z/c-1). */
	invc = __data_pow_f64.table[i].invc;
	logc = __data_pow_f64.table[i].logc;
	logctail = __data_pow_f64.table[i].logctail;
	/* Note: 1/c is j/N or j/N/2 where j is an integer in [N,2N) and |z/c - 1| < 1/N, so r = z/c - 1 is exactly representible. */
#if __FP_FAST_FMA
	r = __builtin_fma(z, invc, -1.0);
#else
	/* Split z such that rhi, rlo and rhi*rhi are exact and |rlo| <= |r|. */
	t_f64 zhi = AS_F64((iz + (1ULL << 31)) & (-1ULL << 32));
	t_f64 zlo = z - zhi;
	t_f64 rhi = zhi * invc - 1.0;
	t_f64 rlo = zlo * invc;
	r = rhi + rlo;
#endif
	/* k*Ln2 + log(c) + r. */
	t1 = kd * Ln2hi + logc;
	t2 = t1 + r;
	lo1 = kd * Ln2lo + logctail;
	lo2 = t1 - t2 + r;
	/* Evaluation is optimized assuming superscalar pipelined execution. */
	t_f64 ar, ar2, ar3, lo3, lo4;
	ar = __data_pow_f64.poly[0] * r; /* __data_pow_f64.poly[0] = -0.5. */
	ar2 = r * ar;
	ar3 = r * ar2;
	/* k*Ln2 + log(c) + r + __data_pow_f64.poly[0]*r*r. */
#if __FP_FAST_FMA
	hi = t2 + ar2;
	lo3 = __builtin_fma(ar, r, -ar2);
	lo4 = t2 - hi + ar2;
#else
	t_f64 arhi = __data_pow_f64.poly[0] * rhi;
	t_f64 arhi2 = rhi * arhi;
	hi = t2 + arhi2;
	lo3 = rlo * (ar + arhi);
	lo4 = t2 - hi + arhi2;
#endif
	/* p = log1p(r) - r - __data_pow_f64.poly[0]*r*r. */
	p = (ar3 * (
		__data_pow_f64.poly[1] + r * 
		__data_pow_f64.poly[2] + ar2 * (
		__data_pow_f64.poly[3] + r *
		__data_pow_f64.poly[4] + ar2 * (
		__data_pow_f64.poly[5] + r *
		__data_pow_f64.poly[6]))));
	lo = lo1 + lo2 + lo3 + lo4 + p;
	y = hi + lo;
	*tail = hi - y + lo;
	return y;
}

#define N_POW_F64	(1 << TABLEBITS_EXP_F64)

/*
**	Handle cases that may overflow or underflow when computing the result that is scale*(1+TMP) without intermediate rounding.
**	The bit representation of scale is in SBITS, however it has a computed exponent that may have overflown into the sign bit so that needs to be adjusted before using it as a t_f64.
**	(t_s32)KI is the k used in the argument reduction and exponent adjustment of scale, positive k here means the result may overflow and negative k means the result may underflow.
*/
static inline
t_f64 F64_Pow_specialcase(t_f64 tmp, t_u64 sbits, t_u64 ki)
{
	t_f64 scale, y;

	if ((ki & 0x80000000) == 0)
	{
		/* k > 0, the exponent of scale might have overflowed by <= 460. */
		sbits -= 1009ull << 52;
		scale = AS_F64(sbits);
		y = 0x1p1009 * (scale + scale * tmp);
		return (t_f64)(y);
	}
	/* k < 0, need special care in the subnormal range. */
	sbits += 1022ull << 52;
	/* Note: sbits is signed scale. */
	scale = AS_F64(sbits);
	y = scale + scale * tmp;
	if (F64_Abs(y) < 1.0)
	{
		/*
		Round y to the right precision before scaling it into the subnormal range to avoid t_f64 rounding
		that can cause 0.5+E/2 ulp error where E is the worst-case ulp error outside the subnormal range.
		So this is only useful if the goal is better than 1 ulp worst-case error.
		*/
		t_f64 hi, lo, one = 1.0;
		if (y < 0.0)
			one = -1.0;
		lo = scale - y + scale * tmp;
		hi = one + y;
		lo = one - hi + y + lo;
		y = (t_f64)(hi + lo) - one;
		/* Fix the sign of 0. */
		if (y == 0.0)
			y = AS_F64(sbits & F64_SIGN_BIT_MASK);
		/* The underflow exception needs to be signaled explicitly. */
		/*FORCE_EVAL(fp_barrier(0x1p-1022) * 0x1p-1022);*/
	}
	y = 0x1p-1022 * y;
	return (t_f64)(y);
}

#undef SIGN_BIAS
#define SIGN_BIAS	(0x800 << TABLEBITS_EXP_F64)

/*
**	Computes sign*exp(x+xtail) where |xtail| < 2^-8/N and |xtail| <= |x|.
**	The sign_bias argument is SIGN_BIAS or 0 and sets the sign to -1 or 1.
*/
static inline
t_f64	F64_Pow_exp_inline(t_f64 x, t_f64 xtail, t_u32 sign_bias)
{
	t_u32 abstop;
	t_u64 ki, idx, top, sbits;
	/* t_f64 for better performance on targets with FLT_EVAL_METHOD==2. */
	t_f64 kd, z, r, r2, scale, tail, tmp;

	abstop = F64_Pow_top12(x) & 0x7FF;
	if (predict_false(abstop - F64_Pow_top12(0x1p-54) >= F64_Pow_top12(512.0) - F64_Pow_top12(0x1p-54)))
	{
		if (abstop - F64_Pow_top12(0x1p-54) >= 0x80000000)
		{
			/* Avoid spurious underflow for tiny x. */
			/* Note: 0 is common input. */
			t_f64 one = WANT_ROUNDING ? 1.0 + x : 1.0;
			return sign_bias ? -one : one;
		}
		if (abstop >= F64_Pow_top12(1024.0))
		{
			/* Note: inf and nan are already handled. */
			if (AS_U64(x) >> 63)
				return __math_uflow(sign_bias ? -1. : +1.);
			else
				return __math_oflow(sign_bias ? -1. : +1.);
		}
		/* Large x is special cased below. */
		abstop = 0;
	}

	/* exp(x) = 2^(k/N) * exp(r), with exp(r) in [2^(-1/2N),2^(1/2N)]. */
	/* x = ln2/N*k + r, with int k and r in [-ln2/2N, ln2/2N]. */
	z = __data_exp_f64.invln2N * x;
#if TOINT_INTRINSICS
	kd = roundtoint(z);
	ki = converttoint(z);
#elif EXP_USE_TOINT_NARROW
	/* z - kd is in [-0.5-2^-16, 0.5] in all rounding modes. */
	kd = (t_f64)(z + __data_exp_f64.shift);
	ki = AS_U64(kd) >> 16;
	kd = (t_f64)(t_s32)ki;
#else
	/* z - kd is in [-1, 1] in non-nearest rounding modes. */
	kd = (t_f64)(z + __data_exp_f64.shift);
	ki = AS_U64(kd);
	kd -= __data_exp_f64.shift;
#endif
	r = x + kd * __data_exp_f64.negln2hiN + kd * __data_exp_f64.negln2loN;
	/* The code assumes 2^-200 < |xtail| < 2^-8/N. */
	r += xtail;
	/* 2^(k/N) ~= scale * (1 + tail). */
	idx = 2 * (ki % N_POW_F64);
	top = (ki + sign_bias) << (F64_MANTISSA_BITS - TABLEBITS_EXP_F64);
	tail = AS_F64(__data_exp_f64.table[idx]);
	/* This is only a valid scale when -1023*N < k < 1024*N. */
	sbits = __data_exp_f64.table[idx + 1] + top;
	/* exp(x) = 2^(k/N) * exp(r) ~= scale + scale * (tail + exp(r) - 1). */
	/* Evaluation is optimized assuming superscalar pipelined execution. */
	r2 = r * r;
	/* Without fma the worst case error is 0.25/N ulp larger. */
	/* Worst case error is less than 0.5+1.11/N+(abs poly error * 2^53) ulp. */
	tmp = tail + r + r2 * (
		__data_exp_f64.poly[0] + r *
		__data_exp_f64.poly[1]) + r2 * r2 * (
		__data_exp_f64.poly[2] + r * 
		__data_exp_f64.poly[3]);
	//	__data_exp_f64.poly[4]
	if (predict_false(abstop == 0))
		return F64_Pow_specialcase(tmp, sbits, ki);
	scale = AS_F64(sbits);
	/* Note: tmp == 0 or |tmp| > 2^-200 and scale > 2^-739, so there is no spurious underflow here even without fma. */
	return (t_f64)(scale + scale * tmp);
}

/*!
**	Returns 0 if not int, 1 if odd int, 2 if even int.
**	The argument is the bit representation of a non-zero finite floating-point value.
*/
static inline
int	F64_Pow_checkint(t_u64 iy)
{
	int e = iy >> 52 & 0x7FF;
	if (e < 0x3FF)
		return 0;
	if (e > 0x3FF + 52)
		return 2;
	if (iy & ((1ULL << (0x3FF + 52 - e)) - 1))
		return 0;
	if (iy & (1ULL << (0x3FF + 52 - e)))
		return 1;
	return 2;
}

/*!
**	Returns 1 if input is the bit representation of 0, infinity or nan.
*/
static inline
int	F64_Pow_zeroinfnan(t_u64 i)
{
	return 2 * i - 1 >= 2 * AS_U64(INFINITY) - 1;
}

t_f64	F64_Pow(t_f64 x, t_f64 y)
{
	t_u32 sign_bias = 0;
	t_u64 ix, iy;
	t_u32 topx, topy;

	ix = AS_U64(x);
	iy = AS_U64(y);
	topx = F64_Pow_top12(x);
	topy = F64_Pow_top12(y);
	if (predict_false(topx - 0x001 >= 0x7FF - 0x001 || (topy & 0x7FF) - 0x3BE >= 0x43E - 0x3BE))
	{
		/* Note: if |y| > 1075 * ln2 * 2^53 ~= 0x1.749p62 then pow(x,y) = inf/0 and if |y| < 2^-54 / 1075 ~= 0x1.e7b6p-65 then pow(x,y) = +-1. */
		/* Special cases: (x < 0x1p-126 or inf or nan) or (|y| < 0x1p-65 or |y| >= 0x1p63 or nan). */
		if (predict_false(F64_Pow_zeroinfnan(iy)))
		{
			if (2 * iy == 0)
				return issignaling_inline(x) ? x + y : 1.0;
			if (ix == AS_U64(1.0))
				return issignaling_inline(y) ? x + y : 1.0;
			if (2 * ix > 2 * AS_U64(INFINITY) || 2 * iy > 2 * AS_U64(INFINITY))
				return x + y;
			if (2 * ix == 2 * AS_U64(1.0))
				return 1.0;
			if ((2 * ix < 2 * AS_U64(1.0)) == !(iy >> 63))
				return 0.0; /* |x|<1 && y==inf or |x|>1 && y==-inf. */
			return y * y;
		}
		if (predict_false(F64_Pow_zeroinfnan(ix)))
		{
			t_f64 x2 = x * x;
			if (ix >> 63 && F64_Pow_checkint(iy) == 1)
				x2 = -x2;
			/* Without the barrier some versions of clang hoist the 1/x2 and thus division by zero exception can be signaled spuriously. */
			return iy >> 63 ? /*fp_barrier*/(1 / x2) : x2;
		}
		/* Here x and y are non-zero finite. */
		if (ix >> 63)
		{
			/* Finite x < 0. */
			int yint = F64_Pow_checkint(iy);
			if (yint == 0)
				return __math_invalid(x);
			if (yint == 1)
				sign_bias = SIGN_BIAS;
			ix &= ~F64_SIGN_BIT_MASK;
			topx &= 0x7FF;
		}
		if ((topy & 0x7FF) - 0x3BE >= 0x43E - 0x3BE)
		{
			/* Note: sign_bias == 0 here because y is not odd. */
			if (ix == AS_U64(1.0))
				return 1.0;
			if ((topy & 0x7FF) < 0x3BE)
			{
				/* |y| < 2^-65, x^y ~= 1 + y*log(x). */
				if (WANT_ROUNDING)
					return ix > AS_U64(1.0) ? 1.0 + y : 1.0 - y;
				else
					return 1.0;
			}
			return (ix > AS_U64(1.0)) == (topy < 0x800) ?
				__math_oflow(sign_bias ? -1. : +1.) :
				__math_uflow(sign_bias ? -1. : +1.);
		}
		if (topx == 0)
		{
			/* Normalize subnormal x so exponent becomes negative. */
			ix = AS_U64(x * 0x1p52);
			ix &= ~F64_SIGN_BIT_MASK;
			ix -= 52ULL << 52;
		}
	}
	t_f64 lo;
	t_f64 hi = log_inline(ix, &lo);
	t_f64 ehi, elo;
#if __FP_FAST_FMA
	ehi = y * hi;
	elo = y * lo + __builtin_fma(y, hi, -ehi);
#else
	t_f64 yhi = AS_F64(iy & -1ULL << 27);
	t_f64 ylo = y - yhi;
	t_f64 lhi = AS_F64(AS_U64(hi) & -1ULL << 27);
	t_f64 llo = hi - lhi + lo;
	ehi = yhi * lhi;
	elo = ylo * lhi + y * llo; /* |elo| < |ehi| * 2^-25. */
#endif
	return F64_Pow_exp_inline(ehi, elo, sign_bias);
}



/*
**	Copyright (c) 2008 Stephen L. Moshier <steve@moshier.net>
**
**	Permission to use, copy, modify, and distribute this software for any
**	purpose with or without fee is hereby granted, provided that the above
**	copyright notice and this permission notice appear in all copies.
**
**	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
**	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
**	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
**	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
**	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
**	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
**	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*! powl()
**
**      Power function, t_f80 precision
**
**
** SYNOPSIS:
**
** t_f80 x, y, z, powl();
**
** z = powl( x, y );
**
**
** DESCRIPTION:
**
** Computes x raised to the yth power.  Analytically,
**
**      x**y  =  exp( y log(x) ).
**
** Following Cody and Waite, this program uses a lookup table
** of 2**-i/32 and pseudo extended precision arithmetic to
** obtain several extra bits of accuracy in both the logarithm
** and the exponential.
**
**
** ACCURACY:
**
** The relative error of pow(x,y) can be estimated
** by   y dl ln(2),   where dl is the absolute error of
** the internally computed base 2 logarithm.  At the ends
** of the approximation interval the logarithm equal 1/32
** and its relative error is about 1 lsb = 1.1e-19.  Hence
** the predicted relative error in the result is 2.3e-21 y .
**
**                      Relative error:
** arithmetic   domain     # trials      peak         rms
**
**    IEEE     +-1000       40000      2.8e-18      3.7e-19
** .001 < x < 1000, with log(x) uniformly distributed.
** -1000 < y < 1000, y uniformly distributed.
**
**    IEEE     0,8700       60000      6.5e-18      1.0e-18
** 0.99 < x < 1.01, 0 < y < 8700, uniformly distributed.
**
*/

/* Table size */
#define NXT 32

#define F W
#define Fa Wa
#define Fb Wb
#define G W
#define Ga Wa
#define Gb u
#define H W
#define Ha Wb
#define Hb Wb


/*! powil()
**
**	Positive real raised to integer power, t_f80 precision
**
** SYNOPSIS:
**
** t_f80 x, y, powil();
** int n;
**
** y = powil( x, n );
**
**
** DESCRIPTION:
**
** Returns argument x>0 raised to the nth power.
** The routine efficiently decomposes n as a sum of powers of
** two. The desired power is a product of two-to-the-kth
** powers of x.  Thus to compute the 32767 power of x requires
** 28 multiplications instead of 32767 multiplications.
**
**
** ACCURACY:
**
**                      Relative error:
** arithmetic   x domain   n domain  # trials      peak         rms
**    IEEE     .001,1000  -1022,1023  50000       4.3e-17     7.8e-18
**    IEEE        1,2     -1022,1023  20000       3.9e-17     7.6e-18
**    IEEE     .99,1.01     0,8700    10000       3.6e-16     7.2e-17
**
** Returns MAXNUM on overflow, zero on underflow.
*/

#define DEFINEFUNC_FLOAT_POW(BITS) \
static const \
struct data_pow_f##BITS \
{ \
	t_f##BITS	P[4]; \
	t_f##BITS	Q[3]; \
	t_f##BITS	antilog[33]; \
	t_f##BITS	B[17]; \
	t_f##BITS	R[7]; \
	t_f##BITS	MEXP; \
	t_f##BITS	MNEXP; \
	t_f##BITS	LOG2EA; \
	t_f##BITS	MAXLOGL; \
	t_f##BITS	MINLOGL; \
	t_f##BITS	LOGE2L; \
	t_f##BITS	huge; \
} \
__data_pow_f##BITS = \
{ \
	/* log(1+x) =  x - .5x^2 + x^3 *  P(z)/Q(z) on the domain  2^(-1/32) - 1  <=  x  <=  2^(1/32) - 1 */ \
	.P = \
	{ \
		+8.3319510773868690346226e-4L, \
		+4.9000050881978028599627e-1L, \
		+1.7500123722550302671919e0L, \
		+1.4000100839971580279335e0L, \
	}, \
	.Q = \
	{ \
		+1.0000000000000000000000e0L, \
		+5.2500282295834889175431e0L, \
		+8.4000598057587009834666e0L, \
		+4.2000302519914740834728e0L, \
	}, \
	/* antilog[i] = 2^(-i/32), rounded to IEEE t_f80 precision. */ \
	/* If i is even, antilog[i] + B[i/2] gives additional accuracy. */ \
	.antilog = \
	{ \
		+1.0000000000000000000000e0L, \
		+9.7857206208770013448287e-1L, \
		+9.5760328069857364691013e-1L, \
		+9.3708381705514995065011e-1L, \
		+9.1700404320467123175367e-1L, \
		+8.9735453750155359320742e-1L, \
		+8.7812608018664974155474e-1L, \
		+8.5930964906123895780165e-1L, \
		+8.4089641525371454301892e-1L, \
		+8.2287773907698242225554e-1L, \
		+8.0524516597462715409607e-1L, \
		+7.8799042255394324325455e-1L, \
		+7.7110541270397041179298e-1L, \
		+7.5458221379671136985669e-1L, \
		+7.3841307296974965571198e-1L, \
		+7.2259040348852331001267e-1L, \
		+7.0710678118654752438189e-1L, \
		+6.9195494098191597746178e-1L, \
		+6.7712777346844636413344e-1L, \
		+6.6261832157987064729696e-1L, \
		+6.4841977732550483296079e-1L, \
		+6.3452547859586661129850e-1L, \
		+6.2092890603674202431705e-1L, \
		+6.0762367999023443907803e-1L, \
		+5.9460355750136053334378e-1L, \
		+5.8186242938878875689693e-1L, \
		+5.6939431737834582684856e-1L, \
		+5.5719337129794626814472e-1L, \
		+5.4525386633262882960438e-1L, \
		+5.3357020033841180906486e-1L, \
		+5.2213689121370692017331e-1L, \
		+5.1094857432705833910408e-1L, \
		+5.0000000000000000000000e-1L, \
	}, \
	.B = \
	{ \
		+0.0000000000000000000000e0L, \
		+2.6176170809902549338711e-20L, \
		-1.0126791927256478897086e-20L, \
		+1.3438228172316276937655e-21L, \
		+1.2207982955417546912101e-20L, \
		-6.3084814358060867200133e-21L, \
		+1.3164426894366316434230e-20L, \
		-1.8527916071632873716786e-20L, \
		+1.8950325588932570796551e-20L, \
		+1.5564775779538780478155e-20L, \
		+6.0859793637556860974380e-21L, \
		-2.0208749253662532228949e-20L, \
		+1.4966292219224761844552e-20L, \
		+3.3540909728056476875639e-21L, \
		-8.6987564101742849540743e-22L, \
		-1.2327176863327626135542e-20L, \
		+0.0000000000000000000000e0L, \
	}, \
	/* 2^x = 1 + x P(x), on the interval -1/32 <= x <= 0 */ \
	.R = \
	{ \
		+1.5089970579127659901157e-5L, \
		+1.5402715328927013076125e-4L, \
		+1.3333556028915671091390e-3L, \
		+9.6181291046036762031786e-3L, \
		+5.5504108664798463044015e-2L, \
		+2.4022650695910062854352e-1L, \
		+6.9314718055994530931447e-1L, \
	}, \
	.MEXP = (NXT*16384.0L), \
	/* The following if denormal numbers are supported, else -MEXP: */ \
	.MNEXP = (-NXT*(16384.0L+64.0L)), \
	/* log2(e) - 1 */ \
	.LOG2EA = 0.44269504088896340735992L, \
 \
	.MAXLOGL = 1.1356523406294143949492E4L, \
	.MINLOGL = -1.13994985314888605586758E4L, \
	.LOGE2L = 6.9314718055994530941723E-1L, \
	.huge = 0x1p10000L, \
}; \
 \
/* XXX Prevent gcc from erroneously constant folding this. */ \
static const volatile t_f##BITS twom10000 = 0x1p-10000L; \
 \
static \
t_f##BITS	powil(t_f##BITS x, int nn) \
{ \
	t_f##BITS ww, y; \
	t_f##BITS s; \
	int n, e, sign, lx; \
 \
	if (nn == 0) \
		return 1.0; \
 \
	if (nn < 0) \
	{ \
		sign = -1; \
		n = -nn; \
	} \
	else \
	{ \
		sign = 1; \
		n = nn; \
	} \
	/* Overflow detection */ \
	/* Calculate approximate logarithm of answer */ \
	s = x; \
	s = F##BITS##_SplitExp( s, &lx); \
	e = (lx - 1)*n; \
	if ((e == 0) || (e > 64) || (e < -64)) \
	{ \
		s = (s - 7.0710678118654752e-1L) / (s +  7.0710678118654752e-1L); \
		s = (2.9142135623730950L * s - 0.5 + lx) * nn * __data_pow_f80.LOGE2L; \
	} \
	else \
	{ \
		s = __data_pow_f##BITS.LOGE2L * e; \
	} \
	if (s > __data_pow_f##BITS.MAXLOGL) \
		return __data_pow_f##BITS.huge * __data_pow_f##BITS.huge; /* overflow */ \
	if (s < __data_pow_f##BITS.MINLOGL) \
		return twom10000 * twom10000; /* underflow */ \
	/* Handle tiny denormal answer, but with less accuracy \
	**	since roundoff error in 1.0/x will be amplified. \
	**	The precise demarcation should be the gradual underflow threshold. \
	*/ \
	if (s < -__data_pow_f##BITS.MAXLOGL + 2.0) \
	{ \
		x = 1.0/x; \
		sign = -sign; \
	} \
	/* First bit of the power */ \
	if (n & 1) \
		y = x; \
	else \
		y = 1.0; \
	ww = x; \
	n >>= 1; \
	while (n) \
	{ \
		ww = ww * ww;  /* arg to the 2-to-the-kth power */ \
		if (n & 1) /* if that bit is set, then include in product */ \
			y *= ww; \
		n >>= 1; \
	} \
	if (sign < 0) \
		y = 1.0/y; \
	return y; \
} \
 \
/*! Find a multiple of 1/NXT that is within 1/NXT of x. */ \
static \
t_f##BITS	reducl(t_f##BITS x) \
{ \
	t_f##BITS t; \
 \
	t = x * NXT; \
	t = F##BITS##_Floor(t); \
	t = t / NXT; \
	return t; \
} \
 \
t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y) \
{ \
	/* t_f64 F, Fa, Fb, G, Ga, Gb, H, Ha, Hb */ \
	int i, nflg, iyflg, yoddint; \
	long e; \
	t_f##BITS w=0, W=0, Wa=0, Wb=0, ya=0, yb=0, u=0; \
	volatile t_f##BITS z=0; \
	/* make sure no invalid exception is raised by nan comparision */ \
	if (IS_NAN(x)) \
	{ \
		if (!IS_NAN(y) && y == 0.0) \
			return 1.0; \
		return x; \
	} \
	if (IS_NAN(y)) \
	{ \
		if (x == 1.0) \
			return 1.0; \
		return y; \
	} \
	if (x == 1.0) \
		return 1.0; /* 1**y = 1, even if y is nan */ \
	if (y == 0.0) \
		return 1.0; /* x**0 = 1, even if x is nan */ \
	if (y == 1.0) \
		return x; \
	/* \
	if y*log2(x) < log2(LDBL_TRUE_MIN)-1 then x^y uflows to 0 \
	if y*log2(x) > -log2(LDBL_TRUE_MIN)+1 > LDBL_MAX_EXP then x^y oflows \
	if |x|!=1 then |log2(x)| > |log(x)| > LDBL_EPSILON/2 so \
	x^y oflows/uflows if |y|*LDBL_EPSILON/2 > -log2(LDBL_TRUE_MIN)+1 \
	*/ \
	if (F##BITS##_Abs(y) > 2*(-LDBL_MIN_EXP+LDBL_MANT_DIG+1)/LDBL_EPSILON) \
	{ \
		/* y is not an odd int */ \
		if (x == -1.0) \
			return 1.0; \
		if (y == INFINITY) \
		{ \
			if (x > 1.0 || x < -1.0) \
				return INFINITY; \
			return 0.0; \
		} \
		if (y == -INFINITY) \
		{ \
			if (x > 1.0 || x < -1.0) \
				return 0.0; \
			return INFINITY; \
		} \
		if ((x > 1.0 || x < -1.0) == (y > 0)) \
			return __data_pow_f##BITS.huge * __data_pow_f##BITS.huge; \
		return twom10000 * twom10000; \
	} \
	if (x == INFINITY) \
	{ \
		if (y > 0.0) \
			return INFINITY; \
		return 0.0; \
	} \
	w = F##BITS##_Floor(y); \
	/* Set iyflg to 1 if y is an integer. */ \
	iyflg = 0; \
	if (w == y) \
		iyflg = 1; \
	/* Test for odd integer y. */ \
	yoddint = 0; \
	if (iyflg) \
	{ \
		ya = F##BITS##_Abs(y); \
		ya = F##BITS##_Floor(0.5 * ya); \
		yb = 0.5 * F##BITS##_Abs(w); \
		if( ya != yb ) \
			yoddint = 1; \
	} \
	if (x == -INFINITY) \
	{ \
		if (y > 0.0) \
		{ \
			if (yoddint) \
				return -INFINITY; \
			return INFINITY; \
		} \
		if (y < 0.0) \
		{ \
			if (yoddint) \
				return -0.0; \
			return 0.0; \
		} \
	} \
	nflg = 0; /* (x<0)**(odd int) */ \
	if (x <= 0.0) \
	{ \
		if (x == 0.0) \
		{ \
			if (y < 0.0) \
			{ \
				if (signbit(x) && yoddint) \
					/* (-0.0)**(-odd int) = -inf, divbyzero */ \
					return -1.0/0.0; \
				/* (+-0.0)**(negative) = inf, divbyzero */ \
				return 1.0/0.0; \
			} \
			if (signbit(x) && yoddint) \
				return -0.0; \
			return 0.0; \
		} \
		if (iyflg == 0) \
			return (x - x) / (x - x); /* (x<0)**(non-int) is NaN */ \
		/* (x<0)**(integer) */ \
		if (yoddint) \
			nflg = 1; /* negate result */ \
		x = -x; \
	} \
	/* (+integer)**(integer) */ \
	if (iyflg && F##BITS##_Floor(x) == x && F##BITS##_Abs(y) < 32768.0) \
	{ \
		w = powil(x, (int)y); \
		return nflg ? -w : w; \
	} \
	/* separate significand from exponent */ \
	x = F##BITS##_SplitExp(x, &i); \
	e = i; \
	/* find significand in antilog table */ \
	i = 1; \
	if (x <= __data_pow_f##BITS.antilog[17]  )	i = 17; \
	if (x <= __data_pow_f##BITS.antilog[i+8] )	i += 8; \
	if (x <= __data_pow_f##BITS.antilog[i+4] )	i += 4; \
	if (x <= __data_pow_f##BITS.antilog[i+2] )	i += 2; \
	if (x >= __data_pow_f##BITS.antilog[1]   )	i = -1; \
	i += 1; \
	/* \
	Find (x - antilog[i])/antilog[i] in order to compute log(x/antilog[i]): \
	log(x) = log( a x/a ) = log(a) + log(x/a) \
	log(x/a) = log(1+v),  v = x/a - 1 = (x-a)/a \
	*/ \
	x -= __data_pow_f##BITS.antilog[i]; \
	x -= __data_pow_f##BITS.B[i/2]; \
	x /= __data_pow_f##BITS.antilog[i]; \
	/* \
	rational approximation for log(1+v): \
	log(1+v)  =  v  -  v**2/2  +  v**3 P(v) / Q(v) \
	*/ \
	z = x*x; \
	w = x * (z * __polynomial_f##BITS(x, P, 3) / __polynomial_f##BITS(x, Q, 3)); \
	w = w - 0.5*z; \
	/* Convert to base 2 logarithm: multiply by log2(e) = 1 + __data_pow_f##BITS.LOG2EA */ \
	z = __data_pow_f##BITS.LOG2EA * w; \
	z += w; \
	z += __data_pow_f##BITS.LOG2EA * x; \
	z += x; \
	/* Compute exponent term of the base 2 logarithm. */ \
	w = -i; \
	w /= NXT; \
	w += e; \
	/* Now base 2 log of x is w + z. */ \
	/* Multiply base 2 log by y, in extended precision. */ \
	/* separate y into large part ya  and small part yb less than 1/NXT  */ \
	ya = reducl(y); \
	yb = y - ya; \
	/* (w+z)(ya+yb) = w*ya + w*yb + z*y */ \
	F = z * y  +  w * yb; \
	Fa = reducl(F); \
	Fb = F - Fa; \
 \
	G = Fa + w * ya; \
	Ga = reducl(G); \
	Gb = G - Ga; \
 \
	H = Fb + Gb; \
	Ha = reducl(H); \
	w = (Ga + Ha) * NXT; \
	/* Test the power of 2 for overflow */ \
	if (w > __data_pow_f##BITS.MEXP) \
		return __data_pow_f##BITS.huge * __data_pow_f##BITS.huge; /* overflow */ \
	if (w < __data_pow_f##BITS.MNEXP) \
		return twom10000 * twom10000; /* underflow */ \
	e = w; \
	Hb = H - Ha; \
	if (Hb > 0.0) \
	{ \
		e += 1; \
		Hb -= 1.0/NXT;  /*0.0625L;*/ \
	} \
	/* \
	Now the product y * log2(x) = Hb + e/NXT. \
	Compute base 2 exponential of Hb, where -0.0625 <= Hb <= 0. \
	*/ \
	z = Hb * __polynomial_f##BITS(Hb, __data_pow_f##BITS.R, 6); /* z = 2**Hb - 1 */ \
	/* \
	Express e/NXT as an integer plus a negative number of (1/NXT)ths. \
	Find lookup table entry for the fractional power of 2. \
	*/ \
	if (e < 0) \
		i = 0; \
	else \
		i = 1; \
	i = e/NXT + i; \
	e = NXT*i - e; \
	w = __data_pow_f##BITS.antilog[e]; \
	z = w * z; /* 2**-e * ( 1 + (2**Hb-1) ) */ \
	z = z + w; \
	z = F##BITS##_From(z, i); /* multiply by integer power of 2 */ \
	if (nflg) \
		z = -z; \
	return z; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_POW(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_POW(128)
#endif



#endif
