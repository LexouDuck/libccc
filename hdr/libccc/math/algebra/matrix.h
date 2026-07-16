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
/*!@group{libccc_math_algebra_matrix,62,libccc/math/algebra/matrix.h}
**
**	This header defines matrix types and functions, in several dimensions (2x2/3x3/4x4, and generic NxM)
*/
// TODO add other function macros for integral, distance, etc

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/algebra/vector.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc A simple struct which stores a 2x2 matrix of real numbers, arranged in 2 rows of 2D vectors
//!@{
typedef struct mat2d
{
	s_vector2d	u;
	s_vector2d	v;
}				s_matrix2d;
TYPEDEF_ALIAS(	s_matrix2d, MATRIX_2D, STRUCT)
//!@}

//!@doc This union stores a 2x2 matrix which can be accessed in several ways
//!@{
typedef	union matrix2d
{
	t_float		values[2*2];	//!< An array, to access the matrix values from within brackets
	s_matrix2d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix2d;
TYPEDEF_ALIAS(	u_matrix2d, MATRIX_2D, UNION)
//!@}

//! A 2-dimensional matrix in which every number is zero
#define MATRIX2D_NULL \
{ \
	.u={ 0, 0 }, \
	.v={ 0, 0 }, \
} \

//! A 2-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX2D_IDENTITY \
{ \
	.u={ 1, 0 }, \
	.v={ 0, 1 }, \
} \



//!@doc A simple struct which stores a 3x3 matrix of real numbers, arranged in 3 rows of 3D vectors
//!@{
typedef struct mat3d
{
	s_vector3d	u;
	s_vector3d	v;
	s_vector3d	w;
}				s_matrix3d;
TYPEDEF_ALIAS(	s_matrix3d, MATRIX_3D, STRUCT)
//!@}

//!@doc This union stores a 3x3 matrix which can be accessed in several ways
//!@{
typedef	union matrix3d
{
	t_float		values[3*3];	//!< An array, to access the matrix values from within brackets
	s_matrix3d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix3d;
TYPEDEF_ALIAS(	u_matrix3d, MATRIX_3D, UNION)
//!@}

//! A 3-dimensional matrix in which every number is zero
#define MATRIX3D_NULL \
{ \
	.u={ 0, 0, 0 }, \
	.v={ 0, 0, 0 }, \
	.w={ 0, 0, 0 }, \
} \

//! A 3-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX3D_IDENTITY \
{ \
	.u={ 1, 0, 0 }, \
	.v={ 0, 1, 0 }, \
	.w={ 0, 0, 1 }, \
} \



//!@doc A simple struct which stores a 4x4 matrix of real numbers, arranged in 4 rows of 4D vectors
//!@{
typedef struct mat4d
{
	s_vector4d	u;
	s_vector4d	v;
	s_vector4d	w;
	s_vector4d	t;
}				s_matrix4d;
TYPEDEF_ALIAS(	s_matrix4d, MATRIX_4D, STRUCT)
//!@}

//!@doc This union stores a 4x4 matrix which can be accessed in several ways
//!@{
typedef	union matrix4d
{
	t_float		values[4*4];	//!< An array, to access the matrix values from within brackets
	s_matrix4d	matrix;			//!< A struct, to access the matrix values as several row vectors
}				u_matrix4d;
TYPEDEF_ALIAS(	u_matrix4d, MATRIX_4D, UNION)
//!@}

//! A 4-dimensional matrix in which every number is zero
#define MATRIX4D_NULL \
{ \
	.u={ 0, 0, 0, 0 }, \
	.v={ 0, 0, 0, 0 }, \
	.w={ 0, 0, 0, 0 }, \
	.t={ 0, 0, 0, 0 }, \
} \

//! A 4-dimensional matrix which is neutral (does nothing) when applied/multiplied
#define MATRIX4D_IDENTITY \
{ \
	.u={ 1, 0, 0, 0 }, \
	.v={ 0, 1, 0, 0 }, \
	.w={ 0, 0, 1, 0 }, \
	.t={ 0, 0, 0, 1 }, \
} \



//!@doc A matrix struct which stores a generic N-by-M matrix of real numbers (the dimensions are stored at runtime)
/*!
**	Unlike the fixed-size matrix structs above, this struct holds its values
**	in a heap-allocated array buffer, whose size is only known at runtime.
**	The values are stored in row-major order: the value at row `i` and column `j`
**	is stored at `matrix.values[i * matrix.cols + j]` (also see Matrix_Get() and Matrix_Set()).
**	As such, any #s_matrix created via the Matrix() or Matrix_New() constructor
**	functions must be freed appropriately, by calling Matrix_Free() or Matrix_Delete().
*/
//!@{
typedef struct matrix
{
	t_uint		rows;		//!< The amount of rows in this matrix
	t_uint		cols;		//!< The amount of columns in this matrix
	t_float*	values;		//!< The array which holds the `rows * cols` values of this matrix (in row-major order)
}				s_matrix;
TYPEDEF_ALIAS(	s_matrix, MATRIX, STRUCT)
//!@}
//! The default/null value for a #s_matrix (zero rows and columns, with no allocated buffer)
#define MATRIX_NULL	(s_matrix){ .rows = 0, .cols = 0, .values = NULL } 



/*============================================================================*\
||                        2-dimensional Matrix Operations                     ||
\*============================================================================*/

//! A 2-dimensional matrix which, when applied, rotates a vector by the given 'ANGLE'
#define MATRIX2D_ROTATE(ANGLE) \
{ \
	.u={ c_cos(ANGLE), -c_sin(ANGLE) }, \
	.v={ c_sin(ANGLE),  c_cos(ANGLE) }, \
} \



//!@doc Returns a matrix struct, setting its values from the given vectors
//!@{
s_matrix2d				Matrix2D(s_vector2d const* u, s_vector2d const* v);
#define c_mat2			Matrix2D
//!@}

//!@doc Allocates a new matrix struct, setting its values from the given vectors
//!@{
_MALLOC()
s_matrix2d*				Matrix2D_New(s_vector2d const* u, s_vector2d const* v);
#define c_mat2new		Matrix2D_New
//!@}

//!@doc Returns TRUE if the two given matrices are equal (all their values are identical)
//!@{
t_bool					Matrix2D_Equals(s_matrix2d const* m1, s_matrix2d const* m2);
#define c_mat2equ		Matrix2D_Equals
//!@}

//!@doc Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
//!@{
s_vector2d				Matrix2D_Apply(s_matrix2d const* matrix, s_vector2d const* vector);
#define c_mat2apply		Matrix2D_Apply
//!@}

//!@doc Returns the determinant value for the given 'matrix'
//!@{
t_float					Matrix2D_Determinant(s_matrix2d const* matrix);
#define c_mat2determ	Matrix2D_Determinant
//!@}

//!@doc Changes the values of the given 'matrix' to those of its inverse matrix
//!@{
s_matrix2d				Matrix2D_Inverse(s_matrix2d const* matrix);
#define c_mat2inverse	Matrix2D_Inverse
//!@}

//!@doc Returns the transpose the given 'matrix', flipping its values across its diagonal
//!@{
s_matrix2d				Matrix2D_Transpose(s_matrix2d const* matrix);
#define c_mat2transp	Matrix2D_Transpose
//!@}

//!@doc Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
//!@{
s_matrix2d				Matrix2D_Multiply(s_matrix2d const* m1, s_matrix2d const* m2);
#define c_mat2mult		Matrix2D_Multiply
//!@}



/*============================================================================*\
||                        3-dimensional Matrix Operations                     ||
\*============================================================================*/

//! A 3-dimensional matrix which, when applied, rotates a vector about the X axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_X(ANGLE) \
{ \
	.u={ 1, 0,             0            }, \
	.v={ 0, c_cos(ANGLE), -c_sin(ANGLE) }, \
	.w={ 0, c_sin(ANGLE),  c_cos(ANGLE) }, \
} \

//! A 3-dimensional matrix which, when applied, rotates a vector about the Y axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Y(ANGLE) \
{ \
	.u={  c_cos(ANGLE), 0, c_sin(ANGLE) }, \
	.v={  0,            1, 0            }, \
	.w={ -c_sin(ANGLE), 0, c_cos(ANGLE) }, \
} \

//! A 3-dimensional matrix which, when applied, rotates a vector about the Z axis by the given 'ANGLE'
#define MATRIX3D_ROTATE_Z(ANGLE) \
{ \
	.u={ c_cos(ANGLE), -c_sin(ANGLE), 0 }, \
	.v={ c_sin(ANGLE),  c_cos(ANGLE), 0 }, \
	.w={ 0,             0,            1 }, \
} \



//!@doc Returns a matrix struct, setting its values from the given vectors
//!@{
s_matrix3d				Matrix3D(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w);
#define c_mat3			Matrix3D
//!@}

//!@doc Allocates a new matrix struct, setting its values from the given vectors
//!@{
_MALLOC()
s_matrix3d*				Matrix3D_New(s_vector3d const* u, s_vector3d const* v, s_vector3d const* w);
#define c_mat3new		Matrix3D_New
//!@}

//!@doc Returns TRUE if the two given matrices are equal (all their values are identical)
//!@{
t_bool					Matrix3D_Equals(s_matrix3d const* m1, s_matrix3d const* m2);
#define c_mat3equ		Matrix3D_Equals
//!@}

//!@doc Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
//!@{
s_vector3d				Matrix3D_Apply(s_matrix3d const* matrix, s_vector3d const* vector);
#define c_mat3apply		Matrix3D_Apply
//!@}

//!@doc Returns the determinant value for the given 'matrix'
//!@{
t_float					Matrix3D_Determinant(s_matrix3d const* matrix);
#define c_mat3determ	Matrix3D_Determinant
//!@}

//!@doc Changes the values of the given 'matrix' to those of its inverse matrix
//!@{
s_matrix3d				Matrix3D_Inverse(s_matrix3d const* matrix);
#define c_mat3inverse	Matrix3D_Inverse
//!@}

//!@doc Returns the transpose the given 'matrix', flipping its values across its diagonal
//!@{
s_matrix3d				Matrix3D_Transpose(s_matrix3d const* matrix);
#define c_mat3transp	Matrix3D_Transpose
//!@}

//!@doc Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
//!@{
s_matrix3d				Matrix3D_Multiply(s_matrix3d const* m1, s_matrix3d const* m2);
#define c_mat3mult		Matrix3D_Multiply
//!@}



/*============================================================================*\
||                        4-dimensional Matrix Operations                     ||
\*============================================================================*/

//! A 4-dimensional matrix which, when applied, rotates a vector about the X axis by the given 'ANGLE'
#define MATRIX4D_ROTATE_X(ANGLE) \
{ \
	.u={ 1, 0,             0,            0 }, \
	.v={ 0, c_cos(ANGLE), -c_sin(ANGLE), 0 }, \
	.w={ 0, c_sin(ANGLE),  c_cos(ANGLE), 0 }, \
	.t={ 0, 0,             0,            1 }, \
} \

//! A 4-dimensional matrix which, when applied, rotates a vector about the Y axis by the given 'ANGLE'
#define MATRIX4D_ROTATE_Y(ANGLE) \
{ \
	.u={  c_cos(ANGLE), 0, c_sin(ANGLE), 0 }, \
	.v={  0,            1, 0,            0 }, \
	.w={ -c_sin(ANGLE), 0, c_cos(ANGLE), 0 }, \
	.t={  0,            0, 0,            1 }, \
} \

//! A 4-dimensional matrix which, when applied, rotates a vector about the Z axis by the given 'ANGLE'
#define MATRIX4D_ROTATE_Z(ANGLE) \
{ \
	.u={ c_cos(ANGLE), -c_sin(ANGLE), 0, 0 }, \
	.v={ c_sin(ANGLE),  c_cos(ANGLE), 0, 0 }, \
	.w={ 0,             0,            1, 0 }, \
	.t={ 0,             0,            0, 1 }, \
} \

//! A 4-dimensional matrix which, when applied to a homogeneous vector (whose `t` is 1), translates it by the given offsets
#define MATRIX4D_TRANSLATE(X, Y, Z) \
{ \
	.u={ 1,   0,   0,   0 }, \
	.v={ 0,   1,   0,   0 }, \
	.w={ 0,   0,   1,   0 }, \
	.t={ (X), (Y), (Z), 1 }, \
} \

//! A 4-dimensional matrix which, when applied, scales a vector by the given factors along each axis
#define MATRIX4D_SCALE(X, Y, Z) \
{ \
	.u={ (X), 0,   0,   0 }, \
	.v={ 0,   (Y), 0,   0 }, \
	.w={ 0,   0,   (Z), 0 }, \
	.t={ 0,   0,   0,   1 }, \
} \



//!@doc Returns a matrix struct, setting its values from the given vectors
//!@{
s_matrix4d				Matrix4D(s_vector4d const* u, s_vector4d const* v, s_vector4d const* w, s_vector4d const* t);
#define c_mat4			Matrix4D
//!@}

//!@doc Allocates a new matrix struct, setting its values from the given vectors
//!@{
_MALLOC()
s_matrix4d*				Matrix4D_New(s_vector4d const* u, s_vector4d const* v, s_vector4d const* w, s_vector4d const* t);
#define c_mat4new		Matrix4D_New
//!@}

//!@doc Returns TRUE if the two given matrices are equal (all their values are identical)
//!@{
t_bool					Matrix4D_Equals(s_matrix4d const* m1, s_matrix4d const* m2);
#define c_mat4equ		Matrix4D_Equals
//!@}

//!@doc Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
//!@{
s_vector4d				Matrix4D_Apply(s_matrix4d const* matrix, s_vector4d const* vector);
#define c_mat4apply		Matrix4D_Apply
//!@}

//!@doc Returns the determinant value for the given 'matrix'
//!@{
t_float					Matrix4D_Determinant(s_matrix4d const* matrix);
#define c_mat4determ	Matrix4D_Determinant
//!@}

//!@doc Changes the values of the given 'matrix' to those of its inverse matrix
//!@{
s_matrix4d				Matrix4D_Inverse(s_matrix4d const* matrix);
#define c_mat4inverse	Matrix4D_Inverse
//!@}

//!@doc Returns the transpose the given 'matrix', flipping its values across its diagonal
//!@{
s_matrix4d				Matrix4D_Transpose(s_matrix4d const* matrix);
#define c_mat4transp	Matrix4D_Transpose
//!@}

//!@doc Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
//!@{
s_matrix4d				Matrix4D_Multiply(s_matrix4d const* m1, s_matrix4d const* m2);
#define c_mat4mult		Matrix4D_Multiply
//!@}



/*============================================================================*\
||                      N-by-M-dimensional Matrix Operations                  ||
\*============================================================================*/

//!@doc Returns a matrix struct with the given dimensions, allocating its `values` buffer
/*!
**	@param	rows	The amount of rows for the new matrix
**	@param	cols	The amount of columns for the new matrix
**	@param	values	The array of `rows * cols` values (in row-major order) to copy into the new matrix (if `NULL`, the matrix is zero-filled)
**	@returns a new matrix struct (its `values` buffer must be freed by calling Matrix_Free())
*/
//!@{
s_matrix			Matrix(t_uint rows, t_uint cols, t_float const* values);
#define c_mat		Matrix
//!@}

//!@doc Allocates a new matrix struct on heap, with the given dimensions
/*!
**	@param	rows	The amount of rows for the new matrix
**	@param	cols	The amount of columns for the new matrix
**	@param	values	The array of `rows * cols` values (in row-major order) to copy into the new matrix (if `NULL`, the matrix is zero-filled)
**	@returns a newly allocated matrix struct (must be freed by calling Matrix_Delete())
*/
//!@{
_MALLOC()
s_matrix*			Matrix_New(t_uint rows, t_uint cols, t_float const* values);
#define c_matnew	Matrix_New
//!@}

//!@doc Returns a square matrix of the given size `n`, which is neutral (does nothing) when applied/multiplied
//!@{
s_matrix			Matrix_Identity(t_uint n);
#define c_matident	Matrix_Identity
//!@}

//!@doc Returns a newly allocated copy of the given `matrix`
//!@{
s_matrix			Matrix_Duplicate(s_matrix const* matrix);
#define c_matdup	Matrix_Duplicate
//!@}

//!@doc Deallocates the `values` buffer of the given `matrix` (and sets its fields to zero)
//!@{
void				Matrix_Free(s_matrix* matrix);
#define c_matfree	Matrix_Free
//!@}

//!@doc Deallocates the given heap-allocated `matrix` (its `values` buffer, and the struct itself)
//!@{
void				Matrix_Delete(s_matrix* *a_matrix);
#define c_matdel	Matrix_Delete
//!@}



//!@doc Returns the value stored in the given `matrix`, at row `row` and column `col`
//!@{
t_float				Matrix_Get(s_matrix const* matrix, t_uint row, t_uint col);
#define c_matget	Matrix_Get
//!@}

//!@doc Sets the value stored in the given `matrix`, at row `row` and column `col`, to the given `value`
//!@{
void				Matrix_Set(s_matrix* matrix, t_uint row, t_uint col, t_float value);
#define c_matset	Matrix_Set
//!@}



//!@doc Returns TRUE if the two given matrices are equal (same dimensions, and all their values are identical)
//!@{
t_bool				Matrix_Equals(s_matrix const* m1, s_matrix const* m2);
#define c_matequ	Matrix_Equals
//!@}

//!@doc Applies the transformation stored by the given 'matrix' onto the given 'vector' and returns it
/*!
**	The given `vector` is treated as a row vector, so its amount of dimensions
**	must be equal to the amount of rows of the given `matrix`.
**	The resulting vector has as many dimensions as the `matrix` has columns.
**
**	@returns #VECTOR_NULL if `vector->dims` is not equal to `matrix->rows`
*/
//!@{
s_vector			Matrix_Apply(s_matrix const* matrix, s_vector const* vector);
#define c_matapply	Matrix_Apply
//!@}

//!@doc Returns the determinant value for the given 'matrix' (which must be square)
/*!
**	This function uses LU decomposition with partial pivoting, in `O(n^3)` operations.
**
**	@returns `0` if the given `matrix` is not square (ie: `matrix->rows != matrix->cols`)
*/
//!@{
t_float				Matrix_Determinant(s_matrix const* matrix);
#define c_matdeterm	Matrix_Determinant
//!@}

//!@doc Returns the inverse matrix of the given 'matrix' (which must be square)
/*!
**	This function uses Gauss-Jordan elimination with partial pivoting, in `O(n^3)` operations.
**
**	@returns a zero-filled matrix if the given `matrix` is singular (ie: not invertible),
**		or #MATRIX_NULL if the given `matrix` is not square (ie: `matrix->rows != matrix->cols`)
*/
//!@{
s_matrix				Matrix_Inverse(s_matrix const* matrix);
#define c_matinverse	Matrix_Inverse
//!@}

//!@doc Returns the transpose the given 'matrix', flipping its values across its diagonal
/*!
**	The resulting matrix has its dimensions swapped: `cols` rows, and `rows` columns.
*/
//!@{
s_matrix			Matrix_Transpose(s_matrix const* matrix);
#define c_mattransp	Matrix_Transpose
//!@}

//!@doc Performs a matrix multiplication on the two given matrices 'm1' and 'm2'
/*!
**	The resulting matrix has `m1->rows` rows and `m2->cols` columns.
**
**	@returns #MATRIX_NULL if `m1->cols` is not equal to `m2->rows`
*/
//!@{
s_matrix			Matrix_Multiply(s_matrix const* m1, s_matrix const* m2);
#define c_matmult	Matrix_Multiply
//!@}



/*! @endgroup */
HEADER_END
#endif
