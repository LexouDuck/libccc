/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_errors.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ERRORS_H
#define __LIBCCC_ERRORS_H
/*! @file libccc_errors.h
**	@addtogroup libccc_errors
**	@{
**	This header defines all the primitive types and common macros to use.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                             Error handling logic                           *|
** ************************************************************************** *|
*/

//! These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These macro functions determine how exception cases are to be handled by libccc.
**	You may change the logic here (to implement custom exception handling for example).
*/
#define LIBCONFIG_HANDLE_ERROR(...) \
{									\
	IO_Output_Format(__VA_ARGS__);	\
}									\

//! The action to take when there is an integer overflow (by default, let it continue)
#define LIBCONFIG_HANDLE_OVERFLOW \
	// return (0);



//! The file to include in source files which use `HANDLE_ERROR()`
#define LIBCONFIG_HANDLE_INCLUDE	"libccc/error.h"



//! These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These "plural-named" can be used to activate or deactivate exception handling at will.
*/
//!@{
#define HANDLE_ERRORS_UNSPECIFIED  1
#define HANDLE_ERRORS_SYSTEM       1
#define HANDLE_ERRORS_ALLOCFAILURE 1
#define HANDLE_ERRORS_INVALIDARGS  1
#define HANDLE_ERRORS_NULLPOINTER  1
#define HANDLE_ERRORS_MATHDOMAIN   1
#define HANDLE_ERRORS_RESULTRANGE  1
#define HANDLE_ERRORS_NANARGUMENT  1
#define HANDLE_ERRORS_ILLEGALBYTES 1
#define HANDLE_ERRORS_INVALIDENUM  1
#define HANDLE_ERRORS_INDEX2SMALL  1
#define HANDLE_ERRORS_INDEX2LARGE  1
#define HANDLE_ERRORS_LENGTH2SMALL 1
#define HANDLE_ERRORS_LENGTH2LARGE 1
#define HANDLE_ERRORS_KEYNOTFOUND  1
#define HANDLE_ERRORS_WRONGTYPE    1
#define HANDLE_ERRORS_DELETEREF    1
#define HANDLE_ERRORS_PARSE        1
#define HANDLE_ERRORS_PRINT        1
//!@}



//! Comment out this `#define` to deactivate all error handling (not recommended)
#define HANDLE_ERRORS
#ifndef HANDLE_ERRORS
#define HANDLE_ERROR(	ERRORTYPE, CONDITION, ACTION) 
#define HANDLE_ERROR_SF(ERRORTYPE, CONDITION, ACTION, ...) 



