/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
#define LIBFT_IO_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"
#include "libft_string.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define IO_Read_File		ft_readfile
#define IO_Read_NextLine	ft_getnextline
#define IO_Read_Lines		ft_readlines

#define IO_Write_Char		ft_write_char
#define IO_Write_String		ft_write_str
#define IO_Write_Line		ft_write_line
#define IO_Write_Lines		ft_write_strls
#define IO_Write_Memory		ft_write_memory

#define IO_Output_Char		ft_output_char
#define IO_Output_String	ft_output_str
#define IO_Output_Line		ft_output_line
#define IO_Output_Lines		ft_output_strls
#define IO_Output_Memory	ft_output_memory



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Define the 3 standard (std) streams of data - these numbers are special
**	file descriptors used to read from and write to the terminal commandline.
*/
# define STDIN	0
# define STDOUT	1
# define STDERR	2

/*
**	Define the return values for ft_GetNextLine().
*/
# define GNL_ERROR -1
# define GNL_LINE	1
# define GNL_END	0

/*
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
# define BUFF_SIZE 2048

/*
**	Define some useful string literals for commandline output colors.
**	May be used with any of the 'ft_output' and 'ft_write' functions.
*/
#ifndef __COLORS__
#define __COLORS__
#define C_RED		"\x1b[31m"
#define C_GREEN		"\x1b[32m"
#define C_YELLOW	"\x1b[33m"
#define C_BLUE		"\x1b[34m"
#define C_MAGENTA	"\x1b[35m"
#define C_CYAN		"\x1b[36m"
#define C_RESET		"\x1b[0m"
#endif



/*
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

/*
**	Reads the contents of the file descriptor 'fd', and puts it into 'file'.
**	Returns 0 if the stream was read successfully, 1 if there was an error.
*/
int		ft_readfile(int const fd, char **file, t_size max);

/*
**	Reads the contents of the file descriptor 'fd' line per line.
**	This means that it will allocate and fill a buffer until reading '\n',
**	at which point this buffer is returned via the 'line' char pointer arg.
**	Returns:
**		-1 if there's an error
**		1 if a line of characters was successfully read
**		0 if the end of the file was reached
*/
int		ft_getnextline(int const fd, char **line);

/*
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line.
**	The '\n' characters are replaced by '\0' string terminators.
**	Returns 0 if the stream was read successfully, 1 if there was an error.
*/
int		ft_readlines(int const fd, char ***strls);



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

/*
**	Writes the given character 'c' to the given file descriptor 'fd'.
*/
void	ft_write_char(int fd, char c);

/*
**	Writes the given string 'str' to the given file descriptor 'fd'.
*/
void	ft_write_str(int fd, char const *str);

/*
**	Writes the given string 'str' to the given file descriptor 'fd',
**	with a newline '\n' character at the end.
*/
void	ft_write_line(int fd, char const *str);

/*
**	Writes the given string array 'strls' to the given file descriptor 'fd'.
*/
void	ft_write_strls(int fd, char const **strls);

/*
**	Writes hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks to 'fd'.
*/
void	ft_write_memory(int fd, t_u8 const *ptr, t_size n, t_u8 cols);



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

/*
**	Writes the given char 'c' to the standard output.
*/
void	ft_output_char(char c);

/*
**	Writes the given string 'str' to the standard output.
*/
void	ft_output_str(char const *str);

/*
**	Writes the given string 'str' to the standard output,
**	with a newline '\n' character at the end.
*/
void	ft_output_line(char const *str);

/*
**	Writes the given string array 'strls' to the standard output.
*/
void	ft_output_strls(char const **strls);

/*
**	Outputs hexadecimal memory in the null-terminated string 'str',
**	writing lines of 'cols' columns of 4-byte chunks.
*/
void	ft_output_memory(t_u8 const *ptr, t_size n, t_u8 cols);

#endif
