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
**	@isostd{C,https://en.cppreference.com/w/c/numeric/random}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/random/prng.h"
#include "libccc/random/csprng.h"

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
typedef LIBCONFIG_TYPE_RANDOM   t_rand;



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
