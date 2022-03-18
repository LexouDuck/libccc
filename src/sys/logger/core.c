
#ifndef __NOSTD__
	#include <errno.h>
#else
	#ifndef	errno
	extern	int*	errno(void);
	#define errno	(*errno())
	#endif
#endif
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l)	__builtin_va_start(v,l)
	#define va_end(v)		__builtin_va_end(v)
	#define va_arg(v,l)		__builtin_va_arg(v,l)
	#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/time.h"
#include "libccc/sys/logger.h"

#include LIBCONFIG_ERROR_INCLUDE



static
void	Log_Logger_FatalError(s_logger const* logger, t_char const* output)
{
	t_char*	tmp = String_Concat("Could not write log message to ", output);
//	HANDLE_ERROR(ALLOCFAILURE, (tmp == NULL), return;)
	if (tmp == NULL)
		Log_Fatal(logger, "Could not write log message: allocation failure");
	else Log_Fatal(logger, tmp);
	String_Delete(&tmp);
}



static
void	Log_Logger_ErrorHandler(e_cccerror error, t_char const* funcname, t_char const* message)
{
	t_char*	tmp;
	if (funcname)
		tmp = String_Format("%s -> %s", funcname, message);
	else
		tmp = String_Duplicate(message);
	Log_Fatal(NULL, tmp);
	if (error == ERROR_SYSTEM)
	{
		Log_Fatal(NULL, Error_STD_Message(error));
	}
	String_Delete(&tmp);
}



e_cccerror 	Log(s_logger const* logger,
	t_char const* message,
	t_char const* format, ...)
{
	e_cccerror result;
	va_list args;
	va_start(args, format);
	result = Log_VA(logger,
		OK,
		NULL,
		NULL,
		message,
		format,
		args);
	va_end(args);
	return (result);
}



e_cccerror 	Log_Custom(s_logger const* logger,
	int				error_code,
	t_char const*	prefix,
	t_char const*	prefix_color,
	t_char const*	suffix,
	t_char const*	format, ...)
{
	e_cccerror result;
	va_list args;
	va_start(args, format);
	result = Log_VA(logger,
		error_code,
		prefix,
		prefix_color,
		suffix,
		format,
		args);
	va_end(args);
	return (result);
}



