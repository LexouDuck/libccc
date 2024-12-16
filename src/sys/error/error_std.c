
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"

#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	extern	int*	errno(void);
	#define errno	(*errno())
	#endif
#endif
#ifndef __NOSTD__
	#include <string.h>
#else
	char*	strerror(int errnum);
	int		strerror_s(char* buf, size_t buflen, int errnum);
	int		strerror_r(int errnum, char* buf, size_t buflen);
#endif

#include "libccc/sys/io.h"
#include "libccc/sys/error.h"

#include LIBCONFIG_ERROR_INCLUDE



#ifndef ENUMLENGTH_STDERROR
#define ENUMLENGTH_STDERROR	(t_errno)256
#endif

//! Define the list of info for all the common POSIX-1/C++11 errno macros
static s_error_info	Error_STD[ENUMLENGTH_STDERROR] =
{
#ifndef __NOSTD__
	{ E2BIG,            "E2BIG",            "Argument list too long" },
	{ EACCES,           "EACCES",           "Permission denied" },
	{ EADDRINUSE,       "EADDRINUSE",       "Address in use" },
	{ EADDRNOTAVAIL,    "EADDRNOTAVAIL",    "Address not available" },
	{ EAFNOSUPPORT,     "EAFNOSUPPORT",     "Address family not supported" },
	{ EAGAIN,           "EAGAIN",           "Resource unavailable, try again" },
	{ EALREADY,         "EALREADY",         "Connection already in progress" },
	{ EBADF,            "EBADF",            "Bad file descriptor" },
	{ EBADMSG,          "EBADMSG",          "Bad message" },
	{ EBUSY,            "EBUSY",            "Device or resource busy" },
	{ ECANCELED,        "ECANCELED",        "Operation canceled" },
	{ ECHILD,           "ECHILD",           "No child processes" },
	{ ECONNABORTED,     "ECONNABORTED",     "Connection aborted" },
	{ ECONNREFUSED,     "ECONNREFUSED",     "Connection refused" },
	{ ECONNRESET,       "ECONNRESET",       "Connection reset" },
	{ EDEADLK,          "EDEADLK",          "Resource deadlock would occur" },
	{ EDESTADDRREQ,     "EDESTADDRREQ",     "Destination address required" },
	{ EDOM,             "EDOM",             "Mathematics argument out of domain of function" },
	{ EEXIST,           "EEXIST",           "File exists" },
	{ EFAULT,           "EFAULT",           "Bad address" },
	{ EFBIG,            "EFBIG",            "File too large" },
	{ EHOSTUNREACH,     "EHOSTUNREACH",     "Host is unreachable" },
	{ EIDRM,            "EIDRM",            "Identifier removed" },
	{ EILSEQ,           "EILSEQ",           "Illegal byte sequence" },
	{ EINPROGRESS,      "EINPROGRESS",      "Operation in progress" },
	{ EINTR,            "EINTR",            "Interrupted function" },
	{ EINVAL,           "EINVAL",           "Invalid argument" },
	{ EIO,              "EIO",              "I/O error" },
	{ EISCONN,          "EISCONN",          "Socket is connected" },
	{ EISDIR,           "EISDIR",           "Is a directory" },
	{ ELOOP,            "ELOOP",            "Too many levels of symbolic links" },
	{ EMFILE,           "EMFILE",           "File descriptor value too large" },
	{ EMLINK,           "EMLINK",           "Too many links" },
	{ EMSGSIZE,         "EMSGSIZE",         "Message too large" },
	{ ENAMETOOLONG,     "ENAMETOOLONG",     "Filename too long" },
	{ ENETDOWN,         "ENETDOWN",         "Network is down" },
	{ ENETRESET,        "ENETRESET",        "Connection aborted by network" },
	{ ENETUNREACH,      "ENETUNREACH",      "Network unreachable" },
	{ ENFILE,           "ENFILE",           "Too many files open in system" },
	{ ENOBUFS,          "ENOBUFS",          "No buffer space available" },
	{ ENODATA,          "ENODATA",          "No message is available on the STREAM head read queue" },
	{ ENODEV,           "ENODEV",           "No such device" },
	{ ENOENT,           "ENOENT",           "No such file or directory" },
	{ ENOEXEC,          "ENOEXEC",          "Executable file format error" },
	{ ENOLCK,           "ENOLCK",           "No locks available" },
	{ ENOLINK,          "ENOLINK",          "Link has been severed" },
	{ ENOMEM,           "ENOMEM",           "Not enough space" },
	{ ENOMSG,           "ENOMSG",           "No message of the desired type" },
	{ ENOPROTOOPT,      "ENOPROTOOPT",      "Protocol not available" },
	{ ENOSPC,           "ENOSPC",           "No space left on device" },
	{ ENOSR,            "ENOSR",            "No STREAM resources" },
	{ ENOSTR,           "ENOSTR",           "Not a STREAM" },
	{ ENOSYS,           "ENOSYS",           "Function not supported" },
	{ ENOTCONN,         "ENOTCONN",         "The socket is not connected" },
	{ ENOTDIR,          "ENOTDIR",          "Not a directory" },
	{ ENOTEMPTY,        "ENOTEMPTY",        "Directory not empty" },
	{ ENOTRECOVERABLE,  "ENOTRECOVERABLE",  "State not recoverable" },
	{ ENOTSOCK,         "ENOTSOCK",         "Not a socket" },
	{ ENOTSUP,          "ENOTSUP",          "Not supported" },
	{ ENOTTY,           "ENOTTY",           "Inappropriate I/O control operation" },
	{ ENXIO,            "ENXIO",            "No such device or address" },
	{ EOPNOTSUPP,       "EOPNOTSUPP",       "Operation not supported on socket" },
	{ EOVERFLOW,        "EOVERFLOW",        "Value too large to be stored in data type" },
	{ EOWNERDEAD,       "EOWNERDEAD",       "Previous owner died" },
	{ EPERM,            "EPERM",            "Operation not permitted" },
	{ EPIPE,            "EPIPE",            "Broken pipe" },
	{ EPROTO,           "EPROTO",           "Protocol error" },
	{ EPROTONOSUPPORT,  "EPROTONOSUPPORT",  "Protocol not supported" },
	{ EPROTOTYPE,       "EPROTOTYPE",       "Protocol wrong type for socket" },
	{ ERANGE,           "ERANGE",           "Result too large" },
	{ EROFS,            "EROFS",            "Read-only file system" },
	{ ESPIPE,           "ESPIPE",           "Invalid seek" },
	{ ESRCH,            "ESRCH",            "No such process" },
	{ ETIME,            "ETIME",            "Stream ioctl() timeout" },
	{ ETIMEDOUT,        "ETIMEDOUT",        "Connection timed out" },
	{ ETXTBSY,          "ETXTBSY",          "Text file busy" },
	{ EWOULDBLOCK,      "EWOULDBLOCK",      "Operation would block" },
	{ EXDEV,            "EXDEV",            "Cross-device link" },
#endif
	{ 0, NULL, NULL }
};



