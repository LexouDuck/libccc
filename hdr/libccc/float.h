/*============================================================================*\
||                                            ______________________________  ||
||  libccc/float.h                           |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_FLOAT_H
#define __LIBCCC_FLOAT_H
/*!@group{libccc_float,14,libccc/float.h}
**
**	This header defines the floating-point number primitive types and functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**	@isostd{C,https://en.cppreference.com/w/c/language/floating_constant}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/fenv}
**	- https://en.wikipedia.org/wiki/IEEE_754
*/

// TODO subnormal float util functions/macros ?

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_FLOAT_T
#define __LIBCCC_FLOAT_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

#if LIBCONFIG_USE_FLOAT16
//!@doc Primitive type: 16-bit 'half precision' IEEE-754 floating-point numbers (only certain platforms)
/*!
**	@isostd{C,https://en.cppreference.com/w/cpp/types/floating-point}
**
**	Learn more: https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 5 exponent bits
**	- 10 mantissa bits
*/
//!@{
typedef _Float16	t_f16;
TYPEDEF_ALIAS(		t_f16,	FLOAT_16,	PRIMITIVE)
//!@}
#elif (LIBCONFIG_FLOAT_BITS == 16)
#error "Cannot set default float to 16-bit half-precision, unavailable on this platform"
#endif

//!@doc Primitive type: 32-bit 'single precision' IEEE-754 floating-point numbers
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**
**	Learn more: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 8 exponent bits
**	- 23 mantissa bits
*/
//!@{
typedef float	t_f32;
TYPEDEF_ALIAS(	t_f32,	FLOAT_32,	PRIMITIVE)
//!@}

//!@doc Primitive type: 64-bit 'double precision' IEEE-754 floating-point numbers
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**
**	Learn more: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 11 exponent bits
**	- 52 mantissa bits
*/
//!@{
typedef double	t_f64;
TYPEDEF_ALIAS(	t_f64,	FLOAT_64,	PRIMITIVE)
//!@}

#if LIBCONFIG_USE_FLOAT80
//!@doc Primitive type: 80-bit 'extended precision' x86 floating-point numbers (only certain platforms)
/*!
**	@isostd{C,https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html}
**
**	Learn more: https://en.wikipedia.org/wiki/Extended_precision
**
**	NOTE: There are two major implementations of extended-precision floats:
**	-	80-bit 'extended precision' x86 floating-point numbers
**	-	96-bit 'extended precision' 68881 floating-point numbers
**	The 96-bit variant has a different `sizeof()`, as its name shows, but it
**	does not have any more precision: those 16 added bits are only there
**	for padding, for memory alignment purposes.
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 15 exponent bits
**	- [16 padding bits, if 96-bit]
**	- 1 integer bit
**	- 63 mantissa bits
*/
//!@{
typedef _Float80	t_f80;
TYPEDEF_ALIAS(		t_f80,	FLOAT_80,	PRIMITIVE)
//!@}
#elif (LIBCONFIG_FLOAT_BITS == 80)
#error "Cannot set default float to 80-bit extended-precision, unavailable on this platform"
#endif

#if LIBCONFIG_USE_FLOAT128
//!@doc Primitive type: 128-bit 'quadruple precision' IEEE-754 floating-point numbers (only certain platforms)
/*!
**	@isostd{C,https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html}
**
**	Learn more: https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 15 exponent bits
**	- 112 mantissa bits
*/
//!@{
typedef _Float128	t_f128;
TYPEDEF_ALIAS(		t_f128,	FLOAT_128,	PRIMITIVE)
//!@}
#elif (LIBCONFIG_FLOAT_BITS == 128)
#error "Cannot set default float to 128-bit quadruple-precision, unavailable on this platform"
#endif



//! The actual underlying type for the `t_float` configurable-size type
#define FLOAT_T		CONCAT(t_f,LIBCONFIG_FLOAT_BITS)
//! The actual underlying type for the `t_float` configurable-size type, in uppercase
#define FLOAT_TYPE	CONCAT(F,LIBCONFIG_FLOAT_BITS)

//!@doc The configurable-size floating-point number primitive type.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**
**	A floating-point number is a number which is encoded as 3 distinct parts:
**	- A sign bit (typically the rightmost bit)
**	- An exponent (typically a binary power, ie: 2^number)
**	- A mantissa/significand, which stores the most signficant part of this number
**	So, a floating point number is very much like a number in scientific notation.
**	Also, note that, the way floats are encoded with the IEEE-754 specification,
**	there are as many respresentable floating-point numbers between `0.` and `+1.`,
**	as there are between `+1.` and `+INFINITY`. The higher you go along the real numbers,
**	the more imprecise your floating-point calculations will become.
**	This type can express a number between negative #INFINITY and positive #INFINITY.
**
**	@see
**	- #t_f32
**	- #t_f64
**	- #t_f80
**	- #t_f128
*/
//!@{
typedef CONCAT(t_f,LIBCONFIG_FLOAT_BITS)	t_float;
TYPEDEF_ALIAS(t_float, FLOAT, PRIMITIVE)
//!@}



#if(LIBCONFIG_FLOAT_BITS != 32 && \
	LIBCONFIG_FLOAT_BITS != 64 && \
	LIBCONFIG_FLOAT_BITS != 80 && \
	LIBCONFIG_FLOAT_BITS != 96 && \
	LIBCONFIG_FLOAT_BITS != 128)
	#error "LIBCONFIG_FLOAT_BITS must be equal to one of: 32, 64, 80, 96, 128"
#endif



#undef FLOAT_ERROR

#if (LIBCONFIG_FIXED_NAN == 0)

	#define F32_ERROR	((t_f32)  (0.))
	#define F64_ERROR	((t_f64)  (0.))
	#define F80_ERROR	((t_f80)  (0.))
	#define F128_ERROR	((t_f128) (0.))
	#define FLOAT_ERROR	((t_float)(0.))

#else

	#define F32_ERROR	((t_f32)  (0. / 0.))
	#define F64_ERROR	((t_f64)  (0. / 0.))
	#define F80_ERROR	((t_f80)  (0. / 0.))
	#define F128_ERROR	((t_f128) (0. / 0.))
	#define FLOAT_ERROR	((t_float)(0. / 0.))

#endif



//!@doc The floating-point "not a number" value.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/NAN}
*/
//!@{
#ifndef NAN
#define NAN			(0. / 0.)
#endif
#ifndef NOTANUMBER
#define NOTANUMBER	NAN
#endif
//!@}

//!@doc The floating-point infinity value (use `-INF` for negative)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/INFINITY}
*/
//!@{
#ifndef INF
#define INF			(1. / 0.)
#endif
#ifndef INFINITY
#define INFINITY	INF
#endif
//!@}



