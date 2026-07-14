/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/stringarray/utf8.h          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_STRINGARRAY_UTF8_H
#define __LIBCCC_STRINGARRAY_UTF8_H
/*!@group{libccc_stringarray_utf8,19,libccc/text/stringarray/utf8.h}
**
**	This header defines some useful functions for handling arrays of UTF8 strings.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! Type definition for an array of strings (UTF8 format)
/*!
**	This typedef is only provided for certain niche purposes (such as use with generics),
**	since it is typically not very good practice in C to hide pointers within `typedef` types.
*/
//!@{
typedef t_utf8**	p_mbsarr;
typedef t_utf8**	p_mbstrarr;
typedef t_utf8**	p_mbstringarray;
typedef t_utf8**	p_strarrutf8;
typedef t_utf8**	p_strarrayutf8;
typedef t_utf8**	p_stringarrayutf8;
//!@}



typedef t_utf8*		(*f_stringarray_utf8_iterate)		(t_utf8* str);
typedef t_utf8*		(*f_stringarray_utf8_iterate_i)		(t_utf8* str, t_uint i);
typedef t_utf8*		(*f_stringarray_utf8_map)			(t_utf8 const* str);
typedef t_utf8*		(*f_stringarray_utf8_map_i)			(t_utf8 const* str, t_uint i);
typedef t_bool		(*f_stringarray_utf8_filter)		(t_utf8 const* str);
typedef t_bool		(*f_stringarray_utf8_filter_i)		(t_utf8 const* str, t_uint i);
typedef void*		(*f_stringarray_utf8_reduce)		(t_utf8 const* str, void* acc);
typedef void*		(*f_stringarray_utf8_reduce_i)		(t_utf8 const* str, void* acc, t_uint i);



/*============================================================================*\
||                       StringArray: string splitting                        ||
\*============================================================================*/

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
t_utf8**				StringUTF8_Split_Char(t_utf8 const* str, t_utf32 sep);
#define c_mbssplit_char	StringUTF8_Split_Char
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
t_utf8**				StringUTF8_Split_Charset(t_utf8 const* str, t_utf8 const* sep_chars);
#define c_mbssplit_cset	StringUTF8_Split_Charset
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
t_utf8**				StringUTF8_Split_String(t_utf8 const* str, t_utf8 const* sep);
#define c_mbssplit_str	StringUTF8_Split_String
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
t_utf8**				StringUTF8_Divide(t_utf8 const* str, t_size n);
#define c_mbsdivide		StringUTF8_Divide
//!@}



/*============================================================================*\
||                       StringArray: creation operations                     ||
\*============================================================================*/

//!@doc Gets the amount of strings contained in the given string array `strarr`
/*!
**	@param	strarr	The string array whose length shall be counted
**	@returns
**	The amount of strings in the given string array `strarr` (before the first NULL pointer).
*/
//!@{
t_uint					StringArrayUTF8_Length(t_utf8 const* const* strarr);
#define c_mbsarrlen		StringArrayUTF8_Length
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
t_size					StringArrayUTF8_TotalLength(t_utf8 const* const* strarr, t_uint n);
#define c_mbsarrlens	StringArrayUTF8_TotalLength
//!@}



/*============================================================================*\
||                       StringArray: creation operations                     ||
\*============================================================================*/

//!@doc Allocates a new string array with `n` elements, all set to NULL
/*!
**	@param	n		The amount of strings that can be stored in this string array
**	@returns
**	A null-terminated list of unset `t_utf8*`, of length `length`.
*/
//!@{
_MALLOC()
t_utf8**				StringArrayUTF8_New(t_uint n);
#define c_mbsarrnew		StringArrayUTF8_New
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
t_utf8**				StringArrayUTF8_New_C(t_uint n, t_size length, t_utf32 c);
#define c_mbsarrcnew	StringArrayUTF8_New_C
//!@}

//!@doc Allocates a new string array which consists of `n` strings, initialized from variadic arguments.
/*!
**	@param	n		The amount of strings in this string array (amount of variadic args)
**	@param	...		The variadic list of arguments: there must be `n` arguments, all of type string
**	@returns
**	A newly allocated string array containing `n` elements (the given `...` varargs)
*/
//!@{
t_utf8**				StringArrayUTF8_Create(t_uint n, ...);
#define c_mbsarrcreate	StringArrayUTF8_Create
//!@}

