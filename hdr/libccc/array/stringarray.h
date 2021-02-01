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

#ifndef __LIBCCC_ARRAY_STRINGARRAY_H
#define __LIBCCC_ARRAY_STRINGARRAY_H
/*! @file libccc/array/stringarray.h
**	This header defines some useful functions for string array (char**) handling.
**	@addtogroup libccc/array/stringarray
**	@{
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
**                      String to StringArray Dividers                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
_MALLOC
char**							String_Split_Char(char const* str, char c);
#define c_strsplit_char			String_Split_Char

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by any of the 'char_sep' separators, or the edges
**	of the string.
*/
_MALLOC
char**							String_Split_Charset(char const* str, char const* sep_chars);
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
_MALLOC
char**							String_Split_String(char const* str, char const* query);
#define c_strsplit_str			String_Split_String

/*!
**	Returns a string array which is the result of dividing str into chunks of
**	equal size n, safe for the last chunk of length <= n.
*/
_MALLOC
char**							String_Divide(char const* str, t_size n);
#define c_strdivide				String_Divide


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a null-terminated list of unset char*, of length length.
*/
_MALLOC
char**							StringArray_New(t_u32 length);
#define c_strarrnew				StringArray_New

/*!
**	Returns a newly allocated string array, which has y line and x characters
**	per lines (+1 for null-termination), every character set to the value c.
*/
_MALLOC
char**							StringArray_New_C(t_u32 y, t_size x, const char c);
#define c_strarrcnew			StringArray_New_C

/*!
**	Frees all allocations in a string array, then the string array itself.
*/
void							StringArray_Delete(char** *a_strarr);
#define c_strarrdel				StringArray_Delete

/*!
**	Returns a newly allocated string array, the result of mapping each string
**	of strarr by f. f should be a function that allocates and returns a new
**	string.
*/
_MALLOC
char**							StringArray_Map(char const** strarr, char *(*f)(char const*));
#define c_strarrmap				StringArray_Map

/*!
**	Transforms the content of the input string array, by mapping each string
**	of strarr by f. f should be a function that does not allocate a new string;
** 	but instead edits the string's content in place.
*/
void							StringArray_Map_InPlace(char** *a_strarr, char *(*f)(char*));
#define c_strarrmap_inplace		StringArray_Map_InPlace

/*!
**	Returns a newly allocated string array such that every string is now
**	preceded by n times the character c.
*/
_MALLOC
char**							StringArray_Pad_L(char const** strarr, const char c, t_u32 n);
#define c_strarrpad_l			StringArray_Pad_L

/*!
**	Returns a newly allocated string array, which is the result of removing
**	the lines from index 'start' to 'start + length' from strarr.
*/
_MALLOC
char**							StringArray_Sub(char const** strarr, t_u32 start, t_u32 length);
#define c_strarrsub				StringArray_Sub

/*!
**	Returns a newly allocated string which is the fold/reduce concatenation
**	of all strings in strarr, with the string 'sep' added between each string.
*/
_MALLOC
char*							StringArray_Fold(char const** strarr, char const* sep);
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
_MALLOC
char**							StringArray_Join(char const** strarr1, char const** strarr2);
#define c_strarrjoin			StringArray_Join

/*!
**	Returns the concatenation of 'strarr1' and 'strarr2', and deletes both
**	inputs from memory. Also returns the result.
*/
_MALLOC
char**							StringArray_Merge(char** *a_strarr1, char** *a_strarr2);
#define c_strarrmerge			StringArray_Merge

/*!
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
_MALLOC
char**							StringArray_Append(char** *a_dest, char const** src);
#define c_strarrappend			StringArray_Append


/*!
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
_MALLOC
char**							StringArray_Prepend(char const** src, char** *a_dest);
#define c_strarrprepend			StringArray_Prepend

/*!
**	Inserts the string array 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char**							StringArray_Insert_InPlace(char** *a_dest, char const** src, t_u32 index);
#define c_strarrinsert_inplace	StringArray_Insert_InPlace



/*
** ************************************************************************** *|
**                        StringArray Content Analysis                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the number of strings in a null-terminated string array.
*/
t_u32							StringArray_Length(char const** strarr);
#define c_strarrlen				StringArray_Length

/*!
**	Counts the number of occurences of char c in string array strarr/
*/
t_u32							StringArray_Count_Char(char const** strarr, char const c);
#define c_strarrcount_char		StringArray_Count_Char

/*!
**	Counts the total number of occurences of any of the chars in cset in strarr.
*/
t_u32							StringArray_Count_Charset(char const** strarr, char const* cset);
#define c_strarrcount_charset	StringArray_Count_Charset

/*!
**	Counts the number of occurences of the string 'query' in strarr.
*/
t_u32							StringArray_Count_String(char const** strarr, char const* query);
#define c_strarrcount_str		StringArray_Count_String



/*! @} */
HEADER_END
#endif
