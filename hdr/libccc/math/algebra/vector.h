/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/algebra/vector.h             |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_ALGEBRA_VECTOR_H
#define __LIBCCC_MATH_ALGEBRA_VECTOR_H
/*!@group{libccc_math_algebra_vector,61,libccc/math/algebra/vector.h}
**
**	This header defines vector types and functions, in several dimensions (2d/3d/4d, and generic N-dimensional)
*/
// TODO add other function macros for integral, distance, etc

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/math/float.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc A simple vector struct for storing 2-dimensional values
//!@{
typedef struct vec2d
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
}				s_vector2d;
TYPEDEF_ALIAS(	s_vector2d, VECTOR_2D, STRUCT)
//!@}

//!@doc This union stores a 2-dimensional value which can be accessed in several ways
//!@{
typedef	union vector2d
{
	t_float		values[2];	//!< An array, to access the 2 values from within brackets
	s_vector2d	vector;		//!< A vector, to access the 2 coordinates as `.x` and `.y`
}				u_vector2d;
TYPEDEF_ALIAS(	u_vector2d, VECTOR_2D, UNION)
//!@}
//! The default/null value for a #s_vector2d (all fields set to zero)
#define VECTOR2D_NULL	(s_vector2d){ .x = 0, .y = 0 } 



//!@doc A simple vector struct for storing 3-dimensional values
//!@{
typedef struct vec3d
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
	t_float		z;			//!< The Z axis coordinate of this vector
}				s_vector3d;
TYPEDEF_ALIAS(	s_vector3d, VECTOR_3D, STRUCT)
//!@}

//!@doc This union stores a 3-dimensional value which can be accessed in several ways
//!@{
typedef	union vector3d
{
	t_float		values[3];	//!< An array, to access the 3 values from within brackets
	s_vector3d	vector;		//!< A vector, to access the 3 coordinates as `.x`, `.y` and `.z`
}				u_vector3d;
TYPEDEF_ALIAS(	u_vector3d, VECTOR_3D, UNION)
//!@}
//! The default/null value for a #s_vector3d (all fields set to zero)
#define VECTOR3D_NULL	(s_vector3d){ .x = 0, .y = 0, .z = 0 }



//!@doc A simple vector struct for storing 4-dimensional values
//!@{
typedef struct vec4d
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
	t_float		z;			//!< The Z axis coordinate of this vector
	t_float		t;			//!< The T axis coordinate of this vector
}				s_vector4d;
TYPEDEF_ALIAS(	s_vector4d, VECTOR_4D, STRUCT)
//!@}

//!@doc This union stores a 4-dimensional value which can be accessed in several ways
//!@{
typedef	union vector4d
{
	t_float		values[4];	//!< An array, to access the 4 values from within brackets
	s_vector4d	vector;		//!< A vector, to access the 4 coordinates as `.x`, `.y`, `.z`, and `.t`
}				u_vector4d;
TYPEDEF_ALIAS(	u_vector4d, VECTOR_4D, UNION)
//!@}
//! The default/null value for a #s_vector4d (all fields set to zero)
#define VECTOR4D_NULL	(s_vector4d){ .x = 0, .y = 0, .z = 0, .t = 0 } 



//!@doc A vector struct for storing generic N-dimensional values (the amount of dimensions is stored at runtime)
/*!
**	Unlike the fixed-size vector structs above, this struct holds its coordinate
**	values in a heap-allocated array buffer, whose size is only known at runtime.
**	As such, any #s_vector created via the Vector() or Vector_New() constructor
**	functions must be freed appropriately, by calling Vector_Free() or Vector_Delete().
*/
//!@{
typedef struct vector
{
	t_uint		dims;		//!< The amount of dimensions/coordinates stored in this vector
	t_float*	values;		//!< The array which holds the `dims` coordinate values of this vector
}				s_vector;
TYPEDEF_ALIAS(	s_vector, VECTOR, STRUCT)
//!@}
//! The default/null value for a #s_vector (zero dimensions, with no allocated buffer)
#define VECTOR_NULL	(s_vector){ .dims = 0, .values = NULL } 



/*============================================================================*\
||                        2-dimensional Vector Operations                     ||
\*============================================================================*/

//!@doc Returns a vector struct, with the given coordinates
//!@{
s_vector2d				Vector2D(t_float x, t_float y);
#define c_vec2			Vector2D
//!@}

//!@doc Allocates a new vector struct on heap, with the given coordinates
//!@{
_MALLOC()
s_vector2d*				Vector2D_New(t_float x, t_float y);
#define c_vec2new		Vector2D_New
//!@}