//!@doc Duplicates the contents of a string array, and returns the newly allocated copy.
/*!
**	@param	strarr		The string array to copy
**	@returns
**	A newly allocated string array with contents identical to the given `strarr`
*/
//!@{
_MALLOC()
t_utf8**				StringArrayUTF8_Duplicate(t_utf8 const* const* strarr);
#define c_mbsarrdup		StringArrayUTF8_Duplicate
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
t_utf8**				StringArrayUTF8_Sub(t_utf8 const* const* strarr, t_uint start, t_uint length);
#define c_mbsarrsub		StringArrayUTF8_Sub
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
t_utf8**				StringArrayUTF8_Copy(t_utf8** dest, t_uint dest_i, t_utf8 const* const* src, t_uint src_i, t_uint length);
#define c_mbsarrcpy		StringArrayUTF8_Copy
//!@}



/*============================================================================*\
||                       StringArray: deletion operations                     ||
\*============================================================================*/

//!@doc Frees all allocated strings in a string array, and the string array itself.
/*!
**	@param	strarr		The address of the string array to deallocate
*/
//!@{
void					StringArrayUTF8_Free(t_utf8** strarr);
#define c_mbsarrfree	StringArrayUTF8_Free
//!@}



//!@doc Frees all allocated strings in a string array, and the string array itself.
/*!
**	@param	a_strarr	The address of the string array to deallocate and set to NULL
*/
//!@{
void					StringArrayUTF8_Delete(t_utf8** *a_strarr);
#define c_mbsarrdel		StringArrayUTF8_Delete
//!@}



/*============================================================================*\
||                       StringArray: editing operations                      ||
\*============================================================================*/

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
t_utf8**				StringArrayUTF8_Add(t_utf8** dest, t_utf8 const* str);
#define c_mbsarradd		StringArrayUTF8_Add
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
t_utf8**				StringArrayUTF8_Insert(t_utf8** dest, t_utf8 const* str, t_uint index);
#define c_mbsarrinsert	StringArrayUTF8_Insert
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
t_utf8**				StringArrayUTF8_Wedge(t_utf8** dest, t_utf8 const** src, t_uint index);
#define c_mbsarrwedge	StringArrayUTF8_Wedge
//!@}



//!@doc Removes a single string from the given `strarr`, at the given `index`
/*!
**	@param	strarr	The string array in which to remove a string
**	@param	index	The index of the string to remove from the string array
**	@returns
**	The string array given as argument. The string array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `strarr`, unless the `index` given is zero.
*/
//!@{
void					StringArrayUTF8_RemoveAt(t_utf8** strarr, t_uint index);
#define c_mbsarrdelat	StringArrayUTF8_RemoveAt
//!@}
//!@doc Like Array_RemoveAt(), but you can supply a custom `del` function
//!@{
void					StringArrayUTF8_RemoveAt_F(t_utf8** strarr, t_uint index, void (*del)(t_utf8*));
#define c_mbsarrfdelat	StringArrayUTF8_RemoveAt_F
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
void					StringArrayUTF8_Remove(t_utf8** strarr, t_utf8 const* str);
#define c_mbsarrdelone	StringArrayUTF8_Remove
//!@}
//!@doc Like Array_Remove(), but you can supply a custom `del` function
//!@{
void					StringArrayUTF8_Remove_F(t_utf8** strarr, t_utf8 const* str, void (*del)(t_utf8*));
#define c_mbsarrfdelone	StringArrayUTF8_Remove_F
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
void					StringArrayUTF8_RemoveAll(t_utf8** strarr, t_utf8 const* str);
#define c_mbsarrdelall	StringArrayUTF8_RemoveAll
//!@}
//!@doc Like Array_RemoveAll(), but you can supply a custom `del` function
//!@{
void					StringArrayUTF8_RemoveAll_F(t_utf8** strarr, t_utf8 const* str, void (*del)(t_utf8*));
#define c_mbsarrfdelall	StringArrayUTF8_RemoveAll_F
//!@}



