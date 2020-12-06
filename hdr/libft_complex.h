/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_complex.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
s_complex*			Complex_New(t_float re, t_float im);
#define ft_cplxnew	Complex_New

//! Returns the result of the addition of the two given complex numbers
s_complex			Complex_Add(s_complex const* c1, s_complex const* c2);
#define ft_cplxadd	Complex_Add

//! Returns the result of the subtraction of the two given complex numbers
s_complex			Complex_Subtract(s_complex const* c1, s_complex const* c2);
#define ft_cplxsub	Complex_Subtract
#define Complex_Sub	Complex_Subtract

//! Returns the result of the multiplication of the two given complex numbers
s_complex			Complex_Multiply(s_complex const* c1, s_complex const* c2);
#define ft_cplxmul	Complex_Multiply
#define Complex_Mul	Complex_Multiply

//! Returns the result of the divide of the two given complex numbers
s_complex			Complex_Divide(s_complex const* c1, s_complex const* c2);
#define ft_cplxdiv	Complex_Divide
#define Complex_Div	Complex_Divide



/*
** ************************************************************************** *|
**                            Quaternion Operations                           *|
** ************************************************************************** *|
*/

// TODO define, implement, document



/*! @} */
HEADER_END
#endif
