/*============================================================================*\
||                                            ______________________________  ||
||  libccc/stringarray.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRINGARRAY_H
#define __LIBCCC_STRINGARRAY_H
/*!@group{libccc_stringarray,19,libccc/stringarray.h}
**
**	This header defines some useful functions for string array (t_char**) handling.
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

//! Type definition for an array of strings
/*!
**	This typedef is only provided for certain niche purposes, since it is typically
**	not very good practice in C to hide pointers within `typedef` types.
*/
typedef t_char**	p_strarray;



/*
** ************************************************************************** *|
**                       StringArray: string splitting                        *|
** ************************************************************************** *|
*/

//!@doc Splits a string into several new sub-strings, with `sep` as the delimiter char
/*!
**	@param	str		The string into split into several parts
**	@param	sep		The separator character used to determine where to split
**	@returns
**	A string array made up of substrings of `str`, where each element
**	is a section delimited by `c` separators, or the edges of the string.
*/
//!@{
_MALLOC()
t_char**					String_Split_Char(t_char const* str, t_char sep);
#define c_strsplit_char		String_Split_Char
//!@}

//!@doc Splits a string into several new sub-strings, with `sep` as the delimiter char
/*!
**	@param	str		The string into split into several parts
**	@param	sep		A charset string, listing all characters to be considered as separators
**	@returns
**	A string array made up of substrings of `str`, where each element
**	is a section delimited by any of the `char_sep` separators, or the edges
**	of the string.
*/
//!@{
_MALLOC()
t_char**					String_Split_Charset(t_char const* str, t_char const* sep_chars);
#define c_strsplit_cset		String_Split_Charset
//!@}

//!@doc Splits up the given string `str` into several parts in a string array, using `query` as separator
/*!
**	@param	str		The string into split into several parts
**	@param	sep		The separator string used to determine where to split
**	@returns
**	A string array made up of substrings of `str`, where each element
**	is a section delimited by the full string `query`, or the edges of the string.
**	NB: if a dual query overlaps in str, the query is only counted for distinct
**		parts, ie "||" for "|||aa" will return ["", "|aa"] and not
**		["", "", "aa"]. Note that this is the same behavior as many Ctrl+F:
**		to get the second result, simply keep the second part of the pattern
**		and call replace twice, without the pattern the second time.
**		Ex: "enenen" --s/enen/HIen/-> "HIenen" --s/enen/HI/--> "HIHI"
*/
//!@{
_MALLOC()
t_char**					String_Split_String(t_char const* str, t_char const* sep);
#define c_strsplit_str		String_Split_String
//!@}



//!@doc Splits up the given string `str` into a set of substrings which are all `n` characters long
/*!
**	@param	str		The string into split into several parts
**	@param	n		The amount of characters contained in each substring
**	@returns
**	A string array which is the result of dividing str into chunks of
**	equal size `n`, safe for the last chunk of `length <= n`.
*/
//!@{
_MALLOC()
t_char**				String_Divide(t_char const* str, t_size n);
#define c_strdivide		String_Divide
//!@}



/*
** ************************************************************************** *|
**                       StringArray: creation operations                     *|
** ************************************************************************** *|
*/

//!@doc Gets the amount of strings contained in the given string array `strarr`
/*!
**	@param	strarr	The string array whose length shall be counted
**	@returns
**	The amount of strings in the given string array `strarr` (before the first NULL pointer).
*/
//!@{
t_uint					StringArray_Length(t_char const** strarr);
#define c_strarrlen		StringArray_Length
//!@}

//!@doc Gets the combined length of some or all strings in the given string array `strarr`
/*!
**	@param	strarr	The string array whose strings' total length shall be counted
**	@param	n		The amount of string lengths to sum (if `0`, all string lengths are summed)
**	@returns
**	The combined length of the `n` first strings of the given string array `strarr`.
**	If `n == 0`, returns the combined length of all strings in `strarr`.
**	This total does not include the `\0` null-terminator characters at the end of each string.
*/
//!@{
t_size					StringArray_TotalLength(t_char const** strarr, t_uint n);
#define c_strarrlens	StringArray_TotalLength
//!@}