//!@doc Creates a new string array from the given `strarr`, where any occurence of `str_old` is replaced with `str_new`
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	str_old	The string to be replaced
**	@param	str_new	The replacement for the resulting string array
**	@returns
**	A newly created string array copied from `strarr`, in which in any string equal to `str_old`
**	will instead have a value of `str_new`, or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_utf8**				StringArrayUTF8_Replace(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new);
#define c_mbsarrrep		StringArrayUTF8_Replace
//!@}

//!@doc Creates a new string array from the given `strarr`, where the first `n` occurences of `str_old` are replaced with `str_new`.
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	str_old	The string to be replaced
**	@param	str_new	The replacement for the resulting string array
**	@param	n		The amount of occurences of `str_old` to replace
**	@returns
**	A newly created string array copied from `strarr`, in which in the first (iterating forwards)
**	`n` encountered strings which are equal to `str_old` will instead have a value of `str_new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_utf8**					StringArrayUTF8_ReplaceFirst(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new, t_uint n);
#define c_mbsarrrepfirst	StringArrayUTF8_ReplaceFirst
//!@}

//!@doc Creates a new string array from the given `strarr`, where the last `n` occurences of `str_old` are replaced with `str_new`.
/*!
**	@param	strarr	The string array to use as a basis for copy and string replacement
**	@param	str_old	The string to be replaced
**	@param	str_new	The replacement for the resulting string array
**	@param	n		The amount of occurences of `str_old` to replace
**	@returns
**	A newly created string array copied from `strarr`, in which in the first (iterating backwards)
**	`n` encountered strings which are equal to `str_old` will instead have a value of `str_new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
t_utf8**					StringArrayUTF8_ReplaceLast(t_utf8 const* const* strarr, t_utf8 const* str_old, t_utf8 const* str_new, t_uint n);
#define c_mbsarrreplast		StringArrayUTF8_ReplaceLast
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
t_utf8**				StringArrayUTF8_Reverse(t_utf8 const* const* strarr);
#define c_mbsarrrev		StringArrayUTF8_Reverse
//!@}



//!@doc TODO redesign
/*!
**	@returns
**	A newly allocated string array such that every string is now
**	preceded by `n` times the character `c`.
*/
//!@{
_MALLOC()
t_utf8**				StringArrayUTF8_Pad_L(t_utf8 const* const* strarr, t_utf32 c, t_uint n);
#define c_mbsarrpadl	StringArrayUTF8_Pad_L
//!@}


/*============================================================================*\
||                    StringArray: concatenation operations                   ||
\*============================================================================*/

//!@doc Concatenates two string arrays together
/*!
**	@param	strarr1	The left-hand string array to concatenate
**	@param	strarr2 The right-hand string array to concatenate
**	@returns
**	A newly created string array which is the concatenation of `strarr1` and `strarr2`.
*/
//!@{
_MALLOC()
t_utf8**					StringArrayUTF8_Concat(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2);
#define c_mbsarrconcat		StringArrayUTF8_Concat
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
t_utf8**					StringArrayUTF8_Append(t_utf8** *a_dest, t_utf8 const* const* src);
#define c_mbsarrappend		StringArrayUTF8_Append
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
t_utf8**					StringArrayUTF8_Prepend(t_utf8 const* const* src, t_utf8** *a_dest);
#define c_mbsarrprepend		StringArrayUTF8_Prepend
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
t_utf8**					StringArrayUTF8_Merge(t_utf8** *a_strarr1, t_utf8** *a_strarr2);
#define c_mbsarrmerge		StringArrayUTF8_Merge
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
t_utf8**					StringArrayUTF8_Join(t_utf8 const* const* * strarrs, t_utf8 const* const* sep);
#define c_mbsarrjoin		StringArrayUTF8_Join
//!@}



/*============================================================================*\
||                      StringArray: comparison operations                    ||
\*============================================================================*/

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
t_bool					StringArrayUTF8_Equals(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2);
#define c_mbsarrequ		StringArrayUTF8_Equals
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
t_bool					StringArrayUTF8_Equals_N(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2, t_uint n);
#define c_mbsarrnequ	StringArrayUTF8_Equals_N
//!@}



