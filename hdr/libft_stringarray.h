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

#ifndef LIBFT_STRINGARRAY_H
#define LIBFT_STRINGARRAY_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

#define String_Split_Char(str, c)			ft_strsplit_char(str, c)
#define String_Split_Charset(str, charset)	ft_strsplit_charset(str, charset)
#define String_Split_String(str, query)		ft_strsplit_str(str, query)
#define String_Divide(str, n)				ft_strdivide(str, n)

#define StringArray_New(len)				ft_strarrnew(len)
#define StringArray_New_C(y, x, c)			ft_strarrcnew(y, x, c)
#define StringArray_Delete(a_strarr)		ft_strarrdel(a_strarr)
#define StringArray_Map(strarr, f)			ft_strarrmap(strarr, f)
#define StringArray_Map_InPlace(a_sa, f)	ft_strarrmap_inplace(a_sa, f)
#define StringArray_Pad_L(strarr, c, n)		ft_strarrpad_l(strarr, c, n)
#define StringArray_Sub(strarr, start, n)	ft_strarrsub(strarr, start, n)
#define StringArray_Join(strarr, sep)		ft_strarrjoin(strarr, sep)

#define StringArray_Length(strarr)				ft_strarrlen(strarr)
#define StringArray_Count_Char(str, c)			ft_strarrcount_char(str, c)
#define StringArray_Count_Charset(str, set)		ft_strarrcount_charset(str, set)
#define StringArray_Count_String(str, query)	ft_strarrcount_str(str, query)


/*
** ************************************************************************** *|
**                      String to StringArray Dividers                        *|
** ************************************************************************** *|
*/

/*
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
char	**ft_strsplit_char(char const *str, char c);

/*
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by any of the 'char_sep' separators, or the edges
**	of the string.
*/
char	**ft_strsplit_charset(char const *str, char const *sep_chars);

/*
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

/*
**	Returns a string array which is the result of dividing str into chunks of
**	equal size n, safe for the last chunk of length <= n.
*/
char	**ft_strdivide(const char *str, t_size n);


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

/*
**	Returns a null-terminated list of unset char*, of length len.
*/
char	**ft_strarrnew(t_u32 len);

/*
**	Returns a newly allocated string array, which has y line and x characters
**	per lines (+1 for null-termination), every character set to the value c.
*/
char	**ft_strarrcnew(t_u32 y, t_size x, const char c);

/*
**	Frees all allocations in a string array, then the string array itself.
*/
void	ft_strarrdel(char ***a_strarr);

/*
**	Returns a newly allocated string array, the result of mapping each string
**	of strarr by f. f should be a function that allocates and returns a new
**	string.
*/
char	**ft_strarrmap(char const **strarr, char *(*f)(char const *));

/*
**	Transforms the content of the input string array, by mapping each string
**	of strarr by f. f should be a function that does not allocate a new string;
** 	but instead edits the string's content in place.
*/
void	ft_strarrmap_inplace(char ***a_strarr, char *(*f)(char *));

/*
**	Returns a newly allocated string array such that every string is now
**	preceded by n times the character c.
*/
char	**ft_strarrpad_l(const char **strarr, const char c, t_u32 n);

/*
**	Returns a newly allocated string array, which is the result of removing
**	the lines from index 'start' to 'start + len' from strarr.
*/
char	**ft_strarrsub(const char **strarr, t_u32 start, t_u32 len);

/*
**	Returns a newly allocated string which is the fold/reduce concatenation
**	of all strings in strarr, with the string 'sep' added between each string.
*/
char	*ft_strarrjoin(char const **strarr, char const *sep);


/*
** ************************************************************************** *|
**                        StringArray Content Analysis                        *|
** ************************************************************************** *|
*/

/*
**	Returns the number of strings in a null-terminated string array.
*/
t_u32	ft_strarrlen(char const **strarr);

/*
**	Counts the number of occurences of char c in string array strarr/
*/
t_u32	ft_strarrcount_char(char const **strarr, char const c);

/*
**	Counts the total number of occurences of any of the chars in cset in strarr.
*/
t_u32	ft_strarrcount_charset(char const **strarr, char const *cset);

/*
**	Counts the number of occurences of the string 'query' in strarr.
*/
t_u32	ft_strarrcount_str(char const **strarr, char const *query);

#endif