/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/random/random.h                   |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_RANDOM_RANDOM_H
#define __LIBCCC_RANDOM_RANDOM_H
/*!@group{libccc_random_random}
** @{
**	This header defines some simple pseudo-random number generator functions.
**
**	@isostd{https://en.cppreference.com/w/c/numeric/random}
**
**	@file
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

/*!
**	Pseudo-random number generator. Modulus is `2^31`
**
**	- `OFFSET` and `MODULUS` are mutually prime.
**	- `CEIL_SQRT_MOD % 4` should be equal to 1 because `MODULUS` is a multiple of 4
**	- For all P prime divisors of `MODULUS`, `a % p = 1`
**	- `OFFSET` should be small compared to the two other parameters
**	- The bitwise AND `&` operator is applied, which explains the choice of modulus
**		to be `2^31 - 1` in implementation (could also be called RAND_MAX)
**
**	Basic RNG formula is:
**		`next_value = (CEIL_SQRT_MOD * old_nb + OFFSET) % MODULUS`
*/
//!@{

//! The default random seed for pseudo-random number generation
#define DEFAULT_SEED	(0x93E21FD5)

//! TODO document this
#define MODULUS			(0x7FFFFFFF)
//! TODO document this
#define CEIL_SQRT_MOD	(46341)
//! TODO document this
#define OFFSET			(2835)

//!@}



//! This type stores the current state of the random number generator
/*!
**	This type is intentionally opaque (it is platform-dependent)
*/
typedef void   t_rand;



/*
** ************************************************************************** *|
**                               Random Functions                             *|
** ************************************************************************** *|
*/

#define				Random_SetSeed	CONCAT(LIBCONFIG_NAME_RANDOM,_SetSeed)
#define c_srand		Random_SetSeed

#define				Random_NewSeed	CONCAT(LIBCONFIG_NAME_RANDOM,_NewSeed)
#define c_nrand		Random_NewSeed



#define				Random_New		CONCAT(LIBCONFIG_NAME_RANDOM,_New)
#define c_randnew	Random_New

#define				Random_Delete	CONCAT(LIBCONFIG_NAME_RANDOM,_Delete)
#define c_randdel	Random_Delete



#define				Random_Next		CONCAT(LIBCONFIG_NAME_RANDOM,_Next)
#define c_rand		Random_Next

#define				Random_Get		CONCAT(LIBCONFIG_NAME_RANDOM,_Get)
#define c_randget	Random_Get



#define				Random_UInt			CONCAT(LIBCONFIG_NAME_RANDOM,_UInt)
#define c_randu		Random_UInt

#define				Random_UInt_Range	CONCAT(LIBCONFIG_NAME_RANDOM,_UInt_Range)
#define c_randui	Random_UInt_Range



#define				Random_SInt			CONCAT(LIBCONFIG_NAME_RANDOM,_SInt)
#define c_rands		Random_SInt

#define				Random_SInt_Range	CONCAT(LIBCONFIG_NAME_RANDOM,_SInt_Range)
#define c_randsi	Random_SInt_Range



#define				Random_Fixed		CONCAT(LIBCONFIG_NAME_RANDOM,_Fixed)
#define c_randq		Random_Fixed

#define				Random_Fixed_Range	CONCAT(LIBCONFIG_NAME_RANDOM,_Fixed_Range)
#define c_randqi	Random_Fixed_Range



#define				Random_Float		CONCAT(LIBCONFIG_NAME_RANDOM,_Float)
#define c_randf		Random_Float

#define				Random_Float_Range	CONCAT(LIBCONFIG_NAME_RANDOM,_Float_Range)
#define c_randfi	Random_Float_Range




/*! @} */
HEADER_END
#endif
