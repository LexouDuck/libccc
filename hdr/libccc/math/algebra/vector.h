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
/*!@group{libccc_math_algebra_vector}
** @{
**	This header defines vector type and functions, in several dimensions (2d/3d/4d)
**
**	@file
*/
// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/math/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A simple vector struct for storing 2-dimensional values
typedef struct vec2d
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
}				s_vector2d;
TYPEDEF_ALIAS(	s_vector2d, VECTOR_2D, STRUCT)

//! This union stores a 2-dimensional value which can be accessed in several ways
typedef	union vector2d
{
	t_float		values[2];	//!< An array, to access the 2 values from within brackets
	s_vector2d	vector;		//!< A vector, to access the 2 coordinates as `.x` and `.y`
}				u_vector2d;
TYPEDEF_ALIAS(	u_vector2d, VECTOR_2D, UNION)

#define VECTOR2D_NULL	(s_vector2d){ .x = 0, .y = 0 } 



//! A simple vector struct for storing 3-dimensional values
typedef struct vec3d
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
	t_float		z;			//!< The Z axis coordinate of this vector
}				s_vector3d;
TYPEDEF_ALIAS(	s_vector3d, VECTOR_3D, STRUCT)

//! This union stores a 3-dimensional value which can be accessed in several ways
typedef	union vector3d
{
	t_float		values[3];	//!< An array, to access the 3 values from within brackets
	s_vector3d	vector;		//!< A vector, to access the 3 coordinates as `.x`, `.y` and `.z`
}				u_vector3d;
TYPEDEF_ALIAS(	u_vector3d, VECTOR_3D, UNION)

#define VECTOR3D_NULL	(s_vector3d){ .x = 0, .y = 0, .z = 0 }



//! A simple vector struct for storing 4-dimensional values
typedef struct vec4d
{
	t_float		x;			//!<< The X axis coordinate of this vector
	t_float		y;			//!<< The Y axis coordinate of this vector
	t_float		z;			//!<< The Z axis coordinate of this vector
	t_float		t;			//!<< The T axis coordinate of this vector
}				s_vector4d;
TYPEDEF_ALIAS(	s_vector4d, VECTOR_4D, STRUCT)

//! This union stores a 4-dimensional value which can be accessed in several ways
typedef	union vector4d
{
	t_float		values[4];	//!< An array, to access the 4 values from within brackets
	s_vector4d	vector;		//!< A vector, to access the 4 coordinates as `.x`, `.y`, `.z`, and `.t`
}				u_vector4d;
TYPEDEF_ALIAS(	u_vector4d, VECTOR_4D, UNION)

#define VECTOR4D_NULL	(s_vector4d){ .x = 0, .y = 0, .z = 0, .t = 0 } 



/*
** ************************************************************************** *|
**                        2-dimensional Vector Operations                     *|
** ************************************************************************** *|
*/

//! Returns a vector struct, with the given coordinates
s_vector2d				Vector2D(t_float x, t_float y);
#define c_vec2			Vector2D

//! Allocates a new vector struct on heap, with the given coordinates
_MALLOC()
s_vector2d*				Vector2D_New(t_float x, t_float y);
#define c_vec2new		Vector2D_New



//! Returns `TRUE` if the two given vectors are equal (all their values are identical)
t_bool					Vector2D_Equals(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2equ		Vector2D_Equals

//! Scales the given `vector` by a factor of `scale`
s_vector2d				Vector2D_Scale(s_vector2d const* vector, t_float scale);
#define c_vec2scale		Vector2D_Scale

//! Inverts the sign of the coordinates of the given `vector`
s_vector2d					Vector2D_Invert(s_vector2d const* vector);
#define c_vec2invert		Vector2D_Invert

//! Returns the norm/magnitude of the given `vector`, squared (call Math_SquareRoot() to get the real norm)
t_float						Vector2D_Norm(s_vector2d const* vector);
#define c_vec2norm			Vector2D_Norm
#define Vector2D_Length		Vector2D_Norm
#define Vector2D_Magnitude	Vector2D_Norm

//! Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
s_vector2d					Vector2D_Normalize(s_vector2d const* vector);
#define c_vec2normalize		Vector2D_Normalize



//! Returns the sum of the two given vectors (adding each of their coordinates together)
s_vector2d						Vector2D_Add(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2add				Vector2D_Add

//! Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
t_float							Vector2D_Dot(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2dot				Vector2D_Dot
#define Vector2D_DotProduct		Vector2D_Dot
#define Vector2D_InnerProduct	Vector2D_Dot
#define Vector2D_ScalarProduct	Vector2D_Dot



/*
** ************************************************************************** *|
**                        3-dimensional Vector Operations                     *|
** ************************************************************************** *|
*/

//! Returns a vector struct, with the given coordinates
s_vector3d			Vector3D(t_float x, t_float y, t_float z);
#define c_vec3		Vector3D

//! Allocates a new vector struct, with the given coordinates
_MALLOC()
s_vector3d*			Vector3D_New(t_float x, t_float y, t_float z);
#define c_vec3new	Vector3D_New



//! Returns `TRUE` if the two given vectors are equal (all their values are identical)
t_bool					Vector3D_Equals(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3equ		Vector3D_Equals

//! Scales the given `vector` by a factor of `scale`
s_vector3d				Vector3D_Scale(s_vector3d const* vector, t_float scale);
#define c_vec3scale		Vector3D_Scale

//! Inverts the sign of the coordinates of the given `vector`
s_vector3d					Vector3D_Invert(s_vector3d const* vector);
#define c_vec3invert		Vector3D_Invert

//! Returns the norm/magnitude of the given `vector`, squared (call sqrt to get the real norm)
t_float						Vector3D_Norm(s_vector3d const* vector);
#define c_vec3norm			Vector3D_Norm
#define Vector3D_Length		Vector3D_Norm
#define Vector3D_Magnitude	Vector3D_Norm

//! Makes the norm/magnitude of the given `vector` become 1 (without changing its direction)
s_vector3d					Vector3D_Normalize(s_vector3d const* vector);
#define c_vec3normalize		Vector3D_Normalize



//! Returns the sum of the two given vectors (adding each of their coordinates together)
s_vector3d						Vector3D_Add(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3add				Vector3D_Add

//! Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
t_float							Vector3D_Dot(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3dot				Vector3D_Dot
#define Vector3D_DotProduct		Vector3D_Dot
#define Vector3D_InnerProduct	Vector3D_Dot
#define Vector3D_ScalarProduct	Vector3D_Dot

//! Returns the cross/vector product of the two given vectors (the vector which is perpendicular to both)
s_vector3d						Vector3D_Cross(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3cross				Vector3D_Cross
#define Vector3D_CrossProduct	Vector3D_Cross
#define Vector3D_OuterProduct	Vector3D_Cross
#define Vector3D_VectorProduct	Vector3D_Cross



/*
** ************************************************************************** *|
**                        4-dimensional Vector Operations                     *|
** ************************************************************************** *|
*/

// TODO define and implement 4D vector operations



/*! @} */
HEADER_END
#endif
