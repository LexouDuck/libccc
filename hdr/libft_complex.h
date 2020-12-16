/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_complex.h                         |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBFT_COMPLEX_H
#define __LIBFT_COMPLEX_H
/*! @file libft_complex.h
**	This header defines useful algebra and calculus types, and functions.
**	@addtogroup libft_math
**	@{
*/
// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A struct to store complex/imaginary number values
typedef struct	s_complex_
{
	t_float		re;		//!< The "real" part of this complex number
	t_float		im;		//!< The "imaginary" part of this complex number
}				s_complex;



//! A struct for storing quaternions
typedef struct		s_quaternion_
{
	t_float		s;		//!< The S value of this quaternion
	t_float		i;		//!< The I value of this quaternion
	t_float		j;		//!< The J value of this quaternion
	t_float		k;		//!< The K value of this quaternion
}					s_quaternion;



/*
** ************************************************************************** *|
**                          Complex Number Operations                         *|
** ************************************************************************** *|
*/

//! Allocates a new complex number struct on heap, with the given 're' real part and 'im' imaginary part
s_complex*				Complex_New(t_float re, t_float im);
#define ft_cplxnew		Complex_New

//! Returns TRUE if the two given complex numbers are equal
t_bool					Complex_Equals(s_complex const* z1, s_complex const* z2);
#define ft_cplxequ		Complex_Equals

//! Returns the absolute value |z| of the given complex number 'z' (its distance from zero)
t_float					Complex_Abs(s_complex const* z1);
#define ft_cplxabs		Complex_Abs
#define Complex_Modulus	Complex_Abs

//! Returns the conjugate of the given complex number (inverts the sign of its imaginary part)
s_complex				Complex_Conjugate(s_complex const* z1);
#define ft_cplxconj		Complex_Conjugate
#define Complex_Conj	Complex_Conjugate

//! Returns the result of the addition of the two given complex numbers
s_complex				Complex_Add(s_complex const* z1, s_complex const* z2);
#define ft_cplxadd		Complex_Add

//! Returns the result of the subtraction of the two given complex numbers
s_complex				Complex_Subtract(s_complex const* z1, s_complex const* z2);
#define ft_cplxsub		Complex_Subtract
#define Complex_Sub		Complex_Subtract

//! Returns the result of the multiplication of the two given complex numbers
s_complex				Complex_Multiply(s_complex const* z1, s_complex const* z2);
#define ft_cplxmul		Complex_Multiply
#define Complex_Mul		Complex_Multiply

//! Returns the result of the divide of the two given complex numbers
s_complex				Complex_Divide(s_complex const* z1, s_complex const* z2);
#define ft_cplxdiv		Complex_Divide
#define Complex_Div		Complex_Divide

//! Returns the given complex number, to the power of 'n'
s_complex				Complex_Power(s_complex const* z, t_u8 n);
#define ft_cplxpow		Complex_Power
#define Complex_Pow		Complex_Power

// TODO add polar form operations



/*
** ************************************************************************** *|
**                            Quaternion Operations                           *|
** ************************************************************************** *|
*/

// TODO define, implement, document



/*! @} */
HEADER_END
#endif
