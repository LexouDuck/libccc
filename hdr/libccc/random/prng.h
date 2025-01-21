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

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/pointer.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

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



/*============================================================================*\
||                               Random Functions                             ||
\*============================================================================*/

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



/*============================================================================*\
||                          Stateful RNG functions                            ||
\*============================================================================*/

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



//!@doc	Get a random number
//!@{
t_uint				PRNG_Get_UInt(t_prng* state);
#define c_prngu		PRNG_Get_UInt
t_sint				PRNG_Get_SInt(t_prng* state);
#define c_prngs		PRNG_Get_SInt
t_fixed				PRNG_Get_Fixed(t_prng* state);
#define c_prngq		PRNG_Get_Fixed
t_float				PRNG_Get_Float(t_prng* state);
#define c_prngf		PRNG_Get_Float
//!@}

//!@doc	Get a random number, in the range `[min, max[`
//!@{
t_uint				PRNG_GetInRange_UInt(t_prng* state, t_uint  min, t_uint  max);
#define c_prngxu	PRNG_GetInRange_UInt
t_sint				PRNG_GetInRange_SInt(t_prng* state, t_sint  min, t_sint  max);
#define c_prngxs	PRNG_GetInRange_SInt
t_fixed				PRNG_GetInRange_Fixed(t_prng* state, t_fixed min, t_fixed max);
#define c_prngxq	PRNG_GetInRange_Fixed
t_float				PRNG_GetInRange_Float(t_prng* state, t_float min, t_float max);
#define c_prngxf	PRNG_GetInRange_Float
//!@}



/*============================================================================*\
||                         Stateless RNG functions                            ||
\*============================================================================*/

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



//!@doc	Get a sample of numbers, statelessly.
//!@{
t_uint*				PRNG_Sample_UInt(t_size amount);
#define c_prngnu	PRNG_Sample_UInt
t_sint*				PRNG_Sample_SInt(t_size amount);
#define c_prngns	PRNG_Sample_SInt
t_fixed*			PRNG_Sample_Fixed(t_size amount);
#define c_prngnq	PRNG_Sample_Fixed
t_float*			PRNG_Sample_Float(t_size amount);
#define c_prngnf	PRNG_Sample_Float
//!@}

//!@doc	Get a sample of numbers, within the range `[min, max[`, statelessly.
//!@{
t_uint*				PRNG_SampleInRange_UInt(t_size amount, t_uint min, t_uint max);
#define c_prngnxu	PRNG_SampleInRange_UInt
t_sint*				PRNG_SampleInRange_SInt	(t_size amount, t_sint min, t_sint max);
#define c_prngnxs	PRNG_SampleInRange_SInt
t_fixed*			PRNG_SampleInRange_Fixed(t_size amount, t_fixed min, t_fixed max);
#define c_prngnxq	PRNG_SampleInRange_Fixed
t_float*			PRNG_SampleInRange_Float(t_size amount, t_float min, t_float max);
#define c_prngnxf	PRNG_SampleInRange_Float
//!@}



/*! @endgroup */
HEADER_END
#endif