#else
//! The behavior to handle an error case
/*!
**	@param ERRORTYPE	The type of error to emit (an `e_stderror` value)
**	@param CONDITION	The condition to check the error
**	@param ...			The actions(s) to perform after handling (`return`, `break`, etc)
**			A variadic argument is used here to allow use of the comma operator.
*/
#define HANDLE_ERROR(ERRORTYPE, CONDITION, ACTION) \
	if (CONDITION)												\
	{															\
		Error_Set(ERROR_##ERRORTYPE);							\
		if (HANDLE_ERRORS_##ERRORTYPE)							\
		{														\
			LIBCONFIG_HANDLE_ERROR(								\
				C_RED"ERROR"C_RESET": %s -> %s\n", __func__,	\
				Error_GetMessage(ERROR_##ERRORTYPE))			\
		}														\
		ACTION													\
	}															\

//! The behavior to handle an error case, with a custom message
/*!
**	@param ERRORTYPE	The type of error to emit (an `e_stderror` value)
**	@param CONDITION	The condition to check the error
**	@param ACTION		The actions(s) to perform after handling (`return`, `break`, etc)
**	@param ...			The custom error message (format string and args, like `printf()`)
*/
#define HANDLE_ERROR_SF(ERRORTYPE, CONDITION, ACTION, ...) \
	if (CONDITION)													\
	{																\
		Error_Set(ERROR_##ERRORTYPE);								\
		if (HANDLE_ERRORS_##ERRORTYPE)								\
		{															\
			t_char* tmp_##ERRORTYPE = String_Format(__VA_ARGS__);	\
			LIBCONFIG_HANDLE_ERROR(									\
				C_RED"ERROR"C_RESET": %s -> %s\n%s\n", __func__,	\
				Error_GetMessage(ERROR_##ERRORTYPE),				\
				tmp_##ERRORTYPE)									\
			String_Delete(&tmp_##ERRORTYPE);						\
		}															\
		ACTION														\
	}																\

#endif



/*
** ************************************************************************** *|
**                           Error codes for libccc                           *|
** ************************************************************************** *|
*/

//! This type represents an error code for a libccc function (ie: a value for the 'errno' global variable)
/*!
**	@isostd{https://en.cppreference.com/w/c/error/errno}
**	@isostd{https://en.cppreference.com/w/c/error/errno_macros}
**
**	The `e_stderror` error code enum used is meant to not be platform-specific, unlike `errno`.
**
**	The `ERROR_SYSTEM_IO` error code indicates an error which stores an `strerror(errno)` message.
**	As such, it can hold many different messages (as many as your environment defines/uses).
**
**	NOTE: the only errno macros whch are defined by the standard itself are:
**	-	`EDOM`   (`ERROR_INVALIDARG_MATHDOMAIN`)    Mathematics argument out of domain of function
**	-	`ERANGE` (`ERROR_INVALIDARG_RESULTRANGE`)   Result too large
**	-	`EILSEQ` (`ERROR_INVALIDARG_ILLEGALBYTES`)  Illegal byte sequence (C95)
*/
typedef enum stderror
{
	ERROR_UNSPECIFIED = ERROR, //!< Unspecified error
	ERROR_NONE        = OK,    //!< No error

	ERROR_SYSTEM,       //!< System Error: `strerror(errno)` message
	ERROR_ALLOCFAILURE, //!< System Error: Memory allocation failure

	ERROR_INVALIDARGS,  //!< Argument Error
	ERROR_NULLPOINTER,  //!< Argument Error: null pointer received
	ERROR_MATHDOMAIN,   //!< Argument Error: mathematic out of domain error
	ERROR_RESULTRANGE,  //!< Argument Error: result cannot be represented within limited range
	ERROR_NANARGUMENT,  //!< Argument Error: should not receive NAN as argument
	ERROR_ILLEGALBYTES, //!< Argument Error: illegal byte sequence encountered
	ERROR_INVALIDENUM,  //!< Argument Error: value given is not a valid enum item
	ERROR_INDEX2SMALL,  //!< Argument Error: index value given is too small
	ERROR_INDEX2LARGE,  //!< Argument Error: index value given is too large
	ERROR_LENGTH2SMALL, //!< Argument Error: length value given is too small
	ERROR_LENGTH2LARGE, //!< Argument Error: length value given is too large
	ERROR_KEYNOTFOUND,  //!< Argument Error: could not find item with the given key
	ERROR_WRONGTYPE,    //!< Argument Error: attempted to read dynamic-type item with wrong type
	ERROR_DELETEREF,    //!< Argument Error: attempted to free an area of constant memory

	ERROR_PARSE,        //!< Error while attempting to parse string
	ERROR_PRINT,        //!< Error while attempting to print string

//	ERROR_,

	ENUMLENGTH_STDERROR,
}		e_stderror;

/*
// TODO thread-safe global, like 'errno'
typedef struct stdglobal
{
	void*		thread_id;
	e_stderror	code;
	char*		message;
}			s_stdglobal;

*/

/*
** ************************************************************************** *|
**                           IO 'errno' Error codes                           *|
** ************************************************************************** *|
*/

/*
**	Below is a list of the symbolic error names that are defined on Linux:
*/
#if 0
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
#endif


/*! @} */
HEADER_END
#endif
