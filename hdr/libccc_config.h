/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_config.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_CONFIG_H
#define __LIBCCC_CONFIG_H
/*! @file libccc_config.h
**	This header defines all the primitive types and common macros to use.
**	@addtogroup libccc_config
**	@{
*/

// define 'extern C' header guards to prevent C++ compilers from doing symbol name mangling
#ifdef __cplusplus
	#ifndef HEADER_CPP
	#define HEADER_CPP	extern "C" {
	#endif
	#ifndef HEADER_END
	#define HEADER_END	}
	#endif
#else
	#ifndef HEADER_CPP
	#define HEADER_CPP	
	#endif
	#ifndef HEADER_END
	#define HEADER_END	
	#endif	
#endif

HEADER_CPP

/*
** ************************************************************************** *|
**                            Library Configuration                           *|
** ************************************************************************** *|
*/

//! Configures the typedef nomenclature style used by libccc
/*!
**	This macro sets the nomenclature style that libccc uses for typedefs. The value works like
**	both an enum and a bitflag simultaneously: you can see how this works at the bottom of this file.
**	NB: By default, this is (NAMINGSTYLE_ENUM_SNAKECASE | NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX)
**		This style is used thoughout libccc's code. As such, if you set another style, it
**		will actually a typedef alias above the existing type. For example:
**		Having NAMINGSTYLE_ENUM_SCREAMCASE will create a typedef for `t_u32` which is `U32`
*/
#define LIBCONFIG_NAMINGSTYLE_TYPES		(NAMINGSTYLE_ENUM_SNAKECASE | NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX)



//! If 1, libccc functions handle NULL pointers args, otherwise they segfault.
/*!
**	This macro determines how NULL pointer arguments are to be handled
**	If 0, then libccc functions will always segfault when given NULL pointers.
**	If 1, then all NULL pointer accesses in libccc functions will be avoided, and
**		an appropriate return value (eg:NULL, 0, sometimes -1) will be returned.
*/
#define LIBCONFIG_HANDLE_NULLPOINTERS		1



//! If 1, libccc will define its functions as simple inline wrappers for STD C calls.
/*!
**	This macro determines if the compiler should prefer function implementations
**	from the platform's standard library, or the implementation from libccc.
**	If 0, use libccc function implementations everywhere
**	If 1, call stdlib implementations rather than libccc wherever possible
**	NB: Setting this to 1 can make your code run faster, but it may introduce
**		undefined behaviors depending on the platform (for edge-case arguments).
**		Also, it invalidates the LIBCONFIG_HANDLE_NULLPOINTERS setting:
**		NULL pointer handling is implementation-dependent for STD C functions.
*/
#define LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS	0 // TODO implement this config flag



//! If 1, libccc uses its own fast-approximate math functions, otherwise it's the builtin FPU calls.
/*!
**	This macro determines which math function implementations should be used.
**	If 1, the libccc fast approximate functions will be used (precision error margin: 0.0001)
**	If 0, the builtin FPU-call libc math functions will be used (eg: __builtin_powf(), etc)
*/
#define LIBCONFIG_USE_FAST_APPROX_MATH		0



//! Defines which type/bit size the 't_uint' default unsigned integer type will be
/*!
**	This macro sets the default 't_uint' default unsigned integer type to use.
**	There are 5 possible accepted values for this #define:
**		8	for 8-bit uint	[0, 255]
**		16	for 16-bit uint	[0, 65535]
**		32	for 32-bit uint	[0, 2147483647]
**		64	for 64-bit uint	[0, 18446744073709551615]
**		128	for 128-bit uint (not present on all platforms)
*/
#define LIBCONFIG_BITS_UINT		32
#define LIBCONFIG_TYPE_UINT		t_u32

