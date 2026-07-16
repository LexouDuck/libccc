/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/algebra/tensor.h             |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_ALGEBRA_TENSOR_H
#define __LIBCCC_MATH_ALGEBRA_TENSOR_H
/*!@group{libccc_math_algebra_tensor,63,libccc/math/algebra/tensor.h}
**
**	This header defines a generic N-dimensional tensor type, and functions
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/algebra/vector.h"
#include "libccc/math/algebra/matrix.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc A tensor struct which stores a generic N-dimensional array of real numbers (the dimensions are stored at runtime)
/*!
**	A tensor of order `N` is a generalization of scalars, vectors, and matrices:
**	- a tensor of order `0` is a scalar (it stores a single value, and its `dims` buffer is `NULL`)
**	- a tensor of order `1` is a vector (equivalent to a #s_vector, with `dims[0]` coordinates)
**	- a tensor of order `2` is a matrix (equivalent to a #s_matrix, with `dims[0]` rows and `dims[1]` columns)
**	- tensors of higher orders generalize this to any amount of axes/dimensions
**
**	The values are stored in row-major order (the last axis is contiguous in memory):
**	the value at coordinates `(c[0], c[1], ..., c[N-1])` is stored at
**	`tensor.values[c[0] * strides[0] + ... + c[N-1] * strides[N-1]]`, where
**	`strides[k]` is the product of every `dims[i]` for `i > k` (also see Tensor_Get() and Tensor_Set()).
**	This struct holds its `dims` and `values` in heap-allocated array buffers,
**	as such, any #s_tensor created via the Tensor() or Tensor_New() constructor
**	functions must be freed appropriately, by calling Tensor_Free() or Tensor_Delete().
*/
//!@{
typedef struct tensor
{
	t_uint		order;		//!< The amount of axes/dimensions of this tensor (also called rank, or degree)
	t_uint*		dims;		//!< The array which holds the `order` sizes for each axis of this tensor (`NULL` if `order` is zero)
	t_float*	values;		//!< The array which holds the values of this tensor, in row-major order (its length is the product of all `dims`)
}				s_tensor;
TYPEDEF_ALIAS(	s_tensor, TENSOR, STRUCT)
//!@}
//! The default/null value for a #s_tensor (zero order, with no allocated buffers)
#define TENSOR_NULL	(s_tensor){ .order = 0, .dims = NULL, .values = NULL } 



/*============================================================================*\
||                        N-dimensional Tensor Operations                     ||
\*============================================================================*/

//!@doc Returns a tensor struct with the given dimensions, allocating its `dims` and `values` buffers
/*!
**	@param	order	The amount of axes/dimensions for the new tensor (if `0`, the tensor is a scalar, and `dims` is ignored)
**	@param	dims	The array of `order` axis sizes for the new tensor (every size must be non-zero)
**	@param	values	The array of values (in row-major order) to copy into the new tensor (if `NULL`, the tensor is zero-filled)
**	@returns a new tensor struct (its buffers must be freed by calling Tensor_Free())
*/
//!@{
s_tensor			Tensor(t_uint order, t_uint const* dims, t_float const* values);
#define c_tens		Tensor
//!@}

//!@doc Allocates a new tensor struct on heap, with the given dimensions
/*!
**	@param	order	The amount of axes/dimensions for the new tensor (if `0`, the tensor is a scalar, and `dims` is ignored)
**	@param	dims	The array of `order` axis sizes for the new tensor (every size must be non-zero)
**	@param	values	The array of values (in row-major order) to copy into the new tensor (if `NULL`, the tensor is zero-filled)
**	@returns a newly allocated tensor struct (must be freed by calling Tensor_Delete())
*/
//!@{
_MALLOC()
s_tensor*			Tensor_New(t_uint order, t_uint const* dims, t_float const* values);
#define c_tensnew	Tensor_New
//!@}

//!@doc Returns a newly allocated copy of the given `tensor`
//!@{
s_tensor			Tensor_Duplicate(s_tensor const* tensor);
#define c_tensdup	Tensor_Duplicate
//!@}

//!@doc Deallocates the `dims` and `values` buffers of the given `tensor` (and sets its fields to zero)
//!@{
void				Tensor_Free(s_tensor* tensor);
#define c_tensfree	Tensor_Free
//!@}

//!@doc Deallocates the given heap-allocated `tensor` (its buffers, and the struct itself)
//!@{
void				Tensor_Delete(s_tensor* *a_tensor);
#define c_tensdel	Tensor_Delete
//!@}