//! TODO add HUGE and TINY min/max value macros
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/HUGE_VAL}
**	@isostd{C,https://en.cppreference.com/w/c/types/limits#Limits_of_floating_point_types}
*/



//! This macro sets the rounding behavior for floating-point number operations.
/*!
**	Rounding behavior for floating-point types. Possible values are:
**	`-1`	undetermined
**	 `0`	towards zero
**	 `1`	to nearest
**	 `2`	toward positive infinity
**	 `3`	toward negative infinity
*/
#ifndef FLT_ROUNDS
#define FLT_ROUNDS	1
#endif

//! This macro sets the floating-point expression evaluation method (i.e. how floats are operated upon).
/*!
**	The floating-point evaluation method. Possible values are:
**	`-1`	indeterminate
**	 `0`	evaluate all operations and constants, whose semantic type has at most the range and precision of `float`, to the range and precision of `float`;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `1`	evaluate all operations and constants, whose semantic type has at most the range and precision of `double`, to the range and precision of `double`;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `2`	evaluate all operations and constants, whose semantic type has at most the range and precision of `long double`, to the range and precision of `long double`;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `N`	where `_FloatN`  is a supported interchange floating type:
**	    	evaluate all operations and constants, whose semantic type has at most the range and precision of the `_FloatN` type, to the range and precision of the `_FloatN` type;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `N + 1`, where `_FloatNx` is a supported extended floating type:
**	    	evaluate operations and constants, whose semantic type has at most the range and precision of the `_FloatNx` type, to the range and precision of the `_FloatNx` type;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
*/
#ifndef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD	1
#endif
/*
#if FLT_EVAL_METHOD == 0
#define EPS FLT_EPSILON
#elif FLT_EVAL_METHOD == 1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD == 2
#define EPS LDBL_EPSILON
#else
#error "FLT_EVAL_METHOD has invalid value: "FLT_EVAL_METHOD
#endif
*/



// TODO instead of using FLT_MIN/FLT_MAX/FLT_EPSILON, calculate them manually (in a cross-platform manner)

//!@doc 16-bit float bitwise constants
/*!
**	IEEE 754 16-bit floating point "half precision" bitwise macros
*/
//!@{
#define F16_SIGN_BIT_MASK	(0x8000)				//!< A 16-bit floating-point number's sign bit (bitmask)
#define F16_EXPONENT_BIAS	(15)					//!< A 16-bit floating-point number's exponent bias offset
#define F16_EXPONENT_MASK	(0x7C00)				//!< A 16-bit floating-point number's exponent bit region (bitmask)
#define F16_EXPONENT_ZERO	(0x3C00)				//!< A 16-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F16_EXPONENT_BITS	(5)						//!< A 16-bit floating-point number's amount of bits dedicated to the exponent
#define F16_MANTISSA_MASK	(0x03FF)				//!< A 16-bit floating-point number's mantissa bit region (bitmask)
#define F16_MANTISSA_SIGNED	(0x83FF)				//!< A 16-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F16_MANTISSA_BITS	(10)					//!< A 16-bit floating-point number's amount of bits dedicated to the mantissa
#define F16_INIT_VALUE		(0x1.p-10)				//!< A 16-bit floating-point number's value if all bits are zero
#define F16_EPSILON			(0x1.p-10)				//!< Difference between 1 and the least value greater than 1 that is representable.
#define F16_MIN_INT			(0x2.p-11)				//!< A 16-bit floating-point's minimum representable integer value.
#define F16_MAX_INT			(0x2.p+11)				//!< A 16-bit floating-point's maximum representable integer value.
#define F16_MIN_VAL			(FLT16_MIN)				//!< A 16-bit floating-point's minimum representable positive normal value.
#define F16_MAX_VAL			(FLT16_MAX)				//!< A 16-bit floating-point's maximum representable positive finite value.
#define F16_MIN				(-INF)					//!< A 16-bit floating-point's minimum value (-infinity)
#define F16_MAX				(+INF)					//!< A 16-bit floating-point's maximum value (+infinity)
//!@}

//!@doc 32-bit float bitwise constants
/*!
**	IEEE 754 32-bit floating point "single precision" bitwise macros
*/
//!@{
#define F32_SIGN_BIT_MASK	(0x80000000)			//!< A 32-bit floating-point number's sign bit (bitmask)
#define F32_EXPONENT_BIAS	(127)					//!< A 32-bit floating-point number's exponent bias offset
#define F32_EXPONENT_MASK	(0x7F800000)			//!< A 32-bit floating-point number's exponent bit region (bitmask)
#define F32_EXPONENT_ZERO	(0x3F800000)			//!< A 32-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F32_EXPONENT_BITS	(8)						//!< A 32-bit floating-point number's amount of bits dedicated to the exponent
#define F32_MANTISSA_MASK	(0x007FFFFF)			//!< A 32-bit floating-point number's mantissa bit region (bitmask)
#define F32_MANTISSA_SIGNED	(0x807FFFFF)			//!< A 32-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F32_MANTISSA_BITS	(23)					//!< A 32-bit floating-point number's amount of bits dedicated to the mantissa
#define F32_INIT_VALUE		(0x1.p-23)				//!< A 32-bit floating-point number's value if all bits are zero
#define F32_EPSILON			(0x1.p-23)				//!< Difference between 1 and the least value greater than 1 that is representable.
#define F32_MIN_INT			(0x2.p-24)				//!< A 32-bit floating-point's minimum representable integer value.
#define F32_MAX_INT			(0x2.p+24)				//!< A 32-bit floating-point's maximum representable integer value.
#define F32_MIN_VAL			(FLT_MIN)				//!< A 32-bit floating-point's minimum representable positive normal value.
#define F32_MAX_VAL			(FLT_MAX)				//!< A 32-bit floating-point's maximum representable positive finite value.
#define F32_MIN				(-INF)					//!< A 32-bit floating-point's minimum value (-infinity)
#define F32_MAX				(+INF)					//!< A 32-bit floating-point's maximum value (+infinity)
//!@}

//!@doc 64-bit float bitwise constants
/*!
**	IEEE 754 64-bit floating point "double precision" bitwise macros
*/
//!@{
#define F64_SIGN_BIT_MASK	(0x8000000000000000)	//!< A 64-bit floating-point number's sign bit (bitmask)
#define F64_EXPONENT_BIAS	(1023)					//!< A 64-bit floating-point number's exponent bias offset
#define F64_EXPONENT_MASK	(0x7FF0000000000000)	//!< A 64-bit floating-point number's exponent bit region (bitmask)
#define F64_EXPONENT_ZERO	(0x3FF0000000000000)	//!< A 64-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F64_EXPONENT_BITS	(11)					//!< A 64-bit floating-point number's amount of bits dedicated to the exponent
#define F64_MANTISSA_MASK	(0x000FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa bit region (bitmask)
#define F64_MANTISSA_SIGNED	(0x800FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F64_MANTISSA_BITS	(52)					//!< A 64-bit floating-point number's amount of bits dedicated to the mantissa
#define F64_INIT_VALUE		(0x1.p-52)				//!< A 64-bit floating-point number's value if all bits are zero
#define F64_EPSILON			(0x1.p-52)				//!< Difference between 1 and the least value greater than 1 that is representable.
#define F64_MIN_INT			(0x2.p-53)				//!< A 64-bit floating-point's minimum representable integer value.
#define F64_MAX_INT			(0x2.p+53)				//!< A 64-bit floating-point's maximum representable integer value.
#define F64_MIN_VAL			(DBL_MIN)				//!< A 64-bit floating-point's minimum representable positive normal value.
#define F64_MAX_VAL			(DBL_MAX)				//!< A 64-bit floating-point's maximum representable positive finite value.
#define F64_MIN				(-INF)					//!< A 64-bit floating-point's minimum value (-infinity)
#define F64_MAX				(+INF)					//!< A 64-bit floating-point's maximum value (+infinity)
//!@}

//!@doc 80-bit float bitwise constants
/*!
**	x86 80-bit floating point "extended precision" bitwise macros
*/
//!@{
#define F80_SIGN_BIT_MASK	(0x80000000000000000000l)	//!< A 80-bit floating-point number's sign bit (bitmask)
#define F80_EXPONENT_BIAS	(16383)						//!< A 80-bit floating-point number's exponent bias offset
#define F80_EXPONENT_MASK	(0x7FFF0000000000000000l)	//!< A 80-bit floating-point number's exponent bit region (bitmask)
#define F80_EXPONENT_ZERO	(0x3FFF0000000000000000l)	//!< A 80-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F80_EXPONENT_BITS	(15)						//!< A 80-bit floating-point number's amount of bits dedicated to the exponent
#define F80_MANTISSA_MASK	(0x0000FFFFFFFFFFFFFFFFl)	//!< A 80-bit floating-point number's mantissa bit region (bitmask)
#define F80_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFl)	//!< A 80-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F80_MANTISSA_BITS	(63)						//!< A 80-bit floating-point number's amount of bits dedicated to the mantissa
#define F80_INIT_VALUE		(0x1.p-63)					//!< A 80-bit floating-point number's value if all bits are zero
#define F80_EPSILON			(0x1.p-63)					//!< Difference between 1 and the least value greater than 1 that is representable.
#define F80_MIN_INT			(0x2.p-64)					//!< A 80-bit floating-point's minimum representable integer value.
#define F80_MAX_INT			(0x2.p+64)					//!< A 80-bit floating-point's maximum representable integer value.
#define F80_MIN_VAL			(LDBL_MIN)					//!< A 80-bit floating-point's minimum representable positive normal value.
#define F80_MAX_VAL			(LDBL_MAX)					//!< A 80-bit floating-point's maximum representable positive finite value.
#define F80_MIN				(-INF)						//!< A 80-bit floating-point's minimum value (-infinity)
#define F80_MAX				(+INF)						//!< A 80-bit floating-point's maximum value (+infinity)
//!@}

//!@doc 128-bit float bitwise constants
/*!
**	IEEE 754 128-bit floating point "quadruple precision" bitwise macros
*/
//!@{
#define F128_SIGN_BIT_MASK		(0x80000000000000000000000000000000l)	//!< A 128-bit floating-point number's sign bit (bitmask)
#define F128_EXPONENT_BIAS		(16383)									//!< A 128-bit floating-point number's exponent bias offset
#define F128_EXPONENT_MASK		(0x7FFF0000000000000000000000000000l)	//!< A 128-bit floating-point number's exponent bit region (bitmask)
#define F128_EXPONENT_ZERO		(0x3FFF0000000000000000000000000000l)	//!< A 128-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F128_EXPONENT_BITS		(15)									//!< A 128-bit floating-point number's amount of bits dedicated to the exponent
#define F128_MANTISSA_MASK		(0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFl)	//!< A 128-bit floating-point number's mantissa bit region (bitmask)
#define F128_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFl)	//!< A 128-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F128_MANTISSA_BITS		(112)									//!< A 128-bit floating-point number's amount of bits dedicated to the mantissa
#define F128_INIT_VALUE			(0x1.p-112)								//!< A 128-bit floating-point number's value if all bits are zero
#define F128_EPSILON			(0x1.p-112)								//!< Difference between 1 and the least value greater than 1 that is representable.
#define F128_MIN_INT			(0x2.p-113)								//!< A 128-bit floating-point's minimum representable integer value.
#define F128_MAX_INT			(0x2.p+113)								//!< A 128-bit floating-point's maximum representable integer value.
#define F128_MIN_VAL			(LDBL_MIN)								//!< A 128-bit floating-point's minimum representable positive normal value.
#define F128_MAX_VAL			(LDBL_MAX)								//!< A 128-bit floating-point's maximum representable positive finite value.
#define F128_MIN				(-INF)									//!< A 128-bit floating-point's minimum value (-infinity)
#define F128_MAX				(+INF)									//!< A 128-bit floating-point's maximum value (+infinity)
//!@}



//!@doc Float bitwise constants
/*!
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_, etc) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/
//!@{
#define FLOAT_SIGNED			CONCAT(FLOAT_TYPE,_SIGNED)
#define FLOAT_EXPONENT_BIAS		CONCAT(FLOAT_TYPE,_EXPONENT_BIAS)
#define FLOAT_EXPONENT			CONCAT(FLOAT_TYPE,_EXPONENT)
#define FLOAT_EXPONENT_ZERO		CONCAT(FLOAT_TYPE,_EXPONENT_ZERO)
#define FLOAT_EXPONENT_BITS		CONCAT(FLOAT_TYPE,_EXPONENT_BITS)
#define FLOAT_MANTISSA			CONCAT(FLOAT_TYPE,_MANTISSA)
#define FLOAT_MANTISSA_SIGNED	CONCAT(FLOAT_TYPE,_MANTISSA_SIGNED)
#define FLOAT_MANTISSA_BITS		CONCAT(FLOAT_TYPE,_MANTISSA_BITS)
#define FLOAT_INIT_VALUE		CONCAT(FLOAT_TYPE,_INIT_VALUE)
#define FLOAT_EPSILON			CONCAT(FLOAT_TYPE,_EPSILON)
#define FLOAT_MIN_INT			CONCAT(FLOAT_TYPE,_MIN_INT)
#define FLOAT_MAX_INT			CONCAT(FLOAT_TYPE,_MAX_INT)
#define FLOAT_MIN_VAL			CONCAT(FLOAT_TYPE,_MIN_VAL)
#define FLOAT_MAX_VAL			CONCAT(FLOAT_TYPE,_MAX_VAL)
#define FLOAT_MIN				CONCAT(FLOAT_TYPE,_MIN)
#define FLOAT_MAX				CONCAT(FLOAT_TYPE,_MAX)
//!@}



//! If `(abs(value) >= FLOAT_THRESHOLD_HUGE)`, Float_ToString() functions will write in scientific notation rather than decimal notation
#define FLOAT_THRESHOLD_HUGE	(1e+9)
//! If `(abs(value) <= FLOAT_THRESHOLD_TINY)`, Float_ToString() functions will write in scientific notation rather than decimal notation
#define FLOAT_THRESHOLD_TINY	(1e-9)



// TODO add IS_NORMAL() and IS_SUBNORMAL()



//! Used to force evaluation of a certain operation, without letting the compielr optimize it away
#define FORCE_EVAL(x) \
	do { \
		if (sizeof(x) == 0) {} \
		else if (sizeof(x) == sizeof(float))       { volatile float       __x;	__x = (x); } \
		else if (sizeof(x) == sizeof(double))      { volatile double      __x;	__x = (x); } \
		else if (sizeof(x) == sizeof(long double)) { volatile long double __x;	__x = (x); } \
		else {} \
	} while(0) \



//! Union type to allow direct bitwise manipulation of floating-point values
/*!
**	This union type is used in several math function implementations, to
**	manipulate float bits directly, by using bitwise operators with int types.
*/
//!@{
#if LIBCONFIG_USE_FLOAT16
typedef union cast_f16
{
	t_f16	as_f;
	t_u16	as_u;
	t_s16	as_s;
	struct { t_u8 hi; t_u8 lo; }	split;
}	u_cast_f16;
#endif

typedef union cast_f32
{
	t_f32	as_f;
	t_u32	as_u;
	t_s32	as_s;
	struct { t_u16 hi; t_u16 lo; }	split;
}	u_cast_f32;

typedef union cast_f64
{
	t_f64	as_f;
	t_u64	as_u;
	t_s64	as_s;
	struct { t_u32 hi; t_u32 lo; }	split;
}	u_cast_f64;

#if LIBCONFIG_USE_FLOAT80
typedef union cast_f80
{
	t_f80	as_f;
#if LIBCONFIG_USE_INT128
	t_u128	as_u;
	t_s128	as_s;
#else
	t_u64[2]	as_u;
	t_s64[2]	as_s;
#endif
	struct { t_u64 hi; t_u64 lo; }	split;
}	u_cast_f80;
#endif

#if LIBCONFIG_USE_FLOAT128
typedef union cast_f128
{
	t_f128	as_f;
#if LIBCONFIG_USE_INT128
	t_u128	as_u;
	t_s128	as_s;
#else
	t_u64[2]	as_u;
	t_s64[2]	as_s;
#endif
	struct { t_u64 hi; t_u64 lo; }	split;
}	u_cast_f128;
#endif

typedef union cast_float
{
	t_float	as_f;
#if (LIBCONFIG_FLOAT_BITS == 32)
	t_u32	as_u;
	t_s32	as_s;
#elif (LIBCONFIG_FLOAT_BITS == 64)
	t_u64	as_u;
	t_s64	as_s;
#else
	t_u128	as_u;
	t_s128	as_s;
#endif
}	u_cast_float;
//!@}



//f16
#if LIBCONFIG_USE_FLOAT16
#define AS_U16(f)	((union cast_f16){ .as_f = f }).as_u
#define AS_F16(i)	((union cast_f16){ .as_u = i }).as_f
#else
#define AS_U16(f)	((t_u16)0)
#define AS_F16(i)	((t_f16)0)
#endif
//f32
#define AS_U32(f)	((union cast_f32){ .as_f = f }).as_u
#define AS_F32(i)	((union cast_f32){ .as_u = i }).as_f
//f64
#define AS_U64(f)	((union cast_f64){ .as_f = f }).as_u
#define AS_F64(i)	((union cast_f64){ .as_u = i }).as_f
//f80
#if LIBCONFIG_USE_FLOAT80
#define AS_U80(f)	((union cast_f80){ .as_f = f }).as_u
#define AS_F80(i)	((union cast_f80){ .as_u = i }).as_f
#else
#define AS_U80(f)	((t_u128)0)
#define AS_F80(i)	((t_f128)0)
#endif
//f128
#if LIBCONFIG_USE_FLOAT128
#define AS_U128(f)	((union cast_f128){ .as_f = f }).as_u
#define AS_F128(i)	((union cast_f128){ .as_u = i }).as_f
#else
#define AS_U128(f)	((t_u128)0)
#define AS_F128(i)	((t_f128)0)
#endif



#endif
#ifndef __LIBCCC_FLOAT_F
#define __LIBCCC_FLOAT_F

/*============================================================================*\
||                      Floating-point conversion functions                   ||
\*============================================================================*/

//!@doc A smart constructor: calls the appropriate conversion function from the given argument type
//!@{
#define DEFINEFUNC_Float(X, FUNCTYPE) \
	_Generic((X), \
		t_u8:	 FUNCTYPE##_FromU8, \
		t_u16:	 FUNCTYPE##_FromU16, \
		t_u32:	 FUNCTYPE##_FromU32, \
		t_u64:	 FUNCTYPE##_FromU64, \
		t_u128:	 FUNCTYPE##_FromU128, \
		t_uint:  FUNCTYPE##_FromUInt, \
		t_s8:	 FUNCTYPE##_FromS8, \
		t_s16:	 FUNCTYPE##_FromS16, \
		t_s32:	 FUNCTYPE##_FromS32, \
		t_s64:	 FUNCTYPE##_FromS64, \
		t_s128:	 FUNCTYPE##_FromS128, \
		t_sint:  FUNCTYPE##_FromSInt, \
		t_q8:	 FUNCTYPE##_FromQ8, \
		t_q16:	 FUNCTYPE##_FromQ16, \
		t_q32:	 FUNCTYPE##_FromQ32, \
		t_q64:	 FUNCTYPE##_FromQ64, \
		t_q128:	 FUNCTYPE##_FromQ128, \
		t_fixed: FUNCTYPE##_FromFixed, \
		t_f16:	 FUNCTYPE##_FromF16, \
		t_f32:	 FUNCTYPE##_FromF32, \
		t_f64:	 FUNCTYPE##_FromF64, \
		t_f80:	 FUNCTYPE##_FromF80, \
		t_f128:	 FUNCTYPE##_FromF128, \
		t_float: FUNCTYPE##_FromFloat, \
	)(X)

#define Float(X)	DEFINEFUNC_Float(X, Float)
#define F16(X)		DEFINEFUNC_Float(X, F16)
#define F32(X)		DEFINEFUNC_Float(X, F32)
#define F64(X)		DEFINEFUNC_Float(X, F64)
#if LIBCONFIG_USE_FLOAT80
#define F80(X)		DEFINEFUNC_Float(X, F80)
#endif
#if LIBCONFIG_USE_FLOAT128
#define F128(X)		DEFINEFUNC_Float(X, F128)
#endif

#define c_float(X)	Float(X)
#define c_f16(X)	F16(X)
#define c_f32(X)	F32(X)
#define c_f64(X)	F64(X)
#if LIBCONFIG_USE_FLOAT80
#define c_f80(X)	F80(X)
#endif
#if LIBCONFIG_USE_FLOAT128
#define c_f128(X)	F128(X)
#endif
//!@}



//!@doc Returns the nearest floating-point value from the given unsigned integer `number`
/*!
**	TODO document this
*/
//!@{
#define					Float_FromUInt	CONCAT(FLOAT_TYPE,CONCAT(_From,UINT_TYPE))
#define c_utof			Float_FromUInt
#define					Float_FromU8	CONCAT(FLOAT_TYPE,_FromU8)
#define c_u8tof			Float_FromU8
#define					Float_FromU16	CONCAT(FLOAT_TYPE,_FromU16)
#define c_u16tof		Float_FromU16
#define					Float_FromU32	CONCAT(FLOAT_TYPE,_FromU32)
#define c_u32tof		Float_FromU32
#define					Float_FromU64	CONCAT(FLOAT_TYPE,_FromU64)
#define c_u64tof		Float_FromU64
#if LIBCONFIG_USE_INT128
#define					Float_FromU128	CONCAT(FLOAT_TYPE,_FromU128)
#define c_u128tof		Float_FromU128
#endif

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromU8(t_u8 number);
#define c_u8tof16		F16_FromU8
t_f16					F16_FromU16(t_u16 number);
#define c_u16tof16		F16_FromU16
t_f16					F16_FromU32(t_u32 number);
#define c_u32tof16		F16_FromU32
t_f16					F16_FromU64(t_u64 number);
#define c_u64tof16		F16_FromU64
#if LIBCONFIG_USE_INT128
t_f16					F16_FromU128(t_u128 number);
#define c_u128tof16		F16_FromU128
#endif
#endif

t_f32					F32_FromU8(t_u8 number);
#define c_u8tof32		F32_FromU8
t_f32					F32_FromU16(t_u16 number);
#define c_u16tof32		F32_FromU16
t_f32					F32_FromU32(t_u32 number);
#define c_u32tof32		F32_FromU32
t_f32					F32_FromU64(t_u64 number);
#define c_u64tof32		F32_FromU64
#if LIBCONFIG_USE_INT128
t_f32					F32_FromU128(t_u128 number);
#define c_u128tof32		F32_FromU128
#endif

t_f64					F64_FromU8(t_u8 number);
#define c_u8tof64		F64_FromU8
t_f64					F64_FromU16(t_u16 number);
#define c_u16tof64		F64_FromU16
t_f64					F64_FromU32(t_u32 number);
#define c_u32tof64		F64_FromU32
t_f64					F64_FromU64(t_u64 number);
#define c_u64tof64		F64_FromU64
#if LIBCONFIG_USE_INT128
t_f64					F64_FromU128(t_u128 number);
#define c_u128tof64		F64_FromU128
#endif

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromU8(t_u8 number);
#define c_u8tof80		F80_FromU8
t_f80					F80_FromU16(t_u16 number);
#define c_u16tof80		F80_FromU16
t_f80					F80_FromU32(t_u32 number);
#define c_u32tof80		F80_FromU32
t_f80					F80_FromU64(t_u64 number);
#define c_u64tof80		F80_FromU64
#if LIBCONFIG_USE_INT128
t_f80					F80_FromU128(t_u128 number);
#define c_u128tof80		F80_FromU128
#endif
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromU8(t_u8 number);
#define c_u8tof128		F128_FromU8
t_f128					F128_FromU16(t_u16 number);
#define c_u16tof128		F128_FromU16
t_f128					F128_FromU32(t_u32 number);
#define c_u32tof128		F128_FromU32
t_f128					F128_FromU64(t_u64 number);
#define c_u64tof128		F128_FromU64
#if LIBCONFIG_USE_INT128
t_f128					F128_FromU128(t_u128 number);
#define c_u128tof128	F128_FromU128
#endif
#endif
//!@}

//!@doc Returns the nearest floating-point value from the given signed integer `number`
/*!
**	TODO document this
*/
//!@{
#define					Float_FromSInt	CONCAT(FLOAT_TYPE,CONCAT(_From,SINT_TYPE))
#define c_stof			Float_FromSInt
#define					Float_FromS8	CONCAT(FLOAT_TYPE,_FromS8)
#define c_s8tof			Float_FromS8
#define					Float_FromS16	CONCAT(FLOAT_TYPE,_FromS16)
#define c_s16tof		Float_FromS16
#define					Float_FromS32	CONCAT(FLOAT_TYPE,_FromS32)
#define c_s32tof		Float_FromS32
#define					Float_FromS64	CONCAT(FLOAT_TYPE,_FromS64)
#define c_s64tof		Float_FromS64
#if LIBCONFIG_USE_INT128
#define					Float_FromS128	CONCAT(FLOAT_TYPE,_FromS128)
#define c_s128tof		Float_FromS128
#endif

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromS8(t_s8 number);
#define c_s8tof16		F16_FromS8
t_f16					F16_FromS16(t_s16 number);
#define c_s16tof16		F16_FromS16
t_f16					F16_FromS32(t_s32 number);
#define c_s32tof16		F16_FromS32
t_f16					F16_FromS64(t_s64 number);
#define c_s64tof16		F16_FromS64
#if LIBCONFIG_USE_INT128
t_f16					F16_FromS128(t_s128 number);
#define c_s128tof16		F16_FromS128
#endif
#endif

t_f32					F32_FromS8(t_s8 number);
#define c_s8tof32		F32_FromS8
t_f32					F32_FromS16(t_s16 number);
#define c_s16tof32		F32_FromS16
t_f32					F32_FromS32(t_s32 number);
#define c_s32tof32		F32_FromS32
t_f32					F32_FromS64(t_s64 number);
#define c_s64tof32		F32_FromS64
#if LIBCONFIG_USE_INT128
t_f32					F32_FromS128(t_s128 number);
#define c_s128tof32		F32_FromS128
#endif

t_f64					F64_FromS8(t_s8 number);
#define c_s8tof64		F64_FromS8
t_f64					F64_FromS16(t_s16 number);
#define c_s16tof64		F64_FromS16
t_f64					F64_FromS32(t_s32 number);
#define c_s32tof64		F64_FromS32
t_f64					F64_FromS64(t_s64 number);
#define c_s64tof64		F64_FromS64
#if LIBCONFIG_USE_INT128
t_f64					F64_FromS128(t_s128 number);
#define c_s128tof64		F64_FromS128
#endif

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromS8(t_s8 number);
#define c_s8tof80		F80_FromS8
t_f80					F80_FromS16(t_s16 number);
#define c_s16tof80		F80_FromS16
t_f80					F80_FromS32(t_s32 number);
#define c_s32tof80		F80_FromS32
t_f80					F80_FromS64(t_s64 number);
#define c_s64tof80		F80_FromS64
#if LIBCONFIG_USE_INT128
t_f80					F80_FromS128(t_s128 number);
#define c_s128tof80		F80_FromS128
#endif
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromS8(t_s8 number);
#define c_s8tof128		F128_FromS8
t_f128					F128_FromS16(t_s16 number);
#define c_s16tof128		F128_FromS16
t_f128					F128_FromS32(t_s32 number);
#define c_s32tof128		F128_FromS32
t_f128					F128_FromS64(t_s64 number);
#define c_s64tof128		F128_FromS64
#if LIBCONFIG_USE_INT128
t_f128					F128_FromS128(t_s128 number);
#define c_s128tof128	F128_FromS128
#endif
#endif
//!@}

//!@doc Returns the nearest floating-point value from the given fixed-point `number`
/*!
**	TODO document this
*/
//!@{
#define					Float_FromFixed	CONCAT(FLOAT_TYPE,CONCAT(_From,FIXED_TYPE))
#define c_qtof			Float_FromFixed
#define					Float_FromQ8	CONCAT(FLOAT_TYPE,_FromQ8)
#define c_q8tof			Float_FromQ8
#define					Float_FromQ16	CONCAT(FLOAT_TYPE,_FromQ16)
#define c_q16tof		Float_FromQ16
#define					Float_FromQ32	CONCAT(FLOAT_TYPE,_FromQ32)
#define c_q32tof		Float_FromQ32
#define					Float_FromQ64	CONCAT(FLOAT_TYPE,_FromQ64)
#define c_q64tof		Float_FromQ64
#if LIBCONFIG_USE_INT128
#define					Float_FromQ128	CONCAT(FLOAT_TYPE,_FromQ128)
#define c_q128tof		Float_FromQ128
#endif

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromQ8(t_q8 number);
#define c_q8tof16		F16_FromQ8
t_f16					F16_FromQ16(t_q16 number);
#define c_q16tof16		F16_FromQ16
t_f16					F16_FromQ32(t_q32 number);
#define c_q32tof16		F16_FromQ32
t_f16					F16_FromQ64(t_q64 number);
#define c_q64tof16		F16_FromQ64
#if LIBCONFIG_USE_INT128
t_f16					F16_FromQ128(t_q128 number);
#define c_q128tof16		F16_FromQ128
#endif
#endif

t_f32					F32_FromQ8(t_q8 number);
#define c_q8tof32		F32_FromQ8
t_f32					F32_FromQ16(t_q16 number);
#define c_q16tof32		F32_FromQ16
t_f32					F32_FromQ32(t_q32 number);
#define c_q32tof32		F32_FromQ32
t_f32					F32_FromQ64(t_q64 number);
#define c_q64tof32		F32_FromQ64
#if LIBCONFIG_USE_INT128
t_f32					F32_FromQ128(t_q128 number);
#define c_q128tof32		F32_FromQ128
#endif

t_f64					F64_FromQ8(t_q8 number);
#define c_q8tof64		F64_FromQ8
t_f64					F64_FromQ16(t_q16 number);
#define c_q16tof64		F64_FromQ16
t_f64					F64_FromQ32(t_q32 number);
#define c_q32tof64		F64_FromQ32
t_f64					F64_FromQ64(t_q64 number);
#define c_q64tof64		F64_FromQ64
#if LIBCONFIG_USE_INT128
t_f64					F64_FromQ128(t_q128 number);
#define c_q128tof64		F64_FromQ128
#endif

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromQ8(t_q8 number);
#define c_q8tof80		F80_FromQ8
t_f80					F80_FromQ16(t_q16 number);
#define c_q16tof80		F80_FromQ16
t_f80					F80_FromQ32(t_q32 number);
#define c_q32tof80		F80_FromQ32
t_f80					F80_FromQ64(t_q64 number);
#define c_q64tof80		F80_FromQ64
#if LIBCONFIG_USE_INT128
t_f80					F80_FromQ128(t_q128 number);
#define c_q128tof80		F80_FromQ128
#endif
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromQ8(t_q8 number);
#define c_q8tof128		F128_FromQ8
t_f128					F128_FromQ16(t_q16 number);
#define c_q16tof128		F128_FromQ16
t_f128					F128_FromQ32(t_q32 number);
#define c_q32tof128		F128_FromQ32
t_f128					F128_FromQ64(t_q64 number);
#define c_q64tof128		F128_FromQ64
#if LIBCONFIG_USE_INT128
t_f128					F128_FromQ128(t_q128 number);
#define c_q128tof128	F128_FromQ128
#endif
#endif
//!@}

//!@doc Returns the nearest floating-point value from the given floating-point `number`
/*!
**	TODO document this
*/
//!@{
#define	 				Float_FromFloat	CONCAT(FLOAT_TYPE,CONCAT(_From,FLOAT_TYPE))
#define c_ftof			Float_FromFloat
#define	 				Float_FromF16	CONCAT(FLOAT_TYPE,_FromF16)
#define c_f16tof		Float_FromF16
#define	 				Float_FromF32	CONCAT(FLOAT_TYPE,_FromF32)
#define c_f32tof		Float_FromF32
#define	 				Float_FromF64	CONCAT(FLOAT_TYPE,_FromF64)
#define c_f64tof		Float_FromF64
#if LIBCONFIG_USE_FLOAT80
#define	 				Float_FromF80	CONCAT(FLOAT_TYPE,_FromF80)
#define c_f80tof		Float_FromF80
#endif
#if LIBCONFIG_USE_FLOAT128
#define	 				Float_FromF128	CONCAT(FLOAT_TYPE,_FromF128)
#define c_f128tof		Float_FromF128
#endif

#if LIBCONFIG_USE_FLOAT16
t_f16	 				F16_FromF16(t_f16 number);
#define c_f16tof32		F16_FromF16

t_f16	 				F16_FromF32(t_f32 number);
#define c_f32tof32		F16_FromF32

t_f16	 				F16_FromF64(t_f64 number);
#define c_f64tof32		F16_FromF64
#if LIBCONFIG_USE_FLOAT80
t_f16	 				F16_FromF80(t_f80 number);
#define c_f80tof32		F16_FromF80
#endif
#if LIBCONFIG_USE_FLOAT128
t_f16	 				F16_FromF128(t_f128 number);
#define c_f128tof32		F16_FromF128
#endif
#endif

#if LIBCONFIG_USE_FLOAT16
t_f32	 				F32_FromF16(t_f16 number);
#define c_f16tof32		F32_FromF16
#endif
t_f32	 				F32_FromF32(t_f32 number);
#define c_f32tof32		F32_FromF32

t_f32	 				F32_FromF64(t_f64 number);
#define c_f64tof32		F32_FromF64
#if LIBCONFIG_USE_FLOAT80
t_f32	 				F32_FromF80(t_f80 number);
#define c_f80tof32		F32_FromF80
#endif
#if LIBCONFIG_USE_FLOAT128
t_f32	 				F32_FromF128(t_f128 number);
#define c_f128tof32		F32_FromF128
#endif

#if LIBCONFIG_USE_FLOAT16
t_f64	 				F64_FromF16(t_f16 number);
#define c_f16tof64		F64_FromF16
#endif
t_f64	 				F64_FromF32(t_f32 number);
#define c_f32tof64		F64_FromF32

t_f64	 				F64_FromF64(t_f64 number);
#define c_f64tof64		F64_FromF64
#if LIBCONFIG_USE_FLOAT80
t_f64	 				F64_FromF80(t_f80 number);
#define c_f80tof64		F64_FromF80
#endif
#if LIBCONFIG_USE_FLOAT128
t_f64	 				F64_FromF128(t_f128 number);
#define c_f128tof64		F64_FromF128
#endif

#if LIBCONFIG_USE_FLOAT80
#if LIBCONFIG_USE_FLOAT16
t_f80	 				F80_FromF16(t_f16 number);
#define c_f16tof80		F80_FromF16
#endif
t_f80	 				F80_FromF32(t_f32 number);
#define c_f32tof80		F80_FromF32

t_f80	 				F80_FromF64(t_f64 number);
#define c_f64tof80		F80_FromF64
#if LIBCONFIG_USE_FLOAT80
t_f80	 				F80_FromF80(t_f80 number);
#define c_f80tof80		F80_FromF80
#endif
#if LIBCONFIG_USE_FLOAT128
t_f80	 				F80_FromF128(t_f128 number);
#define c_f128tof80		F80_FromF128
#endif
#endif
#if LIBCONFIG_USE_FLOAT128
#if LIBCONFIG_USE_FLOAT16
t_f128	 				F128_FromF16(t_f16 number);
#define c_f16tof128		F128_FromF16
#endif
t_f128	 				F128_FromF32(t_f32 number);
#define c_f32tof128		F128_FromF32

t_f128	 				F128_FromF64(t_f64 number);
#define c_f64tof128		F128_FromF64
#if LIBCONFIG_USE_FLOAT80
t_f128	 				F128_FromF80(t_f80 number);
#define c_f80tof128		F128_FromF80
#endif
t_f128	 				F128_FromF128(t_f128 number);
#define c_f128tof128	F128_FromF128
#endif
//!@}



/*============================================================================*\
||                        Floating-point number functions                     ||
\*============================================================================*/

//!@doc Creates a float value from its individual component parts.
/*!
**	@isostd{C89,https://en.cppreference.com/w/cpp/numeric/math/ldexp}
**
**	@param	mantissa	The significant digits of this floating-point number
**	@param	exponent	The (base 2) exponent of this floating-point number
**
**	@returns
**	The floating-point number value resulting from putting together
**	the given `mantissa` and `exponent` parts, essentiallylike so:
**	`mantissa * pow(2, exponent)`
*/
//!@{
#define					Float_From	CONCAT(FLOAT_TYPE,_From)
#define c_ldexp			Float_From
#define c_scalbn		Float_From
#define c_fldexp		Float_From
#define c_fscalbn		Float_From
#define c_tof			Float_From

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_From(t_f16 mantissa, t_sint exponent);
#define c_ldexpl		F16_From
#define c_scalbnl		F16_From
#define c_f16ldexp		F16_From
#define c_f16scalbn		F16_From
#define c_tof16			F16_From
#endif
t_f32					F32_From(t_f32 mantissa, t_sint exponent);
#define c_ldexpf		F32_From
#define c_scalbnf		F32_From
#define c_f32ldexp		F32_From
#define c_f32scalbn		F32_From
#define c_tof32			F32_From

t_f64					F64_From(t_f64 mantissa, t_sint exponent);
#define c_ldexpd		F64_From
#define c_scalbnd		F64_From
#define c_f64ldexp		F64_From
#define c_f64scalbn		F64_From
#define c_tof64			F64_From

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_From(t_f80 mantissa, t_sint exponent);
#define c_ldexpl		F80_From
#define c_scalbnl		F80_From
#define c_f80ldexp		F80_From
#define c_f80scalbn		F80_From
#define c_tof80			F80_From
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_From(t_f128 mantissa, t_sint exponent);
#define c_ldexpl		F128_From
#define c_scalbnl		F128_From
#define c_f128ldexp		F128_From
#define c_f128scalbn	F128_From
#define c_tof128		F128_From
#endif
//!@}



// TODO t_float	Float_NaN(t_char const* str)
/* 
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/nan}
*/

// TODO t_float	Float_Inf(void)
/* 
**	@nonstd
*/



//!@doc Decomposes given floating-point value into a normalized fraction and an integral power of two.
/*!
**	@isostd{C89,https://en.cppreference.com/w/cpp/numeric/math/frexp}
*/
//!@{
#define					Float_SplitExp	CONCAT(FLOAT_TYPE,_SplitExp)
#define c_frexp			Float_SplitExp
#define c_ffrexp		Float_SplitExp
#define c_fsplitexp		Float_SplitExp

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_SplitExp(t_f16 number, t_sint* exponent);
#define c_frexpl		F16_SplitExp
#define c_f16frexp		F16_SplitExp
#define c_f16splitexp	F16_SplitExp
#endif
t_f32					F32_SplitExp(t_f32 number, t_sint* exponent);
#define c_frexpf		F32_SplitExp
#define c_f32frexp		F32_SplitExp
#define c_f32splitexp	F32_SplitExp

t_f64					F64_SplitExp(t_f64 number, t_sint* exponent);
#define c_frexpd		F64_SplitExp
#define c_f64frexp		F64_SplitExp
#define c_f64splitexp	F64_SplitExp

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_SplitExp(t_f80 number, t_sint* exponent);
#define c_frexpl		F80_SplitExp
#define c_f80frexp		F80_SplitExp
#define c_f80splitexp	F80_SplitExp
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_SplitExp(t_f128 number, t_sint* exponent);
#define c_frexpl		F128_SplitExp
#define c_f128frexp		F128_SplitExp
#define c_f128splitexp	F128_SplitExp
#endif
//!@}



//!@doc Decomposes given floating-point value into fractional (returned) and integral (stored in the `integral` pointer) parts.
/*!
**	@isostd{C89,https://en.cppreference.com/w/cpp/numeric/math/modf}
*/
//!@{
#define					Float_SplitInt	CONCAT(FLOAT_TYPE,_SplitInt)
#define c_modf	 		Float_SplitInt
#define c_fmodf	 		Float_SplitInt
#define c_fsplitint		Float_SplitInt

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_SplitInt(t_f16 number, t_f16* integral);
#define c_modfl 		F16_SplitInt
#define c_f16modf 		F16_SplitInt
#define c_f16splitint	F16_SplitInt
#endif
t_f32					F32_SplitInt(t_f32 number, t_f32* integral);
#define c_modff 		F32_SplitInt
#define c_f32modf 		F32_SplitInt
#define c_f32splitint	F32_SplitInt

t_f64					F64_SplitInt(t_f64 number, t_f64* integral);
#define c_modfd 		F64_SplitInt
#define c_f64modf 		F64_SplitInt
#define c_f64splitint	F64_SplitInt

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_SplitInt(t_f80 number, t_f80* integral);
#define c_modfl 		F80_SplitInt
#define c_f80modf 		F80_SplitInt
#define c_f80splitint	F80_SplitInt
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_SplitInt(t_f128 number, t_f128* integral);
#define c_modfl 		F128_SplitInt
#define c_f128modf 		F128_SplitInt
#define c_f128splitint	F128_SplitInt
#endif
//!@}



//!@doc Copies the sign value from the given `source` to the given `target`, and returns it.
/*!
**	@isostd{C89,https://en.cppreference.com/w/cpp/numeric/math/copysign}
*/
//!@{
#define					Float_CopySign	CONCAT(FLOAT_TYPE,_CopySign)
#define c_copysign		Float_CopySign
#define c_fcopysign		Float_CopySign

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_CopySign(t_f16 target, t_f16 source);
#define c_copysignl		F16_CopySign
#define c_f16copysign	F16_CopySign
#endif
t_f32					F32_CopySign(t_f32 target, t_f32 source);
#define c_copysignf		F32_CopySign
#define c_f32copysign	F32_CopySign

t_f64					F64_CopySign(t_f64 target, t_f64 source);
#define c_copysignd		F64_CopySign
#define c_f64copysign	F64_CopySign

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_CopySign(t_f80 target, t_f80 source);
#define c_copysignl		F80_CopySign
#define c_f80copysign	F80_CopySign
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_CopySign(t_f128 target, t_f128 source);
#define c_copysignl		F128_CopySign
#define c_f128copysign	F128_CopySign
#endif
//!@}



//!@doc Returns the next representable value of `number` in the direction of `toward`
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/math/nextafter}
*/
//!@{
#define					Float_NextAfter	CONCAT(FLOAT_TYPE,_NextAfter)
#define c_nextafter		Float_NextAfter
#define c_fnextafter	Float_NextAfter

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_NextAfter(t_f16 number, t_f16 toward);
#define c_nextafterl	F16_NextAfter
#define c_f16nextafter	F16_NextAfter
#endif
t_f32					F32_NextAfter(t_f32 number, t_f32 toward);
#define c_nextafterf	F32_NextAfter
#define c_f32nextafter	F32_NextAfter