//! Defines which type/bit size the 't_sint' default signed integer type will be
/*!
**	This macro sets the default 't_sint' default signed integer type to use:
**	There are 5 possible accepted values for this #define:
**		8	for 8-bit int	[-128, 127]
**		16	for 16-bit int	[-32648, 32647]
**		32	for 32-bit int	[-2147483648, 2147483647]
**		64	for 64-bit int	[-9223372036854775808, +9223372036854775807]
**		128	for 128-bit int (not present on all platforms)
*/
#define LIBCONFIG_BITS_SINT		32
#define LIBCONFIG_TYPE_SINT		t_s32

//! Defines which type/bit size the 't_fixed' default fixed-point number type will be
/*!
**	The following macro sets what the 't_fixed' default fixed-point type should be.
**	There are 4 possible accepted values for this #define:
**		16	for 16-bit fixed-point number
**		32	for 32-bit fixed-point number
**		64	for 64-bit fixed-point number
**		128	for 128-bit fixed-point number (not present on all platforms)
*/
#define LIBCONFIG_BITS_FIXED	32
#define LIBCONFIG_TYPE_FIXED	t_g32
#define LIBCONFIG_BITS_FIXED_FRACTIONPART	(LIBCONFIG_BITS_FIXED / 4)
#define LIBCONFIG_BITS_FIXED_INTEGRALPART	(LIBCONFIG_BITS_FIXED - LIBCONFIG_BITS_FIXED_FRACTIONPART)

//! Defines which type/bit size the 't_float' default floating-point number type will be
/*!
**	The following macro sets what the 't_float' default floating-point type should be.
**	There are 4 possible accepted values for this #define:
**		32	for 32-bit IEEE 754 single-precision floating-point number
**		64	for 64-bit IEEE 754 double-precision floating-point number
**		80	for 80-bit x86 extended-precision floating-point number (not present on all platforms)
**		128	for 128-bit IEEE 754 quadruple-precision floating-point number (not present on all platforms)
*/
#define LIBCONFIG_BITS_FLOAT	32
#define LIBCONFIG_TYPE_FLOAT	t_f32



//! If 1, libccc uses exact bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro configures which stdint.h integer types are used by default,
**	as well as setting the corresponding appropriate [INT]_MAX and [INT]_MIN values.
**	There are 3 possible values for this #define:
**	(undefined)	EXACT: This is the default - uses the 'exact size' integer types (int8_t, etc)
**				This is the recommended option as it ensures consistent overflow behavior on ints.
**				Unfortunately, certain platforms do not have these types, so the others can also be of use.
**	_least		LEAST: Uses the smallest available integer type with at least 'n' bits (int_least8_t, etc)
**	_fast		FAST: Uses the fastest available integer type with at least 'n' bits (int_fast8_t, etc)
*/
//#define LIBCONFIG_INTEGER_TYPES _least // uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES _fast  // uncomment this line to use FAST int types



//! If 1, libccc will make the 't_complex' types use the STDC _Complex type
/*!
**	TODO implement & document this
*/
#define LIBCONFIG_USE_STD_COMPLEX		0



//! If 1, libccc will make the fixed point types 't_g*' and 't_fixed' use the STDC `_Sat _Accum` types
/*!
**	It is recommended to keep this set to 0, as the STD C fixed-point types are not yet standard
**	(ie: _Accum, _Fract, and _Sat are not present on all platforms, and only GCC implements them).
**	Furthermore, the libccc fixed-point type may not be as fast as a STD C implementation which
**	may leverage the platform's ASM, but it is configurable in terms of what portion of the
**	fixed-point number type is dedicated to the integral/fractional part.
*/
#define LIBCONFIG_USE_STD_FIXEDPOINT	0



//! If 1, doing `#include "libccc/array/list.h"` will define a doubly-linked list
/*!
**	This macro configures whether the `s_list` type is singly-linked or doubly-linked.
**	NB: This must be set BEFORE including the libccc/array/list.h header file
**	If 0, `s_list` is singly-linked (that is, the struct only holds a `.next` pointer)
**	If 1, `s_list` is doubly-linked (that is, the struct has both a `.prev` and `.next` pointer)
*/
#define LIBCONFIG_LIST_DOUBLYLINKED		0 // TODO