/*
** ************************************************************************** *|
**                       StringArray: creation operations                     *|
** ************************************************************************** *|
*/

//!@doc Allocates a new string array with `n` elements, all set to NULL
/*!
**	@param	n		The amount of strings that can be stored in this string array
**	@returns
**	A null-terminated list of unset `t_char*`, of length `length`.
*/
//!@{
_MALLOC()
t_char**				StringArray_New(t_uint n);
#define c_strarrnew		StringArray_New
//!@}

//!@doc Allocates a new string array with `n` strings, each filled with `length` characters of value `c`
/*!
**	@param	n		The amount of strings that are stored in this string array
**	@param	length	The amount of characters in each allocated string of the string array
**	@param	c		The character used to fill up each allocated string
**	@returns
**	A newly allocated string array, which has `n` strings and `length` characters
**	per string (excluding null-terminators), every character set to the value `c`.
*/
//!@{
_MALLOC()
t_char**				StringArray_New_C(t_uint n, t_size length, t_char c);
#define c_strarrcnew	StringArray_New_C
//!@}

//!@doc Allocates a new string array which consists of `n` strings, initialized from variadic arguments.
/*!
**	@param	n		The amount of strings in this string array (amount of variadic args)
**	@param	...		The variadic list of arguments: there must be `n` arguments, all of type string
**	@returns
**	A newly allocated string array containing `n` elements (the given `...` varargs)
*/
//!@{
t_char**				StringArray_Create(t_uint n, ...);
#define c_strarrcreate	StringArray_Create
//!@}

//!@doc Duplicates the contents of a string array, and returns the newly allocated copy.
/*!
**	@param	strarr		The string array to copy
**	@returns
**	A newly allocated string array with contents identical to the given `strarr`
*/
//!@{
_MALLOC()
t_char**				StringArray_Duplicate(t_char const** strarr);
#define c_strarrdup		StringArray_Duplicate
//!@}



//!@doc Creates a new string array from a subsection of the given string array `strarr`
/*!
**	@param	strarr		The string array to copy
**	@param	start		The index of the start of the subsection to extract
**	@param	length		The length of the subsection to extract (the amount of strings in the result)
**	@returns
**	A newly allocated string array, which is a copy of a subsection of `strarr`.
**	The first string of the result is the string at index `start`  from `strarr`.
**	The last string of the result is the string at index `start + length - 1` in `strarr`.
*/
//!@{
_MALLOC()
t_char**				StringArray_Sub(t_char const** strarr, t_uint start, t_uint length);
#define c_strarrsub		StringArray_Sub
//!@}



//!@doc Copies over `n` strings from the given `src` string array into the given `dest` string array
/*!
**	@param	dest	The destination string array to copy to
**	@param	dest_i	The index in the destination string array at which to copy `n` strings
**	@param	src		The source string array which should be copied
**	@param	src_i	The index in the source string array from which to copy `n` strings
**	@param	n		The amount of string array strings to copy from `src` to `dest` - if `0`, all strings until the end if `src` are copied
**	@returns
**	The given `dest` pointer, or `NULL` if an error occurred. The `dest` string array is modified in-place.
*/
//!@{
t_char**				StringArray_Copy(t_char** dest, t_uint dest_i, t_char const** src, t_uint src_i, t_uint length);
#define c_strarrcpy		StringArray_Copy
//!@}



/*
** ************************************************************************** *|
**                       StringArray: deletion operations                     *|
** ************************************************************************** *|
*/

//!@doc Frees all allocated strings in a string array, and the string array itself.
/*!
**	@param	strarr		The address of the string array to deallocate
*/
//!@{
void					StringArray_Free(t_char** strarr);
#define c_strarrfree	StringArray_Free
//!@}



//!@doc Frees all allocated strings in a string array, and the string array itself.
/*!
**	@param	a_strarr	The address of the string array to deallocate and set to NULL
*/
//!@{
void					StringArray_Delete(t_char** *a_strarr);
#define c_strarrdel		StringArray_Delete
//!@}



