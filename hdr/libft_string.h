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

#ifndef __LIBFT_STRING_H
#define __LIBFT_STRING_H
/*! @file libft_string.h
**	This header defines the common standard string (char*) manipulation functions.
**	@addtogroup libft_string
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
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/* TODO function pointers
**	typedef void	(*f_string_iterate)		(char* )
**	typedef void	(*f_string_iterate_i)	(unsigned int, char* )
**	typedef char	(*f_string_map)			(char)
**	typedef char	(*f_string_map_i)		(unsigned int, char)
*/



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to '\0'.
*/
char*				String_New(t_size n);
#define ft_strnew	String_New

/*!
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to 'c'.
*/
char*				String_New_C(t_size n, char c);
#define ft_strcnew	String_New_C

/*!
**	Sets every byte of the given string 'str' to 'c', only stopping upon
**	reading a '\0' string terminator character.
*/
void				String_Set(char* str, char c);
#define ft_strset	String_Set

/*!
**	Clears the given string 'str', setting each character of 'str' to '\0'.
*/
void				String_Clear(char* str);
#define ft_strclr	String_Clear

/*!
**	Deletes the string pointed to by 'ptr', freeing the associated memory.
*/
void				String_Delete(char* *a_str);
#define ft_strdel	String_Delete

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated).
*/
char*				String_Duplicate(char const* str);
#define ft_strdup	String_Duplicate

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated), copying at most
**	'n' characters.
*/
char*				String_Duplicate_N(char const* str, t_size n);
#define ft_strndup	String_Duplicate_N

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated), stopping at the
**	first occurence of 'c'.
*/
char*				String_Duplicate_Char(char const* str, char const c);
#define ft_strcdup	String_Duplicate_Char

/*!
**	Copies the given string 'src' into 'dest' (null-terminator included),
**	and returns 'dest' (no allocation is performed).
*/
char*				String_Copy(char* dest, char const* src);
#define ft_strcpy	String_Copy

/*!
**	Copies the first 'n' characters of the given string 'src' into 'dest',
**	and returns 'dest' (no allocation is performed).
*/
char*				String_Copy_N(char* dest, char const* src, t_size n);
#define ft_strncpy	String_Copy_N

/*!
**	Copies the given string 'src' into 'dest', null-terminating the result
**	(the '\0' is placed at: ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size				String_Copy_L(char* dest, char const* src, t_size size);
#define ft_strlcpy	String_Copy_L

/*!
**	Concatenates the given string 'src' to the end of 'dest',
**	(removing dest's '\0' terminator) and returns 'dest'.
*/
char*				String_Concat(char* dest, char const* src);
#define ft_strcat	String_Concat

/*!
**	Concatenates the first 'n' characters of the given string 'src'
**	to the end of 'dest', and returns 'dest'.
*/
char*				String_Concat_N(char* dest, char const* src, t_size n);
#define ft_strncat	String_Concat_N

/*!
**	Concatenates characters of the given string 'src' to the end of 'dest',
**	null-terminating the result (places the '\0' at ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
t_size				String_Concat_L(char* dest, char const* src, t_size size);
#define ft_strlcat	String_Concat_L



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

/*!
**	Returns the length of the given null-terminated string 'str'.
*/
t_size				String_Length(char const* str);
#define ft_strlen	String_Length

/*!
**	Compares the two given strings, and returns the first difference
**	between characters encountered (str1[i] - str2[i]).
**	Otherwise, it will return 0 if 'str1' and 'str2' are identical.
*/
int					String_Compare(char const* str1, char const* str2);
#define ft_strcmp	String_Compare

/*!
**	Compares at most 'n' chars of the two given strings, and returns
**	the first difference of characters encountered: (str1[i] - str2[i]).
*/
int					String_Compare_N(char const* str1, char const* str2, t_size n);
#define ft_strncmp	String_Compare_N

/*!
**	Returns 1 if the two given strings match, and 0 otherwise.
*/
t_bool				String_Equals(char const* str1, char const* str2);
#define ft_strequ	String_Equals

/*!
**	Returns 1 if the first 'n' chars of the two given strings match,
**	and returns 0 if this is not the case.
*/
t_bool				String_Equals_N(char const* str1, char const* str2, t_size n);
#define ft_strnequ	String_Equals_N

/*!
**	Returns 1 if the given string 'str' contains at least one occurence
**	of any character found inside 'charset', returns 0 otherwise.
*/
t_bool						String_Has(char const* str, char const* charset);
#define ft_strhas			String_Has

