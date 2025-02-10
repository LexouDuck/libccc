/*============================================================================*\
||                                            ______________________________  ||
||  libccc/random/csprng.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_RANDOM_CSPRNG_H
#define __LIBCCC_RANDOM_CSPRNG_H
/*!@group{libccc_random_csprng,28,libccc/random/csprng.h}
**
**	This header defines cryptographically-secure pseudo-random number generator functions.
**
**  @nonstd
**
**  Inspired by https://github.com/Duthomhas/CSPRNG
**
**  @file
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

//! This type stores the current state of the random number generator
/*!
**	This type is intentionally opaque (it is platform-dependent)
*/
typedef void   t_csprng;



/*============================================================================*\
||                               CSPRNG Functions                             ||
\*============================================================================*/

//!@doc Creates a new CSPRNG state
/*!
**	@returns
**	A new CSPRNG state, or `NULL` if an error occurred.
*/
//!@{
t_csprng*			CSPRNG_New(void);
#define c_csprngnew	CSPRNG_New
//!@}

//!@doc Deletes (free and nullify) an existing CSPRNG state
/*!
**	@param	a_state	The address of the CSPRNG state to free and nullify
*/
//!@{
void				CSPRNG_Delete(t_csprng* *a_state);
#define c_csprngdel	CSPRNG_Delete
//!@}



/*============================================================================*\
||                          Stateful RNG functions                            ||
\*============================================================================*/

//!@doc	Writes `n` bytes of random data to `dest`.
/*!
**	@param	state	The CSPRNG state to use
**	@param	dest	The destination memory buffer to write to
**	@param	n		The amount of bytes of random data to write into `dest`
**	@returns `0` if successful, otherwise a non-zero error code
*/
//!@{
e_cccerror			CSPRNG_Next(t_csprng* state, void* dest, t_size n);
#define c_csprng	CSPRNG_Next
//!@}



//!@doc	Get a cryptographically secure random number
//!@{
t_uint				CSPRNG_Get_UInt(t_csprng* state);
#define c_csprngu	CSPRNG_Get_UInt
t_sint				CSPRNG_Get_SInt(t_csprng* state);
#define c_csprngs	CSPRNG_Get_SInt
t_fixed				CSPRNG_Get_Fixed(t_csprng* state);
#define c_csprngq	CSPRNG_Get_Fixed
t_float				CSPRNG_Get_Float(t_csprng* state);
#define c_csprngf	CSPRNG_Get_Float
//!@}

//!@doc	Get a cryptographically secure random number, in the range `[min, max[`
//!@{
t_uint				CSPRNG_GetInRange_UInt(t_csprng* state, t_uint  min, t_uint  max);
#define c_csprngxu	CSPRNG_GetInRange_UInt
t_sint				CSPRNG_GetInRange_SInt(t_csprng* state, t_sint  min, t_sint  max);
#define c_csprngxs	CSPRNG_GetInRange_SInt
t_fixed				CSPRNG_GetInRange_Fixed(t_csprng* state, t_fixed min, t_fixed max);
#define c_csprngxq	CSPRNG_GetInRange_Fixed
t_float				CSPRNG_GetInRange_Float(t_csprng* state, t_float min, t_float max);
#define c_csprngxf	CSPRNG_GetInRange_Float
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
void*				CSPRNG_Get(void* dest, t_size n);
#define c_csprngget	CSPRNG_Get
//!@}



//!@doc	Get a sample of cryptographically secure random number, statelessly.
//!@{
t_uint*				CSPRNG_Sample_UInt(t_size amount);
#define c_csprngnu	CSPRNG_Sample_UInt
t_sint*				CSPRNG_Sample_SInt(t_size amount);
#define c_csprngns	CSPRNG_Sample_SInt
t_fixed*			CSPRNG_Sample_Fixed(t_size amount);
#define c_csprngnq	CSPRNG_Sample_Fixed
t_float*			CSPRNG_Sample_Float(t_size amount);
#define c_csprngnf	CSPRNG_Sample_Float
//!@}

//!@doc	Get a sample of cryptographically secure random number, within the range `[min, max[`, statelessly.
//!@{
t_uint*				CSPRNG_SampleInRange_UInt(t_size amount, t_uint  min, t_uint  max);
#define c_csprngnxu	CSPRNG_SampleInRange_UInt
t_sint*				CSPRNG_SampleInRange_SInt(t_size amount, t_sint  min, t_sint  max);
#define c_csprngnxs	CSPRNG_SampleInRange_SInt
t_fixed*			CSPRNG_SampleInRange_Fixed(t_size amount, t_fixed min, t_fixed max);
#define c_csprngnxq	CSPRNG_SampleInRange_Fixed
t_float*			CSPRNG_SampleInRange_Float(t_size amount, t_float min, t_float max);
#define c_csprngnxf	CSPRNG_SampleInRange_Float
//!@}



/*! @endgroup */
HEADER_END
#endif
