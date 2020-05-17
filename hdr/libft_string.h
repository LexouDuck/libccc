/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
#define LIBFT_STRING_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define String_New(n)							ft_strnew(n)
#define String_Set(str, c)						ft_strset(str, c)
#define String_Clear(str)						ft_strclr(str)
#define String_Delete(str)						ft_strdel(str)
#define String_Duplicate(str) 					ft_strdup(str)
#define String_Copy(dest, src)					ft_strcpy(dest, src)
#define String_Copy_N(dest, src, n)				ft_strncpy(dest, src, n)
#define String_Copy_L(dest, src, size)			ft_strlcpy(dest, src, size)
#define String_Concat(dest, src)				ft_strcat(dest, src)
#define String_Concat_N(dest, src, n)			ft_strncat(dest, src, n)
#define String_Concat_L(dest, src, size)		ft_strlcat(dest, src, size)

#define String_Length(str)						ft_strlen(str)
#define String_Compare(str1, str2)				ft_strcmp(str1, str2)
#define String_Compare_N(str1, str2, n)			ft_strncmp(str1, str2, n)
#define String_Equals(str1, str2)				ft_strequ(str1, str2)
#define String_Equals_N(str1, str2, n)			ft_strnequ(str1, str2, n)
#define String_Has(str, charset)				ft_strhas(str, charset)
#define String_HasOnly(str, charset)			ft_strhasonly(str, charset)
#define String_Count_Char(str, c)				ft_strcount_char(str, c)
#define String_Count_Charset(str, charset)		ft_strcount_charset(str, charset)
#define String_Count_String(str, query)			ft_strcount_str(str, query)

#define String_Find_Char(str, c)				ft_strchr(str, c)
#define String_Find_CharIndex(str, c)			ft_strichr(str, c)
#define String_Find_String(str, query)			ft_strstr(str, query)
#define String_Find_StringIndex(str, query)		ft_stristr(str, query)
#define String_Find_R_Char(str, c)				ft_strrchr(str, c)
#define String_Find_R_String(str, query)		ft_strrstr(str, query)
#define String_Find_N_Char(str, c, n)			ft_strnchr(str, c, n)
#define String_Find_N_String(str, query, n)		ft_strnstr(str, query, n)
#define String_Remove(str, query)				ft_strremove(str, query)
#define String_ToEscape(str)					ft_strtoescape(str)
#define String_Replace_Char(str, old, new)		ft_strrep_char(str, old, new)
#define String_Replace_Charset(str, old, new)	ft_strrep_charset(str, old, new)
#define String_Replace_String(str, old, new)	ft_strrep_str(str, old, new)

#define String_Merge(a_s1, a_s2)						ft_strmerge(a_s1, a_s2)
#define String_Append(dest, src)						ft_strappend(dest, src)
#define String_Prepend(src, dest)						ft_strprepend(src, dest)
#define String_Insert_InPlace(dest, src, index)			ft_strinsert_inplace(dest, src, index)
#define String_Replace_Char_InPlace(str, old, new)		ft_strrep_char_inplace(str, old, new)
#define String_Replace_Charset_InPlace(str, old, new)	ft_strrep_charset_inplace(str, old, new)
#define String_Replace_String_InPlace(str, old, new)	ft_strrep_str_inplace(str, old, new)
#define String_Map_InPlace(a_str, f)					ft_strmap_inplace(a_str, f)

#define String_Trim(str, charset)			ft_strtrim(str, charset)
#define String_Trim_L(str, charset)			ft_strtrim_l(str, charset)
#define String_Trim_R(str, charset)			ft_strtrim_r(str, charset)
#define String_Pad(str, c, size)			ft_strpad(str, c, size)
#define String_Pad_L(str, c, size)			ft_strpad_l(str, c, size)
#define String_Pad_R(str, c, size)			ft_strpad_r(str, c, size)
#define String_ToPrintableString(str)		ft_strprint(str)

#define String_Reverse(str)					ft_strrev(str)
#define String_Join(str1, str2)				ft_strjoin(str1, str2)
#define String_Insert(dest, src, index)		ft_strinsert(dest, src, index)
#define String_Sub(str, index, n)			ft_strsub(str, index, n)
#define String_Iterate(str, f)				ft_striter(str, f)
#define String_Iterate_I(str, f)			ft_striteri(str, f)
#define String_Map(str, f)					ft_strmap(str, f)
#define String_Map_I(str, f)				ft_strmapi(str, f)



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	typedef void	(*f_string_iterate)(char *);
**	typedef void	(*f_string_iterate_i)(unsigned int, char *);
**	typedef char	(*f_string_map)(char);
**	typedef char	(*f_string_map_i)(unsigned int, char);
*/



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

