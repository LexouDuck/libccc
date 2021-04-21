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
#ifndef T_NAME
#define T_NAME	
#endif
#ifndef T_DEFAULT
#define T_DEFAULT	NULL
#endif
#ifndef T_EQUALS
#define T_EQUALS(A, B)	((A) == (B))
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

#define Dict_T		CONCAT(Dict, T_NAME)
#define dict_T		CONCAT(dict, T_NAME)
#define s_dict_T	CONCAT(s_dict, T_NAME)

//! A simple dictionary struct, stores an array of key/value pairs.
/*
**	TODO document this
*/
typedef struct dict_T
{
	t_uint		length;	//!< The amount of key/value pairs stored in this dictionary
	s_keyval_T*	items;	//!< The array of key/value pairs stored in this dictionary
}				s_dict_T;



#define foreach_s_dict_init(		_TYPE_, _VAR_, _DICT_)	t_uint _VAR_##_i = 0;
#define foreach_s_dict_exit(		_TYPE_, _VAR_, _DICT_)	if ((void*)(_DICT_) != NULL && (_DICT_)->items != NULL)
#define foreach_s_dict_loop_init(	_TYPE_, _VAR_, _DICT_)	_TYPE_ _VAR_ = (_DICT_)->items[_VAR_##_i]
#define foreach_s_dict_loop_exit(	_TYPE_, _VAR_, _DICT_)	(_VAR_##_i < (_DICT_)->length)
#define foreach_s_dict_loop_incr(	_TYPE_, _VAR_, _DICT_)	++_VAR_##_i
#define foreach_s_dict_loop_setv(	_TYPE_, _VAR_, _DICT_)	_VAR_ = (_VAR_##_i == (_DICT_)->length ? _VAR_ : (_DICT_)->items[_VAR_##_i])


/*
** ************************************************************************** *|
**                             Basic Dict Operations                          *|
** ************************************************************************** *|
*/

//! TODO
s_dict_T	CONCAT(Dict_T,_New)(t_uint n, ...);

//! TODO
void		CONCAT(Dict_T,_Delete)(s_dict_T* dict);

//! TODO
s_dict_T	CONCAT(Dict_T,_Duplicate)(s_dict_T* dict);



//! TODO
void	CONCAT(Dict_T,_Get)(s_dict_T* dict, char* key);

//! TODO
void	CONCAT(Dict_T,_Set)(s_dict_T* dict, char* key, T value);

//! TODO
void	CONCAT(Dict_T,_Copy)(s_dict_T* dest, s_dict_T const* src, char** keys);

//! TODO
void	CONCAT(Dict_T,_Sub)(s_dict_T* dict, char** keys);



/*
** ************************************************************************** *|
**                            Dict Editing Operations                         *|
** ************************************************************************** *|
*/

//! TODO
s_keyval_T*	CONCAT(Dict_T,_Add)(s_dict_T* dict, char* key, T value);



//! TODO
void	CONCAT(Dict_T,_Remove)(s_dict_T* dict, char* key);

//! TODO
void	CONCAT(Dict_T,_Remove_F)(s_dict_T* dict, char* key, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_T,_RemoveAll)(s_dict_T* dict, char* key);

//! TODO
void	CONCAT(Dict_T,_RemoveAll_F)(s_dict_T* dict, char* key, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_T,_RemoveMatch)(s_dict_T* dict, T value);

//! TODO
void	CONCAT(Dict_T,_RemoveMatch_F)(s_dict_T* dict, T value, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_T,_RemoveMatches)(s_dict_T* dict, T value);

//! TODO
void	CONCAT(Dict_T,_RemoveMatches_F)(s_dict_T* dict, T value, void (*delete)(s_keyval_T* keyval));



//! TODO
void	CONCAT(Dict_T,_Replace)(s_dict_T* dict, char* key, s_keyval_T new);



/*
** ************************************************************************** *|
**                            Dict Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO
char*		CONCAT(Dict_T,_KeyOf)(s_dict_T* dict, T value);



//! TODO
s_keyval_T*	CONCAT(Dict_T,_Find)(s_dict_T* dict, s_keyval_T value);

//! TODO
s_keyval_T*	CONCAT(Dict_T,_Find_F)(s_dict_T* dict, t_bool (*match)(s_keyval_T value));

//! TODO
t_uint		CONCAT(Dict_T,_Count)(s_dict_T* dict, s_keyval_T value);

//! TODO
t_bool		CONCAT(Dict_T,_Contains)(s_dict_T* dict, s_keyval_T value);

//! TODO
t_bool		CONCAT(Dict_T,_Has)(s_dict_T* dict, s_dict_T* target);

//! TODO
t_bool		CONCAT(Dict_T,_HasOnly)(s_dict_T* dict, s_dict_T* target);



//! TODO
t_bool	CONCAT(Dict_T,_Equals)(s_dict_T* dict1, s_dict_T* dict2);

//! TODO
t_bool	CONCAT(Dict_T,_Equals_K)(s_dict_T* dict1, s_dict_T* dict2, char** keys);

//! TODO
t_sint	CONCAT(Dict_T,_Compare)(s_dict_T* dict1, s_dict_T* dict2, t_sint (*compare)(s_keyval_T item1, s_keyval_T item2));

//! TODO
t_sint	CONCAT(Dict_T,_Compare_K)(s_dict_T* dict1, s_dict_T* dict2, char** keys, t_sint (*compare)(s_keyval_T item1, s_keyval_T item2));



/*
** ************************************************************************** *|
**                           Dict Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO
void		CONCAT(Dict_T,_Iterate)(s_dict_T* dict, void (*f)(s_keyval_T item));

//! TODO
void		CONCAT(Dict_T,_Iterate_I)(s_dict_T* dict, void (*f)(s_keyval_T item));



//! TODO
s_dict_T*	CONCAT(Dict_T,_Map)(s_dict_T* dict, s_keyval_T (*map)(s_keyval_T item));

//! TODO
s_dict_T*	CONCAT(Dict_T,_Map_I)(s_dict_T* dict, s_keyval_T (*map)(s_keyval_T item));



//! TODO
s_dict_T*	CONCAT(Dict_T,_Filter)(s_dict_T* dict, t_bool (*filter)(s_keyval_T item));

//! TODO
s_dict_T*	CONCAT(Dict_T,_Filter_I)(s_dict_T* dict, t_bool (*filter)(s_keyval_T item));



//! TODO Dict_Reduce ?




/*! @} */
HEADER_END
#endif
