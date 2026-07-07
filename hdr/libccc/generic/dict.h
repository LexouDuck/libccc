/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/dict.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_DICT_H
#define __LIBCCC_GENERIC_DICT_H
/*!@group{libccc_generic_dict,33,libccc/generic/dict.h}
**
**	This header defines a generic dictionary type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/char.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/generic/dict.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! The (compile-time configurable) 128-bit seed used by the dictionary key hashing function
/*!
**	These two 64-bit halves make up the 128-bit seed key used by the SipHash-1-3
**	hashing function (see `Dict_HashKey()`). The default value is the "canonical"
**	SipHash reference key (ie: the bytes `000102030405060708090A0B0C0D0E0F`, read
**	as two little-endian 64-bit integers), which makes hashes easily verifiable
**	against the reference implementation (https://github.com/veorq/SipHash).
**	NOTE: for hash-flooding-DoS-sensitive applications, you should redefine these
**	macros with values which are randomized (in some manner) for each build/run.
*/
//!@{
#ifndef LIBCONFIG_DICT_HASHSEED_0
#define LIBCONFIG_DICT_HASHSEED_0	(0x0706050403020100ULL)
#endif
#ifndef LIBCONFIG_DICT_HASHSEED_1
#define LIBCONFIG_DICT_HASHSEED_1	(0x0F0E0D0C0B0A0908ULL)
#endif
//!@}