/*
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to '\0'.
*/
char	*ft_strnew(t_size n);

/*
**	Sets every byte of the given string 'str' to 'c', only stopping upon
**	reading a '\0' string terminator character.
*/
void	ft_strset(char *str, char c);

/*
**	Clears the given string 'str', setting each character of 'str' to '\0'.
*/
void	ft_strclr(char *str);

/*
**	Deletes the string pointed to by 'ptr', freeing the associated memory.
*/
void	ft_strdel(char **ptr);

/*
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated).
*/
char	*ft_strdup(char const *str);

/*
**	Copies the given string 'src' into 'dest' (null-terminator included),
**	and returns 'dest' (no allocation is performed).
*/
char	*ft_strcpy(char *dest, char const *src);

/*
**	Copies the first 'n' characters of the given string 'src' into 'dest',
**	and returns 'dest' (no allocation is performed).
*/
char	*ft_strncpy(char *dest, char const *src, t_size n);

/*
**	Copies the given string 'src' into 'dest', null-terminating the result
**	(the '\0' is placed at: ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size	ft_strlcpy(char *dest, char const *src, t_size size);

/*
**	Concatenates the given string 'src' to the end of 'dest',
**	(removing dest's '\0' terminator) and returns 'dest'.
*/
char	*ft_strcat(char *dest, char const *src);

/*
**	Concatenates the first 'n' characters of the given string 'src'
**	to the end of 'dest', and returns 'dest'.
*/
char	*ft_strncat(char *dest, char const *src, t_size n);

/*
**	Concatenates characters of the given string 'src' to the end of 'dest',
**	null-terminating the result (places the '\0' at ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size	ft_strlcat(char *dest, char const *src, t_size size);



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

/*
**	Returns the length of the given null-terminated string 'str'.
*/
t_size	ft_strlen(char const *str);

/*
**	Compares the two given strings, and returns the first difference
**	between characters encountered (str1[i] - str2[i]).
**	Otherwise, it will return 0 if 'str1' and 'str2' are identical.
*/
int		ft_strcmp(char const *str1, char const *str2);

/*
**	Compares at most 'n' chars of the two given strings, and returns
**	the first difference of characters encountered: (str1[i] - str2[i]).
*/
int		ft_strncmp(char const *str1, char const *str2, t_size n);

/*
**	Returns 1 if the two given strings match, and 0 otherwise.
*/
t_bool	ft_strequ(char const *str1, char const *str2);

/*
**	Returns 1 if the first 'n' chars of the two given strings match,
**	and returns 0 if this is not the case.
*/
t_bool	ft_strnequ(char const *str1, char const *str2, t_size n);

/*
**	Returns 1 if the given string 'str' contains at least one occurence
**	of any character found inside 'charset', returns 0 otherwise.
*/
t_bool	ft_strhas(char const *str, char const *charset);

/*
**	Returns 1 if all the characters inside the given string 'str'
**	are contained within the string 'charset', returns 0 otherwise.
*/
t_bool	ft_strhasonly(char const *str, char const *charset);

/*
**	Returns the amount of occurences of char 'c' in the given string 'str'.
*/
t_size	ft_strcount_char(char const *str, char c);

/*
**	Returns the amount of occurences of chars in 'cset' in the given string
**	'str'.
*/
t_size	ft_strcount_charset(char const *str, char const *cset);

/*
**	Returns the amount of occurences of 'query' in the given string 'str'.
*/
t_size	ft_strcount_str(char const *str, char const *query);



/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

/*
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strchr(char const *str, char c);

/*
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strstr(char const *str, char const *query);

/*
**	Returns the first index at which 'c' is found in 'str', or -1 if 'c' does
**	not exist in 'str'.
*/
t_s32	ft_strichr(char const *str, char c);

/*
**	Returns the first index at which 'query' is found in 'str', or -1 if
**	'query' does not exist in str.
*/
t_s32	ft_stristr(char const *str, char const *query);

/*
**	Returns a pointer to the last occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strrchr(char const *str, char c);

/*
**	Returns the last occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strrstr(char const *str, char const *query);

/*
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char	*ft_strnchr(char const *str, char c, t_size n);

/*
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char	*ft_strnstr(char const *str, char const *query, t_size n);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which all occurences of the string 'query' have been removed.
*/
char	*ft_strremove(char const *str, char const *query);