t_f64					F64_NextAfter(t_f64 number, t_f64 toward);
#define c_nextafterd	F64_NextAfter
#define c_f64nextafter	F64_NextAfter

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_NextAfter(t_f80 number, t_f80 toward);
#define c_nextafterl	F80_NextAfter
#define c_f80nextafter	F80_NextAfter
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_NextAfter(t_f128 number, t_f128 toward);
#define c_nextafterl	F128_NextAfter
#define c_f128nextafter	F128_NextAfter
#endif
//!@}



//!@doc Rounds the floating-point argument to an integer value in floating-point format, using the current rounding mode.
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/math/nearbyint}
*/
//!@{
#define					Float_NearbyInt	CONCAT(FLOAT_TYPE,_NearbyInt)
#define c_rint			Float_NearbyInt
#define c_nearbyint		Float_NearbyInt
#define c_frint			Float_NearbyInt
#define c_fnearbyint	Float_NearbyInt

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_NearbyInt(t_f16 number);
#define c_rintl			F16_NearbyInt
#define c_nearbyintl	F16_NearbyInt
#define c_f16rint		F16_NearbyInt
#define c_f16nearbyint	F16_NearbyInt
#endif
t_f32					F32_NearbyInt(t_f32 number);
#define c_rintf			F32_NearbyInt
#define c_nearbyintf	F32_NearbyInt
#define c_f32rint		F32_NearbyInt
#define c_f32nearbyint	F32_NearbyInt