//!@doc Compares two string arrays using the given `compare` function
/*!
**	@param	strarr1	The first string array to compare
**	@param	strarr2	The second string array to compare
**	@param	compare	The function used to determine whether strings are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					StringArrayUTF8_Compare	(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2, t_sint (*compare)(t_utf8 const* str1, t_utf8 const* str2));
#define c_mbsarrcmp		StringArrayUTF8_Compare

//!@doc Compares two string arrays using the given `compare` function, for the `n` first strings
/*!
**	@param	strarr1	The first string array to compare
**	@param	strarr2	The second string array to compare
**	@param	compare	The function used to determine whether strings are considered "equal" or not
**	@param	n		The amount of strings to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					StringArrayUTF8_Compare_N	(t_utf8 const* const* strarr1, t_utf8 const* const* strarr2, t_sint (*compare)(t_utf8 const* str1, t_utf8 const* str2), t_uint n);
#define c_mbsarrncmp	StringArrayUTF8_Compare_N



/*============================================================================*\
||                      StringArray: analysis operations                      ||
\*============================================================================*/

//!@doc Returns the first encountered item in the given `strarr` matching the given `str`
/*!
**	@param	strarr	The string array to look through
**	@param	str		The `str` pointer to match against
**	@returns
**	The first encountered item of the given `strarr` which is equal to `item`,
**	or `NULL` if no such item was found.
*/
//!@{
t_utf8* const*			StringArrayUTF8_Find(t_utf8* const* strarr, t_utf8 const* str);
#define c_mbsarrfind	StringArrayUTF8_Find
//!@}

//!@doc Returns the first encountered item in the given `strarr` matching the given `str`
/*!
**	@param	strarr	The string array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given `strarr` for which the given `match` function
**	returned `TRUE`. Otherwise, returns `NULL` if no such item was found.
*/
//!@{
t_utf8* const*			StringArrayUTF8_Find_F(t_utf8* const* strarr, t_bool (*match)(t_utf8 const* str));
#define c_mbsarrffind	StringArrayUTF8_Find_F
//!@}

//!@doc Returns the index of the first encountered item in the given `strarr` matching the given `str`
/*!
**	@param	strarr	the string array to look through
**	@param	str		the `str` pointer to match against
**	@returns
**	The first encountered item of the given `strarr` which is equal to `str`,
**	or `-1` if no such item was found.
*/
//!@{
t_sint					StringArrayUTF8_IndexOf(t_utf8 const* const* strarr, t_utf8 const* str);
#define c_mbsarrfindi	StringArrayUTF8_IndexOf
//!@}

//!@doc Returns the index of the first encountered item in the given `strarr` matching the given `str`
/*!
**	@param	strarr	the string array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given `strarr` for which the given `match` function
**	returned `TRUE`. Otherwise, `-1` if no such item was found.
*/
//!@{
t_sint					StringArrayUTF8_IndexOf_F(t_utf8 const* const* strarr, t_bool (*match)(t_utf8 const* str));
#define c_mbsarrffindi	StringArrayUTF8_IndexOf_F
//!@}



//!	Counts the amount of occurences of the char `c` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint						StringArrayUTF8_Count_Char(t_utf8 const* const* strarr, t_utf32 c);
#define c_mbsarrcount_char	StringArrayUTF8_Count_Char
//!@}

//!	Counts the amount of occurences of any of the chars in the given `charset` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint						StringArrayUTF8_Count_Charset(t_utf8 const* const* strarr, t_utf8 const* cset);
#define c_mbsarrcount_cset	StringArrayUTF8_Count_Charset
//!@}

//!	Counts the amount of occurences of the string `query` in the given string array `strarr`.
/*!
**	TODO document this
*/
//!@{
t_uint						StringArrayUTF8_Count_String(t_utf8 const* const* strarr, t_utf8 const* query);
#define c_mbsarrcount_str	StringArrayUTF8_Count_String
//!@}



// TODO StringArrayUTF8_Has()
// TODO StringArrayUTF8_HasOnly()



/*============================================================================*\
||                      StringArray: functional operations                    ||
\*============================================================================*/