e_cccerror	Log_VA(s_logger const* logger,
	int				error_code,
	t_char const*	prefix,
	t_char const*	prefix_color,
	t_char const*	suffix,
	t_char const*	format,
	va_list			args)
{
	t_char*	timestamp  = NULL;
	t_char* prefix_str = NULL;
	t_char* suffix_str = NULL;
	t_char*	log_fmt = NULL;
	t_char*	log_msg = NULL;
	t_size length;
	f_ccchandler handlers[ENUMLENGTH_CCCERROR] = {0};

	if (logger == NULL)
	{
		Log_Fatal(logger, "Log_VA() received NULL logger struct argument");
		return (ERROR_NULLPOINTER);
	}
	if (format == NULL)
	{
		Log_Fatal(logger, "Log_VA() received NULL format string argument");
		return (ERROR_NULLPOINTER);
	}

	// temporarily disable error-handling to avoid any infinite recursion
	for (e_cccerror i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		handlers[i] = Error_GetHandler(i);
	}
	Error_SetAllHandlers(Log_Logger_ErrorHandler);

	if (logger->timestamp)
	{
		timestamp = Logger_GetTimestamp(Time_Now());
	}
	// construct log prefix string, according to current config
	if (prefix && prefix[0] != '\0')
	{
		if (prefix_color && logger->format == LOGFORMAT_ANSI)
			prefix_str = String_Format("%s%s"C_RESET": ", prefix_color, prefix);
		else
			prefix_str = String_Format("%s: ", prefix);
	}
	// construct log suffix string, according to current config
	if (suffix && suffix[0] != '\0')
	{
		suffix_str = String_Format("\n -> %s", suffix);
	}

	if (logger->format == LOGFORMAT_JSON)
	{
		t_char* message_str = NULL;
		message_str = String_Format("%s%s%s",
			(prefix_str ? prefix_str : ""),
			format,
			(suffix_str ? suffix_str : ""));
		if (message_str == NULL)
		{
			Log_Fatal(logger, "Could not construct log message");
			goto failure;
		}
		else
		{
			t_char* tmp = message_str;
//			Error_SetAllHandlers(NULL);
			message_str = String_ToEscape(message_str, "");
//			Error_SetAllHandlers(Log_Logger_ErrorHandler);
			String_Delete(&tmp);
		}
		if (logger->timestamp)
		{
			t_char* tmp = timestamp;
			timestamp = String_Format("    \"timestamp\": \"%s\",\n", timestamp);
			String_Delete(&tmp);
		}
		t_char* status_str = NULL;
		if (error_code)
		{
			status_str = String_Format("    \"status\": %i\n", error_code);
		}
		log_fmt = String_Format(
			"{\n"
			"%s"
			"%s"
			"    \"message\": \"%s\",\n"
			"}\n",
			(status_str ? status_str : ""),
			(timestamp  ? timestamp  : ""),
			message_str);
		String_Delete(&status_str);
		String_Delete(&message_str);
	}
	else
	{
		if (logger->timestamp)
		{
			t_char* tmp = timestamp;
			timestamp = String_Format("%s"LOG_TIMESTAMP_SEPARATOR, timestamp);
			String_Delete(&tmp);
		}
		t_char* format_str = String_Duplicate(format);
		length = String_Length(format_str);
		if (format_str[length - 1] == '\n')
			format_str[length - 1] = '\0';
		log_fmt = String_Format("%s%s%s%s",
			(timestamp  ? timestamp  : ""),
			(prefix_str ? prefix_str : ""),
			format_str,
			(suffix_str ? suffix_str : ""));
		if (logger->timestamp)
		{
			t_char* tmp = log_fmt;
			log_fmt = String_Replace_String(log_fmt, "\n", "\n" LOG_TIMESTAMP_INDENT LOG_TIMESTAMP_SEPARATOR);
			String_Delete(&tmp);
		}
	}
	String_Delete(&timestamp);
	String_Delete(&prefix_str);
	String_Delete(&suffix_str);

	if (log_fmt == NULL)
	{
		Log_Fatal(logger, "Could not construct log message format string");
		goto failure;
	}
	length = String_Length(log_fmt);
	if (log_fmt[0] != '\0' && log_fmt[length - 1] != '\n')
	{
		log_fmt = Memory_Reallocate(log_fmt, length + 2);
		log_fmt[length + 0] = '\n';
		log_fmt[length + 1] = '\0';
	}
	// NB: a va_list (in this case, 'args') can only be called ONCE (for every va_start), or else will segfault
	log_msg = String_Format_VA(log_fmt, args);
	String_Delete(&log_fmt);
	if (log_msg == NULL)
	{
		Log_Fatal(logger, "Could not construct log message");
		goto failure;
	}
	else
	{
		if (logger->fd > 0)
		{
			t_size	wrote = IO_Write_String(logger->fd, log_msg);
			// logging itself failed
			HANDLE_ERROR_BEGIN(PRINT, (wrote == 0))
				Log_Logger_FatalError(logger, logger->path);
			HANDLE_ERROR_FINAL()
		}
	}
	String_Delete(&log_msg);

	// re-enable error-handling
	for (e_cccerror i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_SetHandler(i, handlers[i]);
	}

	return (OK);

failure:
	// cleanup
	String_Delete(&timestamp);
	String_Delete(&prefix_str);
	String_Delete(&suffix_str);
	String_Delete(&log_fmt);
	String_Delete(&log_msg);

	// re-enable error-handling
	for (e_cccerror i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_SetHandler(i, handlers[i]);
	}

	return (ERROR);
}
