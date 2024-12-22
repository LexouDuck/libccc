
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH

#elif LIBCONFIG_USE_CCC_MATH

#else



float	__math_oflowf	(float x)	{ return (x); }
double	__math_oflow	(double x)	{ return (x); }

float	__math_uflowf	(float x)	{ return (x); }
double	__math_uflow	(double x)	{ return (x); }

float	__math_xflowf	(uint32_t sign, float y)	{ return (float)(/*fp_barrierf*/(sign ? -y : y) * y); }
double	__math_xflow	(uint32_t sign, double y)	{ return (double)(/*fp_barrier*/(sign ? -y : y) * y); }

float	__math_divzerof (uint32_t sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
double	__math_divzero  (uint32_t sign)	{ return /*fp_barrier*/(sign ? -1.0 : 1.0) / 0.0; }

float		__math_invalidf	(float       x)	{ return (x - x) / (x - x); }
double		__math_invalid	(double      x)	{ return (x - x) / (x - x); }
long double	__math_invalidl	(long double x)	{ return (x - x) / (x - x); }


#endif
