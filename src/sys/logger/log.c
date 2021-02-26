
#include <stdarg.h>

#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"


#define LOGONE_FUNCTION_CONTENT(VERBOSE_ONLY, IS_ERROR, USE_ERRNO, PREFIX, PREFIX_COLOR) \
	t_io_error	result;							\
	va_list		args;							\
												\
	va_start(args, format_str);					\
	result = Log_VA(logger,						\
		VERBOSE_ONLY, IS_ERROR, USE_ERRNO,		\
		PREFIX, PREFIX_COLOR,					\
		format_str, args);						\
	va_end(args);								\
	return (result);							\


#define LOGALL_FUNCTION_CONTENT(VERBOSE_ONLY, IS_ERROR, USE_ERRNO, PREFIX, PREFIX_COLOR) \
	t_io_error	result;							\
	va_list		args;							\
												\
	for (t_u32 i = 0; loggers[i]; ++i)			\
	{ 											\
		va_start(args, format_str);				\
		result = Log_VA(loggers[i],				\
		VERBOSE_ONLY, IS_ERROR, USE_ERRNO,		\
		PREFIX, PREFIX_COLOR,					\
			format_str, args);					\
		va_end(args);							\
	} 											\
	return (result);							\


t_io_error	LogAll(t_logptrarr const loggers,
	t_bool verbose_only,
	t_bool is_error,
	t_bool use_errno,
	char const* format_str, ...)
{
	LOGALL_FUNCTION_CONTENT(verbose_only, is_error, use_errno, "", NULL)
}



//! To be called when there is an error which does not use errno
t_io_error	Log_Error				(s_logger const* logger, int error_code, char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE, error_code,    "Error", C_RED)    }
//! To be called when there is an error that sets errno
t_io_error	Log_Error_IO			(s_logger const* logger, int error_code, char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE,  TRUE, error_code, "IO Error", C_RED)    }
//! To be called when there is an important warning to show to the user
t_io_error	Log_Warning				(s_logger const* logger,                 char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Warning", C_YELLOW) }
//! To be called when there is an successful operation (or result) to notify the user of
t_io_error	Log_Success				(s_logger const* logger,                 char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Success", C_GREEN)  }
//! To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
t_io_error	Log_Message				(s_logger const* logger,                 char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT(FALSE, FALSE,          0,         "", NULL)     }
//! To be called when there is "verbose" data to be logged
t_io_error	Log_Message_Verbose		(s_logger const* logger,                 char const* format_str, ...)		{ LOGONE_FUNCTION_CONTENT( TRUE, FALSE,          0,         "", NULL)     }


//! To be called when there is an error which does not use errno
t_io_error	LogAll_Error			(t_logptrarr const loggers, int error_code, char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE, error_code,    "Error", C_RED)    }
//! To be called when there is an error that sets errno
t_io_error	LogAll_Error_IO			(t_logptrarr const loggers, int error_code, char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE,  TRUE, error_code, "IO Error", C_RED)    }
// To be called when there is an important warning to show to the user
t_io_error	LogAll_Warning			(t_logptrarr const loggers,                 char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Warning", C_YELLOW) }
// To be called when there is an successful operation (or result) to notify the user of
t_io_error	LogAll_Success			(t_logptrarr const loggers,                 char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,  "Success", C_GREEN)  }
// To be called when there is user-useful data to be logged (operation successful with value X returned, etc)
t_io_error	LogAll_Message			(t_logptrarr const loggers,                 char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT(FALSE, FALSE,          0,         "", NULL)     }
// To be called when there is "verbose" data to be logged
t_io_error	LogAll_Message_Verbose	(t_logptrarr const loggers,                 char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT( TRUE, FALSE,          0,         "", NULL)     }