/*
** ************************************************************************** *|
**                       StringArray: editing operations                      *|
** ************************************************************************** *|
*/

//!@doc Appends the given string `string` to the end of the given string array `dest`.
/*!
**	If `dest` is NULL, it'll append `string` at index 0, creating a 1-string string array.
**
**	@param	dest	The destination string array to append an string to
**	@param	string	The string to copy and append to the given `dest`
**	@returns
**	The new pointer for the given `strarr`. The string array is modified in-place.
**	This return will be the same as the given `dest` argument, unless `dest == NULL`.
*/
//!@{
t_char**					StringArray_Add(t_char** dest, t_char const* str);
#define c_strarradd			StringArray_Add
//!@}

//!@doc Inserts the given `string` at the given `index` of the given string array `dest`
/*!
**	If `index` is greater than the length of the string array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination string array in which to insert a new string
**	@param	string	The string to copy and insert into the given `dest`
**	@param	index	The index at which to insert the new string array string
**	@returns
**	The new beginning pointer for the given `dest`. The string array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, and the `index` given is zero.
*/
//!@{
t_char**					StringArray_Insert(t_char** dest, t_char const* str, t_uint index);
#define c_strarrinsert		StringArray_Insert
//!@}



//!@doc Inserts all strings from `src` at the given `index` of the given string array `dest`
/*!
**	If `index` is greater than the length of the string array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination string array in which to insert new strings
**	@param	src		The source string array, whose strings will be copied and inserted into `dest`
**	@param	index	The index at which to insert the new string array strings
**	@returns
**	The new beginning pointer for the given string array `dest`. The string array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, or the `index` given is zero.
*/
//!@{
t_char**					StringArray_Wedge(t_char** dest, t_char const** src, t_uint index);
#define c_strarrwedge		StringArray_Wedge
//!@}



//!@doc Removes a single string from the given `strarr`, at the given `index`
/*!
**	@param	strarr	The string array in which to remove an string
**	@param	index	The index of the string to delete from the string array
**	@returns
**	The string array given as argument. The string array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `strarr`, unless the `index` given is zero.
*/
//!@{
void					StringArray_RemoveAt(t_char** strarr, t_uint index);
#define c_strarrdelat	StringArray_RemoveAt
//!@}
//!@doc Like Array_RemoveAt(), but you can supply a custom `delete` function
//!@{
void					StringArray_RemoveAt_F(t_char** strarr, t_uint index, void (*delete)(t_char*));
#define c_strarrfdelat	StringArray_RemoveAt_F
//!@}

//!@doc Removes the first string from the given `strarr` which is equal to the given `string`
/*!
**	@param	strarr	The string array in which to remove an string
**	@param	string	The string value which is to be removed from `strarr`
**	@returns
**	The `strarr` given as argument. The string array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `strarr`, unless the matched string is at position zero.
*/
//!@{
void					StringArray_Remove(t_char** strarr, t_char const* str);
#define c_strarrdelone	StringArray_Remove
//!@}
//!@doc Like Array_Remove(), but you can supply a custom `delete` function
//!@{
void					StringArray_Remove_F(t_char** strarr, t_char const* str, void (*delete)(t_char*));
#define c_strarrfdelone	StringArray_Remove_F
//!@}

//!@doc Removes any strings which are equal to the given `string` from the given `strarr`
/*!
**	@param	strarr	The string array in which to remove strings
**	@param	string	The string value for which any occurrences are to be removed from `strarr`
**	@returns
**	The string array given as argument. The string array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `strarr`, unless a matched string is at position zero.
*/
//!@{
void					StringArray_RemoveAll(t_char** strarr, t_char const* str);
#define c_strarrdelall	StringArray_RemoveAll
//!@}
//!@doc Like Array_RemoveAll(), but you can supply a custom `delete` function
//!@{
void					StringArray_RemoveAll_F(t_char** strarr, t_char const* str, void (*delete)(t_char*));
#define c_strarrfdelall	StringArray_RemoveAll_F
//!@}



