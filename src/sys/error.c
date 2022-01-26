
#include "libccc/memory.h"

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

#include "libccc.h"
#include "libccc/string.h"
#include "libccc/format.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



#define BUFFERSIZE_STRERROR	(512)



t_char*	Error_STDC(int errno_value)
{
	t_char	buffer[BUFFERSIZE_STRERROR] = {0};

#ifdef _WIN32
/*
// windows sockets
	int error = WSAGetLastError();
	DWORD len = FormatMessageA(
		SF_MESSAGE_ARGUMENT_ARRAY |
		SF_MESSAGE_FROM_SYSTEM |
		SF_MESSAGE_IGNORE_INSERTS,
		NULL, error, 0, result, BUFFERSIZE_STRERROR, NULL);
	if (len)
		buffer[len] = '\0';
	else
		sprintf(result, "Error: %d", error);
*/
	strerror_s(buffer, BUFFERSIZE_STRERROR, errno_value);
#else
	strerror_r(errno_value, buffer, BUFFERSIZE_STRERROR);
#endif
	return (String_Duplicate(buffer));
}



e_cccerror		LastError = OK; // TODO figure out a way to not use any global state ?

//! TODO using `&errno`, a thread-safe pseudo-global (a list of globals)

inline
e_cccerror	Error_Get(void)
{
	return (LastError);
}

inline
e_cccerror	Error_Set(e_cccerror error)
{
	LastError = error;
	return (error);
}



typedef struct cccerror_info
{
	f_ccchandler	handler;
	e_cccerror		code;
	t_char const*	name;
	t_char const*	message;
}			s_cccerror_info;

static s_cccerror_info	cccerrors[ENUMLENGTH_CCCERROR] =
{
	{ Error_Handler, ERROR_UNSPECIFIED,  "UNSPECIFIED",  "Unspecified error" },

	{ Error_Handler, ERROR_SYSTEM,       "SYSTEM",       "System Error: `strerror(errno)` message" },
	{ Error_Handler, ERROR_ALLOCFAILURE, "ALLOCFAILURE", "System Error: Memory allocation failure" },

	{ Error_Handler, ERROR_PARSE,        "PARSE",        "Parse Error" },
	{ Error_Handler, ERROR_PRINT,        "PRINT",        "Print Error" },
	{ Error_Handler, ERROR_NOTFOUND,     "NOTFOUND",     "Error: could not find value" },

	{ Error_Handler, ERROR_INVALIDARGS,  "INVALIDARGS",  "Argument Error" },
	{ Error_Handler, ERROR_NULLPOINTER,  "NULLPOINTER",  "Argument Error: null pointer received" },
	{ Error_Handler, ERROR_MATHDOMAIN,   "MATHDOMAIN",   "Argument Error: mathematic out of domain error" },
	{ Error_Handler, ERROR_RESULTRANGE,  "RESULTRANGE",  "Argument Error: result cannot be represented within limited range" },
	{ Error_Handler, ERROR_NANARGUMENT,  "NANARGUMENT",  "Argument Error: should not receive NAN as argument" },
	{ Error_Handler, ERROR_ILLEGALBYTES, "ILLEGALBYTES", "Argument Error: illegal byte sequence encountered" },
	{ Error_Handler, ERROR_INVALIDENUM,  "INVALIDENUM",  "Argument Error: value given is not a valid enum item" },
	{ Error_Handler, ERROR_INVALIDRANGE, "INVALIDRANGE", "Argument Error: range given is inverted: 'min' is larger than 'max'" },
	{ Error_Handler, ERROR_INDEX2SMALL,  "INDEX2SMALL",  "Argument Error: index value given is too small" },
	{ Error_Handler, ERROR_INDEX2LARGE,  "INDEX2LARGE",  "Argument Error: index value given is too large" },
	{ Error_Handler, ERROR_LENGTH2SMALL, "LENGTH2SMALL", "Argument Error: length value given is too small" },
	{ Error_Handler, ERROR_LENGTH2LARGE, "LENGTH2LARGE", "Argument Error: length value given is too large" },
	{ Error_Handler, ERROR_KEYNOTFOUND,  "KEYNOTFOUND",  "Argument Error: could not find item with the given key" },
	{ Error_Handler, ERROR_WRONGTYPE,    "WRONGTYPE",    "Argument Error: attempted to read dynamic-type item with wrong type" },
	{ Error_Handler, ERROR_DELETEREF,    "DELETEREF",    "Argument Error: attempted to free an area of constant memory" },
};



t_char*		Error_GetMessage(e_cccerror error)
{
	if (error == ERROR_NONE)
		return (String_Duplicate(""));
	if (error == ERROR_SYSTEM)
		return (Error_STDC(errno));
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (cccerrors[i].code == error)
			return (String_Duplicate(cccerrors[i].message));
	}
	return (NULL);
}



t_char*		Error_GetName(e_cccerror error)
{
	if (error == ERROR_NONE)
		return (String_Duplicate(""));
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (cccerrors[i].code == error)
			return (String_Duplicate(cccerrors[i].name));
	}
	return (NULL);
}



e_cccerror	Error_GetCode(t_char const* name)
{
	HANDLE_ERROR(NULLPOINTER, (name == NULL), return (ERROR_UNSPECIFIED);)
	if (name[0] == '\0') // empty string
		return (ERROR_NONE);
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (String_Equals(cccerrors[i].name, name))
			return (cccerrors[i].code);
	}
	return (ERROR_UNSPECIFIED);
}



void	Error_Handle(e_cccerror error, t_char const* funcname, t_char* message)
{
	f_ccchandler	handler;
	t_char*			tmp;
	t_char*			error_msg;

	handler = Error_GetHandler(error);
	if (handler)
	{
		error_msg = Error_GetMessage(error);
		if (message) { tmp = String_Format("%s -> %s%s",  funcname, error_msg, message); }
		else         { tmp = String_Format("%s -> %s",    funcname, error_msg);          }
		handler(error, tmp);
		String_Delete(&error_msg);
		String_Delete(&tmp);
		String_Delete(&message);
	}
}



void	Error_Handler(e_cccerror error, t_char const* message)
{
	if (!error && message == NULL)
		return;
	LIBCONFIG_ERROR_DEFAULTHANDLER(error, message)
}



f_ccchandler	Error_GetHandler(e_cccerror error)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (cccerrors[i].code == error)
			return (cccerrors[i].handler);
	}
	return (NULL);
}

void			Error_SetHandler(e_cccerror error, f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (cccerrors[i].code == error)
		{
			cccerrors[i].handler = handler;
			return;
		}
	}
}

void			Error_SetAllHandlers(f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		cccerrors[i].handler = handler;
	}
}
