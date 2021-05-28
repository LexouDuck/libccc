
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/format.h"

#include LIBCONFIG_HANDLE_INCLUDE



e_stderror		LastError = OK; // TODO figure out a way to not use any global state ?

//! TODO using `&errno`, a thread-safe pseudo-global (a list of globals)

inline
e_stderror	Error_Get(void)
{
	return (LastError);
}

inline
e_stderror	Error_Set(e_stderror error)
{
	LastError = error;
	return (error);
}



typedef struct stderror_info
{
	e_stderror		code;
	t_char const*	name;
	t_char const*	message;
}			s_stderror_info;

static s_stderror_info	stderrors[ENUMLENGTH_STDERROR] =
{
	{ ERROR_UNSPECIFIED,  "ERROR_UNSPECIFIED",  "Unspecified error" },

	{ ERROR_SYSTEM,       "ERROR_SYSTEM",       "System Error: `strerror(errno)` message" },
	{ ERROR_ALLOCFAILURE, "ERROR_ALLOCFAILURE", "System Error: Memory allocation failure" },

	{ ERROR_INVALIDARGS,  "ERROR_INVALIDARGS",  "Argument Error" },
	{ ERROR_NULLPOINTER,  "ERROR_NULLPOINTER",  "Argument Error: null pointer received" },
	{ ERROR_MATHDOMAIN,   "ERROR_MATHDOMAIN",   "Argument Error: mathematic out of domain error" },
	{ ERROR_RESULTRANGE,  "ERROR_RESULTRANGE",  "Argument Error: result cannot be represented within limited range" },
	{ ERROR_NANARGUMENT,  "ERROR_NANARGUMENT",  "Argument Error: should not receive NAN as argument" },
	{ ERROR_ILLEGALBYTES, "ERROR_ILLEGALBYTES", "Argument Error: illegal byte sequence encountered" },
	{ ERROR_INVALIDENUM,  "ERROR_INVALIDENUM",  "Argument Error: value given is not a valid enum item" },
	{ ERROR_INDEX2SMALL,  "ERROR_INDEX2SMALL",  "Argument Error: index value given is too small" },
	{ ERROR_INDEX2LARGE,  "ERROR_INDEX2LARGE",  "Argument Error: index value given is too large" },
	{ ERROR_LENGTH2SMALL, "ERROR_LENGTH2SMALL", "Argument Error: length value given is too small" },
	{ ERROR_LENGTH2LARGE, "ERROR_LENGTH2LARGE", "Argument Error: length value given is too large" },
	{ ERROR_KEYNOTFOUND,  "ERROR_KEYNOTFOUND",  "Argument Error: could not find item with the given key" },
	{ ERROR_WRONGTYPE,    "ERROR_WRONGTYPE",    "Argument Error: attempted to read dynamic-type item with wrong type" },
	{ ERROR_DELETEREF,    "ERROR_DELETEREF",    "Argument Error: attempted to free an area of constant memory" },

	{ ERROR_PARSE,        "ERROR_PARSE",        "Error: while attempting to parse string" },
	{ ERROR_PRINT,        "ERROR_PRINT",        "Error: while attempting to print string" },
};



t_char const*	Error_GetMessage(e_stderror error)
{
	if (error == ERROR_NONE)
		return ("");
	for (t_uint i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (stderrors[i].code == error)
			return (stderrors[i].message);
	}
	return (NULL);
}

t_char const*	Error_GetName(e_stderror error)
{
	if (error == ERROR_NONE)
		return ("");
	for (t_uint i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (stderrors[i].code == error)
			return (stderrors[i].name);
	}
	return (NULL);
}

e_stderror		Error_GetCode(t_char const* name)
{
	HANDLE_ERROR(NULLPOINTER, (name == NULL), return (ERROR_UNSPECIFIED);)
	if (name[0] == '\0') // empty string
		return (ERROR_NONE);
	for (t_uint i = 0; i < ENUMLENGTH_STDERROR; ++i)
	{
		if (String_Equals(stderrors[i].name, name))
			return (stderrors[i].code);
	}
	return (ERROR_UNSPECIFIED);
}
