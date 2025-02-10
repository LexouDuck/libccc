
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Erf, erf)
MATH_DECL_REALFUNCTION(ErfC, erfc)

#else
/*
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/
/* t_f64 erf(t_f64 x)
** t_f64 erfc(t_f64 x)
**                           x
**                    2      |\
**     erf(x)  =  ---------  | exp(-t*t)dt
**                 sqrt(pi) \|
**                           0
**
**     erfc(x) =  1-erf(x)
**  Note that
**              erf(-x) = -erf(x)
**              erfc(-x) = 2 - erfc(x)
**
** Method:
**      1. For |x| in [0, 0.84375]
**          erf(x)  = x + x*R(x^2)
**          erfc(x) = 1 - erf(x)           if x in [-.84375,0.25]
**                  = 0.5 + ((0.5-x)-x*R)  if x in [0.25,0.84375]
**         where R = P/Q where P is an odd poly of degree 8 and
**         Q is an odd poly of degree 10.
**                                               -57.90
**                      | R - (erf(x)-x)/x | <= 2
**
**
**         Remark. The formula is derived by noting
**          erf(x) = (2/sqrt(pi))*(x - x^3/3 + x^5/10 - x^7/42 + ....)
**         and that
**          2/sqrt(pi) = 1.128379167095512573896158903121545171688
**         is close to one. The interval is chosen because the fix
**         point of erf(x) is near 0.6174 (i.e., erf(x)=x when x is
**         near 0.6174), and by some experiment, 0.84375 is chosen to
**         guarantee the error is less than one ulp for erf.
**
**      2. For |x| in [0.84375,1.25], let s = |x| - 1, and
**         c = 0.84506291151 rounded to single (24 bits)
**              erf(x)  = sign(x) * (c  + P1(s)/Q1(s))
**              erfc(x) = (1-c)  - P1(s)/Q1(s) if x > 0
**                        1+(c+P1(s)/Q1(s))    if x < 0
**              |P1/Q1 - (erf(|x|)-c)| <= 2**-59.06
**         Remark: here we use the taylor series expansion at x=1.
**              erf(1+s) = erf(1) + s*Poly(s)
**                       = 0.845.. + P1(s)/Q1(s)
**         That is, we use rational approximation to approximate
**                      erf(1+s) - (c = (single)0.84506291151)
**         Note that |P1/Q1|< 0.078 for x in [0.84375,1.25]
**         where
**              P1(s) = degree 6 poly in s
**              Q1(s) = degree 6 poly in s
**
**      3. For x in [1.25,1/0.35(~2.857143)],
**              erfc(x) = (1/x)*exp(-x*x-0.5625+R1/S1)
**              erf(x)  = 1 - erfc(x)
**         where
**              R1(z) = degree 7 poly in z, (z=1/x^2)
**              S1(z) = degree 8 poly in z
**
**      4. For x in [1/0.35,28]
**              erfc(x) = (1/x)*exp(-x*x-0.5625+R2/S2) if x > 0
**                      = 2.0 - (1/x)*exp(-x*x-0.5625+R2/S2) if -6<x<0
**                      = 2.0 - tiny            (if x <= -6)
**              erf(x)  = sign(x)*(1.0 - erfc(x)) if x < 6, else
**              erf(x)  = sign(x)*(1.0 - tiny)
**         where
**              R2(z) = degree 6 poly in z, (z=1/x^2)
**              S2(z) = degree 7 poly in z
**
**      Note1:
**         To compute exp(-x*x-0.5625+R/S), let s be a single
**         precision number and s := x; then
**              -x*x = -s*s + (s-x)*(s+x)
**              exp(-x*x-0.5626+R/S) =
**                      exp(-s*s-0.5625)*exp((s-x)*(s+x)+R/S);
**      Note2:
**         Here 4 and 5 make use of the asymptotic series
**                        exp(-x*x)
**              erfc(x) ~ ---------- * ( 1 + Poly(1/x^2) )
**                        x*sqrt(pi)
**         We use rational approximation to approximate
**              g(s)=f(1/x^2) = log(erfc(x)*x) - x*x + 0.5625
**         Here is the error bound for R1/S1 and R2/S2
**              |R1/S1 - f(x)|  < 2**(-62.57)
**              |R2/S2 - f(x)|  < 2**(-61.52)
**
**      5. For inf > x >= 28
**              erf(x)  = sign(x) *(1 - tiny)  (raise inexact)
**              erfc(x) = tiny*tiny (raise underflow) if x > 0
**                      = 2 - tiny if x<0
**
**      7. Special case:
**              erf(0)  = 0, erf(inf)  = 1, erf(-inf) = -1,
**              erfc(0) = 1, erfc(inf) = 0, erfc(-inf) = 2,
**              erfc/erf(NaN) is NaN
*/



