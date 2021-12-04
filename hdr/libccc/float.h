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
/*!@group{libccc_float}
** @{
**	This header defines the floating-point number primitive types and functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**	@isostd{C,https://en.cppreference.com/w/c/language/floating_constant}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/fenv}
**	- https://en.wikipedia.org/wiki/IEEE_754
**
**	@file
*/

// TODO subnormal float util functions/macros ?

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_FLOAT_T
#define __LIBCCC_FLOAT_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Primitive type: 32-bit 'single precision' IEEE-754 floating-point numbers
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**
**	Learn more: https://en.wikipedia.org/wiki/Single-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 8 exponent bits
**	- 23 fraction bits
*/
typedef float		t_f32;
TYPEDEF_ALIAS(		t_f32,	FLOAT_32,	PRIMITIVE)

//! Primitive type: 64-bit 'double precision' IEEE-754 floating-point numbers
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Real_floating_types}
**
**	Learn more: https://en.wikipedia.org/wiki/Double-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 11 exponent bits
**	- 52 fraction bits
*/
typedef double		t_f64;
TYPEDEF_ALIAS(		t_f64,	FLOAT_64,	PRIMITIVE)

#if LIBCONFIG_USE_FLOAT80
//! Primitive type: 80-bit 'extended precision' x86 floating-point numbers (only certain platforms)
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
**	- 63 fraction bits
*/
typedef _Float80	t_f80;
TYPEDEF_ALIAS(		t_f80,	FLOAT_80,	PRIMITIVE)
#elif (LIBCONFIG_FLOAT_BITS == 80)
	#error "Cannot set default float to 80-bit extended-precision, unavailable on this platform"
#endif

#if LIBCONFIG_USE_FLOAT128
//! Primitive type: 32-bit 'quadruple precision' IEEE-754 floating-point numbers (only certain platforms)
/*!
**	@isostd{C,https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html}
**
**	Learn more: https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
**
**	This floating-point type consists of:
**	- 1 sign bit
**	- 15 exponent bits
**	- 112 fraction bits
*/
typedef _Float128	t_f128;
TYPEDEF_ALIAS(		t_f128,	FLOAT_128,	PRIMITIVE)
#elif (LIBCONFIG_FLOAT_BITS == 128)
	#error "Cannot set default float to 128-bit quadruple-precision, unavailable on this platform"
#endif



//! The actual underlying type for the `t_float` configurable type
#define FLOAT_T		CONCAT(t_f,LIBCONFIG_FLOAT_BITS)
//! The actual underlying type for the `t_float` configurable type, in uppercase
#define FLOAT_TYPE	CONCAT(F,LIBCONFIG_FLOAT_BITS)

//! The configurable-size floating-point number primitive type.
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
typedef CONCAT(t_f,LIBCONFIG_FLOAT_BITS)	t_float;
TYPEDEF_ALIAS(t_float, FLOAT, PRIMITIVE)



#if(LIBCONFIG_FLOAT_BITS != 32 && \
	LIBCONFIG_FLOAT_BITS != 64 && \
	LIBCONFIG_FLOAT_BITS != 80 && \
	LIBCONFIG_FLOAT_BITS != 96 && \
	LIBCONFIG_FLOAT_BITS != 128)
	#error "LIBCONFIG_FLOAT_BITS must be equal to one of: 32, 64, 80, 96, 128"
#endif



#undef FLOAT_ERROR

#if (LIBCONFIG_FIXED_ERROR == 0)

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



//! The floating-point "not a number" value.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/NAN}
*/
//!@{
#ifndef NAN
#define NAN			(0. / 0.)
#endif
#ifndef NOTNUMBER
#define NOTNUMBER	NAN
#endif
//!@}

//! Checks if the given 'x' has a "not a number" value.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/isnan}
**
**	Also, define isnan() for ANSI C compatibility, if needed.
*/
//!@{
#ifndef isnan
#define isnan(X)	(X != X)
#endif
#ifndef IS_NAN
#define IS_NAN(X)		isnan(X)
#endif
#ifndef IS_NOTNUMBER
#define IS_NOTNUMBER(X)	isnan(X)
#endif
//!@}



//! The floating-point infinity value (use `-INF` for negative)
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

//! Checks if the given 'x' is either +INFINITY or -INFINITY
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/isinf}
**
**	Also, define isinf() for ANSI C compatibility, if needed.
*/
//!@{
#ifndef isinf
#define isinf(X)	(isnan((X) - (X)) && !isnan(X))
#endif
#ifndef IS_INF
#define IS_INF(X)		isinf(X)
#endif
#ifndef IS_INFINITY
#define IS_INFINITY(X)	isinf(X)
#endif
//!@}