//! The item type used by the `s_list` struct (by default it is `void*`, ie: dynamic list).
/*
**	This macro sets the type for the item stored within each `s_list` element.
**	NB: This must be set BEFORE including the libccc/array/list.h header file
*/
#define LIBCONFIG_LIST_TYPE				void*	// TODO

//! The type name used by the linked-list type (by default it is `s_list`).
/*
**	This macro sets the typedef name for the linked-list struct (by default `s_list`).
**	NB: This must be set BEFORE including the libccc/array/list.h header file
*/
#define LIBCONFIG_LIST_NAME				s_list	// TODO



/*
** ************************************************************************** *|
**                          Naming-style configuration                        *|
** ************************************************************************** *|
*/

//! Naming-style enum region bitmask
#define NAMINGSTYLE_ENUM		0xF
// Naming-style enum values
#define NAMINGSTYLE_ENUM_CSTYLE		0	//!< lowercase & abbreviated:	`extype`
#define NAMINGSTYLE_ENUM_SNAKECASE	1	//!< lowercase & underscores:	`example_type`
#define NAMINGSTYLE_ENUM_CAMELCASE	2	//!< mixedcase (char 1 lower):	`exampleType`
#define NAMINGSTYLE_ENUM_PASCALCASE	3	//!< mixedcase (char 1 upper):	`ExampleType`
#define NAMINGSTYLE_ENUM_SCREAMCASE	4	//!< uppercase & underscores:	`EXAMPLE_TYPE`

// Naming-style boolean bitflags
#define NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX		(1 << 4)	//!< If 1, adds type prefix: `t_example_type`
#define NAMINGSTYLE_FLAG_HUNGARIAN_SUFFIX		(1 << 5)	//!< If 1, adds type suffix: `example_type_t`
#define NAMINGSTYLE_FLAG_HUNGARIAN_UPPERCASE	(1 << 6)	//!< If 1, hungarian prefix/suffix is uppercase

// Naming-style hungarian notation prefix/suffix (is prepended/appended with an underscore)
#if (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_FLAG_HUNGARIAN_UPPERCASE)
	#define HUNGARIAN_PRIMITIVE	T	//!< Hungarian type prefix/suffix for a primitive typedef
	#define HUNGARIAN_STRUCT	S	//!< Hungarian type prefix/suffix for a struct typedef
	#define HUNGARIAN_ENUM		E	//!< Hungarian type prefix/suffix for an enum typedef
	#define HUNGARIAN_UNION		U	//!< Hungarian type prefix/suffix for a union typedef
	#define HUNGARIAN_FUNCTION	F	//!< Hungarian type prefix/suffix for a function pointer typedef
#else
	#define HUNGARIAN_PRIMITIVE	t	//!< Hungarian type prefix/suffix for a primitive typedef
	#define HUNGARIAN_STRUCT	s	//!< Hungarian type prefix/suffix for a struct typedef
	#define HUNGARIAN_ENUM		e	//!< Hungarian type prefix/suffix for an enum typedef
	#define HUNGARIAN_UNION		u	//!< Hungarian type prefix/suffix for a union typedef
	#define HUNGARIAN_FUNCTION	f	//!< Hungarian type prefix/suffix for a function pointer typedef
#endif