t_f64					F64_NearbyInt(t_f64 number);
#define c_rintd			F64_NearbyInt
#define c_nearbyintd	F64_NearbyInt
#define c_f64rint		F64_NearbyInt
#define c_f64nearbyint	F64_NearbyInt

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_NearbyInt(t_f80 number);
#define c_rintl			F80_NearbyInt
#define c_nearbyintl	F80_NearbyInt
#define c_f80rint		F80_NearbyInt
#define c_f80nearbyint	F80_NearbyInt
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_NearbyInt(t_f128 number);
#define c_rintl			F128_NearbyInt
#define c_nearbyintl	F128_NearbyInt
#define c_f128rint		F128_NearbyInt
#define c_f128nearbyint	F128_NearbyInt
#endif
//!@}

//!@doc Rounds the floating-point argument to an integer value in integer format, using the current rounding mode.
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/math/lrint}
*/
//!@{
#define					Float_ToInt	CONCAT(FLOAT_TYPE,_ToInt)
#define c_lrint			Float_ToInt
#define c_flrint		Float_ToInt
#define c_ftoint		Float_ToInt

#if LIBCONFIG_USE_FLOAT16
t_sint					F16_ToInt(t_f16 number);
#define c_lrintl		F16_ToInt
#define c_f16lrint		F16_ToInt
#define c_f16toint		F16_ToInt
#endif
t_sint					F32_ToInt(t_f32 number);
#define c_lrintf		F32_ToInt
#define c_f32lrint		F32_ToInt
#define c_f32toint		F32_ToInt

