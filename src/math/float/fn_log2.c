
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Log2, log2)
#elif 0 //LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_LOG2(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Log2(t_f##BITS x) \
{ \
	return (F##BITS##_Log(x) / LN_2); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_LOG2(16)
#endif
DEFINEFUNC_FLOAT_LOG2(32)

DEFINEFUNC_FLOAT_LOG2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG2(128)
#endif



#else

/*
ULP error: 0.752 (nearest rounding.)
Relative error: 1.9 * 2^-26 (before rounding.)
*/


#define LOG2F_TABLE_BITS 4
#undef N
#undef OFF
#define N (1 << LOG2F_TABLE_BITS)
#define OFF 0x3f330000

extern const struct data_log2_f32
{
	struct { t_f64 invc, logc; } table[N];
	t_f64 poly[4];
} __data_log2_f32;

const struct data_log2_f32 __data_log2_f32 =
{
	.table =
	{
		{ +0x1.661EC79F8F3BEp+0, -0x1.EFEC65B963019p-2 },
		{ +0x1.571ED4AAF883Dp+0, -0x1.B0B6832D4FCA4p-2 },
		{ +0x1.49539F0F010B0p+0, -0x1.7418B0A1FB77Bp-2 },
		{ +0x1.3C995B0B80385p+0, -0x1.39DE91A6DCF7Bp-2 },
		{ +0x1.30D190C8864A5p+0, -0x1.01D9BF3F2B631p-2 },
		{ +0x1.25E227B0B8EA0p+0, -0x1.97C1D1B3B7AF0p-3 },
		{ +0x1.1BB4A4A1A343Fp+0, -0x1.2F9E393AF3C9Fp-3 },
		{ +0x1.12358F08AE5BAp+0, -0x1.960CBBF788D5Cp-4 },
		{ +0x1.0953F419900A7p+0, -0x1.A6F9DB6475FCEp-5 },
		{ +0x1.0000000000000p+0, +0x0.0000000000000p+0 },
		{ +0x1.E608CFD9A47ACp-1, +0x1.338CA9F24F53Dp-4 },
		{ +0x1.CA4B31F026AA0p-1, +0x1.476A9543891BAp-3 },
		{ +0x1.B2036576AFCE6p-1, +0x1.E840B4AC4E4D2p-3 },
		{ +0x1.9C2D163A1AA2Dp-1, +0x1.40645F0C6651Cp-2 },
		{ +0x1.886E6037841EDp-1, +0x1.88E9C2C1B9FF8p-2 },
		{ +0x1.767DCF5534862p-1, +0x1.CE0A44EB17BCCp-2 },
	},
	.poly =
	{
		-0x1.712B6F70A7E4Dp-2,
		+0x1.ECABF496832E0p-2,
		-0x1.715479FFAE3DEp-1,
		+0x1.715475F35C8B8p+0,
	}
};

t_f32	F32_Log2(t_f32 x)
{
	t_f64 z, r, r2, p, y, y0, invc, logc;
	t_u32 ix, iz, top, tmp;
	int k, i;

	ix = AS_U32(x);
	/* Fix sign of zero with downward rounding when x==1.  */
	if (WANT_ROUNDING && predict_false(ix == 0x3f800000))
		return 0;
	if (predict_false(ix - 0x00800000 >= 0x7f800000 - 0x00800000))
	{
		/* x < 0x1p-126 or inf or nan.  */
		if CCCERROR((ix * 2 == 0), ERROR_MATHDOMAIN, NULL)
			return __math_divzero_f32(1);
		if (ix == 0x7f800000) /* log2(inf) == inf.  */
			return x;
		if CCCERROR(((ix & 0x80000000) || ix * 2 >= 0xff000000), ERROR_MATHDOMAIN, NULL)
			return __math_invalid_f32(x);
		/* x is subnormal, normalize it.  */
		ix = AS_U32(x * 0x1p23f);
		ix -= 23 << 23;
	}
	/* x = 2^k z; where z is in range [OFF,2*OFF] and exact.
	   The range is split into N subintervals.
	   The ith subinterval contains z and c is near its center.  */
	tmp = ix - OFF;
	i = (tmp >> (23 - LOG2F_TABLE_BITS)) % N;
	top = tmp & 0xff800000;
	iz = ix - top;
	k = (t_s32)tmp >> 23; /* arithmetic shift */
	invc = __data_log2_f32.table[i].invc;
	logc = __data_log2_f32.table[i].logc;
	z = (t_f64)AS_F32(iz);

	/* log2(x) = log1p(z/c-1)/ln2 + log2(c) + k */
	r = z * invc - 1;
	y0 = logc + (t_f64)k;

	/* Pipelined polynomial evaluation to approximate log1p(r)/ln2.  */
	r2 = r * r;
	y = __data_log2_f32.poly[1] * r + __data_log2_f32.poly[2];
	y = __data_log2_f32.poly[0] * r2 + y;
	p = __data_log2_f32.poly[3] * r + y0;
	y = y * r2 + p;
	return (t_f32)(y);
}



#define LOG2_TABLE_BITS 6
#undef N
#undef OFF
#define N (1 << LOG2_TABLE_BITS)
#define OFF 0x3FE6000000000000

extern const struct data_log2_f64
{
	t_f64 invln2hi;
	t_f64 invln2lo;
	t_f64 poly1[10];
	t_f64 poly[6];
	struct { t_f64 invc, logc; } table[N];
#if !__FP_FAST_FMA
	struct { t_f64 chi, clo; } table2[N];
#endif
} __data_log2_f64;

const struct data_log2_f64 __data_log2_f64 =
{
	// First coefficient: 0x1.71547652b82fe1777d0ffda0d24p0
	.invln2hi = 0x1.7154765200000p+0,
	.invln2lo = 0x1.705FC2EEFA200p-33,
	.poly1 =
	{
	// relative error: 0x1.2fad8188p-63
	// in -0x1.5b51p-5 0x1.6ab2p-5
		-0x1.71547652B82FEp-1,
		+0x1.EC709DC3A03F7p-2,
		-0x1.71547652B7C3Fp-2,
		+0x1.2776C50F05BE4p-2,
		-0x1.EC709DD768FE5p-3,
		+0x1.A61761EC4E736p-3,
		-0x1.7153FBC64A79Bp-3,
		+0x1.484D154F01B4Ap-3,
		-0x1.289E4A72C383Cp-3,
		+0x1.0B32F285AEE66p-3,
	},
	.poly =
	{
	// relative error: 0x1.a72c2bf8p-58
	// abs error: 0x1.67a552c8p-66
	// in -0x1.f45p-8 0x1.f45p-8
		-0x1.71547652B8339p-1,
		+0x1.EC709DC3A04BEp-2,
		-0x1.7154764702FFBp-2,
		+0x1.2776C50034C48p-2,
		-0x1.EC7B328EA92BCp-3,
		+0x1.A6225E117F92Ep-3,
	},
	/* Algorithm:

		x = 2^k z
		log2(x) = k + log2(c) + log2(z/c)
		log2(z/c) = poly(z/c - 1)

	where z is in [1.6p-1; 1.6p0] which is split into N subintervals and z falls
	into the ith one, then table entries are computed as

		table[i].invc = 1/c
		table[i].logc = (t_f64)log2(c)
		table2[i].chi = (t_f64)c
		table2[i].clo = (t_f64)(c - (t_f64)c)

	where c is near the center of the subinterval and is chosen by trying +-2^29
	floating point invc candidates around 1/center and selecting one for which

		1) the rounding error in 0x1.8p10 + logc is 0,
		2) the rounding error in z - chi - clo is < 0x1p-64 and
		3) the rounding error in (t_f64)log2(c) is minimized (< 0x1p-68).

	Note: 1) ensures that k + logc can be computed without rounding error, 2)
	ensures that z/c - 1 can be computed as (z - chi - clo)*invc with close to a
	single rounding error when there is no fast fma for z*invc - 1, 3) ensures
	that logc + poly(z/c - 1) has small error, however near x == 1 when
	|log2(x)| < 0x1p-4, this is not enough so that is special cased.  */
	.table =
	{
		{ +0x1.724286BB1ACF8p+0, -0x1.1095FEECDB000p-1 },
		{ +0x1.6E1F766D2CCA1p+0, -0x1.08494BD76D000p-1 },
		{ +0x1.6A13D0E30D48Ap+0, -0x1.00143AEE8F800p-1 },
		{ +0x1.661EC32D06C85p+0, -0x1.EFEC5360B4000p-2 },
		{ +0x1.623FA951198F8p+0, -0x1.DFDD91AB7E000p-2 },
		{ +0x1.5E75BA4CF026Cp+0, -0x1.CFFAE0CC79000p-2 },
		{ +0x1.5AC055A214FB8p+0, -0x1.C043811FDA000p-2 },
		{ +0x1.571ED0F166E1Ep+0, -0x1.B0B67323AE000p-2 },
		{ +0x1.53909590BF835p+0, -0x1.A152F5A2DB000p-2 },
		{ +0x1.5014FED61ADDDp+0, -0x1.9217F5AF86000p-2 },
		{ +0x1.4CAB88E487BD0p+0, -0x1.8304DB0719000p-2 },
		{ +0x1.49539B4334FEEp+0, -0x1.74189F9A9E000p-2 },
		{ +0x1.460CBDFAFD569p+0, -0x1.6552BB5199000p-2 },
		{ +0x1.42D664EE4B953p+0, -0x1.56B23A29B1000p-2 },
		{ +0x1.3FB01111DD8A6p+0, -0x1.483650F5FA000p-2 },
		{ +0x1.3C995B70C5836p+0, -0x1.39DE937F6A000p-2 },
		{ +0x1.3991C4AB6FD4Ap+0, -0x1.2BAA1538D6000p-2 },
		{ +0x1.3698E0CE099B5p+0, -0x1.1D98340CA4000p-2 },
		{ +0x1.33AE48213E7B2p+0, -0x1.0FA853A40E000p-2 },
		{ +0x1.30D191985BDB1p+0, -0x1.01D9C32E73000p-2 },
		{ +0x1.2E025CAB271D7p+0, -0x1.E857DA2FA6000p-3 },
		{ +0x1.2B404CF13CD82p+0, -0x1.CD3C8633D8000p-3 },
		{ +0x1.288B02C7CCB50p+0, -0x1.B26034C14A000p-3 },
		{ +0x1.25E2263944DE5p+0, -0x1.97C1C2F4FE000p-3 },
		{ +0x1.234563D8615B1p+0, -0x1.7D6023F800000p-3 },
		{ +0x1.20B46E33EAF38p+0, -0x1.633A71A05E000p-3 },
		{ +0x1.1E2EEFDCDA3DDp+0, -0x1.494F5E9570000p-3 },
		{ +0x1.1BB4A580B3930p+0, -0x1.2F9E424E0A000p-3 },
		{ +0x1.19453847F2200p+0, -0x1.162595AFDC000p-3 },
		{ +0x1.16E06C0D5D73Cp+0, -0x1.F9C9A75BD8000p-4 },
		{ +0x1.1485F47B7E4C2p+0, -0x1.C7B575BF9C000p-4 },
		{ +0x1.12358AD0085D1p+0, -0x1.960C60FF48000p-4 },
		{ +0x1.0FEF00F532227p+0, -0x1.64CE247B60000p-4 },
		{ +0x1.0DB2077D03A8Fp+0, -0x1.33F78B2014000p-4 },
		{ +0x1.0B7E6D65980D9p+0, -0x1.0387D1A42C000p-4 },
		{ +0x1.0953EFE7B408Dp+0, -0x1.A6F9208B50000p-5 },
		{ +0x1.07325CAC53B83p+0, -0x1.47A954F770000p-5 },
		{ +0x1.05197E40D1B5Cp+0, -0x1.D23A8C50C0000p-6 },
		{ +0x1.03091C1208EA2p+0, -0x1.16A2629780000p-6 },
		{ +0x1.0101025B37E21p+0, -0x1.720F8D8E80000p-8 },
		{ +0x1.FC07EF9CAA76Bp-1, +0x1.6FE53B1500000p-7 },
		{ +0x1.F4465D3F6F184p-1, +0x1.11CCCE10F8000p-5 },
		{ +0x1.ECC079F84107Fp-1, +0x1.C4DFC8C8B8000p-5 },
		{ +0x1.E573A99975AE8p-1, +0x1.3AA321E574000p-4 },
		{ +0x1.DE5D6F0BD3DE6p-1, +0x1.918A0D08B8000p-4 },
		{ +0x1.D77B681FF38B3p-1, +0x1.E72E9DA044000p-4 },
		{ +0x1.D0CB5724DE943p-1, +0x1.1DCD2507F6000p-3 },
		{ +0x1.CA4B2DC0E7563p-1, +0x1.476AB03DEA000p-3 },
		{ +0x1.C3F8EE8D6CB51p-1, +0x1.7074377E22000p-3 },
		{ +0x1.BDD2B4F020C4Cp-1, +0x1.98EDE8BA94000p-3 },
		{ +0x1.B7D6C006015CAp-1, +0x1.C0DB86AD2E000p-3 },
		{ +0x1.B20366E2E338Fp-1, +0x1.E840AAFCEE000p-3 },
		{ +0x1.AC57026295039p-1, +0x1.0790AB4678000p-2 },
		{ +0x1.A6D01BC2731DDp-1, +0x1.1AC056801C000p-2 },
		{ +0x1.A16D3BC3FF18Bp-1, +0x1.2DB11D4FEE000p-2 },
		{ +0x1.9C2D14967FEADp-1, +0x1.406464EC58000p-2 },
		{ +0x1.970E4F47C9902p-1, +0x1.52DBE093AF000p-2 },
		{ +0x1.920FB3982BCF2p-1, +0x1.651902050D000p-2 },
		{ +0x1.8D30187F759F1p-1, +0x1.771D2CDEAF000p-2 },
		{ +0x1.886E5EBB9F66Dp-1, +0x1.88E9C857D9000p-2 },
		{ +0x1.83C97B658B994p-1, +0x1.9A80155E16000p-2 },
		{ +0x1.7F405FFC61022p-1, +0x1.ABE186ED3D000p-2 },
		{ +0x1.7AD22181415CAp-1, +0x1.BD0F2AEA0E000p-2 },
		{ +0x1.767DCF99EFF8Cp-1, +0x1.CE0A43DBF4000p-2 },
	},
#if !__FP_FAST_FMA
	.table2 =
	{
		{ +0x1.6200012B90A8Ep-1, +0x1.904AB0644B605p-55 },
		{ +0x1.66000045734A6p-1, +0x1.1FF9BEA62F7A9p-57 },
		{ +0x1.69FFFC325F2C5p-1, +0x1.27ECFCB3C90BAp-55 },
		{ +0x1.6E00038B95A04p-1, +0x1.8FF8856739326p-55 },
		{ +0x1.71FFFE09994E3p-1, +0x1.AFD40275F82B1p-55 },
		{ +0x1.7600015590E10p-1, -0x1.2FD75B4238341p-56 },
		{ +0x1.7A00012655BD5p-1, +0x1.808E67C242B76p-56 },
		{ +0x1.7E0003259E9A6p-1, -0x1.208E426F622B7p-57 },
		{ +0x1.81FFFEDB4B2D2p-1, -0x1.402461EA5C92Fp-55 },
		{ +0x1.860002DFAFCC3p-1, +0x1.DF7F4A2F29A1Fp-57 },
		{ +0x1.89FFFF78C6B50p-1, -0x1.E0453094995FDp-55 },
		{ +0x1.8E00039671566p-1, -0x1.A04F3BEC77B45p-55 },
		{ +0x1.91FFFE2BF1745p-1, -0x1.7FA34400E203Cp-56 },
		{ +0x1.95FFFCC5C9FD1p-1, -0x1.6FF8005A0695Dp-56 },
		{ +0x1.9A0003BBA4767p-1, +0x1.0F8C4C4EC7E03p-56 },
		{ +0x1.9DFFFE7B92DA5p-1, +0x1.E7FD9478C4602p-55 },
		{ +0x1.A1FFFD72EFDAFp-1, -0x1.A0C554DCDAE7Ep-57 },
		{ +0x1.A5FFFDE04FF95p-1, +0x1.67DA98CE9B26Bp-55 },
		{ +0x1.A9FFFCA5E8D2Bp-1, -0x1.284C9B54C13DEp-55 },
		{ +0x1.ADFFFDDAD03EAp-1, +0x1.812C8EA602E3Cp-58 },
		{ +0x1.B1FFFF10D3D4Dp-1, -0x1.EFADDAD27789Cp-55 },
		{ +0x1.B5FFFCE21165Ap-1, +0x1.3CB1719C61237p-58 },
		{ +0x1.B9FFFD950E674p-1, +0x1.3F7D94194CE00p-56 },
		{ +0x1.BE000139CA8AFp-1, +0x1.50AC4215D9BC0p-56 },
		{ +0x1.C20005B46DF99p-1, +0x1.BEEA653E9C1C9p-57 },
		{ +0x1.C600040B9F7AEp-1, -0x1.C079F274A70D6p-56 },
		{ +0x1.CA0006255FD8Ap-1, -0x1.A0B4076E84C1Fp-56 },
		{ +0x1.CDFFFD94C095Dp-1, +0x1.8F933F99AB5D7p-55 },
		{ +0x1.D1FFFF975D6CFp-1, -0x1.82C08665FE1BEp-58 },
		{ +0x1.D5FFFA2561C93p-1, -0x1.B04289BD295F3p-56 },
		{ +0x1.D9FFF9D228B0Cp-1, +0x1.70251340FA236p-55 },
		{ +0x1.DE00065BC7E16p-1, -0x1.5011E16A4D80Cp-56 },
		{ +0x1.E200002F64791p-1, +0x1.9802F09EF62E0p-55 },
		{ +0x1.E600057D7A6D8p-1, -0x1.E0B75580CF7FAp-56 },
		{ +0x1.EA00027EDC00Cp-1, -0x1.C848309459811p-55 },
		{ +0x1.EE0006CF5CB7Cp-1, -0x1.F8027951576F4p-55 },
		{ +0x1.F2000782B7DCCp-1, -0x1.F81D97274538Fp-55 },
		{ +0x1.F6000260C450Ap-1, -0x1.071002727FFDCp-59 },
		{ +0x1.F9FFFE88CD533p-1, -0x1.81BDCE1FDA8B0p-58 },
		{ +0x1.FDFFFD50F8689p-1, +0x1.7F91ACB918E6Ep-55 },
		{ +0x1.0200004292367p+0, +0x1.B7FF365324681p-54 },
		{ +0x1.05FFFE3E3D668p+0, +0x1.6FA08DDAE957Bp-55 },
		{ +0x1.0A0000A85A757p+0, -0x1.7E2DE80D3FB91p-58 },
		{ +0x1.0E0001A5F3FCCp+0, -0x1.1823305C5F014p-54 },
		{ +0x1.11FFFF8AFBAF5p+0, -0x1.BFABB6680BAC2p-55 },
		{ +0x1.15FFFE54D91ADp+0, -0x1.D7F121737E7EFp-54 },
		{ +0x1.1A00011AC36E1p+0, +0x1.C000A0516F5FFp-54 },
		{ +0x1.1E00019C84248p+0, -0x1.082FBE4DA5DA0p-54 },
		{ +0x1.220000FFE5E6Ep+0, -0x1.8FDD04C9CFB43p-55 },
		{ +0x1.26000269FD891p+0, +0x1.CFE2A7994D182p-55 },
		{ +0x1.2A00029A6E6DAp+0, -0x1.00273715E8BC5p-56 },
		{ +0x1.2DFFFE0293E39p+0, +0x1.B7C39DAB2A6F9p-54 },
		{ +0x1.31FFFF7DCF082p+0, +0x1.DF1336EDC5254p-56 },
		{ +0x1.35FFFF05A8B60p+0, -0x1.E03564CCD31EBp-54 },
		{ +0x1.3A0002E0EAECCp+0, +0x1.5F0E74BD3A477p-56 },
		{ +0x1.3E000043BB236p+0, +0x1.C7DCB149D8833p-54 },
		{ +0x1.4200002D187FFp+0, +0x1.E08AFCF2D3D28p-56 },
		{ +0x1.460000D387CB1p+0, +0x1.20837856599A6p-55 },
		{ +0x1.4A00004569F89p+0, -0x1.9FA5C904FBCD2p-55 },
		{ +0x1.4E000043543F3p+0, -0x1.81125ED175329p-56 },
		{ +0x1.51FFFCC027F0Fp+0, +0x1.883D8847754DCp-54 },
		{ +0x1.55FFFFD87B36Fp+0, -0x1.709E731D02807p-55 },
		{ +0x1.59FFFF21DF7BAp+0, +0x1.7F79F68727B02p-55 },
		{ +0x1.5DFFFEBFC3481p+0, -0x1.180902E30E93Ep-54 },
	},
#endif
};

/* Top 16 bits of a t_f64.  */
static inline
t_u32	top16(t_f64 x)
{
	return AS_U64(x) >> 48;
}

t_f64	F64_Log2(t_f64 x)
{
	t_f64 z, r, r2, r4, y, invc, logc, kd, hi, lo, t1, t2, t3, p;
	t_u64 ix, iz, tmp;
	t_u32 top;
	int k, i;

	ix = AS_U64(x);
	top = top16(x);
#define LO AS_U64(1.0 - 0x1.5b51p-5)
#define HI AS_U64(1.0 + 0x1.6ab2p-5)
	if (predict_false(ix - LO < HI - LO))
	{
		/* Handle close to 1.0 inputs separately.  */
		/* Fix sign of zero with downward rounding when x==1.  */
		if (WANT_ROUNDING && predict_false(ix == AS_U64(1.0)))
			return 0;
		r = x - 1.0;
#if __FP_FAST_FMA
		hi = r * __data_log2_f64.invln2hi;
		lo = r * __data_log2_f64.invln2lo + __builtin_fma(r, __data_log2_f64.invln2hi, -hi);
#else
		t_f64 rhi, rlo;
		rhi = AS_F64(AS_U64(r) & -1ULL << 32);
		rlo = r - rhi;
		hi = rhi * __data_log2_f64.invln2hi;
		lo = rlo * __data_log2_f64.invln2hi + r * __data_log2_f64.invln2lo;
#endif
		r2 = r * r; /* rounding error: 0x1p-62.  */
		r4 = r2 * r2;
		/* Worst-case error is less than 0.54 ULP (0.55 ULP without fma).  */
		p = r2 * (__data_log2_f64.poly1[0] + r * __data_log2_f64.poly1[1]);
		y = hi + p;
		lo += hi - y + p;
		lo += r4 *
			(__data_log2_f64.poly1[2] + r * __data_log2_f64.poly1[3] + r2 *
			(__data_log2_f64.poly1[4] + r * __data_log2_f64.poly1[5]) + r4 *
			(__data_log2_f64.poly1[6] + r * __data_log2_f64.poly1[7] + r2 *
			(__data_log2_f64.poly1[8] + r * __data_log2_f64.poly1[9])));
		y += lo;
		return (t_f64)(y);
	}
	if (predict_false(top - 0x0010 >= 0x7ff0 - 0x0010))
	{
		/* x < 0x1p-1022 or inf or nan.  */
		if CCCERROR((ix * 2 == 0), ERROR_MATHDOMAIN, NULL)
			return __math_divzero_f64(1);
		if (ix == AS_U64(INFINITY)) /* log(inf) == inf.  */
			return x;
		if CCCERROR(((top & 0x8000) || (top & 0x7ff0) == 0x7ff0), ERROR_MATHDOMAIN, NULL)
			return __math_invalid_f64(x);
		/* x is subnormal, normalize it.  */
		ix = AS_U64(x * 0x1p52);
		ix -= 52ULL << 52;
	}

	/* x = 2^k z; where z is in range [OFF,2*OFF) and exact.
	   The range is split into N subintervals.
	   The ith subinterval contains z and c is near its center.  */
	tmp = ix - OFF;
	i = (tmp >> (52 - LOG2_TABLE_BITS)) % N;
	k = (t_s64)tmp >> 52; /* arithmetic shift */
	iz = ix - (tmp & 0xfffULL << 52);
	invc = __data_log2_f64.table[i].invc;
	logc = __data_log2_f64.table[i].logc;
	z = AS_F64(iz);
	kd = (t_f64)k;

	/* log2(x) = log2(z/c) + log2(c) + k.  */
	/* r ~= z/c - 1, |r| < 1/(2*N).  */
#if __FP_FAST_FMA
	/* rounding error: 0x1p-55/N.  */
	r = __builtin_fma(z, invc, -1.0);
	t1 = r * __data_log2_f64.invln2hi;
	t2 = r * __data_log2_f64.invln2lo + __builtin_fma(r, __data_log2_f64.invln2hi, -t1);
#else
	t_f64 rhi, rlo;
	/* rounding error: 0x1p-55/N + 0x1p-65.  */
	r = (z - __data_log2_f64.table2[i].chi - __data_log2_f64.table2[i].clo) * invc;
	rhi = AS_F64(AS_U64(r) & -1ULL << 32);
	rlo = r - rhi;
	t1 = rhi * __data_log2_f64.invln2hi;
	t2 = rlo * __data_log2_f64.invln2hi + r * __data_log2_f64.invln2lo;
#endif

	/* hi + lo = r/ln2 + log2(c) + k.  */
	t3 = kd + logc;
	hi = t3 + t1;
	lo = t3 - hi + t1 + t2;

	/* log2(r+1) = r/ln2 + r^2*poly(r).  */
	/* Evaluation is optimized assuming superscalar pipelined execution.  */
	r2 = r * r; /* rounding error: 0x1p-54/N^2.  */
	r4 = r2 * r2;
	/* Worst-case error if |y| > 0x1p-4: 0.547 ULP (0.550 ULP without fma).
	   ~ 0.5 + 2/N/ln2 + abs-poly-error*0x1p56 ULP (+ 0.003 ULP without fma).  */
	p = __data_log2_f64.poly[0] + r *
		__data_log2_f64.poly[1] + r2 * (
		__data_log2_f64.poly[2] + r *
		__data_log2_f64.poly[3]) + r4 * (
		__data_log2_f64.poly[4] + r *
		__data_log2_f64.poly[5]);
	y = lo + r2 * p + hi;
	return (t_f64)(y);
}





/*
**      Base 2 logarithm, t_f80 precision
**
**
** SYNOPSIS:
**
** t_f80 x, y, log2l();
**
** y = log2l( x );
**
**
** DESCRIPTION:
**
** Returns the base 2 logarithm of x.
**
** The argument is separated into its exponent and fractional
** parts.  If the exponent is between -1 and +1, the (natural)
** logarithm of the fraction is approximated by
**
**     log(1+x) = x - 0.5 x**2 + x**3 P(x)/Q(x).
**
** Otherwise, setting  z = 2(x-1)/x+1),
**
**     log(x) = z + z**3 P(z)/Q(z).
**
**
** ACCURACY:
**
**                      Relative error:
** arithmetic   domain     # trials      peak         rms
**    IEEE      0.5, 2.0     30000      9.8e-20     2.7e-20
**    IEEE     exp(+-10000)  70000      5.4e-20     2.3e-20
**
** In the tests over the interval exp(+-10000), the logarithms
** of the random arguments were uniformly distributed over
** [-10000, +10000].
*/

#define DEFINEFUNC_FLOAT_LOG2(BITS) \
static const \
struct data_log2_f##BITS \
{ \
	t_f##BITS	P[7]; \
	t_f##BITS	Q[8]; \
	t_f##BITS	R[4]; \
	t_f##BITS	S[4]; \
	t_f##BITS	LOG2EA; \
	t_f##BITS	SQRTH; \
} \
__data_log2_f##BITS = \
{ \
	/* Coefficients for ln(1+x) = x - x**2/2 + x**3 P(x)/Q(x) \
	** 1/sqrt(2) <= x < sqrt(2) \
	** Theoretical peak relative error = 6.2e-22 \
	*/ \
	.P = \
	{ \
		+4.9962495940332550844739e-1L, \
		+1.0767376367209449010438e+1L, \
		+7.7671073698359539859595e+1L, \
		+2.5620629828144409632571e+2L, \
		+4.2401812743503691187826e+2L, \
		+3.4258224542413922935104e+2L, \
		+1.0747524399916215149070e+2L, \
	}, \
	.Q = \
	{ \
		+1.0000000000000000000000e+0L, \
		+2.3479774160285863271658e+1L, \
		+1.9444210022760132894510e+2L, \
		+7.7952888181207260646090e+2L, \
		+1.6911722418503949084863e+3L, \
		+2.0307734695595183428202e+3L, \
		+1.2695660352705325274404e+3L, \
		+3.2242573199748645407652e+2L, \
	}, \
	/* Coefficients for log(x) = z + z^3 P(z^2)/Q(z^2), \
	** where z = 2(x-1)/(x+1) \
	** 1/sqrt(2) <= x < sqrt(2) \
	** Theoretical peak relative error = 6.16e-22 \
	*/ \
	.R = \
	{ \
		+1.9757429581415468984296e-3L, \
		-7.1990767473014147232598e-1L, \
		+1.0777257190312272158094e+1L, \
		-3.5717684488096787370998e+1L, \
	}, \
	.S = \
	{ \
		+1.0000000000000000000000e+0L, \
		-2.6201045551331104417768e+1L, \
		+1.9361891836232102174846e+2L, \
		-4.2861221385716144629696e+2L, \
	}, \
	/* log2(e) - 1 */ \
	.LOG2EA = 4.4269504088896340735992e-1L, \
	.SQRTH = 0.70710678118654752440L, \
}; \
 \
t_f##BITS	F##BITS##_Log2(t_f##BITS x) \
{ \
	t_f##BITS y, z; \
	int e; \
 \
	if (IS_NAN(x)) \
		return x; \
	if (x == INFINITY) \
		return x; \
	if (x <= 0.0) \
	{ \
		if (x == 0.0) \
			return -1/(x*x); /* -inf with divbyzero */ \
		return 0/0.0f; /* nan with invalid */ \
	} \
 \
	/* separate mantissa from exponent */ \
	/* Note, frexp is used so that denormal numbers \
	**	will be handled properly. \
	*/ \
	x = F##BITS##_SplitExp(x, &e); \
 \
	/* logarithm using log(x) = z + z**3 P(z)/Q(z), \
	**	where z = 2(x-1)/x+1) \
	*/ \
	if (e > 2 || e < -2) \
	{ \
		if (x < __data_log2_f##BITS.SQRTH) \
		{  /* 2(2x-1)/(2x+1) */ \
			e -= 1; \
			z = x - 0.5; \
			y = 0.5 * z + 0.5; \
		} \
		else \
		{  /*  2 (x-1)/(x+1)   */ \
			z = x - 0.5; \
			z -= 0.5; \
			y = 0.5 * x + 0.5; \
		} \
		x = z / y; \
		z = x*x; \
		y = x * (z * __polynomial_f##BITS(z, __data_log2_f##BITS.R, 3) / __polynomial_f##BITS(z, __data_log2_f##BITS.S, 3)); \
		goto done; \
	} \
 \
	/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */ \
	if (x < __data_log2_f##BITS.SQRTH) \
	{ \
		e -= 1; \
		x = 2.0*x - 1.0; \
	} \
	else \
	{ \
		x = x - 1.0; \
	} \
	z = x*x; \
	y = x * (z * __polynomial_f##BITS(x, __data_log2_f##BITS.P, 6) / __polynomial_f##BITS(x, __data_log2_f##BITS.Q, 7)); \
	y = y - 0.5*z; \
 \
done: \
	/* Multiply log of fraction by log2(e) \
	**	and base 2 exponent by 1 \
	**	\
	**	***CAUTION*** \
	**	\
	**	This sequence of operations is critical and it may \
	**	be horribly defeated by some compiler optimizers. \
	*/ \
	z = y * __data_log2_f##BITS.LOG2EA; \
	z += x * __data_log2_f##BITS.LOG2EA; \
	z += y; \
	z += x; \
	z += e; \
	return z; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG2(128)
#endif



#endif
