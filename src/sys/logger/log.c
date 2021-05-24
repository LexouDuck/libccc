
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"

#include LIBCONFIG_HANDLE_INCLUDE

/*

e_stderror	LogAll(t_logptrarr const loggers,
	t_bool verbose_only,
	t_bool is_error,
	t_bool use_errno,
	t_char const* format_str, ...)
{
	LOGALL_FUNCTION_CONTENT(verbose_only, is_error, use_errno, "", NULL)
}

*/

//! To be called when there is an error which does not use errno
e_stderror	Log_Error				(s_logger const* logger, int error_code, t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE, error_code,    "Error", C_RED)    }
//! To be called when there is an error that sets errno
e_stderror	Log_Error_IO			(s_logger const* logger, int error_code, t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE,  TRUE, error_code, "IO Error", C_RED)    }
//! To be called when there is an important warning to show to the user
e_stderror	Log_Warning				(s_logger const* logger,                 t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Warning", C_YELLOW) }
//! To be called when there is an successful operation (or result) to notify the user of
e_stderror	Log_Success				(s_logger const* logger,                 t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Success", C_GREEN)  }
//! To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
e_stderror	Log_Message				(s_logger const* logger,                 t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,         "", NULL)     }
//! To be called when there is "verbose" data to be logged
e_stderror	Log_Message_Verbose		(s_logger const* logger,                 t_char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT( TRUE, FALSE,          0,         "", NULL)     }

//! To be called when there is an error which does not use errno
e_stderror	LogAll_Error			(t_logptrarr const loggers, int error_code, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE, error_code,    "Error", C_RED)    }
//! To be called when there is an error that sets errno
e_stderror	LogAll_Error_IO			(t_logptrarr const loggers, int error_code, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE,  TRUE, error_code, "IO Error", C_RED)    }
// To be called when there is an important warning to show to the user
e_stderror	LogAll_Warning			(t_logptrarr const loggers,                 t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Warning", C_YELLOW) }
// To be called when there is an successful operation (or result) to notify the user of
e_stderror	LogAll_Success			(t_logptrarr const loggers,                 t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Success", C_GREEN)  }
// To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
e_stderror	LogAll_Message			(t_logptrarr const loggers,                 t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,         "", NULL)     }
// To be called when there is "verbose" data to be logged
e_stderror	LogAll_Message_Verbose	(t_logptrarr const loggers,                 t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT( TRUE, FALSE,          0,         "", NULL)     }