/*
**	Returns a new null-terminated string which is a copy of 'str', in which
**	all non-printable characters found in 'str' are made into printable
**	ANSI-C '\xHH' escape sequences (where "H"s are uppercase hex digits).
*/
char	*ft_strtoescape(char const *str);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of an 'old' char is replaced with a 'new' char.
*/
//TODO implement
char	*ft_strrep_char(char const *str,
	char const old,
	char const new);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every char in the 'old' charset is replaced by the
**	corresponding character in the 'new' charset (at the same index).
*/
//TODO implement
char	*ft_strrep_charset(char const *str,
	char const *old,
	char const *new);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of the string 'old' is replaced with 'new'.
**	NB: see stringarray.h -> ft_strsplit_str for extra notes on bevahior.
*/
char	*ft_strrep_str(char const *str,
	char const *old,
	char const *new);


/*
** ************************************************************************** *|
**                           String In Place Editors                          *|
** ************************************************************************** *|
*/

/*
**	Returns the concatenation of 's1' and 's2', and deletes both inputs from
**	memory. Also returns the result.
*/
char		*ft_strmerge(char **a_s1, char **a_s2);

/*
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char		*ft_strappend(char **dest, char const *src);


/*
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char		*ft_strprepend(char const *src, char **dest);

/*
**	Inserts the string 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char		*ft_strinsert_inplace(char **dest, char const *src, t_u32 index);

/*
**	Replaces every occurence of 'old' by 'new' in 'str'.
*/
void		ft_strrep_char_inplace(char *str,
	char const old,
	char const new);

/*
**	Replaces 'old' charset by 'new' charset in 'str'.
**	Works like the bash function tr. Substitutes old[i] by new[i] in 'str'.
**	Fails silently if strlen is different for 'old' and 'new', or if a
**	character is repeated in 'old' (only one image for every antecedent), or if
**	'old' or 'new' are the empty string.
*/
void		ft_strrep_charset_inplace(char *str,
	char const *old,
	char const *new);

/*
**	Replaces every occurence of the query old by the string new in str.
**	NB: see stringarray.h -> ft_strsplit_str for extra notes on bevahior.
*/
void		ft_strrep_str_inplace(char **a_str,
	char const *old,
	char const *new);

/*
**	Changes the content of '*a_str' by applying f to each of its chars.
**	Deletes 'a_str', and sets the result in it instead. Also returns the 
**	result.
*/
char		*ft_strmap_inplace(char **a_str, char (*f)(char));


/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

/*
**	Returns a new string from 'str' in which all leading and trailing
**	whitespace characters (' ', \n, \t,  \r, \v and \f) have been removed.
*/
char	*ft_strtrim(char const *str, char const *charset);

/*
**	Returns a new string from 'str' in which all leading
**	characters present in 'charset' have been removed.
*/
char	*ft_strtrim_l(char const *str, char const *charset);

/*
**	Returns a new string from 'str' in which all trailing
**	characters present in 'charset' have been removed.
*/
char	*ft_strtrim_r(char const *str, char const *charset);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on both sides
**	if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad(char const *str, char c, t_size length);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	left side if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad_l(char const *str, char c, t_size length);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	right side if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad_r(char const *str, char c, t_size length);

/*
**	Returns a new null-terminated string where every non-printable character
**	of 'str' is replaced by either its 'normal' escape sequence (if available)
**	or a '\x'-type byte escape sequence otherwise.
*/
char	*ft_strprint(char const *str);

/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

/*
**	Returns a newly allocated string which is a copy of the given string 'str',
**	but in reverse order (except for the \0 terminator, obviously).
*/
char	*ft_strrev(char const *str);

/*
**	Returns a new null-terminated string which is the result of
**	the concatenation of the two given strings 'str1' and 'str2'.
*/
char	*ft_strjoin(char const *str1, char const *str2);

/*
**	Returns a reallocated version of the given string 'dest', in which
**	the string 'str' has been inserted at the index 'offset'.
*/
char	*ft_strinsert(char const *dest, char const *src, t_size offset);

/*
**	Returns a new null-terminated string which is a subsection of 'str',
**	starting at char index 'index' and copying 'n' characters.
*/
char	*ft_strsub(char const *str, t_size index, t_size n);

/*
**	Iterates upon each character of the given string 'str',
**	applying the given function 'f' to each of its characters.
*/
void	ft_striter(char *str, void (*f)(char *));

/*
**	Iterates upon each character of the given string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
void	ft_striteri(char *str, void (*f)(t_size, char *));

/*
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars.
*/
char	*ft_strmap(char const *str, char (*f)(char));

/*
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
char	*ft_strmapi(char const *str, char (*f)(t_size, char));

#endif
