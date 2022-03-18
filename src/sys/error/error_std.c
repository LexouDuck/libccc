
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



s_error_info	Error_STD[ENUMLENGTH_STDERROR] =
{
	{ Error_Handler, E2BIG,            "E2BIG",            "Argument list too long" },
	{ Error_Handler, EACCES,           "EACCES",           "Permission denied" },
	{ Error_Handler, EADDRINUSE,       "EADDRINUSE",       "Address in use" },
	{ Error_Handler, EADDRNOTAVAIL,    "EADDRNOTAVAIL",    "Address not available" },
	{ Error_Handler, EAFNOSUPPORT,     "EAFNOSUPPORT",     "Address family not supported" },
	{ Error_Handler, EAGAIN,           "EAGAIN",           "Resource unavailable, try again" },
	{ Error_Handler, EALREADY,         "EALREADY",         "Connection already in progress" },
	{ Error_Handler, EBADF,            "EBADF",            "Bad file descriptor" },
	{ Error_Handler, EBADMSG,          "EBADMSG",          "Bad message" },
	{ Error_Handler, EBUSY,            "EBUSY",            "Device or resource busy" },
	{ Error_Handler, ECANCELED,        "ECANCELED",        "Operation canceled" },
	{ Error_Handler, ECHILD,           "ECHILD",           "No child processes" },
	{ Error_Handler, ECONNABORTED,     "ECONNABORTED",     "Connection aborted" },
	{ Error_Handler, ECONNREFUSED,     "ECONNREFUSED",     "Connection refused" },
	{ Error_Handler, ECONNRESET,       "ECONNRESET",       "Connection reset" },
	{ Error_Handler, EDEADLK,          "EDEADLK",          "Resource deadlock would occur" },
	{ Error_Handler, EDESTADDRREQ,     "EDESTADDRREQ",     "Destination address required" },
	{ Error_Handler, EDOM,             "EDOM",             "Mathematics argument out of domain of function" },
	{ Error_Handler, EEXIST,           "EEXIST",           "File exists" },
	{ Error_Handler, EFAULT,           "EFAULT",           "Bad address" },
	{ Error_Handler, EFBIG,            "EFBIG",            "File too large" },
	{ Error_Handler, EHOSTUNREACH,     "EHOSTUNREACH",     "Host is unreachable" },
	{ Error_Handler, EIDRM,            "EIDRM",            "Identifier removed" },
	{ Error_Handler, EILSEQ,           "EILSEQ",           "Illegal byte sequence" },
	{ Error_Handler, EINPROGRESS,      "EINPROGRESS",      "Operation in progress" },
	{ Error_Handler, EINTR,            "EINTR",            "Interrupted function" },
	{ Error_Handler, EINVAL,           "EINVAL",           "Invalid argument" },
	{ Error_Handler, EIO,              "EIO",              "I/O error" },
	{ Error_Handler, EISCONN,          "EISCONN",          "Socket is connected" },
	{ Error_Handler, EISDIR,           "EISDIR",           "Is a directory" },
	{ Error_Handler, ELOOP,            "ELOOP",            "Too many levels of symbolic links" },
	{ Error_Handler, EMFILE,           "EMFILE",           "File descriptor value too large" },
	{ Error_Handler, EMLINK,           "EMLINK",           "Too many links" },
	{ Error_Handler, EMSGSIZE,         "EMSGSIZE",         "Message too large" },
	{ Error_Handler, ENAMETOOLONG,     "ENAMETOOLONG",     "Filename too long" },
	{ Error_Handler, ENETDOWN,         "ENETDOWN",         "Network is down" },
	{ Error_Handler, ENETRESET,        "ENETRESET",        "Connection aborted by network" },
	{ Error_Handler, ENETUNREACH,      "ENETUNREACH",      "Network unreachable" },
	{ Error_Handler, ENFILE,           "ENFILE",           "Too many files open in system" },
	{ Error_Handler, ENOBUFS,          "ENOBUFS",          "No buffer space available" },
	{ Error_Handler, ENODATA,          "ENODATA",          "No message is available on the STREAM head read queue" },
	{ Error_Handler, ENODEV,           "ENODEV",           "No such device" },
	{ Error_Handler, ENOENT,           "ENOENT",           "No such file or directory" },
	{ Error_Handler, ENOEXEC,          "ENOEXEC",          "Executable file format error" },
	{ Error_Handler, ENOLCK,           "ENOLCK",           "No locks available" },
	{ Error_Handler, ENOLINK,          "ENOLINK",          "Link has been severed" },
	{ Error_Handler, ENOMEM,           "ENOMEM",           "Not enough space" },
	{ Error_Handler, ENOMSG,           "ENOMSG",           "No message of the desired type" },
	{ Error_Handler, ENOPROTOOPT,      "ENOPROTOOPT",      "Protocol not available" },
	{ Error_Handler, ENOSPC,           "ENOSPC",           "No space left on device" },
	{ Error_Handler, ENOSR,            "ENOSR",            "No STREAM resources" },
	{ Error_Handler, ENOSTR,           "ENOSTR",           "Not a STREAM" },
	{ Error_Handler, ENOSYS,           "ENOSYS",           "Function not supported" },
	{ Error_Handler, ENOTCONN,         "ENOTCONN",         "The socket is not connected" },
	{ Error_Handler, ENOTDIR,          "ENOTDIR",          "Not a directory" },
	{ Error_Handler, ENOTEMPTY,        "ENOTEMPTY",        "Directory not empty" },
	{ Error_Handler, ENOTRECOVERABLE,  "ENOTRECOVERABLE",  "State not recoverable" },
	{ Error_Handler, ENOTSOCK,         "ENOTSOCK",         "Not a socket" },
	{ Error_Handler, ENOTSUP,          "ENOTSUP",          "Not supported" },
	{ Error_Handler, ENOTTY,           "ENOTTY",           "Inappropriate I/O control operation" },
	{ Error_Handler, ENXIO,            "ENXIO",            "No such device or address" },
	{ Error_Handler, EOPNOTSUPP,       "EOPNOTSUPP",       "Operation not supported on socket" },
	{ Error_Handler, EOVERFLOW,        "EOVERFLOW",        "Value too large to be stored in data type" },
	{ Error_Handler, EOWNERDEAD,       "EOWNERDEAD",       "Previous owner died" },
	{ Error_Handler, EPERM,            "EPERM",            "Operation not permitted" },
	{ Error_Handler, EPIPE,            "EPIPE",            "Broken pipe" },
	{ Error_Handler, EPROTO,           "EPROTO",           "Protocol error" },
	{ Error_Handler, EPROTONOSUPPORT,  "EPROTONOSUPPORT",  "Protocol not supported" },
	{ Error_Handler, EPROTOTYPE,       "EPROTOTYPE",       "Protocol wrong type for socket" },
	{ Error_Handler, ERANGE,           "ERANGE",           "Result too large" },
	{ Error_Handler, EROFS,            "EROFS",            "Read-only file system" },
	{ Error_Handler, ESPIPE,           "ESPIPE",           "Invalid seek" },
	{ Error_Handler, ESRCH,            "ESRCH",            "No such process" },
	{ Error_Handler, ETIME,            "ETIME",            "Stream ioctl() timeout" },
	{ Error_Handler, ETIMEDOUT,        "ETIMEDOUT",        "Connection timed out" },
	{ Error_Handler, ETXTBSY,          "ETXTBSY",          "Text file busy" },
	{ Error_Handler, EWOULDBLOCK,      "EWOULDBLOCK",      "Operation would block" },
	{ Error_Handler, EXDEV,            "EXDEV",            "Cross-device link" },
	{ 0 }
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
inline
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
inline
t_char*		Error_STD_GetName(t_errno error)
{
	return (String_Duplicate(Error_STD_Name(error)));
}



t_errno		Error_STD_Code(t_char const* name)
{
	HANDLE_ERROR(NULLPOINTER, (name == NULL), return (ERROR);)
	if (name[0] == '\0') // empty string
		return (ERROR_NONE);
	for (t_uint i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (String_Equals(Error_STD[i].name, name))
		{
			return (Error_STD[i].code);
		}
	}
	return (ERROR);
}



inline
t_errno	Error_STD_Get(void)
{
	return (errno);
}

inline
t_errno	Error_STD_Set(t_errno error)
{
	errno = error;
	return (errno);
}
