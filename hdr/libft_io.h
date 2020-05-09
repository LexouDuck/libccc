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

#include <unistd.h>

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define FT_Read_File(fd, file, max)		ft_readfile(fd, file, max)
#define FT_Read_NextLine(fd, line)		ft_getnextline(fd, line)
#define FT_Read_Lines(fd, strls)		ft_readlines(fd, strls)

#define FT_Write_Char(fd, c)			ft_write_char(fd, c)
#define FT_Write_String(fd, str)		ft_write_str(fd, str)
#define FT_Write_Line(fd, str)			ft_write_line(fd, str)
#define FT_Write_Lines(fd, strls)		ft_write_strls(fd, strls)
#define FT_Write_Memory(fd, ptr, cols)	ft_write_memory(fd, ptr, cols)

#define FT_Output_Char(c)				ft_output_char(c)
#define FT_Output_String(str)			ft_output_str(str)
#define FT_Output_Line(str)				ft_output_line(str)
#define FT_Output_Lines(strls)			ft_output_strls(strls)
#define FT_Output_Memory(ptr, cols)		ft_output_memory(ptr, cols)



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
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

/*
**	Reads the contents of the file descriptor 'fd', and puts it into 'file'.
**	Returns 0 if the stream was read successfully, 1 if there was an error.
*/
int		ft_readfile(int const fd, char **file, size_t max);

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
void	ft_write_memory(int fd, t_u8 const *ptr, size_t n, t_u8 cols);



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
void	ft_output_memory(t_u8 const *ptr, size_t n, t_u8 cols);

#endif