// TODO add wrapper for isfinite(x)
// TODO add wrapper for isnormal(x)
// TODO add wrapper for isunordered(x, y)
// TODO add wrapper for fpclassify()



//! TODO add HUGE and TINY min/max value macros
/*!
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/HUGE_VAL}
**	@isostd{C,https://en.cppreference.com/w/c/types/limits#Limits_of_floating_point_types}
*/



//! TODO document this
#define SAMPLE_NB		(1024)



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

//! This macro sets the floating-point expression evaluation method (ie: how floats are operated upon).
/*!
**	The floating-point evaluation method. Possible values are:
**	`-1`	indeterminate
**	 `0`	evaluate all operations and constants, whose semantic type has at most the range and precision of float, to the range and precision of float;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `1`	evaluate all operations and constants, whose semantic type has at most the range and precision of double, to the range and precision of double;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `2`	evaluate all operations and constants, whose semantic type has at most the range and precision of long double, to the range and precision of long double;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `N`	where `_FloatN`  is a supported interchange floating type:
**	    	evaluate all operations and constants, whose semantic type has at most the range and precision of the _FloatN type, to the range and precision of the _FloatN type;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
**	 `N + 1`, where `_FloatNx` is a supported extended floating type:
**	    	evaluate operations and constants, whose semantic type has at most the range and precision of the _FloatNx type, to the range and precision of the _FloatNx type;
**	    	evaluate all other operations and constants to the range and precision of the semantic type.
*/
#ifndef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD	1
#endif



//! If `(value >= FLOAT_THRESHOLD_HUGE)`, Float_ToString() functions will write in scientific notation rather than decimal notation
#define FLOAT_THRESHOLD_HUGE	(1e+9)
//! If `(value <= FLOAT_THRESHOLD_TINY)`, Float_ToString() functions will write in scientific notation rather than decimal notation
#define FLOAT_THRESHOLD_TINY	(1e-9)

// TODO add IS_NORMAL() and IS_SUBNORMAL()

// TODO instead of using FLT_MIN/FLT_MAX/FLT_EPSILON, calculate them manually (in a cross-platform manner)

/*! @name 32-bit float bitwise constants
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
//!@{
#define F32_SIGNED			(0x80000000)			//!< A 32-bit floating-point number's sign bit (bitmask)
#define F32_EXPONENT_BIAS	(127)					//!< A 32-bit floating-point number's exponent bias offset
#define F32_EXPONENT		(0x7F800000)			//!< A 32-bit floating-point number's exponent bit region (bitmask)
#define F32_EXPONENT_ZERO	(0x3F800000)			//!< A 32-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F32_EXPONENT_BITS	(8)						//!< A 32-bit floating-point number's amount of bits dedicated to the exponent
#define F32_MANTISSA		(0x007FFFFF)			//!< A 32-bit floating-point number's mantissa bit region (bitmask)
#define F32_MANTISSA_SIGNED	(0x807FFFFF)			//!< A 32-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F32_MANTISSA_BITS	(23)					//!< A 32-bit floating-point number's amount of bits dedicated to the mantissa
#define F32_INIT_VALUE		(0x1.p-23)				//!< A 32-bit floating-point number's value if all bits are zero
#define F32_NEXT(X, TOWARD)	(nextafterf(X, TOWARD))	//!< Returns the nearest float value greater than the one given as `X`, going in the direction of `TOWARD`
#define F32_MIN				(FLT_MIN)				//!< A 32-bit floating-point's minimum representable positive normal value.
#define F32_MAX				(FLT_MAX)				//!< A 32-bit floating-point's maximum finite representable value.
#define F32_EPSILON			(FLT_EPSILON)			//!< Difference between 1 and the least value greater than 1 that is representable.
//!@}

/*! @name 64-bit float bitwise constants
**	IEEE 754 64-bit floating point double-precision bitwise macros
*/
//!@{
#define F64_SIGNED			(0x8000000000000000)	//!< A 64-bit floating-point number's sign bit (bitmask)
#define F64_EXPONENT_BIAS	(1023)					//!< A 64-bit floating-point number's exponent bias offset
#define F64_EXPONENT		(0x7FF0000000000000)	//!< A 64-bit floating-point number's exponent bit region (bitmask)
#define F64_EXPONENT_ZERO	(0x3FF0000000000000)	//!< A 64-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F64_EXPONENT_BITS	(11)					//!< A 64-bit floating-point number's amount of bits dedicated to the exponent
#define F64_MANTISSA		(0x000FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa bit region (bitmask)
#define F64_MANTISSA_SIGNED	(0x800FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F64_MANTISSA_BITS	(52)					//!< A 64-bit floating-point number's amount of bits dedicated to the mantissa
#define F64_INIT_VALUE		(0x1.p-52)				//!< A 64-bit floating-point number's value if all bits are zero
#define F64_NEXT(X, TOWARD)	(nextafterd(X, TOWARD))	//!< Returns the nearest float value greater than the one given as `X`, going in the direction of `TOWARD`
#define F64_MIN				(DBL_MIN)				//!< A 64-bit floating-point's minimum representable positive normal value.
#define F64_MAX				(DBL_MAX)				//!< A 64-bit floating-point's maximum finite representable value.
#define F64_EPSILON			(DBL_EPSILON)			//!< Difference between 1 and the least value greater than 1 that is representable.
//!@}

