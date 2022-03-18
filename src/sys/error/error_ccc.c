
#include "libccc.h"
#include "libccc/memory.h"

#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	extern	int*	errno(void);
	#define errno	(*errno())
	#endif
#endif

#include "libccc/string.h"
#include "libccc/format.h"
#include "libccc/sys/io.h"
#include "libccc/sys/error.h"

#include LIBCONFIG_ERROR_INCLUDE



s_error_info	Error_CCC[ENUMLENGTH_CCCERROR] =
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



t_char const*	Error_CCC_Message(e_cccerror error)
{
	if (error == ERROR_NONE)
		return ("");
	if (error == ERROR_SYSTEM)
		return (Error_STD_Message(errno));
	for (e_cccerror i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (Error_CCC[i].code == error)
		{
			return (Error_CCC[i].message);
		}
	}
	return (NULL);
}
inline
t_char*			Error_CCC_GetMessage(e_cccerror error)
{
	return (String_Duplicate(Error_CCC_Message(error)));
}



t_char const*	Error_CCC_Name(e_cccerror error)
{
	if (error == ERROR_NONE)
		return ("");
	for (e_cccerror i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (Error_CCC[i].code == error)
		{
			return (Error_CCC[i].name);
		}
	}
	return (NULL);
}
inline
t_char*			Error_CCC_GetName(e_cccerror error)
{
	return (String_Duplicate(Error_CCC_Name(error)));
}



e_cccerror		Error_CCC_Code(t_char const* name)
{
	HANDLE_ERROR(NULLPOINTER, (name == NULL), return (ERROR_UNSPECIFIED);)
	if (name[0] == '\0') // empty string
		return (ERROR_NONE);
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (String_Equals(Error_CCC[i].name, name))
		{
			return (Error_CCC[i].code);
		}
	}
	return (ERROR_UNSPECIFIED);
}



e_cccerror		LastError = OK; // TODO figure out a way to not use any global state ?

//! TODO using `&errno`, a thread-safe pseudo-global (a list of globals)

inline
e_cccerror	Error_CCC_Get(void)
{
	return (LastError);
}

inline
e_cccerror	Error_CCC_Set(e_cccerror error)
{
	LastError = error;
	return (error);
}