#define DEFINEDATA_FLOAT_ERF(BITS) \
struct data_erf_f##BITS \
{ \
	t_f##BITS	erx; \
	t_f##BITS	efx8; \
	t_f##BITS	pp[5]; \
	t_f##BITS	qq[6]; \
	t_f##BITS	pa[7]; \
	t_f##BITS	qa[7]; \
	t_f##BITS	ra[8]; \
	t_f##BITS	sa[9]; \
	t_f##BITS	rb[7]; \
	t_f##BITS	sb[8]; \
	t_f##BITS	rc[6]; \
	t_f##BITS	sc[6]; \
}; \

#if LIBCONFIG_USE_FLOAT16
DEFINEDATA_FLOAT_ERF(16)
#endif
DEFINEDATA_FLOAT_ERF(32)

DEFINEDATA_FLOAT_ERF(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEDATA_FLOAT_ERF(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEDATA_FLOAT_ERF(128)
#endif

const struct data_erf_f32 __data_erf_f32 =
{
	.erx  = +8.4506291151e-01f, /* 0x3F58560B */
	/* Coefficients for approximation to  erf on [0,0.84375] */
	.efx8 = +1.0270333290e+00f, /* 0x3F8375D4 */
	.pp =
	{
		-2.3763017452e-05f, /* 0xB7C756B1 */
		-5.7702702470e-03f, /* 0xBBBD1489 */
		-2.8481749818e-02f, /* 0xBCE9528F */
		-3.2504209876e-01f, /* 0xBEA66BEB */
		+1.2837916613e-01f, /* 0x3E0375D4 */
	},
	.qq =
	{
		-3.9602282413e-06, /* 0xB684E21A */
		+1.3249473704e-04, /* 0x390AEE49 */
		+5.0813062117e-03, /* 0x3BA68116 */
		+6.5022252500e-02, /* 0x3D852A63 */
		+3.9791721106e-01, /* 0x3ECBBBCE */
		+1.0000000000e+00,
	},
	/* Coefficients for approximation to  erf  in [0.84375,1.25] */
	.pa =
	{
		-2.1663755178e-03, /* 0xBB0DF9C0 */
		+3.5478305072e-02, /* 0x3D1151B3 */
		-1.1089469492e-01, /* 0xBDE31CC2 */
		+3.1834661961e-01, /* 0x3EA2FE54 */
		-3.7220788002e-01, /* 0xBEBE9208 */
		+4.1485610604e-01, /* 0x3ED46805 */
		-2.3621185683e-03, /* 0xBB1ACDC6 */
	},
	.qa =
	{
		+1.1984500103e-02, /* 0x3C445AA3 */
		+1.3637083583e-02, /* 0x3C5F6E13 */
		+1.2617121637e-01, /* 0x3E013307 */
		+7.1828655899e-02, /* 0x3D931AE7 */
		+5.4039794207e-01, /* 0x3F0A5785 */
		+1.0642088205e-01, /* 0x3DD9F331 */
		+1.0000000000e+00,
	},
	/* Coefficients for approximation to  erfc in [1.25,1/0.35] */
	.ra =
	{
		-9.8143291473e+00, /* 0xC11D077E */
		-8.1287437439e+01, /* 0xC2A2932B */
		-1.8460508728e+02, /* 0xC3389AE7 */
		-1.6239666748e+02, /* 0xC322658C */
		-6.2375331879e+01, /* 0xC2798057 */
		-1.0558626175e+01, /* 0xC128F022 */
		-6.9385856390e-01, /* 0xBF31A0B7 */
		-9.8649440333e-03, /* 0xBC21A093 */
	},
	.sa =
	{
		-6.0424413532e-02, /* 0xBD777F97 */
		+6.5702495575e+00, /* 0x40D23F7C */
		+1.0863500214e+02, /* 0x42D9451F */
		+4.2900814819e+02, /* 0x43D6810B */
		+6.4538726807e+02, /* 0x442158C9 */
		+4.3456588745e+02, /* 0x43D9486F */
		+1.3765776062e+02, /* 0x4309A863 */
		+1.9651271820e+01, /* 0x419D35CE */
		+1.0000000000e+00,
	},
	/* Coefficients for approximation to  erfc in [1/.35,28] */
	.rb =
	{
		-4.8351919556e+02, /* 0xC3F1C275 */
		-1.0250950928e+03, /* 0xC480230B */
		-6.3756646729e+02, /* 0xC41F6441 */
		-1.6063638306e+02, /* 0xC320A2EA */
		-1.7757955551e+01, /* 0xC18E104B */
		-7.9928326607e-01, /* 0xBF4C9DD4 */
		-9.8649431020e-03, /* 0xBC21A092 */
	},
	.sb =
	{
		-2.2440952301e+01, /* 0xC1B38712 */
		+4.7452853394e+02, /* 0x43ED43A7 */
		+2.5530502930e+03, /* 0x451F90CE */
		+3.1998581543e+03, /* 0x4547FDBB */
		+1.5367296143e+03, /* 0x44C01759 */
		+3.2579251099e+02, /* 0x43A2E571 */
		+3.0338060379e+01, /* 0x41F2B459 */
		+1.0000000000e+00,
	},
	.rc = {0},
	.sc = {0},
};

const struct data_erf_f64 __data_erf_f64 =
{
	.erx  = 8.45062911510467529297e-01, /* 0x3FEB0AC1, 0x60000000 */
/* Coefficients for approximation to  erf on [0,0.84375] */
	.efx8 = +1.02703333676410069053e+00, /* 0x3FF06EBA, 0x8214DB69 */
	.pp =
	{
		-2.37630166566501626084e-05, /* 0xBEF8EAD6, 0x120016AC */
		-5.77027029648944159157e-03, /* 0xBF77A291, 0x236668E4 */
		-2.84817495755985104766e-02, /* 0xBF9D2A51, 0xDBD7194F */
		-3.25042107247001499370e-01, /* 0xBFD4CD7D, 0x691CB913 */
		+1.28379167095512558561e-01, /* 0x3FC06EBA, 0x8214DB68 */
	},
	.qq =
	{
		-3.96022827877536812320e-06, /* 0xBED09C43, 0x42A26120 */
		+1.32494738004321644526e-04, /* 0x3F215DC9, 0x221C1A10 */
		+5.08130628187576562776e-03, /* 0x3F74D022, 0xC4D36B0F */
		+6.50222499887672944485e-02, /* 0x3FB0A54C, 0x5536CEBA */
		+3.97917223959155352819e-01, /* 0x3FD97779, 0xCDDADC09 */
		+1.00000000000000000000e+00,
	},
/* Coefficients for approximation to  erf  in [0.84375,1.25] */
	.pa =
	{
		-2.16637559486879084300e-03, /* 0xBF61BF38, 0x0A96073F */
		+3.54783043256182359371e-02, /* 0x3FA22A36, 0x599795EB */
		-1.10894694282396677476e-01, /* 0xBFBC6398, 0x3D3E28EC */
		+3.18346619901161753674e-01, /* 0x3FD45FCA, 0x805120E4 */
		-3.72207876035701323847e-01, /* 0xBFD7D240, 0xFBB8C3F1 */
		+4.14856118683748331666e-01, /* 0x3FDA8D00, 0xAD92B34D */
		-2.36211856075265944077e-03, /* 0xBF6359B8, 0xBEF77538 */
	},
	.qa =
	{
		+1.19844998467991074170e-02, /* 0x3F888B54, 0x5735151D */
		+1.36370839120290507362e-02, /* 0x3F8BEDC2, 0x6B51DD1C */
		+1.26171219808761642112e-01, /* 0x3FC02660, 0xE763351F */
		+7.18286544141962662868e-02, /* 0x3FB2635C, 0xD99FE9A7 */
		+5.40397917702171048937e-01, /* 0x3FE14AF0, 0x92EB6F33 */
		+1.06420880400844228286e-01, /* 0x3FBB3E66, 0x18EEE323 */
		+1.00000000000000000000e+00,
	},
/* Coefficients for approximation to  erfc in [1.25,1/0.35] */
	.ra =
	{
		-9.81432934416914548592e+00, /* 0xC023A0EF, 0xC69AC25C */
		-8.12874355063065934246e+01, /* 0xC0545265, 0x57E4D2F2 */
		-1.84605092906711035994e+02, /* 0xC067135C, 0xEBCCABB2 */
		-1.62396669462573470355e+02, /* 0xC0644CB1, 0x84282266 */
		-6.23753324503260060396e+01, /* 0xC04F300A, 0xE4CBA38D */
		-1.05586262253232909814e+01, /* 0xC0251E04, 0x41B0E726 */
		-6.93858572707181764372e-01, /* 0xBFE63416, 0xE4BA7360 */
		-9.86494403484714822705e-03, /* 0xBF843412, 0x600D6435 */
	},
	.sa =
	{
		-6.04244152148580987438e-02, /* 0xBFAEEFF2, 0xEE749A62 */
		+6.57024977031928170135e+00, /* 0x401A47EF, 0x8E484A93 */
		+1.08635005541779435134e+02, /* 0x405B28A3, 0xEE48AE2C */
		+4.29008140027567833386e+02, /* 0x407AD021, 0x57700314 */
		+6.45387271733267880336e+02, /* 0x40842B19, 0x21EC2868 */
		+4.34565877475229228821e+02, /* 0x407B290D, 0xD58A1A71 */
		+1.37657754143519042600e+02, /* 0x4061350C, 0x526AE721 */
		+1.96512716674392571292e+01, /* 0x4033A6B9, 0xBD707687 */
		+1.00000000000000000000e+00,
	},
/* Coefficients for approximation to  erfc in [1/.35,28] */
	.rb =
	{
		-4.83519191608651397019e+02, /* 0xC07E384E, 0x9BDC383F */
		-1.02509513161107724954e+03, /* 0xC0900461, 0x6A2E5992 */
		-6.37566443368389627722e+02, /* 0xC083EC88, 0x1375F228 */
		-1.60636384855821916062e+02, /* 0xC064145D, 0x43C5ED98 */
		-1.77579549177547519889e+01, /* 0xC031C209, 0x555F995A */
		-7.99283237680523006574e-01, /* 0xBFE993BA, 0x70C285DE */
		-9.86494292470009928597e-03, /* 0xBF843412, 0x39E86F4A */
	},
	.sb =
	{
		-2.24409524465858183362e+01, /* 0xC03670E2, 0x42712D62 */
		+4.74528541206955367215e+02, /* 0x407DA874, 0xE79FE763 */
		+2.55305040643316442583e+03, /* 0x40A3F219, 0xCEDF3BE6 */
		+3.19985821950859553908e+03, /* 0x40A8FFB7, 0x688C246A */
		+1.53672958608443695994e+03, /* 0x409802EB, 0x189D5118 */
		+3.25792512996573918826e+02, /* 0x40745CAE, 0x221B9F0A */
		+3.03380607434824582924e+01, /* 0x403E568B, 0x261D5190 */
		+1.00000000000000000000e+00,
	},
	.rc = {0},
	.sc = {0},
};

#define DEFINEDATA_FLOAT_ERF_LD(BITS) \
const struct data_erf_f##BITS __data_erf_f##BITS = \
{ \
	.erx = 0.845062911510467529296875L, \
	/* Coefficients for approximation to  erf on [0,0.84375] */ \
	/* 8 * (2/sqrt(pi) - 1) */ \
	.efx8 = 1.0270333367641005911692712249723613735048e+00L, \
	.pp = \
	{ \
		+1.122751350964552113068262337278335028553e+06L, \
		-2.808533301997696164408397079650699163276e+06L, \
		-3.314325479115357458197119660818768924100e+05L, \
		-6.848684465326256109712135497895525446398e+04L, \
		-2.657817695110739185591505062971929859314e+03L, \
		-1.655310302737837556654146291646499062882e+02L, \
	}, \
	.qq = \
	{ \
		+8.745588372054466262548908189000448124232e+06L, \
		+3.746038264792471129367533128637019611485e+06L, \
		+7.066358783162407559861156173539693900031e+05L, \
		+7.448928604824620999413120955705448117056e+04L, \
		+4.511583986730994111992253980546131408924e+03L, \
		+1.368902937933296323345610240009071254014e+02L, \
		+1.000000000000000000000000000000000000000e+00L, \
	}, \
	/* Coefficients for approximation to  erf  in [0.84375,1.25] */ \
	/* erf(x+1) = 0.845062911510467529296875 + pa(x)/qa(x) | -0.15625 <= x <= +.25 | Peak relative error 8.5e-22 */ \
	.pa = \
	{ \
		-1.076952146179812072156734957705102256059e+00L, \
		+1.884814957770385593365179835059971587220e+02L, \
		-5.339153975012804282890066622962070115606e+01L, \
		+4.435910679869176625928504532109635632618e+01L, \
		+1.683219516032328828278557309642929135179e+01L, \
		-2.360236618396952560064259585299045804293e+00L, \
		+1.852230047861891953244413872297940938041e+00L, \
		+9.394994446747752308256773044667843200719e-02L, \
	}, \
	.qa = \
	{ \
		+4.559263722294508998149925774781887811255e+02L, \
		+3.289248982200800575749795055149780689738e+02L, \
		+2.846070965875643009598627918383314457912e+02L, \
		+1.398715859064535039433275722017479994465e+02L, \
		+6.060190733759793706299079050985358190726e+01L, \
		+2.078695677795422351040502569964299664233e+01L, \
		+4.641271134150895940966798357442234498546e+00L, \
		+1.000000000000000000000000000000000000000e+00L, \
	}, \
	/* Coefficients for approximation to  erfc in [1.25,1/0.35] */ \
	/* erfc(1/x) = x exp (-1/x^2 - 0.5625 + ra(x^2)/sa(x^2)) | 1/2.85711669921875 < 1/x < 1/1.25 | Peak relative error 3.1e-21 */ \
	.ra = \
	{ \
		+1.363566591833846324191000679620738857234e-01L, \
		+1.018203167219873573808450274314658434507e+01L, \
		+1.862359362334248675526472871224778045594e+02L, \
		+1.411622588180721285284945138667933330348e+03L, \
		+5.088538459741511988784440103218342840478e+03L, \
		+8.928251553922176506858267311750789273656e+03L, \
		+7.264436000148052545243018622742770549982e+03L, \
		+2.387492459664548651671894725748959751119e+03L, \
		+2.220916652813908085449221282808458466556e+02L, \
	}, \
	.sa = \
	{ \
		-1.382234625202480685182526402169222331847e+01L, \
		-3.315638835627950255832519203687435946482e+02L, \
		-2.949124863912936259747237164260785326692e+03L, \
		-1.246622099070875940506391433635999693661e+04L, \
		-2.673079795851665428695842853070996219632e+04L, \
		-2.880269786660559337358397106518918220991e+04L, \
		-1.450600228493968044773354186390390823713e+04L, \
		-2.874539731125893533960680525192064277816e+03L, \
		-1.402241261419067750237395034116942296027e+02L, \
		+1.000000000000000000000000000000000000000e+00L, \
	}, \
	/* Coefficients for approximation to  erfc in [1/.35,107] */ \
	/* erfc(1/x) = x exp (-1/x^2 - 0.5625 + rb(x^2)/sb(x^2)) | 1/6.6666259765625 < 1/x < 1/2.85711669921875 | Peak relative error 4.2e-22 */ \
	.rb = \
	{ \
		-4.869587348270494309550558460786501252369e-05L, \
		-4.030199390527997378549161722412466959403e-03L, \
		-9.434425866377037610206443566288917589122e-02L, \
		-9.319032754357658601200655161585539404155e-01L, \
		-4.273788174307459947350256581445442062291e+00L, \
		-8.842289940696150508373541814064198259278e+00L, \
		-7.069215249419887403187988144752613025255e+00L, \
		-1.401228723639514787920274427443330704764e+00L, \
	}, \
	.sb = \
	{ \
		+4.936254964107175160157544545879293019085e-03L, \
		+1.583457624037795744377163924895349412015e-01L, \
		+1.850647991850328356622940552450636420484e+00L, \
		+9.927611557279019463768050710008450625415e+00L, \
		+2.531667257649436709617165336779212114570e+01L, \
		+2.869752886406743386458304052862814690045e+01L, \
		+1.182059497870819562441683560749192539345e+01L, \
		+1.000000000000000000000000000000000000000e+00L, \
	}, \
	/* erfc(1/x) = x exp (-1/x^2 - 0.5625 + rc(x^2)/sc(x^2)) | 1/107 <= 1/x <= 1/6.6666259765625 | Peak relative error 1.1e-21 */ \
	.rc = \
	{ \
		-8.299617545269701963973537248996670806850e-05L, \
		-6.243845685115818513578933902532056244108e-03L, \
		-1.141667210620380223113693474478394397230e-01L, \
		-7.521343797212024245375240432734425789409e-01L, \
		-1.765321928311155824664963633786967602934e+00L, \
		-1.029403473103215800456761180695263439188e+00L, \
	}, \
	.sc = \
	{ \
		+8.413244363014929493035952542677768808601e-03L, \
		+2.065114333816877479753334599639158060979e-01L, \
		+1.639064941530797583766364412782135680148e+00L, \
		+4.936788463787115555582319302981666347450e+00L, \
		+5.005177727208955487404729933261347679090e+00L, \
		+1.000000000000000000000000000000000000000e+00L, \
	}, \
}; \

#if LIBCONFIG_USE_FLOAT80
DEFINEDATA_FLOAT_ERF_LD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEDATA_FLOAT_ERF_LD(128)
#endif



#define DEFINEFUNC_FLOAT_ERF(BITS, TINY, ZMASK) \
static \
t_f##BITS F##BITS##_ErfC1(t_f##BITS abs_x) \
 \
{ \
	t_f##BITS s,P,Q; \
	s = abs_x - 1; \
	P = __polynomial_f##BITS(s, __data_erf_f##BITS.pa, 6); \
	Q = __polynomial_f##BITS(s, __data_erf_f##BITS.qa, 6); \
	return (1 - __data_erf_f##BITS.erx - P / Q); \
} \
 \
static \
t_f##BITS F##BITS##_ErfC2(t_f##BITS abs_x) \
{ \
	t_f##BITS z,s,R,S; \
	u_cast_f##BITS tmp; \
	s = 1 / (abs_x * abs_x); \
	if (abs_x < (1. / 0.35)) \
	{ \
		R = __polynomial_f##BITS(s, __data_erf_f##BITS.ra, 7); \
		S = __polynomial_f##BITS(s, __data_erf_f##BITS.sa, 8); \
	} \
	else /* |x| >= 1/.35 */ \
	{ \
		R = __polynomial_f##BITS(s, __data_erf_f##BITS.rb, 6); \
		S = __polynomial_f##BITS(s, __data_erf_f##BITS.sb, 7); \
	} \
	tmp.as_f = abs_x; \
	tmp.as_u &= ((~(t_u##BITS)0) << ZMASK); \
	z = tmp.as_f; \
	return ( \
		F##BITS##_Exp(-z * z - 0.5625) * \
		F##BITS##_Exp((z - abs_x) * (z + abs_x) + R / S) / abs_x); \
} \
 \
t_f##BITS F##BITS##_Erf(t_f##BITS x) \
{ \
	t_f##BITS r,s,x2,y; \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	t_bool sign = (x < 0); /* F##BITS##_SIGN_BIT_MASK >> (BITS - 1); */ \
	if CCCERROR(F##BITS##_IsNaN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (F##BITS##_IsInf(x)) \
	{	/* erf(+-inf)=+-1 */ \
		return (F##BITS##_Sgn(x)); \
	} \
	if (abs_x < 0.84375) \
	{ \
		if (abs_x < 0x1p-56) \
		{	/* avoid underflow */ \
			return (0.125 * (8 * x + __data_erf_f##BITS.efx8 * x)); \
		} \
		x2 = x * x; \
		r = __polynomial_f##BITS(x2, __data_erf_f##BITS.pp, 4); \
		s = __polynomial_f##BITS(x2, __data_erf_f##BITS.qq, 5); \
		y = r / s; \
		return (x + x * y); \
	} \
	else if (abs_x < 6.) \
	{ \
		y = ((abs_x < 1.25) ? \
			F##BITS##_ErfC1(abs_x) : \
			F##BITS##_ErfC2(abs_x)); \
	} \
	else \
	{ \
		y = TINY; \
	} \
	y = (1 - y); \
	return (sign ? -y : y); \
} \
 \
t_f##BITS F##BITS##_ErfC(t_f##BITS x) \
{ \
	t_f##BITS r,s,x2,y; \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	t_bool sign = (x < 0); /* F##BITS##_SIGN_BIT_MASK >> (BITS - 1); */ \
	if CCCERROR(F##BITS##_IsNaN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (F##BITS##_IsInf(x)) \
	{ \
		return (1 - F##BITS##_Sgn(x)); \
	} \
	if (abs_x < 0.84375) \
	{ \
		if (abs_x < 0x1p-56) \
		{ \
			return (1.0 - x); \
		} \
		x2 = x * x; \
		r = __polynomial_f##BITS(x2, __data_erf_f##BITS.pp, 4); \
		s = __polynomial_f##BITS(x2, __data_erf_f##BITS.qq, 5); \
		y = r / s; \
		if (x < 0.25) \
		{ \
			return (1.0 - (x + x * y)); \
		} \
		return (0.5 - (x - 0.5 + x * y)); \
	} \
	else if (abs_x < 28.) \
	{ \
		y = (abs_x < 1.25) ? \
			F##BITS##_ErfC1(abs_x) : \
			F##BITS##_ErfC2(abs_x); \
	} \
	else \
	{ \
		y = (sign ? TINY : (TINY * TINY)); \
	} \
	return (sign ? (2 - y) : y); \
} \



#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_ERF(16, 0x1p-14f, 8)
#endif
DEFINEFUNC_FLOAT_ERF(32, 0x1p-120f, 13)

DEFINEFUNC_FLOAT_ERF(64, 0x1p-1022, 32)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ERF(80, 0x1p-16382L, 40)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ERF(128, 0x1p-16382L, 72)
#endif

#endif

#if 0

#undef isinf
#undef isnan
#include <math.h>

static
float erfc1(float x)
{
	t_f32 s,P,Q;

	s = F32_Abs(x) - 1;
	P = 
		__data_erf_f32.pa[0]+s*(
		__data_erf_f32.pa[1]+s*(
		__data_erf_f32.pa[2]+s*(
		__data_erf_f32.pa[3]+s*(
		__data_erf_f32.pa[4]+s*(
		__data_erf_f32.pa[5]+s*
		__data_erf_f32.pa[6])))));
	Q = 1+s*(
		__data_erf_f32.qa[1]+s*(
		__data_erf_f32.qa[2]+s*(
		__data_erf_f32.qa[3]+s*(
		__data_erf_f32.qa[4]+s*(
		__data_erf_f32.qa[5]+s*
		__data_erf_f32.qa[6])))));
	return 1 - 
		__data_erf_f32.erx - P/Q;
}

static
float erfc2(uint32_t ix, float x)
{
	t_f32 s,R,S;
	float z;

	if (ix < 0x3fa00000)  /* |x| < 1.25 */
		return erfc1(x);

	x = F32_Abs(x);
	s = 1/(x*x);
	if (ix < 0x4036db6d) {   /* |x| < 1/0.35 */
		R = 
			__data_erf_f32.ra[0]+s*(
			__data_erf_f32.ra[1]+s*(
			__data_erf_f32.ra[2]+s*(
			__data_erf_f32.ra[3]+s*(
			__data_erf_f32.ra[4]+s*(
			__data_erf_f32.ra[5]+s*(
			__data_erf_f32.ra[6]+s*
			__data_erf_f32.ra[7]))))));
		S = 1.0f+s*(
			__data_erf_f32.sa[1]+s*(
			__data_erf_f32.sa[2]+s*(
			__data_erf_f32.sa[3]+s*(
			__data_erf_f32.sa[4]+s*(
			__data_erf_f32.sa[5]+s*(
			__data_erf_f32.sa[6]+s*(
			__data_erf_f32.sa[7]+s*
			__data_erf_f32.sa[8])))))));
	} else {                 /* |x| >= 1/0.35 */
		R = 
			__data_erf_f32.rb[0]+s*(
			__data_erf_f32.rb[1]+s*(
			__data_erf_f32.rb[2]+s*(
			__data_erf_f32.rb[3]+s*(
			__data_erf_f32.rb[4]+s*(
			__data_erf_f32.rb[5]+s*
			__data_erf_f32.rb[6])))));
		S = 1.0f+s*(
			__data_erf_f32.sb[1]+s*(
			__data_erf_f32.sb[2]+s*(
			__data_erf_f32.sb[3]+s*(
			__data_erf_f32.sb[4]+s*(
			__data_erf_f32.sb[5]+s*(
			__data_erf_f32.sb[6]+s*
			__data_erf_f32.sb[7]))))));
	}
	GET_F32_WORD(ix, x);
	SET_F32_WORD(z, ix&0xffffe000);
	return expf(-z*z - 0.5625f) * expf((z-x)*(z+x) + R/S)/x;
}
float F32_Erf(float x)
{
	float r,s,z,y;
	uint32_t ix;
	int sign;

	GET_F32_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix >= 0x7f800000) {
		/* erf(nan)=nan, erf(+-inf)=+-1 */
		return 1-2*sign + 1/x;
	}
	if (ix < 0x3f580000) {  /* |x| < 0.84375 */
		if (ix < 0x31800000) {  /* |x| < 2**-28 */
			/*avoid underflow */
			return 0.125f*(8*x + 
				__data_erf_f32.efx8*x);
		}
		z = x*x;
		r = 
			__data_erf_f32.pp[0]+z*(
			__data_erf_f32.pp[1]+z*(
			__data_erf_f32.pp[2]+z*(
			__data_erf_f32.pp[3]+z*
			__data_erf_f32.pp[4])));
		s = 1+z*(
			__data_erf_f32.qq[1]+z*(
			__data_erf_f32.qq[2]+z*(
			__data_erf_f32.qq[3]+z*(
			__data_erf_f32.qq[4]+z*
			__data_erf_f32.qq[5]))));
		y = r/s;
		return x + x*y;
	}
	if (ix < 0x40c00000)  /* |x| < 6 */
		y = 1 - erfc2(ix,x);
	else
		y = 1 - 0x1p-120f;
	return sign ? -y : y;
}
float F32_ErfC(float x)
{
	float r,s,z,y;
	uint32_t ix;
	int sign;

	GET_F32_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix >= 0x7f800000) {
		/* erfc(nan)=nan, erfc(+-inf)=0,2 */
		return 2*sign + 1/x;
	}

	if (ix < 0x3f580000) {  /* |x| < 0.84375 */
		if (ix < 0x23800000)  /* |x| < 2**-56 */
			return 1.0f - x;
		z = x*x;
		r = 
			__data_erf_f32.pp[0]+z*(
			__data_erf_f32.pp[1]+z*(
			__data_erf_f32.pp[2]+z*(
			__data_erf_f32.pp[3]+z*
			__data_erf_f32.pp[4])));
		s = 1.0f+z*(
			__data_erf_f32.qq[1]+z*(
			__data_erf_f32.qq[2]+z*(
			__data_erf_f32.qq[3]+z*(
			__data_erf_f32.qq[4]+z*
			__data_erf_f32.qq[5]))));
		y = r/s;
		if (sign || ix < 0x3e800000)  /* x < 1/4 */
			return 1.0f - (x+x*y);
		return 0.5f - (x - 0.5f + x*y);
	}
	if (ix < 0x41e00000) {  /* |x| < 28 */
		return sign ? 2 - erfc2(ix,x) : erfc2(ix,x);
	}
	return sign ? 2 - 0x1p-120f : 0x1p-120f*0x1p-120f;
}
#endif
