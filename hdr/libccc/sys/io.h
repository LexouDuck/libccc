/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/io.h	                         |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_IO_H
#define __LIBCCC_SYS_IO_H
/*!@group{libccc_sys_io}
** @{
**	This header defines all the functions for OS-level input/output, read/write.
**
**	@isostd{C,https://en.cppreference.com/w/c/io}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <fcntl.h>
#else
	#define O_RDONLY    0 // TODO find platform-specific value
	#define O_WRONLY    0 // TODO find platform-specific value
	#define O_RDWR      0 // TODO find platform-specific value
	#define O_EXEC      0 // TODO find platform-specific value
	#define O_ACCMODE   0 // TODO find platform-specific value
	#define O_CREAT     0 // TODO find platform-specific value
	#define O_TRUNC     0 // TODO find platform-specific value
	#define O_EXCL      0 // TODO find platform-specific value
	#define O_NOFOLLOW  0 // TODO find platform-specific value
	#define O_NOLINK    0 // TODO find platform-specific value
	#define O_TMPFILE   0 // TODO find platform-specific value
	#define O_APPEND    0 // TODO find platform-specific value
	#define O_NONBLOCK  0 // TODO find platform-specific value
	#define O_ASYNC     0 // TODO find platform-specific value
	#define O_FSYNC     0 // TODO find platform-specific value
	#define O_NOATIME   0 // TODO find platform-specific value
	#define O_BINARY    0 // TODO find platform-specific value
	#define O_TEST      0 // TODO find platform-specific value
#endif

#include "libccc.h"
#include "libccc/color.h"
#include "libccc/sys/ansi.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! File descriptor integer type for libccc/sys/io functions
/*!
**	Define a type for file descriptors (which is usually the default machine 'int')
*/
typedef int		t_fd;
TYPEDEF_ALIAS(	t_fd, FILEDESC, PRIMITIVE)

/*!
**	@def STDIN
**	@def STDOUT
**	@def STDERR
**	@isostd{C,https://en.cppreference.com/w/c/io/std_streams}
**
**	Define the 3 standard (std) streams of data - these numbers are special
**	file descriptors used to read from and write to the terminal commandline.
*/
#define STDIN	((t_fd)0)	//!< Special file descriptor (0), refers to the standard input stream
#define STDOUT	((t_fd)1)	//!< Special file descriptor (1), refers to the standard output stream
#define STDERR	((t_fd)2)	//!< Special file descriptor (2), refers to the standard error stream



//! Arbitrary buffer size for libccc/sys/io functions
/*!
**	This is the arbitrary buffer size to be used by the reading functions.
**	Raising this amount will lower the amount of function calls made to
**	the 'read' function from unistd.h, resulting in possible speed improvments,
**	depending on the amount of files to read, and their filesizes.
**	It is also recommended to have this number be a power of 2, as it can be
**	occasionally faster to manage arrays of such sizes on certain machines.
*/
#define IO_BUFFER_SIZE	(2048)



//! This type represents a file access permissions bitflag value (like you would use with chmod)
typedef unsigned int	t_io_mode;
TYPEDEF_ALIAS(			t_io_mode, IO_MODE, PRIMITIVE)

/*!
**	Access permissions bitflag (user/group/other and read/write/execute), used with the `t_io_mode` type
*/
//!@{
#define ACCESSMODE_USER_RWX		0700	//!< S_IRWXU - User (file owner) has read, write, and execute permission
#define ACCESSMODE_USER_R		0400	//!< S_IRUSR - User has read permission
#define ACCESSMODE_USER_W		0200	//!< S_IWUSR - User has write permission
#define ACCESSMODE_USER_X		0100	//!< S_IXUSR - User has execute permission

#define ACCESSMODE_GROUP_RWX	0070	//!< S_IRWXG - Group has read, write, and execute permission
#define ACCESSMODE_GROUP_R		0040	//!< S_IRGRP - Group has read permission
#define ACCESSMODE_GROUP_W		0020	//!< S_IWGRP - Group has write permission
#define ACCESSMODE_GROUP_X		0010	//!< S_IXGRP - Group has execute permission

