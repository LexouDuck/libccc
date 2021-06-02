/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/random/csprng.h                   |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_RANDOM_CSPRNG_H
#define __LIBCCC_RANDOM_CSPRNG_H
/*!@group{libccc_random_csprng}
** @{
**	This header defines cryptographically-secure pseudo-random number generator functions.
**
**  @nonstd
**
**  Inspired by https://github.com/Duthomhas/CSPRNG
**
**  @file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This type stores the current state of the random number generator
/*!
**	This type is intentionally opaque (it is platform-dependent)
*/
typedef void   t_csprng;



/*
** ************************************************************************** *|
**                               CSPRNG Functions                             *|
** ************************************************************************** *|
*/

//! Creates a new CSPRNG state
/*!
**	@returns
**	A new CSPRNG state, or `NULL` if an error occurred.
*/
t_csprng*			CSPRNG_New(void);
#define c_csprngnew	CSPRNG_New

//! Deletes (free and nullify) an existing CSPRNG state
/*!
**	@param	a_state	The address of the CSPRNG state to free and nullify
*/
void				CSPRNG_Delete(t_csprng* *a_state);
#define c_csprngdel	CSPRNG_Delete



/*
** ************************************************************************** *|
**                          Stateful RNG functions                            *|
** ************************************************************************** *|
*/

//!	Writes `n` bytes of random data to `dest`.
/*!
**	@param	state	The CSPRNG state to use
**	@param	dest	The destination memory buffer to write to
**	@param	n		The amount of bytes of random data to write into `dest`
**	@returns `0` if successful, otherwise a non-zero error code
*/
e_cccerror			CSPRNG_Next			(t_csprng* state, void* dest, t_size n);
#define c_csprng	CSPRNG_Next


//!	Get a cryptographically secure random unsigned integer value
t_uint				CSPRNG_UInt			(t_csprng* state);
#define c_csprngu	CSPRNG_UInt

//!	Get a cryptographically secure random unsigned integer value, in the range `[min, max[`
t_uint				CSPRNG_UInt_Range	(t_csprng* state, t_uint  min, t_uint  max);
#define c_csprngui	CSPRNG_UInt_Range


//!	Get a cryptographically secure random integer value
t_sint				CSPRNG_SInt			(t_csprng* state);
#define c_csprngs	CSPRNG_SInt

//!	Get a cryptographically secure random integer value, in the range `[min, max[`
t_sint				CSPRNG_SInt_Range	(t_csprng* state, t_sint  min, t_sint  max);
#define c_csprngsi	CSPRNG_SInt_Range


//!	Get a cryptographically secure random fixed-point value
t_fixed				CSPRNG_Fixed		(t_csprng* state);
#define c_csprngq	CSPRNG_Fixed

//!	Get a cryptographically secure random fixed-point value, in the range `[min, max[`
t_fixed				CSPRNG_Fixed_Range	(t_csprng* state, t_fixed min, t_fixed max);
#define c_csprngqi	CSPRNG_Fixed_Range


//!	Get a cryptographically secure random floating-point value
t_float				CSPRNG_Float		(t_csprng* state);
#define c_csprngf	CSPRNG_Float

//!	Get a cryptographically secure random floating-point value, in the range `[min, max[`
t_float				CSPRNG_Float_Range	(t_csprng* state, t_float min, t_float max);
#define c_csprngfi	CSPRNG_Float_Range



/*
** ************************************************************************** *|
**                         Stateless RNG functions                            *|
** ************************************************************************** *|
*/

//!	Writes `n` bytes of random data to `dest` (creating and deleting a state).
/*!
**	@param	dest	The destination memory buffer to write to
**	@param	n		The amount of bytes of random data to write into `dest`
**	@returns `dest` if successful, otherwise a `NULL` pointer
*/
void*					CSPRNG_Get				(void* dest, t_size n);
#define c_csprngget		CSPRNG_Get


//!	Get a cryptographically secure random unsigned integer, statelessly.
t_uint					CSPRNG_UInt_Get			(void);
#define c_csprnggetu	CSPRNG_UInt_Get

//!	Get a cryptographically secure random unsigned integer, within the range `[min, max[`, statelessly.
t_uint					CSPRNG_UInt_Get_Range	(t_uint  min, t_uint  max);
#define c_csprnggetui	CSPRNG_UInt_Get_Range


//!	Get a cryptographically secure random integer value, statelessly.
t_sint					CSPRNG_SInt_Get			(void);
#define c_csprnggets	CSPRNG_SInt_Get

//!	Get a cryptographically secure random integer value, within the range `[min, max[`, statelessly.
t_sint					CSPRNG_SInt_Get_Range	(t_sint  min, t_sint  max);
#define c_csprnggetsi	CSPRNG_SInt_Get_Range


//!	Get a cryptographically secure random fixed-point value, statelessly.
t_fixed					CSPRNG_Fixed_Get		(void);
#define c_csprnggetq	CSPRNG_Fixed_Get

//!	Get a cryptographically secure random fixed-point value, within the range `[min, max[`, statelessly.
t_fixed					CSPRNG_Fixed_Get_Range	(t_fixed min, t_fixed max);
#define c_csprnggetqi	CSPRNG_Fixed_Get_Range


//!	Get a cryptographically secure random floating-point value, statelessly.
t_float					CSPRNG_Float_Get		(void);
#define c_csprnggetf	CSPRNG_Float_Get

//!	Get a cryptographically secure random floating-point value, within the range `[min, max[`, statelessly.
t_float					CSPRNG_Float_Get_Range	(t_float min, t_float max);
#define c_csprnggetfi	CSPRNG_Float_Get_Range



/*! @} */
HEADER_END
#endif
