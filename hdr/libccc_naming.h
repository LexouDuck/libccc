/*============================================================================*\
||                                            ______________________________  ||
||  libccc_naming.h                          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_NAMING_H
#define __LIBCCC_NAMING_H
/*!@group{libccc_naming,5,libccc_naming.h}
**
**	This header defines alternate versions of all the type names of libccc.
**	This allows any user to have type names use the nomenclature style of their
**	choice, by simply changing one configuration macro: #LIBCONFIG_NAMINGSTYLE_TYPES
**
**	Here is a description of the nomenclature conventions used by libccc:
**	`snake_case`	for local variables, struct/union members, and types
**	`PascalCase`	for global variables, function names (there are also snake case c-style aliases)
**	`SCREAMCASE`	for macros, enum items
**	`__HEADER_H`	for header include guards
**	`__DEFINE__`	for macros defined outside the code (eg: by the compiler/environment)
**
**	The naming convention for types is to always use a prefix to show its kind.
**	These prefixes are always one letter followed by an underscore character.
**	There are five such type prefixes that libccc uses:
**		- `t_` for a typedef on a primitive type	ex: `typedef t_u32 t_color; t_color a = 0;`
**		- `s_` for a typedef on a struct			ex: `s_point pos = { .x = 0, .y = 0 };`
**		- `e_` for a typedef on an enum				ex: `e_httperror code = ERROR_HTTP_404;`
**		- `u_` for a typedef on a union type		ex: `typedef union color { t_u8 channels[4]; t_u32 argb; } u_color;`
**		- `f_` for a typedef on a function pointer	ex: `typedef char (*f_strmapi)(char c, t_size index);`
**		- `p_` for a typedef which hides a pointer	ex: `typedef char* p_string;`
**	This also allows most any text editor's syntax coloring to be able to match and color
**	any user-defined typedefs, with a very simple regular expression:
**		`\b([tseufp]_\w+)\b`
**	Additionnally, libccc provides function aliases which follow the C standard library's
**	nomenclature style - to avoid clashing with existing names, these are prefixed with `c_`.
**	For example, the C `memset()` function is named Memory_Set() in libccc, and has an alias c_memset().
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                          Naming-style configuration                        *|
** ************************************************************************** *|
*/

//! Naming-style enum region bitmask
#define NAMINGSTYLE_ENUM		0xF
//! Naming-style enum values
//!@{
#define NAMINGSTYLE_CSTYLE		0	//!< lowercase & abbreviated:	`extype`
#define NAMINGSTYLE_SNAKECASE	1	//!< lowercase & underscores:	`example_type`
#define NAMINGSTYLE_CAMELCASE	2	//!< mixedcase (char 1 lower):	`exampleType`
#define NAMINGSTYLE_PASCALCASE	3	//!< mixedcase (char 1 upper):	`ExampleType`
#define NAMINGSTYLE_SCREAMCASE	4	//!< uppercase & underscores:	`EXAMPLE_TYPE`
//!@}

//! Naming-style boolean bitflags
//!@{
#define NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX		(1 << 4)	//!< If 1, adds type prefix: `t_example_type`
#define NAMINGSTYLE_FLAG_HUNGARIAN_SUFFIX		(1 << 5)	//!< If 1, adds type suffix: `example_type_t`
#define NAMINGSTYLE_FLAG_HUNGARIAN_UPPERCASE	(1 << 6)	//!< If 1, hungarian prefix/suffix is uppercase
//!@}

//! Naming-style hungarian notation prefix/suffix (is prepended/appended with an underscore)
//!@{
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
//!@}


#if (LIBCONFIG_NAMINGSTYLE_TYPES == 0)

	#define TYPEDEF_ALIAS(TYPE, NAME, KIND) \



#else



	#if	(LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_SNAKECASE || \
		(LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_CAMELCASE
		#define LIBCONFIG_TYPENAME_CHAR			char
		#define LIBCONFIG_TYPENAME_ASCII		ascii
		#define LIBCONFIG_TYPENAME_UTF_8		utf8
		#define LIBCONFIG_TYPENAME_UTF_16		utf16
		#define LIBCONFIG_TYPENAME_UTF_32		utf32
		#define LIBCONFIG_TYPENAME_BOOL			bool
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
		#define LIBCONFIG_TYPENAME_FIXED_16		q16
		#define LIBCONFIG_TYPENAME_FIXED_32		q32
		#define LIBCONFIG_TYPENAME_FIXED_64		q64
		#define LIBCONFIG_TYPENAME_FIXED_128	q128
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
		#define LIBCONFIG_TYPENAME_IO_MODE		io_mode
		#define LIBCONFIG_TYPENAME_IO_OPEN		io_open
		#define LIBCONFIG_TYPENAME_IO_ERROR		io_error
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

	#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_CSTYLE
		#define LIBCONFIG_TYPENAME_CHAR			char
		#define LIBCONFIG_TYPENAME_ASCII		ascii
		#define LIBCONFIG_TYPENAME_UTF_8		utf8
		#define LIBCONFIG_TYPENAME_UTF_16		utf16
		#define LIBCONFIG_TYPENAME_UTF_32		utf32
		#define LIBCONFIG_TYPENAME_BOOL			bool
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
		#define LIBCONFIG_TYPENAME_IO_MODE		io_mode
		#define LIBCONFIG_TYPENAME_IO_OPEN		io_open
		#define LIBCONFIG_TYPENAME_IO_ERROR		io_errno
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

	#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_PASCALCASE
		#define LIBCONFIG_TYPENAME_CHAR			Char
		#define LIBCONFIG_TYPENAME_ASCII		ASCII
		#define LIBCONFIG_TYPENAME_UTF_8		UTF8
		#define LIBCONFIG_TYPENAME_UTF_16		UTF16
		#define LIBCONFIG_TYPENAME_UTF_32		UTF32
		#define LIBCONFIG_TYPENAME_BOOL			Bool
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
		#define LIBCONFIG_TYPENAME_FIXED_16		Q16
		#define LIBCONFIG_TYPENAME_FIXED_32		Q32
		#define LIBCONFIG_TYPENAME_FIXED_64		Q64
		#define LIBCONFIG_TYPENAME_FIXED_128	Q128
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
		#define LIBCONFIG_TYPENAME_COLOR_RGB	ColorARGB
		#define LIBCONFIG_TYPENAME_COLOR_HSL	ColorAHSL
		#define LIBCONFIG_TYPENAME_IO_FILEDESC	FileDesc
		#define LIBCONFIG_TYPENAME_IO_MODE		IO_Mode
		#define LIBCONFIG_TYPENAME_IO_OPEN		IO_Open
		#define LIBCONFIG_TYPENAME_IO_ERROR		IO_Error
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

	#elif (LIBCONFIG_NAMINGSTYLE_TYPES & NAMINGSTYLE_ENUM) == NAMINGSTYLE_SCREAMCASE
		#define LIBCONFIG_TYPENAME_CHAR			CHAR
		#define LIBCONFIG_TYPENAME_ASCII		ASCII
		#define LIBCONFIG_TYPENAME_UTF_8		UTF8
		#define LIBCONFIG_TYPENAME_UTF_16		UTF16
		#define LIBCONFIG_TYPENAME_UTF_32		UTF32
		#define LIBCONFIG_TYPENAME_BOOL			BOOL
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
		#define LIBCONFIG_TYPENAME_IO_MODE		IO_MODE
		#define LIBCONFIG_TYPENAME_IO_OPEN		IO_OPEN
		#define LIBCONFIG_TYPENAME_IO_ERROR		IO_ERROR
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

#endif



/*! @endgroup */
HEADER_END
#endif
