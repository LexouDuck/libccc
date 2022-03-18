
#include "libccc.h"
#include "libccc/string.h"
#include "libccc/format.h"
#include "libccc/sys/io.h"
#include "libccc/sys/error.h"

#include LIBCONFIG_ERROR_INCLUDE



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
		if (Error_CCC[i].code == error)
		{
			return (Error_CCC[i].handler);
		}
	}
	return (NULL);
}

void	Error_SetHandler(e_cccerror error, f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		if (Error_CCC[i].code == error)
		{
			Error_CCC[i].handler = handler;
			return;
		}
	}
}

void	Error_SetAllHandlers(f_ccchandler handler)
{
	for (t_uint i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_CCC[i].handler = handler;
	}
}
