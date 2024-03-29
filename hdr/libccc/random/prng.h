/*============================================================================*\
||                                            ______________________________  ||
||  libccc/random/prng.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_RANDOM_PRNG_H
#define __LIBCCC_RANDOM_PRNG_H
/*!@group{libccc_random_prng,27,libccc/random/prng.h}
**
**	This header defines some simple pseudo-random number generator functions.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/pointer.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//!@doc Pseudo-random number generator (Linear Congruential Generator). Modulus is `2^31`
/*!
**	- `PRNG_OFFSET` and `PRNG_MODULUS` are mutually prime.
**	- `PRNG_CEIL_SQRT_MOD % 4` should be equal to 1 because `PRNG_MODULUS` is a multiple of 4
**	- For all P prime divisors of `PRNG_MODULUS`, `a % p = 1`
**	- `PRNG_OFFSET` should be small compared to the two other parameters
**	- The bitwise AND `&` operator is applied, which explains the choice of modulus
**		to be `2^31 - 1` in implementation (could also be called `RAND_MAX`)
**
**	Basic RNG formula is:
**		`next_value = (PRNG_CEIL_SQRT_MOD * old_nb + PRNG_OFFSET) % PRNG_MODULUS`
**
**	@see https://www.freecodecamp.org/news/random-number-generator/
*/
//!@{

//! The default random seed for pseudo-random number generation
#define PRNG_SEED_DEFAULT	(0x93E21FD5)

//! Modulus for the Linear Congruential RNG
#define PRNG_MODULUS		(0x7FFFFFFF)
//! The value of the multiplier for the Linear Congruential RNG
#define PRNG_CEIL_SQRT_MOD	(46341)
//! The value of the increment for the Linear Congruential RNG
#define PRNG_OFFSET			(2835)

//!@}



//! This type stores the current state of the random number generator
typedef t_u32   t_prng;



/*
** ************************************************************************** *|
**                               Random Functions                             *|
** ************************************************************************** *|
*/

//!@doc TODO document this
//!@{
void				PRNG_SetSeed(t_prng* state, t_u32 seed);
#define c_sprng		PRNG_SetSeed
//!@}

//!@doc Randomizes the current seed, using PRNG_Shuffle()
//!@{
void				PRNG_NewSeed(t_prng* state);
#define c_nprng		PRNG_NewSeed
//!@}



//!@doc Creates a new PRNG state
/*!
**	@returns
**	A new PRNG state, or `NULL` if an error occurred.
*/
//!@{
t_prng*				PRNG_New(void);
#define c_prngnew	PRNG_New
//!@}

//!@doc Deletes (free and nullify) an existing PRNG state
/*!
**	@param	a_state	The address of the PRNG state to free and nullify
*/
//!@{
void				PRNG_Delete(t_prng* *a_state);
#define c_prngdel	PRNG_Delete
//!@}



/*
** ************************************************************************** *|
**                          Stateful RNG functions                            *|
** ************************************************************************** *|
*/

//!@doc	Writes `n` bytes of random data to `dest`.
/*!
**	@param	state	The PRNG state to use
**	@param	dest	The destination memory buffer to write to
**	@param	n		The amount of bytes of random data to write into `dest`
**	@returns
**	`0`(#OK) if successful, otherwise a non-zero error code
*/
//!@{
e_cccerror			PRNG_Next(t_prng* state, void* dest, t_size n);
#define c_prng		PRNG_Next
//!@}



//!@doc	Get a random unsigned integer value
//!@{
t_uint				PRNG_UInt(t_prng* state);
#define c_prngu		PRNG_UInt
//!@}
//!@doc	Get a random unsigned integer value, in the range `[min, max[`
//!@{
t_uint				PRNG_UInt_Range(t_prng* state, t_uint  min, t_uint  max);
#define c_prngxu	PRNG_UInt_Range
//!@}

//!@doc	Get a random integer value
//!@{
t_sint				PRNG_SInt(t_prng* state);
#define c_prngs		PRNG_SInt
//!@}
//!@doc	Get a random integer value, in the range `[min, max[`
//!@{
t_sint				PRNG_SInt_Range(t_prng* state, t_sint  min, t_sint  max);
#define c_prngxs	PRNG_SInt_Range
//!@}

//!@doc	Get a random fixed-point value
//!@{
t_fixed				PRNG_Fixed(t_prng* state);
#define c_prngq		PRNG_Fixed
//!@}
//!@doc	Get a random fixed-point value, in the range `[min, max[`
//!@{
t_fixed				PRNG_Fixed_Range(t_prng* state, t_fixed min, t_fixed max);
#define c_prngxq	PRNG_Fixed_Range
//!@}

//!@doc	Get a random floating-point value
//!@{
t_float				PRNG_Float(t_prng* state);
#define c_prngf		PRNG_Float
//!@}
//!@doc	Get a random floating-point value, in the range `[min, max[`
//!@{
t_float				PRNG_Float_Range(t_prng* state, t_float min, t_float max);
#define c_prngxf	PRNG_Float_Range
//!@}



/*
** ************************************************************************** *|
**                         Stateless RNG functions                            *|
** ************************************************************************** *|
*/

//!@doc	Writes `n` bytes of random data to `dest` (creating and deleting a state).
/*!
**	@param	dest	The destination memory buffer to write to
**	@param	n		The amount of bytes of random data to write into `dest`
**	@returns `dest` if successful, otherwise a `NULL` pointer
*/
//!@{
void*				PRNG_Get(void* dest, t_size n);
#define c_prngget	PRNG_Get
//!@}



//!@doc	Get a random unsigned integer, statelessly.
//!@{
t_uint				PRNG_UInt_Get(void);
#define c_prnggetu	PRNG_UInt_Get
//!@}
//!@doc	Get a random unsigned integer, within the range `[min, max[`, statelessly.
//!@{
t_uint				PRNG_UInt_Get_Range(t_uint  min, t_uint  max);
#define c_prnggetxu	PRNG_UInt_Get_Range
//!@}

//!@doc	Get a random integer value, statelessly.
//!@{
t_sint				PRNG_SInt_Get(void);
#define c_prnggets	PRNG_SInt_Get
//!@}
//!@doc	Get a random integer value, within the range `[min, max[`, statelessly.
//!@{
t_sint				PRNG_SInt_Get_Range	(t_sint  min, t_sint  max);
#define c_prnggetxs	PRNG_SInt_Get_Range
//!@}

//!@doc	Get a random fixed-point value, statelessly.
//!@{
t_fixed				PRNG_Fixed_Get(void);
#define c_prnggetq	PRNG_Fixed_Get
//!@}
//!@doc	Get a random fixed-point value, within the range `[min, max[`, statelessly.
//!@{
t_fixed				PRNG_Fixed_Get_Range(t_fixed min, t_fixed max);
#define c_prnggetxq	PRNG_Fixed_Get_Range
//!@}

//!@doc	Get a random floating-point value, statelessly.
//!@{
t_float				PRNG_Float_Get(void);
#define c_prnggetf	PRNG_Float_Get
//!@}
//!@doc	Get a random floating-point value, within the range `[min, max[`, statelessly.
//!@{
t_float				PRNG_Float_Get_Range(t_float min, t_float max);
#define c_prnggetxf	PRNG_Float_Get_Range
//!@}



/*! @endgroup */
HEADER_END
#endif
