/*============================================================================*\
||                                            ______________________________  ||
||  libccc_errors.h                          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ERRORS_H
#define __LIBCCC_ERRORS_H
/*!@group{libccc_errors,4,libccc_errors.h}
**
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



//!@doc The file to include in source files which use `HANDLE_ERROR()`
//!@{
#ifndef LIBCONFIG_ERROR_INCLUDE
#define LIBCONFIG_ERROR_INCLUDE	"libccc/sys/logger.h"
#endif
//!@}

//!@doc These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These macro functions determine how exception cases are to be handled by libccc.
**	You may change the logic here (to implement custom exception handling for example).
*/
//!@{
#ifndef LIBCONFIG_ERROR_DEFAULTHANDLER
	#ifdef DEBUG
	#define LIBCONFIG_ERROR_DEFAULTHANDLER(ERRORCODE, FUNCNAME, MESSAGE) \
	{\
		s_logger logger = DEFAULT_LOGGER_STDERR;\
		Log_Error_CCC(&logger, error,\
			"%s -> %s", FUNCNAME, MESSAGE);\
	}\

	#else
	#define LIBCONFIG_ERROR_DEFAULTHANDLER(ERRORCODE, FUNCNAME, MESSAGE) \
	{}
	
	#endif
#endif
//!@}



//!@doc The action to take when there is an integer overflow
//!@{
#ifndef LIBCONFIG_ERROR_HANDLEOVERFLOW
#if LIBCONFIG_UINT_INF
#define LIBCONFIG_ERROR_HANDLEOVERFLOW(TYPE, VALUE) \
	return VALUE
#elif LIBCONFIG_UINT_NAN
#define LIBCONFIG_ERROR_HANDLEOVERFLOW(TYPE, VALUE) \
	return TYPE##_NAN
#else // default action: let it continue
#define LIBCONFIG_ERROR_HANDLEOVERFLOW(TYPE, VALUE) \
	{}	//	return (VALUE);
#endif

#ifndef LIBCONFIG_ERROR_PARSEROVERFLOW
#define LIBCONFIG_ERROR_PARSEROVERFLOW(VALUE) \
	{}	//	if (dest)	*dest = VALUE;	return (i);
#endif

// TODO implement configurable return values in cases of number overflow with this macro
#define LIBCONFIG_ERROR_OVERFLOW(TYPE, VALUE) \
	CONCAT(TYPE,_ERROR)	//!< configurable error value
//	(VALUE)				//!< saturated type
//!@}



//!@doc These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These "plural-named" can be used to activate or deactivate exception handling at will.
*/
//!@{
#ifndef SHOULDHANDLE_ERROR_UNSPECIFIED
#define SHOULDHANDLE_ERROR_UNSPECIFIED  1
#endif

#ifndef SHOULDHANDLE_ERROR_SYSTEM
#define SHOULDHANDLE_ERROR_SYSTEM       1
#endif
#ifndef SHOULDHANDLE_ERROR_ALLOCFAILURE
#define SHOULDHANDLE_ERROR_ALLOCFAILURE 1
#endif

#ifndef SHOULDHANDLE_ERROR_PARSE
#define SHOULDHANDLE_ERROR_PARSE        1
#endif
#ifndef SHOULDHANDLE_ERROR_PRINT
#define SHOULDHANDLE_ERROR_PRINT        1
#endif
#ifndef SHOULDHANDLE_ERROR_NOTFOUND
#define SHOULDHANDLE_ERROR_NOTFOUND     1
#endif