//!@doc Returns the total amount of values stored in the given `tensor` (the product of all its axis sizes)
/*!
**	@returns the product of every axis size of the given `tensor` (`1` if the tensor is a scalar, ie: its `order` is zero)
*/
//!@{
t_uint				Tensor_Size(s_tensor const* tensor);
#define c_tenssize	Tensor_Size
//!@}

//!@doc Returns the value stored in the given `tensor`, at the given coordinates
/*!
**	@param	tensor	The tensor to read a value from
**	@param	coords	The array of `tensor->order` coordinates for the value to get (ignored if the tensor is a scalar)
*/
//!@{
t_float				Tensor_Get(s_tensor const* tensor, t_uint const* coords);
#define c_tensget	Tensor_Get
//!@}

//!@doc Sets the value stored in the given `tensor`, at the given coordinates, to the given `value`
/*!
**	@param	tensor	The tensor to write a value into
**	@param	coords	The array of `tensor->order` coordinates for the value to set (ignored if the tensor is a scalar)
**	@param	value	The value to store at the given coordinates
*/
//!@{
void				Tensor_Set(s_tensor* tensor, t_uint const* coords, t_float value);
#define c_tensset	Tensor_Set
//!@}



//!@doc Returns `TRUE` if the two given tensors are equal (same order and dimensions, and all their values are identical)
//!@{
t_bool				Tensor_Equals(s_tensor const* t1, s_tensor const* t2);
#define c_tensequ	Tensor_Equals
//!@}

//!@doc Scales the given `tensor` by a factor of `scale`
//!@{
s_tensor			Tensor_Scale(s_tensor const* tensor, t_float scale);
#define c_tensscale	Tensor_Scale
//!@}

//!@doc Inverts the sign of the values of the given `tensor`
//!@{
s_tensor				Tensor_Invert(s_tensor const* tensor);
#define c_tensinvert	Tensor_Invert
//!@}

//!@doc Returns the norm/magnitude of the given `tensor`, squared (call sqrt to get the real norm)
/*!
**	The norm of a tensor is the square root of the sum of the squares of all
**	its values (for a matrix, this is known as the Frobenius norm).
*/
//!@{
t_float					Tensor_Norm(s_tensor const* tensor);
#define c_tensnorm		Tensor_Norm
#define Tensor_Length	Tensor_Norm
#define Tensor_Magnitude	Tensor_Norm
//!@}

//!@doc Makes the norm/magnitude of the given `tensor` become 1 (without changing its direction)
//!@{
s_tensor					Tensor_Normalize(s_tensor const* tensor);
#define c_tensnormalize		Tensor_Normalize
//!@}



//!@doc Returns the sum of the two given tensors (adding each of their values together)
/*!
**	@returns #TENSOR_NULL if the two given tensors do not have the same order and dimensions
*/
//!@{
s_tensor			Tensor_Add(s_tensor const* t1, s_tensor const* t2);
#define c_tensadd	Tensor_Add
//!@}

//!@doc Returns the dot/scalar product of the two given tensors (the sum of their multiplied values)
/*!
**	This is the full contraction of the two given tensors: for order-1 tensors,
**	this is the usual vector dot product, and for order-2 tensors, this is
**	known as the Frobenius inner product of two matrices.
**
**	@returns `0` if the two given tensors do not have the same order and dimensions
*/
//!@{
t_float						Tensor_Dot(s_tensor const* t1, s_tensor const* t2);
#define c_tensdot			Tensor_Dot
#define Tensor_DotProduct	Tensor_Dot
#define Tensor_InnerProduct	Tensor_Dot
//!@}

//!@doc Returns the tensor/outer product of the two given tensors
/*!
**	The resulting tensor has an order which is the sum of the orders of the two
**	given tensors (its dimensions are those of `t1`, followed by those of `t2`),
**	and each of its values is the product of one value of `t1` and one value of `t2`:
**	`result[i..., j...] = t1[i...] * t2[j...]`
*/
//!@{
s_tensor					Tensor_Product(s_tensor const* t1, s_tensor const* t2);
#define c_tensprod			Tensor_Product
#define Tensor_OuterProduct	Tensor_Product
#define Tensor_TensorProduct	Tensor_Product
//!@}

