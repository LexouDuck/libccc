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
**	@isostd{https://en.cppreference.com/w/c/io}
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
	// TODO O_* macros for open() ?
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
**	@isostd{https://en.cppreference.com/w/c/io/std_streams}
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



//! This type represents an error code for a system call IO function (ie: a value for the 'errno' global variable)
/*!
**	@isostd{https://en.cppreference.com/w/c/error/errno}
**	@isostd{https://en.cppreference.com/w/c/error/errno_macros}
*/
typedef int				t_io_error;
TYPEDEF_ALIAS(			t_io_error, IO_ERROR, PRIMITIVE)



//! This type represents a file access permissions bitflag value (like you would use with chmod)
typedef unsigned int	t_io_mode;
TYPEDEF_ALIAS(			t_io_mode, IO_MODE, PRIMITIVE)

/*
**	Access permissions bitflag (user/group/other and read/write/execute), used with the t_accessmode type
*/
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
#define OPEN_NOEXISTING	O_EXCL	//!< If both O_CREAT and O_EXCL are set, then open fails if the specified file already exists. (otherwise, platform-specific)
//#define OPEN_NOSYMLINK	O_NOFOLLOW	//!< If set, the open operation fails if the final component of the file name refers to a symbolic link.
//#define OPEN_SYMLINK	O_NOLINK	//!< If the named file is a symbolic link, open the link itself instead of the file it refers to.
//#define OPEN_TEMPFILE	O_TMPFILE	//!< (GNU ext) If set, functions in the open family create an unnamed temporary file (must have write access, 'path' arg is the folder to put the temp file in)

// 3) operating modes
#define OPEN_APPEND		O_APPEND	//!< If set, then all write operations append the data at the end of the file, regardless of the current file position.
//#define OPEN_NONBLOCK	O_NONBLOCK	//!< If set, read/write requests on the file can return immediately with a failure status, instead of blocking, if nothing can be done.
//#define OPEN_ASYNC	O_ASYNC		//!< (BSD only) If set, then SIGIO signals will be generated when input is available.
//#define OPEN_FSYNC	O_FSYNC		//!< (BSD only) If set, each write call will make sure the data is reliably stored on disk before returning.
//#define OPEN_NOTIME	O_NOATIME	//!< (GNU ext) If set, read will not update the access time of the file. (only the file owner or sudo can use this)



/*
** ************************************************************************** *|
**                             General IO Functions                           *|
** ************************************************************************** *|
*/

//! Returns the error message corresponding to the given 'errno' error number.
/*!
**	This is equivalent to the STD C strerror(), strerror_r() functions.
**
**	@returns A newly allocated string which contains the system IO error message.
*/
t_char*						IO_GetError(int error_num);
#define c_strerror			IO_GetError
#define c_strerror_r		IO_GetError
#define IO_GetErrorMessage	IO_GetError



//! Returns the ANSI color code number for the nearest color to the given 32-bit `color`.
/*!
**	(Learn more about ANSI colors)[https://misc.flogisoft.com/bash/tip_colors_and_formatting]
*/
t_u8						IO_GetColor(t_argb32 color);
#define c_io_getcolor		IO_GetColor
#define IO_GetANSIColor		IO_GetColor



//! Returns 1(TRUE) if the given file descriptor `fd` corresponds to a terminal.
/*!
**	
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
**	SYSCALL wrapper:
**		int	open(const char *pathname, int flags, mode_t mode);
**
**	@param	filepath	The path of the file to open
**	@param	flags		The flags with which to open the file (bitflag, can or bitwise OR'd, for example: `OPEN_READONLY|OPEN_CREATE`)
**	@param	mode		The file access mode (permissions) with which to open the file
**	@returns the new file descriptor value for the opened file, or a non-zero error code (ie: an 'errno' value)
*/
t_fd					IO_Open(t_char const* filepath, t_io_open flags, t_io_mode mode);
#define c_open			IO_Open
#define IO_File_Open	IO_Open

//! Closes the given file descriptor 'fd', so that it no longer refers to any file, and may be reused.
/*!
**	SYSCALL wrapper:
**		int close(int fd);
**
**	@param	fd	The file descriptor to close
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error				IO_Close(t_fd fd);
#define c_close			IO_Close
#define IO_File_Close	IO_Close

//! Changes the file access mode permissions for the file at 'filepath' to the new value 'mode'
/*!
**	SYSCALL wrapper:
**		int chmod(const char *pathname, mode_t mode);
**
**	@param	filepath	The path of the file whose access permissions should change
**	@param	mode		The new file access mode permissions bitflag value to set
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error					IO_ChangeMode(t_char const* filepath, t_io_mode mode);
#define c_chmod				IO_ChangeMode
#define IO_File_ChangeMode	IO_ChangeMode

// TODO find a way to make this as cross-platform as possible
#if 0
//! Changes the owner and group for the file at 'filepath'
/*!
**	SYSCALL wrapper:
**		int chown(const char *pathname, uid_t owner, gid_t group);
**
**	@param	filepath	The path of the file whose owner/group should change
**	@param	owner		The new owner to set for the file
**	@param	group		The new group to set for the file
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error					IO_ChangeOwner(t_char const* filepath, t_char const* owner, t_char const* group);
#define c_chown				IO_ChangeOwner
#define IO_File_ChangeOwner	IO_ChangeOwner
#endif



// TODO wrapper for tmpfile() @isostd{https://en.cppreference.com/w/c/io/tmpfile}



/*
** ************************************************************************** *|
**                              Reading Functions                             *|
** ************************************************************************** *|
*/

//! Reads the contents of 'fd' and fill a data buffer with those bytes
/*!
**	SYSCALL wrapper:
**		int	read(const char *pathname, int flags, mode_t mode);
**
**	Reads the full contents of the file descriptor `fd` (ie, until read() returns 0),
**	and allocates a memory region which stores the file contents in `*a_file`.
**
**	@param	fd		The file descriptor to read data from
**	@param	a_file	The address of the buffer to fill: is allocated and filled with the data
**	@param	max		The maximum amount of bytes to read from 'fd' (if 0, replaced by `(t_size)-1`)
**	@returns the amount of bytes read from the given file descriptor `fd` in total.
**		If the return value is a negative number, there was a read error:
**		You should then check `errno`, and/or use `IO_GetError(errno)` immediately after.
*/
t_sintmax				IO_Read_File(t_fd const fd, t_char* *a_file, t_size max);
#define c_readfile		IO_Read_File

//! Reads the contents of 'fd' and makes an array of strings, one for each line
/*!
**	Reads the contents of the file descriptor 'fd', and puts that into
**	an array of strings, one char pointer for each line (each '\\n' newline char).
**	Each '\\n' character in the string are replaced by '\\0' string terminators.
**	NB: If the file being read contains any '\\0' chars, the string array will end there.
**
**	@param	fd			The file descriptor to read data from
**	@param	a_strarr	The address of the string array to fill: the top-level
**						top-level pointer array is allocated and filled appropriately.
**	@returns the amount of bytes read from the given file descriptor `fd` in total.
**		If the return value is a negative number, there was a read error:
**		You should then check `errno`, and/or use `IO_GetError(errno)` immediately after.
*/
t_sintmax				IO_Read_Lines(t_fd const fd, t_char** *a_strarr);
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
**	@returns
**		+1 (GNL_LINE)	if a line of characters was successfully read
**		 0 (GNL_END)	if the end of the file was reached
**		-1 (GNL_ERROR)	if there's an error
*/
//TODO DO NOT USE, TODO FIX, confirmed to have very, very rare, platform-specific problems...
int						IO_Read_NextLine(t_fd const fd, t_char* *a_line);
#define c_getline		IO_Read_NextLine
#define c_getnextline	IO_Read_NextLine
#define c_readnextline	IO_Read_NextLine

#define GNL_LINE  +1	//!< Return value for c_getnextline: indicates succesful line read, more to follow
#define GNL_END    0	//!< Return value for c_getnextline: indicates successful line read, end of file reached
#define GNL_ERROR -1	//!< Return value for c_getnextline: indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character 'c' to the given file descriptor 'fd'
t_io_error				IO_Write_Char(t_fd fd, t_char c);
#define c_write_char	IO_Write_Char

//! Writes the given string 'str' to the given file descriptor 'fd'
t_io_error				IO_Write_String(t_fd fd, t_char const* str);
#define c_write_string	IO_Write_String

//! Writes the given string 'str' to the given file descriptor 'fd', and a newline '\n' char at the end
t_io_error				IO_Write_Line(t_fd fd, t_char const* str);
#define c_write_line	IO_Write_Line

//! Writes the given string array 'strarr' to the given file descriptor 'fd'
t_io_error				IO_Write_Lines(t_fd fd, t_char const** strarr);
#define c_write_lines	IO_Write_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the given file descriptor 'fd'
t_io_error				IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);
#define c_write_memory	IO_Write_Memory

//! Writes the given formatted string to the standard output - equivalent to 'fprintf()', or rather 'dprintf()'
_FORMAT(printf, 2, 3)
t_io_error				IO_Write_Format(t_fd fd, t_char const* format, ...);
#define c_write_format	IO_Write_Format
#define c_dprintf		IO_Write_Format



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char 'c' to the standard output.
t_io_error				IO_Output_Char(t_char c);
#define c_output_char	IO_Output_Char
#define c_putchar		IO_Output_Char

//! Writes the given string 'str' to the standard output.
t_io_error				IO_Output_String(t_char const* str);
#define c_output_string	IO_Output_String
#define c_putstr		IO_Output_String

//! Writes the given string 'str' to the standard output, with a newline '\n' character at the end.
t_io_error				IO_Output_Line(t_char const* str);
#define c_output_line	IO_Output_Line
#define c_putline		IO_Output_Line

//! Writes the given string array 'strls' to the standard output.
t_io_error				IO_Output_Lines(t_char const** strarr);
#define c_output_lines	IO_Output_Lines
#define c_putlines		IO_Output_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the standard output
t_io_error				IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);
#define c_output_memory	IO_Output_Memory
#define c_putmem		IO_Output_Memory