//!@doc Creates a new string array from the given `strarr`, where any occurence of `old` is replaced with `new`
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	old		The string to be replaced
**	@param	new		The replacement for the resulting string array
**	@returns
**	A newly created string array copied from `strarr`, in which in any string equal to `old`
**	will instead have a value of `new`, or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_char**				StringArray_Replace(t_char const** strarr, t_char const* old, t_char const* new);
#define c_strarrrep		StringArray_Replace
//!@}

//!@doc Creates a new string array from the given `strarr`, where the first `n` occurences of `old` are replaced with `new`.
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	old		The string to be replaced
**	@param	new		The replacement for the resulting string array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created string array copied from `strarr`, in which in the first (iterating forwards)
**	`n` encountered strings which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_char**					StringArray_ReplaceFirst(t_char const** strarr, t_char const* old, t_char const* new, t_uint n);
#define c_strarrrepfirst	StringArray_ReplaceFirst
//!@}

//!@doc Creates a new string array from the given `strarr`, where the last `n` occurences of `old` are replaced with `new`.
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	old		The string to be replaced
**	@param	new		The replacement for the resulting string array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created string array copied from `strarr`, in which in the first (iterating backwards)
**	`n` encountered strings which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_char**					StringArray_ReplaceLast(t_char const** strarr, t_char const* old, t_char const* new, t_uint n);
#define c_strarrreplast		StringArray_ReplaceLast
//!@}



//!@doc Creates a new string array from the given `strarr`, with each string's position being inverted
/*!
**	@param	strarr	The string array to duplicate and invert
**	@returns
**	A newly created string array copied from `strarr`, in which all strings' positions have been
**	reversed. This means that the last string will become the first string, and so on.
*/
//!@{
_MALLOC()
t_char**				StringArray_Reverse(t_char const** strarr);
#define c_strarrrev		StringArray_Reverse
//!@}



//!@doc TODO redesign
/*!
**	@returns
**	A newly allocated string array such that every string is now
**	preceded by `n` times the character `c`.
*/
//!@{
_MALLOC()
t_char**				StringArray_Pad_L(t_char const** strarr, t_char c, t_uint n);
#define c_strarrpadl	StringArray_Pad_L
//!@}


/*
** ************************************************************************** *|
**                    StringArray: concatenation operations                   *|
** ************************************************************************** *|
*/

//!@doc Concatenates two string arrays together
/*!
**	@param	strarr1	The left-hand string array to concatenate
**	@param	strarr2 The right-hand string array to concatenate
**	@returns
**	A newly created string array which is the concatenation of `strarr1` and `strarr2`.
*/
//!@{
_MALLOC()
t_char**					StringArray_Concat(t_char const** strarr1, t_char const** strarr2);
#define c_strarrconcat		StringArray_Concat
//!@}

//!@doc Concatenates two string arrays together, and deletes the left-hand string array given
/*!
**	@param	strarr1	The left-hand string array to concatenate
**	@param	strarr2 The right-hand string array to concatenate
**	@returns
**	A newly created string array which is the concatenation of `dest` and `src`,
**	and deletes `dest`, replacing it with the resulting new string array.
*/
//!@{
_MALLOC()
t_char**					StringArray_Append(t_char** *a_dest, t_char const** src);
#define c_strarrappend		StringArray_Append
//!@}

//!@doc Concatenates two string arrays together, and deletes the right-hand string array given
/*!
**	@param	strarr1	The left-hand string array to concatenate
**	@param	strarr2 The right-hand string array to concatenate
**	@returns
**	A newly created string array which is the concatenation of `src` and `dest`,
**	and deletes `dest`, replacing it with the resulting new string array.
*/
//!@{
_MALLOC()
t_char**					StringArray_Prepend(t_char const** src, t_char** *a_dest);
#define c_strarrprepend		StringArray_Prepend
//!@}

//!@doc Concatenates two string arrays together, and deletes both string arrays given
/*!
**	@param	strarr1	The left-hand string array to concatenate
**	@param	strarr2 The right-hand string array to concatenate
**	@returns
**	A newly created string array which is the concatenation of `strarr1` and `strarr2`,
**	and deletes both input string arrays.
*/
//!@{
_MALLOC()
t_char**					StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2);
#define c_strarrmerge		StringArray_Merge
//!@}



