/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stringarray.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_STRINGARRAY_H
#define __LIBFT_STRINGARRAY_H
/*! @file libft_stringarray.h
**	This header defines some useful functions for string array (char**) handling.
**	@addtogroup libft_stringarray
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

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
char**							String_Split_Char(char const *str, char c);
#define ft_strsplit_char		String_Split_Char

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by any of the 'char_sep' separators, or the edges
**	of the string.
*/
char**							String_Split_Charset(char const *str, char const *sep_chars);
#define ft_strsplit_charset		String_Split_Charset

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
char**							String_Split_String(char const *str, char const *query);
#define ft_strsplit_str			String_Split_String

/*!
**	Returns a string array which is the result of dividing str into chunks of
**	equal size n, safe for the last chunk of length <= n.
*/
char**							String_Divide(const char *str, t_size n);
#define ft_strdivide			String_Divide


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a null-terminated list of unset char*, of length length.
*/
char**							StringArray_New(t_u32 length);
#define ft_strarrnew			StringArray_New

/*!
**	Returns a newly allocated string array, which has y line and x characters
**	per lines (+1 for null-termination), every character set to the value c.
*/
char**							StringArray_New_C(t_u32 y, t_size x, const char c);
#define ft_strarrcnew			StringArray_New_C

/*!
**	Frees all allocations in a string array, then the string array itself.
*/
void							StringArray_Delete(char** *a_strarr);
#define ft_strarrdel			StringArray_Delete

/*!
**	Returns a newly allocated string array, the result of mapping each string
**	of strarr by f. f should be a function that allocates and returns a new
**	string.
*/
char**							StringArray_Map(char const **strarr, char *(*f)(char const *));
#define ft_strarrmap			StringArray_Map

/*!
**	Transforms the content of the input string array, by mapping each string
**	of strarr by f. f should be a function that does not allocate a new string;
** 	but instead edits the string's content in place.
*/
void							StringArray_Map_InPlace(char** *a_strarr, char *(*f)(char *));
#define ft_strarrmap_inplace	StringArray_Map_InPlace

/*!
**	Returns a newly allocated string array such that every string is now
**	preceded by n times the character c.
*/
char**							StringArray_Pad_L(const char **strarr, const char c, t_u32 n);
#define ft_strarrpad_l			StringArray_Pad_L

/*!
**	Returns a newly allocated string array, which is the result of removing
**	the lines from index 'start' to 'start + length' from strarr.
*/
char**							StringArray_Sub(const char **strarr, t_u32 start, t_u32 length);
#define ft_strarrsub			StringArray_Sub

/*!
**	Returns a newly allocated string which is the fold/reduce concatenation
**	of all strings in strarr, with the string 'sep' added between each string.
*/
char*							StringArray_Join(char const **strarr, char const *sep);
#define ft_strarrjoin			StringArray_Join


/*
** ************************************************************************** *|
**                        StringArray In Place Editors                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the concatenation of 'strarr1' and 'strarr2', and deletes both
**	inputs from memory. Also returns the result.
*/
char**							StringArray_Merge(char** *a_strarr1, char* **a_strarr2);
#define ft_strarrmerge			StringArray_Merge

/*!
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char**							StringArray_Append(char** *a_dest, char const** src);
#define ft_strarrappend			StringArray_Append


/*!
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char**							StringArray_Prepend(char const** src, char** *a_dest);
#define ft_strarrprepend		StringArray_Prepend

/*!
**	Inserts the string array 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char**							StringArray_Insert_InPlace(char** *a_dest, char const** src, t_u32 index);
#define ft_strarrinsert_inplace	StringArray_Insert_InPlace



/*
** ************************************************************************** *|
**                        StringArray Content Analysis                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the number of strings in a null-terminated string array.
*/
t_u32							StringArray_Length(char const **strarr);
#define ft_strarrlen			StringArray_Length

/*!
**	Counts the number of occurences of char c in string array strarr/
*/
t_u32							StringArray_Count_Char(char const **strarr, char const c);
#define ft_strarrcount_char		StringArray_Count_Char

/*!
**	Counts the total number of occurences of any of the chars in cset in strarr.
*/
t_u32							StringArray_Count_Charset(char const **strarr, char const *cset);
#define ft_strarrcount_charset	StringArray_Count_Charset

/*!
**	Counts the number of occurences of the string 'query' in strarr.
*/
t_u32							StringArray_Count_String(char const **strarr, char const *query);
#define ft_strarrcount_str		StringArray_Count_String



/*! @} */
HEADER_END
#endif