#define ACCESSMODE_OTHER_RWX	0007	//!< S_IRWXO - Others have read, write, and execute permission
#define ACCESSMODE_OTHER_R		0004	//!< S_IROTH - Others have read permission
#define ACCESSMODE_OTHER_W		0002	//!< S_IWOTH - Others have write permission
#define ACCESSMODE_OTHER_X		0001	//!< S_IXOTH - Others have execute permission
//!@}



//! This type represents the bitflag value which handles options for the open() function
typedef unsigned int	t_io_open;
TYPEDEF_ALIAS(			t_io_open, IO_OPEN, PRIMITIVE)

/*!
**	Options for opening a file, used with the `t_io_open` type
*/
//!@{
// 1) file access modes
#define OPEN_READONLY	O_RDONLY	//!< Open the file for read access.
#define OPEN_WRITEONLY	O_WRONLY	//!< Open the file for write access.
#define OPEN_READWRITE	O_RDWR		//!< Open the file for both reading and writing.
#define OPEN_ACCESSMODE	O_ACCMODE	//!< The full bitmask value for the file access mode 'io_mode' portion within the 'io_open' int
// 2) open-time flags
#define OPEN_CREATE		O_CREAT		//!< If set, the file will be created if it doesn’t already exist.
#define OPEN_CLEARFILE	O_TRUNC		//!< If writing is allowed (ie: O_RDWR or O_WRONLY) then remove all contents of the file upon opening
#define OPEN_NOEXISTING	O_EXCL		//!< If both O_CREAT and O_EXCL are set, then open fails if the specified file already exists. (otherwise, platform-specific)
//#define OPEN_NOSYMLINK	O_NOFOLLOW	//!< If set, the open operation fails if the final component of the file name refers to a symbolic link.
//#define OPEN_SYMLINK	O_NOLINK	//!< If the named file is a symbolic link, open the link itself instead of the file it refers to.
//#define OPEN_TEMPFILE	O_TMPFILE	//!< (GNU ext) If set, functions in the open family create an unnamed temporary file (must have write access, 'path' arg is the folder to put the temp file in)
// 3) operating modes
#define OPEN_APPEND		O_APPEND	//!< If set, then all write operations append the data at the end of the file, regardless of the current file position.
//#define OPEN_NONBLOCK	O_NONBLOCK	//!< If set, read/write requests on the file can return immediately with a failure status, instead of blocking, if nothing can be done.
//#define OPEN_ASYNC	O_ASYNC		//!< (BSD only) If set, then SIGIO signals will be generated when input is available.
//#define OPEN_FSYNC	O_FSYNC		//!< (BSD only) If set, each write call will make sure the data is reliably stored on disk before returning.
//#define OPEN_NOTIME	O_NOATIME	//!< (GNU ext) If set, read will not update the access time of the file. (only the file owner or sudo can use this)
//!@}



#ifndef __LIBCCC_NOFUNCTIONS__

/*
** ************************************************************************** *|
**                             General IO Functions                           *|
** ************************************************************************** *|
*/

//! Get the ANSI color code number for the nearest color to the given 32-bit `color`.
/*!
**	(Learn more about ANSI colors)[https://misc.flogisoft.com/bash/tip_colors_and_formatting]
*/
t_u8						IO_GetColor(t_argb32 color);
#define c_io_getcolor		IO_GetColor
#define IO_GetANSIColor		IO_GetColor



//! Checks whether the given file descriptor `fd` points to a terminal.
/*!
**	@returns
**	`TRUE` if the given file descriptor `fd` corresponds to a terminal,
**	otherwise `FALSE`.
*/
t_bool						IO_IsTerminal(t_fd fd);
#define c_isatty			IO_IsTerminal
#define IO_File_IsTerminal	IO_IsTerminal