//!@doc Executes the given function `f` for each string contained in the given string array `strarr`.
/*!
**	NOTE: the return value of this `f` function will be assigned to the string in `strarr`
**	This means that if you wish for your `f` function to return a newly allocated string,
**	to replace the old one, you should remember to deallocate the old string.
**
**	@param	strarr	The string array to iterate upon.
**	@param	f		The function to execute for each string in the string array.
**					The returned value will replace the corresponding string in the string array.
*/
//!@{
void					StringArrayUTF8_Iterate(t_utf8** strarr, t_utf8* (*f)(t_utf8* str));
#define c_mbsarriter	StringArrayUTF8_Iterate
//!@}
//!@doc Like StringArrayUTF8_Iterate(), but the user-supplied function receives the current index
//!@{
void					StringArrayUTF8_Iterate_I(t_utf8** strarr, t_utf8* (*f)(t_utf8* str, t_uint index));
#define c_mbsarriiter	StringArrayUTF8_Iterate_I
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
t_utf8**				StringArrayUTF8_Map(t_utf8 const* const* strarr, t_utf8* (*map)(t_utf8 const* str));
#define c_mbsarrmap		StringArrayUTF8_Map
//!@}
//!@doc Like StringArrayUTF8_Map(), but the user-supplied function receives the current index
//!@{
t_utf8**				StringArrayUTF8_Map_I(t_utf8 const* const* strarr, t_utf8* (*map)(t_utf8 const* str, t_uint index));
#define c_mbsarrimap	StringArrayUTF8_Map_I
//!@}



//!@doc Creates a new string array which is a subset of `strarr`, with only the strings where the `filter` function returned `TRUE`
/*!
**	@param	strarr	The string array whose strings should be iterated upon
**	@param	filter	The function to call to check if an string of `strarr` should be added to the result
**	@returns
**	A new string array, created by duplicating the strings of the given `array`
**	for which the corresponding call to the `filter` function returned `TRUE`.
*/
//!@{
t_utf8**				StringArrayUTF8_Filter(t_utf8 const* const* strarr, t_bool (*filter)(t_utf8 const* str));
#define c_mbsarrfilter	StringArrayUTF8_Filter
//!@}
//!@doc Like StringArrayUTF8_Filter(), but the user-supplied function receives the current index
//!@{
t_utf8**				StringArrayUTF8_Filter_I(t_utf8 const* const* strarr, t_bool (*filter)(t_utf8 const* str, t_uint index));
#define c_mbsarrifilter	StringArrayUTF8_Filter_I
//!@}



//!@doc Creates a single value by executing the given function `f` for each string of the given string array `strarr`.
/*!
**	The difference between StringArrayUTF8_Reduce() and StringArrayUTF8_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	strarr	The string array to iterate upon.
**	@param	reduce	The user-specified function to execute for each string of the given string array `strarr`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type.
**	@returns
**	A single value, of any type, which is created by calling `f()` for each string of the given `strarr`.
*/
//!@{
void*					StringArrayUTF8_Reduce(t_utf8 const* const* strarr, void* (*f)(t_utf8 const* str, void* acc));
#define c_mbsarrreduce	StringArrayUTF8_Reduce
//!@}
//!@doc Like StringArrayUTF8_Reduce(), but the user-supplied function receives the current index
//!@{
void*					StringArrayUTF8_Reduce_I(t_utf8 const* const* strarr, void* (*f)(t_utf8 const* str, void* acc, t_uint index));
#define c_mbsarrireduce	StringArrayUTF8_Reduce_I
//!@}

//!@doc Creates a single value by executing the given function `f` for each string of the given string array `strarr`.
/*!
**	The difference between StringArrayUTF8_Fold() and StringArrayUTF8_Reduce() is that with this function,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	strarr	The string array to iterate upon.
**	@param	reduce	The user-specified function to execute for each string of the given string array `strarr`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type.
**	@returns
**	A single value, of any type, which is created by calling `f()` for each string of the given `strarr`.
*/
//!@{
void*					StringArrayUTF8_Fold(t_utf8 const* const* strarr, void* (*f)(t_utf8 const* str, void* acc), void* initial);
#define c_mbsarrfold	StringArrayUTF8_Fold
//!@}
//!@doc Like StringArrayUTF8_Reduce(), but the user-supplied function receives the current index
//!@{
void*					StringArrayUTF8_Fold_I(t_utf8 const* const* strarr, void* (*f)(t_utf8 const* str, void* acc, t_uint index), void* initial);
#define c_mbsarrifold	StringArrayUTF8_Fold_I
//!@}



/*! @endgroup */
HEADER_END
#endif