/*!
**	Returns 1 if all the characters inside the given string 'str'
**	are contained within the string 'charset', returns 0 otherwise.
*/
t_bool						String_HasOnly(char const* str, char const* charset);
#define ft_strhasonly		String_HasOnly

/*!
**	Returns the amount of occurences of char 'c' in the given string 'str'.
*/
t_size						String_Count_Char(char const* str, char c);
#define ft_strcount_char	String_Count_Char

/*!
**	Returns the amount of occurences of chars in 'cset' in the given string
**	'str'.
*/
t_size						String_Count_Charset(char const* str, char const* cset);
#define ft_strcount_charset	String_Count_Charset

/*!
**	Returns the amount of occurences of 'query' in the given string 'str'.
*/
t_size						String_Count_String(char const* str, char const* query);
#define ft_strcount_str		String_Count_String



/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

/*!
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_Char(char const* str, char c);
#define ft_strchr	String_Find_Char

/*!
**	Returns the first index at which 'c' is found in 'str', or -1 if 'c' does
**	not exist in 'str'.
*/
t_s32				String_Find_CharIndex(char const* str, char c);
#define ft_strichr	String_Find_CharIndex

/*!
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_String(char const* str, char const* query);
#define ft_strstr	String_Find_String

/*!
**	Returns the first index at which 'query' is found in 'str', or -1 if
**	'query' does not exist in str.
*/
t_s32				String_Find_StringIndex(char const* str, char const* query);
#define ft_stristr	String_Find_StringIndex

/*!
**	Returns a pointer to the last occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_R_Char(char const* str, char c);
#define ft_strrchr	String_Find_R_Char

/*!
**	Returns the last occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char*				String_Find_R_String(char const* str, char const* query);
#define ft_strrstr	String_Find_R_String

/*!
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char*				String_Find_N_Char(char const* str, char c, t_size n);
#define ft_strnchr	String_Find_N_Char

/*!
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char*				String_Find_N_String(char const* str, char const* query, t_size n);
#define ft_strnstr	String_Find_N_String

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which all occurences of the string 'query' have been removed.
*/
char*						String_Remove(char const* str, char const* query);
#define ft_strremove		String_Remove

/*!
**	Returns a new null-terminated string which is a copy of 'str', in which
**	all non-printable characters found in 'str' are made into printable
**	ANSI-C '\xHH' escape sequences (where "H"s are uppercase hex digits).
*/
char*						String_ToEscape(char const* str);
#define ft_strtoescape		String_ToEscape

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of an 'old' char is replaced with a 'new' char.
*/
//TODO implement
char*						String_Replace_Char(char const* str, char const char_old, char const char_new);
#define ft_strrep_char		String_Replace_Char

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every char in the 'old' charset is replaced by the
**	corresponding character in the 'new' charset (at the same index).
*/
//TODO implement
char*						String_Replace_Charset(char const* str, char const* charset_old, char const* charset_new);
#define ft_strrep_charset	String_Replace_Charset

/*!
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of the string 'old' is replaced with 'new'.
**	NB: see stringarray.h -> ft_strsplit_str for extra notes on bevahior.
*/
char*						String_Replace_String(char const* str, char const* str_old, char const* str_new);
#define ft_strrep_str		String_Replace_String



/*
** ************************************************************************** *|
**                           String In Place Editors                          *|
** ************************************************************************** *|
*/

/*!
**	Returns the concatenation of 's1' and 's2', and deletes both inputs from
**	memory. Also returns the result.
*/
char*					String_Merge(char* *a_s1, char* *a_s2);
#define ft_strmerge		String_Merge

/*!
**	Returns the concatenation of 'dest' and 'src', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char*					String_Append(char* *dest, char const* src);
#define ft_strappend	String_Append


/*!
**	Returns the concatenation of 'src' and 'dest', and deletes 'dest', replacing
**	it by the result. Also returns the result.
*/
char*					String_Prepend(char const* src, char* *dest);
#define ft_strprepend	String_Prepend

/*!
**	Inserts the string 'src' at index 'index' in 'dest'; deletes 'dest' and
**	replaces it by the result. Also returns the result.
*/
char*								String_Insert_InPlace(char* *dest, char const* src, t_u32 index);
#define ft_strinsert_inplace		String_Insert_InPlace