/*
** ************************************************************************** *|
**                              File IO Functions                             *|
** ************************************************************************** *|
*/

//! Opens the file at 'filepath', with the given file open 'flags', and the given file access 'mode' permissions
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/open}
**
**	@param	filepath	The path of the file to open
**	@param	flags		The flags with which to open the file (bitflag, can be bitwise OR'd, ie: `(OPEN_READONLY|OPEN_CREATE)`)
**	@param	mode		The file access mode (permissions) with which to open the file
**	@returns
**	The new file descriptor value for the opened file,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
t_fd					IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode);
#define c_open			IO_Open
#define IO_File_Open	IO_Open

//! Closes the given file descriptor 'fd', so that it no longer refers to any file, and may be reused.
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/close}
**
**	@param	fd	The file descriptor to close
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
e_cccerror				IO_Close(t_fd fd);
#define c_close			IO_Close
#define IO_File_Close	IO_Close

//! Changes the file access mode permissions for the file at 'filepath' to the new value 'mode'
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/chmod}
**
**	@param	filepath	The path of the file whose access permissions should change
**	@param	mode		The new file access mode permissions bitflag value to set
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
e_cccerror					IO_ChangeMode(t_char const* filepath, t_io_mode mode);
#define c_chmod				IO_ChangeMode
#define IO_File_ChangeMode	IO_ChangeMode

// TODO find a way to make this as cross-platform as possible
#if 0
//! Changes the owner and group for the file at 'filepath'
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/chown}
**
**	@param	filepath	The path of the file whose owner/group should change
**	@param	owner		The new owner to set for the file
**	@param	group		The new group to set for the file
**	@returns
**	`0`(#OK) if the function completed successfully,
**	otherwise a non-zero error code (ie: an `errno` value)
*/
e_cccerror					IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group);
#define c_chown				IO_ChangeOwner
#define IO_File_ChangeOwner	IO_ChangeOwner
#endif



// TODO wrapper for tmpfile() @isostd{C,https://en.cppreference.com/w/c/io/tmpfile}



/*
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

//! Reads the contents of the given `fd` and fill a data buffer with those bytes
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/read}
**
**	Reads the full contents of the file descriptor `fd` (ie, until read() returns 0),
**	and allocates a memory region which stores the file contents in `*a_file`.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_file	The address of the buffer to fill: is allocated and filled with the data
**	@param	max		The maximum amount of bytes to read from 'fd' (if 0, replaced by `(t_size)-1`)
**	@returns
**	The amount of bytes read from the given file descriptor `fd` in total.
**	If the return value is a negative number, there was a read error:
**	You should then check `errno`, and/or use `IO_GetError(errno)` immediately after.
*/
t_sintmax				IO_Read_File(t_fd const fd, t_char* *a_file, t_size max);
#define c_readfile		IO_Read_File

//! Reads the contents of `fd` and makes an array of strings, one for each line
/*!
**	@nonstd
**
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line (each '\\n' newline char).
**	Each '\\n' character in the string are replaced by '\\0' string terminators.
**	NB: If the file being read contains any '\\0' chars, the string array will end there.
**
**	@param	fd			The file descriptor to read data from
**	@param	a_strarr	The address of the string array to fill: the top-level
**						top-level pointer array is allocated and filled appropriately.
**	@returns
**	The amount of bytes read from the given file descriptor `fd` in total.
**	If the return value is a negative number, there was a read error:
**	You should then check `errno`, and/or use `IO_GetError(errno)` immediately after.
*/
t_sintmax				IO_Read_Lines(t_fd const fd, t_char** *a_strarr);
#define c_readlines		IO_Read_Lines

