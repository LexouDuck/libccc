/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/io.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_IO_H
#define __LIBCCC_SYS_IO_H
/*! @file libccc/sys/io.h
**	This header defines all the functions for OS-level input/output, read/write.
**	@addtogroup libccc/sys/io
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
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Arbitrary buffer size for libccc/sys/io functions
/*!
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
#define BUFF_SIZE	(2048)

//! File descriptor integer type for libccc/sys/io functions
/*!
** Define a type for file descriptors (which is usually the default machine 'int')
*/
typedef int		t_fd;
TYPEDEF_ALIAS(	t_fd, FILEDESC, PRIMITIVE)

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
**	May be used with any of the 'c_output' and 'c_write' functions.
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

// TODO make macros like this for every type of libccc, so that this header can act as doc on printf
/*
**	Cross-platform '%' format specifiers for printf()-family calls: String_Format(), IO_Write_Format(), etc
*/

#define FORMAT_ENUM	"%d"

// libccc/bool.h
#define FORMAT_BOOL	"%d"

// libccc/char.h
#define FORMAT_CHAR	"%c"
#define FORMAT_UTF8	"%c"

// libccc/int.h
#define FORMAT_S8		"%+i"
#define FORMAT_S16		"%+i"
#define FORMAT_S32		"%+i"
#define FORMAT_U8		"%0u"
#define FORMAT_U16		"%0u"
#define FORMAT_U32		"%0u"
#define FORMAT_HEX_U8	"%#X"
#define FORMAT_HEX_U16	"%#X"
#define FORMAT_HEX_U32	"%#X"
#if defined(__APPLE__) || defined(_WIN32)
	#define FORMAT_S64		"%+lli"
	#define FORMAT_U64		"%0llu"
	#define FORMAT_HEX_U64	"%#llX"
#else
	#define FORMAT_S64		"%+li"
	#define FORMAT_U64		"%0lu"
	#define FORMAT_HEX_U64	"%#lX"
#endif
#define FORMAT_S128		"%+lli"
#define FORMAT_U128		"%0llu"
#define FORMAT_HEX_U128	"%#llX"

#define FORMAT_SINT		CONCAT(FORMAT_S,	 LIBCONFIG_BITS_SINT)
#define FORMAT_UINT		CONCAT(FORMAT_U,	 LIBCONFIG_BITS_UINT)
#define FORMAT_HEX_UINT	CONCAT(FORMAT_HEX_U, LIBCONFIG_BITS_UINT)

// libccc/fixed.h
#define FORMAT_K16		"%0.8i"
#define FORMAT_K32		"%0.8i"
#define FORMAT_K64		"%0.8i"
#define FORMAT_K128		"%0.8i"
#define FORMAT_HEX_K16	"%#0.8X"
#define FORMAT_HEX_K32	"%#0.8X"
#define FORMAT_HEX_K64	"%#0.8X"
#define FORMAT_HEX_K128	"%#0.8X"

#define FORMAT_FIXED		"%0.8i"
#define FORMAT_HEX_FIXED	"%#0.8X"

// libccc/float.h
#define FORMAT_F32		"%#g"
#define FORMAT_F64		"%#g"
#define FORMAT_F80		"%#g"
#define FORMAT_F128		"%#g"
#define FORMAT_HEX_F32	"%#a"
#define FORMAT_HEX_F64	"%#a"
#define FORMAT_HEX_F80	"%#a"
#define FORMAT_HEX_F128	"%#a"

#define FORMAT_FLOAT		"%#g"
#define FORMAT_HEX_FLOAT	"%#g"

// libccc/pointer.h
#define FORMAT_PTR			FORMAT_POINTER
#define FORMAT_POINTER		"%#p"
#define FORMAT_SIZE			"%zu"
#define FORMAT_HEX_SIZE		"%#zx"
#define FORMAT_PTRDIFF		"%ti"
#define FORMAT_HEX_PTRDIFF	"%#tx"

// libccc/memory.h
#define FORMAT_MEM(N)		FORMAT_MEMORY(N)
#define FORMAT_MEMORY(N)	"%."#N"s"

// libccc/string.h
#define FORMAT_STR			FORMAT_STRING
#define FORMAT_STRING		"%s"

// libccc/color.h
#define FORMAT_COLOR_ARGB16	"#%X"
#define FORMAT_COLOR_ARGB32	"#%X"
#define FORMAT_COLOR_ARGB	"(A:%g, R:%g, G:%g, B:%g)"
#define FORMAT_COLOR_AHSL	"(A:%g, H:%g, S:%g, L:%g)"

