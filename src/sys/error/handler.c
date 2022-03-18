
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/format.h"
#include "libccc/sys/io.h"
#include "libccc/sys/error.h"

#include LIBCONFIG_ERROR_INCLUDE



static s_ccchandler	Error_Handlers[ENUMLENGTH_CCCERROR] =
{
	{ ERROR_UNSPECIFIED,  Error_Handler },

	{ ERROR_SYSTEM,       Error_Handler },
	{ ERROR_ALLOCFAILURE, Error_Handler },

	{ ERROR_PARSE,        Error_Handler },
	{ ERROR_PRINT,        Error_Handler },
	{ ERROR_NOTFOUND,     Error_Handler },

	{ ERROR_INVALIDARGS,  Error_Handler },
	{ ERROR_NULLPOINTER,  Error_Handler },
	{ ERROR_MATHDOMAIN,   Error_Handler },
	{ ERROR_RESULTRANGE,  Error_Handler },
	{ ERROR_NANARGUMENT,  Error_Handler },
	{ ERROR_ILLEGALBYTES, Error_Handler },
	{ ERROR_INVALIDENUM,  Error_Handler },
	{ ERROR_INVALIDRANGE, Error_Handler },
	{ ERROR_INDEX2SMALL,  Error_Handler },
	{ ERROR_INDEX2LARGE,  Error_Handler },
	{ ERROR_LENGTH2SMALL, Error_Handler },
	{ ERROR_LENGTH2LARGE, Error_Handler },
	{ ERROR_KEYNOTFOUND,  Error_Handler },
	{ ERROR_WRONGTYPE,    Error_Handler },
	{ ERROR_DELETEREF,    Error_Handler },
};



void	Error_Handle(e_cccerror error, t_char const* funcname, t_char* message)
{
	f_ccchandler	handler;

	handler = Error_GetHandler(error);
	if (handler)
	{
		handler(error, funcname, message);
		String_Delete(&message);
	}
}



void	Error_Handler(e_cccerror error, t_char const* funcname, t_char const* message)
{
	if (!error && (message == NULL || funcname == NULL))
		return;
	LIBCONFIG_ERROR_DEFAULTHANDLER(error, funcname, message)
}



f_ccchandler	Error_GetHandler(e_cccerror error)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (Error_Handlers[i].code == error)
		{
			return (Error_Handlers[i].handler);
		}
	}
	return (NULL);
}

void	Error_SetHandler(e_cccerror error, f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (Error_Handlers[i].code == error)
		{
			Error_Handlers[i].handler = handler;
			return;
		}
	}
}

void	Error_SetAllHandlers(f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_Handlers[i].handler = handler;
	}
}