//!@doc Returns `TRUE` if the two given vectors are equal (all their values are identical)
//!@{
t_bool					Vector2D_Equals(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2equ		Vector2D_Equals
//!@}

//!@doc Scales the given `vector` by a factor of `scale`
//!@{
s_vector2d				Vector2D_Scale(s_vector2d const* vector, t_float scale);
#define c_vec2scale		Vector2D_Scale
//!@}

//!@doc Inverts the sign of the coordinates of the given `vector`
//!@{
s_vector2d					Vector2D_Invert(s_vector2d const* vector);
#define c_vec2invert		Vector2D_Invert
//!@}

//!@doc Returns the norm/magnitude of the given `vector`, squared (call Math_SquareRoot() to get the real norm)
//!@{
t_float						Vector2D_Norm(s_vector2d const* vector);
#define c_vec2norm			Vector2D_Norm
#define Vector2D_Length		Vector2D_Norm
#define Vector2D_Magnitude	Vector2D_Norm
//!@}

//!@doc Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
//!@{
s_vector2d					Vector2D_Normalize(s_vector2d const* vector);
#define c_vec2normalize		Vector2D_Normalize
//!@}



//!@doc Returns the sum of the two given vectors (adding each of their coordinates together)
//!@{
s_vector2d						Vector2D_Add(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2add				Vector2D_Add
//!@}

//!@doc Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
//!@{
t_float							Vector2D_Dot(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2dot				Vector2D_Dot
#define Vector2D_DotProduct		Vector2D_Dot
#define Vector2D_InnerProduct	Vector2D_Dot
#define Vector2D_ScalarProduct	Vector2D_Dot
//!@}



/*============================================================================*\
||                        3-dimensional Vector Operations                     ||
\*============================================================================*/

//!@doc Returns a vector struct, with the given coordinates
//!@{
s_vector3d			Vector3D(t_float x, t_float y, t_float z);
#define c_vec3		Vector3D
//!@}

//!@doc Allocates a new vector struct, with the given coordinates
//!@{
_MALLOC()
s_vector3d*			Vector3D_New(t_float x, t_float y, t_float z);
#define c_vec3new	Vector3D_New
//!@}



//!@doc Returns `TRUE` if the two given vectors are equal (all their values are identical)
//!@{
t_bool					Vector3D_Equals(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3equ		Vector3D_Equals
//!@}

//!@doc Scales the given `vector` by a factor of `scale`
//!@{
s_vector3d				Vector3D_Scale(s_vector3d const* vector, t_float scale);
#define c_vec3scale		Vector3D_Scale
//!@}

//!@doc Inverts the sign of the coordinates of the given `vector`
//!@{
s_vector3d					Vector3D_Invert(s_vector3d const* vector);
#define c_vec3invert		Vector3D_Invert
//!@}

//!@doc Returns the norm/magnitude of the given `vector`, squared (call sqrt to get the real norm)
//!@{
t_float						Vector3D_Norm(s_vector3d const* vector);
#define c_vec3norm			Vector3D_Norm
#define Vector3D_Length		Vector3D_Norm
#define Vector3D_Magnitude	Vector3D_Norm
//!@}

//!@doc Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
//!@{
s_vector3d					Vector3D_Normalize(s_vector3d const* vector);
#define c_vec3normalize		Vector3D_Normalize
//!@}



//!@doc Returns the sum of the two given vectors (adding each of their coordinates together)
//!@{
s_vector3d						Vector3D_Add(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3add				Vector3D_Add
//!@}

//!@doc Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
//!@{
t_float							Vector3D_Dot(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3dot				Vector3D_Dot
#define Vector3D_DotProduct		Vector3D_Dot
#define Vector3D_InnerProduct	Vector3D_Dot
#define Vector3D_ScalarProduct	Vector3D_Dot
//!@}

//!@doc Returns the cross/vector product of the two given vectors (the vector which is perpendicular to both)
//!@{
s_vector3d						Vector3D_Cross(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3cross				Vector3D_Cross
#define Vector3D_CrossProduct	Vector3D_Cross
#define Vector3D_OuterProduct	Vector3D_Cross
#define Vector3D_VectorProduct	Vector3D_Cross
//!@}



/*============================================================================*\
||                        4-dimensional Vector Operations                     ||
\*============================================================================*/

//!@doc Returns a vector struct, with the given coordinates
//!@{
s_vector4d			Vector4D(t_float x, t_float y, t_float z, t_float t);
#define c_vec4		Vector4D
//!@}

//!@doc Allocates a new vector struct, with the given coordinates
//!@{
_MALLOC()
s_vector4d*			Vector4D_New(t_float x, t_float y, t_float z, t_float t);
#define c_vec4new	Vector4D_New
//!@}



//!@doc Returns `TRUE` if the two given vectors are equal (all their values are identical)
//!@{
t_bool					Vector4D_Equals(s_vector4d const* v1, s_vector4d const* v2);
#define c_vec4equ		Vector4D_Equals
//!@}

//!@doc Scales the given `vector` by a factor of `scale`
//!@{
s_vector4d				Vector4D_Scale(s_vector4d const* vector, t_float scale);
#define c_vec4scale		Vector4D_Scale
//!@}

//!@doc Inverts the sign of the coordinates of the given `vector`
//!@{
s_vector4d					Vector4D_Invert(s_vector4d const* vector);
#define c_vec4invert		Vector4D_Invert
//!@}

//!@doc Returns the norm/magnitude of the given `vector`, squared (call sqrt to get the real norm)
//!@{
t_float						Vector4D_Norm(s_vector4d const* vector);
#define c_vec4norm			Vector4D_Norm
#define Vector4D_Length		Vector4D_Norm
#define Vector4D_Magnitude	Vector4D_Norm
//!@}

//!@doc Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
//!@{
s_vector4d					Vector4D_Normalize(s_vector4d const* vector);
#define c_vec4normalize		Vector4D_Normalize
//!@}



//!@doc Returns the sum of the two given vectors (adding each of their coordinates together)
//!@{
s_vector4d						Vector4D_Add(s_vector4d const* v1, s_vector4d const* v2);
#define c_vec4add				Vector4D_Add
//!@}

//!@doc Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
//!@{
t_float							Vector4D_Dot(s_vector4d const* v1, s_vector4d const* v2);
#define c_vec4dot				Vector4D_Dot
#define Vector4D_DotProduct		Vector4D_Dot
#define Vector4D_InnerProduct	Vector4D_Dot
#define Vector4D_ScalarProduct	Vector4D_Dot
//!@}



/*============================================================================*\
||                        N-dimensional Vector Operations                     ||
\*============================================================================*/

//!@doc Returns a vector struct of the given amount of dimensions `dims`, allocating its `values` buffer
/*!
**	@param	dims	The amount of dimensions/coordinates for the new vector
**	@param	values	The array of coordinate values to copy into the new vector (if `NULL`, the vector is zero-filled)
**	@returns a new vector struct (its `values` buffer must be freed by calling Vector_Free())
*/
//!@{
s_vector			Vector(t_uint dims, t_float const* values);
#define c_vec		Vector
//!@}

//!@doc Allocates a new vector struct on heap, with the given amount of dimensions `dims`
/*!
**	@param	dims	The amount of dimensions/coordinates for the new vector
**	@param	values	The array of coordinate values to copy into the new vector (if `NULL`, the vector is zero-filled)
**	@returns a newly allocated vector struct (must be freed by calling Vector_Delete())
*/
//!@{
_MALLOC()
s_vector*			Vector_New(t_uint dims, t_float const* values);
#define c_vecnew	Vector_New
//!@}

//!@doc Returns a newly allocated copy of the given `vector`
//!@{
s_vector			Vector_Duplicate(s_vector const* vector);
#define c_vecdup	Vector_Duplicate
//!@}

//!@doc Deallocates the `values` buffer of the given `vector` (and sets its fields to zero)
//!@{
void				Vector_Free(s_vector* vector);
#define c_vecfree	Vector_Free
//!@}

//!@doc Deallocates the given heap-allocated `vector` (its `values` buffer, and the struct itself)
//!@{
void				Vector_Delete(s_vector* *a_vector);
#define c_vecdel	Vector_Delete
//!@}



//!@doc Returns `TRUE` if the two given vectors are equal (same dimensions, and all their values are identical)
//!@{
t_bool				Vector_Equals(s_vector const* v1, s_vector const* v2);
#define c_vecequ	Vector_Equals
//!@}

//!@doc Scales the given `vector` by a factor of `scale`
//!@{
s_vector			Vector_Scale(s_vector const* vector, t_float scale);
#define c_vecscale	Vector_Scale
//!@}

//!@doc Inverts the sign of the coordinates of the given `vector`
//!@{
s_vector				Vector_Invert(s_vector const* vector);
#define c_vecinvert		Vector_Invert
//!@}

//!@doc Returns the norm/magnitude of the given `vector`, squared (call sqrt to get the real norm)
//!@{
t_float					Vector_Norm(s_vector const* vector);
#define c_vecnorm		Vector_Norm
#define Vector_Length	Vector_Norm
#define Vector_Magnitude	Vector_Norm
//!@}

//!@doc Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
//!@{
s_vector				Vector_Normalize(s_vector const* vector);
#define c_vecnormalize	Vector_Normalize
//!@}



//!@doc Returns the sum of the two given vectors (adding each of their coordinates together)
/*!
**	@returns #VECTOR_NULL if the two given vectors do not have the same amount of dimensions
*/
//!@{
s_vector					Vector_Add(s_vector const* v1, s_vector const* v2);
#define c_vecadd			Vector_Add
//!@}

//!@doc Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
/*!
**	@returns `0` if the two given vectors do not have the same amount of dimensions
*/
//!@{
t_float						Vector_Dot(s_vector const* v1, s_vector const* v2);
#define c_vecdot			Vector_Dot
#define Vector_DotProduct	Vector_Dot
#define Vector_InnerProduct	Vector_Dot
#define Vector_ScalarProduct	Vector_Dot
//!@}



/*! @endgroup */
HEADER_END
#endif
