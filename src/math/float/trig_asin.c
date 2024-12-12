
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcSin, asin)
#else
// mixed approach: polynomial approximation + stepwise linear approx
#define DEFINEFUNC_FLOAT_ARCSIN(BITS) \
t_f##BITS	F##BITS##_ArcSin(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((x < -1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if CCCERROR((x > +1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	t_f##BITS abs_x = F##BITS##_Abs(x); \
	if (abs_x == 1.) \
		return (PI_HALF * SGN(x)); \
	t_f##BITS const correction = -0.0005; \
	t_f##BITS result = 0; \
	if (abs_x < 0.651609764) \
	{ \
		t_f##BITS power = x; \
		result += power * -1.0000000000;	power *= (x * x); \
		result += power * -0.0584000000;	power *= (x * x); \
		result += power * -0.6852000000;	power *= (x * x); \
		result += power * +1.1661600000;	power *= (x * x); \
		result += power * -0.9933563268; \
		return (-result); \
	} \
	if (abs_x < 0.92) \
	{ \
		t_f##BITS const term = abs_x - 0.85; \
		t_f##BITS power = term; \
		result = 1.0168; \
		result += power * 1.9164;	power *= term; \
		result += power * 2.7894;	power *= term; \
		result += power * 4.5131; \
	} \
	else if (abs_x < 0.9323076923076923)	result = (02.6537466126925790 * abs_x + -01.27336639846293750 + correction); \
	else if (abs_x < 0.9435897435897436)	result = (02.8866517417672997 * abs_x + -01.49050564187721560 + correction); \
	else if (abs_x < 0.9538461538461539)	result = (03.1672223729550377 * abs_x + -01.75524921181846600 + correction); \
	else if (abs_x < 0.9630769230769230)	result = (03.5114088569871450 * abs_x + -02.08355016581832200 + correction); \
	else if (abs_x < 0.9712820512820513)	result = (03.9432048093094780 * abs_x + -02.49940288297798400 + correction); \
	else if (abs_x < 0.9784615384615385)	result = (04.5004611357475275 * abs_x + -03.04065595081063300 + correction); \
	else if (abs_x < 0.9846153846153847)	result = (05.2466177344165230 * abs_x + -03.77074148427752660 + correction); \
	else if (abs_x < 0.9897435897435898)	result = (06.2968623133130330 * abs_x + -04.80482845426793800 + correction); \
	else if (abs_x < 0.9973333333333333)	result = (09.2624681237850730 * abs_x + -07.74001779488898100 + correction); \
	else if (abs_x < 0.9993333333333333)	result = (18.2645234110693050 * abs_x + -16.71806760140712500 + correction); \
	else if (abs_x < 0.9997777777777778)	result = (34.7279053082986500 * abs_x + -33.17047391070498000 + correction); \
	else if (abs_x < 1.0000000000000000)	result = (94.8700867138177800 * abs_x + -93.29929038702288000 + correction); \
	return (x < 0 ? -result : +result); \
} \

// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#if 0
	t_f##BITS result = 0;
	t_f##BITS power = x;
	result += power * -1.0000000000;	power *= (x * x);
	result += power * -0.0584000000;	power *= (x * x);
	result += power * -0.6852000000;	power *= (x * x);
	result += power * +1.1661600000;	power *= (x * x);
	result += power * -0.9933563268;
	return (-result);
#endif

// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((0.8047926 * x * x + 0.766) * x); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCSIN(32)
DEFINEFUNC_FLOAT_ARCSIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCSIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCSIN(128)
#endif

#endif
