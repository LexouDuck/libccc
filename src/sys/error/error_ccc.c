
#include "libccc.h"
#include "libccc/enum.h"
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

#include "libccc/format.h"
#include "libccc/sys/io.h"
#include "libccc/sys/error.h"

#include LIBCONFIG_ERROR_INCLUDE



//! Define the list of info for each libccc error code
static s_error_info	Error_CCC[ENUMLENGTH_CCCERROR] =
{
	{ ERROR_UNSPECIFIED,  "UNSPECIFIED",  "Unspecified error" },

	{ ERROR_SYSTEM,       "SYSTEM",       "System Error: `strerror(errno)` message" },
	{ ERROR_ALLOCFAILURE, "ALLOCFAILURE", "System Error: Memory allocation failure" },

	{ ERROR_PARSE,        "PARSE",        "Parse Error: " },
	{ ERROR_PRINT,        "PRINT",        "Print Error: " },
	{ ERROR_NOTFOUND,     "NOTFOUND",     "Error: could not find value" },

	{ ERROR_INVALIDARGS,  "INVALIDARGS",  "Argument Error: " },
	{ ERROR_NULLPOINTER,  "NULLPOINTER",  "Argument Error: null pointer received" },
	{ ERROR_MATHDOMAIN,   "MATHDOMAIN",   "Argument Error: mathematic out of domain error" },
	{ ERROR_RESULTRANGE,  "RESULTRANGE",  "Argument Error: result cannot be represented within limited range" },
	{ ERROR_NANARGUMENT,  "NANARGUMENT",  "Argument Error: should not receive NAN as argument" },
	{ ERROR_ILLEGALBYTES, "ILLEGALBYTES", "Argument Error: illegal byte sequence encountered" },
	{ ERROR_INVALIDENUM,  "INVALIDENUM",  "Argument Error: value given is not a valid enum item" },
	{ ERROR_INVALIDRANGE, "INVALIDRANGE", "Argument Error: range given is inverted: 'min' is larger than 'max'" },
	{ ERROR_INDEX2SMALL,  "INDEX2SMALL",  "Argument Error: index value given is too small" },
	{ ERROR_INDEX2LARGE,  "INDEX2LARGE",  "Argument Error: index value given is too large" },
	{ ERROR_LENGTH2SMALL, "LENGTH2SMALL", "Argument Error: length value given is too small" },
	{ ERROR_LENGTH2LARGE, "LENGTH2LARGE", "Argument Error: length value given is too large" },
	{ ERROR_KEYNOTFOUND,  "KEYNOTFOUND",  "Argument Error: could not find item with the given key" },
	{ ERROR_WRONGTYPE,    "WRONGTYPE",    "Argument Error: attempted to read dynamic-type item with wrong type" },
	{ ERROR_DELETEREF,    "DELETEREF",    "Argument Error: attempted to free an area of constant memory" },
};



t_char const*	Error_CCC_Message(e_cccerror error)
{
	if (error == ERROR_NONE)
		return ("");
	if (error == ERROR_SYSTEM)
		return (Error_STD_Message(errno));
	for (t_enum i = 0; (e_cccerror)i < ENUMLENGTH_CCCERROR; ++i)
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
	for (t_enum i = 0; (e_cccerror)i < ENUMLENGTH_CCCERROR; ++i)
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
	for (t_enum i = 0; (e_cccerror)i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (String_Equals(Error_CCC[i].name, name))
		{
			return ((e_cccerror)Error_CCC[i].code);
		}
	}
	return (ERROR_UNSPECIFIED);
}



e_cccerror		LastError = ERROR_NONE; // TODO figure out a way to not use any global state ?

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
