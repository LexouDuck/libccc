
#include <stdarg.h>
#include <errno.h>

#include "libccc.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/time.h"
#include "libccc/sys/logger.h"



static inline void Log_VA_Write(s_logger const* logger, t_fd fd, char const* output, char const* log_msg)
{
	int status = IO_Write_String(fd, log_msg);
	if (status < 0)
	{
		char* tmp = String_Join("Could not write log message to ", output);
		Log_FatalError(logger, tmp);
		String_Delete(&tmp);
	}
}



t_io_error	Log_VA(s_logger const* logger,
	t_bool			verbose_only,
	t_bool			use_errno,
	int				error_code,
	char const*		prefix,
	char const*		prefix_color,
	char const*		format_str,
	va_list			args)
{
	if (( logger->silence_logs   && !error_code) ||
		( logger->silence_errors &&  error_code) ||
		(!logger->verbose        && verbose_only))
		return (OK);

	char*	error_str = NULL;
	if (use_errno)
	{
		error_str = IO_GetError(errno);
	}
	char*	full_format_str = NULL;
	char*	log_msg			= NULL;
	char*	timestamp 		= logger->timestamp ? Logger_GetTimestamp(Time_Now()) : NULL;
/*
	size_t	length = String_Length(time_now_utc);
	if (length > 0 && time_now_utc[length - 1] == '\n')
		time_now_utc[length - 1] = '\0';
*/
	if (logger->format == LOGFORMAT_ANSI)
	{
		if (use_errno)
		{
			full_format_str = String_Format("%s%s%s%s%s%s%s-> %s%s",
				timestamp ? timestamp : "",
				prefix_color ? prefix_color : "",
				prefix,
				prefix_color ? C_RESET": " : "",
				format_str,
				format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n",
				timestamp ? LOG_TIMESTAMP_INDENT : " ",
				error_str,
				error_str[0] != '\0' && error_str[String_Length(error_str) - 1] == '\n' ? "" : "\n");
		}
		else
		{
			full_format_str = String_Format("%s%s%s%s%s%s",
				timestamp ? timestamp : "",
				prefix_color ? prefix_color : "",
				prefix,
				prefix_color ? C_RESET": " : "",
				format_str,
				format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n");
		}
	}
	else if (logger->format == LOGFORMAT_TEXT)
	{
		if (use_errno)
		{
			full_format_str = String_Format("%s%s%s%s%s-> %s%s",
				timestamp ? timestamp : "",
				prefix,
				format_str,
				format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n",
				timestamp ? LOG_TIMESTAMP_INDENT : " ",
				error_str,
				error_str[0] != '\0' && error_str[String_Length(error_str) - 1] == '\n' ? "" : "\n");
		}
		else
		{
			full_format_str = String_Format("%s%s%s%s",
				timestamp ? timestamp : "",
				prefix,
				format_str,
				format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n");
		}
	}
	else if (logger->format == LOGFORMAT_JSON)
	{
		if (use_errno)
		{
			full_format_str = String_Format(
				"\n{"
				"%s%s%s"
				"\n    message: \"%s%s%s"
				"-> %s%s\","
				"\n    status: %d"
				"\n}",
				(timestamp ? "\n    timestamp: " : ""), (timestamp ? timestamp : ""), (timestamp ? ",\n" : ""),
				prefix, format_str, (format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n"),
				error_str, (error_str[0] != '\0' && error_str[String_Length(error_str) - 1] == '\n' ? "" : "\n"),
				error_code
			);
		}
		else
		{
			full_format_str = String_Format(
				"\n{"
				"%s%s%s"
				"\n    message: \"%s%s%s\","
				"\n    status: %d"
				"\n}",
				(timestamp ? "\n    timestamp: " : ""), (timestamp ? timestamp : ""), (timestamp ? ",\n" : ""),
				prefix, format_str, (format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n"),
				error_code
			);
		}
	}
	else
	{
		full_format_str = String_Format(
			"UNIMPLEMENTED LOGGING FORMAT: %d\n"
			"%s%s",
			logger->format,
			format_str, (format_str[0] != '\0' && format_str[String_Length(format_str) - 1] == '\n' ? "" : "\n")
		);
	}
	String_Delete(&timestamp);
	String_Delete(&error_str);

	if (full_format_str == NULL)
	{
		Log_FatalError(logger, "Could not construct log message format string");
		return (ERROR);
	}

	// NB: a va_list (in this case, 'args') can only be called ONCE (for every va_start), or else will segfault
	log_msg = String_Format_VA(full_format_str, args);
	String_Delete(&full_format_str);
	if (log_msg == NULL)
	{
		Log_FatalError(logger, "Could not construct log message");
		return (ERROR);
	}
	else
	{
		if (logger->fd > 0)
		{
			Log_VA_Write(logger,
				logger->fd,
				logger->path,
				log_msg);
		}
	}
	String_Delete(&log_msg);

	return (OK);
}