/*! @name 80-bit float bitwise constants
**	x86 80-bit floating point extended precision bitwise macros
*/
//!@{
#define F80_SIGNED			(0x80000000000000000000l)	//!< A 80-bit floating-point number's sign bit (bitmask)
#define F80_EXPONENT_BIAS	(16383)						//!< A 80-bit floating-point number's exponent bias offset
#define F80_EXPONENT		(0x7FFF0000000000000000l)	//!< A 80-bit floating-point number's exponent bit region (bitmask)
#define F80_EXPONENT_ZERO	(0x3FFF0000000000000000l)	//!< A 80-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F80_EXPONENT_BITS	(15)						//!< A 80-bit floating-point number's amount of bits dedicated to the exponent
#define F80_MANTISSA		(0x0000FFFFFFFFFFFFFFFFl)	//!< A 80-bit floating-point number's mantissa bit region (bitmask)
#define F80_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFl)	//!< A 80-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F80_MANTISSA_BITS	(64)						//!< A 80-bit floating-point number's amount of bits dedicated to the mantissa
#define F80_INIT_VALUE		(0x1.p-64)					//!< A 80-bit floating-point number's value if all bits are zero
#define F80_NEXT(X, TOWARD)	(nextafterld(X, TOWARD))	//!< Returns the nearest float value greater than the one given as `X`, going in the direction of `TOWARD`
#define F80_MIN				(LDBL_MIN)					//!< A 80-bit floating-point's minimum representable positive normal value.
#define F80_MAX				(LDBL_MAX)					//!< A 80-bit floating-point's maximum finite representable value.
#define F80_EPSILON			(LDBL_EPSILON)				//!< Difference between 1 and the least value greater than 1 that is representable.
//!@}

/*! @name 128-bit float bitwise constants
**	IEEE 754 128-bit floating point quadruple-precision bitwise macros
*/
//!@{
#define F128_SIGNED				(0x80000000000000000000000000000000l)	//!< A 128-bit floating-point number's sign bit (bitmask)
#define F128_EXPONENT_BIAS		(16383)									//!< A 128-bit floating-point number's exponent bias offset
#define F128_EXPONENT			(0x7FFF0000000000000000000000000000l)	//!< A 128-bit floating-point number's exponent bit region (bitmask)
#define F128_EXPONENT_ZERO		(0x3FFF0000000000000000000000000000l)	//!< A 128-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F128_EXPONENT_BITS		(15)									//!< A 128-bit floating-point number's amount of bits dedicated to the exponent
#define F128_MANTISSA			(0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFl)	//!< A 128-bit floating-point number's mantissa bit region (bitmask)
#define F128_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFl)	//!< A 128-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F128_MANTISSA_BITS		(112)									//!< A 128-bit floating-point number's amount of bits dedicated to the mantissa
#define F128_INIT_VALUE			(0x1.p-112)								//!< A 128-bit floating-point number's value if all bits are zero
#define F128_NEXT(X, TOWARD)	(nextafterq(X, TOWARD))					//!< Returns the nearest float value greater than the one given as `X`, going in the direction of `TOWARD`
#define F128_MIN				(LDBL_MIN)								//!< A 128-bit floating-point's minimum representable positive normal value.
#define F128_MAX				(LDBL_MAX)								//!< A 128-bit floating-point's maximum finite representable value.
#define F128_EPSILON			(LDBL_EPSILON)							//!< Difference between 1 and the least value greater than 1 that is representable.
//!@}