//!@doc Concatenates a set of string arrays together, adding the given set of strings `sep` between each
/*!
**	@param	strarrs	The set of string arrays which should be joined together
**	@param	sep		The separator string array, to be added in between each string array of `strarrs`
**	@returns
**	A newly allocated string array, which is the fold/reduce concatenation
**	of all string arrays in `strarrs`, with the strings of `sep` added between each string array.
*/
//!@{
_MALLOC()
t_char**					StringArray_Join(t_char const*** strarrs, t_char const** sep);
#define c_strarrjoin		StringArray_Join
//!@}



/*
** ************************************************************************** *|
**                          Array: comparison operations                      *|
** ************************************************************************** *|
*/

//!@doc Checks if two string arrays have the same content (pointers may differ)
/*!
**	If both pointers given are identical, this function returns `TRUE` without value-checking.
**
**	@param	strarr1	The first string array to check for equality
**	@param	strarr2	The second string array to check for equality
**	@returns
**	`TRUE` if each string of both string arrays are equal, and the string arrays have the same amount of strings.
**	Otherwise, `FALSE` is returned.
*/
//!@{
t_bool					StringArray_Equals(t_char const** strarr1, t_char const** strarr2);
#define c_strarrequ		StringArray_Equals
//!@}

//!@doc Checks if two string arrays have the same content (pointers may differ), for the `n` first strings
/*!
**	If both pointers given are identical, this function returns `TRUE` without value-checking.
**
**	@param	strarr1	The first string array to check for equality
**	@param	strarr2	The second string array to check for equality
**	@param	n		The amount of strings to check for equality
**	@returns
**	`TRUE` if the first `n` strings of both string arrays are equal.
**	Otherwise, `FALSE` is returned.
*/
//!@{
t_bool					StringArray_Equals_N(t_char const** strarr1, t_char const** strarr2, t_uint n);
#define c_strarrnequ	StringArray_Equals_N
//!@}



//!@doc Compares two string arrays using the given `compare` function
/*!
**	@param	strarr1	The first string array to compare
**	@param	strarr2	The second string array to compare
**	@param	compare	The function used to determine whether strings are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					StringArray_Compare	(t_char const** strarr1, t_char const** strarr2, t_sint (*compare)(t_char const* str1, t_char const* str2));
#define c_strarrcmp		StringArray_Compare

//!@doc Compares two string arrays using the given `compare` function, for the `n` first strings
/*!
**	@param	strarr1	The first string array to compare
**	@param	strarr2	The second string array to compare
**	@param	compare	The function used to determine whether strings are considered "equal" or not
**	@param	n		The amount of strings to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					StringArray_Compare_N	(t_char const** strarr1, t_char const** strarr2, t_sint (*compare)(t_char const* str1, t_char const* str2), t_uint n);
#define c_strarrncmp	StringArray_Compare_N



/*
** ************************************************************************** *|
**                      StringArray: analysis operations                      *|
** ************************************************************************** *|
*/

//!	Counts the amount of occurences of the char `c` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint							StringArray_Count_Char(t_char const** strarr, t_char const c);
#define c_strarrcount_char		StringArray_Count_Char
//!@}

//!	Counts the amount of occurences of any of the chars in the given `charset` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint							StringArray_Count_Charset(t_char const** strarr, t_char const* cset);
#define c_strarrcount_cset		StringArray_Count_Charset
//!@}

//!	Counts the amount of occurences of the string `query` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint							StringArray_Count_String(t_char const** strarr, t_char const* query);
#define c_strarrcount_str		StringArray_Count_String
//!@}



// TODO StringArray_Has()
// TODO StringArray_HasOnly()



/*
** ************************************************************************** *|
**                      StringArray: functional operations                    *|
** ************************************************************************** *|
*/

