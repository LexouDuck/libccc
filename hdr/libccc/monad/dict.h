/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/dict.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_DICT_H
#define __LIBCCC_MONAD_DICT_H
/*!@group{libccc_monad_dict}
** @{
**	This header defines a generic dictionary type and utility functions for it.
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

#include "libccc/bool.h"
#include "libccc/int.h"

#include "libccc/monad/keyval.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

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
s_dict_T	CONCAT(Dict,T_NAME)(t_uint n, ...);

//! TODO
s_dict_T*	CONCAT(Dict_New,T_NAME)(t_uint n, ...);

//! TODO
void		CONCAT(Dict_Delete,T_NAME)(s_dict_T* dict);

//! TODO
void		CONCAT(Dict_Delete_F,T_NAME)(s_dict_T* dict, void (*delete)(s_keyval_T* keyval));

//! TODO
s_dict_T	CONCAT(Dict_Duplicate,T_NAME)(s_dict_T* dict);



//! TODO
void	CONCAT(Dict_Get,T_NAME)(s_dict_T* dict, t_char* key);

//! TODO
void	CONCAT(Dict_Set,T_NAME)(s_dict_T* dict, t_char* key, T value);

//! TODO
void	CONCAT(Dict_Copy,T_NAME)(s_dict_T* dest, s_dict_T const* src, t_char** keys);

//! TODO
void	CONCAT(Dict_Sub,T_NAME)(s_dict_T* dict, t_char** keys);



/*
** ************************************************************************** *|
**                            Dict Editing Operations                         *|
** ************************************************************************** *|
*/

//! TODO
s_keyval_T*	CONCAT(Dict_Add,T_NAME)(s_dict_T* dict, t_char* key, T value);



//! TODO
void	CONCAT(Dict_Remove,T_NAME)(s_dict_T* dict, t_char* key);

//! TODO
void	CONCAT(Dict_Remove_F,T_NAME)(s_dict_T* dict, t_char* key, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_RemoveAll,T_NAME)(s_dict_T* dict, t_char* key);

//! TODO
void	CONCAT(Dict_RemoveAll_F,T_NAME)(s_dict_T* dict, t_char* key, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_RemoveMatch,T_NAME)(s_dict_T* dict, T value);

//! TODO
void	CONCAT(Dict_RemoveMatch_F,T_NAME)(s_dict_T* dict, T value, void (*delete)(s_keyval_T* keyval));

//! TODO
void	CONCAT(Dict_RemoveMatches,T_NAME)(s_dict_T* dict, T value);

//! TODO
void	CONCAT(Dict_RemoveMatches_F,T_NAME)(s_dict_T* dict, T value, void (*delete)(s_keyval_T* keyval));



//! TODO
void	CONCAT(Dict_Replace,T_NAME)(s_dict_T* dict, t_char* key, s_keyval_T new);



/*
** ************************************************************************** *|
**                            Dict Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO
t_char*		CONCAT(Dict_KeyOf,T_NAME)(s_dict_T* dict, T value);



//! TODO
s_keyval_T*	CONCAT(Dict_Find,T_NAME)(s_dict_T* dict, s_keyval_T value);

//! TODO
s_keyval_T*	CONCAT(Dict_Find_F,T_NAME)(s_dict_T* dict, t_bool (*match)(s_keyval_T value));

//! TODO
t_uint		CONCAT(Dict_Count,T_NAME)(s_dict_T* dict, s_keyval_T value);

//! TODO
t_bool		CONCAT(Dict_Contains,T_NAME)(s_dict_T* dict, s_keyval_T value);

//! TODO
t_bool		CONCAT(Dict_Has,T_NAME)(s_dict_T* dict, s_dict_T* target);

//! TODO
t_bool		CONCAT(Dict_HasOnly,T_NAME)(s_dict_T* dict, s_dict_T* target);



//! TODO
t_bool	CONCAT(Dict_Equals,T_NAME)(s_dict_T* dict1, s_dict_T* dict2);

//! TODO
t_bool	CONCAT(Dict_Equals_K,T_NAME)(s_dict_T* dict1, s_dict_T* dict2, t_char** keys);

//! TODO
t_sint	CONCAT(Dict_Compare,T_NAME)(s_dict_T* dict1, s_dict_T* dict2, t_sint (*compare)(s_keyval_T item1, s_keyval_T item2));

//! TODO
t_sint	CONCAT(Dict_Compare_K,T_NAME)(s_dict_T* dict1, s_dict_T* dict2, t_char** keys, t_sint (*compare)(s_keyval_T item1, s_keyval_T item2));



/*
** ************************************************************************** *|
**                           Dict Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO
void		CONCAT(Dict_Iterate,T_NAME)(s_dict_T* dict, void (*f)(s_keyval_T item));

//! TODO
void		CONCAT(Dict_Iterate_I,T_NAME)(s_dict_T* dict, void (*f)(s_keyval_T item));



//! TODO
s_dict_T*	CONCAT(Dict_Map,T_NAME)(s_dict_T* dict, s_keyval_T (*map)(s_keyval_T item));

//! TODO
s_dict_T*	CONCAT(Dict_Map_I,T_NAME)(s_dict_T* dict, s_keyval_T (*map)(s_keyval_T item));



//! TODO
s_dict_T*	CONCAT(Dict_Filter,T_NAME)(s_dict_T* dict, t_bool (*filter)(s_keyval_T item));

//! TODO
s_dict_T*	CONCAT(Dict_Filter_I,T_NAME)(s_dict_T* dict, t_bool (*filter)(s_keyval_T item));



//! TODO Dict_Reduce ?



/*! @} */
HEADER_END
#endif
