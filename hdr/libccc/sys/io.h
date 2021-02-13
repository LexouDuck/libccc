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

#include <fcntl.h>

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



//! This type represents a file access permissions bitflag value (like you would use with chmod)
typedef unsigned int	t_io_mode;
TYPEDEF_ALIAS(			t_io_mode, IO_MODE, PRIMITIVE)

/*
**	Access permissions bitflag (user/group/other and read/write/execute), used with the t_accessmode type
*/
#define MODE_USER_RWX	0700	//!< S_IRWXU - User (file owner) has read, write, and execute permission
#define MODE_USER_R		0400	//!< S_IRUSR - User has read permission
#define MODE_USER_W		0200	//!< S_IWUSR - User has write permission
#define MODE_USER_X		0100	//!< S_IXUSR - User has execute permission

#define MODE_GROUP_RWX	0070	//!< S_IRWXG - Group has read, write, and execute permission
#define MODE_GROUP_R	0040	//!< S_IRGRP - Group has read permission
#define MODE_GROUP_W	0020	//!< S_IWGRP - Group has write permission
#define MODE_GROUP_X	0010	//!< S_IXGRP - Group has execute permission

#define MODE_OTHER_RWX	0007	//!< S_IRWXO - Others have read, write, and execute permission
#define MODE_OTHER_R	0004	//!< S_IROTH - Others have read permission
#define MODE_OTHER_W	0002	//!< S_IWOTH - Others have write permission
#define MODE_OTHER_X	0001	//!< S_IXOTH - Others have execute permission



//! This type represents the bitflag value which handles options for the open() function
typedef unsigned int	t_io_open;
TYPEDEF_ALIAS(			t_io_open, IO_OPEN, PRIMITIVE)

// 1) file access modes
#define OPEN_READONLY	O_RDONLY	//!< Open the file for read access.
#define OPEN_WRITEONLY	O_WRONLY	//!< Open the file for write access.
#define OPEN_READWRITE	O_RDWR		//!< Open the file for both reading and writing.
#define OPEN_ACCESSMODE	O_ACCMODE	//!< The full bitmask value for the file access mode 'io_mode' portion within the 'io_open' int

// 2) open-time flags
#define OPEN_CREATE		O_CREAT	//!< If set, the file will be created if it doesn’t already exist.
#define OPEN_CLEARFILE	O_TRUNC	//!< If writing is allowed (ie: O_RDWR or O_WRONLY) then remove all contents of the file upon opening
#define OPEN_EXCLUSIVE	O_EXCL	//!< If both O_CREAT and O_EXCL are set, then open fails if the specified file already exists. (otherwise, platform-specific)
//#define OPEN_NOSYMLINK	O_NOFOLLOW	//! If set, the open operation fails if the final component of the file name refers to a symbolic link.
//#define OPEN_SYMLINK	O_NOLINK	//!< If the named file is a symbolic link, open the link itself instead of the file it refers to.
//#define OPEN_TEMPFILE	O_TMPFILE	//!< (GNU ext) If set, functions in the open family create an unnamed temporary file (must have write access, 'path' arg is the folder to put the temp file in)

// 3) operating modes
#define OPEN_APPEND		O_APPEND	//!< If set, then all write operations append the data at the end of the file, regardless of the current file position.
//#define OPEN_NONBLOCK	O_NONBLOCK	//!< If set, read/write requests on the file can return immediately with a failure status, instead of blocking, if nothing can be done.
//#define OPEN_ASYNC	O_ASYNC		//!< (BSD only) If set, then SIGIO signals will be generated when input is available.
//#define OPEN_FSYNC	O_FSYNC		//!< (BSD only) If set, each write call will make sure the data is reliably stored on disk before returning.
//#define OPEN_NOTIME	O_NOATIME	//!< (GNU ext) If set, read will not update the access time of the file. (only the file owner or sudo can use this)



/*!
**	Define some useful string literals for commandline output colors.
**	Can be used with any of the 'IO_Output_*' and 'IO_Write_*' functions.
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
** ************************************************************************** *|
**                              File IO Functions                             *|
** ************************************************************************** *|
*/

//! Opens the file at 'filepath', with the given file open 'flags', and the given file access 'mode' permissions
/*!
**	SYSCALL wrapper:
**		int	open(const char *pathname, int flags, mode_t mode);
**
**	@param	filepath	The path of the file to open
**	@param	flags		The flags with which to open the file (bitflag, can or bitwise OR'd, for example: `OPEN_READONLY|OPEN_CREATE`)
**	@param	mode		The file access mode (permissions) with which to open the file
**	@returns the new file descriptor value for the opened file, or -1 if an error occured (sets 'errno' appropriately)
*/
t_fd					IO_Open(char const* filepath, t_io_open flags, t_io_mode mode);
#define c_open			IO_Open
#define IO_File_Open	IO_Open

//! Closes the given file descriptor 'fd', so that it no longer refers to any file, and may be reused.
/*!
**	SYSCALL wrapper:
**		int close(int fd);
**
**	@param	fd	The file descriptor to close
**	@returns 0 on success, or -1 if an error occured (sets 'errno' appropriately)
*/
int						IO_Close(t_fd fd);
#define c_close			IO_Close
#define IO_File_Close	IO_Close



//! Changes the file access mode permissions for the file at 'filepath' to the new value 'mode'
/*!
**	SYSCALL wrapper:
**		int chmod(const char *pathname, mode_t mode);
**
**	@param	filepath	The path of the file whose access permissions should change
**	@param	mode		The new file access mode permissions bitflag value to set
**	@returns 0 on success, or -1 if an error occured (sets 'errno' appropriately)
*/
int							IO_ChangeMode(char const* filepath, t_io_mode mode);
#define c_chmod				IO_ChangeMode
#define IO_File_ChangeMode	IO_ChangeMode

//! Changes the owner and group for the file at 'filepath'
/*!
**	SYSCALL wrapper:
**		int chown(const char *pathname, uid_t owner, gid_t group);
**
**	@param	filepath	The path of the file whose owner/group should change
**	@param	owner		The new owner to set for the file
**	@param	group		The new group to set for the file
**	@returns 0 on success, or -1 if an error occured (sets 'errno' appropriately)
*/
/* TODO find a way to make this as cross-platform as possible
int							IO_ChangeOwner(char const* filepath, char const* owner, char const* group);
#define c_chown				IO_ChangeOwner
#define IO_File_ChangeOwner	IO_ChangeOwner
*/



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