//! Reads the contents of the file descriptor `fd` line-per-line.
/*!
**	@nonstd
**
**	This function will read `fd` line-per-line as you call it repeatedly.
**	This means that it will allocate and fill a buffer until reading `'\n'`,
**	at which point this buffer is returned via the `line` char pointer arg.
**	As such, this function will typically be called within a while loop.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_line	The address of the string to allocate and fill with the current line.
**	@returns
**	- `+1` (`GNL_LINE`) 	if a line of characters was successfully read
**	- `0`  (`GNL_END`)  	if the end of the file was reached
**	- `-1` (`GNL_ERROR`)	if there's an error
*/
//TODO DO NOT USE, TODO FIX, confirmed to have very, very rare, platform-specific problems...
int						IO_Read_NextLine(t_fd const fd, t_char* *a_line);
#define c_getline		IO_Read_NextLine
#define c_getnextline	IO_Read_NextLine
#define c_readnextline	IO_Read_NextLine

#define GNL_LINE  +1	//!< Return value for IO_Read_NextLine(): indicates succesful line read, more to follow
#define GNL_END    0	//!< Return value for IO_Read_NextLine(): indicates successful line read, end of file reached
#define GNL_ERROR -1	//!< Return value for IO_Read_NextLine(): indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character `c` to the given file descriptor `fd`
/*!
**	@nonstd
*/
t_size					IO_Write_Char(t_fd fd, t_char c);
#define c_write_char	IO_Write_Char

//! Writes the given string `str` to the given file descriptor `fd`
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/write}
*/
t_size					IO_Write_String(t_fd fd, t_char const* str);
#define c_write_string	IO_Write_String

//! Writes the given string `str` to the given file descriptor `fd`, and a newline `'\n'` char at the end
/*!
**	@nonstd
*/
t_size					IO_Write_Line(t_fd fd, t_char const* str);
#define c_write_line	IO_Write_Line

//! Writes the given string array `strarr` to the given file descriptor `fd`
/*!
**	@nonstd
*/
t_size					IO_Write_Lines(t_fd fd, t_char const** strarr);
#define c_write_lines	IO_Write_Lines

//!< Writes 'n' bytes of memory from `ptr` as hexadecimal 2-char blocks in `cols` columns, to the given file descriptor `fd`
/*!
**	@nonstd
*/
t_size					IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);
#define c_write_memory	IO_Write_Memory

//! Writes the given formatted string to the standard output - equivalent to `dprintf()`
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/dprintf}
*/
_FORMAT(printf, 2, 3)
t_size					IO_Write_Format(t_fd fd, t_char const* format, ...);
#define c_write_format	IO_Write_Format
#define c_dprintf		IO_Write_Format



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char `c` to the standard output.
/*!
**	@nonstd
*/
t_size					IO_Output_Char(t_char c);
#define c_output_char	IO_Output_Char
#define c_putchar		IO_Output_Char

//! Writes the given string `str` to the standard output.
/*!
**	@nonstd
*/
t_size					IO_Output_String(t_char const* str);
#define c_output_string	IO_Output_String
#define c_putstr		IO_Output_String

//! Writes the given string `str` to the standard output, with a newline `'\n'` character at the end.
/*!
**	@nonstd
*/
t_size					IO_Output_Line(t_char const* str);
#define c_output_line	IO_Output_Line
#define c_putline		IO_Output_Line

//! Writes the given string array `strls` to the standard output.
/*!
**	@nonstd
*/
t_size					IO_Output_Lines(t_char const** strarr);
#define c_output_lines	IO_Output_Lines
#define c_putlines		IO_Output_Lines

//!< Writes 'n' bytes of memory from `ptr` as hexadecimal 2-char blocks in `cols` columns, to the standard output
/*!
**	@nonstd
*/
t_size					IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);
#define c_output_memory	IO_Output_Memory
#define c_putmem		IO_Output_Memory

//! Writes the given formatted string to the standard output - equivalent to `printf()`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/io/printf}
*/
_FORMAT(printf, 1, 2)
t_size					IO_Output_Format(t_char const* format, ...);
#define c_output_format	IO_Output_Format
#define c_printf		IO_Output_Format



#endif



/*! @} */
HEADER_END
#endif