t_sint					F64_ToInt(t_f64 number);
#define c_lrintd		F64_ToInt
#define c_f64lrint		F64_ToInt
#define c_f64toint		F64_ToInt

#if LIBCONFIG_USE_FLOAT80
t_sint					F80_ToInt(t_f80 number);
#define c_lrintl		F80_ToInt
#define c_f80lrint		F80_ToInt
#define c_f80toint		F80_ToInt
#endif
#if LIBCONFIG_USE_FLOAT128
t_sint					F128_ToInt(t_f128 number);
#define c_lrintl		F128_ToInt
#define c_f128lrint		F128_ToInt
#define c_f128toint		F128_ToInt
#endif
//!@}




//!@doc Returns the base-2 exponent of the given number `x`, as an integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/ilogb}
*/
//!@{
#define						Float_GetExp2	CONCAT(FLOAT_TYPE,_GetExp2)
#define c_ilogb				Float_GetExp2
#define c_filogb			Float_GetExp2
#define c_filog2			Float_GetExp2
#define c_fgetexp2			Float_GetExp2
#define Float_GetExponent2	Float_GetExp2

#if LIBCONFIG_USE_FLOAT16
t_sint						F16_GetExp2(t_f16 number);
#define c_ilogbl			F16_GetExp2
#define c_f16ilogb			F16_GetExp2
#define c_f16ilog2			F16_GetExp2
#define c_f16getexp2		F16_GetExp2
#define F16_GetExponent2	F16_GetExp2
#endif
t_sint						F32_GetExp2(t_f32 number);
#define c_ilogbf			F32_GetExp2
#define c_f32ilogb			F32_GetExp2
#define c_f32ilog2			F32_GetExp2
#define c_f32getexp2		F32_GetExp2
#define F32_GetExponent2	F32_GetExp2

