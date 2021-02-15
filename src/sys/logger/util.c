
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
	s_logfile const* file;
	char const* message = IO_GetError(errno);

	if (logger->dest_stderr)
	{
		result = IO_Write_Format(STDERR,
			C_RED"Fatal Error"C_RESET": %s\n%s", str, message);
		if (result)	return (result);
	}
	else if (logger->dest_stdout)
	{
		result = IO_Write_Format(STDOUT,
			C_RED"Fatal Error"C_RESET": %s\n%s", str, message);
		if (result)	return (result);
	}
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		file = &logger->dest_files[i];
		if (file->path && IO_IsTerminal(file->fd))
		{
			result = IO_Write_Format(file->fd,
				C_RED"Fatal Error"C_RESET": %s\n%s", str, message);
			if (result)	return (result);
		}
		else
		{
			result = IO_Write_Format(file->fd,
				"Fatal Error: %s\n%s", str, message);
			if (result)	return (result);
		}
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
	char* result = NULL;
	char* filepaths = NULL;
	for (t_uint i = 0; i < LOGFILES_MAX; ++i)
	{
		if (logger->dest_files[i].path)
		{
			if (filepaths == NULL)
				filepaths = String_Duplicate(logger->dest_files[i].path);
			else
			{
				filepaths = String_Append(&filepaths, ", ");
				filepaths = String_Append(&filepaths, logger->dest_files[i].path);
			}
		}
	}
	result = String_Format("Logger settings:"
		"\nShow TimeStamp: %s"
		"\nVerbose mode: %s"
		"\nObfuscated mode: %s"
		"\nLogging to stdout: %s"
		"\nLogging to stderr: %s"
		"\nLogging to files: [%s]",
		(logger->show_timestamp	 ? "ON" : "OFF"),
		(logger->mode_verbose	 ? "ON" : "OFF"),
		(logger->mode_obfuscated ? "ON" : "OFF"),
		(logger->dest_stdout	 ? "ON" : "OFF"),
		(logger->dest_stderr	 ? "ON" : "OFF"),
		filepaths);
	String_Delete(&filepaths);
	return (result);
}

inline t_io_error	Logger_LogSettings(s_logger const* logger)
{
	char*	tmp = Logger_GetSettings(logger);
	t_io_error result = Log_Message(logger, "%s", tmp);
	String_Delete(&tmp);
	return (result);
}