/*! @name float bitwise constants
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
#define FLOAT_NEXT				CONCAT(FLOAT_TYPE,_NEXT)
#define FLOAT_MIN				CONCAT(FLOAT_TYPE,_MIN)
#define FLOAT_MAX				CONCAT(FLOAT_TYPE,_MAX)
#define FLOAT_EPSILON			CONCAT(FLOAT_TYPE,_EPSILON)
//!@}



//! Union type to allow direct bitwise manipulation of floating-point values
/*!
**	This union type is used in several math function implementations, to
**	manipulate float bits directly, by using bitwise operators with int types.
*/
typedef union float_cast
{
	t_float	value_float;
#if (LIBCONFIG_FLOAT_BITS == 32)
	s32		value_int;
#elif (LIBCONFIG_FLOAT_BITS == 64)
	s64		value_int;
#else
	s64[2]	value_int;
#endif
}	u_float_cast;



#endif
#ifndef __LIBCCC_FLOAT_F
#define __LIBCCC_FLOAT_F

/*
** ************************************************************************** *|
**                        Floating-point number functions                     *|
** ************************************************************************** *|
*/

//! A smart constructor: calls the appropriate `Float_From*()` function from the given argument type
//!@{
#define DEFINEFUNC_Float(X, FUNCTYPE) \
	_Generic((X),	\
		t_s16:	 FUNCTYPE##_FromInt,	\
		t_s32:	 FUNCTYPE##_FromInt,	\
		t_s64:	 FUNCTYPE##_FromInt,	\
		t_s128:	 FUNCTYPE##_FromInt,	\
		t_sint:  FUNCTYPE##_FromInt,	\
		t_q16:	 FUNCTYPE##_FromFixed,	\
		t_q32:	 FUNCTYPE##_FromFixed,	\
		t_q64:	 FUNCTYPE##_FromFixed,	\
		t_q128:	 FUNCTYPE##_FromFixed,	\
		t_fixed: FUNCTYPE##_FromFixed,	\
		t_f32:	 FUNCTYPE##_FromFloat,	\
		t_f64:	 FUNCTYPE##_FromFloat,	\
		t_f80:	 FUNCTYPE##_FromFloat,	\
		t_f128:	 FUNCTYPE##_FromFloat,	\
		t_float: FUNCTYPE##_FromFloat,	\
	)(X)
#define Float(X)	DEFINEFUNC_Float(X, Fixed)
#define F32(X)		DEFINEFUNC_Float(X, F32)
#define F64(X)		DEFINEFUNC_Float(X, F64)
#define F80(X)		DEFINEFUNC_Float(X, F80)
#define F128(X)		DEFINEFUNC_Float(X, F128)
//!@}

//! Returns the nearest floating-point value to the given integer `number`
/*!
**	TODO document
*/
//!@{
#define					Float_FromInt	CONCAT(FIXED_TYPE,_FromInt)
#define c_itofloat		Float_FromInt

t_f32					F32_FromInt(t_sint number);
#define c_itof32		F32_FromInt

t_f64					F64_FromInt(t_sint number);
#define c_itof64		F64_FromInt

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromInt(t_sint number);
#define c_itof80		F80_FromInt
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromInt(t_sint number);
#define c_itof128		F128_FromInt
#endif
//!@}

//! Returns the nearest floating-point value to the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define					Float_FromFixed	CONCAT(FIXED_TYPE,_FromFixed)
#define c_qtofloat		Float_FromFixed

t_f32					F32_FromFixed(t_fixed number);
#define c_qtof32		F32_FromFixed

t_f64					F64_FromFixed(t_fixed number);
#define c_qtof64		F64_FromFixed

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_FromFixed(t_fixed number);
#define c_qtof80		F80_FromFixed
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_FromFixed(t_fixed number);
#define c_qtof128		F128_FromFixed
#endif
//!@}

//! Returns the nearest floating-point value to the given floating-point `number`
/*!
**	TODO document
*/
//!@{
#define	 				Float_FromFloat	CONCAT(FIXED_TYPE,_FromFloat)
#define c_ftofloat		Float_FromFloat

t_f32	 				F32_FromFloat(t_float number);
#define c_ftof32		F32_FromFloat

t_f64	 				F64_FromFloat(t_float number);
#define c_ftof64		F64_FromFloat

