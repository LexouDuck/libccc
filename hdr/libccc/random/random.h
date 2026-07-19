/*============================================================================*\
||                                            ______________________________  ||
||  libccc/random/random.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_RANDOM_RANDOM_H
#define __LIBCCC_RANDOM_RANDOM_H
/*!@group{libccc_random_random,26,libccc/random/random.h}
**
**	This header defines some simple pseudo-random number generator functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/random}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/random/prng.h"
#include "libccc/random/csprng.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! This type stores the current state of the random number generator
/*!
**	This type is intentionally opaque (it is platform-dependent)
*/
typedef LIBCONFIG_RANDOM_TYPE   t_rand;



/*============================================================================*\
||                               Random Functions                             ||
\*============================================================================*/

//!@doc Sets the seed of the given random number generator `state`
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_SetSeed(), CSPRNG_SetSeed()
*/
//!@{
#define				Random_SetSeed	CONCAT(LIBCONFIG_RANDOM_NAME,_SetSeed)
#define c_srand		Random_SetSeed
//!@}

//!@doc Randomizes the seed of the given random number generator `state`
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_NewSeed(), CSPRNG_NewSeed()
*/
//!@{
#define				Random_NewSeed	CONCAT(LIBCONFIG_RANDOM_NAME,_NewSeed)
#define c_nrand		Random_NewSeed
//!@}



//!@doc Allocates a new random number generator state
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_New(), CSPRNG_New()
*/
//!@{
#define				Random_New		CONCAT(LIBCONFIG_RANDOM_NAME,_New)
#define c_randnew	Random_New
//!@}

//!@doc Deletes (frees and nullifies) an existing random number generator state
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_Delete(), CSPRNG_Delete()
*/
//!@{
#define				Random_Delete	CONCAT(LIBCONFIG_RANDOM_NAME,_Delete)
#define c_randdel	Random_Delete
//!@}



//!@doc Writes `n` bytes of random data to `dest`, using the given RNG `state`
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_Next(), CSPRNG_Next()
*/
//!@{
#define				Random_Next		CONCAT(LIBCONFIG_RANDOM_NAME,_Next)
#define c_rand		Random_Next
//!@}

//!@doc Writes `n` bytes of random data to `dest`, statelessly (creating and deleting a state)
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_Get(), CSPRNG_Get()
*/
//!@{
#define				Random_Get		CONCAT(LIBCONFIG_RANDOM_NAME,_Get)
#define c_randget	Random_Get
//!@}



//!@doc Gets a random number, using the given RNG `state`
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_Get_UInt(), CSPRNG_Get_UInt()
*/
//!@{
#define				Random_Get_UInt			CONCAT(LIBCONFIG_RANDOM_NAME,_Get_UInt)
#define c_randu		Random_Get_UInt
#define				Random_Get_SInt			CONCAT(LIBCONFIG_RANDOM_NAME,_Get_SInt)
#define c_rands		Random_Get_SInt
#define				Random_Get_Fixed		CONCAT(LIBCONFIG_RANDOM_NAME,_Get_Fixed)
#define c_randq		Random_Get_Fixed
#define				Random_Get_Float		CONCAT(LIBCONFIG_RANDOM_NAME,_Get_Float)
#define c_randf		Random_Get_Float
//!@}

//!@doc Gets a random number within the range `[min, max[`, using the given RNG `state`
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_GetInRange_UInt(), CSPRNG_GetInRange_UInt()
*/
//!@{
#define				Random_GetInRange_UInt	CONCAT(LIBCONFIG_RANDOM_NAME,_GetInRange_UInt)
#define c_randxu	Random_GetInRange_UInt
#define				Random_GetInRange_SInt	CONCAT(LIBCONFIG_RANDOM_NAME,_GetInRange_SInt)
#define c_randxs	Random_GetInRange_SInt
#define				Random_GetInRange_Fixed	CONCAT(LIBCONFIG_RANDOM_NAME,_GetInRange_Fixed)
#define c_randxq	Random_GetInRange_Fixed
#define				Random_GetInRange_Float	CONCAT(LIBCONFIG_RANDOM_NAME,_GetInRange_Float)
#define c_randxf	Random_GetInRange_Float
//!@}

//!@doc Gets a newly allocated sample (array) of random numbers, statelessly
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_Sample_UInt(), CSPRNG_Sample_UInt()
*/
//!@{
#define				Random_Sample_UInt		CONCAT(LIBCONFIG_RANDOM_NAME,_Sample_UInt)
#define c_randnu	Random_Sample_UInt
#define				Random_Sample_SInt		CONCAT(LIBCONFIG_RANDOM_NAME,_Sample_SInt)
#define c_randns	Random_Sample_SInt
#define				Random_Sample_Fixed		CONCAT(LIBCONFIG_RANDOM_NAME,_Sample_Fixed)
#define c_randnq	Random_Sample_Fixed
#define				Random_Sample_Float		CONCAT(LIBCONFIG_RANDOM_NAME,_Sample_Float)
#define c_randnf	Random_Sample_Float
//!@}

//!@doc Gets a newly allocated sample (array) of random numbers within the range `[min, max[`, statelessly
/*!
**	This is a configurable macro alias: it resolves to the corresponding
**	function of the RNG implementation which was chosen via the
**	`LIBCONFIG_RANDOM_NAME` configuration macro (by default, the simple
**	`PRNG_*` functions - can also be set to the cryptographically-secure
**	`CSPRNG_*` functions).
**
**	@see PRNG_SampleInRange_UInt(), CSPRNG_SampleInRange_UInt()
*/
//!@{
#define				Random_SampleInRange_UInt	CONCAT(LIBCONFIG_RANDOM_NAME,_SampleInRange_UInt)
#define c_randnxu	Random_SampleInRange_UInt
#define				Random_SampleInRange_SInt	CONCAT(LIBCONFIG_RANDOM_NAME,_SampleInRange_SInt)
#define c_randnxs	Random_SampleInRange_SInt
#define				Random_SampleInRange_Fixed	CONCAT(LIBCONFIG_RANDOM_NAME,_SampleInRange_Fixed)
#define c_randnxq	Random_SampleInRange_Fixed
#define				Random_SampleInRange_Float	CONCAT(LIBCONFIG_RANDOM_NAME,_SampleInRange_Float)
#define c_randnxf	Random_SampleInRange_Float
//!@}



/*! @endgroup */
HEADER_END
#endif
