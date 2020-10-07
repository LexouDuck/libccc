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
**                                  Macros                                    *|
** ************************************************************************** *|
*/

#define String_Split_Char			ft_strsplit_char
#define String_Split_Charset		ft_strsplit_charset
#define String_Split_String			ft_strsplit_str
#define String_Divide				ft_strdivide

#define StringArray_New				ft_strarrnew
#define StringArray_New_C			ft_strarrcnew
#define StringArray_Delete			ft_strarrdel

#define StringArray_Merge			ft_strarrmerge
#define StringArray_Append			ft_strarrappend
#define StringArray_Prepend			ft_strarrprepend
#define StringArray_Insert_InPlace	ft_strarrinsert_inplace

#define StringArray_Map				ft_strarrmap
#define StringArray_Map_InPlace		ft_strarrmap_inplace
#define StringArray_Pad_L			ft_strarrpad_l
#define StringArray_Sub				ft_strarrsub
#define StringArray_Join			ft_strarrjoin

#define StringArray_Length			ft_strarrlen
#define StringArray_Count_Char		ft_strarrcount_char
#define StringArray_Count_Charset	ft_strarrcount_charset
#define StringArray_Count_String	ft_strarrcount_str


/*
** ************************************************************************** *|
**                      String to StringArray Dividers                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
char	**ft_strsplit_char(char const *str, char c);

/*!
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by any of the 'char_sep' separators, or the edges
**	of the string.
*/
char	**ft_strsplit_charset(char const *str, char const *sep_chars);

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
char	**ft_strsplit_str(char const *str, char const *query);

/*!
**	Returns a string array which is the result of dividing str into chunks of
**	equal size n, safe for the last chunk of length <= n.
*/
char	**ft_strdivide(const char *str, t_size n);


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a null-terminated list of unset char*, of length length.
*/
char	**ft_strarrnew(t_u32 length);

/*!
**	Returns a newly allocated string array, which has y line and x characters
**	per lines (+1 for null-termination), every character set to the value c.
*/
char	**ft_strarrcnew(t_u32 y, t_size x, const char c);

/*!
**	Frees all allocations in a string array, then the string array itself.
*/
void	ft_strarrdel(char** *a_strarr);

/*!
**	Returns a newly allocated string array, the result of mapping each string
**	of strarr by f. f should be a function that allocates and returns a new
**	string.
*/
char	**ft_strarrmap(char const **strarr, char *(*f)(char const *));

/*!
**	Transforms the content of the input string array, by mapping each string
**	of strarr by f. f should be a function that does not allocate a new string;
** 	but instead edits the string's content in place.
*/
void	ft_strarrmap_inplace(char** *a_strarr, char *(*f)(char *));

/*!
**	Returns a newly allocated string array such that every string is now
**	preceded by n times the character c.
*/
char	**ft_strarrpad_l(const char **strarr, const char c, t_u32 n);

/*!
**	Returns a newly allocated string array, which is the result of removing
**	the lines from index 'start' to 'start + length' from strarr.
*/
char	**ft_strarrsub(const char **strarr, t_u32 start, t_u32 length);

/*!
**	Returns a newly allocated string which is the fold/reduce concatenation
**	of all strings in strarr, with the string 'sep' added between each string.
*/
char	*ft_strarrjoin(char const **strarr, char const *sep);


/*
** ************************************************************************** *|
**                        StringArray In Place Editors                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the concatenation of 'strarr1' and 'strarr2', and deletes both
**	inputs from memory. Also returns the result.
*/
char		**ft_strarrmerge(char** *a_strarr1, char* **a_strarr2);

/*!
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char		**ft_strarrappend(char** *a_dest, char const** src);


/*!
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char		**ft_strarrprepend(char const** src, char** *a_dest);

/*!
**	Inserts the string array 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char		**ft_strarrinsert_inplace(char** *a_dest, char const** src, t_u32 index);



/*
** ************************************************************************** *|
**                        StringArray Content Analysis                        *|
** ************************************************************************** *|
*/

/*!
**	Returns the number of strings in a null-terminated string array.
*/
t_u32	ft_strarrlen(char const **strarr);

/*!
**	Counts the number of occurences of char c in string array strarr/
*/
t_u32	ft_strarrcount_char(char const **strarr, char const c);

/*!
**	Counts the total number of occurences of any of the chars in cset in strarr.
*/
t_u32	ft_strarrcount_charset(char const **strarr, char const *cset);

/*!
**	Counts the number of occurences of the string 'query' in strarr.
*/
t_u32	ft_strarrcount_str(char const **strarr, char const *query);



/*! @} */
HEADER_END
#endif
