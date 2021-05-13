/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/stringarray.h               |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_STRINGARRAY_H
#define __LIBCCC_STRINGARRAY_H
/*!@group{libccc_stringarray}
** @{
**	This header defines some useful functions for string array (t_char**) handling.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"
#include "libccc/char.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                      String to StringArray Dividers                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
_MALLOC()
t_char**							String_Split_Char(t_char const* str, char c);
#define c_strsplit_char			String_Split_Char

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by any of the 'char_sep' separators, or the edges
**	of the string.
*/
_MALLOC()
t_char**							String_Split_Charset(t_char const* str, t_char const* sep_chars);
#define c_strsplit_charset		String_Split_Charset

//! Splits up the given string 'str' into several parts in a string array, using 'query' as separator
/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by the full string 'query', or the edges of the
**	string.
**	NB: if a dual query overlaps in str, the query is only counted for distinct
**		parts, ie "||" for "|||aa" will return ["", "|aa"] and not
**		["", "", "aa"]. Note that this is the same behavior as many Ctrl+F:
**		to get the second result, simply keep the second part of the pattern
**		and call replace twice, without the pattern the second time.
**		Ex: "enenen" --s/enen/HIen/-> "HIenen" --s/enen/HI/--> "HIHI"
*/
_MALLOC()
t_char**							String_Split_String(t_char const* str, t_char const* query);
#define c_strsplit_str			String_Split_String

/*!
**	Returns a string array which is the result of dividing str into chunks of
**	equal size n, safe for the last chunk of length <= n.
*/
_MALLOC()
t_char**							String_Divide(t_char const* str, t_size n);
#define c_strdivide				String_Divide


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a null-terminated list of unset t_char*, of length length.
*/
_MALLOC()
t_char**							StringArray_New(t_u32 length);
#define c_strarrnew				StringArray_New

/*!
**	Returns a newly allocated string array, which has y line and x characters
**	per lines (+1 for null-termination), every character set to the value c.
*/
_MALLOC()
t_char**							StringArray_New_C(t_u32 y, t_size x, const char c);
#define c_strarrcnew			StringArray_New_C

/*!
**	Frees all allocations in a string array, then the string array itself.
*/
void							StringArray_Delete(t_char** *a_strarr);
#define c_strarrdel				StringArray_Delete

/*!
**	Returns a newly allocated string array, the result of mapping each string
**	of strarr by f. f should be a function that allocates and returns a new
**	string.
*/
_MALLOC()
t_char**							StringArray_Map(t_char const** strarr, char *(*f)(t_char const*));
#define c_strarrmap				StringArray_Map

/*!
**	Transforms the content of the input string array, by mapping each string
**	of strarr by f. f should be a function that does not allocate a new string;
** 	but instead edits the string's content in place.
*/
void							StringArray_Map_InPlace(t_char** *a_strarr, char *(*f)(t_char*));
#define c_strarrmap_inplace		StringArray_Map_InPlace

/*!
**	Returns a newly allocated string array such that every string is now
**	preceded by n times the character c.
*/
_MALLOC()
t_char**							StringArray_Pad_L(t_char const** strarr, const char c, t_u32 n);
#define c_strarrpad_l			StringArray_Pad_L

/*!
**	Returns a newly allocated string array, which is the result of removing
**	the lines from index 'start' to 'start + length' from strarr.
*/
_MALLOC()
t_char**							StringArray_Sub(t_char const** strarr, t_u32 start, t_u32 length);
#define c_strarrsub				StringArray_Sub

/*!
**	Returns a newly allocated string which is the fold/reduce concatenation
**	of all strings in strarr, with the string 'sep' added between each string.
*/
_MALLOC()
t_char*							StringArray_Fold(t_char const** strarr, t_char const* sep);
#define c_strarrfold			StringArray_Fold


/*
** ************************************************************************** *|
**                        StringArray In Place Editors                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the concatenation of 'strarr1' and 'strarr2', and deletes both
**	inputs from memory. Also returns the result.
*/
_MALLOC()
t_char**							StringArray_Join(t_char const** strarr1, t_char const** strarr2);
#define c_strarrjoin			StringArray_Join

/*!
**	Returns the concatenation of 'strarr1' and 'strarr2', and deletes both
**	inputs from memory. Also returns the result.
*/
_MALLOC()
t_char**							StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2);
#define c_strarrmerge			StringArray_Merge

/*!
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
_MALLOC()
t_char**							StringArray_Append(t_char** *a_dest, t_char const** src);
#define c_strarrappend			StringArray_Append


/*!
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
_MALLOC()
t_char**							StringArray_Prepend(t_char const** src, t_char** *a_dest);
#define c_strarrprepend			StringArray_Prepend

/*!
**	Inserts the string array 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
t_char**							StringArray_Insert_InPlace(t_char** *a_dest, t_char const** src, t_u32 index);
#define c_strarrinsert_inplace	StringArray_Insert_InPlace



/*
** ************************************************************************** *|
**                        StringArray Content Analysis                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the number of strings in a null-terminated string array.
*/
t_u32							StringArray_Length(t_char const** strarr);
#define c_strarrlen				StringArray_Length

/*!
**	Counts the number of occurences of char c in string array strarr/
*/
t_u32							StringArray_Count_Char(t_char const** strarr, char const c);
#define c_strarrcount_char		StringArray_Count_Char

/*!
**	Counts the total number of occurences of any of the chars in cset in strarr.
*/
t_u32							StringArray_Count_Charset(t_char const** strarr, t_char const* cset);
#define c_strarrcount_charset	StringArray_Count_Charset

/*!
**	Counts the number of occurences of the string 'query' in strarr.
*/
t_u32							StringArray_Count_String(t_char const** strarr, t_char const* query);
#define c_strarrcount_str		StringArray_Count_String



/*! @} */
HEADER_END
#endif
