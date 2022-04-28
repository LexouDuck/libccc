
#include "libccc.h"
#include "libccc/enum.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/json.h"

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
	t_char*	message = NULL;
	t_char*	result = NULL;
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
	for (t_enum i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		handlers[i] = Error_GetHandler((e_cccerror)i);
	}
	Error_SetAllHandlers(Log_Logger_ErrorHandler);

	// Construct log message body from format/variadic arguments
	// NB: a va_list (in this case, 'args') can only be called ONCE (for every va_start), or else will segfault
	message = String_Format_VA(format, args);
	if (message == NULL)
	{
		Log_Fatal(logger, "Could not construct log message body");
		goto failure;
	}
	length = String_Length(message);
	if (message[0] != '\0' && message[length - 1] != '\n')
	{
		message = (t_char*)Memory_Reallocate(message, length + 2);
		message[length + 0] = '\n';
		message[length + 1] = '\0';
	}

	// Get log timestamp string
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
		s_json* json = JSON_CreateObject();
		t_char* message_str = NULL;
		message_str = String_Format("%s%s%s",
			(prefix_str ? prefix_str : ""),
			message,
			(suffix_str ? suffix_str : ""));
		if (message_str == NULL || json == NULL)
		{
			Log_Fatal(logger, "Could not construct log message json");
			goto failure;
		}
		if (logger->timestamp)
		{
			JSON_AddToObject_String(json, "timestamp", timestamp);
		}
		if (error_code)
		{
			JSON_AddToObject_Integer(json, "status", error_code);
		}
//		Error_SetAllHandlers(NULL);
		JSON_AddToObject_String(json, "message", message_str);
//		Error_SetAllHandlers(Log_Logger_ErrorHandler);
		result = JSON_ToString_Minify(json);
		JSON_Delete(json);
		String_Delete(&message_str);
		String_Append(&result, "\n");
	}
	else
	{
		if (logger->timestamp)
		{
			t_char* tmp = timestamp;
			timestamp = String_Format("%s"LOG_TIMESTAMP_SEPARATOR, timestamp);
			String_Delete(&tmp);
		}
		t_char* message_str = String_Duplicate(message);
		length = String_Length(message_str);
		if (message_str[length - 1] == '\n')
			message_str[length - 1] = '\0';
		result = String_Format("%s%s%s%s",
			(timestamp  ? timestamp  : ""),
			(prefix_str ? prefix_str : ""),
			message_str,
			(suffix_str ? suffix_str : ""));
		if (result == NULL)
		{
			Log_Fatal(logger, "Could not construct log message head");
			goto failure;
		}
		if (logger->timestamp)
		{
			t_char* tmp = result;
			result = String_Replace_String(result, "\n", "\n" LOG_TIMESTAMP_INDENT LOG_TIMESTAMP_SEPARATOR);
			String_Delete(&tmp);
		}
	}
	String_Delete(&timestamp);
	String_Delete(&prefix_str);
	String_Delete(&suffix_str);
	String_Delete(&message);

	if (logger->fd > 0)
	{
		t_size	wrote = IO_Write_String(logger->fd, result);
		// logging itself failed
		HANDLE_ERROR_BEGIN(PRINT, (wrote == 0))
			Log_Logger_FatalError(logger, logger->path);
		HANDLE_ERROR_FINAL()
	}
	String_Delete(&result);

	// re-enable error-handling
	for (t_enum i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_SetHandler((e_cccerror)i, handlers[i]);
	}

	return (ERROR_NONE);

failure:
	// cleanup
	String_Delete(&timestamp);
	String_Delete(&prefix_str);
	String_Delete(&suffix_str);
	String_Delete(&message);
	String_Delete(&result);

	// re-enable error-handling
	for (t_enum i = 0; i < ENUMLENGTH_CCCERROR; ++i)
	{
		Error_SetHandler((e_cccerror)i, handlers[i]);
	}

	return (ERROR_PRINT);
}
