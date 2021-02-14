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
typedef int				t_io_error;
TYPEDEF_ALIAS(			t_io_error, IO_ERROR, PRIMITIVE)



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
**	@returns the new file descriptor value for the opened file, or a non-zero error code (ie: an 'errno' value)
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
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error				IO_Close(t_fd fd);
#define c_close			IO_Close
#define IO_File_Close	IO_Close



//! Returns the error message (a string literal) corresponding to the given 'errno' error number
char*						IO_GetError(int error_num);
#define c_strerror			IO_GetError
#define c_strerror_r		IO_GetError
#define IO_GetErrorMessage	IO_GetError

//! Returns 1(TRUE) if the given file fd corresponds to a terminal/commandline rather than a file
t_bool						IO_IsTerminal(t_fd fd);
#define c_isatty			IO_IsTerminal
#define IO_File_IsTerminal	IO_IsTerminal

//! Changes the file access mode permissions for the file at 'filepath' to the new value 'mode'
/*!
**	SYSCALL wrapper:
**		int chmod(const char *pathname, mode_t mode);
**
**	@param	filepath	The path of the file whose access permissions should change
**	@param	mode		The new file access mode permissions bitflag value to set
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error					IO_ChangeMode(char const* filepath, t_io_mode mode);
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
**	@returns 0(OK) on success, or a non-zero error code (ie: an 'errno' value)
*/
/* TODO find a way to make this as cross-platform as possible
t_io_error					IO_ChangeOwner(char const* filepath, char const* owner, char const* group);
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
**	@returns 0(OK) if the stream was read successfully, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error				IO_Read_File(t_fd const fd, char* *a_file, t_size max);
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
**	@returns 0(OK) if the stream was read successfully, or a non-zero error code (ie: an 'errno' value)
*/
t_io_error				IO_Read_Lines(t_fd const fd, char** *a_strarr);
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
int						IO_Read_NextLine(t_fd const fd, char* *a_line);
#define c_readnextline	IO_Read_NextLine
#define c_getnextline	IO_Read_NextLine

#define GNL_LINE  +1	//!< Return value for c_getnextline: indicates succesful line read, more to follow
#define GNL_END    0	//!< Return value for c_getnextline: indicates successful line read, end of file reached
#define GNL_ERROR -1	//!< Return value for c_getnextline: indicates a read error occurred



/*
** ************************************************************************** *|
**                              Writing Functions                             *|
** ************************************************************************** *|
*/

//! Writes the given character 'c' to the given file descriptor 'fd'
t_io_error				IO_Write_Char(t_fd fd, char c);
#define c_write_char	IO_Write_Char

//! Writes the given string 'str' to the given file descriptor 'fd'
t_io_error				IO_Write_String(t_fd fd, char const* str);
#define c_write_string	IO_Write_String

//! Writes the given string 'str' to the given file descriptor 'fd', and a newline '\n' char at the end
t_io_error				IO_Write_Line(t_fd fd, char const* str);
#define c_write_line	IO_Write_Line

//! Writes the given string array 'strarr' to the given file descriptor 'fd'
t_io_error				IO_Write_Lines(t_fd fd, char const** strarr);
#define c_write_lines	IO_Write_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the given file descriptor 'fd'
t_io_error				IO_Write_Memory(t_fd fd, t_u8 const* ptr, t_size n, t_u8 cols);
#define c_write_memory	IO_Write_Memory

//! Writes the given formatted string to the standard output - equivalent to 'fprintf()', or rather 'dprintf()'
_FORMAT(printf, 2, 3)
t_io_error				IO_Write_Format(t_fd fd, char const* format, ...);
#define c_write_format	IO_Write_Format
#define c_dprintf		IO_Write_Format



/*
** ************************************************************************** *|
**                             Commandline Output                             *|
** ************************************************************************** *|
*/

//! Writes the given char 'c' to the standard output.
t_io_error				IO_Output_Char(char c);
#define c_output_char	IO_Output_Char
#define c_putchar		IO_Output_Char

//! Writes the given string 'str' to the standard output.
t_io_error				IO_Output_String(char const* str);
#define c_output_string	IO_Output_String
#define c_putstr		IO_Output_String

//! Writes the given string 'str' to the standard output, with a newline '\n' character at the end.
t_io_error				IO_Output_Line(char const* str);
#define c_output_line	IO_Output_Line
#define c_putline		IO_Output_Line

//! Writes the given string array 'strls' to the standard output.
t_io_error				IO_Output_Lines(char const** strarr);
#define c_output_lines	IO_Output_Lines
#define c_putlines		IO_Output_Lines

