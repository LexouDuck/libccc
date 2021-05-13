
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/sys/time.h"
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



t_io_error	Log_FatalError(s_logger const* logger, t_char const* str)
{
	t_io_error result = OK;
	t_char const* message = IO_GetError(errno);

	if (logger->path && IO_IsTerminal(logger->fd))
	{
		result = IO_Write_Format(logger->fd,
			C_RED"Fatal Error"C_RESET": %s\n\t-> %s\n", str, message);
		if (result)	return (result);
	}
	else
	{
		result = IO_Write_Format(logger->fd,
			"Fatal Error: %s\n%s", str, message);
		if (result)	return (result);
	}
	return (result);
}



t_char*	Logger_GetTimestamp(t_time utc)
{
	static const t_size max = 24;
	t_char*		result;
	s_date	date = Time_ToDate_UTC(utc);
	result = String_New(max);
	if (result == NULL)
		return (NULL);
	Date_ToString_N(result, max, &date, LOG_TIMESTAMP_FORMAT);
	return (result);
}



/*
**	Functions to help debug the logger
*/

t_char*	Logger_GetSettings(s_logger const* logger)
{
	t_char*		result = NULL;
	t_char const*	logformat = NULL;

	switch (logger->format)
	{
		case LOGFORMAT_ANSI: logformat = LOGFORMAT_STRING_ANSI; break;
		case LOGFORMAT_TEXT: logformat = LOGFORMAT_STRING_TEXT; break;
		case LOGFORMAT_JSON: logformat = LOGFORMAT_STRING_JSON; break;
		case LOGFORMAT_XML:  logformat = LOGFORMAT_STRING_XML ; break;
		default: break;
	}
	result = String_Format(
		"\n"LOG_TIMESTAMP_INDENT"\tLogger settings:"
		"\n"LOG_TIMESTAMP_INDENT"\t- Silence normal logs and warnings: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Silence error logs: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Show TimeStamp: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Verbose mode: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Obfuscated mode: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Append mode: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Format mode: %s"
		"\n"LOG_TIMESTAMP_INDENT"\t- Logging to fd: %d"
		"\n"LOG_TIMESTAMP_INDENT"\t- Logging to file: \"%s\"",
		(logger->silence_logs   ? "ON" : "OFF"),
		(logger->silence_errors ? "ON" : "OFF"),
		(logger->timestamp      ? "ON" : "OFF"),
		(logger->verbose        ? "ON" : "OFF"),
		(logger->obfuscated     ? "ON" : "OFF"),
		(logger->append         ? "ON" : "OFF"),
		logformat,
		logger->fd,
		logger->path
	);
	return (result);
}

inline t_io_error	Logger_LogSettings(s_logger const* logger)
{
	t_char*	tmp = Logger_GetSettings(logger);
	t_io_error result = Log_Message(logger, "%s", tmp);
	String_Delete(&tmp);
	return (result);
}