//!@doc Performs a tensor contraction on the two given tensors, along one axis of each
/*!
**	The axis `axis1` of the tensor `t1` and the axis `axis2` of the tensor `t2`
**	must have the same size: the resulting tensor sums over that shared axis,
**	and has an order of `t1->order + t2->order - 2` (its dimensions are those
**	of `t1` without `axis1`, followed by those of `t2` without `axis2`):
**	`result[i..., j...] = sum over k of (t1[i..., k, i...] * t2[j..., k, j...])`
**
**	This operation is the generalization of the matrix product to tensors:
**	- contracting two order-1 tensors (along their only axis) gives their dot
**	  product, as an order-0 scalar tensor
**	- contracting axis `1` of an order-2 tensor with axis `0` of another
**	  is exactly the matrix multiplication (see Matrix_Multiply())
**
**	@param	t1		The left-hand tensor of the contraction
**	@param	axis1	The axis of `t1` to contract (must be smaller than `t1->order`)
**	@param	t2		The right-hand tensor of the contraction
**	@param	axis2	The axis of `t2` to contract (must be smaller than `t2->order`)
**	@returns #TENSOR_NULL if either axis index is out of bounds,
**		or if the two axes to contract do not have the same size
*/
//!@{
s_tensor				Tensor_Contract(s_tensor const* t1, t_uint axis1, s_tensor const* t2, t_uint axis2);
#define c_tenscontract	Tensor_Contract
//!@}

//!@doc Performs a tensor contraction of the given `tensor` with itself, along two of its own axes
/*!
**	The two given axes must be different, and must have the same size:
**	the resulting tensor sums over the diagonal of those two axes, and has an
**	order of `tensor->order - 2` (its dimensions are those of the given `tensor`,
**	without `axis1` and `axis2`):
**	`result[i...] = sum over k of (tensor[i..., k, i..., k, i...])`
**
**	This operation is the generalization of the matrix trace to tensors:
**	tracing the two axes of an order-2 tensor gives the sum of the diagonal
**	values of that matrix, as an order-0 scalar tensor.
**
**	@param	tensor	The tensor to contract with itself
**	@param	axis1	The first axis to trace over (must be smaller than `tensor->order`)
**	@param	axis2	The second axis to trace over (must be different from `axis1`)
**	@returns #TENSOR_NULL if either axis index is out of bounds, if both axis
**		indices are identical, or if the two axes do not have the same size
*/
//!@{
s_tensor				Tensor_Trace(s_tensor const* tensor, t_uint axis1, t_uint axis2);
#define c_tenstrace		Tensor_Trace
//!@}

//!@doc Returns the transpose of the given 'tensor', permuting its axes according to the given `permutation`
/*!
**	@param	tensor		The tensor whose axes should be permuted
**	@param	permutation	The array of `tensor->order` axis indices: axis `i` of the
**		resulting tensor is axis `permutation[i]` of the given `tensor` (each axis
**		index must occur exactly once). If `NULL`, the axis order is reversed
**		(which, for an order-2 tensor, is exactly the matrix transposition).
**	@returns #TENSOR_NULL if the given `permutation` is not a valid permutation
*/
//!@{
s_tensor			Tensor_Transpose(s_tensor const* tensor, t_uint const* permutation);
#define c_tenstransp	Tensor_Transpose
//!@}

//!@doc Returns a copy of the given 'tensor', with its dimensions changed (but its values kept identical)
/*!
**	@param	tensor	The tensor whose dimensions should be changed
**	@param	order	The amount of axes/dimensions for the resulting tensor
**	@param	dims	The array of `order` axis sizes for the resulting tensor
**	@returns #TENSOR_NULL if the product of the new `dims` is not equal to the
**		total amount of values stored in the given `tensor`
*/
//!@{
s_tensor				Tensor_Reshape(s_tensor const* tensor, t_uint order, t_uint const* dims);
#define c_tensreshape	Tensor_Reshape
//!@}



//!@doc Returns an order-1 tensor which holds a copy of the values of the given `vector`
//!@{
s_tensor				Tensor_FromVector(s_vector const* vector);
#define c_vectotens		Tensor_FromVector
//!@}

//!@doc Returns an order-2 tensor which holds a copy of the values of the given `matrix`
//!@{
s_tensor				Tensor_FromMatrix(s_matrix const* matrix);
#define c_mattotens		Tensor_FromMatrix
//!@}

//!@doc Returns a vector which holds a copy of the values of the given order-1 `tensor`
/*!
**	@returns #VECTOR_NULL if the given `tensor` does not have an order of exactly `1`
*/
//!@{
s_vector				Tensor_ToVector(s_tensor const* tensor);
#define c_tenstovec		Tensor_ToVector
//!@}

//!@doc Returns a matrix which holds a copy of the values of the given order-2 `tensor`
/*!
**	@returns #MATRIX_NULL if the given `tensor` does not have an order of exactly `2`
*/
//!@{
s_matrix				Tensor_ToMatrix(s_tensor const* tensor);
#define c_tenstomat		Tensor_ToMatrix
//!@}



/*! @endgroup */
HEADER_END
#endif