t_sint						F64_GetExp2(t_f64 number);
#define c_ilogbd			F64_GetExp2
#define c_f64ilogb			F64_GetExp2
#define c_f64ilog2			F64_GetExp2
#define c_f64getexp2		F64_GetExp2
#define F64_GetExponent2	F64_GetExp2

#if LIBCONFIG_USE_FLOAT80
t_sint						F80_GetExp2(t_f80 number);
#define c_ilogbl			F80_GetExp2
#define c_f80ilogb			F80_GetExp2
#define c_f80ilog2			F80_GetExp2
#define c_f80getexp2		F80_GetExp2
#define F80_GetExponent2	F80_GetExp2
#endif
#if LIBCONFIG_USE_FLOAT128
t_sint						F128_GetExp2(t_f128 number);
#define c_ilogbl			F128_GetExp2
#define c_f128ilogb			F128_GetExp2
#define c_f128ilog2			F128_GetExp2
#define c_f128getexp2		F128_GetExp2
#define F128_GetExponent2	F128_GetExp2
#endif
//!@}

//!@doc Returns the base-10 exponent of the given number `x`, as an integer
/*!
**	@nonstd
*/
//!@{
#define						Float_GetExp10	CONCAT(FLOAT_TYPE,_GetExp10)
#define c_ilog				Float_GetExp10
#define c_filog				Float_GetExp10
#define c_filogd			Float_GetExp10
#define c_filog10			Float_GetExp10
#define c_fgetexp10			Float_GetExp10
#define Float_GetExponent10	Float_GetExp10

#if LIBCONFIG_USE_FLOAT16
t_sint						F16_GetExp10(t_f16 number);
#define c_ilogl				F16_GetExp10
#define c_f16ilog			F16_GetExp10
#define c_f16ilogd			F16_GetExp10
#define c_f16ilog10			F16_GetExp10
#define c_f16getexp10		F16_GetExp10
#define F16_GetExponent10	F16_GetExp10
#endif
t_sint						F32_GetExp10(t_f32 number);
#define c_ilogf				F32_GetExp10
#define c_f32ilog			F32_GetExp10
#define c_f32ilogd			F32_GetExp10
#define c_f32ilog10			F32_GetExp10
#define c_f32getexp10		F32_GetExp10
#define F32_GetExponent10	F32_GetExp10

t_sint						F64_GetExp10(t_f64 number);
#define c_ilogd				F64_GetExp10
#define c_f64ilog			F64_GetExp10
#define c_f64ilogd			F64_GetExp10
#define c_f64ilog10			F64_GetExp10
#define c_f64getexp10		F64_GetExp10
#define F64_GetExponent10	F64_GetExp10