#ifndef SHOULDHANDLE_ERROR_INVALIDARGS
#define SHOULDHANDLE_ERROR_INVALIDARGS  1
#endif
#ifndef SHOULDHANDLE_ERROR_NULLPOINTER
#define SHOULDHANDLE_ERROR_NULLPOINTER  1
#endif
#ifndef SHOULDHANDLE_ERROR_MATHDOMAIN
#define SHOULDHANDLE_ERROR_MATHDOMAIN   1
#endif
#ifndef SHOULDHANDLE_ERROR_RESULTRANGE
#define SHOULDHANDLE_ERROR_RESULTRANGE  1
#endif
#ifndef SHOULDHANDLE_ERROR_NANARGUMENT
#define SHOULDHANDLE_ERROR_NANARGUMENT  1
#endif
#ifndef SHOULDHANDLE_ERROR_ILLEGALBYTES
#define SHOULDHANDLE_ERROR_ILLEGALBYTES 1
#endif
#ifndef SHOULDHANDLE_ERROR_INVALIDENUM
#define SHOULDHANDLE_ERROR_INVALIDENUM  1
#endif
#ifndef SHOULDHANDLE_ERROR_INVALIDRANGE
#define SHOULDHANDLE_ERROR_INVALIDRANGE 1
#endif
#ifndef SHOULDHANDLE_ERROR_INDEX2SMALL
#define SHOULDHANDLE_ERROR_INDEX2SMALL  1
#endif
#ifndef SHOULDHANDLE_ERROR_INDEX2LARGE
#define SHOULDHANDLE_ERROR_INDEX2LARGE  1
#endif
#ifndef SHOULDHANDLE_ERROR_LENGTH2SMALL
#define SHOULDHANDLE_ERROR_LENGTH2SMALL 1
#endif
#ifndef SHOULDHANDLE_ERROR_LENGTH2LARGE
#define SHOULDHANDLE_ERROR_LENGTH2LARGE 1
#endif
#ifndef SHOULDHANDLE_ERROR_KEYNOTFOUND
#define SHOULDHANDLE_ERROR_KEYNOTFOUND  1
#endif
#ifndef SHOULDHANDLE_ERROR_WRONGTYPE
#define SHOULDHANDLE_ERROR_WRONGTYPE    1
#endif
#ifndef SHOULDHANDLE_ERROR_DELETEREF
#define SHOULDHANDLE_ERROR_DELETEREF    1
#endif
//!@}

/*!
**	This `#define` enables libccc error-handling when set to `1`.
**	You can set this `#define` to `0` if you wish to deactivate all error checking/handling.
**	This is not recommended, since no checks will be performed, so segfaults will happen.
**	Only do so if your code is robust and thoroughly tested, and you really need some extra performance.
*/
#define CHECK_ERRORS	1



#if (CHECK_ERRORS == 0) // error-checking disabled

#define CCCERROR(_CONDITION_, _ERRORTYPE_, ...) \
	(FALSE)

#else // error-checking enabled

/*!
**	@param _CONDITION_	The condition which checks if an error occurred
**	@param _ERRORTYPE_	The type of error to emit (an #e_cccerror value)
*/
#define CCCERROR(_CONDITION_, _ERRORTYPE_, ...) \
    ((_CONDITION_) && Error_If( \
        _ERRORTYPE_, \
        SHOULDHANDLE_##_ERRORTYPE_, \
        (const char*)__func__, \
        __VA_ARGS__)) \

//!@}

#endif



/*
** ************************************************************************** *|
**                           Error codes for libccc                           *|
** ************************************************************************** *|
*/