//! A simple key+value pair struct, used in the 's_dict' dictionary struct
/*!
**	This struct associates a `value` of type `T` with a string `key`.
**	The `key` string is owned by the key/value pair: it is duplicated when the
**	pair is created (see `KeyVal()`), and freed when the pair is deleted.
**	The `hash` field caches the hash of the `key` string (see `Dict_HashKey()`),
**	so that dictionary lookup operations can compare hashes (a single integer
**	comparison) instead of comparing whole strings, for faster key lookups.
*/
struct keyval(T)
{
	t_u64		hash;	//!< The hash of the `key` string (see `Dict_HashKey()`)
	t_char*		key;	//!< The key string associated with the `value` (owned/freed by the dict)
	T			value;	//!< The value data associated with the `key`
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct keyval(T)	s_keyval(T);
#endif

//! A simple dictionary struct, stores an array of key/value pairs.
/*!
**	This struct holds a "dictionary" (ie: an associative container, which maps
**	unique string keys to values of type `T`), stored as a dense array of
**	key/value pairs (in insertion order). Keys within a dictionary are unique:
**	the editing functions ensure that no two pairs can share an equal `key`.
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

//!@doc Computes the hash of the given `key` string (SipHash-1-3, seeded with `LIBCONFIG_DICT_HASHSEED_*`)
/*!
**	@param	key		The key string to hash (if `NULL`, is treated like an empty string)
**	@returns
**	The 64-bit SipHash-1-3 hash of the given `key` string.
*/
//!@{
_GENERIC()
t_u64					Dict_HashKey(T)(t_char const* key);
#define c_dicthash(T)		Dict_HashKey(T)
//!@}

//!@doc Creates a new key/value pair, with a copy of the given `key` string, and the given `value`
/*!
**	@param	key		The key string for this pair (it is duplicated: the pair owns its own copy)
**	@param	value	The value to associate with the given `key`
**	@returns
**	A new key/value pair (returned by value), whose `.hash` field is filled.
**	If an error occurred (allocation failure, or `key` is `NULL`),
**	the returned pair will have its `.key` field set to `NULL`.
*/
//!@{
_GENERIC()
s_keyval(T)				KeyVal(T)(t_char const* key, T value);
#define c_keyval(T)			KeyVal(T)
//!@}

//!@doc Deletes the given key/value pair `keyval` (frees its `.key` string, and zeroes the struct fields)
/*!
**	NOTE: the `.value` field is not deleted by this function (values are caller-managed).
*/
//!@{
_GENERIC()
void					KeyVal_Free(T)(s_keyval(T)* keyval);
#define c_keyvalfree(T)		KeyVal_Free(T)
//!@}



/*============================================================================*\
||                             Basic Dict Operations                          ||
\*============================================================================*/

//!@doc Creates a new (empty) dictionary
/*!
**	@returns
**	A new empty dictionary (`length` is `0` and `items` is `NULL`),
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_New(T)(void);
#define c_dictnew(T)		Dict_New(T)
//!@}

//!@doc Creates a new dictionary from the given `n` amount of (key, value) pairs of variadic arguments
/*!
**	@param	n		The amount of key/value pairs given as variadic arguments
**	@param	...		The pairs to store, given as alternating arguments: `key1, value1, key2, value2, ...`
**					(each `key` is a `t_char*` string, and each `value` is of type `T`)
**	@returns
**	A new dictionary, containing the given key/value pairs.
**	If the same key is given several times, only the last value given for it is kept.
**	Returns `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_Create(T)(t_uint n, ...);
#define c_dictcreate(T)		Dict_Create(T)
//!@}

//!@doc Duplicates the given `dict` (allocates a new dictionary, with copies of every key string)
/*!
**	NOTE: the `value` fields are copied shallowly (values are caller-managed).
*/
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_Duplicate(T)(s_dict(T) const* dict);
#define c_dictdup(T)		Dict_Duplicate(T)
//!@}



//!@doc Deletes the given `dict` (frees every key string, the items array, and the struct itself)
//!@{
_GENERIC()
void					Dict_Free(T)(s_dict(T)* dict);
#define c_dictfree(T)		Dict_Free(T)
//!@}

//!@doc Like `Dict_Free()`, but also calls the given `del` function on each value stored
//!@{
_GENERIC()
void					Dict_Free_F(T)(s_dict(T)* dict, void (*del)(T value));
#define c_dictffree(T)		Dict_Free_F(T)
//!@}

//!@doc Deletes the dictionary pointed to by the given address `a_dict` (and sets `*a_dict` to `NULL`)
//!@{
_GENERIC()
void					Dict_Delete(T)(s_dict(T)* *a_dict);
#define c_dictdel(T)		Dict_Delete(T)
//!@}

//!@doc Like `Dict_Delete()`, but also calls the given `del` function on each value stored
//!@{
_GENERIC()
void					Dict_Delete_F(T)(s_dict(T)* *a_dict, void (*del)(T value));
#define c_dictfdel(T)		Dict_Delete_F(T)
//!@}



//!@doc Gets a pointer to the value associated with the given `key` in the given `dict`
/*!
**	@param	dict	The dictionary to look into
**	@param	key		The key string to look for
**	@returns
**	A pointer to the value associated with the given `key`,
**	or `NULL` if the given `key` is not present in the given `dict`.
**	NOTE: the returned pointer refers to storage held within the given `dict`:
**	it is only valid until the next editing operation on this dictionary.
*/
//!@{
_GENERIC()
T*						Dict_Get(T)(s_dict(T) const* dict, t_char const* key);
#define c_dictget(T)		Dict_Get(T)
//!@}

//!@doc Sets the value associated with the given `key` in the given `dict` (adding a new pair if needed)
/*!
**	If the given `key` is already present in the given `dict`, its associated
**	value is overwritten with the given `value`. Otherwise, a new key/value
**	pair is added at the end of the dictionary.
**
**	@returns
**	A pointer to the added/updated key/value pair,
**	or `NULL` if an error occurred.
**	NOTE: the returned pointer refers to storage held within the given `dict`:
**	it is only valid until the next editing operation on this dictionary.
*/
//!@{
_GENERIC()
s_keyval(T)*			Dict_Set(T)(s_dict(T)* dict, t_char const* key, T value);
#define c_dictset(T)		Dict_Set(T)
//!@}

//!@doc Adds a new key/value pair to the given `dict` (errors out if the given `key` is already present)
/*!
**	@returns
**	A pointer to the newly added key/value pair,
**	or `NULL` if an error occurred (in particular, if the given `key` is already present).
**	NOTE: the returned pointer refers to storage held within the given `dict`:
**	it is only valid until the next editing operation on this dictionary.
*/
//!@{
_GENERIC()
s_keyval(T)*			Dict_Add(T)(s_dict(T)* dict, t_char const* key, T value);
#define c_dictadd(T)		Dict_Add(T)
//!@}



/*============================================================================*\
||                            Dict Editing Operations                         ||
\*============================================================================*/

//!@doc Removes the key/value pair with the given `key` from the given `dict` (if present)
//!@{
_GENERIC()
void					Dict_Remove(T)(s_dict(T)* dict, t_char const* key);
#define c_dictremove(T)		Dict_Remove(T)
//!@}

//!@doc Like `Dict_Remove()`, but also calls the given `del` function on the removed value
//!@{
_GENERIC()
void					Dict_Remove_F(T)(s_dict(T)* dict, t_char const* key, void (*del)(T value));
#define c_dictfremove(T)	Dict_Remove_F(T)
//!@}

//!@doc Removes the first key/value pair whose value is equal to the given `value` (if any)
//!@{
_GENERIC()
void					Dict_RemoveMatch(T)(s_dict(T)* dict, T value);
#define c_dictremmatch(T)	Dict_RemoveMatch(T)
//!@}

//!@doc Like `Dict_RemoveMatch()`, but also calls the given `del` function on the removed value
//!@{
_GENERIC()
void					Dict_RemoveMatch_F(T)(s_dict(T)* dict, T value, void (*del)(T value));
#define c_dictfremmatch(T)	Dict_RemoveMatch_F(T)
//!@}

//!@doc Removes every key/value pair whose value is equal to the given `value` (if any)
//!@{
_GENERIC()
void					Dict_RemoveMatches(T)(s_dict(T)* dict, T value);
#define c_dictremmatches(T)	Dict_RemoveMatches(T)
//!@}

//!@doc Like `Dict_RemoveMatches()`, but also calls the given `del` function on each removed value
//!@{
_GENERIC()
void					Dict_RemoveMatches_F(T)(s_dict(T)* dict, T value, void (*del)(T value));
#define c_dictfremmatches(T)	Dict_RemoveMatches_F(T)
//!@}



//!@doc Creates a new dictionary, with only the pairs of `dict` whose keys are in the given `keys` list
/*!
**	@param	dict	The dictionary to take key/value pairs from
**	@param	keys	A `NULL`-terminated list of key strings to keep (keys which
**					are not present in the given `dict` are simply ignored)
**	@returns
**	A new dictionary, containing copies of the matched key/value pairs,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_Sub(T)(s_dict(T) const* dict, t_char const* const* keys);
#define c_dictsub(T)		Dict_Sub(T)
//!@}



/*============================================================================*\
||                            Dict Checking Operations                        ||
\*============================================================================*/

//!@doc Gets the key/value pair with the given `key` in the given `dict` (or `NULL` if not present)
/*!
**	NOTE: the returned pointer refers to storage held within the given `dict`:
**	it is only valid until the next editing operation on this dictionary.
*/
//!@{
_GENERIC()
s_keyval(T)*			Dict_Find(T)(s_dict(T) const* dict, t_char const* key);
#define c_dictfind(T)		Dict_Find(T)
//!@}

//!@doc Gets the first key/value pair of `dict` which matches the given `match` function (or `NULL`)
//!@{
_GENERIC()
s_keyval(T)*			Dict_Find_F(T)(s_dict(T) const* dict, t_bool (*match)(s_keyval(T) keyval));
#define c_dictffind(T)		Dict_Find_F(T)
//!@}

//!@doc Checks whether the given `key` is present in the given `dict`
//!@{
_GENERIC()
t_bool					Dict_HasKey(T)(s_dict(T) const* dict, t_char const* key);
#define c_dicthaskey(T)		Dict_HasKey(T)
//!@}

//!@doc Gets the key associated with the first value of `dict` which is equal to the given `value`
/*!
**	@returns
**	The key string of the first pair whose value is equal to the given `value`,
**	or `NULL` if no pair matches. NOTE: the returned string is owned by the `dict`.
*/
//!@{
_GENERIC()
t_char const*			Dict_KeyOf(T)(s_dict(T) const* dict, T value);
#define c_dictkeyof(T)		Dict_KeyOf(T)
//!@}



//!@doc Returns the amount of key/value pairs of `dict` whose value is equal to the given `value`
//!@{
_GENERIC()
t_uint					Dict_Count(T)(s_dict(T) const* dict, T value);
#define c_dictcount(T)		Dict_Count(T)
//!@}

//!@doc Checks whether any key/value pair of `dict` has a value equal to the given `value`
//!@{
_GENERIC()
t_bool					Dict_Contains(T)(s_dict(T) const* dict, T value);
#define c_dictcontains(T)	Dict_Contains(T)
//!@}

//!@doc Checks whether any key of the given `dict` is present in the given `target` dictionary
//!@{
_GENERIC()
t_bool					Dict_Has(T)(s_dict(T) const* dict, s_dict(T) const* target);
#define c_dicthas(T)		Dict_Has(T)
//!@}

//!@doc Checks whether every key of the given `dict` is present in the given `target` dictionary
//!@{
_GENERIC()
t_bool					Dict_HasOnly(T)(s_dict(T) const* dict, s_dict(T) const* target);
#define c_dicthasonly(T)	Dict_HasOnly(T)
//!@}



//!@doc Checks whether the two given dictionaries are equal (same keys, and equal values for each key)
/*!
**	NOTE: this check is order-independent: two dictionaries which hold the same
**	key/value pairs are considered equal, regardless of their insertion order.
*/
//!@{
_GENERIC()
t_bool					Dict_Equals(T)(s_dict(T) const* dict1, s_dict(T) const* dict2);
#define c_dictequ(T)		Dict_Equals(T)
//!@}



/*============================================================================*\
||                           Dict Functional Operations                       ||
\*============================================================================*/

//!@doc Iterates upon each key/value pair of the given `dict`, calling the given function `f` for each
//!@{
_GENERIC()
void					Dict_Iterate(T)(s_dict(T)* dict, void (*f)(s_keyval(T) keyval));
#define c_dictiter(T)		Dict_Iterate(T)
//!@}

//!@doc Like `Dict_Iterate()`, but the given function `f` also receives the current index
//!@{
_GENERIC()
void					Dict_Iterate_I(T)(s_dict(T)* dict, void (*f)(s_keyval(T) keyval, t_uint index));
#define c_dictiiter(T)		Dict_Iterate_I(T)
//!@}



//!@doc Creates a new dictionary, with the same keys as `dict`, and values mapped by the given `map` function
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_Map(T)(s_dict(T) const* dict, T (*map)(t_char const* key, T value));
#define c_dictmap(T)		Dict_Map(T)
//!@}

//!@doc Creates a new dictionary, with only the pairs of `dict` which match the given `filter` function
//!@{
_MALLOC()
_GENERIC()
s_dict(T)*				Dict_Filter(T)(s_dict(T) const* dict, t_bool (*filter)(s_keyval(T) keyval));
#define c_dictfilter(T)		Dict_Filter(T)
//!@}



//!@doc Runs the given function `f` on each key/value pair of `dict`, accumulating into a single result
/*!
**	The accumulator starts as `NULL` (use `Dict_Fold()` to give an `initial` value).
*/
//!@{
_GENERIC()
void*					Dict_Reduce(T)(s_dict(T) const* dict, void* (*f)(s_keyval(T) keyval, void* acc));
#define c_dictreduce(T)		Dict_Reduce(T)
//!@}

//!@doc Like `Dict_Reduce()`, but the accumulator starts with the given `initial` value
//!@{
_GENERIC()
void*					Dict_Fold(T)(s_dict(T) const* dict, void* (*f)(s_keyval(T) keyval, void* acc), void* initial);
#define c_dictfold(T)		Dict_Fold(T)
//!@}



/*! @endgroup */
HEADER_END
#endif