#if LIBCONFIG_USE_FLOAT80
t_sint						F80_GetExp10(t_f80 number);
#define c_ilogl				F80_GetExp10
#define c_f80ilog			F80_GetExp10
#define c_f80ilogd			F80_GetExp10
#define c_f80ilog10			F80_GetExp10
#define c_f80getexp10		F80_GetExp10
#define F80_GetExponent10	F80_GetExp10
#endif
#if LIBCONFIG_USE_FLOAT128
t_sint						F128_GetExp10(t_f128 number);
#define c_ilogl				F128_GetExp10
#define c_f128ilog			F128_GetExp10
#define c_f128ilogd			F128_GetExp10
#define c_f128ilog10		F128_GetExp10
#define c_f128getexp10		F128_GetExp10
#define F128_GetExponent10	F128_GetExp10
#endif
//!@}



/*============================================================================*\
||                         Float-to-String Conversions                        ||
\*============================================================================*/



//!@doc Get the shortest string representation of the given floating-point number (dec or exp), with 'precision' fractional digits
/*!
**	@nonstd `ftoa()`
**
**	@param	number		The number to convert to a string
**	@param	precision	The amount of digits to print after the decimal point
**	@returns
**	A newly allocated string representation of the given `number`, with `precision` digits
*/
//!@{
#define					Float_ToString	CONCAT(FLOAT_TYPE,_ToString)
#define c_ftostr		Float_ToString

#if LIBCONFIG_USE_FLOAT16
_MALLOC()	t_char*		F16_ToString(t_f16 number, t_u8 precision);
#define c_f16tostr		F16_ToString
#endif
_MALLOC()	t_char*		F32_ToString(t_f32 number, t_u8 precision);
#define c_f32tostr		F32_ToString

_MALLOC()	t_char*		F64_ToString(t_f64 number, t_u8 precision);
#define c_f64tostr		F64_ToString

#if LIBCONFIG_USE_FLOAT80
_MALLOC()	t_char*		F80_ToString(t_f80 number, t_u8 precision);
#define c_f80tostr		F80_ToString
#endif
#if LIBCONFIG_USE_FLOAT128
_MALLOC()	t_char*		F128_ToString(t_f128 number, t_u8 precision);
#define c_f128tostr		F128_ToString
#endif
//!@}



//!@doc Get the string scientific notation of a floating-point number, with 'precision' fractional digits
/*!
**	@nonstd
**
**	@param	number		The number to convert to a string
**	@param	precision	The amount of digits to print after the decimal point
**	@returns
**	A newly allocated string representation of the given `number`, with `precision` digits
*/
//!@{
#define								Float_ToString_Exp	CONCAT(FLOAT_TYPE,_ToString_Exp)
#define c_ftostrexp					Float_ToString_Exp
#define c_ftostrsci					Float_ToString_Exp
#define Float_ToString_Sci			Float_ToString_Exp

#if LIBCONFIG_USE_FLOAT16
_MALLOC()	t_char*					F16_ToString_Exp(t_f16 number, t_u8 precision);
#define c_f16tostrexp				F16_ToString_Exp
#define c_f16tostrsci				F16_ToString_Exp
#define F16_ToString_Sci			F16_ToString_Exp
#endif
_MALLOC()	t_char*					F32_ToString_Exp(t_f32 number, t_u8 precision);
#define c_f32tostrexp				F32_ToString_Exp
#define c_f32tostrsci				F32_ToString_Exp
#define F32_ToString_Sci			F32_ToString_Exp

_MALLOC()	t_char*					F64_ToString_Exp(t_f64 number, t_u8 precision);
#define c_f64tostrexp				F64_ToString_Exp
#define c_f64tostrsci				F64_ToString_Exp
#define F64_ToString_Sci			F64_ToString_Exp

#if LIBCONFIG_USE_FLOAT80
_MALLOC()	t_char*					F80_ToString_Exp(t_f80 number, t_u8 precision);
#define c_f80tostrexp				F80_ToString_Exp
#define c_f80tostrsci				F80_ToString_Exp
#define F80_ToString_Sci			F80_ToString_Exp
#endif
#if LIBCONFIG_USE_FLOAT128
_MALLOC()	t_char*					F128_ToString_Exp(t_f128 number, t_u8 precision);
#define c_f128tostrexp				F128_ToString_Exp
#define c_f128tostrsci				F128_ToString_Exp
#define F128_ToString_Sci			F128_ToString_Exp
#endif
//!@}



//!@doc Get the string decimal representation of a floating-point number, with 'precision' fractional digits
/*!
**	@nonstd
**
**	@param	number		The number to convert to a string
**	@param	precision	The amount of digits to print after the decimal point
**	@returns
**	A newly allocated string representation of the given `number`, with `precision` digits
*/
//!@{
#define					Float_ToString_Dec	CONCAT(FLOAT_TYPE,_ToString_Dec)
#define c_ftostrdec		Float_ToString_Dec

#if LIBCONFIG_USE_FLOAT16
_MALLOC()	t_char*		F16_ToString_Dec(t_f16 number, t_u8 precision);
#define c_f16tostrdec	F16_ToString_Dec
#endif
_MALLOC()	t_char*		F32_ToString_Dec(t_f32 number, t_u8 precision);
#define c_f32tostrdec	F32_ToString_Dec

_MALLOC()	t_char*		F64_ToString_Dec(t_f64 number, t_u8 precision);
#define c_f64tostrdec	F64_ToString_Dec

#if LIBCONFIG_USE_FLOAT80
_MALLOC()	t_char*		F80_ToString_Dec(t_f80 number, t_u8 precision);
#define c_f80tostrdec	F80_ToString_Dec
#endif
#if LIBCONFIG_USE_FLOAT128
_MALLOC()	t_char*		F128_ToString_Dec(t_f128 number, t_u8 precision);
#define c_f128tostrdec	F128_ToString_Dec
#endif
//!@}



//!@doc Get the string hexadecimal representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
/*!
**	@nonstd
**
**	@param	number		The number to convert to a string
**	@param	precision	The amount of digits to print after the decimal point
**	@returns
**	A newly allocated string representation of the given `number`, with `precision` digits
*/
//!@{
#define					Float_ToString_Hex	CONCAT(FLOAT_TYPE,_ToString_Hex)
#define c_ftostrhex		Float_ToString_Hex

#if LIBCONFIG_USE_FLOAT16
_MALLOC()	t_char*		F16_ToString_Hex(t_f16 number, t_u8 precision);
#define c_f16tostrhex	F16_ToString_Hex
#endif
_MALLOC()	t_char*		F32_ToString_Hex(t_f32 number, t_u8 precision);
#define c_f32tostrhex	F32_ToString_Hex

_MALLOC()	t_char*		F64_ToString_Hex(t_f64 number, t_u8 precision);
#define c_f64tostrhex	F64_ToString_Hex

#if LIBCONFIG_USE_FLOAT80
_MALLOC()	t_char*		F80_ToString_Hex(t_f80 number, t_u8 precision);
#define c_f80tostrhex	F80_ToString_Hex
#endif
#if LIBCONFIG_USE_FLOAT128
_MALLOC()	t_char*		F128_ToString_Hex(t_f128 number, t_u8 precision);
#define c_f128tostrhex	F128_ToString_Hex
#endif
//!@}



//!@doc Get the string binary representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
/*!
**	@nonstd
**
**	@param	number		The number to convert to a string
**	@param	precision	The amount of digits to print after the decimal point
**	@returns
**	A newly allocated string representation of the given `number`, with `precision` digits
*/
//!@{
#define					Float_ToString_Bin	CONCAT(FLOAT_TYPE,_ToString_Bin)
#define c_ftostrbin		Float_ToString_Bin

#if LIBCONFIG_USE_FLOAT16
_MALLOC()	t_char*		F16_ToString_Bin(t_f16 number, t_u8 precision);
#define c_f16tostrbin	F16_ToString_Bin
#endif
_MALLOC()	t_char*		F32_ToString_Bin(t_f32 number, t_u8 precision);
#define c_f32tostrbin	F32_ToString_Bin

_MALLOC()	t_char*		F64_ToString_Bin(t_f64 number, t_u8 precision);
#define c_f64tostrbin	F64_ToString_Bin

#if LIBCONFIG_USE_FLOAT80
_MALLOC()	t_char*		F80_ToString_Bin(t_f80 number, t_u8 precision);
#define c_f80tostrbin	F80_ToString_Bin
#endif
#if LIBCONFIG_USE_FLOAT128
_MALLOC()	t_char*		F128_ToString_Bin(t_f128 number, t_u8 precision);
#define c_f128tostrbin	F128_ToString_Bin
#endif
//!@}



// TODO Float_ToString_Base()



/*============================================================================*\
||                         String-to-Float Conversions                        ||
\*============================================================================*/



// General parser functions



//!@doc Parse a floating-point number from the given number string `str`
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Float_Parse	CONCAT(FIXED_TYPE,_Parse)
#define c_fparse		Float_Parse

#if LIBCONFIG_USE_FLOAT16
t_size					F16_Parse	(t_f16	*dest, t_char const* str, t_size n);
#define c_f16parse		F16_Parse
#endif
t_size					F32_Parse	(t_f32	*dest, t_char const* str, t_size n);
#define c_f32parse		F32_Parse

t_size					F64_Parse	(t_f64	*dest, t_char const* str, t_size n);
#define c_f64parse		F64_Parse