#if LIBCONFIG_USE_FLOAT80
t_f80	 				F80_FromFloat(t_float number);
#define c_ftof80		F80_FromFloat
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128	 				F128_FromFloat(t_float number);
#define c_ftof128		F128_FromFloat
#endif
//!@}



//! Creates a float value from its individual component parts.
/*!
**	@nonstd
**
**	@param	integer		The significant digits of this floating-point number
**	@param	exponent	The (base 2) exponent of this floating-point number,
**						this is applied like so: `integer * pow(2, exponent)`
**	@returns
**	The floating-point number value resulting from putting together
**	the given `integer` and `exponent` parts.
*/
//!@{
#define					Float_From	CONCAT(FLOAT_TYPE,_From)
#define c_tofloat		Float_From

t_f32					F32_From(t_sint integer, t_sint exponent);
#define c_tof32			F32_From

t_f64					F64_From(t_sint integer, t_sint exponent);
#define c_tof64			F64_From

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_From(t_sint integer, t_sint exponent);
#define c_tof80			F80_From
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_From(t_sint integer, t_sint exponent);
#define c_tof128		F128_From
#endif
//!@}



// TODO t_float	Float_NaN(t_char const* str)
/* 
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math/nan}
*/

// TODO t_float	Float_Infinity(void)
/* 
**	@nonstd
*/



//! Returns the base-2 exponent of the given number `x`, as an integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/ilogb}
*/
//!@{
#define						Float_GetExp2	CONCAT(FLOAT_TYPE,_GetExp2)
#define c_fgetexp2			Float_GetExp2
#define c_filogb			Float_GetExp2
#define c_filog2			Float_GetExp2
#define Float_GetExponent2	Float_GetExp2

t_sint						F32_GetExp2(t_f32 number);
#define c_f32getexp2		F32_GetExp2

t_sint						F64_GetExp2(t_f64 number);
#define c_f64getexp2		F64_GetExp2

#if LIBCONFIG_USE_FLOAT80
t_sint						F80_GetExp2(t_f80 number);
#define c_f80getexp2		F80_GetExp2
#endif
#if LIBCONFIG_USE_FLOAT128
t_sint						F128_GetExp2(t_f128 number);
#define c_f128getexp2		F128_GetExp2
#endif
//!@}

//! Returns the base-10 exponent of the given number `x`, as an integer
/*!
**	@nonstd
*/
//!@{
#define						Float_GetExp10	CONCAT(FLOAT_TYPE,_GetExp10)
#define c_fgetexp10			Float_GetExp10
#define c_filogd			Float_GetExp10
#define c_filog10			Float_GetExp10
#define Float_GetExponent10	Float_GetExp10

t_sint						F32_GetExp10(t_f32 number);
#define c_f32getexp10		F32_GetExp10

t_sint						F64_GetExp10(t_f64 number);
#define c_f64getexp10		F64_GetExp10

#if LIBCONFIG_USE_FLOAT80
t_sint						F80_GetExp10(t_f80 number);
#define c_f80getexp10		F80_GetExp10
#endif
#if LIBCONFIG_USE_FLOAT128
t_sint						F128_GetExp10(t_f128 number);
#define c_f128getexp10		F128_GetExp10
#endif
//!@}



/*
** ************************************************************************** *|
**                         Float-to-String Conversions                        *|
** ************************************************************************** *|
*/



//! Get the shortest string representation of the given floating-point number (dec or exp), with 'precision' fractional digits
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



//! Get the string scientific notation of a floating-point number, with 'precision' fractional digits
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



//! Get the string decimal representation of a floating-point number, with 'precision' fractional digits
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



//! Get the string hexadecimal representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
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



//! Get the string binary representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
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



/*
** ************************************************************************** *|
**                         String-to-Float Conversions                        *|
** ************************************************************************** *|
*/



// General parser functions



//! Parse a floating-point number from the given number string `str`
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

//! Parse a floating-point number from the given string (can be decimal/exponential/hexdecimal)
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



//! Parse a floating-point number from the given decimal number string
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

//! Parse the decimal representation of a floating-point number
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



//! Parse a floating-point number from the given hexadecimal (base 16) number string
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

//! Parse the hexadecimal representation of a floating-point number
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



//! Parse a floating-point number from the given octal (base 8) number string
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

//! Parse the octal representation of a floating-point number
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



//! Parse a floating-point number from the given binary (base 2) number string
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

//! Parse the binary representation of a floating-point number
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

/*! @} */
HEADER_END
#endif
