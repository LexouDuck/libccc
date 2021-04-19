/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/dict.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_DICT_H
#define __LIBCCC_MONAD_DICT_H
/*!@group{libccc_monad_dict}
** @{
**	This header defines a simple dictionary type and utility functions for it.
**
**	@file
*/

#ifndef T
#define T	void*
#endif

#ifndef TYPE
#define TYPE	
#endif

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/monad/keyval.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#ifdef	dict_T
#undef	dict_T
#endif
#define dict_T		CONCAT(dict, TYPE)

#ifdef	s_dict_T
#undef	s_dict_T
#endif
#define s_dict_T	CONCAT(s_dict, TYPE)

//! A simple dictionary struct, stores an array of key/value pairs.
/*
**	TODO document this
*/
typedef struct dict_T
{
	t_size		length;	//!< The amount of key/value pairs stored in this dictionary
	s_keyval_T*	items;	//!< The array of key/value pairs stored in this dictionary
}				s_dict_T;
TYPEDEF_ALIAS(	s_dict_T, DICT, STRUCT)



#define foreach_s_dict_init(		_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_exit(		_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_init(	_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_exit(	_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_incr(	_TYPE_, _VAR_, _DICT_)	



/*
** ************************************************************************** *|
**                             Basic Dict Operations                          *|
** ************************************************************************** *|
*/

// TODO Dict_New
// TODO Dict_Delete
// TODO Dict_Duplicate

// TODO Dict_Get
// TODO Dict_Set
// TODO Dict_Copy
// TODO Dict_Sub

// TODO Dict_Append
// TODO Dict_Prepend
// TODO Dict_Insert
// TODO Dict_Replace

// TODO Dict_Find
// TODO Dict_IndexOf

// TODO Dict_Equals
// TODO Dict_Equals_N
// TODO Dict_Compare
// TODO Dict_Compare_N

// TODO Dict_Iterate
// TODO Dict_Iterate_I
// TODO Dict_Map
// TODO Dict_Map_I
// TODO Dict_Filter
// TODO Dict_Filter_I

// TODO Dict_Reduce ?



/*! @} */
HEADER_END
#endif