// libccc/math/complex.h
#define FORMAT_COMPLEX	"(%g + %g*i)"

// libccc/math/algebra.h
#define FORMAT_VECTOR	"(%g)"
#define FORMAT_VECTOR2D	"(%g, %g)"
#define FORMAT_VECTOR3D	"(%g, %g, %g)"
#define FORMAT_VECTOR4D	"(%g, %g, %g, %g)"
#define FORMAT_MATRIX	FORMAT_VECTOR
#define FORMAT_MATRIX2D	FORMAT_VECTOR2D"\n"FORMAT_VECTOR2D"\n"
#define FORMAT_MATRIX3D	FORMAT_VECTOR3D"\n"FORMAT_VECTOR3D"\n"FORMAT_VECTOR3D"\n"
#define FORMAT_MATRIX4D	FORMAT_VECTOR4D"\n"FORMAT_VECTOR4D"\n"FORMAT_VECTOR4D"\n"FORMAT_VECTOR4D"\n"




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
**	@param	max		The maximum amount of bytes to read from 'fd'; if 0, replaced by (t_size)-1
**	@returns 0(OK) if the stream was read successfully, 1(ERROR) if there was an error.
*/
t_bool					IO_Read_File(t_fd const fd, char* *a_file, t_size max);
#define c_readfile		IO_Read_File

//! Reads the contents of 'fd' and makes an array of strings, one for each line
/*!
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line (each '\\n' newline char).
**	Each '\\n' character in the string are replaced by '\\0' string terminators.
**
**	@param	fd			The file descriptor to read data from
**	@param	a_strarr	The address of the string array to fill: the top-level
**						top-level pointer array is allocated and filled appropriately.
**	@returns 0(OK) if the stream was read successfully, 1(ERROR) if there was an error.
*/
t_bool					IO_Read_Lines(t_fd const fd, char** *a_strarr);
#define c_readlines		IO_Read_Lines

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
//TODO DO NOT USE, TODO FIX, confirmed to have very, very rare, platform-specific problems...
int						IO_Read_NextLine(t_fd const fd, char* *a_line);
#define c_getnextline	IO_Read_NextLine
#define GNL_LINE   1	//!< Return value for c_getnextline: indicates succesful line read, more to follow
#define GNL_END    0	//!< Return value for c_getnextline: indicates successful line read, end of file reached
#define GNL_ERROR -1	//!< Return value for c_getnextline: indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character 'c' to the given file descriptor 'fd'
int						IO_Write_Char(t_fd fd, char c);
#define c_write_char	IO_Write_Char

//! Writes the given string 'str' to the given file descriptor 'fd'
int						IO_Write_String(t_fd fd, char const* str);
#define c_write_string	IO_Write_String

//! Writes the given string 'str' to the given file descriptor 'fd', and a newline '\n' char at the end
int						IO_Write_Line(t_fd fd, char const* str);
#define c_write_line	IO_Write_Line

//! Writes the given string array 'strarr' to the given file descriptor 'fd'
int						IO_Write_Lines(t_fd fd, char const** strarr);
#define c_write_lines	IO_Write_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the given file descriptor 'fd'
int						IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);
#define c_write_memory	IO_Write_Memory

//! Writes the given formatted string to the standard output - equivalent to 'fprintf()', or rather 'dprintf()'
_FORMAT(printf, 2, 3)
int						IO_Write_Format(t_fd fd, char const* format, ...);
#define c_write_format	IO_Write_Format
#define c_dprintf		IO_Write_Format



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char 'c' to the standard output.
int							IO_Output_Char(char c);
#define c_output_char		IO_Output_Char
#define c_putchar			IO_Output_Char

//! Writes the given string 'str' to the standard output.
int							IO_Output_String(char const* str);
#define c_output_string		IO_Output_String
#define c_putstr			IO_Output_String

//! Writes the given string 'str' to the standard output, with a newline '\n' character at the end.
int							IO_Output_Line(char const* str);
#define c_output_line		IO_Output_Line
#define c_putline			IO_Output_Line

//! Writes the given string array 'strls' to the standard output.
int							IO_Output_Lines(char const** strarr);
#define c_output_lines		IO_Output_Lines
#define c_putlines			IO_Output_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the standard output
int							IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);
#define c_output_memory		IO_Output_Memory
#define c_putmem			IO_Output_Memory

//! Writes the given formatted string to the standard output - equivalent to 'printf()'
_FORMAT(printf, 1, 2)
int							IO_Output_Format(char const* format, ...);
#define c_output_format		IO_Output_Format
#define c_printf			IO_Output_Format



/*! @} */
HEADER_END
#endif