#if	(LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_ENUM_SNAKECASE || \
	(LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_ENUM_CAMELCASE
	#define LIBCONFIG_TYPENAME_BOOL			bool
	#define LIBCONFIG_TYPENAME_CHAR			char
	#define LIBCONFIG_TYPENAME_UTF8			utf8
	#define LIBCONFIG_TYPENAME_SINT			sint
	#define LIBCONFIG_TYPENAME_SINT_8		s8
	#define LIBCONFIG_TYPENAME_SINT_16		s16
	#define LIBCONFIG_TYPENAME_SINT_32		s32
	#define LIBCONFIG_TYPENAME_SINT_64		s64
	#define LIBCONFIG_TYPENAME_SINT_128		s128
	#define LIBCONFIG_TYPENAME_UINT			uint
	#define LIBCONFIG_TYPENAME_UINT_8		u8
	#define LIBCONFIG_TYPENAME_UINT_16		u16
	#define LIBCONFIG_TYPENAME_UINT_32		u32
	#define LIBCONFIG_TYPENAME_UINT_64		u64
	#define LIBCONFIG_TYPENAME_UINT_128		u128
	#define LIBCONFIG_TYPENAME_FIXED		fixed
	#define LIBCONFIG_TYPENAME_FIXED_16		g16
	#define LIBCONFIG_TYPENAME_FIXED_32		g32
	#define LIBCONFIG_TYPENAME_FIXED_64		g64
	#define LIBCONFIG_TYPENAME_FIXED_128	g128
	#define LIBCONFIG_TYPENAME_FLOAT		float
	#define LIBCONFIG_TYPENAME_FLOAT_32		f32
	#define LIBCONFIG_TYPENAME_FLOAT_64		f64
	#define LIBCONFIG_TYPENAME_FLOAT_80		f80
	#define LIBCONFIG_TYPENAME_FLOAT_128	f128
	#define LIBCONFIG_TYPENAME_SIZE			size
	#define LIBCONFIG_TYPENAME_PTRDIFF		ptrdiff
	#define LIBCONFIG_TYPENAME_SINTMAX		sintmax
	#define LIBCONFIG_TYPENAME_UINTMAX		uintmax
	#define LIBCONFIG_TYPENAME_SINTPTR		sintptr
	#define LIBCONFIG_TYPENAME_UINTPTR		uintptr
	#define LIBCONFIG_TYPENAME_COLOR_RGB	argb
	#define LIBCONFIG_TYPENAME_COLOR_HSL	ahsl
	#define LIBCONFIG_TYPENAME_IO_FILEDESC	fd
	#define LIBCONFIG_TYPENAME_TIME			time
	#define LIBCONFIG_TYPENAME_TIMESPEC		timespec
	#define LIBCONFIG_TYPENAME_TIMEZONE		timezone
	#define LIBCONFIG_TYPENAME_TIME_DATE	date
	#define LIBCONFIG_TYPENAME_TIME_WEEKDAY	weekday
	#define LIBCONFIG_TYPENAME_TIME_MONTH	month
	#define LIBCONFIG_TYPENAME_VECTOR		vector
	#define LIBCONFIG_TYPENAME_VECTOR2D		vector2d
	#define LIBCONFIG_TYPENAME_VECTOR3D		vector3d
	#define LIBCONFIG_TYPENAME_VECTOR4D		vector4d
	#define LIBCONFIG_TYPENAME_MATRIX		matrix
	#define LIBCONFIG_TYPENAME_MATRIX2D		matrix2d
	#define LIBCONFIG_TYPENAME_MATRIX3D		matrix3d
	#define LIBCONFIG_TYPENAME_MATRIX4D		matrix4d
	#define LIBCONFIG_TYPENAME_TENSOR		tensor
	#define LIBCONFIG_TYPENAME_AABB			box
	#define LIBCONFIG_TYPENAME_INTERVAL		interval
	#define LIBCONFIG_TYPENAME_COMPLEX		complex
	#define LIBCONFIG_TYPENAME_QUATERNION	quaternion
	#define LIBCONFIG_TYPENAME_ARRAY		array
	#define LIBCONFIG_TYPENAME_LIST			list
	#define LIBCONFIG_TYPENAME_TREE			tree
	#define LIBCONFIG_TYPENAME_LEAF			leaf
	#define LIBCONFIG_TYPENAME_DICT			dict
	#define LIBCONFIG_TYPENAME_KEYVAL		keyval
	#define LIBCONFIG_TYPENAME_OBJECT		object

#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_ENUM_CSTYLE
	#define LIBCONFIG_TYPENAME_BOOL			bool
	#define LIBCONFIG_TYPENAME_CHAR			char
	#define LIBCONFIG_TYPENAME_UTF8			wchar
	#define LIBCONFIG_TYPENAME_SINT			int
	#define LIBCONFIG_TYPENAME_SINT_8		i8
	#define LIBCONFIG_TYPENAME_SINT_16		i16
	#define LIBCONFIG_TYPENAME_SINT_32		i32
	#define LIBCONFIG_TYPENAME_SINT_64		i64
	#define LIBCONFIG_TYPENAME_SINT_128		i128
	#define LIBCONFIG_TYPENAME_UINT			uint
	#define LIBCONFIG_TYPENAME_UINT_8		u8
	#define LIBCONFIG_TYPENAME_UINT_16		u16
	#define LIBCONFIG_TYPENAME_UINT_32		u32
	#define LIBCONFIG_TYPENAME_UINT_64		u64
	#define LIBCONFIG_TYPENAME_UINT_128		u128
	#define LIBCONFIG_TYPENAME_FIXED		fixed
	#define LIBCONFIG_TYPENAME_FIXED_16		k16
	#define LIBCONFIG_TYPENAME_FIXED_32		k32
	#define LIBCONFIG_TYPENAME_FIXED_64		k64
	#define LIBCONFIG_TYPENAME_FIXED_128	k128
	#define LIBCONFIG_TYPENAME_FLOAT		float
	#define LIBCONFIG_TYPENAME_FLOAT_32		f32
	#define LIBCONFIG_TYPENAME_FLOAT_64		f64
	#define LIBCONFIG_TYPENAME_FLOAT_80		f80
	#define LIBCONFIG_TYPENAME_FLOAT_128	f128
	#define LIBCONFIG_TYPENAME_SIZE			size
	#define LIBCONFIG_TYPENAME_PTRDIFF		ptrdiff
	#define LIBCONFIG_TYPENAME_SINTMAX		intmax
	#define LIBCONFIG_TYPENAME_UINTMAX		uintmax
	#define LIBCONFIG_TYPENAME_SINTPTR		intptr
	#define LIBCONFIG_TYPENAME_UINTPTR		uintptr
	#define LIBCONFIG_TYPENAME_COLOR_RGB	argb
	#define LIBCONFIG_TYPENAME_COLOR_HSL	ahsl
	#define LIBCONFIG_TYPENAME_IO_FILEDESC	fd
	#define LIBCONFIG_TYPENAME_TIME			time
	#define LIBCONFIG_TYPENAME_TIMESPEC		timespec
	#define LIBCONFIG_TYPENAME_TIMEZONE		tz
	#define LIBCONFIG_TYPENAME_TIME_DATE	tm
	#define LIBCONFIG_TYPENAME_TIME_WEEKDAY	week
	#define LIBCONFIG_TYPENAME_TIME_MONTH	month
	#define LIBCONFIG_TYPENAME_VECTOR		vec
	#define LIBCONFIG_TYPENAME_VECTOR2D		vec2
	#define LIBCONFIG_TYPENAME_VECTOR3D		vec3
	#define LIBCONFIG_TYPENAME_VECTOR4D		vec4
	#define LIBCONFIG_TYPENAME_MATRIX		matrix
	#define LIBCONFIG_TYPENAME_MATRIX2D		matrix2
	#define LIBCONFIG_TYPENAME_MATRIX3D		matrix3
	#define LIBCONFIG_TYPENAME_MATRIX4D		matrix4
	#define LIBCONFIG_TYPENAME_TENSOR		tensor
	#define LIBCONFIG_TYPENAME_AABB			box
	#define LIBCONFIG_TYPENAME_INTERVAL		interval
	#define LIBCONFIG_TYPENAME_COMPLEX		cplx
	#define LIBCONFIG_TYPENAME_QUATERNION	quat
	#define LIBCONFIG_TYPENAME_ARRAY		array
	#define LIBCONFIG_TYPENAME_LIST			list
	#define LIBCONFIG_TYPENAME_TREE			tree
	#define LIBCONFIG_TYPENAME_LEAF			leaf
	#define LIBCONFIG_TYPENAME_DICT			dict
	#define LIBCONFIG_TYPENAME_KEYVAL		keyval
	#define LIBCONFIG_TYPENAME_OBJECT		object

#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_ENUM_PASCALCASE
	#define LIBCONFIG_TYPENAME_BOOL			Bool
	#define LIBCONFIG_TYPENAME_CHAR			Char
	#define LIBCONFIG_TYPENAME_UTF8			UTF8
	#define LIBCONFIG_TYPENAME_SINT			SInt
	#define LIBCONFIG_TYPENAME_SINT_8		S8
	#define LIBCONFIG_TYPENAME_SINT_16		S16
	#define LIBCONFIG_TYPENAME_SINT_32		S32
	#define LIBCONFIG_TYPENAME_SINT_64		S64
	#define LIBCONFIG_TYPENAME_SINT_128		S128
	#define LIBCONFIG_TYPENAME_UINT			UInt
	#define LIBCONFIG_TYPENAME_UINT_8		U8
	#define LIBCONFIG_TYPENAME_UINT_16		U16
	#define LIBCONFIG_TYPENAME_UINT_32		U32
	#define LIBCONFIG_TYPENAME_UINT_64		U64
	#define LIBCONFIG_TYPENAME_UINT_128		U128
	#define LIBCONFIG_TYPENAME_FIXED		Fixed
	#define LIBCONFIG_TYPENAME_FIXED_16		G16
	#define LIBCONFIG_TYPENAME_FIXED_32		G32
	#define LIBCONFIG_TYPENAME_FIXED_64		G64
	#define LIBCONFIG_TYPENAME_FIXED_128	G128
	#define LIBCONFIG_TYPENAME_FLOAT		Float
	#define LIBCONFIG_TYPENAME_FLOAT_32		F32
	#define LIBCONFIG_TYPENAME_FLOAT_64		F64
	#define LIBCONFIG_TYPENAME_FLOAT_80		F80
	#define LIBCONFIG_TYPENAME_FLOAT_128	F128
	#define LIBCONFIG_TYPENAME_SIZE			Size
	#define LIBCONFIG_TYPENAME_PTRDIFF		PtrDiff
	#define LIBCONFIG_TYPENAME_SINTMAX		SIntMax
	#define LIBCONFIG_TYPENAME_UINTMAX		UIntMax
	#define LIBCONFIG_TYPENAME_SINTPTR		SIntPtr
	#define LIBCONFIG_TYPENAME_UINTPTR		UIntPtr
	#define LIBCONFIG_TYPENAME_COLOR_RGB	ARGB
	#define LIBCONFIG_TYPENAME_COLOR_HSL	AHSL
	#define LIBCONFIG_TYPENAME_IO_FILEDESC	FileDesc
	#define LIBCONFIG_TYPENAME_TIME			Time
	#define LIBCONFIG_TYPENAME_TIMESPEC		TimeSpec
	#define LIBCONFIG_TYPENAME_TIMEZONE		TimeZone
	#define LIBCONFIG_TYPENAME_TIME_DATE	Date
	#define LIBCONFIG_TYPENAME_TIME_WEEKDAY	WeekDay
	#define LIBCONFIG_TYPENAME_TIME_MONTH	Month
	#define LIBCONFIG_TYPENAME_VECTOR		Vector
	#define LIBCONFIG_TYPENAME_VECTOR2D		Vector2D
	#define LIBCONFIG_TYPENAME_VECTOR3D		Vector3D
	#define LIBCONFIG_TYPENAME_VECTOR4D		Vector4D
	#define LIBCONFIG_TYPENAME_MATRIX		Matrix
	#define LIBCONFIG_TYPENAME_MATRIX2D		Matrix2D
	#define LIBCONFIG_TYPENAME_MATRIX3D		Matrix3D
	#define LIBCONFIG_TYPENAME_MATRIX4D		Matrix4D
	#define LIBCONFIG_TYPENAME_TENSOR		Tensor
	#define LIBCONFIG_TYPENAME_AABB			Box
	#define LIBCONFIG_TYPENAME_INTERVAL		Interval
	#define LIBCONFIG_TYPENAME_COMPLEX		Complex
	#define LIBCONFIG_TYPENAME_QUATERNION	Quaternion
	#define LIBCONFIG_TYPENAME_ARRAY		Array
	#define LIBCONFIG_TYPENAME_LIST			List
	#define LIBCONFIG_TYPENAME_TREE			Tree
	#define LIBCONFIG_TYPENAME_LEAF			Leaf
	#define LIBCONFIG_TYPENAME_DICT			Dict
	#define LIBCONFIG_TYPENAME_KEYVAL		KeyVal
	#define LIBCONFIG_TYPENAME_OBJECT		Object

#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_ENUM_SCREAMCASE
	#define LIBCONFIG_TYPENAME_BOOL			BOOL
	#define LIBCONFIG_TYPENAME_CHAR			CHAR
	#define LIBCONFIG_TYPENAME_UTF8			UTF8
	#define LIBCONFIG_TYPENAME_SINT			SINT
	#define LIBCONFIG_TYPENAME_SINT_8		S8
	#define LIBCONFIG_TYPENAME_SINT_16		S16
	#define LIBCONFIG_TYPENAME_SINT_32		S32
	#define LIBCONFIG_TYPENAME_SINT_64		S64
	#define LIBCONFIG_TYPENAME_SINT_128		S128
	#define LIBCONFIG_TYPENAME_UINT			UINT
	#define LIBCONFIG_TYPENAME_UINT_8		U8
	#define LIBCONFIG_TYPENAME_UINT_16		U16
	#define LIBCONFIG_TYPENAME_UINT_32		U32
	#define LIBCONFIG_TYPENAME_UINT_64		U64
	#define LIBCONFIG_TYPENAME_UINT_128		U128
	#define LIBCONFIG_TYPENAME_FIXED		FIXED
	#define LIBCONFIG_TYPENAME_FIXED_16		G16
	#define LIBCONFIG_TYPENAME_FIXED_32		G32
	#define LIBCONFIG_TYPENAME_FIXED_64		G64
	#define LIBCONFIG_TYPENAME_FIXED_128	G128
	#define LIBCONFIG_TYPENAME_FLOAT		FLOAT
	#define LIBCONFIG_TYPENAME_FLOAT_32		F32
	#define LIBCONFIG_TYPENAME_FLOAT_64		F64
	#define LIBCONFIG_TYPENAME_FLOAT_80		F80
	#define LIBCONFIG_TYPENAME_FLOAT_128	F128
	#define LIBCONFIG_TYPENAME_SIZE			SIZE
	#define LIBCONFIG_TYPENAME_PTRDIFF		PTRDIFF
	#define LIBCONFIG_TYPENAME_SINTMAX		SINTMAX
	#define LIBCONFIG_TYPENAME_UINTMAX		UINTMAX
	#define LIBCONFIG_TYPENAME_SINTPTR		SINTPTR
	#define LIBCONFIG_TYPENAME_UINTPTR		UINTPTR
	#define LIBCONFIG_TYPENAME_COLOR_RGB	ARGB
	#define LIBCONFIG_TYPENAME_COLOR_HSL	AHSL
	#define LIBCONFIG_TYPENAME_IO_FILEDESC	FD
	#define LIBCONFIG_TYPENAME_TIME			TIME
	#define LIBCONFIG_TYPENAME_TIMESPEC		TIMESPEC
	#define LIBCONFIG_TYPENAME_TIMEZONE		TIMEZONE
	#define LIBCONFIG_TYPENAME_TIME_DATE	DATE
	#define LIBCONFIG_TYPENAME_TIME_WEEKDAY	WEEKDAY
	#define LIBCONFIG_TYPENAME_TIME_MONTH	MONTH
	#define LIBCONFIG_TYPENAME_VECTOR		VECTOR
	#define LIBCONFIG_TYPENAME_VECTOR2D		VECTOR2D
	#define LIBCONFIG_TYPENAME_VECTOR3D		VECTOR3D
	#define LIBCONFIG_TYPENAME_VECTOR4D		VECTOR4D
	#define LIBCONFIG_TYPENAME_MATRIX		MATRIX
	#define LIBCONFIG_TYPENAME_MATRIX2D		MATRIX2D
	#define LIBCONFIG_TYPENAME_MATRIX3D		MATRIX3D
	#define LIBCONFIG_TYPENAME_MATRIX4D		MATRIX4D
	#define LIBCONFIG_TYPENAME_TENSOR		TENSOR
	#define LIBCONFIG_TYPENAME_AABB			BOX
	#define LIBCONFIG_TYPENAME_INTERVAL		INTERVAL
	#define LIBCONFIG_TYPENAME_COMPLEX		COMPLEX
	#define LIBCONFIG_TYPENAME_QUATERNION	QUATERNION
	#define LIBCONFIG_TYPENAME_ARRAY		ARRAY
	#define LIBCONFIG_TYPENAME_LIST			LIST
	#define LIBCONFIG_TYPENAME_TREE			TREE
	#define LIBCONFIG_TYPENAME_LEAF			LEAF
	#define LIBCONFIG_TYPENAME_DICT			DICT
	#define LIBCONFIG_TYPENAME_KEYVAL		KEYVAL
	#define LIBCONFIG_TYPENAME_OBJECT		OBJECT

#else
	#error "Invalid naming-style enum selected: change your LIBCONFIG_NAMINGSTYLE_TYPES setting."
#endif



#define TYPEDEF_ALIAS(TYPE, NAME, KIND) \
		TYPEDEF_ALIAS_(TYPE, LIBCONFIG_TYPENAME_##NAME, HUNGARIAN_##KIND)

#if (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX) && \
	(LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_FLAG_HUNGARIAN_SUFFIX)
	#error "Cannot have both prefix and suffix set to 1 for type name: change your LIBCONFIG_NAMINGSTYLE_TYPES setting."
#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX)
	#define TYPEDEF_ALIAS_(TYPE, NAME, KIND)	TYPEDEF_ALIAS_WITH_PREFIX(TYPE, NAME, CONCAT(KIND, _))
#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_FLAG_HUNGARIAN_SUFFIX)
	#define TYPEDEF_ALIAS_(TYPE, NAME, KIND)	TYPEDEF_ALIAS_WITH_SUFFIX(TYPE, NAME, CONCAT(_, KIND))
#else
	#define TYPEDEF_ALIAS_(TYPE, NAME, KIND)	TYPEDEF_ALIAS_WITH_NONE(TYPE, NAME)
#endif

#define TYPEDEF_ALIAS_WITH_PREFIX(TYPE, NAME, PREFIX)	typedef TYPE	CONCAT(PREFIX, NAME);
#define TYPEDEF_ALIAS_WITH_SUFFIX(TYPE, NAME, SUFFIX)	typedef TYPE	CONCAT(NAME, SUFFIX);
#define TYPEDEF_ALIAS_WITH_NONE(TYPE, NAME)				typedef TYPE	NAME;



/*! @} */
HEADER_END
#endif