//!< Writes 'n' bytes of memory from 'ptr' as hexadecimal 2-char blocks in 'cols' columns, to the standard output
t_io_error				IO_Output_Memory(t_u8 const* ptr, t_size n, t_u8 cols);
#define c_output_memory	IO_Output_Memory
#define c_putmem		IO_Output_Memory

//! Writes the given formatted string to the standard output - equivalent to 'printf()'
_FORMAT(printf, 1, 2)
t_io_error				IO_Output_Format(char const* format, ...);
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
#define IO_ERROR_2BIG			E2BIG			//!< Argument list too long (POSIX.1-2001).
#define IO_ERROR_ACCES			EACCES			//!< Permission denied (POSIX.1-2001).
#define IO_ERROR_ADDRINUSE		EADDRINUSE		//!< Address already in use (POSIX.1-2001).
#define IO_ERROR_ADDRNOTAVAIL	EADDRNOTAVAIL	//!< Address not available (POSIX.1-2001).
#define IO_ERROR_AFNOSUPPORT	EAFNOSUPPORT	//!< Address family not supported (POSIX.1-2001).
#define IO_ERROR_AGAIN			EAGAIN			//!< Resource temporarily unavailable (may be the same value as EWOULDBLOCK) (POSIX.1-2001).
#define IO_ERROR_ALREADY		EALREADY		//!< Connection already in progress (POSIX.1-2001).
#define IO_ERROR_BADE			EBADE			//!< Invalid exchange.
#define IO_ERROR_BADF			EBADF			//!< Bad file descriptor (POSIX.1-2001).
#define IO_ERROR_BADFD			EBADFD			//!< File descriptor in bad state.
#define IO_ERROR_BADMSG			EBADMSG			//!< Bad message (POSIX.1-2001).
#define IO_ERROR_BADR			EBADR			//!< Invalid request descriptor.
#define IO_ERROR_BADRQC			EBADRQC			//!< Invalid request code.
#define IO_ERROR_BADSLT			EBADSLT			//!< Invalid slot.
#define IO_ERROR_BUSY			EBUSY			//!< Device or resource busy (POSIX.1-2001).
#define IO_ERROR_CANCELED		ECANCELED		//!< Operation canceled (POSIX.1-2001).
#define IO_ERROR_CHILD			ECHILD			//!< No child processes (POSIX.1-2001).
#define IO_ERROR_CHRNG			ECHRNG			//!< Channel number out of range.
#define IO_ERROR_COMM			ECOMM			//!< Communication error on send.
#define IO_ERROR_CONNABORTED	ECONNABORTED	//!< Connection aborted (POSIX.1-2001).
#define IO_ERROR_CONNREFUSED	ECONNREFUSED	//!< Connection refused (POSIX.1-2001).
#define IO_ERROR_CONNRESET		ECONNRESET		//!< Connection reset (POSIX.1-2001).
#define IO_ERROR_DEADLK			EDEADLK			//!< Resource deadlock avoided (POSIX.1-2001).
#define IO_ERROR_DEADLOCK		EDEADLOCK		//!< On most architectures, a synonym for EDEADLK.  On some architectures (e.g., Linux MIPS, PowerPC, SPARC), it is a separate error code "File locking deadlock error".
#define IO_ERROR_DESTADDRREQ	EDESTADDRREQ	//!< Destination address required (POSIX.1-2001).
#define IO_ERROR_DOM			EDOM			//!< Mathematics argument out of domain of function (POSIX.1,	C99).
#define IO_ERROR_DQUOT			EDQUOT			//!< Disk quota exceeded (POSIX.1-2001).
#define IO_ERROR_EXIST			EEXIST			//!< File exists (POSIX.1-2001).
#define IO_ERROR_FAULT			EFAULT			//!< Bad address (POSIX.1-2001).
#define IO_ERROR_FBIG			EFBIG			//!< File too large (POSIX.1-2001).
#define IO_ERROR_HOSTDOWN		EHOSTDOWN		//!< Host is down.
#define IO_ERROR_HOSTUNREACH	EHOSTUNREACH	//!< Host is unreachable (POSIX.1-2001).
#define IO_ERROR_HWPOISON		EHWPOISON		//!< Memory page has hardware error.
#define IO_ERROR_IDRM			EIDRM			//!< Identifier removed (POSIX.1-2001).
#define IO_ERROR_ILSEQ			EILSEQ			//!< Invalid or incomplete multibyte or wide character	(POSIX.1, C99). The text shown here is the glibc error description; in POSIX.1, this error is described as "Illegal byte sequence".
#define IO_ERROR_INPROGRESS		EINPROGRESS		//!< Operation in progress (POSIX.1-2001).
#define IO_ERROR_INTR			EINTR			//!< Interrupted function call (POSIX.1-2001); see signal(7).
#define IO_ERROR_INVAL			EINVAL			//!< Invalid argument (POSIX.1-2001).
#define IO_ERROR_IO				EIO				//!< Input/output error (POSIX.1-2001).
#define IO_ERROR_ISCONN			EISCONN			//!< Socket is connected (POSIX.1-2001).
#define IO_ERROR_ISDIR			EISDIR			//!< Is a directory (POSIX.1-2001).
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
#define IO_ERROR_LOOP			ELOOP			//!< Too many levels of symbolic links (POSIX.1-2001).
#define IO_ERROR_MEDIUMTYPE		EMEDIUMTYPE		//!< Wrong medium type.
#define IO_ERROR_MFILE			EMFILE			//!< Too many open files (POSIX.1-2001).  Commonly caused by	exceeding the RLIMIT_NOFILE resource limit described in getrlimit(2).  Can also be caused by exceeding the limit specified in /proc/sys/fs/nr_open.
#define IO_ERROR_MLINK			EMLINK			//!< Too many links (POSIX.1-2001).
#define IO_ERROR_MSGSIZE		EMSGSIZE		//!< Message too long (POSIX.1-2001).
#define IO_ERROR_MULTIHOP		EMULTIHOP		//!< Multihop attempted (POSIX.1-2001).
#define IO_ERROR_NAMETOOLONG	ENAMETOOLONG	//!< Filename too long (POSIX.1-2001).
#define IO_ERROR_NETDOWN		ENETDOWN		//!< Network is down (POSIX.1-2001).
#define IO_ERROR_NETRESET		ENETRESET		//!< Connection aborted by network (POSIX.1-2001).
#define IO_ERROR_NETUNREACH		ENETUNREACH		//!< Network unreachable (POSIX.1-2001).
#define IO_ERROR_NFILE			ENFILE			//!< Too many open files in system (POSIX.1-2001).  On Linux,	this is probably a result of encountering the /proc/sys/fs/file-max limit (see proc(5)).
#define IO_ERROR_NOANO			ENOANO			//!< No anode.
#define IO_ERROR_NOBUFS			ENOBUFS			//!< No buffer space available (POSIX.1 (XSI STREAMS option)).
#define IO_ERROR_NODATA			ENODATA			//!< No message is available on the STREAM head read queue (POSIX.1-2001).
#define IO_ERROR_NODEV			ENODEV			//!< No such device (POSIX.1-2001).
#define IO_ERROR_NOENT			ENOENT			//!< No such file or directory (POSIX.1-2001). Typically, this error results when a specified pathname does not exist, or one of the components in the directory prefix of a pathname does not exist, or the specified pathname is a dangling symbolic link.
#define IO_ERROR_NOEXEC			ENOEXEC			//!< define Exec			//!< format error (POSIX.1-2001).
#define IO_ERROR_NOKEY			ENOKEY			//!< Required key not available.
#define IO_ERROR_NOLCK			ENOLCK			//!< No locks available (POSIX.1-2001).
#define IO_ERROR_NOLINK			ENOLINK			//!< Link has been severed (POSIX.1-2001).
#define IO_ERROR_NOMEDIUM		ENOMEDIUM		//!< No medium found.
#define IO_ERROR_NOMEM			ENOMEM			//!< Not enough space/cannot allocate memory (POSIX.1-2001).
#define IO_ERROR_NOMSG			ENOMSG			//!< No message of the desired type (POSIX.1-2001).
#define IO_ERROR_NONET			ENONET			//!< Machine is not on the network.
#define IO_ERROR_NOPKG			ENOPKG			//!< Package not installed.
#define IO_ERROR_NOPROTOOPT		ENOPROTOOPT		//!< Protocol not available (POSIX.1-2001).
#define IO_ERROR_NOSPC			ENOSPC			//!< No space left on device (POSIX.1-2001).
#define IO_ERROR_NOSR			ENOSR			//!< No STREAM resources (POSIX.1 (XSI STREAMS option)).
#define IO_ERROR_NOSTR			ENOSTR			//!< Not a STREAM (POSIX.1 (XSI STREAMS option)).
#define IO_ERROR_NOSYS			ENOSYS			//!< Function not implemented (POSIX.1-2001).
#define IO_ERROR_NOTBLK			ENOTBLK			//!< Block device required.
#define IO_ERROR_NOTCONN		ENOTCONN		//!< The socket is not connected (POSIX.1-2001).
#define IO_ERROR_NOTDIR			ENOTDIR			//!< Not a directory (POSIX.1-2001).
#define IO_ERROR_NOTEMPTY		ENOTEMPTY		//!< Directory not empty (POSIX.1-2001).
#define IO_ERROR_NOTRECOVERABLE	ENOTRECOVERABLE	//!< State not recoverable (POSIX.1-2008).
#define IO_ERROR_NOTSOCK		ENOTSOCK		//!< Not a socket (POSIX.1-2001).
#define IO_ERROR_NOTSUP			ENOTSUP			//!< Operation not supported (POSIX.1-2001).
#define IO_ERROR_NOTTY			ENOTTY			//!< Inappropriate I/O control operation (POSIX.1-2001).
#define IO_ERROR_NOTUNIQ		ENOTUNIQ		//!< Name not unique on network.
#define IO_ERROR_NXIO			ENXIO			//!< No such device or address (POSIX.1-2001).
#define IO_ERROR_OPNOTSUPP		EOPNOTSUPP		//!< Operation not supported on socket (POSIX.1-2001). (ENOTSUP and EOPNOTSUPP have the same value on Linux, but according to POSIX.1 these error values should be distinct.)
#define IO_ERROR_OVERFLOW		EOVERFLOW		//!< Value too large to be stored in data type (POSIX.1-2001).
#define IO_ERROR_OWNERDEAD		EOWNERDEAD		//!< Owner died (POSIX.1-2008).
#define IO_ERROR_PERM			EPERM			//!< Operation not permitted (POSIX.1-2001).
#define IO_ERROR_PFNOSUPPORT	EPFNOSUPPORT	//!< Protocol family not supported.
#define IO_ERROR_PIPE			EPIPE			//!< Broken pipe (POSIX.1-2001).
#define IO_ERROR_PROTO			EPROTO			//!< Protocol error (POSIX.1-2001).
#define IO_ERROR_PROTONOSUPPORT	EPROTONOSUPPORT	//!< Protocol not supported (POSIX.1-2001).
#define IO_ERROR_PROTOTYPE		EPROTOTYPE		//!< Protocol wrong type for socket (POSIX.1-2001).
#define IO_ERROR_RANGE			ERANGE			//!< Result too large (POSIX.1, C99).
#define IO_ERROR_REMCHG			EREMCHG			//!< Remote address changed.
#define IO_ERROR_REMOTE			EREMOTE			//!< Object is remote.
#define IO_ERROR_REMOTEIO		EREMOTEIO		//!< Remote I/O error.
#define IO_ERROR_RESTART		ERESTART		//!< Interrupted system call should be restarted.
#define IO_ERROR_RFKILL			ERFKILL			//!< Operation not possible due to RF-kill.
#define IO_ERROR_ROFS			EROFS			//!< Read-only filesystem (POSIX.1-2001).
#define IO_ERROR_SHUTDOWN		ESHUTDOWN		//!< Cannot send after transport endpoint shutdown.
#define IO_ERROR_SPIPE			ESPIPE			//!< Invalid seek (POSIX.1-2001).
#define IO_ERROR_SOCKTNOSUPPORT	ESOCKTNOSUPPORT	//!< Socket type not supported.
#define IO_ERROR_SRCH			ESRCH			//!< No such process (POSIX.1-2001).
#define IO_ERROR_STALE			ESTALE			//!< Stale file handle (POSIX.1-2001). This error can occur for NFS and for other filesystems.
#define IO_ERROR_STRPIPE		ESTRPIPE		//!< Streams pipe error.
#define IO_ERROR_TIME			ETIME			//!< Timer expired (POSIX.1 (XSI STREAMS option)). (POSIX.1 says "STREAM ioctl(2) timeout".)
#define IO_ERROR_TIMEDOUT		ETIMEDOUT		//!< Connection timed out (POSIX.1-2001).
#define IO_ERROR_TOOMANYREFS	ETOOMANYREFS	//!< Too many references: cannot splice.
#define IO_ERROR_TXTBSY			ETXTBSY			//!< Text file busy (POSIX.1-2001).
#define IO_ERROR_UCLEAN			EUCLEAN			//!< Structure needs cleaning.
#define IO_ERROR_UNATCH			EUNATCH			//!< Protocol driver not attached.
#define IO_ERROR_USERS			EUSERS			//!< Too many users.
#define IO_ERROR_WOULDBLOCK		EWOULDBLOCK		//!< Operation would block (may be same value as EAGAIN) (POSIX.1-2001).
#define IO_ERROR_XDEV			EXDEV			//!< Improper link (POSIX.1-2001).
#define IO_ERROR_XFULL			EXFULL			//!< Exchange full.



/*! @} */
HEADER_END
#endif