/*!
**	Replaces every occurence of 'old' by 'new' in 'str'.
*/
void								String_Replace_Char_InPlace(char* str, char const char_old, char const char_new);
#define ft_strrep_char_inplace		String_Replace_Char_InPlace

/*!
**	Replaces 'old' charset by 'new' charset in 'str'.
**	Works like the bash function tr. Substitutes old[i] by new[i] in 'str'.
**	Fails silently if strlen is different for 'old' and 'new', or if a
**	character is repeated in 'old' (only one image for every antecedent), or if
**	'old' or 'new' are the empty string.
*/
void								String_Replace_Charset_InPlace(char* str, char const* charset_old, char const* charset_new);
#define ft_strrep_charset_inplace	String_Replace_Charset_InPlace

/*!
**	Replaces every occurence of the query old by the string new in str.
**	NB: see stringarray.h -> ft_strsplit_str for extra notes on bevahior.
*/
void								String_Replace_String_InPlace(char* *a_str, char const* str_old, char const* str_new);
#define ft_strrep_str_inplace		String_Replace_String_InPlace

/*!
**	Changes the content of '*a_str' by applying f to each of its chars.
**	Deletes 'a_str', and sets the result in it instead. Also returns the 
**	result.
*/
char*								String_Map_InPlace(char* *a_str, char (*f)(char));
#define ft_strmap_inplace			String_Map_InPlace



/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

/*!
**	Returns a new string from 'str' in which all leading and trailing
**	whitespace characters (' ', \n, \t,  \r, \v and \f) have been removed.
*/
char*					String_Trim(char const* str, char const* charset);
#define ft_strtrim		String_Trim

/*!
**	Returns a new string from 'str' in which all leading
**	characters present in 'charset' have been removed.
*/
char*					String_Trim_L(char const* str, char const* charset);
#define ft_strtrim_l	String_Trim_L

/*!
**	Returns a new string from 'str' in which all trailing
**	characters present in 'charset' have been removed.
*/
char*					String_Trim_R(char const* str, char const* charset);
#define ft_strtrim_r	String_Trim_R

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on both sides
**	if the desired 'length' is larger than 'str'.
*/
char*					String_Pad(char const* str, char c, t_size length);
#define ft_strpad		String_Pad

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	left side if the desired 'length' is larger than 'str'.
*/
char*					String_Pad_L(char const* str, char c, t_size length);
#define ft_strpad_l		String_Pad_L

/*!
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	right side if the desired 'length' is larger than 'str'.
*/
char*					String_Pad_R(char const* str, char c, t_size length);
#define ft_strpad_r		String_Pad_R

/*!
**	Returns a new null-terminated string where every non-printable character
**	of 'str' is replaced by either its 'normal' escape sequence (if available)
**	or a '\x'-type byte escape sequence otherwise.
*/
char*					String_ToPrintableString(char const* str);
#define ft_strprint		String_ToPrintableString



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Returns a newly allocated string which is a copy of the given string 'str',
**	but in reverse order (except for the \0 terminator, obviously).
*/
char*					String_Reverse(char const* str);
#define ft_strrev		String_Reverse

/*!
**	Returns a new null-terminated string which is the result of
**	the concatenation of the two given strings 'str1' and 'str2'.
*/
char*					String_Join(char const* str1, char const* str2);
#define ft_strjoin		String_Join

/*!
**	Returns a reallocated version of the given string 'dest', in which
**	the string 'str' has been inserted at the index 'offset'.
*/
char*					String_Insert(char const* dest, char const* src, t_size offset);
#define ft_strinsert	String_Insert

/*!
**	Returns a new null-terminated string which is a subsection of 'str',
**	starting at char index 'index' and copying 'n' characters.
*/
char*					String_Sub(char const* str, t_size index, t_size n);
#define ft_strsub		String_Sub

/*!
**	Iterates upon each character of the given string 'str',
**	applying the given function 'f' to each of its characters.
*/
void					String_Iterate(char* str, void (*f)(char* c));
#define ft_striter		String_Iterate

/*!
**	Iterates upon each character of the given string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
void					String_Iterate_I(char* str, void (*f)(t_size index, char* c));
#define ft_striteri		String_Iterate_I

/*!
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars.
*/
char*					String_Map(char const* str, char (*f)(char c));
#define ft_strmap		String_Map

/*!
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
char*					String_Map_I(char const* str, char (*f)(t_size index, char c));
#define ft_strmapi		String_Map_I



/*! @} */
HEADER_END
#endif