//! This type represents an error code for a libccc function (ie: a value for the 'errno' global variable)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/error/errno}
**	@isostd{C89,https://en.cppreference.com/w/c/error/errno_macros}
**
**	The `e_cccerror` error code enum used is meant to not be platform-specific, unlike `errno`.
**
**	The `ERROR_SYSTEM` error code indicates an error which stores an `strerror(errno)` message.
**	As such, it can hold many different messages (as many as your environment defines/uses).
**
**	NOTE: the only errno macros whch are defined by the standard itself are:
**	-	`EDOM`   (`ERROR_INVALIDARG_MATHDOMAIN`)    Mathematics argument out of domain of function
**	-	`ERANGE` (`ERROR_INVALIDARG_RESULTRANGE`)   Result too large
**	-	`EILSEQ` (`ERROR_INVALIDARG_ILLEGALBYTES`)  Illegal byte sequence (C95)
*/
typedef enum cccerror
{
	ERROR_UNSPECIFIED = ERROR, //!< Unspecified error (-1)
	ERROR_NONE        = OK,    //!< No error (0)

	ERROR_SYSTEM,       //!< System Error: `strerror(errno)` message

	ERROR_ALLOCFAILURE, //!< Error: Memory allocation failure
	ERROR_PARSE,        //!< Error: while attempting to parse string
	ERROR_PRINT,        //!< Error: while attempting to print string
	ERROR_NOTFOUND,     //!< Error: could not find value

	ERROR_INVALIDARGS,  //!< Argument Error
	ERROR_NULLPOINTER,  //!< Argument Error: null pointer received
	ERROR_MATHDOMAIN,   //!< Argument Error: mathematic out of domain error
	ERROR_RESULTRANGE,  //!< Argument Error: result cannot be represented within limited range
	ERROR_NANARGUMENT,  //!< Argument Error: should not receive NAN as argument
	ERROR_ILLEGALBYTES, //!< Argument Error: illegal byte sequence encountered
	ERROR_INVALIDENUM,  //!< Argument Error: value given is not a valid enum item
	ERROR_INVALIDRANGE, //!< Argument Error: range given is inverted: 'min' is larger than 'max'
	ERROR_INDEX2SMALL,  //!< Argument Error: index value given is too small
	ERROR_INDEX2LARGE,  //!< Argument Error: index value given is too large
	ERROR_LENGTH2SMALL, //!< Argument Error: length value given is too small
	ERROR_LENGTH2LARGE, //!< Argument Error: length value given is too large
	ERROR_KEYNOTFOUND,  //!< Argument Error: could not find item with the given key
	ERROR_WRONGTYPE,    //!< Argument Error: attempted to read dynamic-type item using the wrong type
	ERROR_DELETEREF,    //!< Argument Error: attempted to free an area of constant memory

//	ERROR_,

	ENUMLENGTH_CCCERROR
}	e_cccerror;

/*
// TODO thread-safe global, like 'errno'
typedef struct stdglobal
{
	void*		thread_id;
	e_cccerror	code;
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
#define ERRNO_2BIG            E2BIG             //!< (POSIX.1-2001) Argument list too long.
#define ERRNO_ACCES           EACCES            //!< (POSIX.1-2001) Permission denied.
#define ERRNO_ADDRINUSE       EADDRINUSE        //!< (POSIX.1-2001) Address already in use.
#define ERRNO_ADDRNOTAVAIL    EADDRNOTAVAIL     //!< (POSIX.1-2001) Address not available.
#define ERRNO_AFNOSUPPORT     EAFNOSUPPORT      //!< (POSIX.1-2001) Address family not supported.
#define ERRNO_AGAIN           EAGAIN            //!< (POSIX.1-2001) Resource temporarily unavailable (may be the same value as EWOULDBLOCK).
#define ERRNO_ALREADY         EALREADY          //!< (POSIX.1-2001) Connection already in progress.
#define ERRNO_BADE            EBADE             //!< Invalid exchange.
#define ERRNO_BADF            EBADF             //!< (POSIX.1-2001) Bad file descriptor.
#define ERRNO_BADFD           EBADFD            //!< File descriptor in bad state.
#define ERRNO_BADMSG          EBADMSG           //!< (POSIX.1-2001) Bad message.
#define ERRNO_BADR            EBADR             //!< Invalid request descriptor.
#define ERRNO_BADRQC          EBADRQC           //!< Invalid request code.
#define ERRNO_BADSLT          EBADSLT           //!< Invalid slot.
#define ERRNO_BUSY            EBUSY             //!< (POSIX.1-2001) Device or resource busy.
#define ERRNO_CANCELED        ECANCELED         //!< (POSIX.1-2001) Operation canceled.
#define ERRNO_CHILD           ECHILD            //!< (POSIX.1-2001) No child processes.
#define ERRNO_CHRNG           ECHRNG            //!< Channel number out of range.
#define ERRNO_COMM            ECOMM             //!< Communication error on send.
#define ERRNO_CONNABORTED     ECONNABORTED      //!< (POSIX.1-2001) Connection aborted.
#define ERRNO_CONNREFUSED     ECONNREFUSED      //!< (POSIX.1-2001) Connection refused.
#define ERRNO_CONNRESET       ECONNRESET        //!< (POSIX.1-2001) Connection reset.
#define ERRNO_DEADLK          EDEADLK           //!< (POSIX.1-2001) Resource deadlock avoided.
#define ERRNO_DEADLOCK        EDEADLOCK         //!< On most architectures, a synonym for EDEADLK. On some architectures (e.g., Linux MIPS, PowerPC, SPARC), it is a separate error code "File locking deadlock error".
#define ERRNO_DESTADDRREQ     EDESTADDRREQ      //!< (POSIX.1-2001) Destination address required.
#define ERRNO_DOM             EDOM              //!< (POSIX.1, C99) Mathematics argument out of domain of function.
#define ERRNO_DQUOT           EDQUOT            //!< (POSIX.1-2001) Disk quota exceeded.
#define ERRNO_EXIST           EEXIST            //!< (POSIX.1-2001) File exists.
#define ERRNO_FAULT           EFAULT            //!< (POSIX.1-2001) Bad address.
#define ERRNO_FBIG            EFBIG             //!< (POSIX.1-2001) File too large.
#define ERRNO_HOSTDOWN        EHOSTDOWN         //!< Host is down.
#define ERRNO_HOSTUNREACH     EHOSTUNREACH      //!< (POSIX.1-2001) Host is unreachable.
#define ERRNO_HWPOISON        EHWPOISON         //!< Memory page has hardware error.
#define ERRNO_IDRM            EIDRM             //!< (POSIX.1-2001) Identifier removed.
#define ERRNO_ILSEQ           EILSEQ            //!< (POSIX.1, C99) Invalid or incomplete multibyte or wide character. The text shown here is the glibc error description; in POSIX.1, this error is described as "Illegal byte sequence".
#define ERRNO_INPROGRESS      EINPROGRESS       //!< (POSIX.1-2001) Operation in progress.
#define ERRNO_INTR            EINTR             //!< (POSIX.1-2001) Interrupted function call; see signal(7).
#define ERRNO_INVAL           EINVAL            //!< (POSIX.1-2001) Invalid argument.
#define ERRNO_IO              EIO               //!< (POSIX.1-2001) Input/output error.
#define ERRNO_ISCONN          EISCONN           //!< (POSIX.1-2001) Socket is connected.
#define ERRNO_ISDIR           EISDIR            //!< (POSIX.1-2001) Is a directory.
#define ERRNO_ISNAM           EISNAM            //!< Is a named type file.
#define ERRNO_KEYEXPIRED      EKEYEXPIRED       //!< Key has expired.
#define ERRNO_KEYREJECTED     EKEYREJECTED      //!< Key was rejected by service.
#define ERRNO_KEYREVOKED      EKEYREVOKED       //!< Key has been revoked.
#define ERRNO_L2HLT           EL2HLT            //!< Level 2 halted.
#define ERRNO_L2NSYNC         EL2NSYNC          //!< Level 2 not synchronized.
#define ERRNO_L3HLT           EL3HLT            //!< Level 3 halted.
#define ERRNO_L3RST           EL3RST            //!< Level 3 reset.
#define ERRNO_LIBACC          ELIBACC           //!< Cannot access a needed shared library.
#define ERRNO_LIBBAD          ELIBBAD           //!< Accessing a corrupted shared library.
#define ERRNO_LIBMAX          ELIBMAX           //!< Attempting to link in too many shared libraries.
#define ERRNO_LIBSCN          ELIBSCN           //!< lib section in a.out corrupted
#define ERRNO_LIBEXEC         ELIBEXEC          //!< Cannot exec a shared library directly.
#define ERRNO_LNRANGE         ELNRANGE          //!< Link number out of range.
#define ERRNO_LOOP            ELOOP             //!< (POSIX.1-2001) Too many levels of symbolic links.
#define ERRNO_MEDIUMTYPE      EMEDIUMTYPE       //!< Wrong medium type.
#define ERRNO_MFILE           EMFILE            //!< (POSIX.1-2001) Too many open files.  Commonly caused by exceeding the RLIMIT_NOFILE resource limit described in getrlimit(2). Can also be caused by exceeding the limit specified in /proc/sys/fs/nr_open.
#define ERRNO_MLINK           EMLINK            //!< (POSIX.1-2001) Too many links.
#define ERRNO_MSGSIZE         EMSGSIZE          //!< (POSIX.1-2001) Message too long.
#define ERRNO_MULTIHOP        EMULTIHOP         //!< (POSIX.1-2001) Multihop attempted.
#define ERRNO_NAMETOOLONG     ENAMETOOLONG      //!< (POSIX.1-2001) Filename too long.
#define ERRNO_NETDOWN         ENETDOWN          //!< (POSIX.1-2001) Network is down.
#define ERRNO_NETRESET        ENETRESET         //!< (POSIX.1-2001) Connection aborted by network.
#define ERRNO_NETUNREACH      ENETUNREACH       //!< (POSIX.1-2001) Network unreachable.
#define ERRNO_NFILE           ENFILE            //!< (POSIX.1-2001) Too many open files in system. On Linux, this is probably a result of encountering the /proc/sys/fs/file-max limit (see proc(5)).
#define ERRNO_NOANO           ENOANO            //!< No anode.
#define ERRNO_NOBUFS          ENOBUFS           //!< (POSIX.1 (XSI STREAMS option)) No buffer space available.
#define ERRNO_NODATA          ENODATA           //!< (POSIX.1-2001) No message is available on the STREAM head read queue.
#define ERRNO_NODEV           ENODEV            //!< (POSIX.1-2001) No such device.
#define ERRNO_NOENT           ENOENT            //!< (POSIX.1-2001) No such file or directory. Typically, this error results when a specified pathname does not exist, or one of the components in the directory prefix of a pathname does not exist, or the specified pathname is a dangling symbolic link.
#define ERRNO_NOEXEC          ENOEXEC           //!< (POSIX.1-2001) define Exec			//!< format error.
#define ERRNO_NOKEY           ENOKEY            //!< Required key not available.
#define ERRNO_NOLCK           ENOLCK            //!< (POSIX.1-2001) No locks available.
#define ERRNO_NOLINK          ENOLINK           //!< (POSIX.1-2001) Link has been severed.
#define ERRNO_NOMEDIUM        ENOMEDIUM         //!< No medium found.
#define ERRNO_NOMEM           ENOMEM            //!< (POSIX.1-2001) Not enough space/cannot allocate memory.
#define ERRNO_NOMSG           ENOMSG            //!< (POSIX.1-2001) No message of the desired type.
#define ERRNO_NONET           ENONET            //!< Machine is not on the network.
#define ERRNO_NOPKG           ENOPKG            //!< Package not installed.
#define ERRNO_NOPROTOOPT      ENOPROTOOPT       //!< (POSIX.1-2001) Protocol not available.
#define ERRNO_NOSPC           ENOSPC            //!< (POSIX.1-2001) No space left on device.
#define ERRNO_NOSR            ENOSR             //!< (POSIX.1 (XSI STREAMS option)) No STREAM resources.
#define ERRNO_NOSTR           ENOSTR            //!< (POSIX.1 (XSI STREAMS option)) Not a STREAM.
#define ERRNO_NOSYS           ENOSYS            //!< (POSIX.1-2001) Function not implemented.
#define ERRNO_NOTBLK          ENOTBLK           //!< Block device required.
#define ERRNO_NOTCONN         ENOTCONN          //!< (POSIX.1-2001) The socket is not connected.
#define ERRNO_NOTDIR          ENOTDIR           //!< (POSIX.1-2001) Not a directory.
#define ERRNO_NOTEMPTY        ENOTEMPTY         //!< (POSIX.1-2001) Directory not empty.
#define ERRNO_NOTRECOVERABLE  ENOTRECOVERABLE   //!< (POSIX.1-2008) State not recoverable.
#define ERRNO_NOTSOCK         ENOTSOCK          //!< (POSIX.1-2001) Not a socket.
#define ERRNO_NOTSUP          ENOTSUP           //!< (POSIX.1-2001) Operation not supported.
#define ERRNO_NOTTY           ENOTTY            //!< (POSIX.1-2001) Inappropriate I/O control operation.
#define ERRNO_NOTUNIQ         ENOTUNIQ          //!< Name not unique on network.
#define ERRNO_NXIO            ENXIO             //!< (POSIX.1-2001) No such device or address.
#define ERRNO_OPNOTSUPP       EOPNOTSUPP        //!< (POSIX.1-2001) Operation not supported on socket. (ENOTSUP and EOPNOTSUPP have the same value on Linux, but according to POSIX.1 these error values should be distinct.)
#define ERRNO_OVERFLOW        EOVERFLOW         //!< (POSIX.1-2001) Value too large to be stored in data type.
#define ERRNO_OWNERDEAD       EOWNERDEAD        //!< (POSIX.1-2008) Owner died.
#define ERRNO_PERM            EPERM             //!< (POSIX.1-2001) Operation not permitted.
#define ERRNO_PFNOSUPPORT     EPFNOSUPPORT      //!< Protocol family not supported.
#define ERRNO_PIPE            EPIPE             //!< (POSIX.1-2001) Broken pipe.
#define ERRNO_PROTO           EPROTO            //!< (POSIX.1-2001) Protocol error.
#define ERRNO_PROTONOSUPPORT  EPROTONOSUPPORT   //!< (POSIX.1-2001) Protocol not supported.
#define ERRNO_PROTOTYPE       EPROTOTYPE        //!< (POSIX.1-2001) Protocol wrong type for socket.
#define ERRNO_RANGE           ERANGE            //!< (POSIX.1, C99) Result too large.
#define ERRNO_REMCHG          EREMCHG           //!< Remote address changed.
#define ERRNO_REMOTE          EREMOTE           //!< Object is remote.
#define ERRNO_REMOTEIO        EREMOTEIO         //!< Remote I/O error.
#define ERRNO_RESTART         ERESTART          //!< Interrupted system call should be restarted.
#define ERRNO_RFKILL          ERFKILL           //!< Operation not possible due to RF-kill.
#define ERRNO_ROFS            EROFS             //!< (POSIX.1-2001) Read-only filesystem.
#define ERRNO_SHUTDOWN        ESHUTDOWN         //!< Cannot send after transport endpoint shutdown.
#define ERRNO_SPIPE           ESPIPE            //!< (POSIX.1-2001) Invalid seek.
#define ERRNO_SOCKTNOSUPPORT  ESOCKTNOSUPPORT   //!< Socket type not supported.
#define ERRNO_SRCH            ESRCH             //!< (POSIX.1-2001) No such process.
#define ERRNO_STALE           ESTALE            //!< (POSIX.1-2001) Stale file handle. This error can occur for NFS and for other filesystems.
#define ERRNO_STRPIPE         ESTRPIPE          //!< Streams pipe error.
#define ERRNO_TIME            ETIME             //!< (POSIX.1 (XSI STREAMS option)) Timer expired. (POSIX.1 says "STREAM ioctl(2) timeout".)
#define ERRNO_TIMEDOUT        ETIMEDOUT         //!< (POSIX.1-2001) Connection timed out.
#define ERRNO_TOOMANYREFS     ETOOMANYREFS      //!< Too many references: cannot splice.
#define ERRNO_TXTBSY          ETXTBSY           //!< (POSIX.1-2001) Text file busy.
#define ERRNO_UCLEAN          EUCLEAN           //!< Structure needs cleaning.
#define ERRNO_UNATCH          EUNATCH           //!< Protocol driver not attached.
#define ERRNO_USERS           EUSERS            //!< Too many users.
#define ERRNO_WOULDBLOCK      EWOULDBLOCK       //!< (POSIX.1-2001) Operation would block (may be same value as EAGAIN).
#define ERRNO_XDEV            EXDEV             //!< (POSIX.1-2001) Improper link.
#define ERRNO_XFULL           EXFULL            //!< Exchange full.
#endif


/*! @endgroup */
HEADER_END
#endif
