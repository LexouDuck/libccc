
#include "libccc.h"
#include "libccc/enum.h"

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

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	   Log_Error(s_logger const* logger, t_char const* error, t_char const* format_str, ...)
{
	LOGONE_FUNCTION_CONTENT((logger->silence_errors), OK, error, LOGPREFIX_ERROR, IO_COLOR_FG_RED)
}
e_cccerror	LogAll_Error(t_logptrarr const loggers, t_char const* error, t_char const* format_str, ...)
{
	LOGALL_FUNCTION_CONTENT((logger->silence_errors), OK, error, LOGPREFIX_ERROR, IO_COLOR_FG_RED)
}

e_cccerror	   Log_Error_STD(s_logger    const* logger, t_errno error, t_char const* format_str, ...)
{
	t_char const* errorname = Error_STD_Name(error);
	t_char const* error_msg = Error_STD_Message(error);
	t_char* prefix = String_Format(LOGPREFIX_ERROR"[STD:%d:%s]", error, errorname);
	LOGONE_FUNCTION_CONTENT((logger->silence_errors), error, error_msg, prefix, IO_COLOR_FG_RED)
	String_Delete(&prefix);
}
e_cccerror	LogAll_Error_STD(t_logptrarr const loggers, t_errno error, t_char const* format_str, ...)
{
	t_char const* errorname = Error_STD_Name(error);
	t_char const* error_msg = Error_STD_Message(error);
	t_char* prefix = String_Format(LOGPREFIX_ERROR"[STD:%d:%s]", error, errorname);
	LOGALL_FUNCTION_CONTENT((logger->silence_errors), error, error_msg, prefix, IO_COLOR_FG_RED)
	String_Delete(&prefix);
}

e_cccerror	   Log_Error_CCC(s_logger    const* logger, e_cccerror error, t_char const* format_str, ...)
{
	t_char const* errorname = Error_CCC_Name(error);
	t_char const* error_msg = Error_CCC_Message(error);
	t_char* prefix = String_Format(LOGPREFIX_ERROR"[CCC:%d:%s]", error, errorname);
	LOGONE_FUNCTION_CONTENT((logger->silence_errors), error, error_msg, prefix, IO_COLOR_FG_RED)
	String_Delete(&prefix);
}
e_cccerror	LogAll_Error_CCC(t_logptrarr const loggers, e_cccerror error, t_char const* format_str, ...)
{
	t_char const* errorname = Error_CCC_Name(error);
	t_char const* error_msg = Error_CCC_Message(error);
	t_char* prefix = String_Format(LOGPREFIX_ERROR"[CCC:%d:%s]", error, errorname);
	LOGALL_FUNCTION_CONTENT((logger->silence_errors), error, error_msg, prefix, IO_COLOR_FG_RED)
	String_Delete(&prefix);
}

e_cccerror	   Log_Failure(s_logger    const* logger, t_char const* format_str, ...)	{ LOGONE_FUNCTION_CONTENT((logger->silence_errors), OK, NULL, LOGPREFIX_FAILURE, IO_COLOR_FG_RED)    }
e_cccerror	LogAll_Failure(t_logptrarr const loggers, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT((logger->silence_errors), OK, NULL, LOGPREFIX_FAILURE, IO_COLOR_FG_RED)    }
e_cccerror	   Log_Warning(s_logger    const* logger, t_char const* format_str, ...)	{ LOGONE_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_WARNING, IO_COLOR_FG_YELLOW) }
e_cccerror	LogAll_Warning(t_logptrarr const loggers, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_WARNING, IO_COLOR_FG_YELLOW) }
e_cccerror	   Log_Success(s_logger    const* logger, t_char const* format_str, ...)	{ LOGONE_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_SUCCESS, IO_COLOR_FG_GREEN)  }
e_cccerror	LogAll_Success(t_logptrarr const loggers, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_SUCCESS, IO_COLOR_FG_GREEN)  }
e_cccerror	   Log_Message(s_logger    const* logger, t_char const* format_str, ...)	{ LOGONE_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_MESSAGE, IO_COLOR_FG_BLUE)   }
e_cccerror	LogAll_Message(t_logptrarr const loggers, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT((logger->silence_logs),   OK, NULL, LOGPREFIX_MESSAGE, IO_COLOR_FG_BLUE)   }
e_cccerror	   Log_Verbose(s_logger    const* logger, t_char const* format_str, ...)	{ LOGONE_FUNCTION_CONTENT((!logger->verbose),       OK, NULL, LOGPREFIX_VERBOSE, IO_COLOR_FG_BLUE)   }
e_cccerror	LogAll_Verbose(t_logptrarr const loggers, t_char const* format_str, ...)	{ LOGALL_FUNCTION_CONTENT((!logger->verbose),       OK, NULL, LOGPREFIX_VERBOSE, IO_COLOR_FG_BLUE)   }