//!@doc Executes the given function `f` for each string contained in the given string array `strarr`.
/*!
**	NOTE: the return value of this `f` function will be assigned to the string in `strarr`
**	This means that if you wish for your `f` function to return a newly allocated string,
**	to replace the old one, you should remember to delete the old string.
**
**	@param	strarr	The string array to iterate upon.
**	@param	f		The function to execute for each string in the string array.
**					The returned value will replace the corresponding string in the string array.
*/
//!@{
void					StringArray_Iterate(t_char** strarr, t_char* (*f)(t_char* str));
#define c_strarriter	StringArray_Iterate
//!@}
//!@doc Like StringArray_Iterate(), but the user-supplied function receives the current index
//!@{
void					StringArray_Iterate_I(t_char** strarr, t_char* (*f)(t_char* str, t_uint index));
#define c_strarriiter	StringArray_Iterate_I
//!@}



//!@doc Creates a new string array from the given `strarr`, creating each string by calling the given `map` function.
/*!
**	@param	strarr	The string array to iterate upon
**	@param	map		The function to execute for each string in the string array.
**					This function should return a newly allocated string.
**	@returns
**	A newly allocated string array, the result of mapping each string of `strarr`
**	to a corresponding result by calling `map()`, or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_char**				StringArray_Map(t_char const** strarr, t_char* (*map)(t_char const* str));
#define c_strarrmap		StringArray_Map
//!@}
//!@doc Like StringArray_Map(), but the user-supplied function receives the current index
//!@{
t_char**				StringArray_Map_I(t_char const** strarr, t_char* (*map)(t_char const* str, t_uint index));
#define c_strarrimap	StringArray_Map_I
//!@}



//!@doc Creates a new string array which is a subset of `strarr`, with only the strings where the `filter` function returned `TRUE`
/*!
**	@param	strarr	The string array whose strings should be iterated upon
**	@param	filter	The function to call to check if an string of `strarr` should be added to the result
**	@returns
**	A new string array, created by storing the return values of each call to the given `map` function.
*/
//!@{
t_char**				StringArray_Filter(t_char const** strarr, t_bool (*filter)(t_char const* str));
#define c_strarrfilter	StringArray_Filter
//!@}
//!@doc Like StringArray_Filter(), but the user-supplied function receives the current index
//!@{
t_char**				StringArray_Filter_I(t_char const** strarr, t_bool (*filter)(t_char const* str, t_uint index));
#define c_strarrifilter	StringArray_Filter_I
//!@}



//!@doc Creates a single value by executing the given function `f` for each string of the given string array `strarr`.
/*!
**	The difference between StringArray_Reduce() and StringArray_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	strarr	The string array to iterate upon.
**	@param	reduce	The user-specified function to execute for each string of the given string array `strarr`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type.
**	@returns
**	A single value, of any type, which is created by calling `f()` for each string of the given `strarr`.
*/
//!@{
void*					StringArray_Reduce(t_char const** strarr, void* (*f)(t_char const* str, void* acc));
#define c_strarrreduce	StringArray_Reduce
//!@}
//!@doc Like StringArray_Reduce(), but the user-supplied function receives the current index
//!@{
void*					StringArray_Reduce_I(t_char const** strarr, void* (*f)(t_char const* str, void* acc, t_uint index));
#define c_strarrireduce	StringArray_Reduce_I
//!@}

//!@doc Creates a single value by executing the given function `f` for each string of the given string array `strarr`.
/*!
**	The difference between StringArray_Fold() and StringArray_Reduce() is that with this function,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	strarr	The string array to iterate upon.
**	@param	reduce	The user-specified function to execute for each string of the given string array `strarr`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type.
**	@returns
**	A single value, of any type, which is created by calling `f()` for each string of the given `strarr`.
*/
//!@{
void*					StringArray_Fold(t_char const** strarr, void* (*f)(t_char const* str, void* acc), void* initial);
#define c_strarrfold	StringArray_Fold
//!@}
//!@doc Like StringArray_Reduce(), but the user-supplied function receives the current index
//!@{
void*					StringArray_Fold_I(t_char const** strarr, void* (*f)(t_char const* str, void* acc, t_uint index), void* initial);
#define c_strarrifold	StringArray_Fold_I
//!@}



/*! @endgroup */
HEADER_END
#endif
