/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_io.h                              |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBFT_IO_H
#define __LIBFT_IO_H
/*! @file libft_io.h
**	This header defines all the functions for OS-level input/output, read/write.
**	@addtogroup libft_io
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

//! Arbitrary buffer size for libft_io functions
/*!
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
#define BUFF_SIZE	(2048)

//! File descriptor integer type for libft_io functions
/*!
** Define a type for file descriptors (which is usually the default machine 'int')
*/
typedef int		t_fd;

/*!
**	@def STDIN
**	@def STDOUT
**	@def STDERR
**	Define the 3 standard (std) streams of data - these numbers are special
**	file descriptors used to read from and write to the terminal commandline.
*/
#define STDIN	((t_fd)0)	//!< Special file descriptor (0), refers to terminal input stream
#define STDOUT	((t_fd)1)	//!< Special file descriptor (1), refers to terminal output stream
#define STDERR	((t_fd)2)	//!< Special file descriptor (2), refers to terminal error stream

/*!
**	Define some useful string literals for commandline output colors.
**	May be used with any of the 'ft_output' and 'ft_write' functions.
*/
#ifndef __COLORS__
#define __COLORS__
#define C_RED		"\x1b[31m"	//!< The string sequence to color the terminal text output red
#define C_GREEN		"\x1b[32m"	//!< The string sequence to color the terminal text output green
#define C_YELLOW	"\x1b[33m"	//!< The string sequence to color the terminal text output yellow
#define C_BLUE		"\x1b[34m"	//!< The string sequence to color the terminal text output blue
#define C_MAGENTA	"\x1b[35m"	//!< The string sequence to color the terminal text output magenta
#define C_CYAN		"\x1b[36m"	//!< The string sequence to color the terminal text output cyan
#define C_RESET		"\x1b[0m"	//!< The string sequence to reset the terminal text output to its default color
#endif

/*
**	Cross-platform '%' Format specifiers for printf calls
*/
#ifdef __APPLE__
	#define PRINTF_S64	"%lld"
	#define PRINTF_U64	"%llu"
#else
	#define PRINTF_S64	"%ld"
	#define PRINTF_U64	"%lu"
#endif
#define PRINTF_SIZE		"%zu"
#define PRINTF_PTRDIFF	"%ti"

#ifdef _INT_64_
	#define PRINTF_W12_INT	"%12ld"
#else
	#define PRINTF_W12_INT	"%12d"
#endif

#ifdef _UINT_64_
	#define PRINTF_W12_UINT	"%12lu"
#else
	#define PRINTF_W12_UINT	"%12u"
#endif



/*
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

//! Reads the contents of 'fd' and fill a data buffer with those bytes
/*!
**	Reads the full contents of the file descriptor 'fd', and puts it into 'a_file'.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_file	The address of the buffer to fill: is allocated and filled with the data
**	@param	max		The maximum amount of bytes to read from 'fd'
**	@return OK(0) if the stream was read successfully, ERROR(1) if there was an error.
*/
t_bool					IO_Read_File(t_fd const fd, char* *a_file, t_size max);
#define ft_readfile		IO_Read_File

//! Reads the contents of 'fd' and makes an array of strings, one for each line
/*!
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line (each '\\n' newline char).
**	Each '\\n' character in the string are replaced by '\\0' string terminators.
**
**	@param	fd			The file descriptor to read data from
**	@param	a_strarr	The address of the string array to fill: the top-level
**						top-level pointer array is allocated and filled appropriately.
**	@return OK(0) if the stream was read successfully, ERROR(1) if there was an error.
*/
t_bool					IO_Read_Lines(t_fd const fd, char** *a_strarr);
#define ft_readlines	IO_Read_Lines

//! Reads the contents of the file descriptor 'fd' line-per-line.
/*!
**	This function will read 'fd' line-per-line as you call it repeatedly.
**	This means that it will allocate and fill a buffer until reading '\\n',
**	at which point this buffer is returned via the 'line' char pointer arg.
**	As such, this function will typically be called within a while loop.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_line	The address of the string to allocate and fill with the current line.
**	@return
**		- 1 if a line of characters was successfully read
**		- 0 if the end of the file was reached
**		- -1 if there's an error
*/
int						IO_Read_NextLine(t_fd const fd, char* *a_line);
#define ft_getnextline	IO_Read_NextLine
#define GNL_LINE   1	//!< Return value for ft_getnextline: indicates succesful line read, more to follow
#define GNL_END    0	//!< Return value for ft_getnextline: indicates successful line read, end of file reached
#define GNL_ERROR -1	//!< Return value for ft_getnextline: indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character 'c' to the given file descriptor 'fd'
int						IO_Write_Char(t_fd fd, char c);
#define ft_write_char	IO_Write_Char

//! Writes the given string 'str' to the given file descriptor 'fd'
int						IO_Write_String(t_fd fd, char const* str);
#define ft_write_string	IO_Write_String

//! Writes the given string 'str' to the given file descriptor 'fd', and a newline '\n' char at the end
int						IO_Write_Line(t_fd fd, char const* str);
#define ft_write_line	IO_Write_Line

//! Writes the given string array 'strarr' to the given file descriptor 'fd'
int						IO_Write_Lines(t_fd fd, char const** strarr);
#define ft_write_lines	IO_Write_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the given file descriptor 'fd'
int						IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);
#define ft_write_memory	IO_Write_Memory

//! Writes the given formatted string to the standard output - equivalent to 'fprintf()', or rather 'dprintf()'
int						IO_Write_Format(t_fd fd, char const* format, ...);
#define ft_write_format	IO_Write_Format
#define ft_dprintf		IO_Write_Format



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char 'c' to the standard output.
int							IO_Output_Char(char c);
#define ft_output_char		IO_Output_Char
#define ft_putchar			IO_Output_Char

//! Writes the given string 'str' to the standard output.
int							IO_Output_String(char const* str);
#define ft_output_string	IO_Output_String
#define ft_putstr			IO_Output_String

//! Writes the given string 'str' to the standard output, with a newline '\n' character at the end.
int							IO_Output_Line(char const* str);
#define ft_output_line		IO_Output_Line
#define ft_putline			IO_Output_Line

//! Writes the given string array 'strls' to the standard output.
int							IO_Output_Lines(char const** strarr);
#define ft_output_lines		IO_Output_Lines
#define ft_putlines			IO_Output_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the standard output
int							IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);
#define ft_output_memory	IO_Output_Memory
#define ft_putmem			IO_Output_Memory

//! Writes the given formatted string to the standard output - equivalent to 'printf()'
int							IO_Output_Format(char const* format, ...);
#define ft_output_format	IO_Output_Format
#define ft_printf			IO_Output_Format



/*! @} */
HEADER_END
#endif
