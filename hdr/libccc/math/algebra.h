/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/algebra.h                    |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ALGEBRA_H
#define __LIBCCC_ALGEBRA_H
/*!@group{libccc_math_algebra}
** @{
**	This header defines useful algebra and calculus types, and functions.
**
**	@file
*/
// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/math/math.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                              Vector Operations                             *|
** ************************************************************************** *|
*/

//! A simple vector struct for storing 2-dimensional values
typedef struct	s_vector2d_
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
}				s_vector2d;
TYPEDEF_ALIAS(	s_vector2d, VECTOR_2D, STRUCT)
//! This union stores a 2-dimensional value which can be accessed in several ways
typedef	union	u_vector2d_
{
	t_float		values[2];	//!< An array, to access the 2 values from within brackets
	s_vector2d	vector;		//!< A vector, to access the 2 coordinates as `.x` and `.y`
}				u_vector2d;
TYPEDEF_ALIAS(	u_vector2d, VECTOR_2D, UNION)

//! Allocates a new vector struct on heap, setting the given coordinates
_MALLOC()
s_vector2d*				Vector2D_New(t_float x, t_float y);
#define c_vec2new		Vector2D_New

//! Returns TRUE if the two given vectors are equal (all their values are identical)
t_bool					Vector2D_Equals(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2equ		Vector2D_Equals

//! Scales the given 'vector' by a factor of 'scale'
s_vector2d				Vector2D_Scale(s_vector2d const* vector, t_float scale);
#define c_vec2scale		Vector2D_Scale

//! Inverts the sign of the coordinates of the given 'vector'
s_vector2d				Vector2D_Invert(s_vector2d const* vector);
#define c_vec2invert	Vector2D_Invert

//! Returns the norm/magnitude of the given 'vector', squared (call sqrt to get the real norm)
t_float						Vector2D_Norm(s_vector2d const* vector);
#define c_vec2norm			Vector2D_Norm
#define Vector2D_Length		Vector2D_Norm
#define Vector2D_Magnitude	Vector2D_Norm

//! Makes the norm/magnitude of the given 'vector' become 1 (without changing its direction)
s_vector2d					Vector2D_Normalize(s_vector2d const* vector);
#define c_vec2normalize		Vector2D_Normalize

//! Returns the sum of the two given vectors (adding each of their coordinates together)
s_vector2d					Vector2D_Add(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2add			Vector2D_Add

//! Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
t_float							Vector2D_Dot(s_vector2d const* v1, s_vector2d const* v2);
#define c_vec2dot				Vector2D_Dot
#define Vector2D_DotProduct		Vector2D_Dot
#define Vector2D_InnerProduct	Vector2D_Dot
#define Vector2D_ScalarProduct	Vector2D_Dot



//! A simple vector struct for storing 3-dimensional values
typedef struct	s_vector3d_
{
	t_float		x;			//!< The X axis coordinate of this vector
	t_float		y;			//!< The Y axis coordinate of this vector
	t_float		z;			//!< The Z axis coordinate of this vector
}				s_vector3d;
TYPEDEF_ALIAS(	s_vector3d, VECTOR_3D, STRUCT)
//! This union stores a 3-dimensional value which can be accessed in several ways
typedef	union	u_vector3d_
{
	t_float		values[3];	//!< An array, to access the 3 values from within brackets
	s_vector3d	vector;		//!< A vector, to access the 3 coordinates as `.x`, `.y` and `.z`
}				u_vector3d;
TYPEDEF_ALIAS(	u_vector3d, VECTOR_3D, UNION)

//! Allocates a new vector struct on heap, setting the given coordinates
_MALLOC()
s_vector3d*				Vector3D_New(t_float x, t_float y, t_float z);
#define c_vec3new		Vector3D_New

//! Returns TRUE if the two given vectors are equal (all their values are identical)
t_bool					Vector3D_Equals(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3equ		Vector3D_Equals

//! Scales the given 'vector' by a factor of 'scale'
s_vector3d				Vector3D_Scale(s_vector3d const* vector, t_float scale);
#define c_vec3scale	Vector3D_Scale

//! Inverts the sign of the coordinates of the given 'vector'
s_vector3d				Vector3D_Invert(s_vector3d const* vector);
#define c_vec3invert	Vector3D_Invert

//! Returns the norm/magnitude of the given 'vector', squared (call sqrt to get the real norm)
t_float						Vector3D_Norm(s_vector3d const* vector);
#define c_vec3norm			Vector3D_Norm
#define Vector3D_Length		Vector3D_Norm
#define Vector3D_Magnitude	Vector3D_Norm

//! Makes the norm/magnitude of the given 'vector' become 1 (without changing its direction)
s_vector3d					Vector3D_Normalize(s_vector3d const* vector);
#define c_vec3normalize	Vector3D_Normalize

//! Returns the sum of the two given vectors (adding each of their coordinates together)
s_vector3d					Vector3D_Add(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3add			Vector3D_Add

//! Returns the dot/scalar product of the two given vectors (the sum of their multiplied coordinates)
t_float							Vector3D_Dot(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3dot				Vector3D_Dot
#define Vector3D_DotProduct		Vector3D_Dot
#define Vector3D_InnerProduct	Vector3D_Dot
#define Vector3D_ScalarProduct	Vector3D_Dot

//! Returns the cross/vector product of the two given vectors (the vector which is perpendicular to both)
s_vector3d						Vector3D_Cross(s_vector3d const* v1, s_vector3d const* v2);
#define c_vec3cross			Vector3D_Cross
#define Vector3D_CrossProduct	Vector3D_Cross
#define Vector3D_OuterProduct	Vector3D_Cross
#define Vector3D_VectorProduct	Vector3D_Cross



//! A simple vector struct for storing 4-dimensional values
typedef struct	s_vector4d_
{
	t_float		x;			//!<< The X axis coordinate of this vector
	t_float		y;			//!<< The Y axis coordinate of this vector
	t_float		z;			//!<< The Z axis coordinate of this vector
	t_float		t;			//!<< The T axis coordinate of this vector
}				s_vector4d;
TYPEDEF_ALIAS(	s_vector4d, VECTOR_4D, STRUCT)
//! This union stores a 4-dimensional value which can be accessed in several ways
typedef	union	u_vector4d_
{
	t_float		values[4];	//!< An array, to access the 4 values from within brackets
	s_vector4d	vector;		//!< A vector, to access the 4 coordinates as `.x`, `.y`, `.z`, and `.t`
}				u_vector4d;
TYPEDEF_ALIAS(	u_vector4d, VECTOR_4D, UNION)

// TODO define and implement 4D vector operations



/*
** ************************************************************************** *|
**                              Matrix Operations                             *|
** ************************************************************************** *|
*/

//! A simple struct which stores a 2x2 matrix of real numbers, arranged in 2 rows of 2D vectors
typedef struct	s_matrix2d_
{
	s_vector2d	u;
	s_vector2d	v;
}				s_matrix2d;
TYPEDEF_ALIAS(	s_matrix2d, MATRIX_2D, STRUCT)
//! This union stores a 2x2 matrix which can be accessed in several ways
typedef	union	u_matrix2d_
{
	t_float		values[2*2];	//!< An array, to access the matrix values from within brackets
	s_matrix2d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix2d;
TYPEDEF_ALIAS(	u_matrix2d, MATRIX_2D, UNION)
//! A 2-dimensional matrix in which every number is zero
#define MATRIX2D_NULL \
{					\
	.u={ 0, 0 },	\
	.v={ 0, 0 },	\
}
//! A 2-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX2D_IDENTITY \
{					\
	.u={ 1, 0 },	\
	.v={ 0, 1 },	\
}
//! A 2-dimensional matrix which, when applied, rotates a vector by the given 'ANGLE'
#define MATRIX2D_ROTATE(ANGLE) \
{											\
	.u={ c_cos(ANGLE), -c_sin(ANGLE) },	\
	.v={ c_sin(ANGLE),  c_cos(ANGLE) },	\
}

//! Allocates a new matrix struct on heap, setting its values from the given vectors
_MALLOC()
s_matrix2d*				Matrix2D_New(s_vector2d const* u, s_vector2d const* v);
#define c_mat2new		Matrix2D_New

//! Returns TRUE if the two given matrices are equal (all their values are identical)
t_bool					Matrix2D_Equals(s_matrix2d const* m1, s_matrix2d const* m2);
#define c_mat2equ		Matrix2D_Equals

//! Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
s_vector2d				Matrix2D_Apply(s_matrix2d const* matrix, s_vector2d const* vector);
#define c_mat2apply	Matrix2D_Apply

//! Returns the determinant value for the given 'matrix'
t_float					Matrix2D_Determinant(s_matrix2d const* matrix);
#define c_mat2determ	Matrix2D_Determinant

//! Changes the values of the given 'matrix' to those of its inverse matrix
s_matrix2d				Matrix2D_Inverse(s_matrix2d const* matrix);
#define c_mat2inverse	Matrix2D_Inverse

//! Returns the transpose the given 'matrix', flipping its values across its diagonal
s_matrix2d				Matrix2D_Transpose(s_matrix2d const* matrix);
#define c_mat2transp	Matrix2D_Transpose

//! Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
s_matrix2d				Matrix2D_Multiply(s_matrix2d const* m1, s_matrix2d const* m2);
#define c_mat2mult		Matrix2D_Multiply



//! A simple struct which stores a 3x3 matrix of real numbers, arranged in 3 rows of 3D vectors
typedef struct	s_matrix3d_
{
	s_vector3d	u;
	s_vector3d	v;
	s_vector3d	w;
}				s_matrix3d;
TYPEDEF_ALIAS(	s_matrix3d, MATRIX_3D, STRUCT)
//! This union stores a 3x3 matrix which can be accessed in several ways
typedef	union	u_matrix3d_
{
	t_float		values[3*3];	//!< An array, to access the matrix values from within brackets
	s_matrix3d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix3d;
TYPEDEF_ALIAS(	u_matrix3d, MATRIX_3D, UNION)
//! A 3-dimensional matrix in which every number is zero
#define MATRIX3D_NULL \
{					\
	.u={ 0, 0, 0 },	\
	.v={ 0, 0, 0 },	\
	.w={ 0, 0, 0 },	\
}
//! A 3-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX3D_IDENTITY \
{					\
	.u={ 1, 0, 0 },	\
	.v={ 0, 1, 0 },	\
	.w={ 0, 0, 1 },	\
}
//! A 3-dimensional matrix which, when applied, rotates a vector about the X axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_X(ANGLE) \
{												\
	.u={ 1, 0,              0             },	\
	.v={ 0, c_cos(ANGLE), -c_sin(ANGLE) },	\
	.w={ 0, c_sin(ANGLE),  c_cos(ANGLE) },	\
}
//! A 3-dimensional matrix which, when applied, rotates a vector about the Y axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Y(ANGLE) \
{												\
	.u={  c_cos(ANGLE), 0, c_sin(ANGLE) },	\
	.v={  0,             1, 0             },	\
	.w={ -c_sin(ANGLE), 0, c_cos(ANGLE) },	\
}
//! A 3-dimensional matrix which, when applied, rotates a vector about the Z axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Z(ANGLE) \
{												\
	.u={ c_cos(ANGLE), -c_sin(ANGLE), 0 },	\
	.v={ c_sin(ANGLE),  c_cos(ANGLE), 0 },	\
	.w={ 0,              0,             1 },	\
}

//! Allocates a new matrix struct on heap, setting its values from the given vectors
_MALLOC()
s_matrix3d*				Matrix3D_New(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w);
#define c_mat3new		Matrix3D_New

//! Returns TRUE if the two given matrices are equal (all their values are identical)
t_bool					Matrix3D_Equals(s_matrix3d const* m1, s_matrix3d const* m2);
#define c_mat3equ		Matrix3D_Equals

//! Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
s_vector3d				Matrix3D_Apply(s_matrix3d const* matrix, s_vector3d const* vector);
#define c_mat3apply	Matrix3D_Apply

//! Returns the determinant value for the given 'matrix'
t_float					Matrix3D_Determinant(s_matrix3d const* matrix);
#define c_mat3determ	Matrix3D_Determinant

//! Changes the values of the given 'matrix' to those of its inverse matrix
s_matrix3d				Matrix3D_Inverse(s_matrix3d const* matrix);
#define c_mat3inverse	Matrix3D_Inverse

//! Returns the transpose the given 'matrix', flipping its values across its diagonal
s_matrix3d				Matrix3D_Transpose(s_matrix3d const* matrix);
#define c_mat3transp	Matrix3D_Transpose

//! Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
s_matrix3d				Matrix3D_Multiply(s_matrix3d const* m1, s_matrix3d const* m2);
#define c_mat3mult		Matrix3D_Multiply



//! A simple struct which stores a 4x4 matrix of real numbers, arranged in 3 rows of 3D vectors
typedef struct	s_matrix4d_
{
	s_vector4d	u;
	s_vector4d	v;
	s_vector4d	w;
	s_vector4d	t;
}				s_matrix4d;
TYPEDEF_ALIAS(	s_matrix4d, MATRIX_4D, STRUCT)
//! This union stores a 4x4 matrix which can be accessed in several ways
typedef	union	u_matrix4d_
{
	t_float		values[4*4];	//!< An array, to access the matrix values from within brackets
	s_matrix3d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix4d;
TYPEDEF_ALIAS(	u_matrix4d, MATRIX_4D, UNION)
//! A 4-dimensional matrix in which every number is zero
#define MATRIX4D_NULL \
{						\
	.u={ 0, 0, 0, 0 }	\
	.v={ 0, 0, 0, 0 }	\
	.w={ 0, 0, 0, 0 }	\
	.t={ 0, 0, 0, 0 }	\
}						\
//! A 4-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX4D_IDENTITY \
{						\
	.u={ 1, 0, 0, 0 }	\
	.v={ 0, 1, 0, 0 }	\
	.w={ 0, 0, 1, 0 }	\
	.t={ 0, 0, 0, 1 }	\
}						\

// TODO define and implement 4D matrix operations



/*
** ************************************************************************** *|
**                     Axis-aligned Bounding-box Operations                   *|
** ************************************************************************** *|
*/

/*
**	Definitions of axis-aligned bounding-box are assumed to be entirely composed of
**	orthogonal edges (brick shaped), which is why only two vectors are necessary to define it.
*/

//! A 1-dimensional interval of coordinates, defined by two corner-point vectors
typedef struct		s_box1d_
{
	t_float		start;
	t_float		end;
}					s_box1d;
TYPEDEF_ALIAS(		s_box1d, BOX_1D, STRUCT)

//! A 2-dimensional area of coordinates, defined by two corner-point vectors
typedef struct		s_box2d_
{
	u_vector2d	start;
	u_vector2d	end;
}					s_box2d;
TYPEDEF_ALIAS(		s_box2d, BOX_2D, STRUCT)

//! A 3-dimensional volume of coordinates, defined by two corner-point vectors
typedef struct		s_box3d_
{
	u_vector3d	start;
	u_vector3d	end;
}					s_box3d;
TYPEDEF_ALIAS(		s_box3d, BOX_3D, STRUCT)

//! A 4-dimensional hypervolume of coordinates, defined by two corner-point vectors
typedef struct		s_box4d_
{
	u_vector4d	start;
	u_vector4d	end;
}					s_box4d;
TYPEDEF_ALIAS(		s_box4d, BOX_4D, STRUCT)



//! An interval/range, defined by a 'start' number and 'end' number
typedef s_box1d	s_interval;
TYPEDEF_ALIAS(	s_interval, INTERVAL, STRUCT)



//! The type of function which takes a 1-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func1)(t_float const v);
//! The type of function which takes a 2-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func2)(u_vector2d const v);
//! The type of function which takes a 3-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func3)(u_vector3d const v);
//! The type of function which takes a 4-dimensional vector as input, and returns a real number
typedef t_float	(*f_scalar_func4)(u_vector4d const v);



/*
**	NB: For a coordinate box in the input space R^3, the volume computed
**	by the integral is thus technically a 4-hypervolume (since you
**	add a dimension because of the output space of dimension 1).
*/
// TODO document these functions
//t_float	lin_integrate(sf, domain);
t_float		c_integrate(f_real_function const f, s_interval const domain, t_float step);
t_float		c_mc_integrate_1d(f_scalar_func1 const sf, s_box1d const domain);
t_float		c_mc_integrate_2d(f_scalar_func2 const sf, s_box2d const domain);
t_float		c_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain);
t_float		c_mc_integrate_4d(f_scalar_func4 const sf, s_box4d const domain);



t_float		c_distance_float(t_float x, t_float y);
t_f32		c_distance_f32  (t_f32   x, t_f32   y);
t_f64		c_distance_f64  (t_f64   x, t_f64   y);

t_uint		c_distance_uint(t_uint x, t_uint y);
t_u8		c_distance_u8  (t_u8   x, t_u8   y);
t_u16		c_distance_u16 (t_u16  x, t_u16  y);
t_u32		c_distance_u32 (t_u32  x, t_u32  y);
t_u64		c_distance_u64 (t_u64  x, t_u64  y);

t_sint		c_distance_int (t_sint x, t_sint y);
t_s8		c_distance_s8  (t_s8  x, t_s8  y);
t_s16		c_distance_s16 (t_s16 x, t_s16 y);
t_s32		c_distance_s32 (t_s32 x, t_s32 y);
t_s64		c_distance_s64 (t_s64 x, t_s64 y);
// TODO distance manh, eucl, inf for 2d, 3d and 4d



/*! @} */
HEADER_END
#endif
