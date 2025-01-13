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
/*!@group{libccc_monad_dict,33,libccc/monad/dict.h}
**
**	This header defines a generic dictionary type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/dict.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A simple key+value pair struct, used in the 's_dict' dictionary struct
/*
**	TODO document this
*/
struct keyval(T)
{
	t_char*		key;	//!< The key string associated with the `value`
	T			value;	//!< The pointer to the data for the `value`
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct keyval(T)	s_keyval(T);
#endif

//! A simple dictionary struct, stores an array of key/value pairs.
/*
**	TODO document this
*/
struct dict(T)
{
	t_uint			length;	//!< The amount of key/value pairs stored in this dictionary
	s_keyval(T)*	items;	//!< The array of key/value pairs stored in this dictionary
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct dict(T)	s_dict(T);
#endif



#define foreach_s_dict_init(		_TYPE_, _VAR_, _DICT_)	t_uint _VAR_##_i = 0;
#define foreach_s_dict_exit(		_TYPE_, _VAR_, _DICT_)	if ((void*)(_DICT_) != NULL && (_DICT_)->items != NULL)
#define foreach_s_dict_loop_init(	_TYPE_, _VAR_, _DICT_)	_TYPE_ _VAR_ = (_DICT_)->items[_VAR_##_i]
#define foreach_s_dict_loop_exit(	_TYPE_, _VAR_, _DICT_)	(_VAR_##_i < (_DICT_)->length)
#define foreach_s_dict_loop_incr(	_TYPE_, _VAR_, _DICT_)	++_VAR_##_i
#define foreach_s_dict_loop_setv(	_TYPE_, _VAR_, _DICT_)	_VAR_ = (_VAR_##_i == (_DICT_)->length ? _VAR_ : (_DICT_)->items[_VAR_##_i])



/*============================================================================*\
||                            Basic KeyVal Operations                         ||
\*============================================================================*/

// TODO KeyVal
// TODO KeyVal_New
// TODO KeyVal_Delete
// TODO KeyVal_Duplicate

// TODO KeyVal_Get
// TODO KeyVal_Set

// TODO KeyVal_Equals
// TODO KeyVal_Compare



/*============================================================================*\
||                             Basic Dict Operations                          ||
\*============================================================================*/

//! TODO
//s_dict(T)*	Dict_New(T)(t_uint n, s_keyval(T) keyval);

//! TODO
//s_dict(T)*	Dict_Create(T)(t_uint n, ...);



//! TODO
//void		Dict_Delete(T)(s_dict(T)* dict);

//! TODO
//void		Dict_Delete_F(T)(s_dict(T)* dict, void (*delete)(s_keyval(T)* keyval));

//! TODO
//s_dict(T)	Dict_Duplicate(T)(s_dict(T)* dict);



//! TODO
//void	Dict_Get(T)(s_dict(T)* dict, t_char* key);

//! TODO
//void	Dict_Set(T)(s_dict(T)* dict, t_char* key, T value);

//! TODO
//void	Dict_Copy(T)(s_dict(T)* dest, s_dict(T) const* src, t_char** keys);

//! TODO
//void	Dict_Sub(T)(s_dict(T)* dict, t_char** keys);



/*============================================================================*\
||                            Dict Editing Operations                         ||
\*============================================================================*/

//! TODO
//s_keyval(T)*	Dict_Add(T)(s_dict(T)* dict, t_char* key, T value);



//! TODO
//void	Dict_Remove(T)(s_dict(T)* dict, t_char* key);

//! TODO
//void	Dict_Remove_F(T)(s_dict(T)* dict, t_char* key, void (*delete)(s_keyval(T)* keyval));

//! TODO
//void	Dict_RemoveAll(T)(s_dict(T)* dict, t_char* key);

//! TODO
//void	Dict_RemoveAll_F(T)(s_dict(T)* dict, t_char* key, void (*delete)(s_keyval(T)* keyval));

//! TODO
//void	Dict_RemoveMatch(T)(s_dict(T)* dict, T value);

//! TODO
//void	Dict_RemoveMatch_F(T)(s_dict(T)* dict, T value, void (*delete)(s_keyval(T)* keyval));

//! TODO
//void	Dict_RemoveMatches(T)(s_dict(T)* dict, T value);

//! TODO
//void	Dict_RemoveMatches_F(T)(s_dict(T)* dict, T value, void (*delete)(s_keyval(T)* keyval));



//! TODO
//void	Dict_Replace(T)(s_dict(T)* dict, t_char* key, s_keyval(T) new);



/*============================================================================*\
||                            Dict Checking Operations                        ||
\*============================================================================*/

//! TODO
//t_char*		Dict_KeyOf(T)(s_dict(T)* dict, T value);



//! TODO
//s_keyval(T)*	Dict_Find(T)(s_dict(T)* dict, s_keyval(T) value);

//! TODO
//s_keyval(T)*	Dict_Find_F(T)(s_dict(T)* dict, t_bool (*match)(s_keyval(T) value));



//! TODO
//t_uint		Dict_Count(T)(s_dict(T)* dict, s_keyval(T) value);

//! TODO
//t_bool		Dict_Contains(T)(s_dict(T)* dict, s_keyval(T) value);

//! TODO
//t_bool		Dict_Has(T)(s_dict(T)* dict, s_dict(T)* target);

//! TODO
//t_bool		Dict_HasOnly(T)(s_dict(T)* dict, s_dict(T)* target);



//! TODO
//t_bool	Dict_Equals(T)(s_dict(T)* dict1, s_dict(T)* dict2);

//! TODO
//t_bool	Dict_Equals_K(T)(s_dict(T)* dict1, s_dict(T)* dict2, t_char** keys);

//! TODO
//t_sint	Dict_Compare(T)(s_dict(T)* dict1, s_dict(T)* dict2, t_sint (*compare)(s_keyval(T) item1, s_keyval(T) item2));

//! TODO
//t_sint	Dict_Compare_K(T)(s_dict(T)* dict1, s_dict(T)* dict2, t_char** keys, t_sint (*compare)(s_keyval(T) item1, s_keyval(T) item2));



/*============================================================================*\
||                           Dict Functional Operations                       ||
\*============================================================================*/

//! TODO
//void		Dict_Iterate(T)(s_dict(T)* dict, void (*f)(s_keyval(T) item));

//! TODO
//void		Dict_Iterate_I(T)(s_dict(T)* dict, void (*f)(s_keyval(T) item));



//! TODO
//s_dict(T)*	Dict_Map(T)(s_dict(T)* dict, s_keyval(T) (*map)(s_keyval(T) item));

//! TODO
//s_dict(T)*	Dict_Map_I(T)(s_dict(T)* dict, s_keyval(T) (*map)(s_keyval(T) item));



//! TODO
//s_dict(T)*	Dict_Filter(T)(s_dict(T)* dict, t_bool (*filter)(s_keyval(T) item));

//! TODO
//s_dict(T)*	Dict_Filter_I(T)(s_dict(T)* dict, t_bool (*filter)(s_keyval(T) item));



//! TODO
//s_dict(T)*	Dict_Reduce(T)(s_dict(T)* dict, void* (*f)(s_keyval(T) item, void* acc));

//! TODO
//s_dict(T)*	Dict_Reduce_I(T)(s_dict(T)* dict, void* (*f)(s_keyval(T) item, void* acc));

//! TODO
//s_dict(T)*	Dict_Fold(T)(s_dict(T)* dict, void* (*f)(s_keyval(T) item, void* acc), void* initial);

//! TODO
//s_dict(T)*	Dict_Fold_I(T)(s_dict(T)* dict, void* (*f)(s_keyval(T) item, void* acc), void* initial);



/*! @endgroup */
HEADER_END
#endif