#ifndef STRERROR_BUFFERSIZE
#define STRERROR_BUFFERSIZE	(512)
#endif
#ifndef STRERROR_THREADSAFE
#define STRERROR_THREADSAFE	FALSE
#endif

/*
// windows sockets
	int error_wsa = WSAGetLastError();
	DWORD len = FormatMessageA(
		SF_MESSAGE_ARGUMENT_ARRAY |
		SF_MESSAGE_FROM_SYSTEM |
		SF_MESSAGE_IGNORE_INSERTS,
		NULL, error_wsa, 0, result, STRERROR_BUFFERSIZE, NULL);
	if (len)
		buffer[len] = '\0';
	else
		sprintf(result, "Error: %d", error_wsa);
*/



t_char const*	Error_STD_Message(t_errno error)
{
#if STRERROR_THREADSAFE
	t_char	buffer[STRERROR_BUFFERSIZE] = {0};
	#ifdef __WINDOWS__
	strerror_s(buffer, STRERROR_BUFFERSIZE, error);
	#else
	strerror_r(error, buffer, STRERROR_BUFFERSIZE);
	#endif
	return (buffer);
#else
	t_char const*	result = strerror(error);
	if (result == NULL)
	{
		for (t_errno i = 0; i < ENUMLENGTH_STDERROR; ++i)
		{
			if (Error_STD[i].code == error)
			{
				result = Error_STD[i].message;
				break;
			}
		}
	}
	return (result);
#endif
}
_INLINE()
t_char*		Error_STD_GetMessage(t_errno error)
{
	return (String_Duplicate(Error_STD_Message(error)));
}



t_char const*	Error_STD_Name(t_errno error)
{
	if (error == ERROR_NONE)
		return ("");
	for (t_errno i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (Error_STD[i].code == error)
		{
			return (Error_STD[i].name);
		}
	}
	return (NULL);
}
_INLINE()
t_char*		Error_STD_GetName(t_errno error)
{
	return (String_Duplicate(Error_STD_Name(error)));
}



t_errno		Error_STD_Code(t_char const* name)
{
	if CCCERROR((name == NULL), ERROR_NULLPOINTER, "error name given is NULL")
		return (ERROR);
	if (name[0] == '\0') // empty string
		return (ERROR_NONE);
	for (t_errno i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (String_Equals(Error_STD[i].name, name))
		{
			return (Error_STD[i].code);
		}
	}
	return (ERROR);
}



_INLINE()
t_errno	Error_STD_Get(void)
{
	return (errno);
}

_INLINE()
t_errno	Error_STD_Set(t_errno error)
{
	errno = error;
	return (errno);
}
