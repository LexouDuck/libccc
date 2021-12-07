/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/algebra/matrix.h             |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_ALGEBRA_MATRIX_H
#define __LIBCCC_MATH_ALGEBRA_MATRIX_H
/*!@group{libccc_math_algebra_matrix}
**
**	This header defines matrix type and functions, in several dimensions (2d/3d/4d)
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
#include "libccc/math/algebra/vector.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A simple struct which stores a 2x2 matrix of real numbers, arranged in 2 rows of 2D vectors
typedef struct mat2d
{
	s_vector2d	u;
	s_vector2d	v;
}				s_matrix2d;
TYPEDEF_ALIAS(	s_matrix2d, MATRIX_2D, STRUCT)

//! This union stores a 2x2 matrix which can be accessed in several ways
typedef	union matrix2d
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



//! A simple struct which stores a 3x3 matrix of real numbers, arranged in 3 rows of 3D vectors
typedef struct mat3d
{
	s_vector3d	u;
	s_vector3d	v;
	s_vector3d	w;
}				s_matrix3d;
TYPEDEF_ALIAS(	s_matrix3d, MATRIX_3D, STRUCT)

//! This union stores a 3x3 matrix which can be accessed in several ways
typedef	union matrix3d
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



//! A simple struct which stores a 4x4 matrix of real numbers, arranged in 3 rows of 3D vectors
typedef struct mat4d
{
	s_vector4d	u;
	s_vector4d	v;
	s_vector4d	w;
	s_vector4d	t;
}				s_matrix4d;
TYPEDEF_ALIAS(	s_matrix4d, MATRIX_4D, STRUCT)

//! This union stores a 4x4 matrix which can be accessed in several ways
typedef	union matrix4d
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



/*
** ************************************************************************** *|
**                        2-dimensional Matrix Operations                     *|
** ************************************************************************** *|
*/

//! A 2-dimensional matrix which, when applied, rotates a vector by the given 'ANGLE'
#define MATRIX2D_ROTATE(ANGLE) \
{										\
	.u={ c_cos(ANGLE), -c_sin(ANGLE) },	\
	.v={ c_sin(ANGLE),  c_cos(ANGLE) },	\
}



//! Returns a matrix struct, setting its values from the given vectors
s_matrix2d				Matrix2D(s_vector2d const* u, s_vector2d const* v);
#define c_mat2			Matrix2D

//! Allocates a new matrix struct, setting its values from the given vectors
_MALLOC()
s_matrix2d*				Matrix2D_New(s_vector2d const* u, s_vector2d const* v);
#define c_mat2new		Matrix2D_New

//! Returns TRUE if the two given matrices are equal (all their values are identical)
t_bool					Matrix2D_Equals(s_matrix2d const* m1, s_matrix2d const* m2);
#define c_mat2equ		Matrix2D_Equals

//! Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
s_vector2d				Matrix2D_Apply(s_matrix2d const* matrix, s_vector2d const* vector);
#define c_mat2apply		Matrix2D_Apply

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



/*
** ************************************************************************** *|
**                        3-dimensional Matrix Operations                     *|
** ************************************************************************** *|
*/

//! A 3-dimensional matrix which, when applied, rotates a vector about the X axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_X(ANGLE) \
{											\
	.u={ 1, 0,             0            },	\
	.v={ 0, c_cos(ANGLE), -c_sin(ANGLE) },	\
	.w={ 0, c_sin(ANGLE),  c_cos(ANGLE) },	\
}
//! A 3-dimensional matrix which, when applied, rotates a vector about the Y axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Y(ANGLE) \
{											\
	.u={  c_cos(ANGLE), 0, c_sin(ANGLE) },	\
	.v={  0,            1, 0            },	\
	.w={ -c_sin(ANGLE), 0, c_cos(ANGLE) },	\
}
//! A 3-dimensional matrix which, when applied, rotates a vector about the Z axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Z(ANGLE) \
{											\
	.u={ c_cos(ANGLE), -c_sin(ANGLE), 0 },	\
	.v={ c_sin(ANGLE),  c_cos(ANGLE), 0 },	\
	.w={ 0,             0,            1 },	\
}



//! Returns a matrix struct, setting its values from the given vectors
s_matrix3d				Matrix3D(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w);
#define c_mat3			Matrix3D

//! Allocates a new matrix struct, setting its values from the given vectors
_MALLOC()
s_matrix3d*				Matrix3D_New(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w);
#define c_mat3new		Matrix3D_New

//! Returns TRUE if the two given matrices are equal (all their values are identical)
t_bool					Matrix3D_Equals(s_matrix3d const* m1, s_matrix3d const* m2);
#define c_mat3equ		Matrix3D_Equals

//! Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
s_vector3d				Matrix3D_Apply(s_matrix3d const* matrix, s_vector3d const* vector);
#define c_mat3apply		Matrix3D_Apply

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



/*
** ************************************************************************** *|
**                        4-dimensional Matrix Operations                     *|
** ************************************************************************** *|
*/

// TODO define and implement 4D matrix operations



/*! @endgroup */
HEADER_END
#endif