//! Writes the given formatted string to the standard output - equivalent to 'printf()'
_FORMAT(printf, 1, 2)
t_io_error				IO_Output_Format(t_char const* format, ...);
#define c_output_format	IO_Output_Format
#define c_printf		IO_Output_Format



/*
** ************************************************************************** *|
**                           IO 'errno' Error codes                           *|
** ************************************************************************** *|
*/

/*
**	Below is a list of the symbolic error names that are defined on Linux:
*/
#define IO_ERROR_2BIG			E2BIG			//!< (POSIX.1-2001) Argument list too long.
#define IO_ERROR_ACCES			EACCES			//!< (POSIX.1-2001) Permission denied.
#define IO_ERROR_ADDRINUSE		EADDRINUSE		//!< (POSIX.1-2001) Address already in use.
#define IO_ERROR_ADDRNOTAVAIL	EADDRNOTAVAIL	//!< (POSIX.1-2001) Address not available.
#define IO_ERROR_AFNOSUPPORT	EAFNOSUPPORT	//!< (POSIX.1-2001) Address family not supported.
#define IO_ERROR_AGAIN			EAGAIN			//!< (POSIX.1-2001) Resource temporarily unavailable (may be the same value as EWOULDBLOCK).
#define IO_ERROR_ALREADY		EALREADY		//!< (POSIX.1-2001) Connection already in progress.
#define IO_ERROR_BADE			EBADE			//!< Invalid exchange.
#define IO_ERROR_BADF			EBADF			//!< (POSIX.1-2001) Bad file descriptor.
#define IO_ERROR_BADFD			EBADFD			//!< File descriptor in bad state.
#define IO_ERROR_BADMSG			EBADMSG			//!< (POSIX.1-2001) Bad message.
#define IO_ERROR_BADR			EBADR			//!< Invalid request descriptor.
#define IO_ERROR_BADRQC			EBADRQC			//!< Invalid request code.
#define IO_ERROR_BADSLT			EBADSLT			//!< Invalid slot.
#define IO_ERROR_BUSY			EBUSY			//!< (POSIX.1-2001) Device or resource busy.
#define IO_ERROR_CANCELED		ECANCELED		//!< (POSIX.1-2001) Operation canceled.
#define IO_ERROR_CHILD			ECHILD			//!< (POSIX.1-2001) No child processes.
#define IO_ERROR_CHRNG			ECHRNG			//!< Channel number out of range.
#define IO_ERROR_COMM			ECOMM			//!< Communication error on send.
#define IO_ERROR_CONNABORTED	ECONNABORTED	//!< (POSIX.1-2001) Connection aborted.
#define IO_ERROR_CONNREFUSED	ECONNREFUSED	//!< (POSIX.1-2001) Connection refused.
#define IO_ERROR_CONNRESET		ECONNRESET		//!< (POSIX.1-2001) Connection reset.
#define IO_ERROR_DEADLK			EDEADLK			//!< (POSIX.1-2001) Resource deadlock avoided.
#define IO_ERROR_DEADLOCK		EDEADLOCK		//!< On most architectures, a synonym for EDEADLK. On some architectures (e.g., Linux MIPS, PowerPC, SPARC), it is a separate error code "File locking deadlock error".
#define IO_ERROR_DESTADDRREQ	EDESTADDRREQ	//!< (POSIX.1-2001) Destination address required.
#define IO_ERROR_DOM			EDOM			//!< (POSIX.1, C99) Mathematics argument out of domain of function.
#define IO_ERROR_DQUOT			EDQUOT			//!< (POSIX.1-2001) Disk quota exceeded.
#define IO_ERROR_EXIST			EEXIST			//!< (POSIX.1-2001) File exists.
#define IO_ERROR_FAULT			EFAULT			//!< (POSIX.1-2001) Bad address.
#define IO_ERROR_FBIG			EFBIG			//!< (POSIX.1-2001) File too large.
#define IO_ERROR_HOSTDOWN		EHOSTDOWN		//!< Host is down.
#define IO_ERROR_HOSTUNREACH	EHOSTUNREACH	//!< (POSIX.1-2001) Host is unreachable.
#define IO_ERROR_HWPOISON		EHWPOISON		//!< Memory page has hardware error.
#define IO_ERROR_IDRM			EIDRM			//!< (POSIX.1-2001) Identifier removed.
#define IO_ERROR_ILSEQ			EILSEQ			//!< (POSIX.1, C99) Invalid or incomplete multibyte or wide character. The text shown here is the glibc error description; in POSIX.1, this error is described as "Illegal byte sequence".
#define IO_ERROR_INPROGRESS		EINPROGRESS		//!< (POSIX.1-2001) Operation in progress.
#define IO_ERROR_INTR			EINTR			//!< (POSIX.1-2001) Interrupted function call; see signal(7).
#define IO_ERROR_INVAL			EINVAL			//!< (POSIX.1-2001) Invalid argument.
#define IO_ERROR_IO				EIO				//!< (POSIX.1-2001) Input/output error.
#define IO_ERROR_ISCONN			EISCONN			//!< (POSIX.1-2001) Socket is connected.
#define IO_ERROR_ISDIR			EISDIR			//!< (POSIX.1-2001) Is a directory.
#define IO_ERROR_ISNAM			EISNAM			//!< Is a named type file.
#define IO_ERROR_KEYEXPIRED		EKEYEXPIRED		//!< Key has expired.
#define IO_ERROR_KEYREJECTED	EKEYREJECTED	//!< Key was rejected by service.
#define IO_ERROR_KEYREVOKED		EKEYREVOKED		//!< Key has been revoked.
#define IO_ERROR_L2HLT			EL2HLT			//!< Level 2 halted.
#define IO_ERROR_L2NSYNC		EL2NSYNC		//!< Level 2 not synchronized.
#define IO_ERROR_L3HLT			EL3HLT			//!< Level 3 halted.
#define IO_ERROR_L3RST			EL3RST			//!< Level 3 reset.
#define IO_ERROR_LIBACC			ELIBACC			//!< Cannot access a needed shared library.
#define IO_ERROR_LIBBAD			ELIBBAD			//!< Accessing a corrupted shared library.
#define IO_ERROR_LIBMAX			ELIBMAX			//!< Attempting to link in too many shared libraries.
#define IO_ERROR_LIBSCN			ELIBSCN			//!< lib section in a.out corrupted
#define IO_ERROR_LIBEXEC		ELIBEXEC		//!< Cannot exec a shared library directly.
#define IO_ERROR_LNRANGE		ELNRANGE		//!< Link number out of range.
#define IO_ERROR_LOOP			ELOOP			//!< (POSIX.1-2001) Too many levels of symbolic links.
#define IO_ERROR_MEDIUMTYPE		EMEDIUMTYPE		//!< Wrong medium type.
#define IO_ERROR_MFILE			EMFILE			//!< (POSIX.1-2001) Too many open files.  Commonly caused by exceeding the RLIMIT_NOFILE resource limit described in getrlimit(2). Can also be caused by exceeding the limit specified in /proc/sys/fs/nr_open.
#define IO_ERROR_MLINK			EMLINK			//!< (POSIX.1-2001) Too many links.
#define IO_ERROR_MSGSIZE		EMSGSIZE		//!< (POSIX.1-2001) Message too long.
#define IO_ERROR_MULTIHOP		EMULTIHOP		//!< (POSIX.1-2001) Multihop attempted.
#define IO_ERROR_NAMETOOLONG	ENAMETOOLONG	//!< (POSIX.1-2001) Filename too long.
#define IO_ERROR_NETDOWN		ENETDOWN		//!< (POSIX.1-2001) Network is down.
#define IO_ERROR_NETRESET		ENETRESET		//!< (POSIX.1-2001) Connection aborted by network.
#define IO_ERROR_NETUNREACH		ENETUNREACH		//!< (POSIX.1-2001) Network unreachable.
#define IO_ERROR_NFILE			ENFILE			//!< (POSIX.1-2001) Too many open files in system. On Linux, this is probably a result of encountering the /proc/sys/fs/file-max limit (see proc(5)).
#define IO_ERROR_NOANO			ENOANO			//!< No anode.
#define IO_ERROR_NOBUFS			ENOBUFS			//!< (POSIX.1 (XSI STREAMS option)) No buffer space available.
#define IO_ERROR_NODATA			ENODATA			//!< (POSIX.1-2001) No message is available on the STREAM head read queue.
#define IO_ERROR_NODEV			ENODEV			//!< (POSIX.1-2001) No such device.
#define IO_ERROR_NOENT			ENOENT			//!< (POSIX.1-2001) No such file or directory. Typically, this error results when a specified pathname does not exist, or one of the components in the directory prefix of a pathname does not exist, or the specified pathname is a dangling symbolic link.
#define IO_ERROR_NOEXEC			ENOEXEC			//!< (POSIX.1-2001) define Exec			//!< format error.
#define IO_ERROR_NOKEY			ENOKEY			//!< Required key not available.
#define IO_ERROR_NOLCK			ENOLCK			//!< (POSIX.1-2001) No locks available.
#define IO_ERROR_NOLINK			ENOLINK			//!< (POSIX.1-2001) Link has been severed.
#define IO_ERROR_NOMEDIUM		ENOMEDIUM		//!< No medium found.
#define IO_ERROR_NOMEM			ENOMEM			//!< (POSIX.1-2001) Not enough space/cannot allocate memory.
#define IO_ERROR_NOMSG			ENOMSG			//!< (POSIX.1-2001) No message of the desired type.
#define IO_ERROR_NONET			ENONET			//!< Machine is not on the network.
#define IO_ERROR_NOPKG			ENOPKG			//!< Package not installed.
#define IO_ERROR_NOPROTOOPT		ENOPROTOOPT		//!< (POSIX.1-2001) Protocol not available.
#define IO_ERROR_NOSPC			ENOSPC			//!< (POSIX.1-2001) No space left on device.
#define IO_ERROR_NOSR			ENOSR			//!< (POSIX.1 (XSI STREAMS option)) No STREAM resources.
#define IO_ERROR_NOSTR			ENOSTR			//!< (POSIX.1 (XSI STREAMS option)) Not a STREAM.
#define IO_ERROR_NOSYS			ENOSYS			//!< (POSIX.1-2001) Function not implemented.
#define IO_ERROR_NOTBLK			ENOTBLK			//!< Block device required.
#define IO_ERROR_NOTCONN		ENOTCONN		//!< (POSIX.1-2001) The socket is not connected.
#define IO_ERROR_NOTDIR			ENOTDIR			//!< (POSIX.1-2001) Not a directory.
#define IO_ERROR_NOTEMPTY		ENOTEMPTY		//!< (POSIX.1-2001) Directory not empty.
#define IO_ERROR_NOTRECOVERABLE	ENOTRECOVERABLE	//!< (POSIX.1-2008) State not recoverable.
#define IO_ERROR_NOTSOCK		ENOTSOCK		//!< (POSIX.1-2001) Not a socket.
#define IO_ERROR_NOTSUP			ENOTSUP			//!< (POSIX.1-2001) Operation not supported.
#define IO_ERROR_NOTTY			ENOTTY			//!< (POSIX.1-2001) Inappropriate I/O control operation.
#define IO_ERROR_NOTUNIQ		ENOTUNIQ		//!< Name not unique on network.
#define IO_ERROR_NXIO			ENXIO			//!< (POSIX.1-2001) No such device or address.
#define IO_ERROR_OPNOTSUPP		EOPNOTSUPP		//!< (POSIX.1-2001) Operation not supported on socket. (ENOTSUP and EOPNOTSUPP have the same value on Linux, but according to POSIX.1 these error values should be distinct.)
#define IO_ERROR_OVERFLOW		EOVERFLOW		//!< (POSIX.1-2001) Value too large to be stored in data type.
#define IO_ERROR_OWNERDEAD		EOWNERDEAD		//!< (POSIX.1-2008) Owner died.
#define IO_ERROR_PERM			EPERM			//!< (POSIX.1-2001) Operation not permitted.
#define IO_ERROR_PFNOSUPPORT	EPFNOSUPPORT	//!< Protocol family not supported.
#define IO_ERROR_PIPE			EPIPE			//!< (POSIX.1-2001) Broken pipe.
#define IO_ERROR_PROTO			EPROTO			//!< (POSIX.1-2001) Protocol error.
#define IO_ERROR_PROTONOSUPPORT	EPROTONOSUPPORT	//!< (POSIX.1-2001) Protocol not supported.
#define IO_ERROR_PROTOTYPE		EPROTOTYPE		//!< (POSIX.1-2001) Protocol wrong type for socket.
#define IO_ERROR_RANGE			ERANGE			//!< (POSIX.1, C99) Result too large.
#define IO_ERROR_REMCHG			EREMCHG			//!< Remote address changed.
#define IO_ERROR_REMOTE			EREMOTE			//!< Object is remote.
#define IO_ERROR_REMOTEIO		EREMOTEIO		//!< Remote I/O error.
#define IO_ERROR_RESTART		ERESTART		//!< Interrupted system call should be restarted.
#define IO_ERROR_RFKILL			ERFKILL			//!< Operation not possible due to RF-kill.
#define IO_ERROR_ROFS			EROFS			//!< (POSIX.1-2001) Read-only filesystem.
#define IO_ERROR_SHUTDOWN		ESHUTDOWN		//!< Cannot send after transport endpoint shutdown.
#define IO_ERROR_SPIPE			ESPIPE			//!< (POSIX.1-2001) Invalid seek.
#define IO_ERROR_SOCKTNOSUPPORT	ESOCKTNOSUPPORT	//!< Socket type not supported.
#define IO_ERROR_SRCH			ESRCH			//!< (POSIX.1-2001) No such process.
#define IO_ERROR_STALE			ESTALE			//!< (POSIX.1-2001) Stale file handle. This error can occur for NFS and for other filesystems.
#define IO_ERROR_STRPIPE		ESTRPIPE		//!< Streams pipe error.
#define IO_ERROR_TIME			ETIME			//!< (POSIX.1 (XSI STREAMS option)) Timer expired. (POSIX.1 says "STREAM ioctl(2) timeout".)
#define IO_ERROR_TIMEDOUT		ETIMEDOUT		//!< (POSIX.1-2001) Connection timed out.
#define IO_ERROR_TOOMANYREFS	ETOOMANYREFS	//!< Too many references: cannot splice.
#define IO_ERROR_TXTBSY			ETXTBSY			//!< (POSIX.1-2001) Text file busy.
#define IO_ERROR_UCLEAN			EUCLEAN			//!< Structure needs cleaning.
#define IO_ERROR_UNATCH			EUNATCH			//!< Protocol driver not attached.
#define IO_ERROR_USERS			EUSERS			//!< Too many users.
#define IO_ERROR_WOULDBLOCK		EWOULDBLOCK		//!< (POSIX.1-2001) Operation would block (may be same value as EAGAIN).
#define IO_ERROR_XDEV			EXDEV			//!< (POSIX.1-2001) Improper link.
#define IO_ERROR_XFULL			EXFULL			//!< Exchange full.



/*! @} */
HEADER_END
#endif
