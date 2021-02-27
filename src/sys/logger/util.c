
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>

#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"
#include "libccc/sys/time.h"
#include "libccc/sys/io.h"
#include "libccc/sys/logger.h"



t_io_error	Log_FatalError(s_logger const* logger, char const* str)
{
	t_io_error result = OK;
	char const* message = IO_GetError(errno);

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



char*	Logger_GetTimestamp(t_time utc)
{
	static const t_size max = 24;
	char*		result;
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

char*	Logger_GetSettings(s_logger const* logger)
{
	char*		result = NULL;
	char const*	logformat = NULL;

	switch (logger->format)
	{
		case LOGFORMAT_ANSI: logformat = LOGFORMAT_STRING_ANSI; break;
		case LOGFORMAT_TEXT: logformat = LOGFORMAT_STRING_TEXT; break;
		case LOGFORMAT_JSON: logformat = LOGFORMAT_STRING_JSON; break;
		case LOGFORMAT_XML:  logformat = LOGFORMAT_STRING_XML ; break;
		default: break;
	}

	result = String_Format(
		"Logger settings:"
		"\nSilence normal logs and warnings: %s"
		"\nSilence error logs: %s"
		"\nShow TimeStamp: %s"
		"\nVerbose mode: %s"
		"\nObfuscated mode: %s"
		"\nAppend mode: %s"
		"\nFormat mode: %s"
		"\nLogging to fd: %d"
		"\nLogging to file: \"%s\"",
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
	char*	tmp = Logger_GetSettings(logger);
	t_io_error result = Log_Message(logger, "%s", tmp);
	String_Delete(&tmp);
	return (result);
}