#if LIBCONFIG_USE_FLOAT80
t_size					F80_Parse	(t_f80	*dest, t_char const* str, t_size n);
#define c_f80parse		F80_Parse
#endif
#if LIBCONFIG_USE_FLOAT128
t_size					F128_Parse	(t_f128	*dest, t_char const* str, t_size n);
#define c_f128parse		F128_Parse
#endif
//!@}

//!@doc Parse a floating-point number from the given string (can be decimal/exponential/hexdecimal)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/atof}
**
**	@param	str	The string to parse a floating-point value from.
**	@returns
**	A floating-point value parsed from the given `str`
*/
//!@{
#define					Float_FromString	CONCAT(FLOAT_TYPE,_FromString)
#define c_strtof		Float_FromString

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromString(t_char const* str);
#define c_strtof16		F16_FromString
#endif
t_f32					F32_FromString(t_char const* str);
#define c_strtof32		F32_FromString

t_f64					F64_FromString(t_char const* str);
#define c_strtof64		F64_FromString

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromString(t_char const* str);
#define c_strtof80		F80_FromString
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromString(t_char const* str);
#define c_strtof128		F128_FromString
#endif
//!@}



// Decimal parser functions



//!@doc Parse a floating-point number from the given decimal number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be decimal number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Float_Parse_Dec	CONCAT(FIXED_TYPE,_Parse_Dec)
#define c_fparsedec		Float_Parse_Dec

#if LIBCONFIG_USE_FLOAT16
t_size					F16_Parse_Dec	(t_f16	*dest, t_char const* str, t_size n);
#define c_f16parsedec	F16_Parse_Dec
#endif
t_size					F32_Parse_Dec	(t_f32	*dest, t_char const* str, t_size n);
#define c_f32parsedec	F32_Parse_Dec

t_size					F64_Parse_Dec	(t_f64	*dest, t_char const* str, t_size n);
#define c_f64parsedec	F64_Parse_Dec

#if LIBCONFIG_USE_FLOAT80
t_size					F80_Parse_Dec	(t_f80	*dest, t_char const* str, t_size n);
#define c_f80parsedec	F80_Parse_Dec
#endif
#if LIBCONFIG_USE_FLOAT128
t_size					F128_Parse_Dec	(t_f128	*dest, t_char const* str, t_size n);
#define c_f128parsedec	F128_Parse_Dec
#endif
//!@}

//!@doc Parse the decimal representation of a floating-point number
/*!
**	@nonstd
**
**	@param	str	The string to parse a floating-point value from:
**				it must be a number in decimal notation (ie: no `e` exponent allowed)
**	@returns
**	A floating-point value parsed from the given `str`
*/
//!@{
#define					Float_FromString_Dec	CONCAT(FLOAT_TYPE,_FromString_Dec)
#define c_strdectof		Float_FromString_Dec

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromString_Dec(t_char const* str);
#define c_strdectof16	F16_FromString_Dec
#endif
t_f32					F32_FromString_Dec(t_char const* str);
#define c_strdectof32	F32_FromString_Dec

t_f64					F64_FromString_Dec(t_char const* str);
#define c_strdectof64	F64_FromString_Dec

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromString_Dec(t_char const* str);
#define c_strdectof80	F80_FromString_Dec
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromString_Dec(t_char const* str);
#define c_strdectof128	F128_FromString_Dec
#endif
//!@}



// Hexadecimal parser functions



//!@doc Parse a floating-point number from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 16) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Float_Parse_Hex	CONCAT(FIXED_TYPE,_Parse_Hex)
#define c_fparsehex		Float_Parse_Hex

#if LIBCONFIG_USE_FLOAT16
t_size					F16_Parse_Hex	(t_f16	*dest, t_char const* str, t_size n);
#define c_f16parsehex	F16_Parse_Hex
#endif
t_size					F32_Parse_Hex	(t_f32	*dest, t_char const* str, t_size n);
#define c_f32parsehex	F32_Parse_Hex

t_size					F64_Parse_Hex	(t_f64	*dest, t_char const* str, t_size n);
#define c_f64parsehex	F64_Parse_Hex

#if LIBCONFIG_USE_FLOAT80
t_size					F80_Parse_Hex	(t_f80	*dest, t_char const* str, t_size n);
#define c_f80parsehex	F80_Parse_Hex
#endif
#if LIBCONFIG_USE_FLOAT128
t_size					F128_Parse_Hex	(t_f128	*dest, t_char const* str, t_size n);
#define c_f128parsehex	F128_Parse_Hex
#endif
//!@}

//!@doc Parse the hexadecimal representation of a floating-point number
/*!
**	@nonstd
**
**	@param	str	The string to parse a floating-point value from:
**				it must be in hexadecimal float notation (ie: with `p` exponent)
**	@returns
**	A floating-point value parsed from the given `str`
*/
//!@{
#define					Float_FromString_Hex	CONCAT(FLOAT_TYPE,_FromString_Hex)
#define c_strhextof		Float_FromString_Hex

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromString_Hex(t_char const* str);
#define c_strhextof16	F16_FromString_Hex
#endif
t_f32					F32_FromString_Hex(t_char const* str);
#define c_strhextof32	F32_FromString_Hex

t_f64					F64_FromString_Hex(t_char const* str);
#define c_strhextof64	F64_FromString_Hex

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromString_Hex(t_char const* str);
#define c_strhextof80	F80_FromString_Hex
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromString_Hex(t_char const* str);
#define c_strhextof128	F128_FromString_Hex
#endif
//!@}



// Octal parser functions



//!@doc Parse a floating-point number from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 8) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Float_Parse_Oct	CONCAT(FIXED_TYPE,_Parse_Oct)
#define c_fparseoct		Float_Parse_Oct

#if LIBCONFIG_USE_FLOAT16
t_size					F16_Parse_Oct	(t_f16	*dest, t_char const* str, t_size n);
#define c_f16parseoct	F16_Parse_Oct
#endif
t_size					F32_Parse_Oct	(t_f32	*dest, t_char const* str, t_size n);
#define c_f32parseoct	F32_Parse_Oct

t_size					F64_Parse_Oct	(t_f64	*dest, t_char const* str, t_size n);
#define c_f64parseoct	F64_Parse_Oct

#if LIBCONFIG_USE_FLOAT80
t_size					F80_Parse_Oct	(t_f80	*dest, t_char const* str, t_size n);
#define c_f80parseoct	F80_Parse_Oct
#endif
#if LIBCONFIG_USE_FLOAT128
t_size					F128_Parse_Oct	(t_f128	*dest, t_char const* str, t_size n);
#define c_f128parseoct	F128_Parse_Oct
#endif
//!@}

//!@doc Parse the octal representation of a floating-point number
/*!
**	@nonstd
**
**	@param	str	The string to parse a floating-point value from:
**				it must be in octal float notation (ie: with `p` exponent)
**	@returns
**	A floating-point value parsed from the given `str`
*/
//!@{
#define					Float_FromString_Oct	CONCAT(TYPE_FLOAT,_FromString_Oct)
#define c_strocttof		Float_FromString_Oct

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromString_Oct(t_char const* str);
#define c_strocttof16	F16_FromString_Oct
#endif
t_f32					F32_FromString_Oct(t_char const* str);
#define c_strocttof32	F32_FromString_Oct

t_f64					F64_FromString_Oct(t_char const* str);
#define c_strocttof64	F64_FromString_Oct

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromString_Oct(t_char const* str);
#define c_strocttof80	F80_FromString_Oct
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromString_Oct(t_char const* str);
#define c_strocttof128	F128_FromString_Oct
#endif
//!@}



// Binary parser functions



//!@doc Parse a floating-point number from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 2) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Float_Parse_Bin	CONCAT(FIXED_TYPE,_Parse_Bin)
#define c_fparsebin		Float_Parse_Bin

#if LIBCONFIG_USE_FLOAT16
t_size					F16_Parse_Bin	(t_f16	*dest, t_char const* str, t_size n);
#define c_f16parsebin	F16_Parse_Bin
#endif
t_size					F32_Parse_Bin	(t_f32	*dest, t_char const* str, t_size n);
#define c_f32parsebin	F32_Parse_Bin

t_size					F64_Parse_Bin	(t_f64	*dest, t_char const* str, t_size n);
#define c_f64parsebin	F64_Parse_Bin

#if LIBCONFIG_USE_FLOAT80
t_size					F80_Parse_Bin	(t_f80	*dest, t_char const* str, t_size n);
#define c_f80parsebin	F80_Parse_Bin
#endif
#if LIBCONFIG_USE_FLOAT128
t_size					F128_Parse_Bin	(t_f128	*dest, t_char const* str, t_size n);
#define c_f128parsebin	F128_Parse_Bin
#endif
//!@}

//!@doc Parse the binary representation of a floating-point number
/*!
**	@nonstd
**
**	@param	str	The string to parse a floating-point value from:
**				it must be in binary float notation (ie: with `p` exponent)
**	@returns
**	A floating-point value parsed from the given `str`
*/
//!@{
#define					Float_FromString_Bin	CONCAT(TYPE_FLOAT,_FromString_Bin)
#define c_strbintof		Float_FromString_Bin

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_FromString_Bin(t_char const* str);
#define c_strbintof16	F16_FromString_Bin
#endif
t_f32					F32_FromString_Bin(t_char const* str);
#define c_strbintof32	F32_FromString_Bin

t_f64					F64_FromString_Bin(t_char const* str);
#define c_strbintof64	F64_FromString_Bin

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromString_Bin(t_char const* str);
#define c_strbintof80	F80_FromString_Bin
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromString_Bin(t_char const* str);
#define c_strbintof128	F128_FromString_Bin
#endif
//!@}



// TODO Float_FromString_Base()



#endif

/*! @endgroup */
HEADER_END
#endif
